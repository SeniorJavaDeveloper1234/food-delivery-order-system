#include "DeliverySystem.h"
#include "JsonStorage.h"
#include "OrderItem.h"
#include "MenuItem.h"
#include "Courier.h"

#include <ctime>

DeliverySystem::DeliverySystem() {
    clientRepo = std::make_unique<ClientRepository>();
    courierRepo = std::make_unique<CourierRepository>();
    menuRepo = std::make_unique<MenuRepository>();
    orderRepo = std::make_unique<OrderRepository>();

    loadAll();
}

void DeliverySystem::loadAll() {
    JsonStorage::loadClients(*clientRepo, "data/clients.json");
    clientRepo->updateNextId();

    JsonStorage::loadCouriers(*courierRepo, "data/couriers.json");
    courierRepo->updateNextId();

    JsonStorage::loadMenu(*menuRepo, "data/menu.json");
    menuRepo->updateNextId();

    JsonStorage::loadOrders(*orderRepo, "data/orders.json");
    orderRepo->updateNextId();
}

void DeliverySystem::saveClients() const {
    JsonStorage::saveClients(*clientRepo, "data/clients.json");
}

void DeliverySystem::saveCouriers() const {
    JsonStorage::saveCouriers(*courierRepo, "data/couriers.json");
}

void DeliverySystem::saveMenu() const {
    JsonStorage::saveMenu(*menuRepo, "data/menu.json");
}

void DeliverySystem::saveOrders() const {
    JsonStorage::saveOrders(*orderRepo, "data/orders.json");
}

void DeliverySystem::saveAll() const {
    saveClients();
    saveCouriers();
    saveMenu();
    saveOrders();
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



bool DeliverySystem::addClient(const Client& c) {
    clientRepo->add(c);
    saveClients();
    return true;
}

bool DeliverySystem::updateClient(int id,
    const std::string& first,
    const std::string& last,
    const std::string& phone,
    const std::string& address)
{
    Client* c = clientRepo->findById(id);
    if (!c)
        return false;

    c->setFirstName(first);
    c->setLastName(last);
    c->setPhone(phone);
    c->setAddress(address);

    saveClients();   
    return true;
}


bool DeliverySystem::removeClient(int id) {
    bool ok = clientRepo->remove(id);
    if (ok) saveClients();
    return ok;
}




bool DeliverySystem::addCourier(const Courier& c) {
    courierRepo->add(c);
    saveCouriers();
    return true;
}

bool DeliverySystem::updateCourier(int id,
    const std::string& first,
    const std::string& last,
    const std::string& phone,
    bool available)
{
    Courier* c = courierRepo->findById(id);
    if (!c)
        return false;

    c->setFirstName(first);
    c->setLastName(last);
    c->setPhone(phone);
    c->setAvailable(available);

    saveCouriers();   
    return true;
}


bool DeliverySystem::removeCourier(int id) {
    bool ok = courierRepo->remove(id);
    if (ok) saveCouriers();
    return ok;
}



bool DeliverySystem::addMenuItem(const MenuItem& m) {
    menuRepo->add(m);
    saveMenu();
    return true;
}

bool DeliverySystem::updateMenuItem(int id,
    const std::string& name,
    const std::string& desc,
    double price)
{
    MenuItem* m = menuRepo->findById(id);
    if (!m)
        return false;

    m->setName(name);
    m->setDescription(desc);
    m->setPrice(price);

    saveMenu();   
    return true;
}


bool DeliverySystem::removeMenuItem(int id) {
    bool ok = menuRepo->remove(id);
    if (ok) saveMenu();
    return ok;
}

std::vector<MenuItem> DeliverySystem::searchMenu(const std::string& part) const {
    return menuRepo->searchByName(part);
}


Order* DeliverySystem::createOrder(int clientId, const std::vector<int>& itemIds) {
    Courier* courier = courierRepo->findAvailableCourier();
    if (!courier)
        return nullptr;

    courier->setAvailable(false);

    std::vector<OrderItem> items;
    for (int menuId : itemIds) {
        MenuItem* mi = menuRepo->findById(menuId);
        if (mi) {
            items.emplace_back(mi->getId(), mi->getName(), mi->getPrice(), 1);
        }
    }

    Order order(0, clientId, items, getCurrentTime());
    order.setCourierId(courier->getId());

    orderRepo->add(order);

    saveCouriers();
    saveOrders();

    auto& list = orderRepo->findByClientId(clientId);
    return list.empty() ? nullptr : const_cast<Order*>(&list.back());
}

Order* DeliverySystem::createOrder(int clientId, const std::vector<OrderItem>& items) {
    Courier* courier = courierRepo->findAvailableCourier();
    if (!courier)
        return nullptr;

    courier->setAvailable(false);

    Order order(0, clientId, items, getCurrentTime());
    order.setCourierId(courier->getId());

    orderRepo->add(order);

    saveCouriers();
    saveOrders();

    auto& list = orderRepo->findByClientId(clientId);
    return list.empty() ? nullptr : const_cast<Order*>(&list.back());
}

bool DeliverySystem::completeOrder(int orderId) {
    Order* order = orderRepo->findById(orderId);
    if (!order) return false;

    order->setStatus(OrderStatus::Completed);
    courierRepo->setCourierAvailability(order->getCourierId(), true);

    saveCouriers();
    saveOrders();
    return true;
}

bool DeliverySystem::cancelOrder(int orderId) {
    Order* order = orderRepo->findById(orderId);
    if (!order) return false;

    order->setStatus(OrderStatus::Cancelled);
    courierRepo->setCourierAvailability(order->getCourierId(), true);

    saveCouriers();
    saveOrders();
    return true;
}


double DeliverySystem::calculateOrderTotal(const std::vector<int>& itemIds) const {
    double total = 0.0;

    for (int menuId : itemIds) {
        MenuItem* mi = menuRepo->findById(menuId);
        if (mi)
            total += mi->getPrice();
    }

    return total;
}

std::vector<Order> DeliverySystem::getClientOrders(int clientId) const {
    return orderRepo->findByClientId(clientId);
}

std::vector<Order> DeliverySystem::getCourierOrders(int courierId) const {
    return orderRepo->findByCourierId(courierId);
}



std::string DeliverySystem::getCurrentTime() const {
    std::time_t now = std::time(nullptr);
    std::tm* t = std::localtime(&now);

    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", t);
    return std::string(buf);
}
