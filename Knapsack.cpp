#include <algorithm>
#include <iostream>
#include <vector>

// Структура для хранения данных о предмете
struct Item
{
    size_t price;
    size_t weight;
};

int main()
{
    // Вместимость рюкзака
    const size_t W = 15;

    // Список предметов
    std::vector<Item> items = {
        {6, 5}, {4, 3}, {3, 1}, {2, 3}, {5, 6}
    }; 
    // Количество предметов
    const size_t N = items.size();

    // Матрица для хранения результатов динамического программирования
    std::vector<std::vector<size_t>> dp(N + 1, std::vector<size_t>(W + 1, 0));

    // Заполнение таблицы dp
    for (size_t i = 1; i <= N; ++i)
    {
        for (size_t j = 0; j <= W; ++j)
        {
            if (items[i - 1].weight > j)
            {
                dp[i][j] = dp[i - 1][j];
            }
            else
            {
                dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - items[i - 1].weight] + items[i - 1].price);
            }
        }
    }

    // Максимальная ценность
    size_t MAX_VALUE = dp[N][W];

    // Восстановление выбранных предметов
    std::vector<Item> selected_items;
    size_t remaining_capacity = W;
    for (size_t i = N; i > 0; --i)
    {
        if (dp[i][remaining_capacity] != dp[i - 1][remaining_capacity])
        {
            selected_items.push_back(items[i - 1]);
            remaining_capacity -= items[i - 1].weight;
        }
    }

    // Вывод результата
    std::cout << "Max value: " << MAX_VALUE << std::endl;
    std::cout << "Items in knapsack:" << std::endl;
    for (const auto& item : selected_items)
    {
        std::cout << "{price: " << item.price << ", weight: " << item.weight << "}" << std::endl;
    }

    return 0;
}
