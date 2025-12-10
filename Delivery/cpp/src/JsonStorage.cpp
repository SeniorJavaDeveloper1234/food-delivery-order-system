#include "JsonStorage.h"
#include <fstream>
#include <filesystem>

json JsonStorage::safeLoad(const std::string& filename)
{
    std::filesystem::create_directories(std::filesystem::path(filename).parent_path());

    if (!std::filesystem::exists(filename))
    {
        std::ofstream f(filename);
        f << "[]";
        return json::array();
    }

    std::ifstream file(filename);
    if (!file.is_open())
    {
        return json::array();
    }

    try
    {
        json j;
        file >> j;

        if (!j.is_array())
            return json::array();

        return j;
    }
    catch (...)
    {
        std::ofstream f(filename, std::ios::trunc);
        f << "[]";
        return json::array();
    }
}

void JsonStorage::safeSave(const json& j, const std::string& filename)
{
    std::filesystem::create_directories(std::filesystem::path(filename).parent_path());

    std::ofstream file(filename, std::ios::trunc);
    file << j.dump(4);
}



void JsonStorage::loadClients(ClientRepository& repo, const std::string& filename)
{
    json j = safeLoad(filename);

    for (auto& c : j)
    {
        repo.addLoaded(Client(
            c["id"],
            c["firstName"],
            c["lastName"],
            c["phone"],
            c["address"]
        ));
    }

    repo.updateNextId();
}

void JsonStorage::loadCouriers(CourierRepository& repo, const std::string& filename)
{
    json j = safeLoad(filename);

    for (auto& c : j)
    {
        repo.addLoaded(Courier(
            c["id"],
            c["firstName"],
            c["lastName"],
            c["phone"],
            c["available"]
        ));
    }

    repo.updateNextId();
}

void JsonStorage::loadMenu(MenuRepository& repo, const std::string& filename)
{
    json j = safeLoad(filename);

    for (auto& m : j)
    {
        repo.addLoaded(MenuItem(
            m["id"],
            m["name"],
            m["description"],
            m["price"]
        ));
    }

    repo.updateNextId();
}

void JsonStorage::loadOrders(OrderRepository& repo, const std::string& filename)
{
    json j = safeLoad(filename);

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

        repo.addLoaded(order);
    }

    repo.updateNextId();
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

    safeSave(j, filename);
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

    safeSave(j, filename);
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

    safeSave(j, filename);
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

    safeSave(j, filename);
}
