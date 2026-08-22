#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Node struct for linked list
struct Node {
    int customerID;
    std::string customerName;
    std::string purchasedGood;
    std::string dateOfPurchase;
    Node* next;

    Node(int id, const std::string& name, const std::string& good, const std::string& date)
        : customerID(id), customerName(name), purchasedGood(good), dateOfPurchase(date), next(nullptr) {}
};

// OnlineStore class
class OnlineStore {
private:
    Node* currentPurchasesHead;
    Node* processedPurchasesHead;
    Node* returnedPurchasesHead;

    void addToEnd(Node*& head, Node* newNode);
    void deleteNodeAt(Node*& head, int location, Node*& movedNode);
    void printList(Node* head) const;
    void bubbleSort(Node*& head);

public:
    OnlineStore();
    ~OnlineStore();
    void addPurchase(int id, const std::string& name, const std::string& good, const std::string& date);
    void processPurchase(int location);
    void returnPurchase(int location);
    void sortPurchases();
    void searchPurchases() const; // Changed to prompt for user input
    void printPurchases() const;
};

// Constructor
OnlineStore::OnlineStore() : currentPurchasesHead(nullptr), processedPurchasesHead(nullptr), returnedPurchasesHead(nullptr) {}

// Destructor
OnlineStore::~OnlineStore() {
    auto deleteList = [](Node*& head) {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        };
    deleteList(currentPurchasesHead);
    deleteList(processedPurchasesHead);
    deleteList(returnedPurchasesHead);
}

// Add a node to the end of a linked list
void OnlineStore::addToEnd(Node*& head, Node* newNode) {
    if (!head) {
        head = newNode;
    }
    else {
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Add a purchase
void OnlineStore::addPurchase(int id, const std::string& name, const std::string& good, const std::string& date) {
    Node* newNode = new Node(id, name, good, date);
    addToEnd(currentPurchasesHead, newNode);
}

// Delete a node at a specific location and move it to another list
void OnlineStore::deleteNodeAt(Node*& head, int location, Node*& movedNode) {
    if (!head || location < 1) {
        std::cout << "Error: Invalid location\n";
        return;
    }
    Node* prev = nullptr;
    Node* current = head;

    for (int i = 1; i < location && current; ++i) {
        prev = current;
        current = current->next;
    }

    if (!current) {
        std::cout << "Error: Location out of bounds\n";
        return;
    }

    movedNode = current;
    if (prev) {
        prev->next = current->next;
    }
    else {
        head = current->next;
    }
    movedNode->next = nullptr;
}

// Process a purchase
void OnlineStore::processPurchase(int location) {
    Node* movedNode = nullptr;
    deleteNodeAt(currentPurchasesHead, location, movedNode);
    if (movedNode) {
        addToEnd(processedPurchasesHead, movedNode);
    }
}

// Return a purchase
void OnlineStore::returnPurchase(int location) {
    Node* movedNode = nullptr;
    deleteNodeAt(currentPurchasesHead, location, movedNode);
    if (movedNode) {
        addToEnd(returnedPurchasesHead, movedNode);
    }
}

// Bubble sort current purchases by customer ID
void OnlineStore::sortPurchases() {
    bubbleSort(currentPurchasesHead);
}

// Search purchases by customer ID with input
void OnlineStore::searchPurchases() const {
    int customerID;
    std::cout << "Enter customer ID to search for: ";
    std::cin >> customerID;

    Node* current = currentPurchasesHead;
    std::vector<int> positions;
    int position = 1;

    while (current) {
        if (current->customerID == customerID) {
            positions.push_back(position);
        }
        current = current->next;
        ++position;
    }

    if (positions.empty()) {
        std::cout << "No purchases found for customer ID " << customerID << ".\n";
    }
    else {
        std::cout << "Purchases found at positions: ";
        for (size_t i = 0; i < positions.size(); ++i) {
            std::cout << positions[i] << (i == positions.size() - 1 ? "\n" : ", ");
        }
    }
}

// Print a linked list
void OnlineStore::printList(Node* head) const {
    std::cout << "[";
    while (head) {
        std::cout << "(" << head->customerID << ", " << head->customerName << ", "
            << head->purchasedGood << ", " << head->dateOfPurchase << ")";
        if (head->next) std::cout << ", ";
        head = head->next;
    }
    std::cout << "]\n";
}

// Print all purchases
void OnlineStore::printPurchases() const {
    std::cout << "Current purchases: ";
    printList(currentPurchasesHead);
    std::cout << "Processed purchases: ";
    printList(processedPurchasesHead);
    std::cout << "Returned purchases: ";
    printList(returnedPurchasesHead);
}

// Bubble sort helper
void OnlineStore::bubbleSort(Node*& head) {
    if (!head) return;
    bool swapped;
    do {
        swapped = false;
        Node* current = head;
        Node* prev = nullptr;

        while (current->next) {
            if (current->customerID > current->next->customerID) {
                swapped = true;
                Node* temp = current->next;
                current->next = temp->next;
                temp->next = current;
                if (prev) {
                    prev->next = temp;
                }
                else {
                    head = temp;
                }
                prev = temp;
            }
            else {
                prev = current;
                current = current->next;
            }
        }
    } while (swapped);
}

// Main function
int main() {
    OnlineStore store;

    // Step 1: Add purchases
    store.addPurchase(58, "Akin Gumus", "pen", "01-10-2023");
    store.addPurchase(129, "Zen Ozer", "glove", "01-10-2023");
    store.addPurchase(3, "Mat Burke", "candle", "03-10-2023");
    store.addPurchase(25, "Jasmine Hedba", "hat", "04-10-2023");
    store.addPurchase(8, "Kelter Ergun", "curtain", "03-10-2023");
    store.addPurchase(3, "Mat Burke", "soap", "05-10-2023");
    store.addPurchase(16, "Mahilda Yaz", "sock", "07-10-2023");
    store.addPurchase(73, "Servet Almat", "map", "09-10-2023");
    store.addPurchase(25, "Jasmine Hedba", "paper", "12-10-2023");
    std::cout << "After Step 1:\n";
    store.printPurchases();

    // Step 2: Return the first purchase
    store.returnPurchase(1);
    std::cout << "\nAfter Step 2:\n";
    store.printPurchases();

    // Step 3: Sort purchases by customer ID
    store.sortPurchases();
    std::cout << "\nAfter Step 3:\n";
    store.printPurchases();

    // Step 4: Process the 2nd and 4th purchase
    store.processPurchase(2);
    store.processPurchase(4);
    std::cout << "\nAfter Step 4:\n";
    store.printPurchases();

    // Step 5: Search for purchases by customer ID
    std::cout << "\nAfter Step 5:\n";
    store.searchPurchases();

    return 0;
}
