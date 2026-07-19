import importlib


def check_dependencies() -> None:
    packages = ["pandas", "numpy", "matplotlib"]
    missing = []

    print("Checking dependencies:")

    for package in packages:
        try:
            module = importlib.import_module(package)
            print(f"[OK] {package} ({module.__version__}) - Ready")
        except ImportError:
            print(f"[KO] {package} - Missing!")
            missing.append(package)

    if missing:
        print("\nMissing dependencies detected.")
        print("Install with pip:")
        print("    pip install -r requirements.txt")
        print("\nOr with Poetry:")
        print("    poetry install")
        exit(1)


try:
    import numpy as np
    import pandas as pd
    import matplotlib
except Exception:
    check_dependencies()


def generate_data() -> "pd.DataFrame":
    values = np.random.randint(0, 100, 1000)

    df = pd.DataFrame({
        "Value": values
    })

    return df


def generate_visuals(df: "pd.DataFrame") -> None:
    import matplotlib.pyplot as plt

    plt.figure(figsize=(8, 5))
    plt.hist(df["Value"], bins=20)
    plt.title("Matrix Data Distribution")
    plt.xlabel("Value")
    plt.ylabel("Frequency")
    plt.savefig("matrix_analysis.png")
    plt.close()


def compare_pip_poetry() -> None:
    print("\nInstalled package versions:")
    print(f"  pandas: {pd.__version__}")
    print(f"  numpy: {np.__version__}")
    print(f"  matplotlib: {matplotlib.__version__}")

    print("\npip vs Poetry:")
    print("  pip    -> pip install -r requirements.txt")
    print("            (no lock file, manual freeze)")
    print("  Poetry -> poetry install")
    print("            (uses poetry.lock, reproducible builds)")


def main() -> None:
    print("LOADING STATUS: Loading programs...\n")

    compare_pip_poetry()

    print("\nAnalyzing Matrix data...")

    df = generate_data()

    print(f"Processing {len(df)} data points...")
    print("Generating visualization...")

    generate_visuals(df)

    print("\nAnalysis complete!")
    print("Results saved to: matrix_analysis.png")


if __name__ == "__main__":
    main()
