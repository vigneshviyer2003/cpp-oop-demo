#include <iostream>
#include <vector>
#include <algorithm>
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
public:
    enum class Type {flying, ground};   // public so main() can write Army::Type::flying
protected:
    string name;
    long int hp, dps;
    int level;
    Type type;
public:
    Army(string name, long int hp, int level,long int dps, Type type);
    virtual ~Army() {
        cout << name << " was destroyed!\n";
    }
    virtual void display() = 0;
    void describe(); // not virtual
    static void disp_army(Army *army[], int size); // for Array of Pointers 
    static string type_name(Type t);    // enum class has no automatic text conversion
    Type get_type() const;
    void upgrade(); // Upgrade should be common to the entire army and only 1 level at a time
    void self_upgrade(); 
    int show_level() const;
    static void show_level(const Army &A);
    friend void special_upgrade(Army &A);
};

Army::Army(string name, long int hp, int level,long int dps, Type type): name(name), hp(hp), level(level), dps(dps), type(type) {}

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
    Hero(string name, long int hp, int level, long int dps, string ability_name, Type type);
    void display() override;
    Hero operator +(const Hero &h);
    bool operator <(const Hero &h) const;
    bool operator ==(const Hero &h) const;
    void switch_ability1(Hero h);
    void switch_ability2(Hero &h);
};

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

class Troop:public Army {
protected:
    //Each troop has a specific housing space, you can think of it like weight
    int housing;
    static int count; // Static variable for total space of troops
public:
    Troop(string name, long int hp, int level, long int dps, int housing, Type type);
    Troop(const Troop &t);
    virtual void display() override;
    void describe();
    bool operator ==(const Troop &t) const;
    Troop& operator =(const Troop &source);
    static void total_troops();
};

int Troop::count = 0;

Troop::Troop(string name, long int hp, int level, long int dps, int housing, Type type): Army(name,hp,level,dps,type), housing(housing) {
    count += housing;
}

Troop::Troop(const Troop &t): Troop(t.name, t.hp, t.level, t.dps, t.housing, t.type) {}

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
    return (t.name == name) && (t.level == level) && (t.housing == housing);
}

Troop& Troop::operator =(const Troop &source) {
    if (this != &source) {
        count += source.housing - housing;
        name = source.name;
        hp = source.hp;
        dps = source.dps;
        level = source.level;
        type = source.type;
        housing = source.housing;
    }
    return *this;
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
    Hero king("Barbarian King", 20000, 1, 200, "Spiky Ball", Army::Type::ground);
    king.display();

    Army *ptr = new Troop("Dragon", 4000, 1, 100, 20, Army::Type::flying);
    ptr->upgrade();
    delete ptr;
    ptr = nullptr;

    Troop t1("Barbarian", 100, 1, 6, 1, Army::Type::ground);
    Troop t2("Archer", 100, 1, 5, 1, Army::Type::ground);
    Troop t3("Balloon", 1500, 1, 20, 5, Army::Type::flying);
    Army *army[3] = {&t1, &t2, &t3};
    Army::disp_army(army, 3);

    const Troop t4("Root Rider", 4800, 4, 60, 20, Army::Type::ground);
    cout << "Const qualified level: " << t4.show_level() << endl;
    Army::show_level(t4);

    shared_ptr<Army> ptr1 = make_shared<Hero>("Archer Queen", 15000, 1, 200, "Invisibility", Army::Type::ground);
    ptr1->display();
    cout << ptr1.use_count() << "\n\n";
    {   
        shared_ptr<Army> ptr2 = ptr1;
        cout << ptr2.use_count() << "\n\n";
    }
    cout << ptr1.use_count() << "\n\n"; 

    king.switch_ability1(king); // Pass by Value
    king.switch_ability2(king); // Pass by Reference

    Hero warden("Grand Warden", 15000, 2, 120, "Eternal Tome", Army::Type::flying);
    warden.self_upgrade(); // passes itself to apply_upgrade

    Troop t5("Valkyrie", 1200, 1, 20, 8, Army::Type::ground);
    special_upgrade(t5); // friend function call

    Army *ptr3 = &t1;
    cout <<"\nDynamic binding-\n";
    ptr3->display(); 
    ptr3->describe();
    t1.describe();

    void_func(static_cast<void*>(&t2));
    
    Hero K = king+warden;
    K.display();

    Troop t6("Wall Breaker", 300, 1, 40, 22, Army::Type::ground);
    Troop t7("Goblin", 90, 1, 10, 11, Army::Type::ground);

    cout << "Before assignment-\n";
    t6.display();
    t7.display();

    if (t6 == t7) {
        cout << "They are the same troops.\n\n";
    }
    else {
        cout << "They are not the same troops.\n\n";
    }

    t6 = t7 = t5;

    cout << "After assignment-\n";
    t6.display();
    t7.display();

    Troop t8(t5); // Copy Contructor
    t8.display();

    // Vector sort according to names of heroes and Lambda expression for display
    Hero duke(Hero("Dragon Duke", 20000, 1, 200, "Fireheart", Army::Type::flying));
    vector<Hero> heroes;
    heroes.reserve(3);
    heroes.push_back(king);
    heroes.push_back(warden);
    heroes.push_back(duke);

    sort(heroes.begin(), heroes.end());
    for_each(heroes.begin(), heroes.end(), [](Hero &h){h.display();});

    // enum class
    Army::Type t = warden.get_type();
    if (t == Army::Type::flying) {
        cout << "Grand Warden is " << Army::type_name(t) << ".\n";
    }
    cout << "Underlying value of flying: " << static_cast<int>(Army::Type::flying) << "\n";
    cout << "Underlying value of ground: " << static_cast<int>(Army::Type::ground) << "\n\n";
    
    Troop::total_troops();
    return 0;
}