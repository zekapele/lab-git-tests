#pragma once
#include <string>
#include "Cart.h"
#include "Inventory.h"
#include "Discounts.h"

struct OrderTotals {
    Money subtotal;
    Money discount;
    Money vat;     // 20% від (subtotal - discount), не < 0
    Money total;   // subtotal - discount + vat
};

class OrderService {
    Inventory& inventory_;
    double vatRate_;
public:
    explicit OrderService(Inventory& inv, double vatRate = 0.20)
        : inventory_(inv), vatRate_(vatRate) {}

    OrderTotals checkout(const Cart& cart, const std::string& promo = "");
};
