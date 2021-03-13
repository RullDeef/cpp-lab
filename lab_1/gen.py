class Mesh:
    def __init__(self, points=[], edges=[]):
        self.points = [p[:] for p in points]
        self.edges = [e[:] for e in edges]
    
    @staticmethod
    def path(points):
        res = Mesh(points)
        for i in range(len(points) - 1):
            res.edges.append([i, i + 1])
        return res
    
    @staticmethod
    def poly(points):
        res = Mesh(points)
        res.edges = [[0, len(points) - 1]]
        for i in range(len(points) - 1):
            res.edges.append([i, i + 1])
        return res
    
    @staticmethod
    def merge(mesh1, mesh2):
        res = Mesh()
        res.points = mesh1.points + mesh2.points
        res.edges = mesh1.edges
        off = len(mesh1.points)
        for edge in mesh2.edges:
            res.edges.append([edge[0] + off, edge[1] + off])
        return res
    
    @staticmethod
    def merge_connect(mesh1, mesh2):
        res = Mesh()
        res.points = mesh1.points + mesh2.points
        res.edges = mesh1.edges
        off = len(mesh1.points)
        for edge in mesh2.edges:
            res.edges.append([edge[0] + off, edge[1] + off])
        for i in range(off):
            res.edges.append([i, i + off])
        return res
    
    def translate(self, dx, dy, dz):
        for point in self.points:
            point[0] += dx
            point[1] += dy
            point[2] += dz

    def scale(self, fx, fy, fz):
        for point in self.points:
            point[0] *= fx
            point[1] *= fy
            point[2] *= fz

    def solidify_z(self, thinkness):
        front = Mesh(self.points, self.edges)
        back = Mesh(self.points, self.edges)
        front.translate(0, 0, thinkness / 2)
        back.translate(0, 0, -thinkness / 2)
        return Mesh.merge_connect(front, back)
    
    def save(self, filename):
        file = open(filename, "wt")
        print(len(self.points), file=file)
        for point in self.points:
            print(*point, sep=" ", file=file)
        print(len(self.edges), file=file)
        for edge in self.edges:
            print(edge[0], edge[1], file=file)

if __name__ == "__main__":
    w = 1
    c = Mesh.poly([
        [-1, 3, 0],
        [-4, 3, 0],
        [-4, -2, 0],
        [-1, -2, 0],
        [-1, -1, 0],
        [-3, -1, 0],
        [-3, 2, 0],
        [-1, 2, 0]
    ]).solidify_z(w)

    p = lambda: Mesh.poly([
        [1, 2, 0],
        [0, 2, 0],
        [0, 1, 0],
        [-1, 1, 0],
        [-1, 0, 0],
        [0, 0, 0],
        [0, -1, 0],
        [1, -1, 0],
        [1, 0, 0],
        [2, 0, 0],
        [2, 1, 0],
        [1, 1, 0]
    ]).solidify_z(w)

    p1 = p()
    p2 = p()
    p2.translate(4, 0, 0)

    mesh = Mesh.merge(c, Mesh.merge(p1, p2))
    mesh.save("test.txt")