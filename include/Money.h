#pragma once
#include <cstdint>
#include <string>
#include <stdexcept>

/**
 * @brief Клас для роботи з грошовими сумами
 * 
 * Зберігає суму в копійках, щоб уникнути проблем з float/double
 */
class Money {
    int64_t cents_;
public:
    /** Конструктор за замовчуванням - 0 грн */
    Money() : cents_(0) {}

    /** Створює Money з копійок
     * @param cents кількість копійок
     */
    explicit Money(int64_t cents) : cents_(cents) {}

    /**
     * Створює Money з гривень і копійок
     * @param major гривні
     * @param minor копійки (0-99)
     * @throws std::invalid_argument якщо minor > 99
     * 
     * @example
     * Money m = Money::fromMajorMinor(10, 50); // 10.50 грн
     */
    static Money fromMajorMinor(int64_t major, int64_t minor) {
        if (minor < 0 || minor > 99) throw std::invalid_argument("minor must be 0..99");
        return Money(major * 100 + minor);
    }

    /** Створює Money з числа з плаваючою комою
     * @param value значення в гривнях
     */
    static Money fromDouble(double value);

    /** Повертає кількість копійок */
    int64_t cents() const { return cents_; }

    /** Додає дві суми */
    Money operator+(Money other) const { return Money(cents_ + other.cents_); }
    
    /** Віднімає одну суму від іншої */
    Money operator-(Money other) const { return Money(cents_ - other.cents_); }
    
    /** Множить суму на кількість */
    Money operator*(int qty) const     { return Money(cents_ * qty); }

    /** Перевіряє рівність сум */
    bool operator==(Money other) const { return cents_ == other.cents_; }
    
    /** Перевіряє нерівність сум */
    bool operator!=(Money other) const { return !(*this == other); }
    
    /** Перевіряє чи поточна сума менша */
    bool operator<(Money other)  const { return cents_ < other.cents_; }

    /** Формат: "X.XX грн" */
    std::string str() const;
};
