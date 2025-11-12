#pragma once
#include <vector>
#include <optional>
#include "Product.h"
#include "Money.h"

/** Елемент кошика */
struct CartItem {
    Product product; ///< Товар
    int qty;         ///< Кількість
};

/**
 * @brief Кошик покупок
 * 
 * Якщо додаєш той самий товар (id+color+size), кількість збільшується
 */
class Cart {
    std::vector<CartItem> items_;
public:
    const std::vector<CartItem>& items() const { return items_; }

    /**
     * @brief Додає товар до кошика
     * 
     * Якщо товар з такими самими id, color та size вже є в кошику,
     * то кількість додається до існуючої. Інакше створюється новий елемент.
     * 
     * @param p товар для додавання
     * @param qty кількість одиниць товару
     * 
     * @example
     * cart.add(product, 2);
     * cart.add(product, 1); // буде 3 штуки
     */
    void add(const Product& p, int qty);

    /** Видаляє qty одиниць товару */
    void remove(const Product& p, int qty);

    /** Сума без знижок і ПДВ */
    Money subtotal() const;

    /** Шукає товар в кошику */
    std::optional<CartItem> find(const Product& p) const;
};
