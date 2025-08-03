#include <iostream>
#include <string>
#include <vector>

// 基类
class Creature {
protected:
    std::string name_;
public:
    Creature(const std::string& name) : name_(name) {}

    // 注意：这是一个普通的、非虚的函数
    void attack() const {
        std::cout << "Creature " << name_ << " performs a generic attack!\n";
    }

    std::string getName() const { return name_; }
};

// 派生类
class Player : public Creature {
public:
    Player(const std::string& name) : Creature(name) {}

    void attack() const { // 试图“覆盖”基类的函数
        std::cout << "Player " << name_ << " swings a sword!\n";
    }
};

class Goblin : public Creature {
public:
    Goblin() : Creature("Goblin") {}

    void attack() const {
        std::cout << "Goblin " << name_ << " jabs with a rusty dagger!\n";
    }
};

// 战斗函数。我们希望它能处理任何 Creature
void battle(const Creature attacker, const Creature defender) {
    std::cout << "\n--- Battle Begins ---\n";
    std::cout << attacker.getName() << " attacks " << defender.getName() << ".\n";

    // 问题就在这里！
    attacker.attack();

    std::cout << "--- Battle Ends ---\n";
}

int main() {
    Player hero("Lilian");
    Goblin gob;

    // 直接调用，没有问题。编译器在编译时就知道对象的具体类型。
    hero.attack(); // 输出: Player Lilian swings a sword!
    gob.attack();  // 输出: Goblin Goblin jabs with a rusty dagger!

    // 现在，通过 battle 函数，使用基类指针调用
    battle(hero, gob);

    return 0;
}
