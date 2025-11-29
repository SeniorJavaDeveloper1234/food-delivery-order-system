#include "Order.h"
#include <numeric> 

Order::Order(int id,
    int clientId,
    const std::vector<OrderItem>& items,
    const std::string& createdAt)
    : id(id),
    clientId(clientId),
    courierId(-1),       
    items(items),
    status(OrderStatus::Pending),
    createdAt(createdAt),
    totalPrice(0.0)
{
    calculateTotalPrice();
}

int Order::getId() const {
    return id;
}

int Order::getClientId() const {
    return clientId;
}

int Order::getCourierId() const {
    return courierId;
}

const std::vector<OrderItem>& Order::getItems() const {
    return items;
}

OrderStatus Order::getStatus() const {
    return status;
}

const std::string& Order::getCreatedAt() const {
    return createdAt;
}

double Order::getTotalPrice() const {
    return totalPrice;
}

void Order::setId(int newId) {
    id = newId;
}

void Order::setCourierId(int courierId) {
    this->courierId = courierId;
}

void Order::setStatus(OrderStatus status) {
    this->status = status;
}

void Order::calculateTotalPrice() {
    totalPrice = 0.0;
    for (const auto& item : items) {
        totalPrice += item.getTotalPrice();
    }
}
