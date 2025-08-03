#include <iostream>


class Account {
private:
    // --- Private Members (Implementation Details) ---
    // 这些是类的内部状态，外界不应直接访问。
    std::string owner_name_; // C++ 社区习惯用下划线后缀表示私有成员
    double balance_;

    // 一个私有辅助函数，只在类内部使用
    void logTransaction(const std::string& message) const {
        std::cout << "[LOG] " << owner_name_ << ": " << message << "\n";
    }

public:
    // --- Public Members (The Interface) ---
    // 这是类的“操作面板”，供外界使用。

    // 公开的 "setter" 方法，但带有逻辑控制
    void deposit(double amount) {
        if (amount > 0) {
            balance_ += amount;
            logTransaction("Deposited " + std::to_string(amount));
        } else {
            std::cout << "[ERROR] Deposit amount must be positive.\n";
        }
    }

    // 另一个 "setter"，同样带有业务规则
    bool withdraw(double amount) {
        if (amount <= 0) {
            std::cout << "[ERROR] Withdrawal amount must be positive.\n";
            return false;
        }
        if (balance_ >= amount) {
            balance_ -= amount;
            logTransaction("Withdrew " + std::to_string(amount));
            return true;
        } else {
            logTransaction("Withdrawal failed. Insufficient funds.");
            return false;
        }
    }

    // 公开的 "getter" 方法
    double getBalance() const {
        return balance_;
    }

    // 初始设置，注意这里我们还没有学构造函数，所以用一个普通函数代替
    void setup(const std::string& name, double initial_balance) {
        owner_name_ = name;
        balance_ = initial_balance;
    }
};

int main() {
    Account my_account;
    my_account.setup("Kaiming He", 1000.0);

    // my_account.balance_ = 1000000.0; // COMPILE ERROR! balance_ is private.
    // 不能直接修改余额，必须通过公共接口。

    std::cout << "Initial Balance: " << my_account.getBalance() << "\n";

    my_account.deposit(500.0);
    my_account.withdraw(2000.0); // This will fail
    my_account.withdraw(200.0);  // This will succeed

    std::cout << "Final Balance: " << my_account.getBalance() << "\n";
}
