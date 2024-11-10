import matplotlib.pyplot as plt
import csv
import os
from pathlib import Path
import re

path = Path("results")
csv_files = [fname for fname in os.listdir(path) if fname.endswith('.csv')]
print("csv files: ",csv_files)

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
        print("current file:", name)
        print("experiment:", experiment)

        i_list = []
        bt_t = []
        avg_bt_t = []
        st_t = []
        avg_st_t = []

        csv_reader.__next__()
        for row in csv_reader:
            i_list.append(int(row[0]))
            bt_t.append(int(row[1]))
            avg_bt_t.append(float(row[2]))
            st_t.append(int(row[3]))
            avg_st_t.append(float(row[4]))

        print("i_list:", i_list)
        print("bt_t:", bt_t)
        print("avg_bt_t:", avg_bt_t)
        print("st_t:", st_t)
        print("avg_st_t:", avg_st_t)
    
        plt.figure(experiment)
        plt.plot(
            i_list,
            avg_bt_t,
            label="Binary Tree",
            marker="o",
            linestyle="-",
            linewidth=2,
            markersize=4,
        )

        plt.figure(experiment)
        plt.plot(
            i_list,
            avg_st_t,
            label="Splay Tree",
            marker="o",
            linestyle="-",
            linewidth=2,
            markersize=4,
        )
        
        plt.figure(experiment)
        plt.legend()
        plt.savefig(os.path.join(path, name + ".png"), transparent=False)