# ShapeHunt

Made by @Karim-Elbahrawy, @laklouka-11, and @salastro for Zewail City CIE202
Fundamentals of Computer Programming course.

## Style Guide

The following set is expected to grow and evolve as we continue to write code.
It is expected to work on Windows using Visual Studio 2022, so there will be no
consideration for other platforms or compilers. This project uses windows.h and
other windows-specific libraries, so it is not expected to work on other
platforms.

_Heavily inspired by Google's C++ Style Guide and the C++ Core Guidelines._

### General

Ctrl+K, Ctrl+D to format your code in Visual Studio. Do this before committing.

### C++ Version

Do not use non-standard extensions.

### Header Files

- Every `.cpp` file should have an associated `.h` file.
- There are some common exceptions, such as unit tests and the main file.
- Guard against multiple inclusion with `#pragma once`.
- Do not rely on transitive inclusions. Include all necessary headers directly.

### Naming

1. Use names that describe the purpose or intent of the object.
	- Minimize the use of abbreviations.
	- Do not abbreviate by deleting letters within a word.
	- Descriptiveness should be proportional to the name's scope of visibility.
	- For names written in mixed case prefer to capitalize abbreviations as single words: `XmlHttpRequest` rather than `XMLHTTPRequest`.
2. Filenames should be lowercase and can include underscores (_).
	- Make your filenames very specific: `http_server_logs.h` rather than `logs.h`.
	- The main file should be named `main.cpp`.
3. Use `camelCase` for variable names.
4. Use `PascalCase` for all types — classes, structs, and enums.
5. Use `PascalCase` for function names.
6. Use `SCREAMING_SNAKE_CASE` for constants.
7. Use `SCREAMING_SNAKE_CASE` for enum values.
8. Use `snake_case` for file-scope static variables and functions.
9. Use `snake_case_` with a trailing underscore for class member variables.
10. If naming something that is analogous to an existing C/C++ entity then follow the existing naming convention scheme.

### Scoping

- Use the smallest scope possible.
- Declare variables as close to their usage as possible.
- Initialize variables as close to their declaration as possible, preferably in the same line.
- Prefer to use a `for` loop instead of a `while` loop when the loop variable is only used within the loop.
- Prefer to use a range-based `for` loop instead of a traditional `for` loop when possible.
- Do not use `goto`.
- Do not use `setjmp` or `longjmp`.
- Do not use global variables.

### Comments

- Use `//` for comments.
- Use comments to explain why, not what.
- Use comments to explain complex algorithms or non-obvious code.
- Use comments to explain the intent of a function or class.
- Use comments to explain the purpose of a variable.
- Use TODO comments for code that is temporary, a short-term solution, or good-enough but not perfect.

### Macros

Avoid using macros whenever possible. If you must use a macro, use `SCREAMING_SNAKE_CASE` for the name.

### Structs vs. Classes

Use a struct only for passive objects that carry data; everything else is a
class.

The struct and class keywords behave almost identically in C++. We add our own
semantic meanings to each keyword, so you should use the appropriate keyword
for the data-type you're defining.

structs should be used for passive objects that carry data, and may have
associated constants. All fields must be public. The struct must not have
invariants that imply relationships between different fields, since direct user
access to those fields may break those invariants. Constructors, destructors,
and helper methods may be present; however, these methods must not require or
enforce any invariants.

If more functionality or invariants are required, or struct has wide visibility
and expected to evolve, then a class is more appropriate. If in doubt, make it
a class.

### Structs vs. Pairs and Tuples

Prefer to use a struct instead of a pair or a tuple whenever the elements can have meaningful names.

### Enums

Use `enum class` instead of `enum`.

### Pointers and References

- Prefer to use references instead of pointers.
- Use pointers only when you need to express the absence of a value.
- Use `nullptr` instead of `NULL` or `0`.

### Functions

- Functions should be short and sweet, and do just one thing.
- Functions should not be large enough to hold nested structures.
- Functions should have a small number of arguments.
- Prefer to use pass-by-reference instead of pass-by-value for large objects.
- Prefer to use pass-by-value for small objects.