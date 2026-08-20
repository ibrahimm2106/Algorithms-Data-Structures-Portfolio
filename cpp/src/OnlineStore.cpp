#include "OnlineStore.hpp"

#include <algorithm>
#include <ostream>
#include <utility>

PurchaseNode::PurchaseNode(int id, std::string name, std::string good, std::string date)
    : customerId(id),
      customerName(std::move(name)),
      purchasedGood(std::move(good)),
      purchaseDate(std::move(date)),
      next(nullptr) {}

OnlineStore::~OnlineStore() {
    clear(currentPurchasesHead_);
    clear(processedPurchasesHead_);
    clear(returnedPurchasesHead_);
}

void OnlineStore::append(PurchaseNode*& head, PurchaseNode* node) {
    if (node == nullptr) {
        return;
    }
    node->next = nullptr;
    if (head == nullptr) {
        head = node;
        return;
    }
    PurchaseNode* cursor = head;
    while (cursor->next != nullptr) {
        cursor = cursor->next;
    }
    cursor->next = node;
}

PurchaseNode* OnlineStore::detachAt(PurchaseNode*& head, std::size_t location) {
    if (head == nullptr || location == 0) {
        return nullptr;
    }

    PurchaseNode* previous = nullptr;
    PurchaseNode* current = head;
    std::size_t index = 1;
    while (current != nullptr && index < location) {
        previous = current;
        current = current->next;
        ++index;
    }
    if (current == nullptr) {
        return nullptr;
    }

    if (previous == nullptr) {
        head = current->next;
    } else {
        previous->next = current->next;
    }
    current->next = nullptr;
    return current;
}

void OnlineStore::clear(PurchaseNode*& head) {
    while (head != nullptr) {
        PurchaseNode* next = head->next;
        delete head;
        head = next;
    }
}

void OnlineStore::addPurchase(int id, const std::string& name, const std::string& good, const std::string& date) {
    append(currentPurchasesHead_, new PurchaseNode{id, name, good, date});
}

bool OnlineStore::processPurchase(std::size_t location) {
    PurchaseNode* node = detachAt(currentPurchasesHead_, location);
    if (node == nullptr) {
        return false;
    }
    append(processedPurchasesHead_, node);
    return true;
}

bool OnlineStore::returnPurchase(std::size_t location) {
    PurchaseNode* node = detachAt(currentPurchasesHead_, location);
    if (node == nullptr) {
        return false;
    }
    append(returnedPurchasesHead_, node);
    return true;
}

void OnlineStore::sortPurchases() {
    if (currentPurchasesHead_ == nullptr) {
        return;
    }

    bool swapped;
    do {
        swapped = false;
        for (PurchaseNode* cursor = currentPurchasesHead_; cursor->next != nullptr; cursor = cursor->next) {
            if (cursor->customerId > cursor->next->customerId) {
                std::swap(cursor->customerId, cursor->next->customerId);
                std::swap(cursor->customerName, cursor->next->customerName);
                std::swap(cursor->purchasedGood, cursor->next->purchasedGood);
                std::swap(cursor->purchaseDate, cursor->next->purchaseDate);
                swapped = true;
            }
        }
    } while (swapped);
}

std::vector<std::size_t> OnlineStore::searchPurchases(int customerId) const {
    std::vector<std::size_t> matches;
    std::size_t position = 1;
    for (PurchaseNode* cursor = currentPurchasesHead_; cursor != nullptr; cursor = cursor->next, ++position) {
        if (cursor->customerId == customerId) {
            matches.push_back(position);
        }
    }
    return matches;
}

void OnlineStore::printList(std::ostream& output, const PurchaseNode* head) {
    output << '[';
    const PurchaseNode* cursor = head;
    while (cursor != nullptr) {
        output << '(' << cursor->customerId << ", " << cursor->customerName << ", "
               << cursor->purchasedGood << ", " << cursor->purchaseDate << ')';
        if (cursor->next != nullptr) {
            output << ", ";
        }
        cursor = cursor->next;
    }
    output << ']';
}

void OnlineStore::printPurchases(std::ostream& output) const {
    output << "Current purchases: ";
    printList(output, currentPurchasesHead_);
    output << "\nProcessed purchases: ";
    printList(output, processedPurchasesHead_);
    output << "\nReturned purchases: ";
    printList(output, returnedPurchasesHead_);
    output << '\n';
}

std::vector<int> OnlineStore::customerIds(const PurchaseNode* head) {
    std::vector<int> ids;
    for (const PurchaseNode* cursor = head; cursor != nullptr; cursor = cursor->next) {
        ids.push_back(cursor->customerId);
    }
    return ids;
}

std::vector<int> OnlineStore::currentCustomerIds() const { return customerIds(currentPurchasesHead_); }
std::vector<int> OnlineStore::processedCustomerIds() const { return customerIds(processedPurchasesHead_); }
std::vector<int> OnlineStore::returnedCustomerIds() const { return customerIds(returnedPurchasesHead_); }
