/* 
### 练习 4: 多态的绘图板 (难度: ★★★★☆)

**目标**: 使用多态来管理一个可以绘制不同形状的系统。

**涉及知识点**: 多态, `virtual` 函数, 纯虚函数, 抽象基类, `override`, `std::vector` 与基类指针。

**任务要求**:

1. 设计一个**抽象基类** `Shape`：
    - 它有一个**纯虚函数** `virtual void draw() const = 0;`。
    - 它应该有一个**虚析构函数** `virtual ~Shape() {}` (思考为什么这很重要)。
2. 设计三个派生类 `Circle`, `Rectangle`, `Triangle`，它们都继承自 `Shape`。
    - 每个类都有自己的构造函数来接收必要的尺寸信息（如半径、长宽等）。
    - 每个类都必须 `override` `draw()` 函数，在其中打印出描述自己如何被绘制的文本，例如 `std::cout << "Drawing a Circle with radius 5.\\n";`。
3. 在 `main` 函数中:
    - 创建一个 `std::vector<Shape*>` 容器。
    - 在堆上 `new` 出几个不同类型的形状（`Circle`, `Rectangle`等）对象，并将它们的指针存入 `vector`。
    - 编写一个循环，遍历这个 `vector`，并对每个 `Shape*` 指针调用 `draw()` 函数。观察多态是如何工作的——同一行代码 `shape_ptr->draw();` 能够调用出不同子类的实现。
    - 在程序结束前，**必须**遍历 `vector` 并 `delete` 掉所有你 `new` 出来的对象，以避免内存泄漏。
*/

#include <iostream>
#include <vector>

class Shape
{
    public:
        virtual void draw() const = 0;
        virtual ~Shape() {}
};

class Circle: public Shape
{
    private:
        int radius_ {};
    
    public:
        Circle(int radius): radius_(radius) {}
        void draw() const override
        {
            std::cout << "Drawing a Circle with radius " << radius_ << ".\n";
        }
};

class Rectangle: public Shape
{
    private:
        int length_ {};
        int width_ {};
    
    public:
        Rectangle(int length, int width): length_(length), width_(width) {}
        void draw() const override
        {
            std::cout << "Drawing a Rectangle with length " << length_ << " and width " << width_ <<  ".\n";
        }
};


class Triangle: public Shape
{
    private:
        int base_ {};
        int height_ {};
    
    public:
        Triangle(int base, int height): base_(base), height_(height) {}
        void draw() const override
        {
            std::cout << "Drawing a Triangle with base " << base_ << " and height " << height_ <<  ".\n";
        }
};

int main()
{
    std::vector<Shape*> shapeVector {};
    shapeVector.push_back(new Circle(5));
    shapeVector.push_back(new Rectangle(2, 2));
    shapeVector.push_back(new Triangle(3, 2));

    for (auto& vec: shapeVector)
    {
        vec->draw();
        delete vec;
    }
}
