# Phase 1 概述

在这个阶段，我们将从零开始，编写第一个 C++ 程序，并逐步加入变量、运算和逻辑控制。我们将学习如何与用户交互，并理解现代 C++ 是如何从第一行代码开始就倡导安全和清晰的。

**核心知识点清单：**

1. **程序的基本结构：** `main` 函数、编译与执行
2. **变量与核心数据类型：** 存储和操作数据
3. **运算符：** 执行计算与比较
4. **控制流：** 指导程序的执行路径
5. **基本输入/输出 (I/O)：** 与用户交互

让我们逐一深入。

---

## 1. 程序的基本结构

### 是什么 (What it is)

一个最基础的 C++ 程序由一个名为 `main` 的特殊函数构成。它是操作系统的入口点，即你的程序从这里开始执行。将 C++ 源代码（`.cpp` 文件）转换成计算机可执行文件（如 Windows 上的 `.exe` 或 Linux/macOS 上的可执行文件）的过程称为**编译**。

### 怎么做 (How to do it)

这是经典的 "Hello, World!" 程序，但我们将使用现代风格来写。

**`hello.cpp`**

```cpp
// 1. 包含(include)标准库头文件以获取功能
#include <iostream> // 用于输入输出流，例如打印到控制台

// 2. main 函数是程序的入口点
int main() {
    // 3. 使用 std 命名空间中的 cout 对象，将字符串字面量发送到标准输出
    //    << 是“流插入运算符”
    std::cout << "Hello, North Star!\\n";

    // 4. 从 main 返回 0 表示程序成功执行
    return 0;
}
```

**编译与运行 (在终端中):**
你需要一个 C++ 编译器，如 G++ (GNU C++ Compiler)。

```bash
# -std=c++17 告诉编译器使用 C++17 标准
# -o hello      指定输出的可执行文件名为 hello
# hello.cpp     是你的源文件名
g++ -std=c++17 hello.cpp -o hello

# 运行你的程序
./hello
```

**输出:**

```
Hello, North Star!
```

### 为什么这么做 (Why we do it this way)

- **`#include <iostream>`**：C++ 将其庞大的功能集分散在不同的“头文件”中。`#include` 是一个预处理器指令，它在编译前将 `<iostream>` 文件的内容“粘贴”到你的代码中，从而让你能使用 `std::cout`。这是一种模块化的设计。
- **`int main()`**：`int` 表示 `main` 函数在执行完毕后会返回一个整数给操作系统。这个整数是一个状态码，`0` 按惯例表示成功，任何非零值表示发生了错误。这是程序与启动它的环境（如脚本、操作系统）进行通信的基本方式。
- **`std::cout`**：`std` 是一个**命名空间 (namespace)**。C++ 标准库的所有内容都定义在 `std` 命名空间内，以避免与你自己的代码或第三方库中的同名函数/对象产生冲突。`::` 是作用域解析运算符，告诉编译器 `cout` 属于 `std`。这种做法避免了所谓的“命名空间污染”。

### 关联与替代方案 (Associated Concepts & Alternatives)

- **头文件 vs. C++20 模块**: `#include` 是 C++ 的传统方式。它的主要缺点是效率较低（同一个头文件可能被反复处理）且容易暴露实现细节。C++20 引入了**模块 (Modules)** (`import <iostream>;`)，它旨在取代头文件，提供更快的编译速度和更好的封装，但目前尚未被所有编译器和构建系统完全支持。
- **命名空间 (`namespace`)**: 除了使用 `std::` 前缀，你也可以使用 `using` 声明：**对比**: `std::` 前缀最清晰、最安全。`using` 声明是折中方案。`using namespace std;` 在简单的 `.cpp` 文件中尚可接受，但在头文件中是绝对禁止的，因为它会污染所有包含该头文件的代码的全局命名空间。
    
    ```cpp
    using std::cout; // 只引入 cout
    cout << "Hello!\\n";
    
    // 或者 (强烈不推荐在头文件中使用)
    using namespace std; // 引入 std 中的所有名称
    cout << "Hello!\\n";
    ```
    
- **返回值**: `return 0;` 是标准做法。你也可以使用 `<cstdlib>` 头文件中的 `EXIT_SUCCESS` 和 `EXIT_FAILURE` 宏，它们更具可读性：`return EXIT_SUCCESS;`。在 `main` 函数中，如果你不写 `return 0;`，编译器会自动为你添加一个，但这被认为是不良风格。

---

## 2. 变量与核心数据类型

### 是什么

**变量**是内存中一块具名的数据存储区域。**数据类型**定义了这块内存可以存储什么样的数据（如整数、小数、字符）以及可以对它执行哪些操作。C++ 是一个**静态类型**语言，意味着每个变量的类型必须在编译时就确定下来，且不能改变。

### 怎么做

```cpp
#include <iostream>

int main() {
    // 声明并初始化变量
    int age = 30;                 // 整数
    double price = 19.99;         // 双精度浮点数 (小数)
    char grade = 'A';             // 单个字符
    bool is_active = true;        // 布尔值 (true 或 false)

    // C++11 引入的“统一初始化”语法，更安全
    int score{95};

    // 修改变量的值
    age = 31;

    std::cout << "Age: " << age << "\\n";
    std::cout << "Price: " << price << "\\n";
    std::cout << "Score: " << score << "\\n";
    std::cout << "Is Active: " << is_active << "\\n"; // bool 值会打印为 1 或 0

    return 0;
}
```

### 为什么这么做

- **静态类型**：这是 C++ 性能和安全的核心基石。编译器在编译时就知道 `age` 是一个整数，所以它可以生成最高效的机器码来进行整数运算。同时，如果你尝试做一些无意义的操作，比如 `age * "hello"`，编译器会直接报错，而不是等到运行时才崩溃。
- **统一初始化 (`{}`)**：使用花括号进行初始化（如 `int score{95};`）被认为是更现代、更安全的方式。它不允许“窄化转换”（narrowing conversion），例如，你不能把一个浮点数放进一个整数里而丢失信息，编译器会警告或报错：`int some_value{7.7}; // 错误!`。而 `int some_value = 7.7; // C风格初始化，7.7 被截断为 7，信息丢失`。

### 关联与替代方案

- **基本类型全景**:
    - **整型**: `short`, `int`, `long`, `long long` (尺寸递增)。每个都可以用 `signed` (默认) 或 `unsigned` 修饰。`unsigned int` 只能表示非负数，但表示范围更大。
    - **浮点型**: `float` (单精度), `double` (双精度), `long double` (扩展精度)。`double` 是最常用的。
    - **字符型**: `char`, `wchar_t`, `char16_t`, `char32_t` (用于支持 Unicode 字符集)。
- **`auto` 类型推导 (C++11)**: 当变量的初始值类型显而易见时，可以使用 `auto` 让编译器自动推断其类型。**对比**: `auto` 可以减少代码冗余，在处理复杂类型名（如迭代器）时尤其有用。但过度使用会降低代码可读性，因为读者需要通过初始值来判断类型。
    
    ```cpp
    auto my_age = 30;           // 推导为 int
    auto my_price = 19.99;      // 推导为 double
    auto is_ok = true;          // 推导为 bool
    ```
    
- **常量 (`const` 与 `constexpr`)**:
**对比**: 所有 `constexpr` 都是 `const`，但并非所有 `const` 都是 `constexpr`。`const` 变量可能由函数返回值等在运行时才能确定的值初始化。优先使用 `constexpr` 表示真正意义上的、在编译期就已知的常量。
    - `const`: 用于声明一个运行时常量，其值在初始化后不能被修改。
    
    ```cpp
    const double PI = 3.14159;
    // PI = 4; // 编译错误！
    ```
    
    - `constexpr` (C++11): 用于声明一个**编译时**常量。编译器在编译程序时就会计算出它的值。这允许进行更深度的优化，并且 `constexpr` 变量可以用在需要编译时常量的上下文中（如数组大小）。
    
    ```cpp
    constexpr int MAX_USERS = 100; // 在编译时就确定为 100
    int user_data[MAX_USERS];      // 合法
    ```
    
- **类型别名 (`using`)**: 使用 `using` 关键字可以为现有类型创建新的名字，使其更具可读性。
这是 C++11 推荐的语法，它比旧的 `typedef double Price;` 更清晰，并且在模板编程中更强大。
    
    ```cpp
    using Price = double;
    using UserID = int;
    
    Price item_price = 99.9;
    UserID user_id = 12345;
    
    ```
    

---

## 3. 运算符 (Operators)

### 是什么 (What it is)

**运算符**是 C++ 语言中预定义的特殊符号，用于对一个或多个**操作数**（变量或值）执行特定操作，如算术计算、比较、逻辑判断等，并产生一个结果。它们是构成 C++ 表达式的基石。

### 怎么做 (How to do it)

我们将通过一个综合示例来演示各类常用运算符。

```cpp
#include <iostream>

int main() {
    int a = 10, b = 4;

    // 1. 算术运算符 (Arithmetic Operators)
    std::cout << "a + b = " << (a + b) << "\\n"; // 加法: 14
    std::cout << "a - b = " << (a - b) << "\\n"; // 减法: 6
    std::cout << "a * b = " << (a * b) << "\\n"; // 乘法: 40
    std::cout << "a / b = " << (a / b) << "\\n"; // 整数除法: 2 (小数部分被截断)
    std::cout << "a % b = " << (a % b) << "\\n"; // 取模 (余数): 2

    // 2. 关系运算符 (Relational Operators) -> 结果为 bool
    std::cout << "a > b is " << (a > b) << "\\n";   // 大于: 1 (true)
    std::cout << "a == 10 is " << (a == 10) << "\\n"; // 等于: 1 (true)
    std::cout << "a != b is " << (a != b) << "\\n";   // 不等于: 1 (true)

    // 3. 逻辑运算符 (Logical Operators) -> 用于组合 bool 表达式
    bool is_sunny = true;
    bool has_time = false;
    std::cout << "Go out? " << (is_sunny && has_time) << "\\n"; // AND: 0 (false)
    std::cout << "Stay home? " << (is_sunny || has_time) << "\\n"; // OR: 1 (true)
    std::cout << "Not sunny? " << (!is_sunny) << "\\n";           // NOT: 0 (false)

    // 4. 赋值运算符 (Assignment Operators)
    int c = 15;
    c += 5; // 等价于 c = c + 5; 现在 c 是 20
    std::cout << "c is " << c << "\\n";
    c *= 2; // 等价于 c = c * 2; 现在 c 是 40
    std::cout << "c is now " << c << "\\n";

    return 0;
}
```

### 为什么这么做 (Why we do it this way)

- **运算符优先级与结合性 (Precedence and Associativity)**：C++ 为运算符定义了严格的优先级规则（如  和 `/` 优先于 `+` 和 ）和结合性规则（如大多数运算符是左结合，即 `a-b-c` 等价于 `(a-b)-c`）。这是为了让表达式的求值顺序符合数学直觉。**最佳实践**：当不确定优先级时，**永远使用括号 `()`** 来明确指定求值顺序，这能极大地提升代码的可读性和正确性。
- **类型决定行为**：`a / b` 的结果是 `2` 而不是 `2.5`，这是 C++ 静态类型系统的直接体现。因为 `a` 和 `b` 都是 `int`，所以编译器执行的是**整数除法**。要获得浮点数结果，至少有一个操作数必须是浮点类型，例如 `static_cast<double>(a) / b`。

### 关联与替代方案 (Associated Concepts & Alternatives)

- **自增/自减运算符 (`++`/`-`)**:
    - **前缀形式**: `++a` (先加1，后使用 `a` 的新值)。
    - **后缀形式**: `a++` (先使用 `a` 的旧值，后对 `a` 加1)。
    
    ```cpp
    int i = 5;
    int j = ++i; // i 变为 6, j 被赋值为 6
    int k = i++; // k 被赋值为 6, i 变为 7
    ```
    
    **对比与建议**: 两者在独立使用时（如 `i++;`）没有区别。但在表达式中，它们的行为不同。对于内置类型（如 `int`），编译器通常能优化掉差异。但对于复杂类型（如迭代器），**前缀形式效率更高**，因为它直接修改并返回对象本身，而后缀形式需要创建一个临时对象来存储原始值。因此，**养成优先使用前缀形式的习惯**是现代 C++ 的一个良好实践。
    
- **位运算符 (Bitwise Operators)**: `&` (按位与), `|` (按位或), `^` (按位异或), `~` (按位取反), `<<` (左移), `>>` (右移)。
    - 这些运算符直接操作整数的二进制位，是 C++ "贴近硬件"特性的体现。
    - **应用场景**: 性能敏感的代码（移位比乘除快）、硬件编程、数据压缩、加密算法、以及用单个整数作为“标志位集合”（bitmasking）。
    - **注意**: 不要将位运算符 `&`, `|` 与逻辑运算符 `&&`, `||` 混淆。
- **短路求值 (Short-circuit Evaluation)**:
    - 对于逻辑与 `&&`：如果左侧表达式为 `false`，则右侧表达式**根本不会被求值**。
    - 对于逻辑或 `||`：如果左侧表达式为 `true`，则右侧表达式**根本不会被求值**。
    - **应用**: 这不仅是性能优化，更是重要的安全和逻辑控制手段。
    
    ```cpp
    // 安全用法：如果指针为空，则不会执行后面的解引用操作，避免程序崩溃。
    if (ptr != nullptr && ptr->is_valid()) { ... }
    ```
    
- **运算符重载 (Operator Overloading)**:
    - 这是 C++ 一个极为强大的特性（我们将在 Phase 3 深入），它允许你为自定义类型（`class` 或 `struct`）定义标准运算符的行为。
    - **示例**: `std::string` 重载了 `+` 来实现字符串拼接；`std::cout` 重载了 `<<` 来实现流式输出。这使得自定义类型的行为能像内置类型一样自然、直观。

---

## 4. 控制流 (Control Flow)

### 是什么 (What it is)

**控制流**决定了程序中语句的执行顺序。默认情况下，代码是自上而下顺序执行的。控制流语句允许我们根据条件执行不同的代码分支（**选择**）或重复执行某段代码（**循环**）。

### 怎么做 (How to do it)

```cpp
#include <iostream>
#include <vector> // 我们会提前使用一个简单的数据容器

int main() {
    // 1. 选择: if-else if-else
    int temperature = 25;
    if (temperature > 30) {
        std::cout << "It's hot.\\n";
    } else if (temperature < 10) {
        std::cout << "It's cold.\\n";
    } else {
        std::cout << "It's pleasant.\\n";
    }

    // 2. 选择: switch
    char grade = 'B';
    switch (grade) {
        case 'A':
            std::cout << "Excellent!\\n";
            break; // 必须有 break，否则会“贯穿”
        case 'B':
            std::cout << "Good.\\n";
            break;
        case 'C':
            std::cout << "Pass.\\n";
            break;
        default:
            std::cout << "Invalid grade.\\n";
            break;
    }

    // 3. 循环: for 循环
    for (int i = 0; i < 3; ++i) { // 经典的计数循环
        std::cout << "For loop iteration: " << i << "\\n";
    }

    // 4. 循环: while 循环
    int countdown = 3;
    while (countdown > 0) {
        std::cout << "Countdown: " << countdown << "\\n";
        --countdown;
    }

    // 5. 循环: 范围 for 循环 (C++11+) - 更现代的方式
    std::vector<int> numbers = {10, 20, 30};
    for (int num : numbers) { // 遍历容器中的每个元素
        std::cout << "Number in vector: " << num << "\\n";
    }

    return 0;
}
```

### 为什么这么做 (Why we do it this way)

- **意图明确**: 选择不同的控制流结构是为了清晰地表达你的编程意图。`for` 循环天然地适用于已知次数的迭代。`while` 循环适用于当循环条件在循环体内部动态变化的场景。`if-else` 链条用于处理复杂的、非互斥的条件。`switch` 用于处理基于单个离散值的多路分支。
- **现代 C++ 的作用域控制 (C++17)**: C++17 引入了带初始化的 `if` 和 `switch` 语句，这是一个重要的进步。
这增强了代码的封装性，避免了变量“泄露”到外部作用域，减少了命名冲突和逻辑错误。
    
    ```cpp
    // score 变量的作用域被严格限制在 if-else 块内部
    if (int score = get_score(); score > 90) {
        std::cout << "High score!\\n";
    } else {
        std::cout << "Low score.\\n";
    }
    // 在这里无法访问 score，因为它已经超出了作用域
    ```
    

### 关联与替代方案 (Associated Concepts & Alternatives)

- **`switch` vs. `if-else if`**:
    - **适用性**: `switch` 只能对单个**整型、字符型或枚举类型**的变量进行判断。`if-else if` 可以处理任何返回 `bool` 的复杂条件表达式（如范围 `x > 0 && x < 10`、不同变量的组合）。
    - **性能**: 对于多路分支，`switch` 通常比 `if-else` 链更高效，因为编译器可以将其优化为一个**跳转表 (jump table)**，实现 O(1) 复杂度的分支，而 `if-else` 链是 O(n) 的顺序比较。
    - **可读性**: 当分支逻辑基于同一个变量的多个离散值时，`switch` 结构更清晰。
- **循环类型对比 (`for` vs. `while` vs. `do-while`)**:
    - **`for`**: 最佳选择当循环次数在开始时已知或可以计算得出时。它将初始化、条件和迭代表达式集中在一处，结构清晰。
    - **`while`**: 循环前检查条件。如果条件初始为 `false`，循环体一次都不会执行。适用于循环次数未知，依赖于某个外部条件的情况。
    - **`do-while`**: 循环后检查条件。循环体**至少会执行一次**。适用于需要先执行一次操作再判断是否继续的场景（如读取用户输入并验证）。`do { ... } while (condition);`
- **范围 `for` 循环 (`for-each`)**:
    - 这是 C++11 引入的语法糖，是遍历标准库容器（如 `std::vector`, `std::string`）、数组或任何定义了 `begin()` 和 `end()` 函数的对象的**首选方式**。
    - **优势**: 代码更简洁、可读性更高，并且从根本上消除了手动管理索引和迭代器时可能出现的“差一错误”（off-by-one errors）。
- **三元条件运算符 (`? :`)**:
    - 它是 `if-else` 语句的紧凑形式，用于根据条件返回两个值中的一个。
    - **语法**: `condition ? expression_if_true : expression_if_false;`
    - **示例**: `int max_val = (a > b) ? a : b;`
    - **对比**: 非常适合用于简单的值选择和赋值。但如果逻辑复杂，或需要在分支中执行多个语句，则应使用完整的 `if-else` 结构，否则会严重损害可读性。过度嵌套的三元运算符是代码的“毒药”。
- **流程控制关键字 (`break`, `continue`, `goto`)**:
    - `break`: 立即终止并跳出**最内层**的循环或 `switch` 语句。
    - `continue`: 立即结束**当前**循环迭代，跳到循环的下一次迭代判断处。
    - `goto`: 无条件跳转到程序中由标签 (`label:`) 标识的任意位置。在现代 C++ 中，`goto` **应极力避免使用**，因为它会破坏代码的结构化，使其难以理解和维护（所谓的“面条代码”）。其极少数的合理用途（如跳出深层嵌套循环）通常可以用更好的结构（如将循环封装进函数并使用 `return`）来替代。

---

## 5. 基本输入/输出 (I/O)

### 是什么 (What it is)

I/O 是指程序与外部世界（通常是控制台/终端）进行数据交换。C++ 通过其标准库中的 **iostream** 库提供了一套类型安全、可扩展的流式 I/O 机制。

- `std::cout`: 标准输出流 (character output)，通常是屏幕。
- `std::cin`: 标准输入流 (character input)，通常是键盘。

### 怎么做 (How to do it)

```cpp
#include <iostream>
#include <string> // 用于 std::string 和 std::getline

int main() {
    // 输出
    std::cout << "Please enter your name: ";

    // 输入
    std::string name;
    // std::cin >> name; // 这个方法遇到空格会停止读取
    std::getline(std::cin, name); // 读取一整行，直到按下回车

    std::cout << "Please enter your age: ";
    int age;
    std::cin >> age;

    // 链式输出
    std::cout << "Hello, " << name
              << "! You are " << age << " years old.\\n";

    return 0;
}
```

### 为什么这么做 (Why we do it this way)

- **类型安全 (Type Safety)**: `iostream` 的核心优势。当你写 `std::cin >> age;` 时，流对象知道 `age` 是一个 `int`，它会自动尝试将用户的输入文本解析为整数。如果你输入了非数字字符，流会进入一个错误状态，你可以对此进行检查。这与 C 语言的 `scanf("%d", &age)` 形成对比，后者需要程序员手动保证格式说明符 `%d` 与变量类型匹配，一旦失配就可能导致未定义行为。
- **可扩展性 (Extensibility)**: 通过重载 `<<` 和 `>>` 运算符，你可以让你自己的类和结构体无缝地与 `iostream` 一起工作。比如 `std::cout << my_vector;` 就可以被实现。

### 关联与替代方案 (Associated Concepts & Alternatives)

- **`std::cin` 的陷阱与 `std::getline`**:
    - `operator>>` 默认以空白字符（空格、制表符、换行符）作为分隔符。因此 `std::cin >> name;` 无法读取包含空格的名字（如 "Lilian Weng"）。
    - `std::getline(std::cin, line);` 是读取整行文本的标准方法。
    - **混合使用的坑**: 在使用 `std::cin >> some_var;` 后，换行符 `\\n` 会残留在输入缓冲区中。如果紧接着调用 `std::getline`，它会立即读到这个换行符并返回一个空字符串。标准解法是在两者之间清除缓冲区：
    
    ```cpp
    std::cin >> age;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\\n'); // 忽略掉缓冲区里剩下的所有内容，直到下一个换行符
    std::getline(std::cin, name);
    ```
    
- **C-Style I/O (`<cstdio>`)**:
    - C++ 为了兼容 C，也支持 `<cstdio>` 头文件中的 `printf` 和 `scanf` 函数。
    - **对比**:
        - `printf`: 提供了非常强大的格式化输出能力（如 `printf("%04d", 12);` 输出 `0012`），在某些场景下可能比 `iostream` 的操纵符更直接，且历史上被认为性能更高（尽管现代编译器已经大大缩小了差距）。
        - `scanf`: **强烈不推荐使用**。它不是类型安全的，且极易导致缓冲区溢出等安全漏洞，是 C 语言程序中最常见的 bug 来源之一。
    - 在现代 C++ 中，除非有特殊的性能或格式化需求，否则应坚持使用 `iostream`。
- **流操纵符 (Stream Manipulators)**:
    - 定义在 `<iomanip>` 头文件中的函数，用于在流中改变输出格式。
    - `std::setw(n)`: 设置下一个输出项的字段宽度。
    - `std::setprecision(n)`: 设置浮点数的输出精度。
    - `std::fixed`: 使用定点表示法输出浮点数。
    - `std::left`/`std::right`: 设置对齐方式。
    - **示例**: `std::cout << std::fixed << std::setprecision(2) << 12.3456;` 会输出 `12.35`。
- **C++20 `<format>` 库**:
    - 这是 C++ I/O 和字符串格式化的未来。它由著名的 {fmt} 库标准化而来。
    - 它结合了 `printf` 的简洁格式化语法和 `iostream` 的类型安全与可扩展性。
    - **示例**:
    
    ```cpp
    #include <format>
    std::string message = std::format("Hello, {}! You are {} years old.", name, age);
    std::cout << message;
    ```
    
    - **优势**: 性能极高，语法清晰，类型安全，是未来 C++ 代码中格式化字符串和输出的**最佳实践**。

---

## Phase 1 实践练习：简易文本角色扮演游戏 (RPG) 属性生成器

这个练习将融合你在 Phase 1 学到的所有知识：变量、I/O、运算符和控制流。

### **目标**

编写一个程序，为一位新的 RPG 角色生成初始属性，并根据这些属性分配一个职业。

### **程序要求**

1. **欢迎与输入**:
    - 程序启动后，欢迎玩家。
    - 提示玩家输入角色的名字，并能正确处理带空格的名字（例如 "Kaiming He"）。
2. **属性生成**:
    - 为角色生成三项核心属性：力量 (Strength)、敏捷 (Agility)、智力 (Intelligence)。
    - 每项属性的值应该是一个在 5 到 20 之间的随机整数。
3. **属性点分配**:
    - 告知玩家他们有额外的 10 个属性点可以自由分配。
    - 使用一个循环，让玩家逐点或批量地将这 10 个点数分配到三项属性上，直到点数用完。
    - 在每次分配后，显示剩余的点数和更新后的各项属性值。
4. **职业分配**:
    - 根据最终的属性值，使用 `if-else if-else` 逻辑为角色分配一个职业：
        - 如果 **力量** 是最高属性，且大于 15，角色是 **“战士 (Warrior)”**。
        - 如果 **敏捷** 是最高属性，且大于 15，角色是 **“盗贼 (Rogue)”**。
        - 如果 **智力** 是最高属性，且大于 15，角色是 **“法师 (Mage)”**。
        - 如果没有任何一项属性特别突出，或者最高属性没到 15，角色是 **“新手 (Novice)”**。
5. **最终展示**:
    - 清屏或用分界线隔开，然后清晰地展示角色的最终信息：名字、三项最终属性值、分配的职业。

### **代码与概念提示**

- **随机数**: 在现代 C++ 中，使用 `<random>` 头文件来生成高质量的随机数。这是一个比 C 风格的 `rand()` 好得多的选择。
    
    ```cpp
    #include <random>
    // 在 main 函数开头创建一次
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(5, 20);
    // 之后每次需要随机数时调用
    int strength = distrib(gen);
    
    ```
    
- **输入处理**: 别忘了 `std::getline` 用于读取名字，以及在混合使用 `std::cin >>` 和 `std::getline` 时可能需要处理的输入缓冲区问题。
- **控制流**: 你会用到 `for` 或 `while` 循环来处理属性点分配，以及 `if-else` 链条来进行职业判断。
- **运算符**: 你需要算术运算符来更新属性，关系运算符来进行逻辑判断。

### **奖励挑战 (Bonus Challenge)**

1. **使用 `switch`**: 将最终的职业（可以用一个 `char` 或 `int` 来代表）传入一个 `switch` 语句，为每个职业输出一句独特的欢迎语。
2. **输入验证**: 当用户分配属性点时，如果他们输入的数字无效（比如负数，或者超过了剩余的点数），程序应该给出提示并要求重新输入，而不是崩溃或接受错误的值。

这个练习完成后，你对 Phase 1 的理解将非常牢固。现在，让我们怀着对性能和底层控制的全新关注，正式开启下一阶段。

---
