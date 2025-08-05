# Phase 3: 面向对象编程 (Building Abstractions)

**核心目标**: 学习如何使用 `struct` 和 `class` 将数据和操作这些数据的函数封装在一起，从而创造出新的、强大的、可复用的**类型**。这是构建大型、复杂、可维护软件系统的基石。

**本阶段我们将探索**:

1. **`struct` vs. `class`**: 从数据聚合到真正的抽象。
2. **封装 (Encapsulation)**：成员变量与成员函数，以及 `public` vs. `private`。
3. **构造与析构 (Construction & Destruction)**：对象的生命周期管理与 RAII 的实现。
4. **继承 (Inheritance)**：代码复用与“is-a”关系。
5. **多态 (Polymorphism)**：使用虚函数实现动态行为。

---

## 1. `struct` vs. `class`

### 是什么 (What it is)

`struct` (结构体) 和 `class` (类) 都是 C++ 中用来创建自定义类型的关键字。它们允许你将不同的变量（**成员变量**）组合成一个逻辑单元。

- **`struct`**: 最初从 C 语言继承而来，其传统用途是作为一个纯粹的**数据聚合体 (Plain Old Data, POD)**。你可以把它看作一个没有行为、只有一堆公开数据的“包裹”。
- **`class`**: C++ 对 `struct` 的扩展，其核心思想是**数据与操作数据的函数绑定在一起**，并提供**访问控制**。这是实现面向对象编程 (OOP) 的主要工具。

在现代 C++ 中，`struct` 和 `class` 的功能**几乎完全一样**，唯一的区别在于：

- `struct` 的成员默认是 **`public`** (公开的)。
- `class` 的成员默认是 **`private`** (私有的)。

### 怎么做 (How to do it)

让我们定义一个表示 2D 点的类型，分别用 `struct` 和 `class` 来实现。

**`types_demo.cpp`**

```cpp
#include <iostream>
#include <cmath> // For std::sqrt

// --- 使用 struct：默认成员为 public ---
// 适用于简单的数据结构，直接访问是可以接受的。
struct PointStruct {
    // 默认情况下，这些成员是 PUBLIC（公共的）
    double x;
    double y;
};

// --- 使用 class：默认成员为 private ---
// 适用于需要维护“不变性”（规则）的类型。
class PointClass {
    // 默认情况下，这些成员是 PRIVATE（私有的）
    double x;
    double y;

public: // 从这里开始，成员是 public（公共的）
    // 用于修改私有数据的“setter”方法
    void set(double new_x, double new_y) {
        x = new_x;
        y = new_y;
    }

    // 用于读取私有数据的“getter”方法
    double getX() const { return x; }
    double getY() const { return y; }

    // 对数据执行操作的方法
    double distanceFromOrigin() const {
        // 这里的 'const' 表示此方法不会修改对象的（x 或 y）状态
        return std::sqrt(x * x + y * y);
    }
};

int main() {
    // --- Struct 用法 ---
    PointStruct p_struct;
    p_struct.x = 3.0; // OK，成员是 public（公共的），可以直接访问
    p_struct.y = 4.0;
    std::cout << "Struct 点: (" << p_struct.x << ", " << p_struct.y << ")\n";

    // --- Class 用法 ---
    PointClass p_class;
    // p_class.x = 3.0; // 编译错误！'x' 是 private（私有的）。
    p_class.set(3.0, 4.0); // 必须使用公共接口（方法）

    std::cout << "Class 点: (" << p_class.getX() << ", " << p_class.getY() << ")\n";
    std::cout << "距离原点的距离: " << p_class.distanceFromOrigin() << "\n";

    return 0;
}
```

### 为什么这么做 (Why we do it this way) & 核心思想：封装

上面代码的核心差异，引出了面向对象三大支柱的第一个：**封装 (Encapsulation)**。

- **`struct` 的方式 (无封装)**: 就像一个透明的玻璃盒子。任何人都可以直接伸手进去拿取或修改里面的东西 (`p_struct.x = 3.0`)。这对于简单数据很方便，但如果数据之间有某种约束（比如，一个矩形的 `width` 必须是正数），这种直接访问就变得很危险，因为无法阻止用户设置一个无效值，如 `rect.width = -100;`。
- **`class` 的方式 (封装)**: 就像一个有特定操作面板的保险箱。你不能直接接触里面的钱（`private` 数据），但你可以通过保险箱提供的按钮（`public` 方法）来存钱或查询余额。**数据 (`x`, `y`) 和操作数据的方法 (`set`, `getX`, `distanceFromOrigin`) 被紧密地绑定在一起**。这带来了巨大的好处：
  1. **保护不变量 (Invariant Protection)**: 类可以保证其内部状态的有效性。例如，`set` 方法可以加入检查逻辑：`if (new_x > 0) x = new_x;`。
  2. **隐藏实现细节**: 用户只需要知道 `distanceFromOrigin()` 这个方法就能计算距离，而无需关心其内部是用 `sqrt(x*x + y*y)` 还是其他更复杂的算法实现的。如果未来我们想优化算法，只需修改类内部，所有使用这个类的代码都无需改动。
  3. **降低认知负担**: 用户只需关注类的公开接口，而不用理解其所有复杂的内部工作原理。

**黄金法则**:

- 当你需要一个纯粹的、没有复杂逻辑、成员可以自由访问的数据集合时，**使用 `struct`**。例如，一个函数的返回多个值的打包体。
- 当你创建一个需要维护内部状态、有自己的行为和规则的“活”的对象时，**使用 `class`**。这适用于绝大多数自定义类型。

### 关联与替代方案 (Associated Concepts & Alternatives)

- **访问修饰符 (`public`, `private`, `protected`)**:
  - **`public`**: 任何代码都可以访问。这是类的“公共接口”。
  - **`private`**: 只有该类的成员函数可以访问。这是类的“实现细节”。
  - **`protected`**: 与 `private` 类似，但允许其**子类 (derived classes)** 访问。我们将在“继承”中详细讨论它。
- **成员函数中的 `const`**:

  - 在成员函数声明末尾的 `const` (如 `double getX() const`) 是一个对程序员和编译器的**承诺**：这个函数**不会修改**任何成员变量。
  - **好处**:

    1. **代码更安全**: 编译器会阻止你在 `const` 函数内意外修改数据。
    2. **接口更清晰**: 它告诉用户“调用这个函数是安全的，不会改变对象状态”。
    3. **允许对 `const` 对象调用**: 如果一个对象被声明为 `const`，那么它只能调用 `const` 成员函数。

       ```cpp
       const PointClass const_point;
       // const_point.set(1,1); // 错误！set 不是 const 函数
       double x = const_point.getX(); // 正确，getX 是 const 函数
       ```

- **C++11 成员初始化**:
  - 现代 C++ 允许在声明成员变量时直接为其提供默认值。
  ```cpp
  class PointClass {
  private:
      double x = 0.0; // 默认值为 0.0
      double y = 0.0;
  public:
      // ...
  };
  ```
  这使得代码更简洁，并能确保对象在创建后总是有合理的初始状态。

## 2. 封装 (Encapsulation)：成员变量与成员函数，以及 `public` vs. `private`

### 是什么 (What it is)

**封装**是面向对象编程的三大基石之一（另两个是继承和多态）。它的核心思想是：

1. **捆绑 (Bundling)**: 将数据（**成员变量**）和操作这些数据的函数（**成员函数/方法**）捆绑在一个逻辑单元——即 `class` 中。
2. **隐藏 (Hiding)**: 将对象的内部实现细节（通常是数据成员）隐藏起来，只暴露一个定义良好的公共接口（`public` 成员函数）供外界使用。

**封装的目的不是为了保密，而是为了降低复杂性、增强代码的健壮性和可维护性。** 它在类和其使用者之间建立了一道“防火墙”。

### 怎么做 (How to do it)

我们通过一个更实际的例子来深化理解：一个银行账户 `Account` 类。

```cpp
class Account {
private:
    // --- Private Members (Implementation Details) ---
    // 这些是类的内部状态，外界不应直接访问。
    std::string owner_name_; // C++ 社区习惯用下划线后缀表示私有成员
    double balance_;

    // 一个私有辅助函数，只在类内部使用
    void logTransaction(const std::string& message) const {
        std::cout << "[LOG] " << owner_name_ << ": " << message << "\\n";
    }

public:
    // --- Public Members (The Interface) ---
    // 这是类的“操作面板”，供外界使用。

    // 公开的 "setter" 方法，但带有逻辑控制
    void deposit(double amount) {
        if (amount > 0) {
            balance_ += amount;
            logTransaction("Deposited " + std::to_string(amount));
        } else {
            std::cout << "[ERROR] Deposit amount must be positive.\\n";
        }
    }

    // 另一个 "setter"，同样带有业务规则
    bool withdraw(double amount) {
        if (amount <= 0) {
            std::cout << "[ERROR] Withdrawal amount must be positive.\\n";
            return false;
        }
        if (balance_ >= amount) {
            balance_ -= amount;
            logTransaction("Withdrew " + std::to_string(amount));
            return true;
        } else {
            logTransaction("Withdrawal failed. Insufficient funds.");
            return false;
        }
    }

    // 公开的 "getter" 方法
    double getBalance() const {
        return balance_;
    }

    // 初始设置，注意这里我们还没有学构造函数，所以用一个普通函数代替
    void setup(const std::string& name, double initial_balance) {
        owner_name_ = name;
        balance_ = initial_balance;
    }
};

int main() {
    Account my_account;
    my_account.setup("Kaiming He", 1000.0);

    // my_account.balance_ = 1000000.0; // COMPILE ERROR! balance_ is private.
    // 不能直接修改余额，必须通过公共接口。

    std::cout << "Initial Balance: " << my_account.getBalance() << "\\n";

    my_account.deposit(500.0);
    my_account.withdraw(2000.0); // This will fail
    my_account.withdraw(200.0);  // This will succeed

    std::cout << "Final Balance: " << my_account.getBalance() << "\\n";
}
```

**输出:**

```
Initial Balance: 1000
[LOG] Kaiming He: Deposited 500.000000
[LOG] Kaiming He: Withdrawal failed. Insufficient funds.
[LOG] Kaiming He: Withdrew 200.000000
Final Balance: 1300
```

### 为什么这么做 (Why we do it this way)

1. **维护不变量 (Maintaining Invariants)**: 一个“不变量”是对象必须始终保持为真的一个规则。对于 `Account`，一个核心不变量是 `balance_` 永远不能为负数。通过将 `balance_` 设为 `private`，并只提供 `deposit` 和 `withdraw` 两个受控的修改途径，我们**保证**了任何人都无法将余额直接设置为负值。封装使得维护这些规则成为可能。
2. **降低耦合 (Reducing Coupling)**: "耦合"是指代码模块之间的依赖程度。如果 `main` 函数可以直接访问 `balance_`，那么 `main` 就与 `Account` 类的**内部实现**紧密地耦合在了一起。如果未来我们决定将 `balance_` 的类型从 `double` 改为更高精度的自定义类型 `Decimal`，那么所有直接访问 `balance_` 的代码（可能散布在整个项目的成百上千个文件中）都必须修改。
   通过封装，`main` 只依赖于 `getBalance()` 这个**稳定接口**。只要接口不变，我们就可以随意改变 `Account` 的内部实现，而无需修改任何使用它的代码。这极大地提高了代码的可维护性。
3. **简化使用 (Simplifying Usage)**: 用户只需学习 `deposit`, `withdraw`, `getBalance` 这几个简单的公共接口，就能使用一个功能强大的 `Account` 对象，而无需关心其内部复杂的日志记录、错误处理等细节。

### 关联与替代方案 (Associated Concepts & Alternatives)

- **`protected` 访问修饰符**:
  - **是什么**: `protected` 成员可以被**当前类**以及其所有**子类**的成员函数访问，但不能被外部代码访问。
  - **对比 `private`**: `private` 成员只能被当前类访问，即使是子类也不行。
  - **应用场景**: 当你希望将某些实现细节对外部世界隐藏，但又希望子类能够访问和扩展这些细节时，使用 `protected`。这是为**继承 (Inheritance)** 这个特性量身定做的。
  ```cpp
  class Base {
  protected:
      int protected_val;
  };
  class Derived : public Base {
      void func() {
          protected_val = 10; // OK, Derived is a subclass of Base
      }
  };
  int main() {
      Derived d;
      // d.protected_val = 20; // ERROR! main is not a member or subclass.
  }
  ```
- **`friend` 关键字**:

  - **是什么**: `friend` 关键字可以打破封装的壁垒。一个类可以声明另一个函数或另一个类为自己的“友元”。友元可以访问该类的所有 `private` 和 `protected` 成员，就像它们是该类的成员一样。
  - **应用场景**:
    1. **运算符重载**: 当重载某些运算符（如 `<<` 用于 `std::cout`）作为非成员函数时，它们需要访问类的私有数据。
    2. **测试**: 测试代码有时需要访问类的内部状态以进行验证。
    3. 当两个类紧密协作，需要互相访问对方的内部实现时。
  - **代码示例**:

  ```cpp
  class MyClass {
  private:
      int secret = 42;
  public:
      friend void showSecret(const MyClass& obj); // Declare a friend function
  };

  void showSecret(const MyClass& obj) {
      // Because it's a friend, this function can access private members.
      std::cout << "The secret is: " << obj.secret << "\\n";
  }
  ```

  - **警告**: `friend` 应该被谨慎使用。它在特定情况下非常有用，但滥用 `friend` 会破坏封装的初衷，增加代码的耦合度。

我们已经完全理解了封装的“是什么”、“怎么做”和“为什么”。然而，我们的 `Account` 类还有一个非常笨拙的地方：必须在创建对象后，手动调用 `setup()` 函数来初始化它。这不仅麻烦，而且容易忘记，导致对象处于无效状态。

我们如何能保证一个对象在被创建的那一刻，就**自动**、**正确**地被初始化呢？

## 3. 构造与析构 (Construction & Destruction)

### 是什么 (What it is)

**构造函数 (Constructor)** 和 **析构函数 (Destructor)** 是两种特殊的类成员函数。它们控制着对象的“诞生”与“消亡”。

- **构造函数 (Constructor)**:
  - 一个与类同名的特殊函数，**没有返回类型**（连 `void` 都没有）。
  - 当一个对象被**创建**时，构造函数被**自动调用**。
  - 它的核心职责是：**初始化成员变量，确保对象在诞生之初就处于一个有效的、合法的状态**。
- **析构函数 (Destructor)**:
  - 一个在类名前加上波浪号 `~` 的特殊函数，也没有返回类型。
  - 当一个对象的**生命周期结束**时（例如，离开作用域、被 `delete`），析构函数被**自动调用**。
  - 它的核心职责是：**释放对象在其生命周期内获取的资源**（例如，堆内存、文件句柄、网络连接等）。

**构造与析构，共同构成了 RAII (Resource Acquisition Is Initialization) 的完整闭环。**

- **Acquisition (获取资源)**: 在构造函数中完成。
- **Release (释放资源)**: 在析构函数中完成。

### 怎么做 (How to do it)

我们将用两个例子来展示。第一个是重构我们的 `Account` 类，第二个是实现 Phase 2 练习中那个简化版的 `MyVector`，让你看到 RAII 的全部威力。

**Example 1: 重构 `Account` 类**

```cpp
#include <iostream>
#include <string>

class Account {
private:
    std::string owner_name_; // 账户名
    double balance_; // 余额

public:
    // --- 1. 构造函数 ---
    // 在对象创建时接收参数来初始化对象。
    Account(const std::string& name, double initial_balance) {
        std::cout << "调用了 " << name << " 的构造函数。\n";
        owner_name_ = name;
        if (initial_balance >= 0) {
            balance_ = initial_balance;
        } else {
            balance_ = 0;
            std::cout << "[警告] 初始余额不能为负数。已设置为 0。\n";

		// --- 现代 C++：成员初始化列表 ---
    // 这是初始化成员的首选方式。
    // 它的优点包括：
    // 1. 效率：直接初始化成员，避免了先默认初始化再赋值的开销。
    // 2. 强制性：对于const成员和引用成员，必须使用初始化列表进行初始化。
    // 3. 清晰性：一眼就能看出成员是如何初始化的，提高了代码的可读性。

    // Account(const std::string& name, double initial_balance)
    //     : owner_name_(name), // 初始化 owner_name_ 成员变量，将其设置为传入的 name 参数。
    //       balance_(initial_balance >= 0 ? initial_balance : 0) // 初始化 balance_ 成员变量：
    //                                                          // 使用三元运算符检查 initial_balance。
    //                                                          // 如果 initial_balance 大于或等于 0，则直接使用该值。
    //                                                          // 否则，将其设置为 0。
    // {
    //     // 构造函数体内的代码会在所有成员初始化完成后执行。

    //     std::cout << "调用了 " << name << " 的构造函数。\n"; // 输出一条消息，表示构造函数被调用。

    //     // 检查初始余额是否为负数，如果为负，打印警告信息。
    //     // 注意：虽然这里有警告，但由于初始化列表已经处理了负数情况，
    //     // 这里的 balance_ 成员变量在执行到这里时一定是非负的。
    //     if (initial_balance < 0) {
    //         std::cout << "[警告] 初始余额不能为负数。已设置为 0。\n";
    //     }
    // }

    // --- 2. 析构函数 ---
    // 在对象被销毁时进行清理。
    ~Account() {
        std::cout << "调用了 " << owner_name_
                  << "（最终余额为 " << balance_ << "）的析构函数。\n";
        // 对于这个简单的类，没有需要释放的资源，
        // 但析构函数仍然会被调用。
    }

    // ... 其他方法，如 deposit, withdraw, getBalance ...
    void deposit(double amount) { if(amount > 0) balance_ += amount; }
    double getBalance() const { return balance_; }
};

int main() {
    std::cout << "--- 进入 main 作用域 ---\n";
    { // 创建一个新的内部作用域
        std::cout << "  --- 进入内部作用域 ---\n";
        // `my_account` 对象在此处被创建。构造函数会自动调用。
        Account my_account("Saining Xie", 2000.0);
        std::cout << "  账户已创建。当前余额: " << my_account.getBalance() << "\n";
        my_account.deposit(500);

        // `my_account` 即将超出作用域。
        std::cout << "  --- 退出内部作用域 ---\n";
    } // `my_account` 在此处被销毁。析构函数会自动调用。

    std::cout << "--- 返回 main 作用域 ---\n";
    return 0;
}
```

**输出:**

```
--- Entering main scope ---
  --- Entering inner scope ---
CONSTRUCTOR for Saining Xie called.
  Account created. Current balance: 2000
  --- Exiting inner scope ---
DESTRUCTOR for Saining Xie with final balance 2500 called.
--- Back in main scope ---
```

**关键观察**: 你再也不需要调用 `setup()` 了。对象的创建和初始化合二为一。当对象离开作用域 `{}` 时，析构函数自动被调用，保证了清理工作的执行。

### 为什么这么做 (Why we do it this way)

1. **保证对象状态的有效性**: 构造函数强制要求对象在创建时就必须提供必要的信息，从根本上杜绝了“未初始化对象”的存在。一个 `Account` 对象一旦被创建，它就一定有一个名字和合法的余额。
2. **自动化资源管理**: 这是析构函数最伟大的贡献。它将资源释放的责任从“程序员记得调用”转变为“语言机制保证调用”。这使得 C++ 代码在面对复杂的逻辑分支和异常时依然能保持健壮，极大地减少了资源泄漏。

**性能与代码质量对比：成员初始化列表 (Member Initializer List)**

- **旧方法 (在构造函数体内赋值)**:
  ```cpp
  Account(const std::string& name, ...) {
      owner_name_ = name; // 2 steps: 1. owner_name_ is default-constructed. 2. It is copy-assigned from name.
  }
  ```
- **现代方法 (使用初始化列表)**:
  ```cpp
  Account(const std::string& name, ...)
      : owner_name_(name) // 1 step: owner_name_ is directly copy-constructed from name.
  { ... }
  ```

**性能对比**: 对于像 `std::string` 这样的复杂类型，使用初始化列表可以避免一次不必要的默认构造和一次赋值操作，直接进行**一次构造**。这更高效。对于 `const` 成员或引用成员，它们**必须**在初始化列表中进行初始化。

**黄金法则**: **始终优先使用成员初始化列表来初始化成员变量。**

### 关联与替代方案 (Associated Concepts & Alternatives)

- **默认构造函数 (Default Constructor)**:
  - 一个**不接收任何参数**的构造函数。如果你没有定义任何构造函数，编译器会为你生成一个公开的、空的默认构造函数。但只要你定义了**任何**一个构造函数，编译器就不再为你生成默认构造函数了。
  - **何时需要**: 当你需要创建对象数组，或者在类中包含一个没有默认构造函数的成员对象时。
  ```cpp
  Account accounts[10]; // 错误！编译器不知道如何创建 Account，因为它需要参数。
  // 要想让上行代码通过，Account 类需要有一个默认构造函数：
  // Account() : owner_name_("Default"), balance_(0) {}
  ```
- **拷贝构造函数 (Copy Constructor)**:
  - 一个接收**同类型的常量引用**作为参数的构造函数。当一个新对象由一个已存在的同类型对象创建时，它被调用。
  - **签名**: `MyClass(const MyClass& other);`
  - **调用时机**:
  ```cpp
  Account a1("A", 100);
  Account a2 = a1;     // 调用拷贝构造函数
  Account a3(a1);      // 也调用拷贝构造函数
  function(a1);        // 按值传递，调用拷贝构造函数
  ```
  - 如果你不提供，编译器会生成一个，它会逐个成员地进行拷贝。对于持有**堆内存指针**的类，这种**浅拷贝 (Shallow Copy)** 是灾难性的，我们稍后会看到。
- **拷贝赋值运算符 (Copy Assignment Operator)**:
  - 一个重载的 `=` 运算符，用于将一个已存在的对象赋值给另一个已存在的对象。
  - **签名**: `MyClass& operator=(const MyClass& other);`
  - **调用时机**: `a3 = a2;`
- **三/五/零法则 (Rule of Three/Five/Zero)**:
  - **三法则 (C++98)**: 如果你手动定义了**析构函数**、**拷贝构造函数**或**拷贝赋值运算符**中的任何一个，那么你几乎肯定需要把这三个都定义出来。
  - **五法则 (C++11)**: 在三法则的基础上，加上**移动构造函数 (Move Constructor)** 和 **移动赋值运算符 (Move Assignment Operator)**。我们将在 Phase 4 学习它们。
  - **零法则 (现代 C++)**: **首选方案**。通过使用 `std::vector`, `std::string`, `std::unique_ptr` 等管理资源的类作为成员变量，你的类通常**不需要**手动编写任何上述五个特殊函数。这些标准库组件已经正确实现了拷贝、移动和析构逻辑，你的类可以自动、正确地享受这些行为。**这就是组合的力量。**

---

**Example 2: 实现简化版 `MyVector` (RAII 的终极体现)**

现在，我们可以用今天学到的知识，完美地实现那个 Phase 2 的练习了。

```cpp
#include <iostream>
#include <cstddef> // For size_t

class MyVector {
private:
    int* data_;
    size_t size_;
    size_t capacity_;

public:
    // 1. CONSTRUCTOR: Acquires resources.
    MyVector() : data_(nullptr), size_(0), capacity_(0) {
        std::cout << "MyVector: Default Constructor\\n";
    }

    // 2. DESTRUCTOR: Releases resources.
    ~MyVector() {
        std::cout << "MyVector: Destructor (freeing memory)\\n";
        delete[] data_; // RAII in action!
    }

		void push_back(int value) {
        // 检查当前存储的元素数量 (size_) 是否已经达到了容器的容量 (capacity_)。
        // 如果 size_ == capacity_，说明容器已满，需要扩容。
        if (size_ == capacity_) {
            // 计算新的容量 (new_capacity)。
            // 如果当前容量为 0 (即容器为空)，则将新容量设置为 1。
            // 否则，将当前容量翻倍。这是一个常见的动态数组扩容策略，
            // 可以 amortized O(1) 的插入操作。
            size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;

            // 在堆上分配一块新的内存空间，用于存储扩容后的元素。
            int* new_data = new int[new_capacity];

            // 将旧内存空间中的所有元素复制到新内存空间中。
            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = data_[i];
            }

            // 释放旧内存空间，防止内存泄漏。
            delete[] data_;

            // 将指向新内存空间的指针赋给 data_，并更新容量。
            data_ = new_data;
            capacity_ = new_capacity;
        }

        // 将要插入的值 (value) 存储到当前 size_ 指向的位置。
        // 然后，将 size_ 加一，表示容器中元素的数量增加了。
        // size_++ 是一个后置递增操作，先使用 size_ 的值作为索引，
        // 然后再将 size_ 加一。
        data_[size_++] = value;
    }

    size_t size() const { return size_; }
};

int main() {
    MyVector vec; // Default constructor called
    vec.push_back(10);
    vec.push_back(20);
    std::cout << "Vector size: " << vec.size() << "\\n";

    return 0; // `vec` goes out of scope, destructor is called automatically.
}
```

**输出:**

```
MyVector: Default Constructor
Vector size: 2
MyVector: Destructor (freeing memory)
```

## 4. 继承 (Inheritance)

### 是什么 (What it is)

**继承**是面向对象编程的三大基石之一。它允许我们创建一个新类（称为**子类 (Subclass)** 或 **派生类 (Derived Class)**），这个新类可以从一个已存在的类（称为**父类 (Superclass)** 或 **基类 (Base Class)**）中**继承**其成员（包括成员变量和成员函数）。

继承的核心是建立一种 **“是一个” (is-a)** 的关系。例如：

- 一个 “贵宾犬 (Poodle)” **是一个** “狗 (Dog)”。
- 一个 “狗 (Dog)” **是一个** “动物 (Animal)”。
- 一个 “正方形 (Square)” **是一个** “矩形 (Rectangle)”。

子类自动拥有父类的所有特性，并可以：

1. **添加新特性**：定义自己独有的成员变量和函数。
2. **覆盖旧特性**：重新定义父类中的某些函数，以实现自己独特的行为（这通常与多态一起使用）。

**继承的主要目的：代码复用和建立类型层次结构。**

### 怎么做 (How to do it)

我们将通过一个游戏角色的例子来展示继承。我们有一个通用的 `GameObject`，然后派生出更具体的 `Player` 和 `Enemy`。

**`inheritance_demo.cpp`**

```cpp
#include <iostream>
#include <string>

// --- 基类 (父类) ---
class GameObject {
protected: // 使用 protected 使得派生类可以访问这些成员
    double x_ = 0.0, y_ = 0.0; // 位置坐标
    std::string id_;           // 唯一标识符

public:
    // 基类的构造函数
    // 初始化 id, x, 和 y 成员。
    GameObject(const std::string& id, double x, double y)
        : id_(id), x_(x), y_(y) {
        std::cout << "GameObject '" << id_ << "' 已构造。\n";
    }

    // 基类的析构函数
    // 打印一条消息，表示对象正在被销毁。
    ~GameObject() {
        std::cout << "GameObject '" << id_ << "' 已销毁。\n";
    }

    // 所有游戏对象都共有的函数
    // 将游戏对象移动到新的位置。
    void moveTo(double new_x, double new_y) {
        x_ = new_x;
        y_ = new_y;
        std::cout << id_ << " 已移动到 (" << x_ << ", " << y_ << ")。\n";
    }

    // 返回游戏对象的 ID。
    std::string getId() const { return id_; }
};

// --- 派生类 1 (子类) ---
// Player "is-a" GameObject，意味着 Player 拥有 GameObject 的所有属性，
// 并且可以拥有自己独特的属性和行为。
class Player : public GameObject { // 公有继承的语法
private:
    int level_ = 1; // 玩家当前等级

public:
    // 派生类构造函数必须调用基类构造函数。
    // 这确保了 Player 的 GameObject 部分能够被正确初始化。
    Player(const std::string& name, double x, double y)
        // 这行代码首先调用 GameObject 的构造函数
        : GameObject(name, x, y) {
        std::cout << "  -> Player '" << name << "' 的特定部分已构造。\n";
    }

    // Player 类的析构函数
    // 打印一条消息，表示 Player 的特定部分正在被销毁。
    ~Player() {
        std::cout << "  -> Player '" << id_ << "' 的特定部分已销毁。\n";
    }

    // 一个新的函数，Player 特有
    // 提升玩家的等级。
    void levelUp() {
        level_++;
        std::cout << id_ << " 已升级到等级 " << level_ << "！\n";
    }
};

// --- 派生类 2 (另一个子类) ---
// Enemy "is-a" GameObject。与 Player 类似，它也继承自 GameObject。
class Enemy : public GameObject {
private:
    int damage_ = 10; // 敌人造成的伤害值

public:
    // Enemy 类的构造函数
    // 调用基类构造函数并初始化自己的成员。
    Enemy(const std::string& type, double x, double y, int damage)
        : GameObject(type, x, y), damage_(damage) {
        std::cout << "  -> Enemy '" << type << "' 的特定部分已构造。\n";
    }

    // Enemy 类的析构函数
    // 打印一条消息，表示 Enemy 的特定部分正在被销毁。
    ~Enemy() {
        std::cout << "  -> Enemy '" << id_ << "' 的特定部分已销毁。\n";
    }

    // 一个新的函数，Enemy 特有
    // 模拟敌人的攻击。
    void attack() {
        std::cout << id_ << " 造成 " << damage_ << " 点伤害！\n";
    }
};

int main() {
    std::cout << "--- 创建一个 Player ---\n";
    // 创建 Player 类的一个实例。
    // 这会首先调用 GameObject 构造函数，然后调用 Player 构造函数。
    Player hero("Karpathy", 10, 20);
    hero.moveTo(15, 25); // 调用从 GameObject 继承的方法
    hero.levelUp();      // 调用 Player 特有的方法
    std::cout << "\n";

    std::cout << "--- 创建一个 Enemy ---\n";
    // 创建 Enemy 类的一个实例。
    // 这会首先调用 GameObject 构造函数，然后调用 Enemy 构造函数。
    Enemy villain("Dragon", 100, 100, 50);
    villain.moveTo(90, 90); // 调用从 GameObject 继承的方法
    villain.attack();       // 调用 Enemy 特有的方法
    std::cout << "\n";

    std::cout << "--- 退出 main ---\n";
    // 当 main() 函数结束时，对象会超出作用域，它们的析构函数会被调用。
    // 对象销毁的顺序与构造顺序相反。
    // 因此，'villain' 对象的析构函数会先被调用，然后是 'hero' 对象的析构函数。
}
```

**输出与分析:**

```
--- Creating a Player ---
GameObject 'Karpathy' constructed.
  -> Player 'Karpathy' specific part constructed.
Karpathy moved to (15, 25).
Karpathy leveled up to level 2!

--- Creating an Enemy ---
GameObject 'Dragon' constructed.
  -> Enemy 'Dragon' specific part constructed.
Dragon moved to (90, 90).
Dragon attacks for 50 damage!

--- Exiting main ---
GameObject 'Dragon' destructed.
  -> Enemy 'Dragon' specific part destructed.
GameObject 'Karpathy' destructed.
  -> Player 'Karpathy' specific part destructed.
```

**构造与析构顺序**:

- **构造**: 先构造基类部分，再构造派生类部分（从上到下）。
- **析构**: 先析构派生类部分，再析构基类部分（从下到上）。
  这个顺序是绝对必要的，以保证依赖关系的正确性。子类可能会依赖于父类的成员，所以父类必须先准备好。

### 为什么这么做 (Why we do it this way)

1. **代码复用**: `Player` 和 `Enemy` 都需要位置信息 (`x`, `y`) 和移动行为 (`moveTo`)。通过继承 `GameObject`，我们只需编写一次这些通用功能，所有派生类都能自动获得它们。这减少了代码冗余，使得修改通用行为（如优化 `moveTo` 函数）变得非常容易。
2. **建立类型层次结构**: 继承创建了一个清晰的、符合逻辑的类型关系。这使得我们可以用一种更通用的方式来思考和组织代码。例如，我们可以创建一个包含各种游戏对象的列表 `std::vector<GameObject*>`，里面可以同时存放 `Player` 和 `Enemy` 的指针。这是实现多态的基础。

### 关联与替代方案 (Associated Concepts & Alternatives)

- **继承类型 (`public`, `protected`, `private`)**:
  - **`public` 继承**: `class Derived : public Base`。这是最常用的继承方式，完美地体现了 "is-a" 关系。基类的 `public` 成员在派生类中仍然是 `public`，`protected` 成员仍然是 `protected`。
  - **`protected` 继承**: 基类的 `public` 和 `protected` 成员在派生类中都变成 `protected`。
  - **`private` 继承**: 基类的 `public` 和 `protected` 成员在派生类中都变成 `private`。
  - **对比与选择**: `protected` 和 `private` 继承通常用于实现一种叫做 **"is-implemented-in-terms-of"** (根据...来实现) 的关系，而不是 "is-a"。然而，在现代 C++ 中，这种场景通常**更倾向于使用组合 (Composition) 而不是继承**。**黄金法则：99% 的情况下，你都应该使用 `public` 继承。**
- **组合 (Composition) vs. 继承 (Inheritance)**: 这是面向对象设计中一个永恒的话题。
  - **组合**: 一个类**包含 (has-a)** 另一个类的对象作为其成员。例如，一辆 “车 (Car)” **有一个** “引擎 (Engine)”。
  ```cpp
  class Engine { /* ... */ };
  class Car {
  private:
      Engine engine_; // Composition: Car has-a Engine
  };
  ```
  - **对比**:
    - **关系**: 继承是 "is-a" (是什么)，组合是 "has-a" (有什么)。
    - **耦合度**: 组合是**松耦合**。`Car` 只与 `Engine` 的公共接口交互。继承是**紧耦合**。子类与父类的 `protected` 甚至 `public` 成员紧密相连。
    - **灵活性**: 组合更灵活。你可以在运行时改变 `Car` 的 `engine_` 对象。继承关系在编译时就固定了。
  - **黄金法则**: **优先使用组合，而不是继承 (Prefer Composition over Inheritance)。** 只有当存在明确的、天然的 "is-a" 关系，并且你需要利用多态时，才使用继承。
- **多重继承 (Multiple Inheritance)**: C++ 允许一个类同时从多个基类继承。
  ```cpp
  class File { public: void open(); };
  class Device { public: void connect(); };
  class NetworkedDeviceFile : public File, public Device {};
  ```
  - **优点**: 提供了强大的建模能力。
  - **缺点**: 可能导致**菱形继承问题 (Diamond Problem)**，即一个类通过两条不同的路径继承自同一个远端基类，造成成员的歧义。C++ 通过**虚继承 (virtual inheritance)** 来解决这个问题，但这会增加复杂性和开销。
  - **替代方案**: 许多现代语言（如 Java, C#）禁止多重继承，而是采用**接口 (Interface)** 的概念来替代。在 C++ 中，可以通过继承多个只包含纯虚函数的抽象基类来模拟接口。

我们已经学会了如何通过继承来构建类型家族，实现了代码复用。但目前为止，我们的继承还只是静态的。`Player` 是 `Player`，`Enemy` 是 `Enemy`。

想象一下，我们想写一个函数 `void anyObjectMakesSound(GameObject* obj)`，我们传入一个 `Player` 指针，它就发出玩家的声音；传入一个 `Enemy` 指针，它就发出敌人的声音。我们希望同一个函数调用，能根据对象的**实际类型**表现出不同的行为。

### 引用和使用权的管理

### 三种核心场景：如何将 `unique_ptr` 传递给函数

假设我们在 `main` 函数中有一个 `unique_ptr`：

C++

```cpp
auto myObject = std::make_unique<GameObject>("Hero");
```

### 场景 1：函数需要“拿走”这个对象（转移所有权）

- **意图：** 调用者 `main` 不再需要这个对象了，希望把它的**所有权**和**管理责任**彻底交给这个函数。
- **做法：** 函数参数直接写 `std::unique_ptr<GameObject>`，调用时使用 `std::move`。

```cpp
// 函数签名：通过值传递，准备接收所有权
void takeOwnership(std::unique_ptr<GameObject> ptr) {
    std::cout << "Function now owns " << ptr->name << std::endl;
    // 当函数结束时，ptr 会被销毁，从而释放 GameObject
}

// 调用：
takeOwnership(std::move(myObject));
// 调用后，main 函数中的 myObject 变为 nullptr，所有权已经转移
```

- **总结：** 当你想表达“这个东西给你了，以后归你管”时，用这个方法。

### 场景 2：函数只需要“看一看”或“用一用”这个对象（非侵入式访问）

- **意图：** 函数需要访问 `unique_ptr` 指向的对象，但**不改变所有权**。`main` 函数依然是这个对象的拥有者。这是**最常见**的场景。
- **做法：** 函数参数使用**常量引用 (const reference)**，即 `const std::unique_ptr<GameObject>&`。

```cpp
// 函数签名：通过 const 引用传递，只读访问
void inspectObject(const std::unique_ptr<GameObject>& ptr) {
    // ptr->name = "Villain"; // 错误！不能通过 const 引用修改对象内容
    // ptr.reset();             // 错误！不能修改 unique_ptr 本身
    std::cout << "Function is inspecting " << ptr->name << std::endl;
}

// 调用：
inspectObject(myObject);
// 调用后，myObject 依然有效，所有权没有变化
```

- **总结：** 当你想表达“借给你用一下，别弄坏，用完还给我”时，用这个方法。**这是 `unique_ptr` 和引用最经典的结合方式。**

### 场景 3：函数需要修改 `unique_ptr` 本身（例如，让它指向别的对象）

- **意图：** 函数需要直接修改调用者 `main` 的那个 `unique_ptr` 变量，比如让它 `reset` 或者指向一个全新的对象。
- **做法：** 函数参数使用**非`const`引用 (non-const reference)**，即 `std::unique_ptr<GameObject>&`。

C++

```cpp
// 函数签名：通过非 const 引用传递，可以修改指针
void modifyPointer(std::unique_ptr<GameObject>& ptr) {
    std::cout << "Function is replacing " << ptr->name << std::endl;
    // 释放旧对象，并让 ptr 指向一个新对象
    ptr = std::make_unique<GameObject>("Sidekick");
}

// 调用：
modifyPointer(myObject);
// 调用后，main 函数中的 myObject 现在指向了 "Sidekick"
```

- **总结：** 当你想表达“我需要改变你手上的那个智能指针”时，用这个方法。这比场景 2 要少见。

## 5. 多态 (Polymorphism)

### 是什么 (What it is)

**多态**，源于希腊语，意为“多种形态 (many forms)”。在 C++ 中，多态特指**运行时多态 (Runtime Polymorphism)**，它允许我们通过**基类的指针或引用**来调用一个函数，而实际执行的函数版本则由该指针或引用所指向的**对象的实际类型**来决定。

换句话说，同一个函数调用，在运行时可以表现出多种不同的行为。

**实现多态的两个关键要素**:

1. **通过基类的指针或引用进行操作**: 你的代码操作的是一个通用的接口（基类），而不是一个具体的实现（派生类）。
2. **在基类中使用 `virtual` 关键字**: 在你希望派生类能够提供自己版本的函数前，加上 `virtual` 关键字。这告诉编译器：“这个函数的调用应该在运行时动态解析，而不是在编译时静态确定。”

**没有多态的世界 vs. 有多态的世界**

- **没有多态**:
  ```cpp
  void handleObject(GameObject* obj) {
      // 我们必须检查对象的具体类型，然后调用正确的函数
      if (typeid(*obj) == typeid(Player)) {
          static_cast<Player*>(obj)->playerSpecificFunction();
      } else if (typeid(*obj) == typeid(Enemy)) {
          static_cast<Enemy*>(obj)->enemySpecificFunction();
      } // 每增加一种新类型，都要修改这里！代码僵化，难以维护。
  }
  ```
- **有多态**:
  ```cpp
  void handleObject(GameObject* obj) {
      // 我们只管调用通用接口，C++ 运行时系统会帮我们找到正确的版本
      obj->update(); // 如果 obj 指向 Player，就调用 Player::update()
                     // 如果 obj 指向 Enemy，就调用 Enemy::update()
  } // 即使未来增加了 100 种新对象，这个函数也无需修改！
  ```

多态的核心价值在于**解耦**和**可扩展性**。它将“做什么”（接口）和“怎么做”（实现）分离开来。

### 怎么做 (How to do it)

我们将构建一个更丰富的游戏场景，包含多种 `GameObject`，它们都能对 `update()` 这个通用行为做出自己独特的响应。这个例子将融合我们学过的所有知识。

```cpp
#include <iostream> // 用于输入输出流操作
#include <string>   // 用于字符串操作
#include <vector>   // 用于动态数组（向量）
#include <memory>   // 用于智能指针，如 std::unique_ptr

// --- 基类：定义了多态的接口 ---
class GameObject {
protected:
    std::string name_; // 游戏对象的名称

public:
    // 构造函数：接收对象名称
    GameObject(const std::string& name) : name_(name) {}

    // 1. 虚析构函数：对于多态基类是至关重要的！
    // 当我们通过基类指针删除派生类对象时，这能确保调用正确的派生类析构函数。
    virtual ~GameObject() {
        std::cout << "GameObject '" << name_ << "' 的基类析构函数被调用。\n";
    }

    // 2. 虚函数，构成了我们多态行为的核心。
    // 派生类期望“重写”（Override）此函数。
    virtual void update() {
        std::cout << name_ << " (一个通用的 GameObject) 只是存在着。\n";
    }

    // 获取对象名称
    std::string getName() const { return name_; }
};

// --- 一个纯抽象类（接口）---
// 这个类不能被实例化，它只定义了一个契约（Contract）。
class Drawable {
public:
    // 析构函数：在多态基类中，总要有虚析构函数。
    // 使用 '= default' 来让编译器生成默认的析构函数实现。
    virtual ~Drawable() = default;

    // 4. 纯虚函数（由 `= 0` 标识）
    // 这使得 Drawable 成为一个"抽象类"。
    // 任何继承自 Drawable 的类都**必须**提供 draw() 函数的实现。
    virtual void draw() const = 0;
};

// --- 派生类 1：玩家 ---
class Player : public GameObject, public Drawable { // Player 继承自 GameObject 和 Drawable
private:
    int health_ = 100; // 玩家的生命值

public:
    // 构造函数：调用基类构造函数，并初始化玩家特有成员
    Player(const std::string& name) : GameObject(name) {}

    // 派生类析构函数：使用 'override' 关键字明确表示重写基类虚函数
    // 'override' 是 C++11 的关键字，强烈推荐使用。
    // 如果基类中不存在同名虚函数，编译器会报错，这可以防止因为拼写错误等原因导致未能成功重写。
    ~Player() override {
        std::cout << "  -> Player '" << name_ << "' 的派生类析构函数被调用。\n";
    }

    // 3. 重写（Override）基类的虚函数
    void update() override {
        std::cout << name_ << " (Player) 正在寻找任务。生命值: " << health_ << "\n";
    }

    // 实现 Drawable 接口的纯虚函数
    void draw() const override {
        std::cout << "正在绘制玩家 '" << name_ << "'，位置在某些坐标。\n";
    }
};

// --- 派生类 2：敌人 ---
class Enemy : public GameObject { // Enemy 继承自 GameObject
private:
    int damage_ = 20; // 敌人的伤害值

public:
    // 构造函数：调用基类构造函数，并初始化敌人特有成员
    Enemy(const std::string& name, int damage) : GameObject(name), damage_(damage) {}

    // 派生类析构函数，同样使用 override 关键字
    ~Enemy() override {
        std::cout << "  -> Enemy '" << name_ << "' 的派生类析构函数被调用。\n";
    }

    // 重写（Override）基类的虚函数
    void update() override {
        std::cout << name_ << " (Enemy) 正在巡逻。伤害值: " << damage_ << "\n";
    }
};

// --- 派生类 3：场景对象（不执行任何操作） ---
class Scenery : public GameObject { // Scenery 继承自 GameObject
public:
    // 构造函数
    Scenery(const std::string& name) : GameObject(name) {}

    // 派生类析构函数
    ~Scenery() override {
        std::cout << "  -> Scenery '" << name_ << "' 的派生类析构函数被调用。\n";
    }

    // 重写是可选的。如果我们不重写，基类的版本就会被调用。
    // 这里我们提供一个空的重写版本。
    void update() override {
        // 一棵树在每一帧不需要做任何事情。
        // std::cout << name_ << " (Scenery) 只是静静地站着。\n"; // 如果需要输出，可以取消注释
    }
};

int main() {
    // 我们使用智能指针的 `std::vector` 来自动管理内存（RAII）。
    // 这是现代 C++ 管理多态对象集合的推荐方式。
    std::vector<std::unique_ptr<GameObject>> game_objects;

    // 填充我们的游戏世界
    // std::make_unique 是创建 std::unique_ptr 的现代 C++14 方式
    game_objects.push_back(std::make_unique<Player>("Lilian"));
    game_objects.push_back(std::make_unique<Enemy>("Goblin", 15));
    game_objects.push_back(std::make_unique<Scenery>("Oak Tree"));
    game_objects.push_back(std::make_unique<Enemy>("Ogre", 40));

    std::cout << "\n--- 游戏循环更新 ---\n";
    // 多态性的魔力：
    // 我们迭代的是基类指针的集合...
    for (const auto& obj_ptr : game_objects) {
        // ...但调用的是实际对象类型的正确 `update()` 方法！
        obj_ptr->update();
    }

    // 我们也可以测试 Drawable 接口
    Player p("Jason"); // 创建一个 Player 对象
    // 将 Player 对象的地址赋给 Drawable* 类型的指针
    // 这是合法的，因为 Player 继承自 Drawable
    const Drawable* drawable_obj = &p;
    drawable_obj->draw(); // 调用 Player 中重写的 draw() 方法

    std::cout << "\n--- 游戏结束 ---\n";
    // 当 `game_objects` 向量离开作用域时，其中包含的 `unique_ptr` 会自动
    // 删除它们所管理的（动态分配的）对象。由于 `GameObject` 有虚析构函数，
    // 这会正确地调用每个派生对象的析构函数。
    return 0;
}
```

### 为什么这么做 (Why we do it this way) & 底层机制 (V-Table)

**为什么需要 `virtual`？**
当编译器看到一个非虚函数调用时（如 `obj->nonVirtualFunc()`），它会进行**静态绑定 (Static Binding)**。它只看指针的类型（`GameObject*`），然后直接生成调用 `GameObject::nonVirtualFunc()` 的机器码。

当编译器看到一个**虚函数**调用时（如 `obj->update()`），它会进行**动态绑定 (Dynamic Binding)**。它知道这个调用需要在运行时确定，于是它会生成一些特殊的代码。

**虚函数表 (Virtual Function Table, or V-Table)**
这就是 C++ 实现动态绑定的底层魔法。

1. **V-Table 创建**: 当一个类包含**任何**虚函数时，编译器会为这个**类**创建一个静态的数组，称为虚函数表（V-Table）。这个表里存放的是该类所有虚函数的地址。
2. **vptr 嵌入**: 编译器还会在该类的每个**对象**实例中，偷偷地嵌入一个指针，称为虚函数表指针（vptr）。这个 vptr 指向该类对应的 V-Table。
3. **动态调用过程**: 当你通过基类指针调用一个虚函数时 (`obj_ptr->update()`)，实际发生的是：
   a. 通过 `obj_ptr` 找到对象的 vptr。
   b. 通过 vptr 找到该对象所属类的 V-Table。
   c. 在 V-Table 中查找 `update()` 函数对应的地址（这是一个固定的偏移量）。
   d. 调用该地址上的函数。

**性能与成本**:

- **内存成本**: 每个对象增加一个 vptr 的大小（一个指针，4 或 8 字节）。每个含有虚函数的类增加一个 V-Table 的大小。
- **时间成本**: 每次虚函数调用比普通函数调用多了一两次内存解引用操作。这在现代 CPU 上开销极小，几乎可以忽略不计，除非是在性能要求达到极致的内层循环中。
- **结论**: 多态带来的巨大灵活性和可维护性，远远超过其微不足道的性能开销。这是 C++ "零成本抽象" 思想的一个小小例外——你为你需要用的东西（多态）付出了一点点代价，但这是值得的。

### 关联与替代方案 (Associated Concepts & Alternatives)

- **`override` 和 `final` (C++11)**:
  - **`override`**: 明确告诉编译器和读者，这个函数意在覆盖基类的虚函数。如果基类中没有对应的虚函数，或者函数签名不匹配（例如参数或 `const` 属性不同），编译器会报错。**这是一个必须养成的现代 C++ 习惯，能避免大量难以发现的 bug。**
  - **`final`**: 用于函数时，表示“这个虚函数不许任何子类再进行覆盖了”。用于类时，表示“这个类不许被任何其他类继承”。
- **虚析构函数 (Virtual Destructor)**:
  - **黄金法则**: **任何时候，只要你的基类准备用于多态（即，你可能会通过基类指针 `delete` 一个派生类对象），你就必须将其析构函数声明为 `virtual`。**
  - **为什么？** 如果不这么做，当 `delete base_ptr;` 时，只会调用基类的析构函数，派生类的析构函数将永远不会被调用，导致派 ש 生类申请的资源（如 `Player` 中可能的武器对象）全部泄漏。虚析构函数保证了在 `delete` 时，会沿着正确的派生关系链，从最底层的派生类开始，一路向上调用所有析构函数。
- **抽象基类 (Abstract Base Class, ABC) 与纯虚函数 (Pure Virtual Function)**:
  - **纯虚函数**: 在虚函数声明的末尾写上 `= 0`，就得到了一个纯虚函数。例如 `virtual void draw() const = 0;`。
  - **抽象基类**: 任何包含至少一个纯虚函数的类，都成为抽象基类。
  - **特性**:
    1. **不能被实例化**: 你不能创建抽象基类的对象（如 `Drawable d;` 会编译失败）。
    2. **强制派生类实现**: 任何继承自抽象基类的**非抽象**派生类，都**必须**为所有纯虚函数提供实现。
  - **用途**: 抽象基类被用来定义**接口 (Interface)**。它只定义一个“契约”——“任何想成为我这种类型的类，都必须具备这些能力”，而不关心具体如何实现。这在大型系统设计中是定义模块边界和插件体系结构的关键。

---

**Phase 3 总结**

我们已经完成了面向对象编程的全部核心内容。

- 你从 `struct` 和 `class` 开始，理解了**封装**如何保护数据、降低耦合。
- 你掌握了**构造函数和析构函数**，学会了如何通过 **RAII** 掌控对象的生命周期，实现了自动化资源管理。
- 你学会了使用**继承**来复用代码、建立清晰的 "is-a" 类型层次。
- 最后，你登上了 OOP 的顶峰，掌握了**多态**，通过**虚函数**和 **V-Table** 实现了真正的动态行为，让你的代码变得灵活、可扩展。

你现在所掌握的，已经不仅仅是 C++ 语法，而是一整套强大的、经过数十年验证的软件设计思想。你已经有能力去设计和构建复杂的、有良好结构的对象模型了。

我们的下一个阶段，**Phase 4: 现代 C++ 与标准库 (Productivity and Safety)**，将为你插上另一只翅膀。我们将学习 C++11 及以后引入的革命性特性，它们将极大地提升你的编程效率和代码安全性，让你写出既强大又优雅的现代 C++ 代码。

在你准备好迈向现代 C++ 的新纪元之前，可以先消化一下 Phase 3 的内容，或者提出任何你想深入探讨的问题。

## Phase 3: 面向对象编程 (Building Abstractions) - 总结

在 **Phase 3** 中，我们完成了从 C++ 的“使用者”到“创造者”的蜕变。我们不再局限于使用内置类型和标准库，而是学会了构建自己的、功能强大的、有生命的数据类型。

- **封装 (Encapsulation)**: 我们从 `struct` 与 `class` 的对比入手，理解了将**数据和行为捆绑**的重要性。通过 `public` 和 `private` 访问修饰符，我们学会了如何隐藏实现细节，只暴露稳定的公共接口，从而构建出健壮、低耦合、易于维护的模块。
- **构造与析构 (Construction & Destruction)**: 我们掌握了对象生命周期的两个关键节点。**构造函数**确保对象在诞生之初就处于有效状态，而**析构函数**则构成了 **RAII (Resource Acquisition Is Initialization)** 的基石，它保证了资源的自动释放。这让我们能够编写出安全、无泄漏的资源管理类。
- **继承 (Inheritance)**: 我们学习了如何通过继承来表达 **"is-a"** 的关系，实现了**代码复用**并建立了清晰的**类型层次结构**。我们还探讨了继承与**组合 (Composition)** 的权衡，明确了“优先使用组合”这一现代 C++ 的设计原则。
- **多态 (Polymorphism)**: 这是本阶段的高潮。我们通过 `virtual` 关键字赋予了对象**动态行为**的能力。理解了**静态绑定**与**动态绑定**的根本区别，并揭示了 `vtable` 这一底层实现机制。多态让我们能编写出真正通用、灵活、可扩展的代码，是构建大型软件框架的核心。

至此，你已经掌握了 C++ 作为一门面向对象语言的全部精髓。你现在有能力设计和实现复杂的系统，比如一个游戏引擎中的角色系统，或是一个图形应用中的图形基元。

---

## 综合实践练习 (Phase 1-3)

这里是五个精心设计的练习，难度递增，它们将迫使你综合运用变量、控制流、内存管理、指针、引用、以及面向对象的全部知识。

### 练习 1: 简单的计分板 (难度: ★☆☆☆☆)

**目标**: 创建一个 `Score` 类来追踪单个玩家的分数，并编写一个简单的程序来操作它。

**涉及知识点**: `class` 基础, 封装 (`private`, `public`), 构造函数, 成员函数。

**任务要求**:

1. 设计一个 `Score` 类。
2. 它应该有一个 `private` 的 `int` 成员变量来存储分数。
3. 提供一个**构造函数**，在创建 `Score` 对象时将分数初始化为 0。
4. 提供以下 `public` 成员函数：
   - `void add(int points)`: 增加指定的分数（分数不能为负）。
   - `void reset()`: 将分数重置为 0。
   - `int get()`: 返回当前的分数。
5. 在 `main` 函数中，创建一个 `Score` 对象，进行几次加分操作，重置一次，再加分，并不断打印当前分数以验证你的类是否工作正常。

---

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

### 练习 3: 武器与伤害计算 (难度: ★★★☆☆)

**目标**: 创建一个 `Weapon` 基类和几个派生类，并使用它们来计算对一个 `Armor` 对象的伤害。

**涉及知识点**: 继承, `protected` 成员, 构造函数链, 组合。

**任务要求**:

1. 设计一个 `Armor` 类，它有一个 `private` 的 `int` 成员 `defense_`，表示防御力。提供构造函数和 `getDefense()` 方法。
2. 设计一个 `Weapon` **基类**:
   - 它有一个 `protected` 的 `int` 成员 `baseDamage_`。
   - 提供一个构造函数来初始化 `baseDamage_`。
   - 提供一个 `public` 成员函数 `int getDamage()`，直接返回 `baseDamage_`。
3. 设计两个派生类 `Sword` 和 `MagicWand`，它们都 `public` 继承自 `Weapon`：
   - `Sword`: 构造函数除了调用基类构造函数外，还额外初始化一个 `private` 的 `int sharpness_`（锋利度）。重写 `getDamage()` 函数，使其返回 `baseDamage_ + sharpness_`。
   - `MagicWand`: 构造函数除了调用基类构造函数外，还额外初始化一个 `private` 的 `int magicBonus_`（魔法加成）。重写 `getDamage()` 函数，使其返回 `baseDamage_ * magicBonus_`。
4. 设计一个 `Fighter` 类：
   - 它**包含 (组合)** 一个 `Armor` 对象和一个 `Weapon*` 指针作为成员。
   - 提供一个构造函数，接收一个 `Armor` 对象和一个 `Weapon*` 来初始化成员。
   - 提供一个 `public` 成员函数 `void attack(Fighter& target)`。此函数计算对 `target` 的伤害，伤害公式为 `this->weapon->getDamage() - target.armor.getDefense()` (伤害至少为 0)。
5. 在 `main` 函数中，创建 `Sword` 和 `MagicWand` 对象，创建两个 `Fighter`，一个装备剑，一个装备魔杖，并让他们互相攻击，打印出造成的伤害。

---

### 练习 4: 多态的绘图板 (难度: ★★★★☆)

**目标**: 使用多态来管理一个可以绘制不同形状的系统。

**涉及知识点**: 多态, `virtual` 函数, 纯虚函数, 抽象基类, `override`, `std::vector` 与基类指针。

**任务要求**:

1. 设计一个**抽象基类** `Shape`：
   - 它有一个**纯虚函数** `virtual void draw() const = 0;`。
   - 它应该有一个**虚析构函数** `virtual ~Shape() {}` (思考为什么这很重要)。
2. 设计三个派生类 `Circle`, `Rectangle`, `Triangle`，它们都继承自 `Shape`。
   - 每个类都有自己的构造函数来接收必要的尺寸信息（如半径、长宽等）。
   - 每个类都必须 `override` `draw()` 函数，在其中打印出描述自己如何被绘制的文本，例如 `std::cout << "Drawing a Circle with radius 5.\\n";`。
3. 在 `main` 函数中:
   - 创建一个 `std::vector<Shape*>` 容器。
   - 在堆上 `new` 出几个不同类型的形状（`Circle`, `Rectangle`等）对象，并将它们的指针存入 `vector`。
   - 编写一个循环，遍历这个 `vector`，并对每个 `Shape*` 指针调用 `draw()` 函数。观察多态是如何工作的——同一行代码 `shape_ptr->draw();` 能够调用出不同子类的实现。
   - 在程序结束前，**必须**遍历 `vector` 并 `delete` 掉所有你 `new` 出来的对象，以避免内存泄漏。

---
