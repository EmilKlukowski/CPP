#include <iostream>
#include "vector";
#include "algorithm"

using namespace std;


class Vehicle {
public:
    double fuel;
    double speed;

public:
    Vehicle(double fuel, double speed) : fuel(fuel), speed(speed) {}

public:
    virtual auto start() -> void {
        if (this->fuel < 0.5) {
            cout << "Could not turn on the vehicle" << endl;
        } else {
            this->speed = 3.5;
            cout << "Vehicle started";
        }
    }
};


class Ship : public Vehicle {
private:
    double bouyancy;

public:
    Ship(double fuel, double speed, double bouyancy) : Vehicle(fuel, speed), bouyancy(bouyancy) {}

public:
    auto start() -> void override {
        if (this->bouyancy < 2) {
            cout << "Ship is sinking, maintenance required";
        } else {
            if (this->fuel < 0.5){
                cout<<"Could not start the ship";
            } else{
                cout<<"Ship started";
            }
        }
    }
};

void startVehicle(Vehicle* vehicle){
    vehicle->start();
}


int main() {
//    Vehicle* vehicle = new Vehicle(0.7, 0.0);
//    Ship* ship = new Ship(0.6, 0.0, 2.5);
//
//    startVehicle(vehicle);
//    cout<<endl;
//    startVehicle(ship);


//    int a = 10;
//    int &b = a;         //referencja
//    //int *c = &a;      //wskaznik
//    int d = 90;
//    b = d;
//    int *c = &a;
//    c = &d;
//    *c = 3;
//
//    //new tworzy obiekty na stercie (heap)
//    //vector<A*> obj = {new A(), new B()};


    return 0;
}
