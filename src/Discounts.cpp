#include "Discounts.h"

DiscountResult Discounts::promoFixed(const std::string& code, Money /*subtotal*/) {
    if (code == "WELCOME50") return { Money::fromMajorMinor(0,50), "Promo WELCOME50" };
    if (code == "MINUS200")  return { Money::fromMajorMinor(2,00), "Promo MINUS200" };
    return { Money{0}, "No promo" };
}

DiscountResult Discounts::tenPercentOver(Money subtotal, Money threshold) {
    if (subtotal.cents() >= threshold.cents()) {
        auto disc = Money( (subtotal.cents() * 10) / 100 );
        return { disc, "10% over threshold" };
    }
    return { Money{0}, "Below threshold" };
}
