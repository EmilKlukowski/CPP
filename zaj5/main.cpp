#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include "vector"
#include "algorithm"

using namespace std;

template<typename MyType, typename T>
auto sum(MyType a, T b) -> MyType {
    return a + b;
}


template<typename Lambda>
auto repeat(int n, Lambda l) {
    while (n > 0) {
        l();
        n--;
    }
}

template<typename MyType>
auto printVector(MyType vec) {
    for (auto el: vec) {
        cout << el;
    }
}

template<typename T, typename F>
auto problem6(vector<T> vec, F function){
    vector<T> result;

    for (auto el : vec) {
        result.push_back(function(el));
    }
    return result;
}



auto problem4() {

    string fileName;
    cout << "Podaj nazwe pliku " << endl;
    cin >> fileName;

    ifstream inFile(fileName);

    set<int> linesToRemove;
    string line;
    int start, end;

    cout << "Podaj pary liczb: " << endl;

    while (true) {
        cin >> start;
        if (start == -1) break;
        cin >> end;
        if (end == -1) break;

        for (int i = start; i <= end ; ++i) {
            linesToRemove.insert(i);
        }
    }

    string tempFileName = fileName + ".tmp";
    ofstream tempFile(tempFileName);

    //.count(el);
    //Return Value: The function returns 1 or 0 as the set contains unique elements only.
    //It returns 1 if the value is present in the set container.
    //It returns 0 if it is not present in the container.

    int currentLine = 1;
    while (getline(inFile, line)) {
        if(linesToRemove.count(currentLine) == 0){
            tempFile << line << endl;
        }
        currentLine++;
    }

    inFile.close();
    tempFile.close();

    //funkcja remove przyjmuje const char* więc musimy użyć funkcji c_str();
    remove(fileName.c_str());
    rename(tempFileName.c_str(), fileName.c_str());

    //zapisać do setu przedzialy 9-12 czyli do setu -> 9, 10, 11, 12;
    //potem 3-40 czyli 3,4 .... powtarzają się więc set je przefiltruje;

}

auto problem5() {


    ifstream inFile("liczby.txt");
    ofstream outFile("normalized.txt");

    vector<double> numbers;
    double num;

    while (inFile >> num) {
        numbers.push_back(num);
    }

    double maxNum = *max_element(numbers.begin(), numbers.end());

    for (auto el: numbers) {
        outFile << el / maxNum << endl;
    }

    inFile.close();
    outFile.close();

    return 0;


}


int main() {
    //   std::string path = R"(C:\Users\s27944\CLionProjects\untitled\main.cpp)";
    //    "C:\\Users\\s27944\\CLionProjects\\untitled\\main.cpp";
    //auto text_stream = std::fstream(path, std::ios::in | std::ios::out | std::ios::app);
    //ios app -> append --> zapis na koniec pliku
    //ios trunc czysci plik z danych
    //text stream zwraca 0 lub -cos gdy nie moze odczytac pliku
    //seekg(0) -> wraca na początek pliku(0) (5)-> piaty znak w naszym pliku;
    //showpos() -> pozycja na ktorej się znajdujemy teraz w pliku

//    auto pos = text_stream.showpos;
//    std::string val;
//    while(text_stream >> val){
//
//    }

//    std::getline(text_stream, val);
//    cout<<val << "\n";


//    auto line_stream = std::stringstream(val);
//   char c;

//    while(line_stream>>c)
//       std::cout<<c<<"";

    //1========
//    cout << "Podaj nazwe pliku z projektu";
//    auto path = "C:\\Users\\s27944\\CLionProjects\\untitled\\";
//
//    std::string userpath;
//    cin >> userpath;
//
//    auto txt = ".txt";
//    auto finalPath = path + userpath + txt;
//    auto text_stream = std::fstream(finalPath);
//    int output;
//    int val;
//    int sum = 0;
//
//    while (text_stream >> val) {
//        sum += val;
//    }
//    cout << sum;

    //2==================

//    repeat(10, []() {
//        cout << "Tekst";
//    });

    //3 ================
//    cout << std::endl;
//    std::vector vec = {1, 2, 4, 6, 7, 8};
//
//    printVector(vec);

    //4==================

    //problem4();

    //5 =================

    //problem5();

    //6 ======================

    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto output = problem6(vec, [](int x) { return x * x; }); // wynik: {1, 4, 9, 16, 25}
    for (int x : output) {
        std::cout << x << " ";
    }






    return 0;
}