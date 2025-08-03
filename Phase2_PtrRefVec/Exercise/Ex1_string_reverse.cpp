#include <iostream> // 包含输入输出流库，用于打印到控制台

// 定义一个函数，用于反转字符数组（字符串）
void reverseString(char* str)
{
    // 检查传入的字符串是否为空指针或者是一个空字符串
    if (str == nullptr || *str == '\0')
    {
        return; // 如果是空指针或空字符串，则直接返回，不做任何操作
    }

    // 初始化一个指针 `start` 指向字符串的开头
    char* start = str;
    // 初始化一个指针 `end` 也指向字符串的开头
    char* end = str;

    // 移动 `end` 指针，直到它指向字符串的末尾（即遇到空字符 '\0'）
    while (*end != '\0')
    {
        ++end; // 将 `end` 指针向后移动一位
    }
    // 当循环结束后，`end` 指向空字符 '\0'。
    // 我们需要将 `end` 指针回退一位，使其指向字符串的最后一个实际字符。
    --end;

    // 开始反转字符串：当 `start` 指针小于 `end` 指针时，就交换它们指向的字符
    while (start < end)
    {
        // 使用一个临时变量 `temp` 来存储 `start` 指向的字符
        char temp = *start;
        // 将 `end` 指向的字符赋值给 `start` 指向的位置
        *start =  *end;
        // 将临时变量 `temp`（即原本 `start` 指向的字符）赋值给 `end` 指向的位置
        *end = temp;

        // 将 `start` 指针向后移动一位
        ++start;
        // 将 `end` 指针向前移动一位
        --end;
    }
}

// 主函数，程序的入口点
int main()
{
    // 定义一个字符数组（字符串），并初始化为 "12"
    char string[] {"12didh12h9e19"};

    // 使用 std::cout 打印原始字符串
    std::cout << "原本的字符串为 " << string << '\n';

    // 调用 reverseString 函数来反转 `string`
    reverseString(string);

    // 打印反转后
    std::cout << "反转的字符串为 " << string << '\n';
}
