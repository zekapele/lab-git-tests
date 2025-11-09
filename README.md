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

## Висновок

Під час виконання лабораторної роботи набуто навичок:

- Документування коду за допомогою Doxygen з використанням стандартних тегів (@brief, @param, @return, @throws, @example)
- Налаштування Doxyfile для генерації HTML-документації
- Створення GitHub Actions workflow для автоматизації CI/CD
- Налаштування автоматичної публікації документації на GitHub Pages
- Робота з гілками Git (створення feature-гілки, коміти, push)

Документація тепер автоматично генерується та публікується після кожного коміту, що спрощує підтримку проекту та роботу команди.
