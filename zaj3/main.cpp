#include <iostream>
#include "vector"
#include "algorithm"
#include <fmt/ranges.h>
#include <wsman.h>

using fmt::print;
using std::cout, std::cin, std::vector, std::endl, std::string;

enum version {even, odd, prime};

//even 0, odd 1, prime 2
auto remove_if_enum(vector<int> vec, version ver){
    switch (ver) {
        case version::even:
        {
            auto toErase = std::ranges::remove_if(vec.begin(), vec.end(), [](int x)->bool{return x%2==0;});
            vec.erase(toErase.begin(), toErase.end());
            break;
        }
        case version::odd:
        {
            auto toErase = std::ranges::remove_if(vec.begin(), vec.end(), [](int x)->bool{return !(x%2==0);});
            vec.erase(toErase.begin(), toErase.end());
            break;
        }
        case version::prime:
        {
            auto toErase = std::ranges::remove_if(vec.begin(), vec.end(), [](int x)->bool{
                if (x <= 1)
                    return false;

                for (int i = 2; i < x; i++)
                    if (x % i == 0)
                        return false;

                return true;
            ;});
            vec.erase(toErase.begin(), toErase.end());
            break;
        }
    }
}

//auto move_by_vowels(vector<string> vec){
//    std::sort(vec.begin(), vec.end(), []()->bool{
//        return true;
//    })
//}


int main() {
    /*int a = 10;
    cout << "żółw" << a << endl;
    print("żółw{}{}\n", a,
          700);                 //do nawiasów klamrowych wstawai się zmienna którą podajemy po zakonczeniu stringa "{}", a

    vector<vector<int>> v = {{9, 3, 8},
                             {4, 9},
                             {1, 2, 3, 4, 5}};
    print("{}\n", v);                            //ten print jest dobry do wyświetlania kontenerów np vektorów.

    //LAMBDA
    //int a = 10;
    auto f2 = [a](int x) -> bool {
        return x % a == 0;
    };

    f2(10);

    vector<int> v1 = {5, 90, 23, 67, 54, 69};
    print("{}\n", v1);
    cout << "Przed ^" << endl;
    std::ranges::sort(v1, [](int x, int y) -> bool { return y > x; });  //jezeli falsz to zamienia za soba wartosci
    print("{}\n", v1);
    cout << "Po ^" << endl;


    //predykat zwraca prawdę lub fałsz
    auto counter = std::ranges::count_if(v1, f2);
    print("{}\n", counter);

    auto range_to_remove = std::ranges::remove_if(v1, f2);
    v1.erase(range_to_remove.begin(), range_to_remove.end());      //remove if duplikuje wartosci wiec trzeba
    print("{}\n", v1);                                             // łapac od kiedy do kiedy usunąc

    auto range_after_part = std::ranges::partition(v1, [](int a) -> bool { return a < 50; });
    print("{}\n", range_after_part);
    */   //notatki z lekcji

    //Zadanie 1 ============================

    vector<int> vec { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    remove_if_enum(vec, even);
    remove_if_enum(vec, odd);
    remove_if_enum(vec, prime);

    for (auto el : vec) {
        std::cout << el << " ";
    }

    //Zadanie 2 ============================




    return 0;
}
