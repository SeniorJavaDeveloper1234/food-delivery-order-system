#include "OrderItem.h"

OrderItem::OrderItem(int menuItemId,
    const std::string& name,
    double unitPrice,
    int quantity)
    : menuItemId(menuItemId),
    name(name),
    unitPrice(unitPrice),
    quantity(quantity)
{
}

int OrderItem::getMenuItemId() const {
    return menuItemId;
}

const std::string& OrderItem::getName() const {
    return name;
}

double OrderItem::getUnitPrice() const {
    return unitPrice;
}

int OrderItem::getQuantity() const {
    return quantity;
}

double OrderItem::getTotalPrice() const {
    return unitPrice * quantity;
}

void OrderItem::setQuantity(int quantity) {
    this->quantity = quantity;
}
