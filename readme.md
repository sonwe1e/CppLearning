# C++ 学习之旅 (C++ Learning Journey)

这是一个系统性的 C++ 学习项目，从基础语法到面向对象编程的完整学习路径。项目采用渐进式学习方法，每个阶段都有理论讲解、代码示例和实践练习。目前已完成三个核心阶段：基础语法、内存管理与数据结构、面向对象编程。

## 📁 项目结构

```
CppLearning/
├── readme.md                     # 项目说明文档
├── .gitignore                    # Git 忽略文件
├── .vscode/                      # VS Code 配置
│   ├── settings.json
│   └── tasks.json
├── Phase1_Basic/                 # 第一阶段：基础语法
│   ├── readme.md                 # 阶段详细教程
│   └── Exercise/                 # 练习文件夹
│       ├── Ex1_basic_version.cpp     # 练习1：基础版本
│       └── Ex1_optimized_version.cpp # 练习1：优化版本
├── Phase2_PtrRefVec/            # 第二阶段：内存管理与数据结构
│   ├── readme.md                # 阶段详细教程
│   ├── Exercise/                # 练习文件夹
│   │   ├── Ex1_string_reverse.cpp   # 练习1：字符串反转
│   │   ├── Ex2_matrix_operations.cpp # 练习2：矩阵操作（基础版本）
│   │   ├── Ex2_matrix_continous_operations.cpp # 练习2：连续内存矩阵
│   │   ├── Ex2_matrix_flat_operations.cpp # 练习2：扁平化矩阵
│   │   └── Ex3_self_vertor.cpp      # 练习3：自定义向量类
│   ├── pointer_examples.cpp     # 指针示例
│   ├── reference_examples.cpp   # 引用示例
│   └── vector_string_examples.cpp # 容器示例
└── Phase3_Abstract/             # 第三阶段：面向对象编程
    ├── readme.md                # 阶段详细教程
    ├── Exercise/                # 练习文件夹
    │   ├── Ex1_score.cpp            # 练习1：计分板（基础版本）
    │   ├── Ex1_score_improved.cpp   # 练习1：计分板（改进版本）
    │   ├── Ex2_dynamicname.cpp      # 练习2：动态命名形状（基础版本）
    │   ├── Ex2_dynamicname_modern.cpp # 练习2：动态命名形状（现代版本）
    │   ├── Ex3_weapon_class.cpp     # 练习3：武器类（基础版本）
    │   ├── Ex3_weapon_class_modern.cpp # 练习3：武器类（现代版本）
    │   └── Ex4_drawtable.cpp        # 练习4：绘图板
    ├── struct_class_example.cpp # struct vs class 示例
    ├── private_public_example.cpp # 访问控制示例
    ├── construct_destruct_example.cpp # 构造析构示例
    ├── inheritance_example.cpp  # 继承示例
    ├── no_polymorphism.cpp      # 无多态示例
    ├── polymorphism_example.cpp # 多态示例
    └── unique_ptr_example.cpp   # 智能指针示例
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

- [`Ex1_basic_version.cpp`](Phase1_Basic/Exercise/Ex1_basic_version.cpp) - 基础实现
- [`Ex1_optimized_version.cpp`](Phase1_Basic/Exercise/Ex1_optimized_version.cpp) - 优化版本（结构化编程）

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

- [`Ex1_string_reverse.cpp`](Phase2_PtrRefVec/Exercise/Ex1_string_reverse.cpp) - 指针操作：就地字符串反转
- [`Ex2_matrix_operations.cpp`](Phase2_PtrRefVec/Exercise/Ex2_matrix_operations.cpp) - 动态二维数组：矩阵操作（基础版本）
- [`Ex2_matrix_continous_operations.cpp`](Phase2_PtrRefVec/Exercise/Ex2_matrix_continous_operations.cpp) - 连续内存矩阵操作
- [`Ex2_matrix_flat_operations.cpp`](Phase2_PtrRefVec/Exercise/Ex2_matrix_flat_operations.cpp) - 扁平化矩阵操作
- [`Ex3_self_vertor.cpp`](Phase2_PtrRefVec/Exercise/Ex3_self_vertor.cpp) - 自定义向量类实现

### Phase 3: 面向对象编程 (Building Abstractions)

**学习重点：** 封装、继承、多态、RAII、智能指针

**核心内容：**

1. **`struct` vs. `class`** - 从数据聚合到真正的抽象
2. **封装 (Encapsulation)** - 成员变量与成员函数，`public` vs. `private`
3. **构造与析构 (Construction & Destruction)** - 对象生命周期管理与 RAII
4. **继承 (Inheritance)** - 代码复用与"is-a"关系
5. **多态 (Polymorphism)** - 虚函数与动态绑定
6. **智能指针** - 现代 C++ 的内存管理

**代码示例：**

- [`struct_class_example.cpp`](Phase3_Abstract/struct_class_example.cpp) - struct vs class 对比
- [`private_public_example.cpp`](Phase3_Abstract/private_public_example.cpp) - 访问控制演示
- [`construct_destruct_example.cpp`](Phase3_Abstract/construct_destruct_example.cpp) - 构造析构机制
- [`inheritance_example.cpp`](Phase3_Abstract/inheritance_example.cpp) - 继承关系演示
- [`no_polymorphism.cpp`](Phase3_Abstract/no_polymorphism.cpp) - 无多态的问题
- [`polymorphism_example.cpp`](Phase3_Abstract/polymorphism_example.cpp) - 多态的威力
- [`unique_ptr_example.cpp`](Phase3_Abstract/unique_ptr_example.cpp) - 智能指针使用

**实践练习：**

- [`Ex1_score.cpp`](Phase3_Abstract/Exercise/Ex1_score.cpp) - 计分板类（基础版本）
- [`Ex1_score_improved.cpp`](Phase3_Abstract/Exercise/Ex1_score_improved.cpp) - 计分板类（改进版本）
- [`Ex2_dynamicname.cpp`](Phase3_Abstract/Exercise/Ex2_dynamicname.cpp) - 动态命名形状（手动内存管理）
- [`Ex2_dynamicname_modern.cpp`](Phase3_Abstract/Exercise/Ex2_dynamicname_modern.cpp) - 动态命名形状（现代 C++）
- [`Ex3_weapon_class.cpp`](Phase3_Abstract/Exercise/Ex3_weapon_class.cpp) - 武器类系统（基础版本）
- [`Ex3_weapon_class_modern.cpp`](Phase3_Abstract/Exercise/Ex3_weapon_class_modern.cpp) - 武器类系统（现代版本）
- [`Ex4_drawtable.cpp`](Phase3_Abstract/Exercise/Ex4_drawtable.cpp) - 多态绘图板

## 🛠️ 开发环境

**C++ 标准：** C++11 或更高  
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
