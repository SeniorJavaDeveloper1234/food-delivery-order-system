#pragma once
#include <vector>

template<typename T>
class IRepository {
public:
    virtual ~IRepository() = default;

    virtual void add(const T& item) = 0;

    virtual bool remove(int id) = 0;

    virtual T* findById(int id) = 0;

    virtual std::vector<T> getAll() const = 0;
};
