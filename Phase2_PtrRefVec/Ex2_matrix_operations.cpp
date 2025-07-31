#include <iostream>

// 创建矩阵空间
int** createMatrix(int rows, int cols)
{
    int** ptr {new int*[rows]};

    for (int i {0}; i<rows; ++i)
    {
        ptr[i] = new int[cols];
    }
    return ptr;
}

// 销毁矩阵空间 
void destroyMatrix(int** matrix, int rows)
{
    if (matrix == nullptr)
    {
        return;
    }
    for (int i {0}; i<rows; ++i)
    {
        delete[] matrix[i];
        matrix[i] = nullptr;
    }
    delete[] matrix;
}

int main()
{
    // 定义矩阵的大小
    int rows {8};
    int cols {5};
    // 创建矩阵
    int** test {createMatrix(rows, cols)};

    // 在矩阵的位置添加数据
    for (int i {0}; i<rows; ++i)
    {
        for (int j {0}; j<cols; ++j)
        {
            test[i][j] = (i+1) * (j+1);
        }
    }


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

    destroyMatrix(test, rows);
}
