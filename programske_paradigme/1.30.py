class MyIterator:
    def __init__(self, limit):
        self.limit = limit

    def __iter__(self):
        self.i = 0
        return self

    def __next__(self):
        self.i += 1
        if self.i > self.limit:
            raise StopIteration
        return self.i
    
def MyGenerator():
    for i in range(5):
        yield i

if __name__ == '__main__':
    # for i in MyIterator(10):
    #    print(i)

    g = MyGenerator()
    for i in g:
        print(i)
    