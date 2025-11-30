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


std::string orderStatusToString(OrderStatus s) {
    switch (s) {
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


    py::class_<Client>(m, "Client")
        .def(py::init<int, const std::string&, const std::string&,
            const std::string&, const std::string&>())
        .def("getId", &Client::getId)
        .def("getFirstName", &Client::getFirstName)
        .def("getLastName", &Client::getLastName)
        .def("getPhone", &Client::getPhone)
        .def("getAddress", &Client::getAddress);

    py::class_<Courier>(m, "Courier")
        .def(py::init<int, const std::string&, const std::string&,
            const std::string&, bool>())
        .def("getId", &Courier::getId)
        .def("getFirstName", &Courier::getFirstName)
        .def("getLastName", &Courier::getLastName)
        .def("getPhone", &Courier::getPhone)
        .def("isAvailable", &Courier::isAvailable);


    py::class_<MenuItem>(m, "MenuItem")
        .def(py::init<int, const std::string&, const std::string&, double>())
        .def("getId", &MenuItem::getId)
        .def("getName", &MenuItem::getName)
        .def("getDescription", &MenuItem::getDescription)
        .def("getPrice", &MenuItem::getPrice);

    py::class_<OrderItem>(m, "OrderItem")
        .def(py::init<int, const std::string&, double, int>())
        .def("getMenuItemId", &OrderItem::getMenuItemId)
        .def("getName", &OrderItem::getName)
        .def("getUnitPrice", &OrderItem::getUnitPrice)
        .def("getQuantity", &OrderItem::getQuantity)
        .def("getTotalPrice", &OrderItem::getTotalPrice);

    py::class_<Order>(m, "Order")
        .def("getId", &Order::getId)
        .def("getClientId", &Order::getClientId)
        .def("getCourierId", &Order::getCourierId)
        .def("getStatus", &Order::getStatus)
        .def("getStatusString", [](const Order& o) { return orderStatusToString(o.getStatus()); })
        .def("getItems", &Order::getItems)
        .def("getTotalPrice", &Order::getTotalPrice)
        .def("getCreatedAt", &Order::getCreatedAt);

    py::class_<ClientRepository>(m, "ClientRepository")
        .def("getAll", &ClientRepository::getAll);

    py::class_<CourierRepository>(m, "CourierRepository")
        .def("getAll", &CourierRepository::getAll);

    py::class_<MenuRepository>(m, "MenuRepository")
        .def("getAll", &MenuRepository::getAll);

    py::class_<OrderRepository>(m, "OrderRepository")
        .def("getAll", &OrderRepository::getAll)
        .def("findByClientId", &OrderRepository::findByClientId)
        .def("findByCourierId", &OrderRepository::findByCourierId);


    py::class_<DeliverySystem>(m, "DeliverySystem")
        .def(py::init<>())
        .def("createOrder", &DeliverySystem::createOrder,
            py::return_value_policy::reference)
        .def("completeOrder", &DeliverySystem::completeOrder)
        .def("cancelOrder", &DeliverySystem::cancelOrder)
        .def("getClientOrders", &DeliverySystem::getClientOrders)
        .def("getCourierOrders", &DeliverySystem::getCourierOrders)
        .def("clients", &DeliverySystem::clients,
            py::return_value_policy::reference)
        .def("couriers", &DeliverySystem::couriers,
            py::return_value_policy::reference)
        .def("menu", &DeliverySystem::menu,
            py::return_value_policy::reference)
        .def("orders", &DeliverySystem::orders,
            py::return_value_policy::reference);
}
