#include <iostream>
#include <string>

template<typename ValueType>
class MyList
{
private:
    struct Node {
        ValueType data;
        Node* next;
        Node* prev;
        
        Node(const ValueType& val) : data(val), next(nullptr), prev(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    int list_size;

public:
    MyList() : head(nullptr), tail(nullptr), list_size(0) {}
    
    MyList(MyList &&obj) noexcept {
        head = obj.head;
        tail = obj.tail;
        list_size = obj.list_size;
        obj.head = nullptr;
        obj.tail = nullptr;
        obj.list_size = 0;
    }
    
    MyList(const MyList &obj) {
        head = nullptr;
        tail = nullptr;
        list_size = 0;
        
        Node* current = obj.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }
    
    ~MyList() {
        clear();
    }
    
    MyList& operator=(const MyList &obj) {
        if (this != &obj) {
            clear();
            Node* current = obj.head;
            while (current != nullptr) {
                push_back(current->data);
                current = current->next;
            }
        }
        return *this;
    }
    
    MyList& operator=(MyList &&obj) noexcept {
        if (this != &obj) {
            clear();
            head = obj.head;
            tail = obj.tail;
            list_size = obj.list_size;
            obj.head = nullptr;
            obj.tail = nullptr;
            obj.list_size = 0;
        }
        return *this;
    }

    void push_back(const ValueType &value) {
        Node* new_node = new Node(value);
        if (tail == nullptr) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        list_size++;
    }
    
    void pop_back() {
        if (tail == nullptr) return;
        
        Node* to_delete = tail;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete to_delete;
        list_size--;
    }
    
    void push_front(const ValueType &value) {
        Node* new_node = new Node(value);
        if (head == nullptr) {
            head = tail = new_node;
        } else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        list_size++;
    }
    
    void pop_front() {
        if (head == nullptr) return;
        
        Node* to_delete = head;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete to_delete;
        list_size--;
    }
    
    ValueType &front() const {
        return head->data;
    }
    
    ValueType &back() const {
        return tail->data;
    }
    
    void insert(int index, const ValueType &value) {
        if (index <= 0) {
            push_front(value);
            return;
        }
        if (index >= list_size) {
            push_back(value);
            return;
        }
        
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        
        Node* new_node = new Node(value);
        new_node->prev = current->prev;
        new_node->next = current;
        current->prev->next = new_node;
        current->prev = new_node;
        list_size++;
    }
    
    void erase(int index) {
        if (index < 0 || index >= list_size) return;
        
        if (index == 0) {
            pop_front();
            return;
        }
        if (index == list_size - 1) {
            pop_back();
            return;
        }
        
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        list_size--;
    }
    
    int size() const {
        return list_size;
    }
    
    bool empty() const {
        return list_size == 0;
    }
    
    void clear() {
        while (head != nullptr) {
            Node* next = head->next;
            delete head;
            head = next;
        }
        tail = nullptr;
        list_size = 0;
    }

    void link(const MyList &obj) {
        Node* current = obj.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }
    
    MyList cut(int index) {
        MyList result;
        
        if (index <= 0) {
            result.head = head;
            result.tail = tail;
            result.list_size = list_size;
            head = tail = nullptr;
            list_size = 0;
            return result;
        }
        
        if (index >= list_size) {
            return result;
        }
        
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        
        result.head = current;
        result.tail = tail;
        result.list_size = list_size - index;
        
        tail = current->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        }
        current->prev = nullptr;
        
        list_size = index;
        
        return result;
    }
};

int main() {
    std::string command;
    MyList<int> lists[15];
    
    while (std::cin >> command) {
        if (command == "new") {
            int id;
            std::cin >> id;
            lists[id] = MyList<int>();
        }
        else if (command == "push_back") {
            int id, value;
            std::cin >> id >> value;
            lists[id].push_back(value);
        }
        else if (command == "pop_back") {
            int id;
            std::cin >> id;
            lists[id].pop_back();
        }
        else if (command == "push_front") {
            int id, value;
            std::cin >> id >> value;
            lists[id].push_front(value);
        }
        else if (command == "pop_front") {
            int id;
            std::cin >> id;
            lists[id].pop_front();
        }
        else if (command == "insert") {
            int id, index, value;
            std::cin >> id >> index >> value;
            lists[id].insert(index, value);
        }
        else if (command == "erase") {
            int id, index;
            std::cin >> id >> index;
            lists[id].erase(index);
        }
        else if (command == "size") {
            int id;
            std::cin >> id;
            std::cout << lists[id].size() << std::endl;
        }
        else if (command == "get") {
            int id, index;
            std::cin >> id >> index;
            MyList<int> temp = lists[id];
            for (int i = 0; i < index; i++) {
                temp.pop_front();
            }
            std::cout << temp.front() << std::endl;
        }
        else if (command == "print") {
            int id;
            std::cin >> id;
            MyList<int> temp = lists[id];
            while (!temp.empty()) {
                std::cout << temp.front();
                temp.pop_front();
                if (!temp.empty()) std::cout << " ";
            }
            std::cout << std::endl;
        }
        else if (command == "link") {
            int id1, id2;
            std::cin >> id1 >> id2;
            lists[id1].link(lists[id2]);
        }
        else if (command == "cut") {
            int id1, id2, index;
            std::cin >> id1 >> id2 >> index;
            lists[id2] = lists[id1].cut(index);
        }
    }
    
    return 0;
}
