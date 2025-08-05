/* 
### 练习 2: 动态命名的形状 (难度: ★★☆☆☆)

**目标**: 创建一个 `NamedShape` 类，它有一个在堆上动态分配的名字，并能正确管理这块内存。

**涉及知识点**: 手动内存管理 (`new[]`/`delete[]`), 指针成员, RAII, 构造函数, 析构函数, 字符串处理。

**任务要求**:

1. 设计一个 `NamedShape` 类。
2. 它有一个 `private` 的 `char*` 成员变量 `shapeName_`，用于存储形状的名字（如 "Circle", "Square"）。
3. **构造函数** `NamedShape(const char* name)`:
    - 接收一个 C 风格字符串作为名字。
    - 在构造函数内部，你必须在**堆上**分配一块新的内存，其大小要足以容纳传入的名字。
    - 使用 `strcpy` 或类似的函数将传入的名字拷贝到你新分配的堆内存中。
4. **析构函数** `~NamedShape()`:
    - 必须在这里 `delete[]` 掉构造函数中分配的 `shapeName_` 的内存，以防止内存泄漏。
5. 提供一个 `public` 成员函数 `const char* getName()` 来返回形状的名字。
6. 在 `main` 函数中，在一个 `{}` 代码块内创建几个 `NamedShape` 对象。当程序执行离开这个代码块时，通过打印日志等方式，验证析构函数是否被自动调用。

---
*/
#include <iostream>
#include <cstring> // 包含了 strcpy, 但也包含了 strlen

// [评价-命名] 类名 `NameShape` 和练习描述中的 `NamedShape` 不一致，这是一个小笔误。
// 在实际项目中，保持命名一致性非常重要。我们以代码中的 `NameShape` 为准进行分析。
class NameShape
{
private:
    char* shapeName_; // 指向动态分配的字符串的指针

public:
    // 构造函数 - 接收一个C风格字符串作为形状名称
    NameShape(const char* name)
    {
        // [评价-逻辑] 这段手动计算长度的代码功能上是正确的，但 C++ 标准库在 <cstring> 中
        // 提供了 `strlen()` 函数来完成完全相同的工作。重复造轮子在实际工程中应尽量避免，
        // 因为标准库的实现通常更高效、经过了充分测试。
        int len {0};
        while (name[len] != '\0')
        {
            ++len;
        }

        // [评价-语法/安全] `new char[len + 1]` 的写法是正确的，为字符串和末尾的 null 终止符 `\0` 分配了空间。
        this->shapeName_ = new char[len + 1];

        // [评价-安全] `strcpy` 是一个“不安全”的函数。它不检查目标缓冲区的大小，
        // 如果源字符串的长度（由外部传入的 `name`）超过了我们计算并分配的 `len`，就会导致缓冲区溢出，
        // 这是 C/C++ 中最常见的安全漏洞之一。虽然在此处逻辑中 `len` 是根据 `name` 计算的，
        // 不会溢出，但在更复杂的代码中依赖 `strcpy` 依然风险很高。
        // C++11 提供了更安全的 `strcpy_s`，或者至少可以使用 `strncpy`。
        strcpy(this->shapeName_, name);
        std::cout << "shapeName_ 的地址已经被创建 \n";
    }

    // 析构函数 - 释放动态分配的内存，防止内存泄漏
    ~NameShape()
    {
        // [评价-语法/正确性] `delete[] shapeName_` 是【完全正确】的！
        // 使用 `new[]` 分配的内存必须用 `delete[]` 释放。用 `delete` 会导致未定义行为。
        // 你正确地匹配了它们，这是手动内存管理中最关键的一步。
        delete[] shapeName_;
        std::cout << "shapeName_ 地址已经被删除 \n";
    }

    // 获取形状名称的公共方法
    // [评价-语法] 这个函数应该被标记为 `const`，即 `const char* getName() const`。
    // 因为它只是返回一个指针，没有（也不应该）修改 `NameShape` 对象的任何状态。
    // `const` 正确性是 C++ 中非常重要的概念，它能让编译器帮你检查无意的修改。
    const char* getName()
    {
        return this->shapeName_;
    }

    // [评价-逻辑/重大缺陷] 这个类缺少了【拷贝构造函数】和【拷贝赋值运算符】的自定义实现。
    // 如果不写，编译器会自动生成它们。但编译器生成的版本只会进行“浅拷贝”(Shallow Copy)，
    // 即直接复制 `shapeName_` 指针的值。
    //
    // 假设你这么做:
    // NameShape a("Circle");
    // NameShape b = a;  // 调用默认拷贝构造函数
    //
    // 现在 `a.shapeName_` 和 `b.shapeName_` 指向【同一块】堆内存。
    // 当 a 和 b 离开作用域时，它们的析构函数都会被调用，都会试图 `delete[]` 这块内存。
    // 第二次 delete 就是“重复释放”，会导致程序崩溃。
    // 这就是著名的“三法则”(The Rule of Three)：如果你需要自己写析构函数、拷贝构造函数、拷贝赋值运算符中的任何一个，
    // 那你几乎肯定需要把它们三个都写全。
};

int main()
{
    // [评价-结构] 使用 `{}` 块来限定 `test` 对象的生命周期，从而清晰地展示析构函数的自动调用，
    // 这是对 RAII 原则的一个绝佳演示。做得非常好！
    {
        NameShape test("name");
        std::cout << test.getName() << "\n";
    } // `test` 在这里被销毁，`~NameShape()` 被调用。

    // [评价-总分]
    // - 结构 (Structure): 8/10。类结构清晰，main函数中的测试方法也很巧妙。
    // - 语法 (Syntax): 7/10。核心内存管理语法正确，但缺少 const 正确性。
    // - 逻辑与安全 (Logic & Safety): 4/10。成功实现了构造和析构的配对，但完全忽略了拷贝语义，这在实际使用中是致命的缺陷。
    //
    // 总结: 这是一个非常好的“C with Classes”风格的实现。它揭示了C++手动内存管理的陷阱，是理解现代C++为何如此设计的完美反面教材。
    
    return 0;
}
