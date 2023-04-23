#include <iostream>
#include "algorithm"
#include "vector"
#include "filesystem"
#include <fstream>
#include <iostream>
#include <fstream>

using std::vector, std::string, std::cout, std::cin, std::endl;

//polimorphism ==================================================================================

struct Person {
    std::string name, surname;

    Person(const std::string &name, const std::string &surname) : name(name), surname(surname) {}

    //virtual mowi ze ktos moze odziedziczyc
    virtual auto info() const -> void {
        std::cout << name << " " << surname << "\n";
    }
};

struct Student : Person {
    int number;

    Student(const std::string &name, const std::string &surname, int number) :
            Person(name, surname), number(number) {}

    auto info() const -> void override {
//        name = "a";
        std::cout << number << " ";
        Person::info();   //polazuje po kim dziediczymy
    }
};

auto getInfo(const Person &p) {
    p.info();
}

//1 ==============================
auto zadanie1() {
    std::filesystem::path sciezka;
    cin >> sciezka;

    if (std::filesystem::is_directory(sciezka)) {
        auto dir_it = std::filesystem::recursive_directory_iterator(sciezka);

        for (auto el: dir_it) {
            if (el.path().extension() == ".txt") {
                std::ifstream inFile(el.path());
                string line;

                while (getline(inFile, line)) {
                    cout << line << "\n";
                }
                inFile.close();
                break;
            }
        }
    }
}

//2 ======================================
void zadanie2(const std::filesystem::path &dir_path, int level = 0) {

    for (auto el: std::filesystem::directory_iterator(dir_path)) {
        if (el.is_directory()) {
            cout << std::string(level, ' ') << "[+] " << el.path().filename() << std::endl;
            zadanie2(el.path(), level + 2);
        } else {
            std::cout << std::string(level, ' ') << "- " << el.path().filename() << std::endl;
        }
    }

}


class Instrumnent {

public:
    vector<string> material;
    string tuning;

public:
    Instrumnent(const string &tuning, const vector<string> &material) {
        this->tuning = tuning;
        this->material = material;
    }


    auto startPlaying(const string &song) {
        return song;
    }

    auto maintenance() {
        cout << "Instrument fixed." << endl;
    }

};

class Saxophone : Instrumnent {
public:
    Saxophone(const string &tuning, const vector<string> &material) : Instrumnent(tuning, material) {
        this->tuning = tuning;
        this->material = material;
    }

    auto maintenance() {
        cout << "Crushions changed, mechanism oiled.";
    }
};

class Violin : Instrumnent {
public:
    Violin(const string &tuning, const vector<string> &material) : Instrumnent(tuning, material) {
        this->tuning = tuning;
        this->material = material;
    }

    auto maintenance() {
        cout << "Strings changed and tuned.";
    }
};


class Piano : Instrumnent {
public:
    Piano(const string &tuning, const vector<string> &material) : Instrumnent(tuning, material) {
        this->tuning = tuning;
        this->material = material;
    }

    auto maintenance() {
        cout << "Hammers attuned.";
    }
};

//4=====================================
enum STATUS {
    NORMAL,
    CHARMED,
    UNCONCIOUS,
    DEAD
};

class Character {
public:
    int strength;
    int wisdom;
    int charisma;
    int level;
    int status;
    int hp;

public:
    Character() {
        int strength = 10;
        int wisdom = 10;
        int charisma = 10;
        int hp = 10;
        int level = 10;
        STATUS status;
    }


public:
    Character(int strength, int wisdom, int charisma, int hp, int level, STATUS status) {
        this->strength = strength;
        this->wisdom = wisdom;
        this->charisma = charisma;
        this->hp = hp;
        this->level = level;
        this->status = status;
    }

    Character(const Character &c) :
            strength(c.strength), wisdom(c.wisdom), charisma(c.charisma),
            hp(c.hp), level(c.level), status(c.status) {}

public:
    auto attack(Character c) {
        c.hp -= 1;
        cout << "Character attacked with fist";
    }

};

//5==============================
class Mage : Character {

public:
    Mage(int strength, int wisdom, int charisma, int hp, int level, STATUS status) {
        this->strength = strength;
        this->wisdom = wisdom;
        this->charisma = charisma;
        this->hp = hp;
        this->level = level;
        this->status = status;
    }

public:
    auto attack(Character c) {
        if (c.status != UNCONCIOUS) {
            c.status = UNCONCIOUS;
        }
    }
};

class Warrior : Character {

    Warrior(int strength, int wisdom, int charisma, int hp, int level, STATUS status) {
        this->strength = strength;
        this->wisdom = wisdom;
        this->charisma = charisma;
        this->hp = hp;
        this->level = level;
        this->status = status;
    }

    auto attack(Character c) {
        c.hp -= this->level + this->strength;
    }
};

int main() {
//   std::filesystem::path home = std::filesystem::current_path();
//    home.parent_path(); //folder wyzej niz się znajdujemy

//    home.append("Data");



    //jesli jest direm to tworzymy iterator
//    if(std::filesystem::is_directory(home)){
//        //auto dir_it = std::filesystem::directory_iterator(home);        //sprawdza czy są foldery w folderach
//        auto dir_it = std::filesystem::recursive_directory_iterator(home);  //i w nie wchodzi
//        for (auto el : dir_it) {
//            if(el.path().extension()==".txt"){
//                cout<<el.path().filename()<<"\n";
//                auto stream = std::fstream(el.path());
//            }
//        }
//    }
//    cout << home << endl;

//    Student s= Student("A","B",1);
//    Person p= Student("C","D",2);
//    Person *p2 = new Student("E","F",3);
//    getInfo(s);
//    s.info();
//    p.info();
//    p2->info();

    //zadanie1();
    
    std::filesystem::path path = R"(D:\Users\Emil\PJC)";
    zadanie2(path, 0);
    


    return 0;
}
