# Python bindings for cecxx

## Installation
To build and install the {cecxx} library, the following dependencies are required:
* LLVM clang++ (>=v19) or GNU g++ (>=v14)
* cmake (>=v3.19)

via pip:
`pip install cecxx`

## Example usage
see `cecxx/example.py` (`uv run -m cecxx.example`) and below

## API

Two ways of evaluating a function are provided:

### 1. Direct Evaluation
Use `cecxx.evaluate` when you want to pass all parameters explicitly for a single call.

```python
cecxx.evaluate(
    edition: CECEdition,
    fn: int,
    dimension: int,
    x: np.ndarray,
    *,
    subtract_y_global: bool = False,
)
```

**Example:** Evaluating F30 of CEC2014 in 30 dimensions:
```python
import cecxx
import numpy as np
 
# Standard evaluation
cecxx.evaluate(cecxx.CECEdition.CEC2014, 30, 30, np.zeros(30))
> np.float64(3200.0)

# Evaluation relative to the global optimum
cecxx.evaluate(cecxx.CECEdition.CEC2014, 1, 30, np.zeros(30), subtract_y_global=True)
> np.float64(200.0)
```

With `subtract_y_global=True`, cecxx returns the difference between the result and the function's global optimum as per the suite definitions. **This is probably what you want**, as it is the grading criterion, but it remains opt-in.

### 2. Wrapped Evaluator
Use `get_cec_function` to create a callable object with fixed parameters.

```python
get_cec_function(
    edition: CECEdition, 
    number: int, 
    dimension: int, 
    *, 
    subtract_y_global: bool | None = None
)
```

This returns a wrapped evaluator which:
* **Permanently sets** the `edition`, `number`, `dimension`, and `subtract_y_global` settings.
* Contains extra metadata properties:
    * `number` - Number of the function.
    * `edition` - The underlying `CECEdition` enum.
    * `y_global` - Global value of the optimum as per the problem definitions.

**Example:**
```python
import cecxx
import numpy as np

# Create a specific evaluator for CEC2014 F30, 30D
f30 = cecxx.get_cec_function(cecxx.CECEdition.CEC2014, 30, 30)

# Now you only need to pass the input vector 'x'
f30(np.zeros(30))
> np.float64(3200.0)

# You can also bake the subtraction into the evaluator creation
f1_diff = cecxx.get_cec_function(cecxx.CECEdition.CEC2013, 1, 30, subtract_y_global=True)

f1_diff(np.zeros(30))
> np.float64(200.0)
```

### Batch Evaluation
Both interfaces support evaluating multiple points in one call by passing a 2D array:

```python
# Evaluates two points at once
points = np.stack((np.zeros(30), np.ones(30)))
cecxx.evaluate(cecxx.CECEdition.CEC2014, 30, 30, points)
> array([3.20000000e+03, 1.14047996e+07])
```

## Installation (development)
`uv sync` in the directory of this README
