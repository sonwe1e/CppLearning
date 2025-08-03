#include <iostream>
#include <cstddef> // For size_t

class MyVector {
private:
    int* data_;
    size_t size_;
    size_t capacity_;

public:
    // 任务1: 实现构造函数
    MyVector() {
        // 在这里初始化你的成员变量
    }

    // 任务2: 实现 size()
    size_t size() const {
        // ...
    }

    // 任务3: 实现 capacity()
    size_t capacity() const {
        // ...
    }

    // ... 其他函数我们稍后实现 ...
};

int main() {
    // 我们可以先简单测试一下
    MyVector vec;
    std::cout << "Initial size: " << vec.size() << std::endl;
    std::cout << "Initial capacity: " << vec.capacity() << std::endl;
    return 0;
}
