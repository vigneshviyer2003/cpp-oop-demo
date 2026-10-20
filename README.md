# Army Management System

**Author:** Vignesh Iyer

## Overview

A C++ project demonstrating Object-Oriented Programming (OOP) concepts through an army management system inspired by Clash of Clans.

The project models an army with different units, including Heroes and Troops, with features such as upgrades, abilities, and unit classification (flying or ground).

## Features

- **Inheritance:** `Army`, `Hero`, `Ability`, and `Troop` classes.
- **Multiple Inheritance:** `Hero` inherits from both `Army` and `Ability`, since only heroes have abilities.
- **Polymorphism:** Virtual functions and dynamic binding through `Army` pointers, with a non-virtual `describe()` to contrast static binding.
- **Abstract Class:** `Army` declares a pure virtual `display()`, so it cannot be instantiated.
- **Encapsulation:** Private, protected, and public access specifiers.
- **Operator Overloading:** `+` to combine hero abilities, `<` and `==` for comparing heroes, and `==` and `=` for troops.
- **Constructors:** Parameterized and copy constructors (the `Troop` copy constructor delegates to the main constructor).
- **Const-Correctness:** `const` methods and `const` reference parameters.
- **Pass by Value vs. Reference:** Demonstrated with `switch_ability1()` and `switch_ability2()`.
- **Self-Referencing Objects:** `*this` is passed to a non-member function (`apply_upgrade`) from within `self_upgrade()`.
- **Friend Functions:** `special_upgrade()` accesses the private upgrade rate.
- **Static Members:** `Troop` tracks total housing space.
- **Smart Pointers:** Memory management using `shared_ptr`, including `use_count()`.
- **Type Casting:** Explicit casting with `static_cast` (via `void*`).
- **Enumerations:** Unit classification using a scoped `enum class` (`Army::Type`).
- **STL and Lambda Expressions:** Sorting heroes by name with `sort()` and `operator<`, and displaying them with `for_each()` and a lambda.