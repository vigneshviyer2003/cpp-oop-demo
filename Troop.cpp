#include "Troop.h"
#include <iostream>
using namespace std;

int Troop::count = 0; // [18] Initialise static member

Troop::Troop(string name, long int hp, int level, long int dps, int housing, Type type)
    : Army(name, hp, level, dps, type), housing(housing) {
    count += housing; // Update total housing space
}

Troop::Troop(const Troop &t)
    : Troop(t.name, t.hp, t.level, t.dps, t.housing, t.type) {} // Copy constructor

void Troop::display() {
    cout << "Name: " << name << endl;
    cout << "HP: " << hp << endl;
    cout << "Damage per second: " << dps << endl;
    cout << "Level: " << level << endl;
    cout << "Type: " << type_name(type) << endl;
    cout << "Housing Space: " << housing << "\n\n";
}

void Troop::describe() {
    cout << name << " is a troop with housing space " << housing << ".\n\n";
}

bool Troop::operator==(const Troop &t) const {
    // Compare name, level and housing space
    return (t.name == name) && (t.level == level) && (t.housing == housing);
}

Troop& Troop::operator=(const Troop &source) {
    if (this != &source) { // Prevent self-assignment
        count += source.housing - housing;
        name = source.name;
        hp = source.hp;
        dps = source.dps;
        level = source.level;
        type = source.type;
        housing = source.housing;
    }
    return *this; // Allows chained assignment
}

void Troop::total_troops() {
    cout << "Total space of army is: " << count << endl;
}