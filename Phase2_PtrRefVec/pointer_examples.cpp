#include <iostream>

void demonstratePointers() {
    // === 情况 1: 指向栈变量的指针 ===
    std::cout << "--- 指向栈变量的指针 ---\n";
    int stack_var = 42;
    int* ptr_to_stack; // 1. 声明：ptr_to_stack 是一个指向整型数据的指针。

    ptr_to_stack = &stack_var; // 2. 初始化：将 stack_var 的地址赋值给指针。

    // 3. 使用
    std::cout << "stack_var 的值: " << stack_var << "\n";
    std::cout << "stack_var 的地址 (&stack_var): " << &stack_var << "\n";
    std::cout << "ptr_to_stack 的值 (存储着地址): " << ptr_to_stack << "\n";
    std::cout << "ptr_to_stack 指向的值 (*ptr_to_stack): " << *ptr_to_stack << "\n\n";

    // 4. 通过指针修改数据
    *ptr_to_stack = 100;
    std::cout << "执行 '*ptr_to_stack = 100;' 后，stack_var 的值变为: " << stack_var << "\n\n";

    // === 情况 2: 指向堆变量的指针 ===
    std::cout << "--- 指向堆变量的指针 ---\n";
    int* ptr_to_heap; // 1. 声明

    // 2. 初始化：使用 'new' 在堆上分配一个整型空间并获取其地址。
    ptr_to_heap = new int(99);

    std::cout << "ptr_to_heap 的值 (一个堆地址): " << ptr_to_heap << "\n";
    std::cout << "该堆地址处的值 (*ptr_to_heap): " << *ptr_to_heap << "\n";

    // 3. 修改堆中的数据
    *ptr_to_heap += 1;
    std::cout << "修改后，堆中的值为: " << *ptr_to_heap << "\n";

    // 4. 关键：释放堆内存以防止内存泄漏。
    delete ptr_to_heap;
    ptr_to_heap = nullptr; // 良好实践：防止野指针。
    std::cout << "堆内存已释放。ptr_to_heap 现在是 nullptr。\n";
}

int main() {
    demonstratePointers();
    return 0;
}
