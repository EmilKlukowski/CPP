#include <iostream>
#include <fstream>
#include "sstream"
#include "algorithm"
#include "vector"
#include "iostream"
#include <string>
#include <cmath>
#include <random>

using std::endl, std::vector, std::ofstream, std::ifstream, std::string, std::cout, std::cin;


struct Student {
    string imie;
    string nazwisko;
    int numerStudenta;
    int semestr;

};

//=====================================================================
//Funkcja "zmienImieKopia" pobiera kopiÄ™ obiektu Student,
//wiÄ™c zmiana wartoĹ›ci pola "imie" w tej funkcji nie wpĹ‚ynie
//na oryginalny obiekt Student.

void zmienImieKopia(Student s1, string noweImie) {
    s1.imie = noweImie;
}

//=====================================================================
//Funkcja "zmienImieReferencja" pobiera referencjÄ™ do obiektu Student,
//wiÄ™c zmiana wartoĹ›ci pola "imie" w tej funkcji wpĹ‚ynie na oryginalny
//obiekt Student. Jezeli dodamy slowo const przed student to nie bÄ™dziemy
//mogli zmienic imienia.

void zmienImieReferencja(Student &s1, string noweImie) {
    s1.imie = noweImie;

}

//=====================================================================
//Funkcja "zmienImieWskaznik" pobiera wskaĹşnik do obiektu Student,
//wiÄ™c musimy uĹĽyÄ‡ operatora "->" aby odwoĹ‚aÄ‡ siÄ™ do pola "imie"
//obiektu wskazywanego przez ten wskaĹşnik. Zmiana wartoĹ›ci pola "imie"
//w tej funkcji rĂłwnieĹĽ wpĹ‚ynie na oryginalny obiekt Student.

void zmienImieWskaznik(Student *s1, string noweImie) {
    s1->imie = noweImie;
}


//const daje nam pewnosc ze oryginalny obiekt nie zostanie zmieniony
auto sprawdzSemestr(const vector<Student> &grupa) {

    int semestr = grupa[0].semestr;

    for (auto el: grupa) {
        if (el.semestr != semestr) {
            return false;
        }
    }
    return true;
}

//3 =====================================================================
struct Point {
    double x;
    double y;

    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }

public:
    auto showCoordinates() {
        cout << "[ " << this->x << ", " << this->y << " ]" << endl;
    }

    auto showDistanceFrom(double givenX, double givenY) {


        return std::sqrt((this->x - givenX) * (this->x - givenX) +
                         (this->y - givenY) * (this->y - givenY));
    }

    auto changeCoordinates(double givenX, double givenY) {
        this->x = givenX;
        this->y = givenY;
    }
};


//4 ========================================

auto findTheSmallestRectangle(vector<Point> points){
    double min_x = points[0].x;
    double max_x = points[0].x;
    double min_y = points[0].y;
    double max_y = points[0].y;

    for (auto point : points) {
        if(point.x<min_x){
            min_x = point.x;
        }

        if(point.x>max_x){
            max_x = point.x;
        }

        if(point.y<min_y){
            min_y = point.y;
        }

        if(point.y>max_y){
            max_y=point.y;
        }
    }

    cout<<"Top left corner: [" << min_x << ", " << max_y << "]" << endl;
    cout<<"Top right corner: [" << max_x << ", " << max_y << "]" << endl;
    cout<<"Bottom left corner: [" << min_x << ", " << min_y << "]" << endl;
    cout<<"Bottom right corner: [" << max_x << ", " << min_y << "]" << endl;
}



int main() {
//    vector<Student> grupa = {
//            {"Adam",  "Kowalski",  123, 1},
//            {"Ewa",   "Nowak",     234, 1},
//            {"Jan",   "Jan",       345, 2},
//            {"Anna",  "WĂłjcik",   456, 1},
//            {"Piotr", "Kaczmarek", 456, 1}
//    };
//
//    std::cout << sprawdzSemestr(grupa);

    //3=============
//    Point p1 = Point(0, 2);
//    p1.showCoordinates();
//    cout << p1.showDistanceFrom(3, 4) << endl;
//    p1.changeCoordinates(3, 5);
//    p1.showCoordinates();

    //4=================

    // create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // define the distribution to be used
    std::uniform_int_distribution<int> dis(-10, 10);


    vector<Point> points;

    for (int i = 0; i < 20; ++i) {
        double random_digit = dis(gen);
        double random_digit2 = dis(gen);
        Point p = Point(random_digit, random_digit2);
        points.push_back(p);
    }


    for (Point point : points) {
        point.showCoordinates();
    }

    findTheSmallestRectangle(points);

    return 0;
}
