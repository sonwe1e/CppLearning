// 任务： 创建一个函数，它接收一个整数序列，并返回一个只包含其中偶数的新序列。
#include <iostream>
#include <vector>
#include <string>

// --- 旧方法：原始指针（危险且复杂） ---
int* filterEvens_C_Style(const int* inputArray, int inputSize, int& outputSize) {
    // 1. 第一次遍历以计算偶数的数量，以便知道需要分配多少内存
    outputSize = 0;
    for (int i = 0; i < inputSize; ++i) {
        if (inputArray[i] % 2 == 0) {
            outputSize++;
        }
    }

    // 2. 在堆上分配内存。调用者现在负责删除它！
    if (outputSize == 0) return nullptr;
    int* resultArray = new int[outputSize];

    // 3. 第二次遍历以复制偶数
    int currentIndex = 0;
    for (int i = 0; i < inputSize; ++i) {
        if (inputArray[i] % 2 == 0) {
            resultArray[currentIndex++] = inputArray[i];
        }
    }
    return resultArray;
}

// --- 现代 C++ 方法：std::vector（安全、简单且高效） ---
std::vector<int> filterEvens_Modern(const std::vector<int>& inputArray) {
    std::vector<int> resultArray;
    // 甚至可以预先分配内存以避免重新分配，尽管通常不是必需的。
    // resultArray.reserve(inputArray.size()); // 性能优化

    for (int number : inputArray) {
        if (number % 2 == 0) {
            // vector 会自行管理内存。
            // 如果其内部缓冲区已满，它会自动分配一个更大的缓冲区。
            resultArray.push_back(number);
        }
    }
    return resultArray; // C++11 及更高版本可以使用移动语义高效地返回此结果
}

void printVec(const std::vector<int>& vec) {
    for (int x : vec) {
        std::cout << x << " ";
    }
    std::cout << "\n";
}

int main() {
    // === C 风格用法 ===
    std::cout << "--- C 风格演示 ---\n";
    int raw_arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int result_size = 0;
    int* even_raw_arr = filterEvens_C_Style(raw_arr, 10, result_size);
    if (even_raw_arr != nullptr) {
        for (int i = 0; i < result_size; ++i) std::cout << even_raw_arr[i] << " ";
        std::cout << "\n";
        delete[] even_raw_arr; // 关键：手动释放内存。很容易忘记！
    }

    // === 现代 C++ 用法 ===
    std::cout << "\n--- 现代 C++ 演示 ---\n";
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> even_vec = filterEvens_Modern(vec);
    printVec(even_vec);
    // 无需 'delete'。内存已自动管理！

    // === std::string 示例 ===
    std::string greeting = "Hello";
    std::string name = "North Star";
    std::string message = greeting + ", " + name + "!"; // Simple concatenation
    message += " Welcome!";
    std::cout << "\n" << message << " (Length: " << message.length() << ")\n";

    return 0;
}
