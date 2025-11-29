#include "MenuRepository.h"

void MenuRepository::add(const MenuItem& item) {
    MenuItem m = item;      
    m.setId(nextId++);     
    items.push_back(m);
}

bool MenuRepository::remove(int id) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->getId() == id) {
            items.erase(it);
            return true;
        }
    }
    return false;
}

MenuItem* MenuRepository::findById(int id) {
    for (auto& m : items) {
        if (m.getId() == id) {
            return &m;
        }
    }
    return nullptr;
}

std::vector<MenuItem> MenuRepository::getAll() const {
    return items;
}

MenuItem* MenuRepository::findByName(const std::string& name) {
    for (auto& m : items) {
        if (m.getName() == name) {
            return &m;
        }
    }
    return nullptr;
}

void MenuRepository::updatePrice(int id, double newPrice) {
    for (auto& m : items) {
        if (m.getId() == id) {
            m.setPrice(newPrice);
            return;
        }
    }
}
