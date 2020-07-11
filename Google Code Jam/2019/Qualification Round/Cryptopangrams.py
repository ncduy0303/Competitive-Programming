# It is easier to solve this problem using Python instead of C++ because of big integers

from math import gcd

def isqrt(n):
    x = n
    y = (x + 1) // 2
    while y < x:
        x = y
        y = (x + n // x) // 2
    if x * x == n: return x
    return None

T = int(input())
for t in range(1, T + 1):
    N, L = map(int, input().split())
    A = list(map(int, input().split()))

    vals = [None for i in range(L + 1)]
    for i in range(L):
        r = isqrt(A[i])
        if r is not None:
            vals[i + 1] = r
            break
    else:
        for i in range(L - 1):
            g = gcd(A[i], A[i + 1])
            if g < A[i]:
                # prime number
                vals[i + 1] = g
                break

    for j in range(i, -1, -1):
        vals[j] = A[j] // vals[j + 1]
    for j in range(i + 2, L + 1):
        vals[j] = A[j - 1] // vals[j - 1]

    primes = {v:chr(ord('A')+i) for i,v in enumerate(sorted(set(vals)))}

    ans = "".join(primes[v] for v in vals)

    print("Case #{t}: {ans}".format(t = t, ans = ans))
