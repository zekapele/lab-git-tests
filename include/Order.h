#pragma once
#include <string>
#include "Cart.h"
#include "Inventory.h"
#include "Discounts.h"

/** Підсумкові суми замовлення */
struct OrderTotals {
    Money subtotal; ///< Сума без знижок і ПДВ
    Money discount; ///< Знижка
    Money vat;      ///< ПДВ (20% від subtotal-discount)
    Money total;    ///< До сплати
};

/**
 * @brief Оформлення замовлень
 * 
 * Рахує суми, застосовує знижки, ПДВ, резервує товари
 */
class OrderService {
    Inventory& inventory_;
    double vatRate_;
public:
    /** Конструктор сервісу замовлень
     * @param inv інвентар для резервування
     * @param vatRate ставка ПДВ (за замовчуванням 0.20 = 20%)
     */
    explicit OrderService(Inventory& inv, double vatRate = 0.20)
        : inventory_(inv), vatRate_(vatRate) {}

    /** Оформляє замовлення. Рахує суми, застосовує знижки, ПДВ, резервує товари. Викидає std::runtime_error якщо не вистачає товарів */
    OrderTotals checkout(const Cart& cart, const std::string& promo = "");
};
