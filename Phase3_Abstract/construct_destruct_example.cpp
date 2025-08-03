#include <iostream>
#include <string>

class Account {
private:
    std::string owner_name_; // 账户名
    double balance_; // 余额

public:
    // --- 1. 构造函数 ---
    // 在对象创建时接收参数来初始化对象。
    Account(const std::string& name, double initial_balance) {
        std::cout << "调用了 " << name << " 的构造函数。\n";
        owner_name_ = name;
        if (initial_balance >= 0) {
            balance_ = initial_balance;
        } else {
            balance_ = 0;
            std::cout << "[警告] 初始余额不能为负数。已设置为 0。\n";
		
        }}
        
    // --- 现代 C++：成员初始化列表 ---
    // 这是初始化成员的首选方式。
    // 它的优点包括：
    // 1. 效率：直接初始化成员，避免了先默认初始化再赋值的开销。
    // 2. 强制性：对于const成员和引用成员，必须使用初始化列表进行初始化。
    // 3. 清晰性：一眼就能看出成员是如何初始化的，提高了代码的可读性。

    // Account(const std::string& name, double initial_balance)
    //     : owner_name_(name), // 初始化 owner_name_ 成员变量，将其设置为传入的 name 参数。
    //       balance_(initial_balance >= 0 ? initial_balance : 0) // 初始化 balance_ 成员变量：
    //                                                          // 使用三元运算符检查 initial_balance。
    //                                                          // 如果 initial_balance 大于或等于 0，则直接使用该值。
    //                                                          // 否则，将其设置为 0。
    // {
    //     // 构造函数体内的代码会在所有成员初始化完成后执行。

    //     std::cout << "调用了 " << name << " 的构造函数。\n"; // 输出一条消息，表示构造函数被调用。

    //     // 检查初始余额是否为负数，如果为负，打印警告信息。
    //     // 注意：虽然这里有警告，但由于初始化列表已经处理了负数情况，
    //     // 这里的 balance_ 成员变量在执行到这里时一定是非负的。
    //     if (initial_balance < 0) {
    //         std::cout << "[警告] 初始余额不能为负数。已设置为 0。\n";
    //     }
    // }

    // --- 2. 析构函数 ---
    // 在对象被销毁时进行清理。
    ~Account() {
        std::cout << "调用了 " << owner_name_
                  << "（最终余额为 " << balance_ << "）的析构函数。\n";
        // 对于这个简单的类，没有需要释放的资源，
        // 但析构函数仍然会被调用。
    }

    // ... 其他方法，如 deposit, withdraw, getBalance ...
    void deposit(double amount) { if(amount > 0) balance_ += amount; }
    double getBalance() const { return balance_; }
};

int main() {
    std::cout << "--- 进入 main 作用域 ---\n";
    { // 创建一个新的内部作用域
        std::cout << "  --- 进入内部作用域 ---\n";
        // `my_account` 对象在此处被创建。构造函数会自动调用。
        Account my_account("Saining Xie", 2000.0);
        std::cout << "  账户已创建。当前余额: " << my_account.getBalance() << "\n";
        my_account.deposit(500);

        // `my_account` 即将超出作用域。
        std::cout << "  --- 退出内部作用域 ---\n";
    } // `my_account` 在此处被销毁。析构函数会自动调用。

    std::cout << "--- 返回 main 作用域 ---\n";
    return 0;
}
