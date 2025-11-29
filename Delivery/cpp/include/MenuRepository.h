#pragma once
#include <vector>
#include "MenuItem.h"
#include "IRepository.h"

class MenuRepository : public IRepository<MenuItem> {
private:
    std::vector<MenuItem> items;
    int nextId = 1;

public:
    MenuRepository() = default;

    void add(const MenuItem& item) override;

    bool remove(int id) override;

    MenuItem* findById(int id) override;

    std::vector<MenuItem> getAll() const override;

    MenuItem* findByName(const std::string& name);

    void updatePrice(int id, double newPrice);
};
