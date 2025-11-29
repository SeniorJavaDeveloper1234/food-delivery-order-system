#include "DeliverySystem.h"
#include "OrderItem.h"
#include <vector>

DeliverySystem::DeliverySystem()
{
    clientRepo = std::make_unique<ClientRepository>();
    courierRepo = std::make_unique<CourierRepository>();
    menuRepo = std::make_unique<MenuRepository>();
    orderRepo = std::make_unique<OrderRepository>();
}

ClientRepository* DeliverySystem::clients() {
    return clientRepo.get();
}

CourierRepository* DeliverySystem::couriers() {
    return courierRepo.get();
}

MenuRepository* DeliverySystem::menu() {
    return menuRepo.get();
}

OrderRepository* DeliverySystem::orders() {
    return orderRepo.get();
}


Order* DeliverySystem::createOrder(int clientId, const std::vector<int>& itemIds)
{

    Courier* courier = courierRepo->findAvailableCourier();
    if (!courier)
        return nullptr;

    courier->setAvailable(false);

    std::vector<OrderItem> items;
    for (int id : itemIds) {
        MenuItem* mi = menuRepo->findById(id);
        if (mi) {
            OrderItem oi(mi->getId(), 1, mi->getPrice());
            items.push_back(oi);
        }
    }

    Order order(
        0,
        clientId,
        courier->getId(),
        items,
        OrderStatus::Pending,
        getCurrentTime()
    );

    orderRepo->add(order);

    return &orderRepo->findByClientId(clientId).back();
}


bool DeliverySystem::completeOrder(int orderId)
{
    Order* order = orderRepo->findById(orderId);
    if (!order) return false;

    order->setStatus(OrderStatus::Completed);
    courierRepo->setCourierAvailability(order->getCourierId(), true);

    return true;
}


bool DeliverySystem::cancelOrder(int orderId)
{
    Order* order = orderRepo->findById(orderId);
    if (!order) return false;

    order->setStatus(OrderStatus::Cancelled);
    courierRepo->setCourierAvailability(order->getCourierId(), true);

    return true;
}


double DeliverySystem::calculateOrderTotal(const std::vector<int>& itemIds)
{
    double total = 0;
    for (int id : itemIds) {
        MenuItem* mi = menuRepo->findById(id);
        if (mi)
            total += mi->getPrice();
    }
    return total;
}


std::vector<Order> DeliverySystem::getClientOrders(int clientId)
{
    return orderRepo->findByClientId(clientId);
}

std::vector<Order> DeliverySystem::getCourierOrders(int courierId)
{
    return orderRepo->findByCourierId(courierId);
}

std::string DeliverySystem::getCurrentTime() const
{
    using namespace std::chrono;


    auto now = system_clock::now();
    std::time_t now_time = system_clock::to_time_t(now);

    std::tm* local = std::localtime(&now_time);

    std::ostringstream oss;
    oss << std::put_time(local, "%Y-%m-%d %H:%M:%S");

    return oss.str();
}

void DeliverySystem::loadAll()
{
    JsonStorage::loadClients(*clientRepo, "data/clients.json");
    JsonStorage::loadCouriers(*courierRepo, "data/couriers.json");
    JsonStorage::loadMenu(*menuRepo, "data/menu.json");
    JsonStorage::loadOrders(*orderRepo, "data/orders.json");
}

void DeliverySystem::saveAll() const
{
    JsonStorage::saveClients(*clientRepo, "data/clients.json");
    JsonStorage::saveCouriers(*courierRepo, "data/couriers.json");
    JsonStorage::saveMenu(*menuRepo, "data/menu.json");
    JsonStorage::saveOrders(*orderRepo, "data/orders.json");
}
