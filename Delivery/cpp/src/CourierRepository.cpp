#include "CourierRepository.h"

void CourierRepository::add(const Courier& courier) {
    Courier c = courier;  
    c.setId(nextId++);     
    couriers.push_back(c);
}

bool CourierRepository::remove(int id) {
    for (auto it = couriers.begin(); it != couriers.end(); ++it) {
        if (it->getId() == id) {
            couriers.erase(it);
            return true;
        }
    }
    return false;
}


Courier* CourierRepository::findById(int id) {
    for (auto& c : couriers) {
        if (c.getId() == id) {
            return &c;
        }
    }
    return nullptr;
}


std::vector<Courier> CourierRepository::getAll() const {
    return couriers;
}

Courier* CourierRepository::findAvailableCourier() {
    for (auto& c : couriers) {
        if (c.isAvailable()) {
            return &c;
        }
    }
    return nullptr; 
}

void CourierRepository::setCourierAvailability(int id, bool available) {
    for (auto& c : couriers) {
        if (c.getId() == id) {
            c.setAvailable(available);
            return;
        }
    }
}

void CourierRepository::addLoaded(const Courier& c)
{
    couriers.push_back(c);
}

void CourierRepository::updateNextId()
{
    int maxId = 0;
    for (auto& c : couriers)
        if (c.getId() > maxId)
            maxId = c.getId();

    nextId = maxId + 1;
}
