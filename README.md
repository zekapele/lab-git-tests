Educational project for practicing Git workflow and unit testing in C++ with GoogleTest.

## Documentation

Документація генерується через Doxygen і автоматично публікується на GitHub Pages.

### Локальна генерація

```bash
brew install doxygen  # macOS
doxygen Doxyfile
```

Документація буде в `docs/html/`.

### Онлайн документація

Автоматично оновлюється після кожного коміту:
https://[username].github.io/[repo-name]/

### Структура

- **Money** - робота з грошовими сумами
- **Product** - товар
- **Cart** - кошик покупок
- **Inventory** - склад
- **Discounts** - знижки
- **OrderService** - оформлення замовлень

Використано Doxygen теги: @brief, @param, @return, @throws, @example
