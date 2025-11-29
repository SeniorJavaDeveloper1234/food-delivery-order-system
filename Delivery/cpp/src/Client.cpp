#include "Client.h"

Client::Client(int id,
    const std::string& firstName,
    const std::string& lastName,
    const std::string& phone, 
    const std::string& address)
    : id(id), firstName(firstName), lastName(lastName), phone(phone), address(address){
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

const std::string& Client::getAddress() const {
    return address;
}


void Client::setId(int newId) {
    id = newId;
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

void Client::setAddress(const std::string& adr) {
    address = adr;
}

