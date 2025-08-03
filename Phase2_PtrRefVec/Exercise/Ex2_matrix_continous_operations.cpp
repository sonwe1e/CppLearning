#include <iostream>

// 方案二：创建 (请你来实现)
int** createMatrix_challenge(int rows, int cols) {
    // 提示:
    // 1. 分配一块能容纳 rows * cols 个整数的连续内存 dataBlock (类型是 int*)
    int* dataBlock {new int[rows * cols]};

    // 2. 分配一个能容纳 rows 个行指针的数组 matrix (类型是 int**)
    int** matrix {new int*[rows]};

    // 3. 使用一个 for 循环，将 matrix 的每个指针 matrix[i] 
    //    指向 dataBlock 中的正确位置 (使用我们推导出的公式)
    for (int i {0}; i<rows; ++i)
    {
        matrix[i] = &dataBlock[i*cols];
    }

    // 4. 返回最终的 matrix
    return matrix; // 请替换这里的代码
}

// 方案二：销毁 (请你来实现)
void destroyMatrix_challenge(int** matrix, int rows) {
    // 提示:
    // 我们在 createMatrix_challenge 中 new 了几次？分别 new 了什么？
    // 那么这里就应该 delete 几次。
    // 思考：销毁的顺序重要吗？应该先 delete 数据块，还是先 delete 行指针数组？
    // (提示：行指针数组里的指针指向数据块，如果先销毁数据块...)
    for (int i {0}; i<rows; ++i)
    {
        matrix[i] = nullptr; // 将行指针数组的每个指针置空
    }
    delete[] matrix[0]; // 删除数据块
    delete[] matrix; // 删除行指针数组
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
