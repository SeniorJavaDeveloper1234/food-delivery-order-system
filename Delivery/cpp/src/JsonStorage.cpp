#include "JsonStorage.h"
#include <fstream>

void JsonStorage::loadClients(ClientRepository& repo, const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) return;

    json j;
    file >> j;

    for (auto& c : j)
    {
        Client client(
            c["id"],
            c["firstName"],
            c["lastName"],
            c["phone"],
            c["address"]
        );
        repo.add(client);
    }
}

void JsonStorage::loadCouriers(CourierRepository& repo, const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) return;

    json j;
    file >> j;

    for (auto& c : j)
    {
        Courier courier(
            c["id"],
            c["firstName"],
            c["lastName"],
            c["phone"],
            c["available"]
        );
        repo.add(courier);
    }
}

void JsonStorage::loadMenu(MenuRepository& repo, const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) return;

    json j;
    file >> j;

    for (auto& m : j)
    {
        MenuItem item(
            m["id"],
            m["name"],
            m["description"],
            m["price"]
        );
        repo.add(item);
    }
}

void JsonStorage::loadOrders(OrderRepository& repo, const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) return;

    json j;
    file >> j;

    for (auto& o : j)
    {
        std::vector<OrderItem> items;

        for (auto& it : o["items"])
        {
            items.emplace_back(
                it["menuItemId"],
                it["name"],
                it["unitPrice"],
                it["quantity"]
            );
        }

        Order order(
            o["id"],
            o["clientId"],
            items,
            o["createdAt"]
        );

        order.setCourierId(o["courierId"]);
        order.setStatus(static_cast<OrderStatus>(o["status"]));

        repo.add(order);
    }
}

void JsonStorage::saveClients(const ClientRepository& repo, const std::string& filename)
{
    json j = json::array();

    for (const auto& c : repo.getAll())
    {
        j.push_back({
            {"id", c.getId()},
            {"firstName", c.getFirstName()},
            {"lastName", c.getLastName()},
            {"phone", c.getPhone()},
            {"address", c.getAddress()}
            });
    }

    std::ofstream file(filename);
    file << j.dump(4);
}

void JsonStorage::saveCouriers(const CourierRepository& repo, const std::string& filename)
{
    json j = json::array();

    for (const auto& c : repo.getAll())
    {
        j.push_back({
            {"id", c.getId()},
            {"firstName", c.getFirstName()},
            {"lastName", c.getLastName()},
            {"phone", c.getPhone()},
            {"available", c.isAvailable()}
            });
    }

    std::ofstream file(filename);
    file << j.dump(4);
}


void JsonStorage::saveMenu(const MenuRepository& repo, const std::string& filename)
{
    json j = json::array();

    for (const auto& m : repo.getAll())
    {
        j.push_back({
            {"id", m.getId()},
            {"name", m.getName()},
            {"description", m.getDescription()},
            {"price", m.getPrice()}
            });
    }

    std::ofstream file(filename);
    file << j.dump(4);
}


void JsonStorage::saveOrders(const OrderRepository& repo, const std::string& filename)
{
    json j = json::array();

    for (const auto& o : repo.getAll())
    {
        json items = json::array();

        for (const auto& it : o.getItems())
        {
            items.push_back({
                {"menuItemId", it.getMenuItemId()},
                {"name", it.getName()},
                {"unitPrice", it.getUnitPrice()},
                {"quantity", it.getQuantity()},
                {"totalPrice", it.getTotalPrice()}
                });
        }

        j.push_back({
            {"id", o.getId()},
            {"clientId", o.getClientId()},
            {"courierId", o.getCourierId()},
            {"status", (int)o.getStatus()},
            {"createdAt", o.getCreatedAt()},
            {"totalPrice", o.getTotalPrice()},
            {"items", items}
            });
    }

    std::ofstream file(filename);
    file << j.dump(4);
}
