#include "MenuRepository.h"
#include <algorithm>


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


std::vector<MenuItem> MenuRepository::searchByName(const std::string& part) const {
    std::vector<MenuItem> result;

    if (part.empty())
        return items;

    std::string lowerPart = part;
    std::transform(lowerPart.begin(), lowerPart.end(), lowerPart.begin(), ::tolower);

    for (const auto& m : items) {
        std::string name = m.getName();
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);

        if (name.find(lowerPart) != std::string::npos) {
            result.push_back(m);
        }
    }

    return result;
}


void MenuRepository::updatePrice(int id, double newPrice) {
    for (auto& m : items) {
        if (m.getId() == id) {
            m.setPrice(newPrice);
            return;
        }
    }
}

void MenuRepository::addLoaded(const MenuItem& m)
{
    items.push_back(m);
}

void MenuRepository::updateNextId()
{
    int maxId = 0;
    for (auto& m : items)
        if (m.getId() > maxId)
            maxId = m.getId();

    nextId = maxId + 1;
}

