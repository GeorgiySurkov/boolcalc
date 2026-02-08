# boolcalc

A command-line boolean expression calculator built in C++17 with minimal standard library usage. The project implements core data structures from scratch and manages memory manually — no `std::vector`, no `std::map`, no smart pointers.

## Features

- **Evaluate** boolean expressions with user-supplied variable values
- **Truth tables** — generate and print complete truth tables
- **CNF / DNF** — convert expressions to Conjunctive and Disjunctive Normal Forms
- **Zhegalkin polynomial** — compute the algebraic normal form (XOR-based representation)
- **Functional completeness** — check whether a system of boolean functions is complete using Post's theorem

### Supported operations

| Symbol | Operation              |
|--------|------------------------|
| `&`    | Conjunction (AND)      |
| `v`    | Disjunction (OR)       |
| `~`    | Negation (NOT)         |
| `>`    | Implication            |
| `<`    | Converse implication   |
| `+`    | XOR (addition mod 2)   |
| `=`    | Biconditional          |
| `\|`   | Sheffer stroke (NAND)  |
| `^`    | Peirce arrow (NOR)     |

Variables are named `xN` where N is a natural number: `x1`, `x2`, `x3`, etc.

## What makes this project educational

The main goal was to understand what happens beneath the abstractions that the C++ standard library provides. Key areas explored:

### Custom standard library (`mstd`)

Instead of relying on STL containers, the project implements its own versions from scratch in the `lib/` directory:

| Component | File | What it replaces |
|-----------|------|------------------|
| `mstd::map` | `lib/avl_map.h` | `std::map` — a fully balanced AVL tree with iterators, insert, erase, find, and `operator[]` |
| `mstd::vector` | `lib/vector.h` | `std::vector` — dynamic array with push/pop, reserve, resize, iterators, and Rule of Five |
| `mstd::pair` | `lib/utility.h` | `std::pair` and `std::swap` |
| `mstd::less` | `lib/functional.h` | `std::less` comparator functor |
| `mstd::strcmp` and friends | `lib/cstring.h` | C string functions (`strcmp`, `strncmp`, `strlen`, `strcpy`) |

### Manual memory management

All dynamic allocations use raw `new` / `delete` with no smart pointers:

- AST nodes are heap-allocated and cleaned up via destructors
- Truth tables and Zhegalkin coefficients use raw `bool*` arrays
- `BooleanExpression` implements the full **Rule of Five** (copy/move constructors, copy/move assignment, destructor)
- Deep copying of the AST is handled through a virtual `clone()` method

### Expression parsing pipeline

A three-stage parsing pipeline converts a string into an evaluable AST:

1. **Infix filter** — normalizes whitespace, validates tokens, handles multi-character variable names
2. **Infix to postfix** — shunting-yard algorithm with an operator precedence table (negation > conjunction > all others)
3. **Postfix to tree** — stack-based construction of a polymorphic AST with 12 concrete node types

### Post's completeness theorem

Functional completeness checking uses a 5-bit class mask to determine membership in Post's five closure classes (T₀, T₁, monotone, self-dual, affine). A system is complete if and only if for each class there exists at least one function not belonging to it.

## Getting started

### Prerequisites

- `g++` with C++17 support
- `make`

### Build

```bash
make
```

### Run

```bash
# Evaluate expressions (prompts for variable values)
./boolcalc -calc input.txt output.txt

# Build Conjunctive Normal Form
./boolcalc -cnf input.txt output.txt

# Build Disjunctive Normal Form
./boolcalc -dnf input.txt output.txt

# Compute Zhegalkin polynomial
./boolcalc -zh input.txt output.txt

# Print truth table
./boolcalc -table input.txt

# Check functional completeness
./boolcalc -isfull input.txt output.txt

# Show help
./boolcalc -h
```

### Input format

The input file contains one boolean expression per line:

```
x1 & x2
x1 v ~x2
x1 > (x2 + x3)
```

### Run tests

```bash
make test
```

This runs 10 functional completeness tests, comparing output against expected results in the `tests/` directory.

## Project structure

```
boolcalc
├── boolcalc.cpp        # CLI entry point and argument dispatch
├── boolexpr.h/.cpp     # BooleanExpression class (parsing, evaluation, transforms)
├── formulaenode.h/.cpp  # AST node hierarchy (12 node types)
├── errors.h            # Custom exception hierarchy
├── helpers.h           # Small utility functions (min, max, xor)
├── lib/
│   ├── avl_map.h       # mstd::map (AVL tree)
│   ├── vector.h        # mstd::vector
│   ├── utility.h       # mstd::pair, mstd::swap
│   ├── functional.h    # mstd::less
│   └── cstring.h/.cpp  # mstd::strcmp, strlen, strcpy, strncmp
├── tests/              # 10 test cases (.in / .out pairs)
└── Makefile
```

## License

This project is provided as-is for educational purposes.
