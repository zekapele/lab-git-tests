#include <iostream>
#include "Inventory.h"
#include "Cart.h"
#include "Order.h"

int main() {
    Inventory inv;
    Product tshirt{"TSHIRT-001", "Basic T-Shirt", "black", Size::M, Money::fromMajorMinor(19,99)};
    inv.setStock(tshirt, 10);

    Cart cart;
    cart.add(tshirt, 2);

    OrderService svc(inv, 0.20);
    auto totals = svc.checkout(cart, "WELCOME50");

    std::cout << "Subtotal: " << totals.subtotal.str() << "\n";
    std::cout << "Discount: " << totals.discount.str() << "\n";
    std::cout << "VAT:      " << totals.vat.str() << "\n";
    std::cout << "Total:    " << totals.total.str() << "\n";
    return 0;
}
