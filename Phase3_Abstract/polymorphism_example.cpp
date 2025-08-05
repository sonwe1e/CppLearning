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
