#pragma once
#include "Army.h"
#include <string>
using std::string;

class Troop:public Army {
protected:
    //Each troop has a specific housing space, you can think of it like weight
    int housing;
    static int count; // [18] Static variable for total space of troops
public:
    Troop(string name, long int hp, int level, long int dps, int housing, Type type);
    Troop(const Troop &t);
    virtual void display() override;
    void describe();
    bool operator ==(const Troop &t) const;
    Troop& operator =(const Troop &source);
    static void total_troops();
};
