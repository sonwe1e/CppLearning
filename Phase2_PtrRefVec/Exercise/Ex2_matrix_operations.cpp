#include <iostream>

// 方案一：创建 (非连续内存分配)
int** createMatrix_challenge(int rows, int cols)
{
    // 提示:
    // 1. 分配一个能容纳 rows 个行指针的数组 matrix (类型是 int**)
    int** matrix {new int*[rows]};

    // 2. 使用一个 for 循环，为每一行分配 cols 个整数的内存空间
    //    每次调用 new int[cols] 都会在堆上分配一块独立的内存
    for (int i {0}; i<rows; ++i)
    {
        matrix[i] = new int[cols];
    }
    // 3. 返回最终的 matrix
    return matrix;
}

// 方案一：销毁 (对应非连续内存分配)
void destroyMatrix_challenge(int** matrix, int rows)
{
    // 提示:
    // 我们在 createMatrix_challenge 中 new 了多少次？
    // 1次 new int*[rows] + rows次 new int[cols]
    // 那么这里就应该 delete 对应的次数
    // 思考：销毁的顺序重要吗？应该先 delete 行数据，还是先 delete 行指针数组？
    // (提示：行指针数组里的指针指向各行数据，如果先销毁行指针数组...)
    if (matrix == nullptr)
    {
        return;
    }
    // 先释放每一行的内存空间
    for (int i {0}; i<rows; ++i)
    {
        delete[] matrix[i];
        matrix[i] = nullptr;
    }
    // 最后释放行指针数组
    delete[] matrix;
}

int main()
{
    // 定义矩阵的大小
    int rows {8};
    int cols {5};
    // 创建矩阵
    int** test {createMatrix_challenge(rows, cols)};

    // 在矩阵的位置添加数据
    for (int i {0}; i<rows; ++i)
    {
        for (int j {0}; j<cols; ++j)
        {
            test[i][j] = (i+1) * (j+1);
        }
    }

    // 可视化矩阵
    for (int i {0}; i<rows; ++i)
    {
        for (int j {0}; j<cols; ++j)
        {
            if (j != cols - 1)
            {
                std::cout << test[i][j] << ' ';
            }
            else
            {
                std::cout << test[i][j] << '\n';
            }
        }
    }

    destroyMatrix_challenge(test, rows);
}
