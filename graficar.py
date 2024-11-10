import matplotlib.pyplot as plt
import csv
import os
from pathlib import Path
import re

path = Path("results")
csv_files = [fname for fname in os.listdir(path) if fname.endswith('.csv')]

plt.figure(1, figsize = (10,10), dpi=150)
plt.subplot()
plt.title("Experimento 1")
plt.xlabel("Inserciones")
plt.ylabel("Tiempo Promedio de Busqueda (ns)")
plt.grid()

plt.figure(2, figsize = (10,10), dpi=150)
plt.subplot()
plt.title("Experimento 2")
plt.xlabel("Inserciones")
plt.ylabel("Tiempo Promedio de Busqueda (ns)")
plt.grid()

plt.figure(3, figsize = (10,10), dpi=150)
plt.subplot()
plt.title("Experimento 3")
plt.xlabel("Inserciones")
plt.ylabel("Tiempo Promedio de Busqueda (ns)")
plt.grid()

plt.figure(4, figsize = (10,10), dpi=150)
plt.subplot()
plt.title("Experimento 4")
plt.xlabel("Inserciones")
plt.ylabel("Tiempo Promedio de Busqueda (ns)")
plt.grid()

for file in csv_files:
    with open(os.path.join(path, file)) as csv_file:
        name = Path(file).stem
        experiment = int(name.split("_")[1])
        csv_reader = csv.reader(csv_file, delimiter=",")
        
        i_list = []
        bt_t = []
        avg_bt_t = []
        st_t = []
        avg_st_t = []
        for row in csv_reader:
            try:
                i_list.append(int(row[0]))
                bt_t.append(int(row[2]))
                avg_bt_t.append(int(row[3]))
                st_t.append(int(row[2]))
                avg_st_t.append(int(row[3]))
            except:
                continue
        
        try:
            plt.figure(experiment)
            plt.plot(
                i_list,
                avg_bt_t,
                label="avg_bt_time ns",
                marker="o",
                linestyle="-",
                linewidth=2,
                markersize=4,
            )
        except:
            continue
        
        try:
            plt.figure(experiment)
            plt.plot(
                i_list,
                avg_st_t,
                label="avg_st_time ns",
                marker="o",
                linestyle="-",
                linewidth=2,
                markersize=4,
            )
        except:
            continue
        
        plt.figure(experiment)
        plt.legend()
        plt.savefig(os.path.join(path, name + ".png"), transparent=False)