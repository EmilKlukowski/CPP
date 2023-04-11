#include <iostream>

using namespace std;

#include <vector>
#include <string>
#include <algorithm>

auto sort_bigger_half(vector<int> vec) {
    auto koniec1 = vec.size();
    auto polowaVec = 0;
    auto suma1pol = 0;
    auto suma2pol = 0;

    if (vec.size() % 2 == 0) {
        polowaVec = vec.size() / 2;
    } else {
        polowaVec = vec.size() / 2 + 1;
    }


    for (int i = 0; i < polowaVec; i++) {
        suma1pol += vec.at(i);
    }

    for (int i = polowaVec; i < vec.size(); ++i) {
        suma2pol += vec.at(i);
    }

    if (suma1pol >= suma2pol) {
        ranges::sort(vec.begin(), vec.begin() + koniec1);
    } else {
        ranges::sort(vec.begin() + polowaVec, vec.end());
    }


    for (auto e: vec) {
        cout << e << " ";
    }

    //return vec;
}
//2 =============================

auto erase_n_biggest(vector<int> vec, int n){
    if(n > vec.size()){
        return vec = {};
    }else{
        ranges::sort(vec.begin(), vec.end());

        for (int i = 0; i < n; ++i) {
            vec.erase(vec.end()-1);
            //np 5 ostatnich
        }
    }
}


int main() {
    vector<int> vec = {2, 1, 6, 10, 5};
    sort_bigger_half(vec);

    return 0;
}
