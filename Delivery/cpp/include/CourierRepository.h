#pragma once
#include <vector>
#include "Courier.h"
#include "IRepository.h"

class CourierRepository : public IRepository<Courier> {
private:
    std::vector<Courier> couriers;
    int nextId = 1;

public:
    CourierRepository() = default;

    void add(const Courier& courier) override;

    bool remove(int id) override;

    Courier* findById(int id) override;

    std::vector<Courier> getAll() const override;

    Courier* findAvailableCourier();

    void setCourierAvailability(int id, bool available);
};
