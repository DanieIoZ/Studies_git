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


if __name__ == "__main__":
    a = MyVector([1,5,8])
    b = MyVector([4,7,2])
    print(a.get_vector)
    print("Soucin: ", a*b)

