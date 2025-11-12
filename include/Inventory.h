#pragma once
#include <unordered_map>
#include <stdexcept>
#include <string>
#include "Product.h"

/**
 * @brief Склад - управління запасами
 * 
 * Відстежує кількість товарів на складі
 */
class Inventory {
    std::unordered_map<std::string, int> stock_;
    static std::string key(const Product& p);
public:
    /** Встановлює кількість товару на складі */
    void setStock(const Product& p, int qty);

    /** Повертає кількість на складі (0 якщо немає) */
    int  getStock(const Product& p) const;

    /** Резервує товар (зменшує кількість). Викидає std::runtime_error якщо не вистачає */
    void reserve(const Product& p, int qty);

    /** Повертає товар на склад (збільшує кількість) */
    void release(const Product& p, int qty);
};
