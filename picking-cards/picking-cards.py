#! /usr/bin/python


def count_ways(N, cards):
    cards.sort()
    cards.reverse()
    total_ways = 1
    for i in range(N):
        opts = len(filter(lambda c: c <= i, cards))
        total_ways *= opts
        cards.pop()
    return total_ways


def main():
    T = int(raw_input())
    for t in range(T):
        N = int(raw_input())
        cards = [int(x) for x in raw_input().split(" ")]
        num_ways = count_ways(N, cards)
        print num_ways % 1000000007


if __name__ == "__main__":
    main()
