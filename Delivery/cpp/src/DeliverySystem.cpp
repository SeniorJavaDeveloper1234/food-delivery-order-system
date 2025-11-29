#include "DeliverySystem.h"

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


Client* DeliverySystem::registerClient(const std::string& firstName,
    const std::string& lastName,
    const std::string& phone)
{
    Client c(0, firstName, lastName, phone); 
    clientRepo->add(c);
    return clientRepo->findByPhone(phone);
}

MenuItem* DeliverySystem::addMenuItem(const std::string& name,
    const std::string& description,
    double price)
{
    MenuItem item(0, name, description, price);
    menuRepo->add(item);
    return menuRepo->findByName(name);
}

Order* DeliverySystem::createOrder(int clientId,
    const std::vector<OrderItem>& items)
{
    Courier* courier = courierRepo->findAvailableCourier();
    if (!courier)
        return nullptr; 

    courier->setAvailable(false);

    Order order(0, clientId, courier->getId(), items,
        OrderStatus::Pending, getCurrentTime());

    orderRepo->add(order);

    return orderRepo->findByClientId(clientId).back();
}

bool DeliverySystem::updateOrderStatus(int orderId, OrderStatus status) {
    return orderRepo->updateStatus(orderId, status);
}

void DeliverySystem::freeCourier(int courierId) {
    courierRepo->setCourierAvailability(courierId, true);
}

std::string DeliverySystem::getCurrentTime() const
{
    return "2025-01-01 12:00";
}
