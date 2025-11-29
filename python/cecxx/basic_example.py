from cecxx.bindings import run_example

if __name__ == "__main__":
    dims = [10, 30]
    if run_example(dims):
        print("Failed to run example")
    else:
        print("Finished")
