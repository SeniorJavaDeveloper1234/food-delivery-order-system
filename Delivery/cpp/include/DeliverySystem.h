#pragma once
#include <memory>
#include <vector>
#include <string>

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


    std::string getCurrentTime() const;

public:
    DeliverySystem();

    ClientRepository* clients() const;
    CourierRepository* couriers() const;
    MenuRepository* menu() const;
    OrderRepository* orders() const;

    Order* createOrder(int clientId, const std::vector<int>& itemIds);

    bool completeOrder(int orderId);
    bool cancelOrder(int orderId);

    double calculateOrderTotal(const std::vector<int>& itemIds) const;

    std::vector<Order> getClientOrders(int clientId) const;
    std::vector<Order> getCourierOrders(int courierId) const;
};
