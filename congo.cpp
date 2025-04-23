#include <iostream>
#include <map>
#include <memory>
#include <unordered_map>
#include <stdexcept>

using namespace std;

class DuplicateItemException : public runtime_error {
    public:
        DuplicateItemException(const string& msg) : runtime_error(msg) {}
};

class ItemNotFoundException : public runtime_error {
    public:
        ItemNotFoundException(const string& msg) : runtime_error(msg) {}
 };

class StoredItem {
    private:
        string id;
        string description;
        string location;
    
    public:
        StoredItem(string id, string desc, string loc)
            : id(id), description(desc), location(loc) {}
    
        string getId() const { return id; }
        string getDescription() const { return description; }
        string getLocation() const { return location; }
};
class StorageManager {
    private:
        unordered_map<string, shared_ptr<StoredItem>> itemById;
        map<string, shared_ptr<StoredItem>> itemByDescription;
    
    public:
        // Add an item to both maps, throw if ID exists
        void addItem(const shared_ptr<StoredItem>& item) {
            const string& id = item->getId();
            if (itemById.find(id) != itemById.end()) {
                throw DuplicateItemException("Item with ID " + id + " already exists!");
            }
            itemById[id] = item;
            itemByDescription[item->getDescription()] = item;
            cout << "Adding item: " << id << " - " << item->getDescription() << endl;
        }
        shared_ptr<StoredItem> findById(const string& id) const {
            auto it = itemById.find(id);
            if (it == itemById.end()) {
                throw ItemNotFoundException("Item with ID " + id + " not found!");
            }
            return it->second;
        }
    
        void removeItem(const string& id) {
            auto it = itemById.find(id);
            if (it == itemById.end()) {
                throw ItemNotFoundException("Item with ID " + id + " not found!");
            }
            itemByDescription.erase(it->second->getDescription());
            itemById.erase(it);
        }
    
        void listItemsByDescription() const {
            if (itemByDescription.empty()) {
                cout << "No items in the warehouse." << endl;
                return;
            }
            cout << "Items in Description Order:" << endl;
            for (const auto& pair : itemByDescription) {
                cout << "- " << pair.first << ": " << pair.second->getLocation() << endl;
            }
        }
};
void testDuplicateAddition(StorageManager& manager){
    auto item1 = make_shared<StoredItem>("ITEM001","LED Light","Aisle 3, Shelf 1");
    manager.addItem(item1);
    cout<< "Attempting to add ITEM001 again."<<endl;
    try {
        manager.addItem(item1);
    } catch (const DuplicateItemException& e) {
        cout << "Error: " << e.what() << endl;
    }
}
void testItemNotFound(const StorageManager& manager){
    cout << "Attempting to find ITEM999..." << endl;
    try {
        manager.findById("ITEM999");
    } catch (const ItemNotFoundException& e) {
        cout << "Error: " << e.what() << endl;
    }
}
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    if (first == string::npos || last == string::npos) return "";
    return str.substr(first, last - first + 1);
}

// Helper function to get input with prompt
string getInput(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return trim(input);
}

int main() {
    StorageManager manager;
    string choice;

    while (true) {
        cout << "\nEric's CONGO Inventory System Menu:" << endl;
        cout << "1. Add Item" << endl;
        cout << "2. Find Item by ID" << endl;
        cout << "3. Remove Item" << endl;
        cout << "4. List Items by Description" << endl;
        cout << "5. Run Tests" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter choice (1-6): ";
        getline(cin, choice);

        if (choice == "1") {
            string id = getInput("Enter Item ID (ex. ITEM001): ");
            string desc = getInput("Enter Description (ex. LED Light): ");
            string loc = getInput("Enter Location (ex. Aisle 3, Shelf 1): ");
            if (id.empty() || desc.empty() || loc.empty()) {
                cout << "Error: All fields must be non-empty." << endl;
                continue;
            }
            try {
                auto item = make_shared<StoredItem>(id, desc, loc);
                manager.addItem(item);
            } catch (const DuplicateItemException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
        else if (choice == "2") {
            // Find Item by ID
            string id = getInput("Enter Item ID to find: ");
            if (id.empty()) {
                cout << "Error: ID cannot be empty." << endl;
                continue;
            }
            try {
                auto item = manager.findById(id);
                cout << "Found: " << item->getDescription() << " at " << item->getLocation() << endl;
            } catch (const ItemNotFoundException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
        else if (choice == "3") {
            // Remove Item
            string id = getInput("Enter Item ID to remove: ");
            if (id.empty()) {
                cout << "Error: ID CANNOT be empty." << endl;
                continue;
            }
            try {
                manager.removeItem(id);
                cout << "Item with ID " << id << " Removed successfully." << endl;
            } catch (const ItemNotFoundException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
        else if (choice == "4") {
            manager.listItemsByDescription();
        }
        else if (choice == "5") {
            cout << "\nRunning Test: Duplicate Addition" << endl;
            testDuplicateAddition(manager);
            cout << "\nRunning Test: Item Not Found" << endl;
            testItemNotFound(manager);
        }
        else if (choice == "6") {
            cout << "Exiting Eric's CONGO Inventory System. Goodbye.\n\n" << endl;
            break;
        }
        else {
            cout << "Invalid choice. Please enter a number between 1-6." << endl;
        }
    }

    return 0;
}