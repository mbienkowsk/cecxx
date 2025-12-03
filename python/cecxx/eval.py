import numpy as np

from cecxx import bindings


def swap_order(arr: np.ndarray):
    return np.swapaxes(arr, 0, 1)


def cec2017(fn: int, input: np.ndarray):
    """Wrapper for evaluating a given cec2017 fun which takes care of array column/row majority and cpp return type"""
    dim: int = input.shape[1]
    return np.array(bindings.cec(2017, fn, dim, swap_order(input)))


# TODO: unit test
if __name__ == "__main__":
    DIM = 10
    FN = 1
    print("ZEROS")
    input = np.zeros((2, 10))
    output = cec2017(FN, input)
    print(f"output: {output}")
    print("=" * 20)
    print("ONES")
    output = cec2017(FN, np.ones((2, 10)))
    print(f"output: {output}")
    print("=" * 20)
    print("100s")
    output = cec2017(FN, np.full((2, 10), 100.0))
    print(f"output: {output}")
    print("=" * 20)
    print("ZEROS & ZEROS")
    output = cec2017(FN, np.stack((np.zeros(10), np.zeros(10)), axis=0))
    print(f"output: {output}")
    print("=" * 20)
    print("ZEROS & ONES")
    output = cec2017(FN, np.stack((np.zeros(10), np.ones(10)), axis=0))
    print(f"output: {output}")
    print("=" * 20)
    print("ZEROS & 100s")
    output = cec2017(FN, np.stack((np.zeros(10), np.full(10, 100.0)), axis=0))
    print(f"output: {output}")
    print("=" * 20)
    print("100s & ZEROS")
    output = cec2017(FN, np.stack((np.full(10, 100.0), np.zeros(10)), axis=0))
    print(f"output: {output}")
