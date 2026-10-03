#include <iostream>
using namespace std;

class Army {
private:
    int upgrade_rate = 5, max_level = 20; 
    // Max level can only be 20 and each level increases stats only by 5%
protected:
    string name;
    long int hp, dps;
    int level;
public:
    Army(string name, long int hp, int level,long int dps): name(name), hp(hp), level(level), dps(dps) {}
    virtual ~Army() {
        cout << name << " was destroyed!\n";
    }
    virtual void display() = 0;
    void upgrade(); // Upgrade should be common to the entire army and only 1 level at a time
    void upgrade(int i); // Doing multi-level upgrades with overloading
    static void disp_army(Army *army[], int size);
};

void Army::disp_army(Army *army[], int size) {
    for(int i = 0; i < size; i++) {
        army[i]->display();
        army[i] = nullptr;
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
        cout << name << " is already at a max level of " << max_level;
        display();
    } 
}

void Army::upgrade(int i) {
    if(level+i<=max_level) {
        hp = hp + (hp * i * upgrade_rate / 100);
        dps = dps + (dps * i * upgrade_rate / 100);
        level = level + i;
        cout << "Upgraded " << name << " by " << i << " levels.\n";
        display();
    }
    else {
        cout << name << " is already at a max level of " << max_level;
        display();
    } 
}

// 2nd Parent of Hero as only Heroes can have abilities
class Ability {
protected:
    string ability_name;
public:
    Ability(string ability_name): ability_name(ability_name) {}
};

class Hero:public Army, public Ability{
protected:
public:
    Hero(string name, long int hp, int level, long int dps, string ability): Army(name,hp,level,dps), Ability(ability) {}
    void display() override;
};

void Hero::display(){
    cout << "Name: " << name << endl;
    cout << "HP: " << hp << endl;
    cout << "Damage per second: " << dps << endl; 
    cout << "Level: " << level << endl;
    cout << "Ability: " << ability_name << endl << endl;
}

class Troop:public Army {
protected:
 int housing;
public:
    Troop(string name, long int hp, int level, long int dps, int housing): Army(name,hp,level,dps), housing(housing) {}
    void display() override;
};

void Troop::display(){
    cout << "Name: " << name << endl;
    cout << "HP: " << hp << endl;
    cout << "Damage per second: " << dps << endl; 
    cout << "Level: " << level << endl;
    cout << "Housing Space: " << housing << endl << endl;
}

int main() {
    Hero king("Barbarian King", 20000, 1, 200, "Spiky Ball");
    king.upgrade();

    Army *ptr = new Troop("Dragon", 4000, 1, 100, 20);
    ptr->upgrade(2);
    delete ptr;
    ptr = nullptr;

    Troop t1("Barbarian", 100, 1, 6, 1);
    Troop t2("Archer", 100, 1, 5, 1);
    Troop t3("Balloon", 1500, 1, 20, 5);
    Army *army[3] = {&t1, &t2, &t3};
    Army::disp_army(army, 3);
    return 0;
}