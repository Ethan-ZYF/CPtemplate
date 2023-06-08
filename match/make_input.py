import random

A = [2**i for i in range(1, 10)]
B = [5**i for i in range(1, 10)]
C = [3**i for i in range(1, 10)]
C += C
C += A + B
C.sort()
T = 10
print(T)
for t in range(T):
    N = 10
    K = random.randint(1, 11)
    print(N, K)
    for i in range(N):
        # print(random.randint(1, 1000), end=" ")
        print(random.choice(C), end=" ")
    print()
