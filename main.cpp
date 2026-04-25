#include <iostream>
#include <string>
#include "src.hpp"

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
