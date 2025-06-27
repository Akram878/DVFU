class Summator:
    def transform(self, n):
        return n
    def sum(self, N):
        summ = 0
        for n in range(1, N + 1):
            summ += self.transform(n)
        return summ

class SquareSummator(Summator):
    def transform(self, n):
        return n**2
class CubeSummator(Summator):
    def transform(self, n):
        return n**3

print(Summator().sum(4))
print(SquareSummator().sum(3))
print(CubeSummator().sum(5))