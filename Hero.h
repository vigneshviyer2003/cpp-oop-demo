#pragma once
#include "Army.h"
#include "Ability.h"
#include <string>
using std::string;

class Hero:public Army, public Ability {
protected:
public:
    Hero(string name, long int hp, int level, long int dps, string ability_name, Type type);
    void display() override;
    Hero operator +(const Hero &h);
    bool operator <(const Hero &h) const;
    bool operator ==(const Hero &h) const;
    void switch_ability1(Hero h);
    void switch_ability2(Hero &h);
};