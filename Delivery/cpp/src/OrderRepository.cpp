#include "OrderRepository.h"

void OrderRepository::add(const Order& order)
{
    Order temp = order;
    temp.setId(nextId++);
    orders.push_back(temp);
}

bool OrderRepository::remove(int id)
{
    for (auto it = orders.begin(); it != orders.end(); ++it)
    {
        if (it->getId() == id) {
            orders.erase(it);
            return true;
        }
    }
    return false;
}

Order* OrderRepository::findById(int id)
{
    for (auto& o : orders) {
        if (o.getId() == id)
            return &o;
    }
    return nullptr;
}

std::vector<Order> OrderRepository::getAll() const
{
    return orders;
}

bool OrderRepository::updateStatus(int id, OrderStatus newStatus)
{
    Order* o = findById(id);
    if (!o) return false;

    o->setStatus(newStatus);
    return true;
}

const std::vector<Order>& OrderRepository::findByClientId(int clientId) const
{
    tempClientResults.clear();
    for (const auto& o : orders)
        if (o.getClientId() == clientId)
            tempClientResults.push_back(o);

    return tempClientResults;
}

const std::vector<Order>& OrderRepository::findByCourierId(int courierId) const
{
    tempCourierResults.clear();
    for (const auto& o : orders)
        if (o.getCourierId() == courierId)
            tempCourierResults.push_back(o);

    return tempCourierResults;
}
