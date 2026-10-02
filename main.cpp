#include <iostream>
using namespace std;

class Army {
private:
    int upgrade_rate = 10, level_cap = 20; 
    // Cannot upgrade the troop/hero (object) by more than 20 levels and each level increases stats only by 10%
protected:
    string name;
    long int hp, dps;
    int level;
public:
    Army(string name, long int hp, int level,long int dps): name(name), hp(hp), level(level), dps(dps) {}
    virtual void display() = 0;
    virtual ~Army() {
        cout << name << " was destroyed!\n";
    }
    void upgrade(); // Upgrade should be common to the entire army and only 1 level at a time
    void upgrade(int inc); // Doing multi-level upgrades with overloading
};

void Army::upgrade() {
    if(level<level_cap) {
        hp = hp + (hp * upgrade_rate / 100);
        dps = dps + (dps * upgrade_rate / 100);
        level++;
        cout << "Upgraded by 1 level.\n";
        display();
    }
    else {
        cout << "Troop is already at a max level of " << level_cap;
        display();
    } 
}

void Army::upgrade(int i) {
    if(level+i<=level_cap) {
        hp = hp + (hp * i * upgrade_rate / 100);
        dps = dps + (dps * i * upgrade_rate / 100);
        level = level + i;
        cout << "Upgraded by " << i << " levels.\n";
        display();
    }
    else {
        cout << "Troop is already at a max level of " << level_cap;
        display();
    } 
}

class Hero:public Army {
protected:
    string ability; // Only heroes have abilities
public:
    Hero(string name, long int hp, int level, int dps, string ability): Army(name,hp,level,dps), ability(ability) {}
    void display() override{
        cout << "Name: " << name << endl;
        cout << "HP: " << hp << endl;
        cout << "Damage per second: " << dps << endl; 
        cout << "Level: " << level << endl;
        cout << "Ability: " << ability << endl;
    }
};

int main() {
    Hero Barb_King("Barbarian King", 20000, 1, 200, "Power Strike");
    Barb_King.upgrade();
    return 0;
}