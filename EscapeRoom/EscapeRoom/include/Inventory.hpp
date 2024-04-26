#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <vector>
#include "Item.hpp"

class Inventory {
public:
    void addItem(const Item& item);
    void removeItem(const Item& item);
    bool useItem(const Item& item);

private:
    std::vector<Item> items;
};

#endif // INVENTORY_HPP
