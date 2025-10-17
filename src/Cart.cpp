#include "Cart.h"
#include <stdexcept>

void Cart::add(const Product& p, int qty) {
    if (qty <= 0) throw std::invalid_argument("qty <= 0");
    for (auto& it : items_) {
        if (it.product == p) { it.qty += qty; return; }
    }
    items_.push_back({p, qty});
}

void Cart::remove(const Product& p, int qty) {
    if (qty <= 0) throw std::invalid_argument("qty <= 0");
    for (auto it = items_.begin(); it != items_.end(); ++it) {
        if (it->product == p) {
            if (qty >= it->qty) { items_.erase(it); }
            else { it->qty -= qty; }
            return;
        }
    }
    throw std::runtime_error("item not in cart");
}

Money Cart::subtotal() const {
    Money sum{0};
    for (const auto& it : items_) {
        sum = sum + (it.product.price * it.qty);
    }
    return sum;
}

std::optional<CartItem> Cart::find(const Product& p) const {
    for (const auto& it : items_) if (it.product == p) return it;
    return std::nullopt;
}
