#include "Money.h"
#include <iomanip>
#include <sstream>
#include <cmath>
#include <cstdlib>

Money Money::fromDouble(double value) {
    return Money(static_cast<int64_t>(std::llround(value * 100.0)));
}

std::string Money::str() const {
    std::ostringstream oss;
    long long absC = std::llabs(cents_);
    oss << (cents_ < 0 ? "-" : "")
        << (absC / 100) << '.'
        << std::setw(2) << std::setfill('0') << (absC % 100);
    return oss.str();
}
