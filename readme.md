# C++ 学习之旅 (C++ Learning Journey)

这是一个系统性的 C++ 学习项目，从基础语法到现代 C++ 高级特性的完整学习路径。项目采用渐进式学习方法，每个阶段都有理论讲解、代码示例和实践练习。

## 📁 项目结构

```
CppLearning/
├── readme.md                     # 项目说明文档
├── test_playground.cpp           # 代码测试场地
├── .gitignore                    # Git 忽略文件
├── .vscode/                      # VS Code 配置
│   ├── settings.json
│   └── tasks.json
├── Phase1_Basic/                 # 第一阶段：基础语法
│   ├── readme.md                 # 阶段详细教程
│   ├── Ex1_basic_version.cpp     # 练习1：基础版本
│   └── Ex1_optimized_version.cpp # 练习1：优化版本
└── Phase2_PtrRefVec/            # 第二阶段：内存管理与数据结构
    ├── readme.md                # 阶段详细教程
    ├── Ex1_string_reverse.cpp   # 练习1：字符串反转
    ├── Ex2_matrix_operations.cpp # 练习2：矩阵操作
    ├── pointer_examples.cpp     # 指针示例
    ├── reference_examples.cpp   # 引用示例
    └── vector_string_examples.cpp # 容器示例
```

## 🎯 学习路径

### Phase 1: 基础语法 (Basic Syntax)

**学习重点：** 程序结构、变量类型、运算符、控制流、基础 I/O

**核心内容：**

- 程序的基本结构与编译
- 变量与核心数据类型
- 运算符与表达式
- 控制流 (if/else, for, while, switch)
- 基本输入输出 (iostream)

**实践项目：** RPG 角色属性生成器

- [`Ex1_basic_version.cpp`](Phase1_Basic/Ex1_basic_version.cpp) - 基础实现
- [`Ex1_optimized_version.cpp`](Phase1_Basic/Ex1_optimized_version.cpp) - 优化版本（结构化编程）

### Phase 2: 内存管理与数据结构 (Memory & Data Structures)

**学习重点：** 栈与堆、指针与引用、原生数组、现代 C++ 容器

**核心内容：**

1. **调用栈与作用域** - 理解程序执行机制
2. **栈内存 vs. 堆内存** - 性能与生命周期对比
3. **指针 (Pointers)** - 底层内存访问
4. **引用 (References)** - 安全的别名机制
5. **原生数组与指针算术** - C 风格数组的陷阱
6. **现代 C++ 容器** - `std::vector` 和 `std::string` 的 RAII 设计

**代码示例：**

- [`pointer_examples.cpp`](Phase2_PtrRefVec/pointer_examples.cpp) - 指针操作演示
- [`reference_examples.cpp`](Phase2_PtrRefVec/reference_examples.cpp) - 引用与数组传递
- [`vector_string_examples.cpp`](Phase2_PtrRefVec/vector_string_examples.cpp) - 现代容器 vs C 风格对比

**实践练习：**

- [`Ex1_string_reverse.cpp`](Phase2_PtrRefVec/Ex1_string_reverse.cpp) - 指针操作：就地字符串反转
- [`Ex2_matrix_operations.cpp`](Phase2_PtrRefVec/Ex2_matrix_operations.cpp) - 动态二维数组：矩阵操作

## 🛠️ 开发环境

**推荐编译器：** GCC 9.0+ 或 Clang 10.0+  
**C++ 标准：** C++17 或更高  
**IDE：** Visual Studio Code (已配置)

### 编译命令

```bash
# 基本编译
g++ -std=c++17 -Wall -Wextra filename.cpp -o output

# 调试版本
g++ -std=c++17 -Wall -Wextra -g filename.cpp -o output

# 优化版本
g++ -std=c++17 -Wall -Wextra -O2 filename.cpp -o output
```
