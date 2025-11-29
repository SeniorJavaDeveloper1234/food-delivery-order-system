#pragma once
#include <string>

class MenuItem {
private:
    int id;                  
    std::string name;           
    std::string description;  
    double price;             

public:
    MenuItem() = default;
    MenuItem(int id,
        const std::string& name,
        const std::string& description,
        double price);

    int getId() const;
    const std::string& getName() const;
    const std::string& getDescription() const;
    double getPrice() const;

    void setId(int newId);
    void setName(const std::string& name);
    void setDescription(const std::string& desc);
    void setPrice(double price);
};
