#pragma once
#include <string>
#include "Money.h"

struct DiscountResult {
    Money discount;    // позитивна сума, яку віднімаємо
    std::string reason;
};

class Discounts {
public:
    // фіксовані промокоди
    static DiscountResult promoFixed(const std::string& code, Money subtotal);
    // 10% знижка, якщо сума >= threshold
    static DiscountResult tenPercentOver(Money subtotal, Money threshold);
};
