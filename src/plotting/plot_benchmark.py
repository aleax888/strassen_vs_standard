import pandas as pd
import matplotlib.pyplot as plt
from pathlib import Path

# Rutas del proyecto
PROJECT_ROOT = Path(__file__).resolve().parents[2]
CSV_PATH = PROJECT_ROOT / "outputs/benchmark/benchmark_results.csv"
OUTPUT_DIR = PROJECT_ROOT / "outputs" / "plots"

OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

df = pd.read_csv(CSV_PATH)

for data_generation_type in df["data_generation_type"].unique():
    data = df[df["data_generation_type"] == data_generation_type]

    plt.figure(figsize=(8, 6))
    plt.plot(data["n"], data["insertion_sort_mean"], label="Insertion Sort")
    plt.plot(data["n"], data["merge_sort_mean"], label="Merge Sort")

    # plt.xscale("log") 

    plt.title(f"{data_generation_type}")
    plt.xlabel("n")
    plt.ylabel("Time (ns)")
    plt.legend()
    plt.grid(True, which="both")

    outfile = OUTPUT_DIR / f"{data_generation_type}.png"
    plt.savefig(outfile, dpi=150)
    plt.close()

print(f"Gráficos generados en {OUTPUT_DIR}")
