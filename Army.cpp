#include "Army.h"
#include <iostream>
using namespace std;

Army::Army(string name, long int hp, int level,long int dps, Type type): name(name), hp(hp), level(level), dps(dps), type(type) {}

Army::~Army() {
    cout << name << " was destroyed!\n";
}


string Army::type_name(Type t) {
    switch (t) {
        case Type::flying: return "Flying";
        case Type::ground: return "Ground";
    }
    return "Unknown";
}

Army::Type Army::get_type() const {
    return type;
}

void Army::describe() {
    cout << name << " is a unit of the army.\n\n";
}

void Army::disp_army(Army *army[], int size) {
    for(int i = 0; i < size; i++) {
        army[i]->display();
    }
}

void Army::upgrade() {
    if(level<max_level) {
        hp = hp + (hp * upgrade_rate / 100);
        dps = dps + (dps * upgrade_rate / 100);
        level++;
        cout << "Upgraded " << name << " by 1 level.\n";
        display();
    }
    else {
        cout << name << " is already at a max level";
        display();
    } 
}

void Army::self_upgrade() {
    apply_upgrade(*this);
}

void apply_upgrade(Army &a) {
    a.upgrade();
}

int Army::show_level() const {
    return level;
}

void Army::show_level(const Army &A) {
    cout << "Level of " << A.name << " is " << A.level << " by passing through const refernce" << "\n\n";
}
