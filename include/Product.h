#pragma once
#include <string>
#include "Money.h"

/** Розміри товарів */
enum class Size { XS, S, M, L, XL };

/**
 * @brief Товар
 * 
 * Два товари рівні, якщо мають однакові id, color і size
 */
struct Product {
    std::string id;     ///< ID товару (напр. "TSHIRT-001")
    std::string title;  ///< Назва
    std::string color;  ///< Колір
    Size        size;   ///< Розмір
    Money       price;  ///< Ціна

    bool operator==(const Product& other) const {
        return id == other.id && color == other.color && size == other.size;
    }
};
