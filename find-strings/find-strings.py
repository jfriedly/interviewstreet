#! /usr/bin/python

def get_substrings(string):
    substrings = set()
    for i in range(1, len(string) + 1):             # i is the length of the substrings currently being added
        for j in range(len(string) - i + 1):        # j is the index in the string that the substrings currently being added start at
            substrings = substrings.union([string[j:j+i]])
    return substrings
    

def main():
    n = int(raw_input())
    lines = []
    for i in range(n):
        lines.append(raw_input())

    los_of_substrings = map(get_substrings, lines)                 # lol = list of sets
    s = reduce(lambda x, y: x.union(y), los_of_substrings, set())
    l = list(s)
    l.sort()                                                       # can't chain this onto the previous line, not sure why

    length = len(l)
    Q = int(raw_input())
    for i in range(Q):
        q = int(raw_input())
        if not q <= length:
            print "INVALID"
        else:
            print l[q-1]

if __name__ == "__main__":
    main()
