// 现代 C++ 版本 (Modern C++ Version)

// 引入<memory>头文件以使用智能指针，<string>和<algorithm>提供额外功能
#include <iostream>
#include <memory>   // 核心改进：用于 std::unique_ptr 和 std::make_unique
#include <string>   // 用于更灵活地传递名字
#include <algorithm>// 用于 std::max

// --- Armor Class (与原版基本一致，仅做风格统一) ---
class Armor
{
private:
    int defense_; // 风格统一：使用下划线后缀表示私有成员

public:
    // 使用显式构造函数(explicit)，防止意外的隐式类型转换。
    // 例如防止不小心写出 Armor myArmor = 10; 这样的代码。
    explicit Armor(int defense) : defense_(defense) {}

    int getDefense() const
    {
        return defense_; // 风格统一：移除不必要的 `this->`
    }
};

// --- Weapon Class (与原版基本一致，添加虚析构函数) ---
class Weapon
{
protected:
    int baseDamage_;

public:
    explicit Weapon(int baseDamage) : baseDamage_(baseDamage) {}

    // 【重要】当一个类拥有虚函数时，几乎总是需要一个虚析构函数。
    // 当我们通过基类指针删除一个派生类对象时（例如 `delete weaponPtr;`），
    // 如果析构函数不是虚函数，只有基类的析构函数会被调用，派生类部分会造成内存泄漏。
    // 声明为 `virtual ~Weapon() = default;` 意味着我们要求编译器生成一个默认的、虚的析构函数。
    virtual ~Weapon() = default;

    virtual int getDamage() const
    {
        return baseDamage_;
    }

    // 添加一个辅助函数，用于获取武器的描述，增强表现力
    virtual std::string getDescription() const = 0; // 纯虚函数 (Pure Virtual Function)
    // = 0 表示这个函数在基类中没有实现，任何派生类都【必须】提供自己的实现。
    // 这使得 Weapon 成为一个“抽象基类”(Abstract Base Class)，它不能被直接实例化（即不能创建 Weapon w(10);）。
    // 这在逻辑上是合理的，因为“武器”是一个抽象概念，你拥有的总是“剑”、“魔杖”等具体武器。
};

// --- Sword Class (继承自 Weapon) ---
class Sword : public Weapon
{
private:
    int sharpness_;

public:
    Sword(int baseDamage, int sharpness) : Weapon(baseDamage), sharpness_(sharpness) {}

    int getDamage() const override
    {
        return baseDamage_ + sharpness_;
    }
    
    std::string getDescription() const override
    {
        return "锋利的剑 (Sharp Sword)";
    }
};

// --- MagicWand Class (继承自 Weapon) ---
class MagicWand : public Weapon
{
private:
    int magicBonus_;

public:
    MagicWand(int baseDamage, int magicBonus) : Weapon(baseDamage), magicBonus_(magicBonus) {}

    int getDamage() const override
    {
        return baseDamage_ * magicBonus_;
    }

    std::string getDescription() const override
    {
        return "附魔的魔杖 (Enchanted Magic Wand)";
    }
};

// --- Fighter Class (核心改进所在) ---
class Fighter
{
private:
    std::string name_;
    Armor armor_;
    // 【核心改进】使用 std::unique_ptr 替换裸指针 Weapon*
    // std::unique_ptr 是一个“智能指针”，它封装了一个裸指针，并保证当 unique_ptr 自己被销毁时，
    // 它所管理的指针指向的内存也会被自动释放（调用 delete）。
    // 这实现了 RAII (Resource Acquisition Is Initialization) 原则，即资源（这里是堆内存）的生命周期
    // 与对象的生命周期绑定，彻底杜绝了内存泄漏的可能。
    // `unique_ptr` 表达了对所管理对象的“独占所有权”(exclusive ownership)，一个 Fighter 拥有自己的、独一无二的 Weapon。
    std::unique_ptr<Weapon> weapon_;

public:
    // 构造函数现在接收一个 std::unique_ptr<Weapon>。
    // 参数 `std::unique_ptr<Weapon> weapon` 是按值传递的，这意味着所有权将被转移到函数参数中。
    // 然后我们使用 `std::move` 将所有权从参数再次转移到成员变量 `weapon_` 中。
    Fighter(std::string name, Armor armor, std::unique_ptr<Weapon> weapon)
        : name_(std::move(name)), // std::move 用于高效转移string的内容
          armor_(armor), // Armor对象很小，直接按值拷贝
          weapon_(std::move(weapon)) // 【核心改进】通过std::move转移Weapon的所有权
    {
    }

    // 【接口改进】attack 函数现在是 const 的，因为它不修改攻击者自身的状态。
    // 它接收一个 const 引用，因为它也不修改目标的状态（只是读取防御力）。
    // 它返回计算出的伤害值，将计算与输出解耦。
    int attack(const Fighter &target) const
    {
        // 调用 weapon_->getDamage() 的语法和裸指针完全一样。
        int rawDamage = weapon_->getDamage() - target.armor_.getDefense();
        // 使用 std::max 确保伤害值至少为0，符合题目要求。
        return std::max(0, rawDamage);
    }

    // 提供 getter 函数以访问私有成员，供外部（如main）使用
    const std::string& getName() const { return name_; }
    const Weapon* getWeapon() const { return weapon_.get(); }
};

int main()
{
    // C++11/14 风格的初始化
    
    // 创建 Armor 对象
    Armor heavyArmor(10);
    Armor lightArmor(4);

    // 【核心改进】创建 Weapon 对象并管理其所有权
    // 我们必须在堆(heap)上创建 Weapon 对象，因为 unique_ptr 需要管理它的生命周期。
    // std::make_unique 是 C++14 引入的最佳实践，它更安全、更高效。
    // 为了严格遵守 C++11，写法是 `std::unique_ptr<Sword>(new Sword(3, 6))`。
    // 这里我们使用更推荐的 C++14 写法并加以说明。
    auto sword = std::make_unique<Sword>(3, 6);
    auto magicWand = std::make_unique<MagicWand>(1, 4);

    // 创建 Fighter 时，我们将 weapon 的所有权通过 `std::move` 转移给 Fighter 的构造函数。
    // `std::move` 本身不移动任何东西，它只是一个类型转换，将一个左值（如 `sword`）
    // 转换为右值引用，使其能够匹配接收 `unique_ptr` 的移动构造函数。
    // 转移后，main 函数中的 `sword` 和 `magicWand` 智能指针变量将变为空(nullptr)，
    // 因为它们所拥有的资源已经“移交”给了 Fighter 对象。
    Fighter warrior("战士", heavyArmor, std::move(sword));
    Fighter mage("法师", lightArmor, std::move(magicWand));

    // 现在，攻击逻辑和输出逻辑是分离的
    int damageToMage = warrior.attack(mage);
    std::cout << warrior.getName() << " 使用 " << warrior.getWeapon()->getDescription() 
              << " 攻击了 " << mage.getName() 
              << ", 造成了 " << damageToMage << " 点伤害！" << std::endl;

    int damageToWarrior = mage.attack(warrior);
    std::cout << mage.getName() << " 使用 " << mage.getWeapon()->getDescription() 
              << " 攻击了 " << warrior.getName() 
              << ", 造成了 " << damageToWarrior << " 点伤害！" << std::endl;

    // 无需手动 delete任何东西！
    // 当 main 函数结束时，`warrior` 和 `mage` 对象被销毁。
    // 作为它们成员的 `std::unique_ptr<Weapon> weapon_` 也会被销毁。
    // `unique_ptr` 的析构函数会自动调用 `delete` 来释放它所管理的 Sword 和 MagicWand 对象占用的堆内存。
    // 这就是 RAII 的威力。
}
