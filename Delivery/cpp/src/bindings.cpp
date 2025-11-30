#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "DeliverySystem.h"
#include "Client.h"
#include "Courier.h"
#include "MenuItem.h"
#include "Order.h"

namespace py = pybind11;

PYBIND11_MODULE(delivery, m)
{
    m.doc() = "Delivery System Python bindings";

    py::class_<Client>(m, "Client")
        .def(py::init<int, const std::string&, const std::string&, const std::string&, const std::string&>())
        .def("getId", &Client::getId)
        .def("getFirstName", &Client::getFirstName)
        .def("getLastName", &Client::getLastName)
        .def("getPhone", &Client::getPhone)
        .def("getAddress", &Client::getAddress);

    py::class_<Courier>(m, "Courier")
        .def(py::init<int, const std::string&, const std::string&, const std::string&, bool>())
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

    py::class_<Order>(m, "Order")
        .def("getId", &Order::getId)
        .def("getClientId", &Order::getClientId)
        .def("getCourierId", &Order::getCourierId)
        .def("getStatus", &Order::getStatus)
        .def("getTotalPrice", &Order::getTotalPrice);

    py::class_<DeliverySystem>(m, "DeliverySystem")
        .def(py::init<>())
        .def("createOrder", &DeliverySystem::createOrder,
            py::return_value_policy::reference)
        .def("completeOrder", &DeliverySystem::completeOrder)
        .def("cancelOrder", &DeliverySystem::cancelOrder)
        .def("getClientOrders", &DeliverySystem::getClientOrders)
        .def("getCourierOrders", &DeliverySystem::getCourierOrders)
        .def("clients", &DeliverySystem::clients, py::return_value_policy::reference)
        .def("couriers", &DeliverySystem::couriers, py::return_value_policy::reference)
        .def("menu", &DeliverySystem::menu, py::return_value_policy::reference);
}
