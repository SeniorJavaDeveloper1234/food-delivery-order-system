#pragma once

#include <string>
#include "ClientRepository.h"
#include "CourierRepository.h"
#include "MenuRepository.h"
#include "OrderRepository.h"

#include "json.hpp"
using json = nlohmann::json;

class JsonStorage {
public:

    static void loadClients(ClientRepository& repo, const std::string& filename);
    static void loadCouriers(CourierRepository& repo, const std::string& filename);
    static void loadMenu(MenuRepository& repo, const std::string& filename);
    static void loadOrders(OrderRepository& repo, const std::string& filename);

    static void saveClients(const ClientRepository& repo, const std::string& filename);
    static void saveCouriers(const CourierRepository& repo, const std::string& filename);
    static void saveMenu(const MenuRepository& repo, const std::string& filename);
    static void saveOrders(const OrderRepository& repo, const std::string& filename);
};
