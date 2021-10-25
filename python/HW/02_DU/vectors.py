import math

class MyVector:
    def __init__(self, coords):
        self.coords = coords
    
    def get_vector(self):
        return self.coords
    
    def __mul__(self, other):
        if len(self.coords) != len(other.coords):
            return
        sum = 0
        for i in range(0, len(self.coords)):
            sum += self.coords[i] * other.coords[i]
        return sum
    
    def __add__(self, other):
        if len(self.get_vector()) != len(other.get_vector()):
            return
        Vector = MyVector([])
        for i in range(0, len(self.coords)):
            Vector.coords.append(self.coords[i] + other.coords[i])
        return Vector

    def norm(self):
        sum = 0
        for i in range(0, len(self.coords)):
            sum += self.coords[i] * self.coords[i]
        return math.sqrt(sum)

if __name__ == "__main__":
    a = MyVector([1,5,8])
    b = MyVector([4,7,2])
    print(a.get_vector)
    print("Soucin: ", a*b)

    c = a+b
    print(c.get_vector())

    print(MyVector([1]).norm())
    print(MyVector([3,4]).norm())
    print(MyVector([1,1,2**0.5]).norm())

