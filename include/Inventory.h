#pragma once
#include <unordered_map>
#include <stdexcept>
#include <string>
#include "Product.h"

class Inventory {
    std::unordered_map<std::string, int> stock_;
    static std::string key(const Product& p);
public:
    void setStock(const Product& p, int qty);
    int  getStock(const Product& p) const;
    void reserve(const Product& p, int qty); // кине, якщо не вистачає
    void release(const Product& p, int qty);
};
