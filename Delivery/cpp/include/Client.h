#pragma once
#include <string>

class Client {
private:
    int id;
    std::string firstName;
    std::string lastName;
    std::string phone;
    std::string address;

public:
    Client() = default;
    Client(int id,
        const std::string& firstName,
        const std::string& lastName,
        const std::string& phone,
        const std::string& address);

    int getId() const;
    const std::string& getFirstName() const;
    const std::string& getLastName() const;
    const std::string& getPhone() const;
    const std::string& getAddress() const;

    void setFirstName(const std::string& firstName);
    void setLastName(const std::string& lastName);
    void setPhone(const std::string& phone);
    void setAddress(const std::string& address);
};
