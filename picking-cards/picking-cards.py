#! /usr/bin/python


def add_one(dictionary, val):
    dictionary[int(val)] += 1
    return dictionary


def count_ways(N):
    num_dict = dict((i, 0) for i in range(N + 1))
    total_ways = 1
    opts = 0
    num_dict = reduce(add_one, raw_input().split(" "), num_dict)
    for i in range(N):
        opts += num_dict[i]
        total_ways *= (opts - i)
    return total_ways


def main():
    T = int(raw_input())
    for t in range(T):
        N = int(raw_input())
        print count_ways(N) % 1000000007


if __name__ == "__main__":
    main()
