#pragma once
#include <vector>
#include "Order.h"
#include "IRepository.h"

class OrderRepository : public IRepository<Order> {
private:
    std::vector<Order> orders;
    int nextId = 1;

public:
    OrderRepository() = default;

    void add(const Order& order) override;

    bool remove(int id) override;

    Order* findById(int id) override;
    std::vector<Order> getAll() const override;

    bool updateStatus(int id, OrderStatus newStatus);

    std::vector<Order> findByClientId(int clientId) const;

    std::vector<Order> findByCourierId(int courierId) const;
};
