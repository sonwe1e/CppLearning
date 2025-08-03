/*  
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
*/

#include <iostream>

class Score
{
    private:
        int score {0};
    
    public:
        Score(): score(0){}
        void add(int points)
        {
            score = points > 0 ? score + points : score;
        }

        void reset()
        {
            score = 0;
        }

        int get() const {
            return score;
        }
};

int main()
{
    Score a1;
    std::cout << a1.get() << '\n';
    a1.add(10);
    std::cout << a1.get() << '\n';
    a1.add(-10);
    std::cout << a1.get() << '\n';
    a1.reset();
    std::cout << a1.get() << '\n';
}
