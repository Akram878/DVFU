 #свой map A
arr = [int(i) for i in input().split(" ")]

def func(x):
  return x + 5
def maps(fun, arr):
    we = []
    for i in arr:
         we.append(fun(i))
    return we
print(maps(func, arr))