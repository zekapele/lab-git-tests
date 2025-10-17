#pragma once
#include <cstdint>
#include <string>
#include <stdexcept>

class Money {
    int64_t cents_;
public:
    Money() : cents_(0) {}                 // ✔️ звичайний дефолтний
    explicit Money(int64_t cents) : cents_(cents) {}  // ✔️ явний зі значенням

    static Money fromMajorMinor(int64_t major, int64_t minor) {
        if (minor < 0 || minor > 99) throw std::invalid_argument("minor must be 0..99");
        return Money(major * 100 + minor);
    }
    static Money fromDouble(double value);

    int64_t cents() const { return cents_; }

    Money operator+(Money other) const { return Money(cents_ + other.cents_); }
    Money operator-(Money other) const { return Money(cents_ - other.cents_); }
    Money operator*(int qty) const     { return Money(cents_ * qty); }

    bool operator==(Money other) const { return cents_ == other.cents_; }
    bool operator!=(Money other) const { return !(*this == other); }
    bool operator<(Money other)  const { return cents_ < other.cents_; }

    std::string str() const;
};
