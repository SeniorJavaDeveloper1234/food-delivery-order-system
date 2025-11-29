
#include "Courier.h"
Courier::Courier(int id,
    const std::string& firstName,
    const std::string& lastName,
    const std::string& phone,
    bool available) : id(id),
    firstName(firstName),
    lastName(lastName),
    phone(phone),
    available(available)
{
}

int Courier::getId() const {
    return id;
}

const std::string& Courier::getFirstName() const {
    return firstName;
}

const std::string& Courier::getLastName() const {
    return lastName;
}

const std::string& Courier::getPhone() const {
    return phone;
}

bool Courier::isAvailable() const {
    return available;
}

void Courier::setFirstName(const std::string& name) {
    firstName = name;
}

void Courier::setLastName(const std::string& name) {
    lastName = name;
}

void Courier::setPhone(const std::string& ph) {
    phone = ph;
}

void Courier::setAvailable(bool isFree) {
    available = isFree;
}
