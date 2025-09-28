# cecxx

Implementation of IEEE Congress of Evolutionary (CEC) Bound-constrained Single Objective Numerical Optimization benchmarks in
C++23.

## About

The `{cecxx}` is a novel implementation of IEEE CEC BC-SOP [^1] benchmarks in C++23, which compared to the [official implementation
](https://github.com/P-N-Suganthan?tab=repositories) does not:
- leak memory 
- involves multiple IO operations during each objective function call.

Solving the above problems results in reliable and fast implementation that is ready to be used in your numerical experiments.

> [!NOTE]
> This **is not** official implementation of CEC BC-SOP benchmarks. However, it can be used as a drop-in replacement. The
> `{cecxx}` is extensively tested to be compliant with the official implementations by emplyoing property-based testing. See
> [test/compliance](https://codeberg.org/ewarchul/cecxx/src/branch/main/test/compliance) for details.


[^1]: Bound-constrained single objective problem.
