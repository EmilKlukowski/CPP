#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

using std::cout, std::cin, std::vector, std::set, std::string;



auto filtered(vector<string> vec, set<string> set1){


    auto toRemove = std::ranges::remove_if(vec, [set1](string el)->bool{
        return set1.contains(el);
    });

    vec.erase(toRemove.begin(), toRemove.end());


    //2 opcja
//    auto toRemove = std::remove_if(vec.begin(), vec.end(), [set1](string el)->bool{
//        return set1.contains(el);
//    });
//
//    vec.erase(toRemove, vec.end());

    return vec;
}




int main() {

    // =================================== WEJSCIOWKA ====================================
    {/*
        // 0  1  2  3  4  5  6  7    indeks 3, 4, 5 wylatuje czyli wartosci 7,3,8
        vector<int> vec = {5, 2, 1, 7, 3, 8, 2, 9};
        vec.erase(vec.begin() + 3, vec.end() - 2);
        for (auto el: vec) {
            cout << el << " ";
        }

        cout << std::endl;

        //2 zadanie======================

        vector<int> vec2 = {5, 2, 1, 7, 3, 8, 2, 9};

        std::ranges::partition(vec2.begin(), vec2.end(), [](int x) -> bool {
            return x % 3 == 0;
        });

        for (auto el: vec2) {
            cout << el << " ";
        }
        */}


    //Zadanie 1 =======================================

    vector<int> liczby = {3, 4, 2, 5, 6, 1};

    auto set1 = set<int>(liczby.begin(), liczby.end());
    auto posortowaneLiczby = set1;

    for (auto e: posortowaneLiczby) {
        cout << e << " ";          //expected output 1, 2, 3, 4, 5, 6
    }

    //Zadanie 2 ========================================
    vector<string> slowa = {"Hej","Czesc", "Witam"};
    auto zakazane = set<string>{"Witam"};

    filtered(slowa, zakazane);

    
    for (auto el : slowa) {
        cout << el;
    }
}