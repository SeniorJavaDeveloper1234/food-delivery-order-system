#include "ClientRepository.h"

void ClientRepository::add(const Client& client) {
    Client c = client;       
    c.setId(nextId++);         
    clients.push_back(c);
}


bool ClientRepository::remove(int id) {
    for (auto it = clients.begin(); it != clients.end(); ++it) {
        if (it->getId() == id) {
            clients.erase(it);
            return true;
        }
    }
    return false;
}

Client* ClientRepository::findById(int id) {
    for (auto& c : clients) {
        if (c.getId() == id) {
            return &c;
        }
    }
    return nullptr;
}

std::vector<Client> ClientRepository::getAll() const {
    return clients;
}


Client* ClientRepository::findByPhone(const std::string& phone) {
    for (auto& c : clients) {
        if (c.getPhone() == phone) {
            return &c;
        }
    }
    return nullptr;
}
