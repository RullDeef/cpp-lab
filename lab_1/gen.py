import numpy as np

R = 4

r = lambda t: np.sqrt(R * R - t * t)

x = lambda t: r(t) * np.sin(3 * np.pi * t)
y = lambda t: r(t) * np.cos(4 * np.pi * t)
z = lambda t: t

points = [(x(t), y(t), z(t)) for t in np.linspace(-R, R, 100)]

with open("model.txt", "wt") as file:
    for point in points:
        print(*point, sep=" ", file=file)
    print(file=file)
    for i in range(len(points) - 1):
        print(i, i + 1, file=file)
