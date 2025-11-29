#pragma once
#include <vector>
#include "Client.h"
#include "IRepository.h"

class ClientRepository : public IRepository<Client> {
private:
    std::vector<Client> clients;
    int nextId = 1;

public:
    ClientRepository() = default;

    void add(const Client& client) override;

    bool remove(int id) override;

    Client* findById(int id) override;

    std::vector<Client> getAll() const override;

    Client* findByPhone(const std::string& phone);
};
