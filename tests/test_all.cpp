#include <gtest/gtest.h>
#include "Money.h"
#include "Product.h"
#include "Cart.h"
#include "Inventory.h"
#include "Discounts.h"
#include "Order.h"

// ---------------- MONEY ----------------
TEST(MoneyTest, FromDoubleAndString) {
    auto m = Money::fromDouble(12.34);
    EXPECT_EQ(m.cents(), 1234);
    EXPECT_EQ(m.str(), "12.34");
    EXPECT_EQ(Money(-250).str(), "-2.50");
}

// ---------------- CART ----------------
static Product mkTee(std::string id="TSHIRT-001", Size size=Size::M, Money price=Money::fromMajorMinor(19,99)) {
    return Product{id, "Basic T-Shirt", "black", size, price};
}

TEST(CartTest, AddAndSubtotal) {
    Cart c; auto p = mkTee();
    c.add(p, 2);
    EXPECT_EQ(c.subtotal().cents(), (p.price * 2).cents());
}

TEST(CartTest, MergeAndRemove) {
    Cart c; auto p = mkTee();
    c.add(p, 1); c.add(p, 2);
    EXPECT_EQ(c.items().size(), 1);
    EXPECT_EQ(c.items()[0].qty, 3);
    c.remove(p, 2);
    EXPECT_EQ(c.items()[0].qty, 1);
    c.remove(p, 1);
    EXPECT_TRUE(c.items().empty());
}

TEST(CartTest, RemoveInvalidThrows) {
    Cart c; auto p = mkTee();
    EXPECT_THROW(c.remove(p, 1), std::runtime_error);
}

// ---------------- INVENTORY ----------------
TEST(InventoryTest, SetGetReserveRelease) {
    Inventory inv; auto p = mkTee();
    inv.setStock(p, 3);
    EXPECT_EQ(inv.getStock(p), 3);
    inv.reserve(p, 2);
    EXPECT_EQ(inv.getStock(p), 1);
    inv.release(p, 1);
    EXPECT_EQ(inv.getStock(p), 2);
}

TEST(InventoryTest, NotEnoughStockThrows) {
    Inventory inv; auto p = mkTee();
    inv.setStock(p, 1);
    EXPECT_THROW(inv.reserve(p, 5), std::runtime_error);
}

// ---------------- DISCOUNTS ----------------
TEST(DiscountsTest, PromoAndThreshold) {
    auto promo = Discounts::promoFixed("WELCOME50", Money::fromMajorMinor(10,0));
    EXPECT_EQ(promo.discount.cents(), 50);
    auto none = Discounts::promoFixed("INVALID", Money::fromMajorMinor(10,0));
    EXPECT_EQ(none.discount.cents(), 0);

    auto over = Discounts::tenPercentOver(Money::fromMajorMinor(60,0), Money::fromMajorMinor(50,0));
    EXPECT_EQ(over.discount.cents(), 600);
    auto below = Discounts::tenPercentOver(Money::fromMajorMinor(40,0), Money::fromMajorMinor(50,0));
    EXPECT_EQ(below.discount.cents(), 0);
}

// ---------------- ORDER ----------------
TEST(OrderTest, CheckoutAppliesMaxDiscount) {
    Inventory inv; OrderService svc(inv, 0.20);
    auto p = mkTee("TSHIRT-001", Size::L, Money::fromMajorMinor(60,0));
    inv.setStock(p, 3);
    Cart cart; cart.add(p, 1);

    auto totals = svc.checkout(cart, "WELCOME50");
    EXPECT_EQ(totals.subtotal.cents(), 6000);
    EXPECT_EQ(totals.discount.cents(), 600);  // 10% over threshold
    EXPECT_EQ(totals.vat.cents(), 1080);
    EXPECT_EQ(totals.total.cents(), 6480);
}

TEST(OrderTest, NegativeTaxableClampedToZero) {
    Inventory inv; OrderService svc(inv, 0.20);
    auto p = mkTee("SALE", Size::S, Money::fromMajorMinor(1,0));
    inv.setStock(p, 1);
    Cart cart; cart.add(p, 1);

    auto totals = svc.checkout(cart, "MINUS200");
    EXPECT_EQ(totals.subtotal.cents(), 100);
    EXPECT_EQ(totals.discount.cents(), 200);
    EXPECT_EQ(totals.vat.cents(), 0);
    EXPECT_EQ(totals.total.cents(), 0);
}
