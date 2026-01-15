# SDA Lab 4 – Design Patterns

## Overview

This laboratory session introduces the concept of Design Patterns as described in
the classic book:

    "Design Patterns: Elements of Reusable Object-Oriented Software"
    by Erich Gamma, Richard Helm, Ralph Johnson, and John Vlissides (GoF)

Design patterns are not code recipes. They are proven, reusable solutions to
recurring design problems in object-oriented software systems.

In this lab, we combine three central topics:

- Modern C++ resource management using smart pointers
- Using interfaces for clear decoupling
- Fundamental design patterns and their practical application

The focus is on understanding:

- why a pattern exists
- which problem it solves
- when it should be applied
- how it looks in clean modern C++ (C++17)

## Learning Goals

After this lab, you should be able to:

- Explain what a design pattern is and why patterns are useful
- Distinguish between creational, structural, and behavioral patterns
- Recognize typical situations where a pattern is appropriate
- Implement basic patterns in modern C++ using RAII and smart pointers
- Understand the role of ownership and lifetime in pattern implementations
- Critically evaluate patterns (e.g., when not to use Singleton)

## Pattern Categories (Gamma et al.)

### Creational Patterns

Concerned with object creation.

Examples in this lab:

- Factory Method
- Builder
- Singleton (discussed critically)

### Structural Patterns

Concerned with object composition and structure.

Examples in this lab:

- Adapter
- Composite
- Decorator
- Facade
- Proxy

### Behavioral Patterns

Concerned with communication between objects.

(Behavioral patterns will be covered in later lab sessions.)

## Smart Pointers and RAII

All examples are implemented using modern C++ smart pointers.

Key concepts:

- std::unique_ptr
  - exclusive ownership
  - zero-overhead abstraction
  - used in Factory, Builder, Composite, Decorator, Proxy

- std::shared_ptr
  - shared ownership
  - reference counting
  - used where multiple objects logically share a resource (e.g., Adapter, Proxy)

- RAII (Resource Acquisition Is Initialization)
  - resource lifetime is bound to object lifetime
  - no manual delete in user code
  - exception-safe and early-return-safe design

## Examples in This Repository

Each design pattern is demonstrated in a self-contained `.cpp` file with:

- a short description of the pattern
- a concrete real-world-inspired use case
- a minimal but complete implementation
- a main() function that can be compiled and executed directly

The following patterns are included:

1. Singleton
   Central configuration object with exactly one instance.
   Demonstrates controlled global access and discusses the drawbacks
   of global state.

2. Builder
   Step-by-step construction of a complex object (HTTP request example).
   Shows how to build objects with many optional parameters in a readable way.

3. Factory Method
   Creation of different document types via a common interface.
   Demonstrates how object creation is delegated to subclasses.

4. Dependency Injection
   A service receives its dependencies from the outside.
   Shows how to decouple high-level logic from concrete implementations.

5. Proxy
   Lazy-loading proxy for an expensive object.
   Demonstrates access control and deferred initialization.

6. Decorator
   Dynamically adding behavior (logging, timing) to a service.
   Demonstrates composition over inheritance.

7. Adapter
   Wrapping a legacy interface to match a modern interface.
   Demonstrates interface translation without modifying existing code.

8. Facade
   Simplified interface for a complex subsystem.
   Demonstrates how to reduce coupling and hide internal complexity.

9. Composite
   Tree structure of objects with uniform treatment.
   Demonstrates part–whole hierarchies (e.g., file system, circuit components).

## How to Use This Lab

For each pattern:

1. Read the description at the top of the file.
2. Study the class structure and relationships.
3. Compile and run the example.
4. Identify the roles (interface, concrete classes, client)
5. Discuss:
   - Why is this pattern useful here?
   - What would the design look like without the pattern?
   - When would this pattern be a bad choice?

## References

- Gamma, E., Helm, R., Johnson, R., Vlissides, J.
  "Design Patterns: Elements of Reusable Object-Oriented Software"
  Addison-Wesley, 1994.

- Sutter, H., Alexandrescu, A.
  "C++ Coding Standards"

- ISO C++ Core Guidelines
  https://isocpp.github.io/CppCoreGuidelines/

- Egon Teiniker's lecture notes
  https://github.com/teiniker/teiniker-lectures-embedded-softwaredesign

## Practice and exercises

- Packaging exercise (composite pattern)
  https://github.com/teiniker/teiniker-lectures-embedded-softwaredesign/tree/master/design-patterns/structural/composite/packaging-exercise

- File service (decorator pattern)
  https://github.com/teiniker/teiniker-lectures-embedded-softwaredesign/tree/master/design-patterns/structural/decorator/file-service-exercise

- List builder (builder pattern)
  https://github.com/teiniker/teiniker-lectures-embedded-softwaredesign/tree/master/design-patterns/creational/builder/list-builder-exercise

## Note

Design patterns are tools, not goals.

They should:

- simplify your design
- improve communication
- support change

They should not:

- add unnecessary complexity
- be applied mechanically
- replace clear thinking

The best pattern is the one that makes the design simpler, not more complicated.
