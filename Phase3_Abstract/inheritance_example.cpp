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
