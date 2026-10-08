#include <iostream>
#include <string>
#include <memory>
using namespace std;

// Parent  
class Army {
private:
    int upgrade_rate = 5, max_level = 20; 
    // Max level can only be 20 and each level increases stats only by 5%
protected:
    string name;
    long int hp, dps;
    int level;
public:
    Army(string name, long int hp, int level,long int dps);
    virtual ~Army() {
        cout << name << " was destroyed!\n";
    }
    virtual void display() = 0;
    void upgrade(); // Upgrade should be common to the entire army and only 1 level at a time
    static void disp_army(Army *army[], int size);
    int show_level() const;
    static void show_level(const Army &A);
};

Army::Army(string name, long int hp, int level,long int dps): name(name), hp(hp), level(level), dps(dps) {}

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

int Army::show_level() const {
    return level;
}

void Army::show_level(const Army &A) {
    cout << "Level of " << A.name << " is " << A.level << " by passing through const refernce" << "\n\n";
}

// 2nd Parent of Hero as only Heroes can have abilities
class Ability {
protected:
    string ability_name;
public:
    Ability(string ability_name);
};

Ability::Ability(string ability_name): ability_name(ability_name) {}

class Hero:public Army, public Ability {
protected:
public:
    Hero(string name, long int hp, int level, long int dps, string ability);
    void display() override;
    void switch_ability1(Hero h);
    void switch_ability2(Hero &h);
};

Hero::Hero(string name, long int hp, int level, long int dps, string ability): Army(name,hp,level,dps), Ability(ability) {}

void Hero::display() {
    cout << "Name: " << name << endl;
    cout << "HP: " << hp << endl;
    cout << "Damage per second: " << dps << endl; 
    cout << "Level: " << level << endl;
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

class Troop:public Army {
protected:
    //Each troop has a specific housing space, you can think of it like weight
    int housing;
    static int count;
public:
    Troop(string name, long int hp, int level, long int dps, int housing);
    void display() override;
    static void total_troops();
};

int Troop::count = 0;

Troop::Troop(string name, long int hp, int level, long int dps, int housing): Army(name,hp,level,dps), housing(housing) {
    count = count + housing;
}

void Troop::display() {
    cout << "Name: " << name << endl;
    cout << "HP: " << hp << endl;
    cout << "Damage per second: " << dps << endl; 
    cout << "Level: " << level << endl;
    cout << "Housing Space: " << housing << "\n\n";
}

void Troop::total_troops() {
    cout << "Total space of army is: " << count << endl; 
}

int main() {
    Hero king("Barbarian King", 20000, 1, 200, "Spiky Ball");
    king.display();

    Army *ptr = new Troop("Dragon", 4000, 1, 100, 20);
    ptr->upgrade();
    delete ptr;
    ptr = nullptr;

    Troop t1("Barbarian", 100, 1, 6, 1);
    Troop t2("Archer", 100, 1, 5, 1);
    Troop t3("Balloon", 1500, 1, 20, 5);
    Army *army[3] = {&t1, &t2, &t3};
    Army::disp_army(army, 3);

    const Troop t4("Root Rider", 4800, 4, 60, 20);
    cout << "Const qualified level: " << t4.show_level() << endl;
    Army::show_level(t4);

    shared_ptr<Army> ptr1 = make_shared<Hero>("Grand Warden", 15000, 2, 120, "Eternal Tome");
    ptr1->display();
    cout << ptr1.use_count() << "\n\n";
    {   
        shared_ptr<Army> ptr2 = ptr1;
        cout << ptr2.use_count() << "\n\n";
    }
    cout << ptr1.use_count() << "\n\n"; 

    king.switch_ability1(king); // Pass by Value
    king.switch_ability2(king); // Pass by Reference

    Troop::total_troops();
    return 0;
}