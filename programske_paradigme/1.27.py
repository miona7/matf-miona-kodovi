class Stack:

    def __init__(self):
        self.items = []
        self.n = 0

    def push(self, e):
        self.items.append(e)
        self.n += 1

    def pop(self):
        try:
            e = self.items.pop()
            self.n -= 1
            return e
        except IndexError as e:
            print("Stack is empty, can not pop!")
            print(e)
            return None
    
    def peek(self):
        try:
            e = self.items[-1]
            return e
        except IndexError as e:
            print("Stack is empty, can not peek!")
            print(e)
            return None
    
    def size(self):
        return self.n
    
if __name__ == '__main__':
    s1 = Stack()
    s1.push(1)
    s1.push(2)
    s1.push(3)
    print("Size", s1.size())
    print(s1.pop())
    print("Size", s1.size())
    print(s1.peek())
    print("Size", s1.size())
    s1.push(69)
    print("Size", s1.size())
    print(s1.peek())
    print("Size", s1.size())