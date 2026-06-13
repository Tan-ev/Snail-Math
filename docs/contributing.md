# Contributing to Snail-Math

Thank you for your interest in contributing to Snail-Math.

Snail-Math is maintained in spare time, so development may progress slowly. All contributions are appreciated.

## Building

```bash
cmake -B build
cmake --build build
```

## Coding Style

Snail-Math uses:

* C17 and C++20
* Allman style braces
* 2-space indentation
* No tabs

If a code block contains only one statement, the opening and closing braces should remain on the same line.

Example:

```cpp
if (expr)
{ statement(); }
else
{ statement(); }

if (expr)
{
  statement1();
  statement2();
}
```

## Naming Convention

### Functions

All public functions should use the `sm_` prefix.

```cpp
sm_abs()
sm_neg()
sm_cmp()
```

### Types

`Num` is the core type.

`CNum` is the C++ wrapper around `Num`.

```cpp
Num
CNum
```

## Pull Requests

Please:

* Keep changes small and focused.
* Follow the existing coding style.
* Avoid unnecessary dependencies.
* Preserve compatibility with the existing API whenever possible.

## Project Goal

The core identity of Snail-Math is its dynamic number type.

Improvements to performance, memory usage, and usability are always welcome.

Thank you for helping improve Snail-Math.
