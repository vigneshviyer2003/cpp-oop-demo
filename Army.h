#pragma once
#include <string>
using std::string;

// Parent  
class Army {
private:
    int upgrade_rate = 5, max_level = 20; 
    // Max level can only be 20 and each level increases stats only by 5%
public:
    enum class Type {flying, ground};   // [19] public so main() can write Army::Type::flying
protected:
    string name;
    long int hp, dps;
    int level;
    Type type;
public:
    Army(string name, long int hp, int level,long int dps, Type type);
    virtual ~Army();
    virtual void display() = 0; // [3] Pure virtual display
    void describe(); // not virtual
    static void disp_army(Army *army[], int size); // for Array of Pointers 
    static string type_name(Type t);
    Type get_type() const;
    void upgrade(); // Upgrade should be common to the entire army and only 1 level at a time
    void self_upgrade(); 
    int show_level() const;
    static void show_level(const Army &A);
    friend void special_upgrade(Army &A); // [11] Friend Function
};

void apply_upgrade(Army &a);