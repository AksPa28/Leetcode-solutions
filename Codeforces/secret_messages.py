"""
https://codeforces.com/contest/2194/problem/C
"""

t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    strList = [input().strip() for _ in range(k)]
    divisors = []
    i = 1
    while True:
        if i * i > n:
            break
        if n % i == 0:
            divisors.append(i)
            if n // i != i:
                divisors.append(n//i)
    divisors.sort()
    for divisor in divisors:
        divisors.append(i)
    