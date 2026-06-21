# closed form: N = int(input()); ans = (N+1)/2 - ((N-2) + 1/(2**(N-1))) / N
# since absolute error is no more than 1e-6, we want 2 / N < 1e-6 / 2 --> N > 4e6 (here, I use 1e7 to be safe)
N = int(input())
if N < 1e7:
    ans = (N + 1) / 2 - (N - 2 + 1 / (1 << (N - 1))) / N
    print(f"{ans:.6f}")
else:
    print(str((N - 1) // 2) + ('.5' if (N - 1) % 2 == 1 else ''))