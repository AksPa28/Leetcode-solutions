"""
Link: https://codeforces.com/contest/2194/problem/B
"""

def solve():
    t = int(input())
    while t>0:
        t = t-1
        n, x, y = map(int, input().split())
        vals = list(map(int, input().split()))
        total = 0
        ans = 0
        for e in vals:
            total += e//x
        for e in vals:
            ans = max((total - e//x)*y + e, ans)
        print(ans)
        
solve()