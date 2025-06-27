class MyVector:
    def __init__(self, x, y):
        self.x, self.y = x, y

    def __add__(self, other):
        return MyVector(self.x + other.x, self.y + other.y)

    def __sub__(self, other):
        return MyVector(self.x - other.x, self.y - other.y)

    def __mul__(self, num):
        return MyVector(self.x * num, self.y * num)

    def __rmul__(self, num):
        self.x *= num
        self.y *= num
        return self

    def __imul__(self, num):
        self.x *= num
        self.y *= num
        return self

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

    def __ne__(self, other):
        return self.x != other.x or self.y != other.y

    def __abs__(self):
        return (self.x**2 + self.y**2)**(1/2)

    def __repr__(self):
        return f"MyVector({self.x}, {self.y})"


v1 = MyVector(-2, 5)
v2 = MyVector(3, -4)
v_sum = v1 + v2
print(v_sum)
v_minus = v1 - v2
print(v_minus)
v_multri = v1 * 5
print(v_multri)
v_multle = 5 * v1
print(v_multle)
v_mult = v1
v_mult *= 5
print(v_mult)
print(v1 == v2)
print(v1 != v2)
print(abs(v1))