#include "OnlineStore.hpp"

#include <cassert>
#include <vector>

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

    assert((store.currentCustomerIds() == std::vector<int>{58,129,3,25,8,3,16,73,25}));
    assert(store.returnPurchase(1));
    assert((store.returnedCustomerIds() == std::vector<int>{58}));
    assert(!store.returnPurchase(100));

    store.sortPurchases();
    assert((store.currentCustomerIds() == std::vector<int>{3,3,8,16,25,25,73,129}));

    assert(store.processPurchase(2));
    assert(store.processPurchase(4));
    assert((store.processedCustomerIds() == std::vector<int>{3,25}));
    assert((store.currentCustomerIds() == std::vector<int>{3,8,16,25,73,129}));
    assert((store.searchPurchases(25) == std::vector<std::size_t>{4}));
}
