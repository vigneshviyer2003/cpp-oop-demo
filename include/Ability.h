#pragma once
#include <string>
using std::string;

// 2nd Parent of Hero as only Heroes can have abilities
class Ability {
protected:
    string ability_name;
public:
    Ability(string ability_name);
};
