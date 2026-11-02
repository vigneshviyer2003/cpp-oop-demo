# Army Management System

**Author:** Vignesh Iyer

**Topic:** Assignment 1 of EEN1097 - Edge Programming in C/C++ and Rust 

**Degree:** MSc in Electronics and Computer Technology / Major in Edge & Network Security

**Institution:** Dublin City University (DCU)

---

## Overview

The **Army Management System** is an edge-oriented C++ software architecture demonstrating advanced Object-Oriented Programming (OOP) paradigms and modern C++17 design patterns. Inspired by tactical strategy game mechanics (such as *Clash of Clans*), the application models high-level unit hierarchies, dynamic resource allocation, memory management, and ability compositions using a clean, modular class structure.

---

## Technical Highlights & OOP Paradigms

* **Class Hierarchies & Multiple Inheritance:** Implements base `Army` and `Ability` parent classes. The derived `Hero` class leverages multiple inheritance to combine unit attributes with unique hero abilities.
* **Polymorphism & Dynamic Binding:** Utilizes pure virtual member functions (`virtual void display() = 0`) to enforce interface design while demonstrating runtime dynamic binding via base-class pointer arrays (`Army*[]`). Contrasted against static binding via non-virtual method hiding (`describe()`).
* **Abstract Base Classes & Resource Protection:** Makes `Army` an abstract base class with strict encapsulation (`private`, `protected`, `public`) to prevent direct instantiation and safeguard object state (such as unit HP and DPS upgrade scaling rates).
* **Smart Pointer Memory Management:** Demonstrates modern C++ memory management techniques using `std::shared_ptr` and `std::make_shared` to model shared unit ownership and safely handle automatic reference counting (`use_count()`).
* **Operator & Assignment Overloading:**
* Overloaded `+` operator to dynamically concatenate unit ability strings.
* Overloaded `==` and `<` relational operators for sorting and comparing unit states.
* Overloaded assignment operator (`operator=`) with self-assignment checks (`this != &source`), chained assignment support, and static resource tracking updates.


* **Modern C++ Standard Template Library (STL):** Manages dynamic object collections via `std::vector`, utilizing capacity reservation (`reserve()`), alphabetical sorting via `std::sort`, and inline functional iteration via `std::for_each` and C++ lambda expressions.
* **Const-Correctness & Safe Parameter Passing:** Enforces immutable state inspection with `const` member functions and `const Army&` reference parameters. Demonstrates side-effect isolation by contrasting pass-by-value vs. pass-by-reference object mutation (`switch_ability1` vs. `switch_ability2`).
* **Encapsulation Bypass & Internal Access:** Features a `friend` function (`special_upgrade()`) to directly modify restricted class members (`upgrade_rate`), and uses `*this` self-referencing to pass object instances to global helper functions.
* **Static Members & Dynamic Allocations:** Tracks cumulative army housing space across instances using static integers (`Troop::count`) and demonstrates heap allocation using `new`/`delete` alongside virtual destructors (`virtual ~Army()`) to prevent resource leaks.
* **Scoped Enums & Type Casting:** Defines scoped type classifications using `enum class Type { flying, ground }` and demonstrates safe pointer conversions using explicit `static_cast` (including `void*` pointer round-tripping).

---

## Class Architecture

```
                 +-------------------+       +-------------------+
                 |       Army        |       |      Ability      |
                 | (Abstract Class)  |       |   (Parent Class)  |
                 +---------+---------+       +---------+---------+
                           ^                           ^
                           |                           |
             +-------------+-------------+             |
             |                           |             |
     +-------+-------+           +-------+-------+     |
     |     Troop     |           |     Hero      +-----+
     | (Derived Class|           | (Derived Class|
     +---------------+           +---------------+

```

---

## File Structure

* `Army.h` / `Army.cpp`: Base class interface defining common unit state, pure virtual display interfaces, and static type conversion methods.
* `Ability.h` / `Ability.cpp`: Encapsulates unique hero ability attributes.
* `Hero.h` / `Hero.cpp`: Multiple inheritance class combining `Army` and `Ability` properties, with overloaded operators.
* `Troop.h` / `Troop.cpp`: Ground/flying unit subclass with static housing space counters and overloaded assignment operators.
* `main.cpp`: Comprehensive driver program showcasing smart pointers, static binding, STL vector sorting, lambda functions, and explicit casting.

---

## Compilation & Execution

To compile and execute the project using G++ (MinGW-w64 / MSYS2 toolchain):

```bash
# Compile all source files into an executable
g++ -std=c++17 main.cpp Army.cpp Ability.cpp Hero.cpp Troop.cpp -o ArmyManagement.exe

# Run the binary
./ArmyManagement.exe

```

---