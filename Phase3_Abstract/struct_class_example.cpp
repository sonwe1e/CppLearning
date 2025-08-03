#include <iostream>
#include <cmath> // For std::sqrt

// --- 使用 struct：默认成员为 public ---
// 适用于简单的数据结构，直接访问是可以接受的。
struct PointStruct {
    // 默认情况下，这些成员是 PUBLIC（公共的）
    double x;
    double y;
};

// --- 使用 class：默认成员为 private ---
// 适用于需要维护“不变性”（规则）的类型。
class PointClass {
    // 默认情况下，这些成员是 PRIVATE（私有的）
    double x;
    double y;

public: // 从这里开始，成员是 public（公共的）
    // 用于修改私有数据的“setter”方法
    void set(double new_x, double new_y) {
        x = new_x;
        y = new_y;
    }

    // 用于读取私有数据的“getter”方法
    double getX() const { return x; }
    double getY() const { return y; }

    // 对数据执行操作的方法
    double distanceFromOrigin() const {
        // 这里的 'const' 表示此方法不会修改对象的（x 或 y）状态
        return std::sqrt(x * x + y * y);
    }
};

int main() {
    // --- Struct 用法 ---
    PointStruct p_struct;
    p_struct.x = 3.0; // OK，成员是 public（公共的），可以直接访问
    p_struct.y = 4.0;
    std::cout << "Struct 点: (" << p_struct.x << ", " << p_struct.y << ")\n";

    // --- Class 用法 ---
    PointClass p_class;
    // p_class.x = 3.0; // 编译错误！'x' 是 private（私有的）。
    p_class.set(3.0, 4.0); // 必须使用公共接口（方法）

    std::cout << "Class 点: (" << p_class.getX() << ", " << p_class.getY() << ")\n";
    std::cout << "距离原点的距离: " << p_class.distanceFromOrigin() << "\n";

    return 0;
}
