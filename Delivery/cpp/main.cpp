#include <iostream>
#include <vector>
#include <cstdlib>
#include <filesystem>

#include "DeliverySystem.h"
#include "Client.h"
#include "Courier.h"
#include "MenuItem.h"
#include "JsonStorage.h"

int main()
{
    system("chcp 1251");

    DeliverySystem system;

    std::filesystem::create_directory("data");

    JsonStorage::loadClients(*system.clients(), "data/clients.json");
    JsonStorage::loadCouriers(*system.couriers(), "data/couriers.json");
    JsonStorage::loadMenu(*system.menu(), "data/menu.json");
    JsonStorage::loadOrders(*system.orders(), "data/orders.json");

    if (system.clients()->getAll().empty())
    {
        system.clients()->add(Client(0, "John", "Smith", "0931112233", "Main Street 20"));
        system.clients()->add(Client(0, "Anna", "Brown", "0975556677", "Freedom Avenue 15"));

    }

    if (system.couriers()->getAll().empty())
    {
        system.couriers()->add(Courier(0, "Igor", "Petrov", "0931122334", true));
        system.couriers()->add(Courier(0, "Maria", "Diaz", "0509988776", true));
    }

    if (system.menu()->getAll().empty())
    {
        system.menu()->add(MenuItem(0, "Pizza Margherita", "Classic italian pizza", 189.0));
        system.menu()->add(MenuItem(0, "Burger", "Juicy beef burger with cheese", 140.0));
        system.menu()->add(MenuItem(0, "Sushi Philadelphia", "Salmon, cream cheese", 235.0));
    }

    int choice = -1;

    while (choice != 0)
    {
        std::cout << "\n===== DELIVERY TEST MENU =====\n";
        std::cout << "1. Показати клієнтів\n";
        std::cout << "2. Показати кур'єрів\n";
        std::cout << "3. Показати меню страв\n";
        std::cout << "4. Створити замовлення\n";
        std::cout << "5. Завершити замовлення\n";
        std::cout << "6. Скасувати замовлення\n";
        std::cout << "7. Показати замовлення клієнта\n";
        std::cout << "8. Показати замовлення кур'єра\n";
        std::cout << "0. Вихід\n";
        std::cout << "Ваш вибір: ";
        std::cin >> choice;

        if (choice == 1)
        {
            std::cout << "\n=== CLIENTS ===\n";
            for (const auto& c : system.clients()->getAll())
            {
                std::cout << c.getId() << ": "
                    << c.getFirstName() << " " << c.getLastName()
                    << " | " << c.getPhone()
                    << " | " << c.getAddress() << "\n";
            }
        }

        else if (choice == 2)
        {
            std::cout << "\n=== COURIERS ===\n";
            for (const auto& c : system.couriers()->getAll())
            {
                std::cout << c.getId() << ": "
                    << c.getFirstName() << " " << c.getLastName()
                    << " | " << c.getPhone()
                    << " | " << (c.isAvailable() ? "вільний" : "зайнятий")
                    << "\n";
            }
        }

        else if (choice == 3)
        {
            std::cout << "\n=== MENU ===\n";
            for (const auto& m : system.menu()->getAll())
            {
                std::cout << m.getId() << ": "
                    << m.getName()
                    << " - " << m.getPrice() << " грн\n";
            }
        }

        else if (choice == 4)
        {
            int clientId;
            std::cout << "Введіть ID клієнта: ";
            std::cin >> clientId;

            std::cout << "Введіть ID страв (через пробіл, 0 – завершення): ";

            std::vector<int> itemIds;
            while (true)
            {
                int id;
                std::cin >> id;
                if (id == 0) break;
                itemIds.push_back(id);
            }

            Order* order = system.createOrder(clientId, itemIds);
            if (!order)
            {
                std::cout << "❌ Немає вільних кур'єрів!\n";
            }
            else
            {
                std::cout << "✔ Замовлення створено. ID = " << order->getId() << "\n";
                std::cout << "Сума: " << order->getTotalPrice() << " грн\n";

                JsonStorage::saveOrders(*system.orders(), "data/orders.json");
            }
        }

        else if (choice == 5)
        {
            int orderId;
            std::cout << "ID замовлення для завершення: ";
            std::cin >> orderId;

            if (system.completeOrder(orderId))
            {
                std::cout << "✔ Замовлення завершено.\n";
                JsonStorage::saveOrders(*system.orders(), "data/orders.json");
            }
            else
                std::cout << "❌ Замовлення не знайдено.\n";
        }

        else if (choice == 6)
        {
            int orderId;
            std::cout << "ID замовлення для скасування: ";
            std::cin >> orderId;

            if (system.cancelOrder(orderId))
            {
                std::cout << "✔ Замовлення скасовано.\n";
                JsonStorage::saveOrders(*system.orders(), "data/orders.json");
            }
            else
                std::cout << "❌ Замовлення не знайдено.\n";
        }

        else if (choice == 7)
        {
            int clientId;
            std::cout << "ID клієнта: ";
            std::cin >> clientId;

            auto orders = system.getClientOrders(clientId);
            if (orders.empty())
            {
                std::cout << "Замовлень немає.\n";
            }
            else
            {
                for (const auto& o : orders)
                {
                    std::cout << "\nORDER #" << o.getId()
                        << " | статус = " << (int)o.getStatus()
                        << " | сума = " << o.getTotalPrice() << "\n";
                }
            }
        }

        else if (choice == 8)
        {
            int courierId;
            std::cout << "ID кур'єра: ";
            std::cin >> courierId;

            auto orders = system.getCourierOrders(courierId);
            if (orders.empty())
            {
                std::cout << "Замовлень немає.\n";
            }
            else
            {
                for (const auto& o : orders)
                {
                    std::cout << "\nORDER #" << o.getId()
                        << " | клієнт = " << o.getClientId()
                        << " | сума = " << o.getTotalPrice() << "\n";
                }
            }
        }
    }

    JsonStorage::saveClients(*system.clients(), "data/clients.json");
    JsonStorage::saveCouriers(*system.couriers(), "data/couriers.json");
    JsonStorage::saveMenu(*system.menu(), "data/menu.json");
    JsonStorage::saveOrders(*system.orders(), "data/orders.json");

    std::cout << "Дані збережено. Вихід із програми.\n";
    return 0;
}
