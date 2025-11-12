#include "Order.h"
#include <stdexcept>
#include <algorithm>
#include <cmath>

OrderTotals OrderService::checkout(const Cart& cart, const std::string& promo) {
    // 1) перевірити наявність
    for (const auto& it : cart.items()) {
        if (inventory_.getStock(it.product) < it.qty) {
            throw std::runtime_error("Insufficient stock for " + it.product.id);
        }
    }
    // 2) резерв
    for (const auto& it : cart.items()) inventory_.reserve(it.product, it.qty);

    // 3) підсумки
    OrderTotals t{};
    t.subtotal = cart.subtotal();

    auto promoRes = Discounts::promoFixed(promo, t.subtotal);
    auto overRes  = Discounts::tenPercentOver(t.subtotal, Money::fromMajorMinor(50,0)); // 50.00

    // беремо більшу знижку
    t.discount = (promoRes.discount.cents() > overRes.discount.cents())
                 ? promoRes.discount : overRes.discount;

    auto taxable = std::max<int64_t>(0, t.subtotal.cents() - t.discount.cents());
    t.vat   = Money(static_cast<int64_t>(std::llround(taxable * vatRate_)));
    t.total = Money(taxable) + t.vat;

    return t;
}
