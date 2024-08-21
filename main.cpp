#include <iostream>
#include <string>

using namespace std;  // Added the "using namespace std;" directive

class StockData {
public:
    string symbol;
    double price;
    int volume;

    StockData(const string& sym, double p, int v) : symbol(sym), price(p), volume(v) {}
};

class StockNode {
public:
    StockData data;
    StockNode* next;

    StockNode(const StockData& d) : data(d), next(nullptr) {}
};

class StockList {
private:
    StockNode* head;

public:
    StockList() : head(nullptr) {}

    void addStock(const StockData& data) {
        StockNode* newNode = new StockNode(data);
        newNode->next = head;
        head = newNode;
    }

    void displayStock(const StockNode* node) const {
        cout << "Symbol: " << node->data.symbol << ", Price: $" << node->data.price << ", Volume: " << node->data.volume << "\n";
    }

    void displayStocks() const {
        const StockNode* current = head;
        while (current != nullptr) {
            displayStock(current);
            current = current->next;
        }
    }

    StockNode* searchStock(const string& symbol) const {
        StockNode* current = head;
        while (current != nullptr) {
            if (current->data.symbol == symbol) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void removeStock(const string& symbol) {
        StockNode* current = head;
        StockNode* prev = nullptr;

        while (current != nullptr && current->data.symbol != symbol) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Stock not found.\n";
            return;
        }

        if (prev == nullptr) {
            head = current->next;
        } else {
            prev->next = current->next;
        }

        delete current;
        cout << "Stock removed successfully.\n";
    }

    void displayLatestStocks(int count) const {
        const StockNode* current = head;
        while (current != nullptr && count > 0) {
            displayStock(current);
            current = current->next;
            --count;
        }
    }
};

class StockTreeNode {
public:
    StockData data;
    StockTreeNode* left;
    StockTreeNode* right;

    StockTreeNode(const StockData& d) : data(d), left(nullptr), right(nullptr) {}
};

class StockBST {
public:
    StockTreeNode* root;

    StockBST() : root(nullptr) {}

    void insert(const StockData& data) {
        root = insertRecursive(root, data);
    }

    StockTreeNode* insertRecursive(StockTreeNode* root, const StockData& data) {
        if (root == nullptr) {
            return new StockTreeNode(data);
        }

        if (data.symbol < root->data.symbol) {
            root->left = insertRecursive(root->left, data);
        } else if (data.symbol > root->data.symbol) {
            root->right = insertRecursive(root->right, data);
        }

        return root;
    }

    void displayInOrder() const {
        displayInOrderRecursive(root);
    }

    void displayInOrderRecursive(StockTreeNode* root) const {
        if (root != nullptr) {
            displayInOrderRecursive(root->left);
            cout << root->data.symbol << " ";
            displayInOrderRecursive(root->right);
        }
    }

    StockTreeNode* removeBST(StockTreeNode* root, const string& symbol) {
        if (root == nullptr) {
            return root;
        }

        if (symbol < root->data.symbol) {
            root->left = removeBST(root->left, symbol);
        } else if (symbol > root->data.symbol) {
            root->right = removeBST(root->right, symbol);
        } else {
            if (root->left == nullptr) {
                StockTreeNode* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                StockTreeNode* temp = root->left;
                delete root;
                return temp;
            }

            StockTreeNode* temp = findMin(root->right);
            root->data = temp->data;
            root->right = removeBST(root->right, temp->data.symbol);
        }

        return root;
    }

    StockTreeNode* findMin(StockTreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
};

int main() {
    StockList stockList;
    StockBST stockBST;

    int choice;
    do {
        cout << "\nStock Market Dashboard:\n";  // Used "cout" instead of "std::cout"
        cout << "1. Add Stock\n";
        cout << "2. Remove Stock\n";
        cout << "3. Search Stock\n";
        cout << "4. Display All Stocks\n";
        cout << "5. Display Latest Stocks\n";
        cout << "6. Display BST In-Order\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string symbol;
                double price;
                int volume;

                cout << "Enter Stock Symbol: ";
                cin >> symbol;
                cout << "Enter Stock Price: $";
                cin >> price;
                cout << "Enter Stock Volume: ";
                cin >> volume;

                StockData stockData(symbol, price, volume);
                stockList.addStock(stockData);
                stockBST.insert(stockData);

                cout << "Stock added successfully.\n";
                break;
            }
            case 2: {
                string symbol;
                cout << "Enter Stock Symbol to Remove: ";
                cin >> symbol;

                stockList.removeStock(symbol);
                stockBST.root = stockBST.removeBST(stockBST.root, symbol);

                break;
            }
            case 3: {
                string symbol;
                cout << "Enter Stock Symbol to Search: ";
                cin >> symbol;

                StockNode* result = stockList.searchStock(symbol);
                if (result != nullptr) {
                    cout << "Stock found:\n";
                    stockList.displayStock(result);
                } else {
                    cout << "Stock not found.\n";
                }

                break;
            }
            case 4:
                stockList.displayStocks();
                break;
            case 5: {
                int count;
                cout << "Enter the number of latest stocks to display: ";
                cin >> count;

                stockList.displayLatestStocks(count);
                break;
            }
            case 6:
                cout << "BST In-Order Traversal:\n";
                stockBST.displayInOrder();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
