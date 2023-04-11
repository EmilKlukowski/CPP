#include <iostream>
#include <vector>
#include <string>
#include "algorithm"

using std::cout, std::cin, std::endl, std::string, std::vector;

#include <vector>

//main -  zwraca integer, nie znajduje sie w klasie
//std -  grupa nazw z ktorej korzystamy, gdy mamy duzo cinów i coutów to std dopisuje nam znaki
//mozemy się go pozbyć bo to denerwujące. //using namespace std --- to nie najbezpieczniejszy sposób.
// using i listujemy czego chcemy uzywać bez pisania std
auto fun() {
    cout << "fun" << endl;
    return 0;                       //returnujemy 0 więc auto obok fun będzie integer;
}

//zadanie 1 =======================================================================
auto countChars(vector<char> v, char c){

    int counter = 0;

    for(int i = 0; i<v.size(); i++){
        if(v.at(i) == c){
            counter++;
        }
    }

    return counter;
}

auto countChars(string s, char c){

    int counter = 0;

    for(int i = 0; i<s.size(); i++){
        if(s.at(i) == c){
            counter++;
        }
    }

    return counter;
}

//zadanie 2 ===============================================================

auto imiona(){
    //tworzymy vector

    auto names = vector<string>(10);

    for (int i = 0; i < 10; ++i) {
        string givenName;
        cout << "Podaj imie";
        cin >> givenName;

        auto found = false;

        for(auto name:names){
            if(name == givenName){
                found = true;
                break;
            }

            if(found==false){
                names.push_back(givenName);
            }
        }
    }

    for(auto name:names){
        cout << name;
    }
}



int main() {
//    auto s = string("Lorem ipsum dolor sit amet");
//
//    {   //pojedyncze literki
//        s.at(0);
//        s[0];
//    }
//    vector<int> v = {5, 21, 23};
//    v.push_back(21);        //dodanie do konca tablicy 21;
//    v[0] = 19;              //zamiana pierwszego elementu z 5 na 10;
//    v.at(0) = 11;        //zamiana pierwszego elementu z 10 na 11 --> bezpieczniejsze
//    v.size();               //rozmiar vectora;
//    std::ranges::sort(v);
//
//
//
//    for (auto el: v) {              //petla for of przez kazdy element w wektorze
//        cout << el;                     //print kazdego elementu
//        cout << endl;                   //znak nowej linii endl;
//    }

    //test 1 zadania =========================================================

    std::cout << countChars(std::vector<char>{'a', 'l', 'a'}, 'a') << '\n'
              << countChars("", 'a') << '\n'
              << countChars(std::string{'k', 'a', 'j', 'a', 'k'}, 'a') << '\n'
              << countChars(std::string("kajak"), 'k') << '\n'
              << countChars(std::vector<char>{'k', 'a', 'j', 'a', 'k'}, 'j') << '\n'
              << countChars("kajak", 'x') << '\n';
    //=========================================================================================

    imiona();

    return 0;
}
