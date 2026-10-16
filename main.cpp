#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include "Army.h"
#include "Hero.h"
#include "Troop.h"
using namespace std;

void void_func(void* x) {
    auto* troop = static_cast<Troop*>(x);
    if (troop != nullptr) {
        cout <<"Explicit cast-\n";
        troop->upgrade();
    }
}

void special_upgrade(Army &A) {
    A.upgrade_rate = 10; //increases upgrade rate to 10 for friend function
    cout << "Speical ";
    A.upgrade();
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