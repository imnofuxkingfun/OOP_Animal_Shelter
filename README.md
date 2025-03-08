# OOP Animal Shelter Management System

## Project Overview
This project is a C++ console-based Animal Shelter Management System, demonstrating Object-Oriented Programming (OOP) concepts using Standard Template Library (STL). The system allows users to manage animals in the shelter, adopt pets, and maintain adoption records through an interactive Singleton menu.

## Features
- STL Containers: Uses `vector`, `set`, `list`, and `map` for efficient data management.
- Singleton Pattern: Ensures only one instance of the menu system.
- Templates
  - Template Class: `Pet<T>` template for managing adopted animals.
  - Template Methods: `changeName<T>` and `checkName<T>`.
- Exception Handling Implements at least six exceptions including:
  - Invalid age or weight input.
  - Duplicate animal names.
  - Incorrect boolean values (`true/false` expected).
- Inheritance Hierarchy
  - `Animal` → `Mammal` → `Cat/Dog`
  - Demonstrates `HasA` and `IsA` relationships.
- Polymorphism
  - Upcasting & Downcasting (`dynamic_cast` used for safe type conversion).
  - Virtual functions for reading and displaying data.
- Operator Overloading
  - input/output stream operators (`>>` and `<<`).
  - Assignment operator (`=`).

