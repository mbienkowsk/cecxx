import numpy as np

from cecxx import bindings
from cecxx.core import get_cec_function
from cecxx.editions import CECEdition


def swap_order(arr: np.ndarray):
    return np.swapaxes(arr, 0, 1)


def cec2017(fn: int, input: np.ndarray):
    """Wrapper for evaluating a given cec2017 fun which takes care of array column/row majority and cpp return type"""
    dim: int = input.shape[1]
    return np.array(bindings.cec(2017, fn, dim, swap_order(input)))


# TODO: unit test
if __name__ == "__main__":
    cec1_2017 = get_cec_function(CECEdition.CEC2017, 1, 10)
    FN = 1
    print("ZEROS")
    input_zeros = np.zeros((2, 10))
    output = cec2017(FN, input_zeros)
    assert np.all(output == cec1_2017(input_zeros))
    print(f"output: {output}")
    print("=" * 20)

    print("ONES")
    input_ones = np.ones((2, 10))
    output = cec2017(FN, input_ones)
    assert np.all(output == cec1_2017(input_ones))
    print(f"output: {output}")
    print("=" * 20)

    print("100s")
    input_100s = np.full((2, 10), 100.0)
    output = cec2017(FN, input_100s)
    assert np.all(output == cec1_2017(input_100s))
    print(f"output: {output}")
    print("=" * 20)

    print("ZEROS & ZEROS")
    input_zeros_zeros = np.stack((np.zeros(10), np.zeros(10)), axis=0)
    output = cec2017(FN, input_zeros_zeros)
    assert np.all(output == cec1_2017(input_zeros_zeros))
    print(f"output: {output}")
    print("=" * 20)

    print("ZEROS & ONES")
    input_zeros_ones = np.stack((np.zeros(10), np.ones(10)), axis=0)
    output = cec2017(FN, input_zeros_ones)
    assert np.all(output == cec1_2017(input_zeros_ones))
    print(f"output: {output}")
    print("=" * 20)

    print("ZEROS & 100s")
    input_zeros_100s = np.stack((np.zeros(10), np.full(10, 100.0)), axis=0)
    output = cec2017(FN, input_zeros_100s)
    assert np.all(output == cec1_2017(input_zeros_100s))
    print(f"output: {output}")
    print("=" * 20)

    print("100s & ZEROS")
    input_100s_zeros = np.stack((np.full(10, 100.0), np.zeros(10)), axis=0)
    output = cec2017(FN, input_100s_zeros)
    assert np.all(output == cec1_2017(input_100s_zeros))
    print(f"output: {output}")
    print("=" * 20)
