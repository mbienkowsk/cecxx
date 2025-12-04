import numpy as np

import cecxx
from cecxx import CECEdition

dim = 10
x = np.full(dim, 10.0)
pop = np.stack([x, np.zeros(dim)])

print("--- Direct Evaluation (CEC2017 F1) ---")
print(f"Input: {x}")
val = cecxx.evaluate(CECEdition.CEC2017, 1, dim, x)
print(f"Result: {val}")

print("\n--- With Global Optimum Subtraction ---")
val_diff = cecxx.evaluate(CECEdition.CEC2017, 1, dim, x, subtract_y_global=True)
print(f"Result (shifted): {val_diff}")

print("\n--- Wrapped Evaluator (CEC2014 F2) ---")
f2 = cecxx.get_cec_function(CECEdition.CEC2014, 2, dim, subtract_y_global=True)
print(f"Global optimum for this function: {f2.y_global}")

print(f"Single evaluation: {f2(x)}")

print(f"Batch evaluation (first row is same as above):{f2(pop)}")
