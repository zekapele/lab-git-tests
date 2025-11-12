#pragma once
#include <string>
#include "Money.h"

/** Результат застосування знижки */
struct DiscountResult {
    Money discount;    ///< Сума знижки
    std::string reason; ///< Причина
};

/**
 * @brief Знижки
 * 
 * Статичні методи для різних типів знижок
 */
class Discounts {
public:
    /** Фіксована знижка за промокодом. Промокоди: SAVE10 (10 грн), SAVE20 (20 грн), SAVE50 (50 грн) */
    static DiscountResult promoFixed(const std::string& code, Money subtotal);

    /** 10% знижка якщо subtotal >= threshold */
    static DiscountResult tenPercentOver(Money subtotal, Money threshold);
};
