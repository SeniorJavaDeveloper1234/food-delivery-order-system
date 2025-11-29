#include "OrderItem.h"

OrderItem::OrderItem(int menuItemId, int quantity, double price)
    : menuItemId(menuItemId),
    quantity(quantity),
    price(price)
{
}

int OrderItem::getMenuItemId() const {
    return menuItemId;
}

int OrderItem::getQuantity() const {
    return quantity;
}

double OrderItem::getPrice() const {
    return price;
}

void OrderItem::setQuantity(int q) {
    quantity = q;
}

void OrderItem::setPrice(double p) {
    price = p;
}

double OrderItem::getTotal() const {
    return price * quantity;
}
