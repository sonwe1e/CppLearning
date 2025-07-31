#include <iostream>
#include <string>
#include <random>
#include <limits> // 用于 std::numeric_limits

// --- Step 1: 消除魔法数字，使用常量定义游戏规则 ---
// 使用 constexpr 可以在编译期确定其值，性能更好，也更符合常量的语义。
constexpr int MIN_STAT_VALUE = 5;
constexpr int MAX_STAT_VALUE = 20;
constexpr int FREE_POINTS_TO_ALLOCATE = 10;
constexpr int CLASS_SPECIALIZATION_THRESHOLD = 15;

// --- Step 2: 使用 struct 聚合角色数据 ---
// 这是一个非常重要的步骤，它将角色的所有相关数据组织在一起。
// 这是面向对象编程思想的雏形。
struct Character
{
    std::string name;
    int strength{};
    int agility{};
    int intelligence{};
};

// --- Step 3: 创建辅助函数，避免代码重复 ---
// 这个函数只负责一件事：打印角色的当前属性。
// 参数使用 const Character& (常量引用)，这是一种高效且安全的传递方式。
// const: 保证函数不会修改角色数据。
// &:   避免复制整个 Character 对象，提升性能。
void print_stats(const Character& character)
{
    std::cout << "力量: " << character.strength
              << ", 敏捷: " << character.agility
              << ", 智力: " << character.intelligence << "\n";
}

// --- Step 4: 将职业判断逻辑分离到独立函数 ---
// 这个函数也只负责一件事：根据属性返回职业名称。
// 同样使用常量引用，因为它只读取数据，不修改。
std::string determine_class(const Character& character)
{
    // 严谨的 if-else if-else 结构，确保所有情况都被覆盖
    if (character.strength > CLASS_SPECIALIZATION_THRESHOLD && character.strength >= character.agility && character.strength >= character.intelligence)
    {
        return "战士 (Warrior)";
    }
    else if (character.agility > CLASS_SPECIALIZATION_THRESHOLD && character.agility >= character.strength && character.agility >= character.intelligence)
    {
        return "盗贼 (Rogue)";
    }
    else if (character.intelligence > CLASS_SPECIALIZATION_THRESHOLD && character.intelligence >= character.strength && character.intelligence >= character.agility)
    {
        return "法师 (Mage)";
    }
    else
    {
        // 任何不满足上述专精条件的情况，都归为新手
        return "新手 (Novice)";
    }
}

int main()
{
    // --- Step 5: 将随机数生成器置于其使用作用域内 ---
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(MIN_STAT_VALUE, MAX_STAT_VALUE);

    std::cout << "欢迎来到RPG世界！请输入你的角色名: ";
    
    Character player;
    std::getline(std::cin, player.name);

    // 初始化属性
    player.strength = distrib(gen);
    player.agility = distrib(gen);
    player.intelligence = distrib(gen);

    std::cout << "\n你好, " << player.name << "! 你的初始属性为:\n";
    print_stats(player);

    std::cout << "\n你现在拥有 " << FREE_POINTS_TO_ALLOCATE << " 点自由属性可以分配。\n";

    int points_remaining = FREE_POINTS_TO_ALLOCATE;
    while (points_remaining > 0)
    {
        std::cout << "\n剩余点数: " << points_remaining << "\n";
        std::cout << "请选择要增加的属性: (1-力量, 2-敏捷, 3-智力): ";
        
        int choice{};
        std::cin >> choice;

        // --- Step 6: 实现健壮的输入处理 ---
        if (std::cin.fail() || (choice < 1 || choice > 3))
        {
            std::cout << "输入无效，请输入 1, 2, 或 3。\n";
            // 重置 cin 的错误状态
            std::cin.clear();
            // 清空输入缓冲区，丢弃当前行所有错误输入
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue; // 跳过本次循环的剩余部分，重新开始
        }
        
        // 清理 cin 在成功读取整数后留下的换行符，为可能的后续 getline 做准备
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {
            case 1:
                ++player.strength;
                break;
            case 2:
                ++player.agility;
                break;
            case 3:
                ++player.intelligence;
                break;
        }
        --points_remaining;
        
        std::cout << "属性已更新: ";
        print_stats(player);
    }
    
    std::cout << "\n所有属性点分配完毕！\n";
    
    // 调用函数获取职业
    std::string player_class = determine_class(player);

    std::cout << "根据你的最终属性，你的职业是: " << player_class << "\n";
    std::cout << "最终属性: ";
    print_stats(player);

    return 0;
}
