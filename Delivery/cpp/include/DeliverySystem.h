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

    void loadAll();
 

    void saveClients() const;
    void saveCouriers() const;
    void saveMenu() const;
    void saveOrders() const;

    std::string getCurrentTime() const;

public:

    void saveAll() const;
    DeliverySystem();

    ClientRepository* clients() const;
    CourierRepository* couriers() const;
    MenuRepository* menu() const;
    OrderRepository* orders() const;

    bool addClient(const Client& c);
    bool removeClient(int id);

    bool addCourier(const Courier& c);
    bool removeCourier(int id);

    bool addMenuItem(const MenuItem& m);
    bool removeMenuItem(int id);

    Order* createOrder(int clientId, const std::vector<int>& itemIds);
    Order* createOrder(int clientId, const std::vector<OrderItem>& items);

    bool completeOrder(int orderId);
    bool cancelOrder(int orderId);

    double calculateOrderTotal(const std::vector<int>& itemIds) const;

    std::vector<Order> getClientOrders(int clientId) const;
    std::vector<Order> getCourierOrders(int courierId) const;
};
