#pragma once
#include <string>

class Courier {
private:
    int id;
    std::string firstName;
    std::string lastName;
    std::string phone;
    bool available;

public:
    Courier() = default;
    Courier(int id,
        const std::string& firstName,
        const std::string& lastName,
        const std::string& phone,
        bool available = true);

    int getId() const;
    const std::string& getFirstName() const;
    const std::string& getLastName() const;
    const std::string& getPhone() const;
    bool isAvailable() const;

    void setId(int newId);
    void setFirstName(const std::string& firstName);
    void setLastName(const std::string& lastName);
    void setPhone(const std::string& phone);
    void setAvailable(bool isFree);
};
