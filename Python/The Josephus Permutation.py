# built-in libraries
from collections import deque
import time

def solution(array, k):
    deck = deque(array) # a better list so its faster
    permutation = []

    while deck:
        deck.rotate(1 - k)
        item = deck.popleft()
        permutation.append(item)

    return permutation

Qsoldiers = 1_000_000
QsoldiersArr = [arr+1 for arr in range(Qsoldiers)]
k = 3

Qstart = time.perf_counter()
QsolutionF = solution(QsoldiersArr, k)
Qstop = time.perf_counter()

#print(QsolutionF)
print(f"Time took to calculate : {Qstop-Qstart}")


def slowSolution(array, k):
    permutation = []
    index = 0

    while array:
        index = (index + k - 1) % len(array)
        item = array.pop(index)
        permutation.append(item)

    return permutation

soldiers = 1_000_000
soldiersArr = [arr+1 for arr in range(soldiers)]
k = 3

start = time.perf_counter()
SolutionF = slowSolution(soldiersArr, k)
stop = time.perf_counter()

#print(SolutionF)
print(f"time took to calculate : {stop-start}")