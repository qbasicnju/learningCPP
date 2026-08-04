# Phase 0 — C++ Fundamentals: Week-by-Week (16 Weeks)

**Target:** ~8–10 hrs/week. Split roughly 4 hrs reading, 4 hrs coding, 1 hr review.
**Exit condition:** You can explain RAII, write a class with correct copy/move behavior, and build a multi-file CMake project without manual `new`/`delete`.

Primary text: *A Tour of C++* (Stroustrup, 3rd ed.) — abbreviated **ToC** below.
Primary course: learncpp.com — abbreviated **LCP**, referenced by chapter number.

---

## Block A — Core Language (Weeks 1–4)

### Week 1 — Toolchain and basic syntax
- **Read:** LCP ch.0–2. ToC ch.1.
- **Learn:** compiling with `g++ -std=c++20 -Wall -Wextra`, translation units, headers vs source files, `#include`, declarations vs definitions.
- **Code:** temperature converter; FizzBuzz; a function that returns the nth Fibonacci number iteratively.
- **Setup task:** install a compiler (g++ 13+ or clang 17+), VS Code with the clangd extension, and CMake. Get a hello-world building from a `CMakeLists.txt`, not just from the command line.

```cmake
# CMakeLists.txt — the minimum you need, keep reusing this
cmake_minimum_required(VERSION 3.20)
project(cpp_practice LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(main src/main.cpp)
```

- **Checkpoint:** you can add a second `.cpp` file to the project and call a function from it.

### Week 2 — Types, control flow, functions
- **Read:** LCP ch.4–5, 8. ToC ch.2–3.
- **Learn:** fixed-width integers (`std::int64_t`), floating-point pitfalls, `auto`, scope and lifetime, function overloading, default arguments, `constexpr`.
- **Code:** a small numerical utilities header — `mean`, `stddev`, `linspace`, `clamp` — with overloads for `float`/`double`.
- **Trap to watch:** integer division and signed/unsigned comparison warnings. Turn warnings into errors (`-Werror`) for one exercise so you feel it.

### Week 3 — References, pointers, and the stack/heap distinction
- **Read:** LCP ch.9, 12. ToC ch.1.7.
- **Learn:** lvalue references, `const&` parameters, pointers, null, pointer arithmetic (know it, avoid it), stack vs heap allocation, dangling references.
- **Code:** write `void swap(int&, int&)`, then a function that takes a `std::vector<double>&` and normalizes it in place. Then deliberately write a function that returns a reference to a local, observe the compiler warning and the crash, and understand why.
- **Checkpoint:** you can explain when to pass by value, by `const&`, and by `&`.

### Week 4 — Classes and RAII
- **Read:** LCP ch.14–15. ToC ch.4. **This is the most important week of Phase 0.**
- **Learn:** constructors, destructors, member initializer lists, `this`, access specifiers, `const` member functions, the idea that a destructor runs deterministically at scope exit.
- **Code:** write a `ScopedTimer` class that records a start time in its constructor and prints elapsed duration in its destructor. Use it to time a loop. This is RAII in eight lines and it will click.

```cpp
#include <chrono>
#include <iostream>
#include <string>

class ScopedTimer {
public:
    explicit ScopedTimer(std::string label)
        : label_{std::move(label)}, start_{std::chrono::steady_clock::now()} {}

    ~ScopedTimer() {
        const auto elapsed = std::chrono::steady_clock::now() - start_;
        const auto ms = std::chrono::duration<double, std::milli>(elapsed).count();
        std::cout << label_ << ": " << ms << " ms\n";
    }

    ScopedTimer(const ScopedTimer&) = delete;
    ScopedTimer& operator=(const ScopedTimer&) = delete;

private:
    std::string label_;
    std::chrono::steady_clock::time_point start_;
};
```

- **Checkpoint:** you can state in one sentence why RAII makes `finally` blocks unnecessary in C++.

---

## Block B — The Standard Library (Weeks 5–8)

### Week 5 — Containers
- **Read:** LCP ch.16–17. ToC ch.12.
- **Learn:** `std::vector` (growth, `reserve`, invalidation), `std::string`, `std::array`, `std::map` vs `std::unordered_map`, when each is appropriate.
- **Code:** word-frequency counter reading from a text file into a `std::map<std::string,int>`, printed in descending count order.

### Week 6 — Iterators and algorithms
- **Read:** ToC ch.13. LCP ch.18.
- **Learn:** iterator categories, `begin`/`end`, range-based for, `std::sort`, `std::find_if`, `std::accumulate`, `std::transform`, and C++20 ranges (`std::ranges::sort`, views).
- **Code:** rewrite Week 5's counter using algorithms instead of raw loops. Then rewrite the numerical utilities from Week 2 on top of `std::accumulate`.
- **Rule for this week:** no hand-written `for (int i = 0; ...)` loops at all. Forcing this teaches the algorithm vocabulary fast.

### Week 7 — File I/O, strings, and error handling
- **Read:** LCP ch.20, 28. ToC ch.11.
- **Learn:** `std::ifstream`/`ofstream`, `std::getline`, string parsing, `std::stod`/`from_chars`, exceptions (`try`/`catch`/`throw`), `std::optional`, when to use exceptions vs return codes.
- **Code:** a robust CSV reader: handles a header row, quoted fields, blank lines, and malformed rows without crashing. **Keep this — the milestone project uses it.**

### Week 8 — Consolidation and review
- No new material. Re-solve five exercises from Weeks 1–7 without looking at your old code. Fix every compiler warning in everything you've written. Write a one-page summary of RAII, value vs reference semantics, and container choice — in your own words.

---

## Block C — Resource Management and Templates (Weeks 9–13)

### Week 9 — Copy semantics and the Rule of 3
- **Read:** LCP ch.14.14–14.16, 21.
- **Learn:** copy constructor, copy assignment, why the compiler-generated versions break for owning classes, deep vs shallow copy.
- **Code:** write a `Buffer` class owning a raw `double*` — implement the Rule of 3 by hand. Test it with a copy, a self-assignment, and a vector of Buffers. Then delete the whole thing and note that `std::vector<double>` did it correctly for free. That contrast is the lesson.

### Week 10 — Move semantics and the Rule of 5/0
- **Read:** ToC ch.6.2. LCP ch.22.
- **Learn:** rvalue references, `std::move` (it only casts — it moves nothing), move constructor, move assignment, `noexcept` on moves, Rule of 0 as the goal.
- **Code:** add move operations to `Buffer`. Instrument all five special members with print statements and observe which fire when you push into a vector, return by value, or call `std::move`.
- **Checkpoint:** you can explain why `std::move` on a `const` object silently copies.

### Week 11 — Smart pointers and ownership
- **Read:** LCP ch.22.5–22.7. ToC ch.15.2.
- **Learn:** `std::unique_ptr`, `std::make_unique`, moving unique_ptrs, `std::shared_ptr` and reference counting, `std::weak_ptr` for cycles, why `shared_ptr` is a design smell when overused.
- **Code:** a small ownership tree — a `Portfolio` owning `std::vector<std::unique_ptr<Position>>`. Practice transferring ownership in and out.
- **Rule from here on:** zero raw `new`/`delete` in any code you write.

### Week 12 — Templates
- **Read:** ToC ch.7. LCP ch.11.
- **Learn:** function templates, class templates, type deduction, `template<typename T>` mechanics, why templates live in headers, basic `concepts` (`std::floating_point`) in C++20.
- **Code:** make Week 2's `mean`/`stddev` generic over any numeric range. Write a `template<typename T> class Matrix` with `operator()(row, col)`.

### Week 13 — Const correctness, enums, and code organization
- **Read:** LCP ch.13, 7.
- **Learn:** `const` member functions and overloads, `enum class`, namespaces, header guards / `#pragma once`, splitting a project into `include/` and `src/`, `struct` vs `class` conventions.
- **Code:** reorganize everything you've written into a single CMake project with a proper directory layout and a static library target.

---

## Block D — Milestone Project (Weeks 14–16)

Full spec below. Week 14: parsing and data model. Week 15: position and P&L engine. Week 16: reporting, polish, and a self-review pass.

---
---

# Milestone Project — Portfolio Tracker

## Objective

A command-line tool that reads a CSV of trades, computes current positions and realized/unrealized P&L, and prints a formatted report.

The point is not the finance — it's that this problem naturally requires every Phase 0 concept: file I/O, error handling, containers, algorithms, value semantics, ownership, const correctness, and RAII. You'll also extend this exact codebase in Phases 1–2, so build it to be extended.

## Requirements

**Input** — a CSV with this schema:

```
date,symbol,side,quantity,price
2026-01-05,AAPL,BUY,100,185.20
2026-01-08,MSFT,BUY,50,402.10
2026-02-11,AAPL,SELL,40,201.75
2026-03-02,AAPL,BUY,25,196.40
2026-03-14,MSFT,SELL,50,411.00
```

**Behavior**
1. Parse the file, skipping the header. Reject malformed rows with a clear message to `stderr` and continue processing the rest.
2. Maintain a position per symbol: net quantity and average cost (use weighted-average cost basis; a SELL reduces quantity and realizes P&L against average cost, leaving average cost unchanged).
3. Accept an optional marks file (`symbol,price`) for unrealized P&L. If absent, report unrealized as N/A.
4. Print a report sorted by symbol.

**Invocation**
```
./portfolio --trades trades.csv [--marks marks.csv]
```

**Sample output**
```
Symbol    Quantity    Avg Cost    Realized      Unrealized
------    --------    --------    --------      ----------
AAPL            85      189.85     +  662.00     +  1289.75
MSFT             0        0.00     +  445.00            N/A
------    --------    --------    --------      ----------
TOTAL                               + 1107.00     +  1289.75
```

## Constraints (these are the actual exercise)

- No raw `new` / `delete`, no owning raw pointers.
- No global mutable state.
- Every function that doesn't modify its argument takes `const&`.
- Compiles clean under `-Wall -Wextra -Wpedantic`.
- Split across at least four translation units plus headers.
- Money and quantities: use `double` for now, but write a comment explaining why production code wouldn't.

## Suggested structure

```
portfolio/
├── CMakeLists.txt
├── include/portfolio/
│   ├── Trade.hpp
│   ├── CsvReader.hpp
│   ├── Position.hpp
│   ├── Portfolio.hpp
│   └── Report.hpp
├── src/
│   ├── main.cpp
│   ├── CsvReader.cpp
│   ├── Position.cpp
│   ├── Portfolio.cpp
│   └── Report.cpp
└── data/
    ├── trades.csv
    └── marks.csv
```

## Starter code

### `include/portfolio/Trade.hpp`

```cpp
#pragma once

#include <string>

namespace portfolio {

enum class Side { Buy, Sell };

// A single executed trade. Value type: cheap to copy, no ownership.
struct Trade {
    std::string date;    // ISO-8601; a real system would use a date type
    std::string symbol;
    Side side{Side::Buy};
    double quantity{0.0};
    double price{0.0};
};

// Returns Side::Buy for "BUY"/"B" (case-insensitive), Sell for "SELL"/"S".
// Throws std::invalid_argument on anything else.
Side parse_side(const std::string& text);

} // namespace portfolio
```

### `include/portfolio/Position.hpp`

```cpp
#pragma once

#include <optional>
#include <string>

namespace portfolio {

struct Trade;

// Running position in a single symbol, built up trade by trade.
class Position {
public:
    explicit Position(std::string symbol);

    // Applies a trade to this position, updating quantity, average cost,
    // and realized P&L. Precondition: trade.symbol == symbol().
    void apply(const Trade& trade);

    [[nodiscard]] const std::string& symbol() const { return symbol_; }
    [[nodiscard]] double quantity() const { return quantity_; }
    [[nodiscard]] double average_cost() const { return average_cost_; }
    [[nodiscard]] double realized_pnl() const { return realized_pnl_; }

    // Returns std::nullopt when no mark is supplied or the position is flat.
    [[nodiscard]] std::optional<double> unrealized_pnl(
        std::optional<double> mark) const;

private:
    std::string symbol_;
    double quantity_{0.0};
    double average_cost_{0.0};
    double realized_pnl_{0.0};
};

} // namespace portfolio
```

### `src/Position.cpp` — the core logic, partially given

```cpp
#include "portfolio/Position.hpp"
#include "portfolio/Trade.hpp"

#include <stdexcept>
#include <utility>

namespace portfolio {

Position::Position(std::string symbol) : symbol_{std::move(symbol)} {}

void Position::apply(const Trade& trade) {
    if (trade.symbol != symbol_) {
        throw std::invalid_argument{"trade symbol does not match position"};
    }

    if (trade.side == Side::Buy) {
        // Weighted-average cost basis: blend the new lot into the old average.
        const double new_quantity = quantity_ + trade.quantity;
        if (new_quantity != 0.0) {
            average_cost_ =
                (average_cost_ * quantity_ + trade.price * trade.quantity)
                / new_quantity;
        }
        quantity_ = new_quantity;
    } else {
        // TODO (you): a sell realizes P&L against the existing average cost
        // and reduces quantity. Average cost is unchanged by a sell.
        //
        // realized_pnl_ += ...
        // quantity_     -= ...
        //
        // Decide and document what should happen if the sell exceeds the
        // current long quantity (short position? throw? clamp?).
    }
}

std::optional<double> Position::unrealized_pnl(
    std::optional<double> mark) const {
    // TODO (you): return nullopt if !mark or quantity_ == 0.0,
    // otherwise (*mark - average_cost_) * quantity_.
    return std::nullopt;
}

} // namespace portfolio
```

### `include/portfolio/CsvReader.hpp`

```cpp
#pragma once

#include <istream>
#include <string>
#include <vector>

namespace portfolio {

struct Trade;

struct ParseError {
    std::size_t line_number{0};
    std::string line;
    std::string reason;
};

struct ParseResult {
    std::vector<Trade> trades;
    std::vector<ParseError> errors;  // malformed rows, reported not fatal
};

// Reads trades from an already-open stream. Skips the header row.
// Never throws on malformed data — collects errors instead.
ParseResult read_trades(std::istream& input);

// Splits one CSV line on commas. Trims surrounding whitespace on each field.
std::vector<std::string> split_line(const std::string& line);

} // namespace portfolio
```

Taking a `std::istream&` rather than a filename is deliberate: it lets you unit-test the parser with a `std::istringstream` and no files on disk. Notice this is already a small design decision about dependencies — the kind Phase 2 formalizes.

### `src/main.cpp` — skeleton

```cpp
#include "portfolio/CsvReader.hpp"
#include "portfolio/Portfolio.hpp"
#include "portfolio/Report.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    const std::vector<std::string> args(argv + 1, argv + argc);

    // TODO (you): parse --trades <path> and optional --marks <path>.
    // Print usage and return 1 if --trades is missing.

    std::ifstream trades_file{/* path */};
    if (!trades_file) {
        std::cerr << "error: cannot open trades file\n";
        return 1;
    }

    const auto result = portfolio::read_trades(trades_file);
    for (const auto& err : result.errors) {
        std::cerr << "warning: line " << err.line_number
                  << ": " << err.reason << '\n';
    }

    // TODO (you): build the Portfolio, load marks, print the report.
    return 0;
}
```

## Build it in this order

1. **`Trade.hpp` + `parse_side`.** Smallest testable unit. Write it, test it with a handful of strings.
2. **`split_line`.** Test with trailing commas, empty fields, whitespace.
3. **`read_trades`** using a `std::istringstream` in a test. Feed it deliberately broken input: missing fields, non-numeric quantity, unknown side.
4. **`Position::apply`.** Hand-compute the expected answers for the sample CSV *before* you run it, then check the program agrees.
5. **`Portfolio`** — holds `std::map<std::string, Position>`, dispatches trades by symbol.
6. **`Report`** — formatting only, no calculation. Use `std::format` (C++20) or `iomanip`.
7. **`main`** — argument parsing and wiring, last.

## Testing without a framework

Don't install a test library yet. Write a `tests/` directory with a plain `assert`-based runner:

```cpp
#include <cassert>
#include <cmath>
#include <sstream>
#include "portfolio/CsvReader.hpp"

static bool close_enough(double a, double b) {
    return std::abs(a - b) < 1e-9;
}

static void test_rejects_bad_quantity() {
    std::istringstream input{
        "date,symbol,side,quantity,price\n"
        "2026-01-05,AAPL,BUY,not_a_number,185.20\n"};

    const auto result = portfolio::read_trades(input);
    assert(result.trades.empty());
    assert(result.errors.size() == 1);
}

int main() {
    test_rejects_bad_quantity();
    // ... more
    return 0;
}
```

Add it as a second CMake target. In Phase 1 you'll swap this for Catch2 and appreciate why.

## Self-review checklist

Before calling it done:

- [ ] Zero warnings under `-Wall -Wextra -Wpedantic`
- [ ] No `new`, `delete`, or owning raw pointers anywhere
- [ ] Every non-mutating parameter is `const&`; every non-mutating member function is `const`
- [ ] No function longer than ~40 lines
- [ ] The parser is tested with a stream, not a file
- [ ] Malformed input produces a useful message and does not abort the run
- [ ] You can explain why each container choice was made
- [ ] You can point at where a copy happens that could be a move, and either fix it or justify it

## Stretch goals (only after the above is clean)

- Support short positions properly and document the P&L convention you chose
- Add a `--fifo` flag using FIFO lot matching instead of average cost — this forces you into a real data structure decision (`std::deque` of lots) and is the single most instructive extension
- Read marks from stdin when `--marks -` is passed
- Add `--format json` output

The FIFO extension in particular is where you'll first feel the need for an abstraction over "cost basis method" — which is exactly the Strategy pattern. Don't build it as a pattern yet. Feel the pain now, and Phase 2's lesson will land properly.
