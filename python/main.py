import os
import sys
import pandas as pd
import numpy as np
import io

dir_path = os.path.dirname(os.path.realpath(__file__))

if __name__ != "__main__":
    exit()

# ===============================================================================================
def load_file_data(filename: str) -> dict[str, float]:
    result = {}
    with open(filename) as file:
        for line in [line.rstrip() for line in file]:
            graph: str = line.split(" ")[0]
            graph = graph.split("/")[-1]
            score: float = float(line.split(" ")[1])
            result[graph] = score
    return result
def load_all_data(directory: str, weighted: bool) -> dict[str, dict[str, float]]:
    result: dict[str, dict[str, float]] = {}
    for file in os.listdir(os.fsencode(directory)):
        filename: str = os.fsdecode(file)
        if filename.endswith(".txt"):
            if filename.endswith("Weighted.txt") == weighted:
                result[filename.removesuffix(".txt")] = load_file_data(directory + "/" + filename)
    return result

def normalize_data(data: dict[str, dict[str, float]]):
    max_scores: dict[str, float] = {}
    for _, results in data.items():
        for graph, score in results.items():
            max_scores[graph] = max(score, max_scores.get(graph, score))
    
    for _, results in data.items():
        for graph, max_score in max_scores.items():
            if (graph in results):
                results[graph] /= max_score

data: dict[str, dict[str, float]] = load_all_data(dir_path + "/../run", weighted=False)
normalize_data(data)

def mean_data(data: dict[str, dict[str, float]]) -> dict[str, float]:
    output: dict[str, float] = {}
    for algo, results in data.items():
        output[algo] = 0
        count = 0
        for _, score in results.items():
            output[algo] += score
            count += 1
        if (count != 0):
            output[algo] /= count
    return output

# ===============================================================================================

import matplotlib.pyplot as plt
from matplotlib.widgets import Slider, Button
from matplotlib.backend_bases import MouseEvent
from matplotlib.text import Annotation

fig, ax = plt.subplots()
fig.subplots_adjust(left=0.1, right=0.9, bottom=0.3, top=0.99)

plot_data: list[tuple[str, list[float]]] = []
for algo, results in data.items():
    if "Worst" in algo or "First" in algo:
        continue
    plot_data.append((algo, [v for v in results.values()]))

plot_data = sorted(plot_data, key=lambda d: d[0])

ax.boxplot([d[1] for d in plot_data], tick_labels=[d[0] for d in plot_data])
ax.tick_params(axis='x', labelrotation=90)
ax.set_ylabel("scores")
plt.show()