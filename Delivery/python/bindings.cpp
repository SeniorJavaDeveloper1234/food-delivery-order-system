#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "Client.h"
#include "Courier.h"
#include "MenuItem.h"
#include "OrderItem.h"
#include "Order.h"
#include "ClientRepository.h"
#include "CourierRepository.h"
#include "MenuRepository.h"
#include "OrderRepository.h"
#include "DeliverySystem.h"

namespace py = pybind11;

std::string orderStatusToString(OrderStatus s)
{
    switch (s)
    {
    case OrderStatus::Pending:    return "Pending";
    case OrderStatus::Preparing:  return "Preparing";
    case OrderStatus::Delivering: return "Delivering";
    case OrderStatus::Completed:  return "Completed";
    case OrderStatus::Cancelled:  return "Cancelled";
    }
    return "Unknown";
}




PYBIND11_MODULE(delivery, m)
{
    m.doc() = "Delivery System Python bindings";

 
    py::enum_<OrderStatus>(m, "OrderStatus")
        .value("Pending", OrderStatus::Pending)
        .value("Preparing", OrderStatus::Preparing)
        .value("Delivering", OrderStatus::Delivering)
        .value("Completed", OrderStatus::Completed)
        .value("Cancelled", OrderStatus::Cancelled);

    py::enum_<OrderSortType>(m, "OrderSortType")
        .value("ById", OrderSortType::ById)
        .value("ByClient", OrderSortType::ByClient)
        .value("ByCourier", OrderSortType::ByCourier)
        .value("ByTotal", OrderSortType::ByTotal)
        .value("ByCreated", OrderSortType::ByCreated);



    py::class_<Client>(m, "Client")
        .def(py::init<>())
        .def(py::init<int, const std::string&, const std::string&,
            const std::string&, const std::string&>())
        .def("getId", &Client::getId)
        .def("getFirstName", &Client::getFirstName)
        .def("getLastName", &Client::getLastName)
        .def("getPhone", &Client::getPhone)
        .def("getAddress", &Client::getAddress)
        .def("setId", &Client::setId)
        .def("setFirstName", &Client::setFirstName)
        .def("setLastName", &Client::setLastName)
        .def("setPhone", &Client::setPhone)
        .def("setAddress", &Client::setAddress);


    py::class_<Courier>(m, "Courier")
        .def(py::init<>())
        .def(py::init<int, const std::string&, const std::string&,
            const std::string&, bool>(),
            py::arg("id"),
            py::arg("firstName"),
            py::arg("lastName"),
            py::arg("phone"),
            py::arg("available") = true)
        .def("getId", &Courier::getId)
        .def("getFirstName", &Courier::getFirstName)
        .def("getLastName", &Courier::getLastName)
        .def("getPhone", &Courier::getPhone)
        .def("isAvailable", &Courier::isAvailable)
        .def("setId", &Courier::setId)
        .def("setFirstName", &Courier::setFirstName)
        .def("setLastName", &Courier::setLastName)
        .def("setPhone", &Courier::setPhone)
        .def("setAvailable", &Courier::setAvailable);


    py::class_<MenuItem>(m, "MenuItem")
        .def(py::init<>())
        .def(py::init<int, const std::string&, const std::string&, double>(),
            py::arg("id"),
            py::arg("name"),
            py::arg("description"),
            py::arg("price"))
        .def("getId", &MenuItem::getId)
        .def("getName", &MenuItem::getName)
        .def("getDescription", &MenuItem::getDescription)
        .def("getPrice", &MenuItem::getPrice)
        .def("setId", &MenuItem::setId)
        .def("setName", &MenuItem::setName)
        .def("setDescription", &MenuItem::setDescription)
        .def("setPrice", &MenuItem::setPrice);

  
    py::class_<OrderItem>(m, "OrderItem")
        .def(py::init<int, const std::string&, double, int>(),
            py::arg("menuItemId"),
            py::arg("name"),
            py::arg("unitPrice"),
            py::arg("quantity"))
        .def("getMenuItemId", &OrderItem::getMenuItemId)
        .def("getName", &OrderItem::getName)
        .def("getUnitPrice", &OrderItem::getUnitPrice)
        .def("getQuantity", &OrderItem::getQuantity)
        .def("getTotalPrice", &OrderItem::getTotalPrice)
        .def("setQuantity", &OrderItem::setQuantity);


    py::class_<Order>(m, "Order")
        .def(py::init<>())
        .def("getId", &Order::getId)
        .def("getClientId", &Order::getClientId)
        .def("getCourierId", &Order::getCourierId)
        .def("getItems", &Order::getItems)
        .def("getStatus", &Order::getStatus)
        .def("getCreatedAt", &Order::getCreatedAt)
        .def("getTotalPrice", &Order::getTotalPrice)
        .def("setId", &Order::setId)
        .def("setCourierId", &Order::setCourierId)
        .def("setStatus", &Order::setStatus)
        .def("calculateTotalPrice", &Order::calculateTotalPrice)
        .def("getStatusString",
            [](const Order& o)
            { return orderStatusToString(o.getStatus()); });


    py::class_<ClientRepository>(m, "ClientRepository")
        .def(py::init<>())
        .def("add", &ClientRepository::add)
        .def("remove", &ClientRepository::remove)
        .def("findById",
            &ClientRepository::findById,
            py::return_value_policy::reference)
        .def("findByPhone",
            &ClientRepository::findByPhone,
            py::return_value_policy::reference)
        .def("getAll", &ClientRepository::getAll);

    py::class_<CourierRepository>(m, "CourierRepository")
        .def(py::init<>())
        .def("add", &CourierRepository::add)
        .def("remove", &CourierRepository::remove)
        .def("findById",
            &CourierRepository::findById,
            py::return_value_policy::reference)
        .def("getAll", &CourierRepository::getAll)
        .def("findAvailableCourier",
            &CourierRepository::findAvailableCourier,
            py::return_value_policy::reference)
        .def("setCourierAvailability",
            &CourierRepository::setCourierAvailability);

    py::class_<MenuRepository>(m, "MenuRepository")
        .def(py::init<>())
        .def("add", &MenuRepository::add)
        .def("remove", &MenuRepository::remove)
        .def("findById",
            &MenuRepository::findById,
            py::return_value_policy::reference)
        .def("findByName",
            &MenuRepository::findByName,
            py::return_value_policy::reference)
        .def("searchByName", &MenuRepository::searchByName)

        .def("getAll", &MenuRepository::getAll)
        .def("updatePrice", &MenuRepository::updatePrice);



    py::class_<OrderRepository>(m, "OrderRepository")
        .def(py::init<>())
        .def("add", &OrderRepository::add)
        .def("remove", &OrderRepository::remove)
        .def("findById",
            &OrderRepository::findById,
            py::return_value_policy::reference)
        .def("getAll", &OrderRepository::getAll)
        .def("updateStatus", &OrderRepository::updateStatus)
        .def("findByClientId", &OrderRepository::findByClientId)
        .def("findByCourierId", &OrderRepository::findByCourierId);


    py::class_<DeliverySystem>(m, "DeliverySystem")
        .def(py::init<>())


        .def("addClient", &DeliverySystem::addClient)
        .def("updateClient", &DeliverySystem::updateClient)
        .def("removeClient", &DeliverySystem::removeClient)


        .def("addCourier", &DeliverySystem::addCourier)
        .def("updateCourier", &DeliverySystem::updateCourier)
        .def("removeCourier", &DeliverySystem::removeCourier)

        .def("addMenuItem", &DeliverySystem::addMenuItem)
        .def("removeMenuItem", &DeliverySystem::removeMenuItem)
        .def("searchMenu", &DeliverySystem::searchMenu)

        .def("createOrder",
            py::overload_cast<int, const std::vector<int>&>(
                &DeliverySystem::createOrder),
            py::return_value_policy::reference)

        .def("createOrder",
            py::overload_cast<int, const std::vector<OrderItem>&>(
                &DeliverySystem::createOrder),
            py::return_value_policy::reference)

        .def("deleteOrder", &DeliverySystem::deleteOrder)


        .def("updateMenuItem", &DeliverySystem::updateMenuItem)

        .def("completeOrder", &DeliverySystem::completeOrder)
        .def("cancelOrder", &DeliverySystem::cancelOrder)

        .def("getClientOrders", &DeliverySystem::getClientOrders)
        .def("getCourierOrders", &DeliverySystem::getCourierOrders)
        .def("getSortedOrders", &DeliverySystem::getSortedOrders)



        .def("clients", &DeliverySystem::clients,
            py::return_value_policy::reference)
        .def("couriers", &DeliverySystem::couriers,
            py::return_value_policy::reference)
        .def("menu", &DeliverySystem::menu,
            py::return_value_policy::reference)
        .def("orders", &DeliverySystem::orders,
            py::return_value_policy::reference)

        .def("saveAll", &DeliverySystem::saveAll);
            
}
