#include <iostream>

struct Node {
    int data;
    Node* next;

    explicit Node(int val, Node* nxt = nullptr)
        : data(val), next(nxt) {
    }
};

class SinglyLinkedList {
private:
    Node* head;

    static void freeChain(Node* node) {
        while (node != nullptr) {
            Node* temp = node;
            node = node->next;
            delete temp;
        }
    }

    static bool containsValue(Node* listHead, int value) {
        Node* curr = listHead;
        while (curr != nullptr) {
            if (curr->data == value) {
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    static void appendToChain(Node*& outHead, Node*& outTail, int value) {
        Node* newNode = new Node(value);
        if (outHead == nullptr) {
            outHead = outTail = newNode;
        }
        else {
            outTail->next = newNode;
            outTail = newNode;
        }
    }

public:
    SinglyLinkedList() : head(nullptr) {}

    ~SinglyLinkedList() {
        freeChain(head);
    }

    Node* getHead() const {
        return head;
    }

    void pushBack(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Node* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = newNode;
    }

    
    Node* clone() const {
        Node* clonedHead = nullptr;
        Node* clonedTail = nullptr;
        Node* curr = head;
        while (curr != nullptr) {
            appendToChain(clonedHead, clonedTail, curr->data);
            curr = curr->next;
        }
        return clonedHead;
    }

    
    Node* operator+(const SinglyLinkedList& other) const {
        Node* resultHead = nullptr;
        Node* resultTail = nullptr;

        Node* curr = head;
        while (curr != nullptr) {
            appendToChain(resultHead, resultTail, curr->data);
            curr = curr->next;
        }

        curr = other.head;
        while (curr != nullptr) {
            appendToChain(resultHead, resultTail, curr->data);
            curr = curr->next;
        }

        return resultHead;
    }

    
    Node* operator*(const SinglyLinkedList& other) const {
        Node* resultHead = nullptr;
        Node* resultTail = nullptr;

        Node* curr = head;
        while (curr != nullptr) {
            if (containsValue(other.head, curr->data) && !containsValue(resultHead, curr->data)) {
                appendToChain(resultHead, resultTail, curr->data);
            }
            curr = curr->next;
        }

        return resultHead;
    }

    static void printChain(Node* node) {
        while (node != nullptr) {
            std::cout << node->data << " -> ";
            node = node->next;
        }
        std::cout << "nullptr\n";
    }

    static void destroyChain(Node* node) {
        freeChain(node);
    }
};

int main() {
    system("chcp 1251>null");
    SinglyLinkedList list1;
    list1.pushBack(1);
    list1.pushBack(2);
    list1.pushBack(4);
    list1.pushBack(6);

    SinglyLinkedList list2;
    list2.pushBack(2);
    list2.pushBack(4);
    list2.pushBack(8);

    std::cout << "Список 1: ";
    SinglyLinkedList::printChain(list1.getHead());

    std::cout << "Список 2: ";
    SinglyLinkedList::printChain(list2.getHead());

    Node* clonedHead = list1.clone();
    std::cout << "Клон списку 1: ";
    SinglyLinkedList::printChain(clonedHead);

    Node* unionHead = list1 + list2;
    std::cout << "Об'єднання (list1 + list2): ";
    SinglyLinkedList::printChain(unionHead);

    Node* intersectionHead = list1 * list2;
    std::cout << "Спільні елементи (list1 * list2): ";
    SinglyLinkedList::printChain(intersectionHead);

    SinglyLinkedList::destroyChain(clonedHead);
    SinglyLinkedList::destroyChain(unionHead);
    SinglyLinkedList::destroyChain(intersectionHead);

    return 0;
}
