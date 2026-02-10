"""
Link: https://codeforces.com/contest/2194/problem/A
"""

def solve():
    t = int(input())
    while t>0:
        t = t-1
        n, w = map(int, input().split())
        quotient = n//w
        print(n - quotient)

solve()