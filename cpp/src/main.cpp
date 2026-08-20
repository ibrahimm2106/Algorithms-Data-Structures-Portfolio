#include "OnlineStore.hpp"

#include <iostream>

int main() {
    OnlineStore store;

    store.addPurchase(58, "Akin Gumus", "pen", "01-10-2023");
    store.addPurchase(129, "Zen Ozer", "glove", "01-10-2023");
    store.addPurchase(3, "Mat Burke", "candle", "03-10-2023");
    store.addPurchase(25, "Jasmine Hedba", "hat", "04-10-2023");
    store.addPurchase(8, "Kelter Ergun", "curtain", "03-10-2023");
    store.addPurchase(3, "Mat Burke", "soap", "05-10-2023");
    store.addPurchase(16, "Mahilda Yaz", "sock", "07-10-2023");
    store.addPurchase(73, "Servet Almat", "map", "09-10-2023");
    store.addPurchase(25, "Jasmine Hedba", "paper", "12-10-2023");

    std::cout << "STEP 1 - Add nine purchases\n";
    store.printPurchases(std::cout);

    store.returnPurchase(1);
    std::cout << "\nSTEP 2 - Return first current purchase\n";
    store.printPurchases(std::cout);

    store.sortPurchases();
    std::cout << "\nSTEP 3 - Sort current purchases by customer ID\n";
    store.printPurchases(std::cout);

    store.processPurchase(2);
    store.processPurchase(4);
    std::cout << "\nSTEP 4 - Process positions 2 and 4\n";
    store.printPurchases(std::cout);

    std::cout << "\nSTEP 5 - Search current purchases for customer ID 25\nPositions: ";
    const auto positions = store.searchPurchases(25);
    for (std::size_t index = 0; index < positions.size(); ++index) {
        std::cout << positions[index] << (index + 1 == positions.size() ? "\n" : ", ");
    }
}
