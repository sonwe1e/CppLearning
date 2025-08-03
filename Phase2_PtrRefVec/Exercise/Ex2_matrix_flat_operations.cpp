#include <iostream>

// 方案三：创建 (一维数组模拟二维矩阵)
int* createMatrix_challenge(int rows, int cols)
{
    // 提示:
    // 1. 分配一块能容纳 rows * cols 个整数的连续内存 dataBlock (类型是 int*)
    //    这种方式只需要一次内存分配，所有数据存储在连续的内存空间中
    int* dataBlock {new int[rows * cols]};

    // 2. 使用嵌套循环初始化矩阵元素
    //    访问二维坐标 (i,j) 对应的一维索引公式：i * cols + j
    for (int i {0}; i<rows; ++i)
    {
        for (int j {0}; j<cols; ++j)
        {
            dataBlock[i * cols + j] = (i + 1) * (j + 1); // 初始化矩阵元素
        }
    }
    // 3. 返回最终的 dataBlock
    return dataBlock;
}

// 获取一维矩阵元素的方式
int& getElement(int* matrix, int rows, int cols, int row, int col)
{
    // 提示：
    // 由于使用一维数组模拟二维矩阵，需要将二维坐标转换为一维索引
    // 转换公式：row * cols + col
    // 同时需要进行边界检查，确保索引不越界
    if (row < 0 || row >= rows || col < 0 || col >= cols)
    {
        throw std::out_of_range("Index out of bounds");
    }
    return matrix[row * cols + col];
}

// 方案三：销毁 (对应一维数组)
void destroyMatrix_challenge(int* matrix, int rows)
{
    // 提示:
    // 我们在 createMatrix_challenge 中 new 了几次？只有1次！
    // 那么这里就应该 delete 1次
    // 相比方案一和方案二，这种方式的内存管理最简单
    if (matrix == nullptr)
    {
        return;
    }
    delete[] matrix;
}

int main()
{
    // 定义矩阵的大小
    int rows {8};
    int cols {5};
    // 创建矩阵
    int* test {createMatrix_challenge(rows, cols)};

    // 可视化矩阵
    for (int i {0}; i<rows; ++i)
    {
        for (int j {0}; j<cols; ++j)
        {
            std::cout << getElement(test, rows, cols, i, j) << ' ';
        }
        if (i != rows - 1)
        {
            std::cout << '\n';
        }
    }

    destroyMatrix_challenge(test, rows);
}
