# C++ Design Patterns: Beginner to Expert Roadmap

A realistic timeline is 18–24 months at ~8–10 hours/week. You can't learn patterns well without solid C++ fundamentals first, so the plan front-loads the language itself.

---

## Phase 0 — C++ Fundamentals (Months 1–4)

**Goal:** Write correct, idiomatic modern C++ (C++17/20) without fighting the language.

### Learn
- Variables, control flow, functions, references vs pointers
- Classes, constructors/destructors, RAII (the single most important C++ idea)
- `std::vector`, `std::string`, `std::map`, iterators, range-based for
- `std::unique_ptr`, `std::shared_ptr` — never raw `new`/`delete`
- Const correctness, pass-by-value vs by-reference
- Copy vs move semantics (basic understanding)
- Basic templates: function templates, class templates
- Compiling with g++/clang, using CMake at a basic level

### Resources
- **Book:** *A Tour of C++* (Stroustrup) — short, modern, no legacy cruft
- **Course:** learncpp.com — free, thorough, updated for modern C++
- **Practice:** Exercism C++ track or LeetCode easy problems in C++

### Milestone project
Build a command-line portfolio tracker: read trades from a CSV, compute positions and P&L, print a report. Use classes, `std::vector`, smart pointers, and no manual memory management.

**Exit test:** You can explain RAII, write a class with proper copy/move behavior, and know why `std::unique_ptr` exists.

---

## Phase 1 — Intermediate C++ & OOP Design (Months 5–7)

**Goal:** Understand polymorphism and abstraction deeply — the raw material of patterns.

### Learn
- Virtual functions, vtables, abstract base classes, `override`/`final`
- Interface design: when to use inheritance vs composition ("composition over inheritance")
- Rule of 0/3/5
- Exceptions and error handling strategies (`std::optional`, `std::expected`)
- Lambdas and `std::function`
- Templates in more depth: specialization, SFINAE basics, concepts (C++20)
- `std::variant`, `std::any`, structured bindings

### Resources
- **Book:** *Effective Modern C++* (Scott Meyers) — item-by-item, read slowly
- **Talks:** CppCon "Back to Basics" track on YouTube (free, excellent)

### Milestone project
Extend the portfolio tracker: support multiple instrument types (equity, bond, option) via an abstract `Instrument` interface, then rewrite it using `std::variant` + `std::visit` instead. Compare the two designs — this is your first real pattern decision.

**Exit test:** You can articulate the tradeoff between runtime polymorphism (virtual) and static polymorphism (templates/variant).

---

## Phase 2 — Classic Design Patterns (Months 8–11)

**Goal:** Know the GoF vocabulary and implement each pattern idiomatically in modern C++.

### Learn (in this order)
1. **Creational:** Factory Method, Abstract Factory, Builder, Singleton (and why it's usually a mistake)
2. **Structural:** Adapter, Decorator, Facade, Composite, Proxy, Bridge, Pimpl (C++-specific)
3. **Behavioral:** Strategy, Observer, Command, Template Method, Visitor, State, Chain of Responsibility

For each pattern: implement it from scratch, then implement the modern-C++ alternative (e.g., Strategy via `std::function` instead of an interface; Visitor via `std::variant` + overload set).

### Resources
- **Primary book:** *C++ Software Design* (Klaus Iglberger) — the best modern treatment; teaches patterns as design principles, not class diagrams
- **Reference:** Refactoring.Guru (free site) for quick pattern lookups
- **Talks:** Iglberger's "Breaking Dependencies" CppCon series

### Milestone project
Build a mini pricing engine skeleton:
- Factory to create instruments from config
- Strategy for pricing models (analytic vs Monte Carlo stub)
- Observer for market-data updates
- Visitor for computing risk measures across instrument types

This mirrors real quant-library architecture and forces every major pattern into one coherent codebase.

**Exit test:** Given a design problem, you can name 2–3 candidate patterns and argue which fits — including "none, keep it simple."

---

## Phase 3 — C++-Specific Idioms & Advanced Patterns (Months 12–16)

**Goal:** Go beyond GoF into patterns that only exist in C++.

### Learn
- **CRTP** (Curiously Recurring Template Pattern) — static polymorphism
- **Type erasure** — how `std::function` works internally; build your own
- **Policy-based design** — composing behavior via template parameters
- **Expression templates** — how Eigen and quant libraries avoid temporaries
- **Pimpl** in depth — compile-time firewalls
- **Tag dispatch, `if constexpr`, concepts-based overloading**
- **Mixins and EBO** (empty base optimization)

### Resources
- **Book:** *Modern C++ Design* (Alexandrescu) — dated syntax, timeless ideas; read for policy-based design and type lists
- **Book:** *C++ Templates: The Complete Guide* (Vandevoorde/Josuttis) — reference, don't read cover to cover
- **Code reading:** QuantLib source. Trace how a `PricingEngine` connects to an `Instrument` (Strategy + Observer), how term structures use lazy evaluation, where CRTP appears. Directly relevant to XVA work.

### Milestone project
Rebuild one component of your pricing engine three ways: virtual interface, CRTP, and type erasure. Benchmark them. Write up (for yourself) when each wins.

**Exit test:** You can implement type erasure from scratch and explain the compile-time/runtime tradeoffs of each polymorphism technique.

---

## Phase 4 — Expert Judgment (Months 17–24, then ongoing)

**Goal:** Knowing when *not* to use patterns. Experts delete abstractions.

### Practice
- Contribute to an open-source C++ project (QuantLib welcomes contributions and would compound your day-job expertise)
- Refactor your earlier projects: remove every pattern that isn't paying rent
- Do design reviews: take a codebase, write a critique of its abstractions
- Study anti-patterns: Singleton abuse, inheritance-for-code-reuse, premature abstraction

### Resources
- **Talks:** Sean Parent — "Inheritance Is the Base Class of Evil," "Better Code" series
- **Book:** *A Philosophy of Software Design* (Ousterhout) — language-agnostic, sharpens judgment
- **Community:** r/cpp, C++ Slack (cpplang), CppCon annually

### Ongoing habits
- One CppCon talk per week
- Read code from well-designed libraries (fmt, ranges-v3, Abseil) and ask "why this structure?"
- Teach: explaining patterns to others (blog posts, internal talks at work) is the fastest way to find gaps

---

## Weekly rhythm suggestion

- 3–4 hrs: reading/course material
- 3–4 hrs: coding the current milestone project
- 1–2 hrs: one talk or code-reading session

## Common traps to avoid

1. **Learning patterns before the language.** Java-style patterns in C++ produce bad C++. Finish Phase 0–1 first.
2. **Pattern fever.** After Phase 2 everything looks like a nail. Phase 4 exists to cure this.
3. **Tutorial loop.** Every phase has a project because patterns only stick when you feel the pain they solve.
4. **Skipping templates.** In C++, half of "design patterns" are template techniques. Don't treat them as optional.
