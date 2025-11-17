import math as m

class Shape:
    def __init__(self, color = "black", filled = False):
        self.__color = color
        self._filled = filled

    def get_color(self):
        return self.__color

    def get_filled(self):
        return self._filled
    
    def set_color(self, color):
        self.__color = color

    def set_filled(self, filled):
        self._filled = filled

class Rectangle(Shape):
    def __init__(self, length, width):
        super().__init__(color="red", filled=False)
        self.__length = length
        self.__width = width

    def area(self):
        return self.__length * self.__width
    
    def perimeter(self):
        return 2 * (self.__length + self.__width)

class Circle(Shape):
    def __init__(self, r):
        super().__init__(color="green", filled=True)
        self.r = r

    def area(self):
        return self.r**2 * m.pi
    
    def perimeter(self):
        return 2 * self.r * m.pi


if __name__ == '__main__':
    # s1 = Shape("blue", True)
    # print(s1.get_color())
    r = Rectangle(5, 10)
    print(r.area())
    print(r.perimeter())
    print(r.get_color())

    c = Circle(3)
    print(c.area())
    print(c.perimeter())
    print(c._filled)