#pragma once
#include <string>
#include "Money.h"

enum class Size { XS, S, M, L, XL };

struct Product {
    std::string id;     // "TSHIRT-001"
    std::string title;  // "Basic T-Shirt"
    std::string color;  // "black"
    Size        size;   // M, L...
    Money       price;  // за одиницю

    bool operator==(const Product& other) const {
        return id == other.id && color == other.color && size == other.size;
    }
};
