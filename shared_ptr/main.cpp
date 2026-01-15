/*
Example: std::shared_ptr + shared ownership
-------------------------------------------
Goal:
    Demonstrate shared ownership via reference counting.

Key takeaways:
    - shared_ptr can be copied (shares ownership)
    - object is destroyed when the last shared_ptr owning it is destroyed
    - use_count() is useful for demonstrations/debugging (not business logic)

Note:
    shared_ptr is more expensive than unique_ptr and should be used only if
    ownership is truly shared.
*/

#include <iostream>
#include <memory>
#include <string>

class DatabaseConnection {
   public:
    explicit DatabaseConnection(std::string uri) : m_Uri(std::move(uri)) {
        std::cout << "[DB] connected: " << m_Uri << "\n";
    }

    ~DatabaseConnection() {
        std::cout << "[DB] disconnected: " << m_Uri << "\n";
    }

    void Query(const std::string& q) const {
        std::cout << "[DB] query: " << q << "\n";
    }

   private:
    std::string m_Uri;
};

class UserRepository {
   public:
    explicit UserRepository(std::shared_ptr<DatabaseConnection> db) : m_Db(db) {
    }

    void FindUserById(int id) const {
        m_Db->Query("SELECT * FROM users WHERE id=" + std::to_string(id));
    }

   private:
    std::shared_ptr<DatabaseConnection> m_Db;
};

class OrderRepository {
   public:
    explicit OrderRepository(std::shared_ptr<DatabaseConnection> db) : m_Db(db) {
    }

    void FindOrderById(int id) const {
        m_Db->Query("SELECT * FROM orders WHERE id=" + std::to_string(id));
    }

   private:
    std::shared_ptr<DatabaseConnection> m_Db;
};

int main() {
    auto db = std::make_shared<DatabaseConnection>("db://localhost:5432");

    std::cout << "use_count after creation: " << db.use_count() << "\n";

    UserRepository users(db);
    std::cout << "use_count after users repo: " << db.use_count() << "\n";

    {
        OrderRepository orders(db);
        std::cout << "use_count after orders repo: " << db.use_count() << "\n";

        users.FindUserById(1);
        orders.FindOrderById(42);
    }  // orders destroyed -> one shared owner removed

    std::cout << "use_count after orders repo scope ends: " << db.use_count() << "\n";

    users.FindUserById(2);

    // When main ends, db and users are destroyed -> connection is closed automatically.
    return 0;
}
