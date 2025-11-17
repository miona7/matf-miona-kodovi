def Fibonacci():
    a, b = 0, 1
    while True:
        yield a
        a, b = b, a + b

if __name__ == '__main__':
    f = Fibonacci()
    for i in range(10):
        print(f, f.__next__())