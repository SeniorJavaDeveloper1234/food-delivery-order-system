#include "OrderRepository.h"

void OrderRepository::add(const Order& order) {
    Order o = order;
    o.setId(nextId++);   
    orders.push_back(o);
}

bool OrderRepository::remove(int id) {
    for (auto it = orders.begin(); it != orders.end(); ++it) {
        if (it->getId() == id) {
            orders.erase(it);
            return true;
        }
    }
    return false;
}

Order* OrderRepository::findById(int id) {
    for (auto& o : orders) {
        if (o.getId() == id) {
            return &o;
        }
    }
    return nullptr;
}

std::vector<Order> OrderRepository::findByClientId(int clientId) const {
    std::vector<Order> result;
    for (const auto& o : orders) {
        if (o.getClientId() == clientId) {
            result.push_back(o);
        }
    }
    return result;
}

std::vector<Order> OrderRepository::findByCourierId(int courierId) const {
    std::vector<Order> result;
    for (const auto& o : orders) {
        if (o.getCourierId() == courierId) {
            result.push_back(o);
        }
    }
    return result;
}

std::vector<Order> OrderRepository::getAll() const {
    return orders;
}

bool OrderRepository::updateStatus(int id, OrderStatus newStatus) {
    for (auto& o : orders) {
        if (o.getId() == id) {
            o.setStatus(newStatus);
            return true;
        }
    }
    return false;
}
