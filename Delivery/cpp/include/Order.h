#pragma once
#include <vector>
#include <string>
#include "OrderItem.h"

enum class OrderStatus {
    Pending,        
    Preparing,      
    Delivering,     
    Completed,      
    Cancelled       
};

class Order {
private:
    int id;                                 
    int clientId;                           
    int courierId;                          
    std::vector<OrderItem> items;           
    OrderStatus status;                     
    std::string createdAt;                  
    double totalPrice;                     

public:
    Order() = default;

    Order(int id,
        int clientId,
        const std::vector<OrderItem>& items,
        const std::string& createdAt);

    int getId() const;
    int getClientId() const;
    int getCourierId() const;
    const std::vector<OrderItem>& getItems() const;
    OrderStatus getStatus() const;
    const std::string& getCreatedAt() const;
    double getTotalPrice() const;

    void setId(int newId);
    void setCourierId(int courierId);
    void setStatus(OrderStatus status);

    void calculateTotalPrice();
};
