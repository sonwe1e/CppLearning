#include <iostream>
#include <string>   // 【核心改进】引入 <string> 头文件
#include <utility>  // 为了使用 std::move

// 在现代C++中，这个类的名字应该更符合其描述
class NamedShape
{
private:
    // 【核心改进】使用 std::string 替换 char*
    // std::string 是一个类，它在内部为你封装了所有复杂的内存管理细节：
    // - 它会自动在堆上分配内存来存储字符串。
    // - 当字符串需要变长或变短时，它会自动处理内存的重新分配。
    // - 它的析构函数会自动释放所管理的内存。
    // - 它的拷贝构造函数和赋值运算符会执行“深拷贝”，确保每个对象都有自己独立的字符串副本。
    // 这意味着我们不再需要手动 new/delete，也自然地解决了原始代码中的重复释放问题。
    std::string shapeName_;

public:
    // 【构造函数改进】
    // 我们可以提供多个重载版本，让类的使用更灵活。

    // 1. 接收一个 C 风格字符串 (const char*)
    // `explicit` 关键字防止 `NamedShape shape = "Circle";` 这种可能引起混淆的隐式转换。
    // 初始化列表 `: shapeName_(name)` 会直接调用 `std::string` 的构造函数，
    // 它会完成所有分配和拷贝工作，代码简洁、高效且安全。
    explicit NamedShape(const char* name) : shapeName_(name)
    {
        std::cout << "NamedShape '" << shapeName_ << "' created from const char*.\n";
    }

    // 2. 接收一个 std::string 对象
    // 使用 const 引用 `const std::string&` 避免不必要的拷贝。
    explicit NamedShape(const std::string& name) : shapeName_(name)
    {
        std::cout << "NamedShape '" << shapeName_ << "' created from std::string.\n";
    }

    // 【析构函数改进】
    // 我们不再需要手动编写析构函数来释放内存了！
    // 当一个 NamedShape 对象被销毁时，它的成员 `shapeName_` (一个 std::string 对象) 会被自动销毁。
    // `std::string` 的析构函数会负责释放它所占用的堆内存。
    // 这就是“零法则”(The Rule of Zero) 的体现：如果你的类成员本身就能很好地管理资源，
    // 你就不需要为你的类编写任何特殊的资源管理函数（析构、拷贝、移动等）。
    // 这里我们保留一个析构函数只是为了打印信息，验证其被调用。
    ~NamedShape()
    {
        std::cout << "NamedShape '" << shapeName_ << "' destroyed. (No manual delete needed!)\n";
    }

    // 【Getter 改进】
    // 返回一个 const 引用，这是最高效的方式。
    // 它既不允许调用者修改内部的 shapeName_，也避免了返回一个新 string 对象带来的拷贝开销。
    // 函数本身也标记为 const，因为它不修改对象状态。
    const std::string& getName() const
    {
        return shapeName_;
    }

    // 【自动获得的健壮性】
    // 因为 `std::string` 已经正确实现了拷贝构造、拷贝赋值、移动构造和移动赋值，
    // 编译器为 NamedShape 自动生成的对应版本也会自动调用 `std::string` 的版本，
    // 从而使 NamedShape 类自动变得“拷贝安全”和“移动高效”。
    // 这就是组合的力量，我们通过组合一个行为正确的类，让我们的新类也行为正确。
};

int main()
{
    std::cout << "--- Entering scope ---\n";
    {
        // 创建对象，构造函数被调用
        NamedShape circle("Circle");
        std::cout << "Shape 1 is: " << circle.getName() << "\n\n";
        
        // 【验证拷贝安全性】
        // 下面这行在原始代码中会导致灾难，但在这里是完全安全的。
        NamedShape circle_copy = circle; // 调用编译器生成的拷贝构造函数
        std::cout << "Shape 2 (a copy) is: " << circle_copy.getName() << "\n";
        // circle 和 circle_copy 现在拥有各自独立的、内容相同的 "Circle" 字符串。
    } // 当离开作用域时, circle_copy 和 circle 的析构函数会依次被调用。
    std::cout << "--- Exited scope ---\n";

    return 0;
}
