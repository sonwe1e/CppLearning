/*
### 练习 3: 武器与伤害计算 (难度: ★★★☆☆)
... (题目描述省略) ...
*/

#include <iostream>

// [评价-结构] Armor 类设计清晰，封装了核心属性 defense。这是一个很好的实践开端。
class Armor
{
private:
    // [评价-语法] 成员变量命名 `defense` 很直观。在团队协作中，通常会统一命名规范，
    // 例如使用后缀 `_`（如 `defense_`）或前缀 `m_`（如 `m_defense`）来区分成员变量。
    // 该代码在不同类中命名规范不统一（例如 Sword 中的 sharpness_）。
    int defense;

public:
    // [评价-语法] 使用成员初始化列表 (member initializer list) `: defense(refden)` 是 C++ 中最高效、最正确的初始化方式。
    // 相比在构造函数体内部使用赋值语句 `this->defense = refden;`，初始化列表直接在对象内存被分配时进行“构造”，
    // 避免了“默认构造后再赋值”的额外开销。对于拥有 const 成员或引用成员的类，这是唯一可行的初始化方法。
    Armor(int refden) : defense(refden) {}

    // [评价-语法] `getDefense() const` 是一个出色的设计。`const` 关键字在这里有两个含义：
    // 1. 它向调用者承诺，这个函数不会修改 Armor 对象的任何状态。
    // 2. 它使得 `const Armor` 类型的对象也能够调用此函数。
    // [评价-风格] `this->defense` 中的 `this->` 在这里是可选的，因为没有参数名与成员变量名冲突。
    // 有些编码规范要求显式使用 `this->` 以增加可读性，而另一些则认为在无歧义时省略更为简洁。
    int getDefense() const
    {
        return this->defense;
    }
};

// [评价-结构] Weapon 作为基类，定义了所有武器的公共接口（getDamage）和基础属性（baseDamage），这是面向对象设计的经典应用。
class Weapon
{
protected:
    // [评价-结构] `protected` 访问修饰符的选择是恰当的。它允许派生类 (Sword, MagicWand) 直接访问 `baseDamage`，
    // 同时禁止外部代码直接访问，维持了一定程度的封装。
    int baseDamage;

public:
    Weapon(int damage) : baseDamage(damage) {}

    // [评价-逻辑] `virtual int getDamage() const` 是整个设计的核心。`virtual` 关键字启用了“动态多态” (dynamic polymorphism)。
    // 这意味着当你通过基类指针（如 `Weapon*`）调用 `getDamage()` 时，C++ 运行时系统会根据指针实际指向的对象类型
    // (是 Sword 还是 MagicWand) 来决定调用哪个版本的 `getDamage()` 函数。这是实现 `Fighter::attack` 逻辑的关键。
    virtual int getDamage() const
    {
        return this->baseDamage;
    }
};

// [评价-结构] Sword 通过 `public Weapon` 继承，正确地表达了 "is-a" (是一个) 的关系。
class Sword : public Weapon
{
private:
    int sharpness{}; // [评价-语法] 使用 C++11 的花括号初始化 `{}` 为成员变量提供了默认值 (0)，这是一个好习惯，可以防止未初始化。

public:
    // [评价-语法] 构造函数链 `Sword(...) : Weapon(damage), ...` 的使用是正确的。
    // 派生类构造函数必须调用其基类的某个构造函数来完成基类部分的初始化。
    Sword(int damage, int sharpness) : Weapon(damage), sharpness(sharpness) {}

    // [评价-语法] `int getDamage() const override` 非常出色！`override` 是 C++11 引入的关键字。
    // 它明确地告诉编译器，这个函数意图覆盖（override）一个基类中的虚函数。
    // 如果基类中没有可被覆盖的同名、同参数、同`const`属性的虚函数，编译器会报错。
    // 这可以防止因拼写错误或签名不匹配导致的多态失效，是现代 C++ 的最佳实践。
    int getDamage() const override
    {
        // [评价-逻辑] 伤害计算逻辑 `this->sharpness + this->baseDamage` 符合题目要求。
        // `this->` 在此也是可选的。
        return this->sharpness + this->baseDamage;
    }
};

class MagicWand : public Weapon
{
private:
    int magicBonus{};

public:
    MagicWand(int damage, int magicBonus) : Weapon(damage), magicBonus(magicBonus) {}

    int getDamage() const override
    {
        return this->baseDamage * this->magicBonus;
    }
};

// [评价-结构] Fighter 类通过组合 (Composition) 的方式持有一个 Armor 对象和一个 Weapon 指针，表达了 "has-a" (有一个) 的关系。
class Fighter
{
private:
    Armor armor;
    // [评价-逻辑/风险] **这是整个代码最核心、也是最薄弱的环节。**
    // 使用裸指针 (raw pointer) `Weapon* weapon` 引入了“所有权” (ownership) 的问题。
    // Fighter 类只是“借用”了这个指针，它并不知道这个指针指向的 Weapon 对象生命周期由谁管理。
    // 在 `main` 函数中，Weapon 对象是在栈上创建的，所以程序结束时会自动销毁，没有发生内存泄漏。
    // 但如果 Weapon 对象是通过 `new` 在堆上创建的，`Fighter` 类没有在其析构函数中 `delete weapon;`，就会导致内存泄漏。
    // 反之，如果 `Fighter` 析构函数 `delete` 了它，但这个 Weapon 对象被多个 Fighter 共享，就会导致二次释放等严重错误。
    // 这种所有权不明的设计是 C++98/03 时代 bug 的主要来源，也是现代 C++ 着力解决的问题。
    Weapon *weapon;

public:
    // [评价-语法] 构造函数通过 const 引用接收 Armor 避免了一次不必要的拷贝，然后初始化成员 `armor`，这是标准的。
    Fighter(const Armor &armor, Weapon *weapon) : armor(armor), weapon(weapon) {}

    // [评价-逻辑] `attack` 函数的逻辑基本正确，但有几点可以改进：
    // 1. 题目要求 "伤害至少为0"，但这里没有处理计算结果为负数的情况。
    // 2. 将伤害计算和文本输出耦合在了一起。更好的设计是让 `attack` 函数返回计算出的伤害值，由调用者（如 `main` 函数）决定如何显示。这遵循了“单一职责原则”。
    // 3. `target` 参数应为 `const Fighter& target`，因为攻击方不应该修改目标的状态，而只是读取其防御力。但这里要计算伤害并输出，所以暂时可以接受。更严谨的设计是，Fighter应该有一个`takeDamage`方法。
    void attack(Fighter &target)
    {
        // [评价-逻辑] 伤害计算公式正确，但`this->`仍然是可选的。
        std::cout << "打出伤害为" << this->weapon->getDamage() - target.armor.getDefense() << '\n';
    }
};

int main()
{
    Armor heavyArmor(10);
    Armor lightArmor(4);
    Sword sword(3, 6);
    MagicWand magicwand(1, 4);

    // [评价-逻辑] 这里的用法是“有效的”，但非常“危险”。
    // `warrior` 和 `mage` 持有 `sword` 和 `magicwand` 的地址。
    // 因为 `sword` 和 `magicwand` 是在 `main` 函数的栈上分配的，它们的生命周期与 `warrior` 和 `mage` 一样长，所以程序能正确运行。
    // 但如果 `sword` 在一个更小的作用域内被创建，当该作用域结束时，`sword` 被销毁，`warrior` 持有的 `weapon` 指针就变成了“悬垂指针” (dangling pointer)。
    // 之后再调用 `warrior.attack()` 就会导致未定义行为（通常是程序崩溃）。
    Fighter warrior(heavyArmor, &sword);
    Fighter mage(lightArmor, &magicwand);

    warrior.attack(mage);
    mage.attack(warrior);

    // [评价-总分]
    // - 结构 (Structure): 8/10。清晰的 OOP 设计，正确使用了继承、多态和组合。
    // - 语法 (Syntax): 9/10。掌握了成员初始化列表、const、virtual、override 等关键语法，非常不错。
    // - 逻辑与安全 (Logic & Safety): 6/10。核心逻辑基本实现，但裸指针带来的所有权和生命周期问题是重大隐患，接口设计也有待提升。
    //
    // 总体而言，这是一个非常好的 C++ OOP 入门练习，但它完美地暴露了从传统 C++ 到现代 C++ 所需跨越的最重要鸿沟：资源管理。
}
