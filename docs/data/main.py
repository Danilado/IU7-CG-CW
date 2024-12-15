import matplotlib.pyplot as plt

x = []
y = []

with open("./rendout.txt", "r") as f:
    lines = f.readlines()
    for line in lines:
        values = line.split()
        x.append(int(values[0]))
        y.append(float(values[1]) / 1000 / 1000)

plt.plot(x, y)
plt.xlabel("Сторона сцены")
plt.ylabel("Время генерации кадра (в мс)")
plt.tight_layout()
plt.savefig("../img/rendprof.svg")
