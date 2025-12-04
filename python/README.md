# Python bindings for cecxx

## Installation
To build and install the {cecxx} library, the following dependencies are required:
* LLVM clang++ (>=v19) or GNU g++ (>=v14)
* cmake (>=v3.19)

via pip:
`pip install cecxx`

## API

Two ways of evaluating a function are shared:

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
evaluates a function with the given parameters once.

Example of evaluating F30 of CEC2014:
```python
import cecxx
import numpy as np
 
cecxx.evaluate_cec(cecxx.CECEdition.CEC2014, 30, 30, np.zeros(30))
> np.float64(3200.0)

cecxx.evaluate_cec(cecxx.CECEdition.CEC2013, 1, 30, np.zeros(30), subtract_y_global=True)
> np.float64(200.0)
```

With `subtract_y_global` you can make cecxx return the difference between the function's global optimum as per the definitions for the given suite, **this is probably what you want to do** since this is the grading criterium, but it's opt-in nonetheless.



```python
get_cec_function(edition: CECEdition, number: int)
```

returns a wrapped evaluator which:
* permanently sets the edition and fn params when evaluating
* contains some extra info:
    * `number` - number of the function
    * `edition` - the underlying CECEdition enum for whatever reason you might need it
    * `y_global` - global value of the optimum as per the problem definitions for the given suite

Example of the same calls with this approach:
```python
import cecxx
import numpy as np

cec30_2014 = cecxx.get_cec_function(cecxx.CECEdition.CEC2014, 30)

cec30_2014(30, np.zeros(30))
> np.float64(3200.0)

cec30_2014(30, np.zeros(30), subtract_y_global=True)
> np.float64(200.0)
```

Both interfaces support evaluating multiple points in one call:
```python
cecxx.evaluate(cecxx.CECEdition.CEC2014, 30, 30, np.stack((np.zeros(30), np.ones(30))))
> array([3.20000000e+03, 1.14047996e+07])
```


## Installation (development)
`uv sync` in the directory of this README
