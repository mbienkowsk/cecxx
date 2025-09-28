# cecxx

Implementation of IEEE Congress of Evolutionary (CEC) Bound-constrained Single Objective Numerical Optimization benchmarks in
C++23.

## About

The `{cecxx}` is a novel implementation of IEEE CEC BC-SOP benchmarks in C++23, which compared to the [official implementation
](https://github.com/P-N-Suganthan?tab=repositories) does not:
- leak memory 
- involve multiple IO operations during each objective function call.

Solving the above problems results in reliable and fast implementation that is ready to be used in your numerical experiments.

Check [example
directory](https://codeberg.org/ewarchul/cecxx/src/branch/main/example)
to see how to use this library. The `{cecxx}` includes also free-standing
implementations of objective functions utlized by CEC benchmarks, see
[include/cecxx/functions](https://codeberg.org/ewarchul/cecxx/src/branch/main/include/cecxx/functions)
for details.

> [!NOTE]
> This **is not** official implementation of CEC BC-SOP benchmarks. However, it can be used as a drop-in replacement. The
> `{cecxx}` is extensively tested to be compliant with the official implementations by emplyoing property-based testing. See
> [test/compliance](https://codeberg.org/ewarchul/cecxx/src/branch/main/test/compliance) for details.

## Installation

To install the `{cecxx}` with `cmake` and GNU Makefile generator, run below commads:

```sh
git clone https://codeberg.org/ewarchul/cecxx.git
pushd cecxx
mkdir build && cd build
cmake .. 
sudo make install
popd
```

If you are using `just` then you can run: 

```sh
CXX=clang++ just setup
```

to build and install the library with the clang compiler. See
[Justfile](https://codeberg.org/ewarchul/cecxx/src/branch/main/Justfile) for
details.
