#pragma once
#include <vector>
#include <optional>
#include "Product.h"
#include "Money.h"

struct CartItem {
    Product product;
    int qty;
};

class Cart {
    std::vector<CartItem> items_;
public:
    const std::vector<CartItem>& items() const { return items_; }

    void add(const Product& p, int qty);    // додає / зливає
    void remove(const Product& p, int qty); // частково або повністю
    Money subtotal() const;                 // сума без знижок/ПДВ
    std::optional<CartItem> find(const Product& p) const;
};
