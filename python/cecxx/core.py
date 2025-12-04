import warnings
from dataclasses import dataclass, field
from functools import partial
from typing import Callable

import numpy as np

from cecxx.bindings import cec
from cecxx.editions import CECEdition


class DimensionMismatchError(ValueError): ...


def check_dimension(arr: np.ndarray, dimension: int):
    if (input_dimension := arr.shape[1]) != dimension:
        raise DimensionMismatchError(
            f"Array dimension ({input_dimension}) doesn't match the provided dimension ({dimension})"
        )


def evaluate(
    edition: CECEdition,
    fn: int,
    dimension: int,
    x: np.ndarray,
    *,
    subtract_y_global: bool = False,
):
    """Evaluate a CEC function of a given edition and number"""
    x_packed = np.atleast_2d(x)
    check_dimension(x_packed, dimension)
    x_column_major = np.swapaxes(x_packed, 0, 1)
    return_value = np.array(cec(edition.value, fn, dimension, x_column_major))

    return_value = (
        return_value
        if not subtract_y_global
        else return_value - edition.optimum_for_function(fn)
    )

    if subtract_y_global and (return_value < 0).all():
        warnings.warn(
            f"y - global_optimum < 0 for {edition}.F{fn} detected - this shouldn't happen",
            category=RuntimeWarning,
        )

    return return_value if len(return_value) > 1 else return_value[0]


@dataclass
class WrappedCECEvaluator:
    evalutor: Callable[[np.ndarray], np.ndarray | np.float64]
    number: int
    edition: CECEdition
    y_global: float = field(init=False)
    subtract_y_global: bool | None

    def __post_init__(self):
        self.y_global = self.edition.optimum_for_function(self.number)

    def __call__(self, x: np.ndarray):
        return self.evalutor(x)


def get_cec_function(
    edition: CECEdition,
    number: int,
    dimension: int,
    *,
    subtract_y_global: bool | None = None,
):
    """Get a CEC function from a given edition and number as a callable"""
    kwargs = (
        {"subtract_y_global": subtract_y_global}
        if subtract_y_global is not None
        else {}
    )
    cec_function = partial(evaluate, edition, number, dimension, **kwargs)
    return WrappedCECEvaluator(cec_function, number, edition, subtract_y_global)
