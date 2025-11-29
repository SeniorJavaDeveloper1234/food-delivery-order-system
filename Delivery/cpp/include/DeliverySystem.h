#pragma once
#include <memory>
#include "ClientRepository.h"
#include "CourierRepository.h"
#include "MenuRepository.h"
#include "OrderRepository.h"

class DeliverySystem {
private:
    std::unique_ptr<ClientRepository> clientRepo;
    std::unique_ptr<CourierRepository> courierRepo;
    std::unique_ptr<MenuRepository> menuRepo;
    std::unique_ptr<OrderRepository> orderRepo;

public:
    DeliverySystem();

    ClientRepository* clients();
    CourierRepository* couriers();
    MenuRepository* menu();
    OrderRepository* orders();


    Order* createOrder(int clientId, const std::vector<int>& itemIds);

    bool completeOrder(int orderId);

    bool cancelOrder(int orderId);

    double calculateOrderTotal(const std::vector<int>& itemIds);

    std::vector<Order> getClientOrders(int clientId);


    std::vector<Order> getCourierOrders(int courierId);

    std::string getCurrentTime() const;
};
