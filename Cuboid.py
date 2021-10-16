class Cuboid:
    def __init__(self, a,b,c):
        self.a = a
        self.b = b
        self.c = c
    def compute_surface(self):
        return self.a*self.b*4 + self.b*self.c*2

    def make_enlarged_copy(self, a1,b1,c1):
        return Cuboid(self.a * a1, self.b * b1, self.c * c1)

if __name__=="__main__":
    Cube1 = Cuboid(1,2,3)
    print(Cube1.compute_surface())

    Cube2 = Cube1.make_enlarged_copy(2,2,2)
    print(type(Cube2))
    print(Cube2.compute_surface())
