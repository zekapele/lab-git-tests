#include "Inventory.h"

static int sizeToInt(Size s){ return static_cast<int>(s); }

std::string Inventory::key(const Product& p) {
    return p.id + "|" + p.color + "|" + std::to_string(sizeToInt(p.size));
}

void Inventory::setStock(const Product& p, int qty) {
    if (qty < 0) throw std::invalid_argument("qty < 0");
    stock_[key(p)] = qty;
}

int Inventory::getStock(const Product& p) const {
    auto k = const_cast<Inventory*>(this)->key(p);
    auto it = stock_.find(k);
    return it == stock_.end() ? 0 : it->second;
}

void Inventory::reserve(const Product& p, int qty) {
    if (qty <= 0) throw std::invalid_argument("qty <= 0");
    auto k = key(p);
    int cur = getStock(p);
    if (cur < qty) throw std::runtime_error("Not enough stock");
    stock_[k] = cur - qty;
}

void Inventory::release(const Product& p, int qty) {
    if (qty <= 0) throw std::invalid_argument("qty <= 0");
    auto k = key(p);
    stock_[k] = getStock(p) + qty;
}
