#include <iostream>
#include <memory> // 包含 <memory> 头文件以使用智能指针
#include <string>

// 一个简单的游戏对象，方便我们追踪其生命周期
struct GameObject {
    std::string name;
    GameObject(const std::string& n) : name(n) {
        std::cout << "  [+] GameObject '" << name << "' has been created.\n";
    }
    ~GameObject() {
        std::cout << "  [-] GameObject '" << name << "' has been destroyed.\n";
    }
    void update() {
        std::cout << "  [*] GameObject '" << name << "' is updating.\n";
    }
};

// 场景1：一个函数需要完全接管一个 GameObject 的所有权
void takeOwnership(std::unique_ptr<GameObject> obj) {
    std::cout << "\n--- Function takeOwnership received ownership ---\n";
    if (obj) {
        obj->update();
    }
    std::cout << "--- Function takeOwnership is about to end. The object will be destroyed now. ---\n";
} // obj 在这里离开作用域，其析构函数被调用，销毁它拥有的 GameObject

// 场景2：一个函数需要修改 unique_ptr 本身 (例如，重新分配)
// 注意参数是引用 &
void reassignPointer(std::unique_ptr<GameObject>& ptr_ref) {
    std::cout << "\n--- Function reassignPointer received a reference ---\n";
    if (ptr_ref) {
        std::cout << "  Original object '" << ptr_ref->name << "' will be destroyed due to reassignment.\n";
    }
    // 让外部的 unique_ptr 指向一个新对象
    ptr_ref = std::make_unique<GameObject>("New Player");
    std::cout << "--- Function reassignPointer has reassigned the pointer. ---\n";
}

int main() {
    std::cout << "--- Starting main ---\n";

    // =========================================================================
    // 对比 1: std::make_unique vs 'new'
    // =========================================================================
    std::cout << "\n[Test 1: Initialization]\n";
    
    // 现代、安全、推荐的方式
    auto player = std::make_unique<GameObject>("Player");

    // 不推荐的旧方式 (为了对比，这里不实际运行，只展示语法)
    // std::unique_ptr<GameObject> enemy(new GameObject("Enemy")); 
    // 上述方式有潜在的异常安全问题，且更冗长。

    // =========================================================================
    // 对比 2: std::move(data) 的使用
    // =========================================================================
    std::cout << "\n[Test 2: Using std::move to transfer ownership]\n";
    std::cout << "Before move, 'player' pointer is " << (player ? "valid" : "null") << ".\n";
    
    // 【有 std::move】
    // 我们必须使用 std::move 来转移所有权给 takeOwnership 函数
    takeOwnership(std::move(player));
    
    // 【无 std::move】
    // 下面的代码将无法编译，因为 unique_ptr 禁止拷贝
    // takeOwnership(player); // COMPILE ERROR: Call to implicitly-deleted copy constructor

    std::cout << "\nAfter move, 'player' pointer is " << (player ? "valid" : "null") << ".\n";
    // 检查：player 已经被置为 nullptr，无法再使用
    if (!player) {
        std::cout << "As expected, 'player' is now a nullptr.\n";
    }

    // =========================================================================
    // 对比 3: &data (通过引用传递) 的使用
    // =========================================================================
    std::cout << "\n[Test 3: Using a reference (&) to modify the pointer]\n";
    auto npc = std::make_unique<GameObject>("Old NPC");
    std::cout << "Before calling reassignPointer, 'npc' points to '" << npc->name << "'.\n";

    // 【有 &】
    // 我们传递引用，让函数可以修改 npc 本身
    reassignPointer(npc); 
    // 注意：这里没有用 &npc，因为函数参数类型已经是引用了。
    // &npc 的结果是 std::unique_ptr<GameObject>*，类型不匹配。

    std::cout << "\nAfter calling reassignPointer, 'npc' points to '" << npc->name << "'.\n";
    npc->update();

    std::cout << "\n--- main function is about to end. All remaining objects will be destroyed. ---\n";
    return 0;
} // 'npc' 在这里离开作用域，其拥有的 "New Player" 对象被销毁
