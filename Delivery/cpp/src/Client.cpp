#include "Client.h"

Client::Client(int id,
    const std::string& firstName,
    const std::string& lastName,
    const std::string& phone)
    : id(id), firstName(firstName), lastName(lastName), phone(phone) {
}

int Client::getId() const {
    return id;
}

const std::string& Client::getFirstName() const {
    return firstName;
}

const std::string& Client::getLastName() const {
    return lastName;
}

const std::string& Client::getPhone() const {
    return phone;
}

void Client::setFirstName(const std::string& name) {
    firstName = name;
}

void Client::setLastName(const std::string& name) {
    lastName = name;
}

void Client::setPhone(const std::string& ph) {
    phone = ph;
}
