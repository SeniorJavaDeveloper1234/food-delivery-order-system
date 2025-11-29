#include "DeliverySystem.h"
#include "OrderItem.h"
#include "MenuItem.h"
#include "Courier.h"
#include <ctime>

DeliverySystem::DeliverySystem()
{
    clientRepo = std::make_unique<ClientRepository>();
    courierRepo = std::make_unique<CourierRepository>();
    menuRepo = std::make_unique<MenuRepository>();
    orderRepo = std::make_unique<OrderRepository>();
}

ClientRepository* DeliverySystem::clients() const {
    return clientRepo.get();
}

CourierRepository* DeliverySystem::couriers() const {
    return courierRepo.get();
}

MenuRepository* DeliverySystem::menu() const {
    return menuRepo.get();
}

OrderRepository* DeliverySystem::orders() const {
    return orderRepo.get();
}

Order* DeliverySystem::createOrder(int clientId, const std::vector<int>& itemIds)
{
    Courier* courier = courierRepo->findAvailableCourier();
    if (!courier)
        return nullptr;

    courier->setAvailable(false);

    std::vector<OrderItem> items;
    for (int menuId : itemIds)
    {
        MenuItem* mi = menuRepo->findById(menuId);
        if (mi) {
            items.emplace_back(
                mi->getId(),
                mi->getName(),
                mi->getPrice(),
                1
            );
        }
    }

    Order order(
        0,             
        clientId,
        items,
        getCurrentTime()
    );

    order.setCourierId(courier->getId());

    orderRepo->add(order);

    auto& list = orderRepo->findByClientId(clientId);
    if (list.empty())
        return nullptr;

    return const_cast<Order*>(&list.back());
}

bool DeliverySystem::completeOrder(int orderId)
{
    Order* order = orderRepo->findById(orderId);
    if (!order)
        return false;

    order->setStatus(OrderStatus::Completed);
    courierRepo->setCourierAvailability(order->getCourierId(), true);
    return true;
}

bool DeliverySystem::cancelOrder(int orderId)
{
    Order* order = orderRepo->findById(orderId);
    if (!order)
        return false;

    order->setStatus(OrderStatus::Cancelled);
    courierRepo->setCourierAvailability(order->getCourierId(), true);
    return true;
}

double DeliverySystem::calculateOrderTotal(const std::vector<int>& itemIds) const
{
    double total = 0.0;

    for (int menuId : itemIds) {
        MenuItem* mi = menuRepo->findById(menuId);
        if (mi)
            total += mi->getPrice();
    }

    return total;
}

std::vector<Order> DeliverySystem::getClientOrders(int clientId) const
{
    return orderRepo->findByClientId(clientId);
}

std::vector<Order> DeliverySystem::getCourierOrders(int courierId) const
{
    return orderRepo->findByCourierId(courierId);
}

std::string DeliverySystem::getCurrentTime() const
{
    std::time_t now = std::time(nullptr);
    std::tm* t = std::localtime(&now);

    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", t);
    return std::string(buf);
}
