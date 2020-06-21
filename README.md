# Cubesolve

*Rubik's cube solver* by [lol-cubes](https://github.com/lol-cubes)

---

## Summary

Cubesolve is a command-line tool that takes an input scramble and method and outputs the sequence of moves that would be required to solve the cube using that method.

## Installation

### Install by Cloning

```bash
git clone 'https://github.com/lol-cubes/cubesolve.git'
cd cubesolve
make
make install
```

### Install with Homebrew

*Coming Soon*

## Usage

`cubesolve <scramble> <method>`

- `scramble`: A scramble using WCA notation or `auto`, which will generate a random scramble.
- `method`: One of the following methods.
    - `opop`* - Old Pochman Edges and Old Pochman Corners 3BLD method.
    - `lbl`* - Layer-by-layer beginner's method.
    - `is` - Inverse scramble.

*Not yet implemented