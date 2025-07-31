#include <iostream>
#include <random>
#include <string>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib(5, 20);

int main()
{
    std::cout << "欢迎玩家进入游戏世界，请输入你的名字\n";
    std::string name{};
    std::getline(std::cin, name);
    
    int strength {distrib(gen)};
    int agility {distrib(gen)};
    int intelligence {distrib(gen)};

    std::cout << "\n你的属性分别为";
    std::cout << "力量为 " << strength << "; " << "敏捷为 " << agility << "; " << "智力为 " << intelligence << ";\n";

    std::cout << "你现在拥有 10 点自由属性可以分配，'1' '2' '3' 分别表示力量，敏捷和智力，现在开始添加\n";

    int free_point {10};
    int plan {};
    while (free_point > 0){
        std::cin >> plan;
        switch (plan){
            case 1:
                ++strength;
                break;
            case 2:
                ++agility;
                break;
            case 3:
                ++intelligence;
                break;
        }
        std::cout << "力量为 " << strength << "; " << "敏捷为 " << agility << "; " << "智力为 " << intelligence << ";\n";
        --free_point;
    }
    if (strength == agility == intelligence || (strength < 15 && intelligence < 15 && agility < 15))
    {
        std::cout << "你是一个新手\n";
        std::cout << "力量为 " << strength << "; " << "敏捷为 " << agility << "; " << "智力为 " << intelligence << ";\n";        
    }
    else if (strength >= agility && strength >= intelligence && strength > 15)
    {
        std::cout << "你是一个战士\n";
        std::cout << "力量为 " << strength << "; " << "敏捷为 " << agility << "; " << "智力为 " << intelligence << ";\n";        
    }
    else if (agility >= strength && agility >= intelligence && agility > 15)
    {
        std::cout << "你是一个盗贼\n";
        std::cout << "力量为 " << strength << "; " << "敏捷为 " << agility << "; " << "智力为 " << intelligence << ";\n";        
    }
    else if (intelligence >= agility && intelligence >= strength && intelligence > 15)
    {
        std::cout << "你是一个法师";
        std::cout << "力量为 " << strength << "; " << "敏捷为 " << agility << "; " << "智力为 " << intelligence << ";\n";        
    }
}
