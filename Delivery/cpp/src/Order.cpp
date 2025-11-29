#include "Order.h"

Order::Order(int id,
    int clientId,
    int courierId,
    const std::vector<OrderItem>& items,
    OrderStatus status,
    const std::string& createdAt)
    : id(id),
    clientId(clientId),
    courierId(courierId),
    items(items),
    status(status),
    createdAt(createdAt)
{
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

OrderStatus Order::getStatus() const {
    return status;
}

const std::vector<OrderItem>& Order::getItems() const {
    return items;
}

const std::string& Order::getCreatedAt() const {
    return createdAt;
}

void Order::setStatus(OrderStatus newStatus) {
    status = newStatus;
}

void Order::setCourierId(int id) {
    courierId = id;
}

void Order::addItem(const OrderItem& item) {
    items.push_back(item);
}

double Order::getTotal() const {
    double total = 0.0;
    for (const auto& item : items) {
        total += item.getTotal();
    }
    return total;
}
