#! /usr/bin/python
# What's the formula that determines the M coin tosses required to get N heads in a row, on average?
# From experimentally determined data:
#   f(N) =  M
#   f(1) =  2
#   f(2) =  6
#   f(3) = 14
#   f(4) = 30
#   f(5) = 62
#
# Therefore I believe the formula is:
#   f(N) = f(N-1) + 2 ^ N


def prob_formula(N, a, b, adder):
    i = 1
    while i < N:
        a, b = b, b + 2**(i + adder)
        i += 1
    return a


def calculate_tosses(n, m):
    if n == m:
        return 0
    elif m == 0:
        return prob_formula(n, 2, 6, 2)
    elif n - m == 1:                                                           # 0 < m < n
        return 1 + (.5 * prob_formula(n, 2, 6, 2))
    else:
        base = prob_formula(n-m, 4, 12, 3)
        for i in range(n - (n- m + 1)):
            base *= 2
        return base


def main():
    T = int(raw_input())
#    print prob_formula(4, 4, 12, 3), prob_formula(3,4,12,3), prob_formula(2,4,12,3)
    for i in range(T):
        n, m = [int(x) for x in raw_input().split(" ")]
        print "%.2f" % calculate_tosses(n, m)



if __name__ == "__main__":
    main()
