#pragma once

#include <cstddef>
#include <iosfwd>
#include <string>
#include <vector>

struct PurchaseNode {
    int customerId;
    std::string customerName;
    std::string purchasedGood;
    std::string purchaseDate;
    PurchaseNode* next;

    PurchaseNode(int id, std::string name, std::string good, std::string date);
};

class OnlineStore {
public:
    OnlineStore() = default;
    ~OnlineStore();

    OnlineStore(const OnlineStore&) = delete;
    OnlineStore& operator=(const OnlineStore&) = delete;

    void addPurchase(int id, const std::string& name, const std::string& good, const std::string& date);
    bool processPurchase(std::size_t location);
    bool returnPurchase(std::size_t location);
    void sortPurchases();
    std::vector<std::size_t> searchPurchases(int customerId) const;
    void printPurchases(std::ostream& output) const;

    std::vector<int> currentCustomerIds() const;
    std::vector<int> processedCustomerIds() const;
    std::vector<int> returnedCustomerIds() const;

private:
    PurchaseNode* currentPurchasesHead_ = nullptr;
    PurchaseNode* processedPurchasesHead_ = nullptr;
    PurchaseNode* returnedPurchasesHead_ = nullptr;

    static void append(PurchaseNode*& head, PurchaseNode* node);
    static PurchaseNode* detachAt(PurchaseNode*& head, std::size_t location);
    static void clear(PurchaseNode*& head);
    static void printList(std::ostream& output, const PurchaseNode* head);
    static std::vector<int> customerIds(const PurchaseNode* head);
};
