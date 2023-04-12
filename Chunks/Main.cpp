#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

//Napisz funkcje chunk(), kt ́ora przyjmie std::vector przechowujacy typ wyliczeniowy
//o nazwie move z mozliwymi wartosciami: left, right oraz idle. Funkcja ma zwrocic std::vector przechowujacy
//trojelementowe tablice tego samego typu, co elementy wektora wej ́sciowego. Je zeli liczba element ́ow wektora wejsciowego jest
//niepodzielna przez 3, to ostatnia trojke dope lnij warto ́sciami idle. Napisz funkcje effectivelyidle(), ktora bedzie mogla przyjac
//obiekt zwracany przez funkcje chunk() oraz sprawdzi, czy wszystkie przekazane tr ́ojki (wspomniane wcze ́sniej trojelementowe tablice)
//efektywnie reprezentuja brak ruchu (brak ruchu jest reprezentowany przez dwa, wykluczajace sie ruchy, czylilewo-prawo lub prawo-lewo
//i dodatkowy ruch idle lub po prostu przez trzy ruchy idle).

//5=====
enum move {
    left, right, idle
};


//5 ====================================

auto chunk(std::vector<move> moves) {
    std::vector<std::array<move, 3>> grp;


    //left = 0, right = 1, idle = 2;
    for (int i = 0; i < moves.size(); i += 3) { //iterujemy co 3 bo inaczej byśmy duplikowali wartości
        std::array<move, 3> element;

        for (int j = 0; j < 3; ++j) {
            if (i + j < moves.size()) {
                element[j] = moves[i + j];
            } else {
                element[j] = idle;
            }
        }
        grp.push_back(element);
    }

    return grp;
}
//Co każdą pętlę zewnętrzną tworzymy nową
//tablicę element do której w pętli wewnętrznej
//przypisujemy wartości z danego vektora moves.

auto effectively_idle(std::vector<std::array<move, 3>> vec) {

    for (int i = 0; i < vec.size(); ++i) {
        std::array<move, 3> element = vec.at(i);
        int manyLefts = 0;
        int manyRights = 0;
        int manyIdles = 0;

        for (int j = 0; j < 3; ++j) {
            if (element[j] == left) {
                manyLefts++;
            }
            if (element[j] == right) {
                manyRights++;
            }
            if (element[j] == idle) {
                manyIdles++;
            }
        }

        if (manyLefts == manyRights && manyIdles != 3) {  //Drugi warunek jest po to, gdy są same wartości idle w tablicy
            std::cout << "Brak ruchu w tablicy nr " << i << std::endl;  //wtedy left(0) = right(0). Zapobiegam temu dodając 2 warunek.
        }else{
            if (manyIdles == 3) {
                std::cout << "Brak ruchu w tablicy nr " << i << std::endl;
            }
        }


    }
}

int main() {
  
  
    //5 ===========
    std::vector<move> vecMove = {move::left, move::right, move::idle,  //0 brak ruchu
                                 move::right, move::left, move::idle,  //1 brak ruchu
                                 move::idle, move::idle, move::idle,   //2 brak ruchu
                                 move::right, move::right, move::left, //3 ruch
                                 move::left};                          //4 dopełnienie + ruch

    std::vector<std::array<move, 3>> triple = chunk(vecMove);
    effectively_idle(triple);
    return 0; 
}
