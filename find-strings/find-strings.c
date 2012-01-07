// For this git commit, find-strings.c is incomplete.  That's because I'm trying something new in the Python version.
#include <stdio.h>
#include <stdlib.h>


#define MAX_M 2000


typedef struct {
    char * start;
    short lenth;
} Substring;


int num_substrings(int length);
Substring[] get_substrings(char[] string);


int num_substrings(int length) {
    return ((n * (n + 1)) / 2)
}


Substring[] get_substrings(char[] string) {
    size_t length = strlen(string);
    substrings[num_substrings] = malloc(num_substrings * sizeof (Substring));

    int current_substring = 0;
    for (int i = 1; i < length + 1; i++) {              // i is the length of the substrings currently being added
        for (int j = 0; j < length - i + 1; j++) {      // j is the index in the string that the substrings currently being added start at
            substrings[current_substring].start = &string[j];
            substrings[current_substring].length = i;
            current_substring++;
        }
    }
    
    return substrings;
}


int main() {
    int n;
    scanf("%d", &n);

    char lines[n][MAX_M + 1];
    for (int i = 0; i < n; i++) {
        scanf("%s", lines[i]);
    }
    
    for (int i = 0; i < n; i++) {
        get_substrings(lines[i]);                           // incomplete
    }
}
