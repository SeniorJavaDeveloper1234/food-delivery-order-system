#include "MenuItem.h"

MenuItem::MenuItem(int id,
    const std::string& name,
    const std::string& description,
    double price)
    : id(id),
    name(name),
    description(description),
    price(price)
{
}

int MenuItem::getId() const {
    return id;
}

const std::string& MenuItem::getName() const {
    return name;
}

const std::string& MenuItem::getDescription() const {
    return description;
}

double MenuItem::getPrice() const {
    return price;
}

void MenuItem::setId(int newId) {
    id = newId; 
}

void MenuItem::setName(const std::string& newName) {
    name = newName;
}

void MenuItem::setDescription(const std::string& desc) {
    description = desc;
}

void MenuItem::setPrice(double newPrice) {
    price = newPrice;
}
