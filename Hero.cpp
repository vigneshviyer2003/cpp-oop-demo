#include "Hero.h"
#include <iostream>
using namespace std;

Hero::Hero(string name, long int hp, int level, long int dps, string ability_name, Type type): Army(name,hp,level,dps,type), Ability(ability_name) {}

void Hero::display() {
    cout << "Name: " << name << endl;
    cout << "HP: " << hp << endl;
    cout << "Damage per second: " << dps << endl; 
    cout << "Level: " << level << endl;
    cout << "Type: " << type_name(type) << endl;
    cout << "Ability: " << ability_name << "\n\n";
}

void Hero::switch_ability1(Hero h) {
    h.ability_name = "Invisibility";
    cout << "Ability didn't switch.\n";
    h.display();
}

void Hero::switch_ability2(Hero &h) {
    h.ability_name = "Giant Gauntlet";
    cout << "Ability switched.\n";
    h.display();
}

Hero Hero::operator+(const Hero &h) {
    cout << name << " acquried " << h.name << "'s " << h.ability_name << " for it's duration.\n";
    return Hero(name, hp, level, dps, ability_name + " & " + h.ability_name, type);
}

bool Hero::operator <(const Hero &h) const {
    return this->name < h.name;
}

bool Hero::operator==(const Hero &h) const {
    return this->name == h.name;
}