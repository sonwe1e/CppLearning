#include <iostream>
#include <cassert> // 引入断言头文件，用于调试

// Score 类用于追踪单个玩家的分数
// 设计目标: 简洁、安全、高效
class Score
{
private:
    // C++11 类内成员初始化。
    // 这确保了只要创建 Score 对象，score 就会被可靠地初始化为 0。
    // 这也让我们能够使用 =default 的默认构造函数。
    int m_score{ 0 }; 

public:
    // 使用 =default 来告诉编译器：请为我生成一个标准的默认构造函数。
    // 编译器生成的版本会利用上面的类内初始化，将 m_score 初始化为 0。
    // 这样做比自己写一个空的或者带初始化列表的构造函数更简洁、意图更明确。
    Score() = default;

    // 增加分数。
    // 标记为 noexcept，因为这个函数逻辑简单，保证不会抛出异常。
    // 这能给编译器提供优化机会。
    void add(int points) noexcept
    {
        // 对于简单的逻辑分支，if 语句通常比三元运算符更具可读性。
        if (points > 0)
        {
            m_score += points;
        }
        // 对于不符合条件的输入（例如 points <= 0），我们选择静默忽略。
        // 在调试版本中，我们也可以使用 assert 来立即发现不合法的调用。
        // assert(points > 0 && "Added points must be positive.");
    }

    // 将分数重置为 0。
    // 同样，此函数不会抛出异常。
    void reset() noexcept
    {
        m_score = 0;
    }

    // 获取当前分数。
    // const 成员函数: 承诺不修改任何成员变量，这是一个极好的习惯。
    // noexcept: 同样，此函数不会抛出异常。
    int get() const noexcept
    {
        return m_score;
    }
};

int main()
{
    Score player1_score; // 使用更具描述性的变量名
    std::cout << "Initial score: " << player1_score.get() << '\n';

    player1_score.add(10);
    std::cout << "Score after adding 10: " << player1_score.get() << '\n';

    player1_score.add(-10); // 尝试增加一个负数
    std::cout << "Score after attempting to add -10: " << player1_score.get() << '\n';

    player1_score.reset();
    std::cout << "Score after reset: " << player1_score.get() << '\n';

    player1_score.add(100);
    std::cout << "Score after adding 100: " << player1_score.get() << '\n';

    return 0;
}
