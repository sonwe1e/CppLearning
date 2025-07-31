#include <iostream>

// 函数接收一个指针和大小来处理数组
// 这是传统的 C 风格方式
void printArray_C_Style(int* arr, int size) {
    std::cout << "Printing array (C-style): ";
    for (int i = 0; i < size; ++i) {
        // 使用指针算术访问元素：*(arr + i)
        // 等价于更常见的数组下标语法：arr[i]
        std::cout << *(arr + i) << " ";
    }
    std::cout << "\n";
}

// 函数接收一个对数组的引用
// 这是现代 C++ 的一种更安全的方式
// 模板 <size_t N> 让我们可以传递任意大小的数组
template<size_t N>
void printArray_Modern(const int (&arr)[N]) {
    std::cout << "Printing array (Modern C++ reference): ";
    // 使用范围 for 循环，因为引用保留了数组的大小信息
    for (int element : arr) {
        std::cout << element << " ";
    }
    std::cout << "\n";
}

int main() {
    // 1. 声明和初始化一个原生数组 (在栈上)
    int numbers[5] = {10, 20, 30, 40, 50};

    // 2. 数组名退化为指针
    int* ptr_to_first_element = numbers; // 'numbers' 自动退化为 &numbers[0]

    std::cout << "Address of the array's first element (&numbers[0]): " << &numbers[0] << "\n";
    std::cout << "Value of the pointer (ptr_to_first_element):      " << ptr_to_first_element << "\n";

    // 3. 使用指针访问数组元素
    std::cout << "First element using pointer: *ptr_to_first_element = " << *ptr_to_first_element << "\n";

    // 4. 指针算术 (Pointer Arithmetic)
    // 指针加 1，移动的字节数是 sizeof(所指向的类型)
    // 对于 int*，ptr + 1 意味着地址增加 4 或 8 字节
    int* ptr_to_second_element = ptr_to_first_element + 1;
    std::cout << "Second element using pointer arithmetic: *(ptr_to_first_element + 1) = " << *(ptr_to_first_element + 1) << "\n";
    std::cout << "Accessing second element via ptr_to_second_element: " << *ptr_to_second_element << "\n";

    // 5. 数组下标语法的真相
    // 编译器会将 numbers[2] 翻译成 *(numbers + 2)
    std::cout << "Third element using array syntax (numbers[2]): " << numbers[2] << "\n";
    std::cout << "Third element using explicit pointer arithmetic (*(numbers + 2)): " << *(numbers + 2) << "\n";

    // 6. 将数组传递给函数
    // 当按值传递时，数组退化为指针，丢失了大小信息！
    printArray_C_Style(numbers, 5); // 必须手动传递大小

    // 使用引用传递，大小信息被保留
    printArray_Modern(numbers);
}
