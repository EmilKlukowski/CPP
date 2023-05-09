#include <iostream>
#include "algorithm"
#include "vector"
#include "filesystem"
#include <fstream>
#include <iostream>
#include <fstream>
#include <utility>

using std::vector, std::string, std::cout, std::cin, std::endl;


class Person {
    static size_t ID;
    string name;
    size_t id;
    std::vector<const Person *> friends;

public:
    explicit Person(string n) : name(std::move(n)), id(ID++) {}

    void makeFriends(Person &p) {
        if (this == &p) {
            return;
        }

        for (auto el: this->friends) {
            if (el == &p) {
                return;
            }
        }

        friends.push_back(&p);
        p.friends.push_back(this);
    }

    void listOfFriends() {
        for (auto el: friends) {
            cout << el->name << " id: " << this->id << endl;
        }
    }

    vector<const Person *> friendsOfFriends() {
        vector<const Person *> toReturn;

        for (const auto &myFriend: this->friends) {
            for (const auto &theirFriend: myFriend->friends) {
                if (theirFriend != this &&
                    std::find(friends.begin(), friends.end(), theirFriend) == friends.end() &&
                    std::find(toReturn.begin(), toReturn.end(), theirFriend) == toReturn.end()) {
                    toReturn.push_back(theirFriend);
                }

            }
        }

        return toReturn;
    }

    string info() const {
        std::stringstream ss;

        ss << "Name: " << name << "\n";
        ss << "ID: " << id << "\n";
        ss << "Friends: ";
        for (const auto& el : friends) {
            ss << el->name << ", ";
        }

        return ss.str();
    }
};

//2========================
struct Node{
    int data;
    Node* next;

    static bool add(Node*& head, int data){
        if(head == nullptr){
            head = new Node{data, nullptr};
            return true;
        }
        if(head->data == data){
            return false;
        }
        Node* current = head;

        while(current->next != nullptr){
            if(current->next->data == data){
                return false;
            }
            current = current->next;
        }
        head = new Node{data, head};
        return true;
    }

    static size_t size(const Node* head) {
        size_t count = 0;
        while (head != nullptr) {
            count++;
            head = head->next;
        }
        return count;
    }

    static void printList(const Node* head) {
        while (head != nullptr) {
            std::cout << head->data << " ";
            head = head->next;
        }
        std::cout << std::endl;
    }

    static void clear(Node*& head) {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            std::cout << "DEL: " << temp->data << " " << endl;
            delete temp;
        }
    }
};





int main(){
//    Person john{"John"}, mary{"Mary"}, kitty{"Kitty"},jill{"Jill"}, bob{"Bob"},   eve{"Eve"};
//
//    john.makeFriends(mary);
//    john.makeFriends(bob);
//    john.makeFriends(eve);
//    bob.makeFriends(john);
//    bob.makeFriends(jill);
//    bob.makeFriends(eve);
//    eve.makeFriends(mary);
//    eve.makeFriends(kitty);
//
//    john.listOfFriends();
//    std::cout << "Friends of John’s friends -> ";
//
//    for (const Person* p : john.friendsOfFriends())
//        std::cout << p->info() << " ";std::cout << std::endl;
//    return 0;

//Problem 2 ====================================

    int tab[] = {1, 4, 1, 3, 5};
    Node* head = nullptr;
    for (size_t i = 0, e = std::size(tab); i != e; ++i) {
        bool b = Node::add(head, tab[i]);
        std::cout << tab[i] << (b ? " " : " NOT ") << "added" << std::endl;
    }
    std::cout << "Size of the list: " << Node::size(head) << std::endl;
    Node::printList(head);
    Node::clear(head);
}
