class Stack:
    def __init__(self, StackSize):
        self.MyStack = []
        self.StackSize = StackSize

    def DisplayStack(self):
        print('Stack currently contains:')
        for item in self.MyStack:
            print(item)

    def Push(self, Value):
        if len(self.MyStack) < self.StackSize:
            self.MyStack.append(Value)
        else:
            print('Stack is full!')

    def Pop(self):
        if len(self.MyStack) > 0:
            print('Popping:', self.MyStack.pop())

        else:
            print('Stack is empty!')


import queue

MyQueue = queue.Queue(3)

print(f'Queue Empty: {MyQueue.empty()}')
MyQueue.put(1)
MyQueue.put(2)
MyQueue.put(3)


print(f'Queue Full: {MyQueue.full()}')

print(f'Popping: {MyQueue.get()}')
print(f'Popping: {MyQueue.get()}')
print(f'Popping: {MyQueue.get()}')
