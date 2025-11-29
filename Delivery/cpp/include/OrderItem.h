#pragma once
#include <string>

class OrderItem {
private:
    int menuItemId;        
    std::string name;       
    double unitPrice;       
    int quantity;          

public:
    OrderItem() = default;

    OrderItem(int menuItemId,
        const std::string& name,
        double unitPrice,
        int quantity);

    int getMenuItemId() const;
    const std::string& getName() const;
    double getUnitPrice() const;
    int getQuantity() const;
    double getTotalPrice() const;

    void setQuantity(int quantity);
};
