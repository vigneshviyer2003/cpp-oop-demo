#include <iostream>
#include <string>
#include <memory>
using namespace std;

class Army;                  
void apply_upgrade(Army &a);

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
    void describe(); // not virtual
    static void disp_army(Army *army[], int size); // for Array of Pointers 
    void upgrade(); // Upgrade should be common to the entire army and only 1 level at a time
    void self_upgrade(); 
    int show_level() const;
    static void show_level(const Army &A);
    friend void special_upgrade(Army &A);
};

Army::Army(string name, long int hp, int level,long int dps): name(name), hp(hp), level(level), dps(dps) {}

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

void special_upgrade(Army &A) {
    A.upgrade_rate = 10; //increases upgrade rate to 10 for friend function
    cout << "Speical ";
    A.upgrade();
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
    Hero(string name, long int hp, int level, long int dps, string ability_name);
    void display() override;
    Hero operator +(Hero &h);
    void switch_ability1(Hero h);
    void switch_ability2(Hero &h);
};

Hero::Hero(string name, long int hp, int level, long int dps, string ability_name): Army(name,hp,level,dps), Ability(ability_name) {}

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

Hero Hero::operator+(Hero &h) {
    cout << name << " acquried " << h.name << "'s " << h.ability_name << " for it's duration.\n";
    return Hero(name, hp, level, dps, ability_name + " & " + h.ability_name);
}

class Troop:public Army {
protected:
    //Each troop has a specific housing space, you can think of it like weight
    int housing;
    static int count; // Static variable for total space of troops
public:
    Troop(string name, long int hp, int level, long int dps, int housing);
    virtual void display() override;
    void describe();
    bool operator ==(Troop);
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

void Troop::describe() {
    cout << name << " is a troop with housing space " << housing << ".\n\n";
}

bool Troop::operator == (Troop t) {
    if (t.housing == housing) {
        return true; 
    }
    else
        return false;
}

void Troop::total_troops() {
    cout << "Total space of army is: " << count << endl; 
}

void void_func(void* x) {
    auto* troop = static_cast<Troop*>(x);
    if (troop != nullptr) {
        cout <<"Explicit cast-\n";
        troop->upgrade();
    }
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

    shared_ptr<Army> ptr1 = make_shared<Hero>("Archer Queen", 15000, 1, 200, "Invisibility");
    ptr1->display();
    cout << ptr1.use_count() << "\n\n";
    {   
        shared_ptr<Army> ptr2 = ptr1;
        cout << ptr2.use_count() << "\n\n";
    }
    cout << ptr1.use_count() << "\n\n"; 

    king.switch_ability1(king); // Pass by Value
    king.switch_ability2(king); // Pass by Reference

    Hero warden("Grand Warden", 15000, 2, 120, "Eternal Tome");
    warden.self_upgrade(); // passes itself to apply_upgrade

    Troop t5("Valkyrie", 1200, 1, 20, 8);
    special_upgrade(t5); // friend function call

    Army *ptr3 = &t1;
    cout <<"\nDynamic binding-\n";
    ptr3->display(); 
    ptr3->describe();
    t1.describe();

    void_func(&t2);

    if (&t1 == &t2) {
        cout << "They have the same housing space.\n\n";
    }
    else {
        cout << "They don't have the same housing space.\n\n";
    }

    Hero K = king+warden;
    K.display();
    Troop::total_troops();
    return 0;
}