#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_M 2000
#define MAX_N 50


typedef struct {
    char * start;
    int length;
} Substring;


int num_substrings(int length);
Substring * get_substrings(char * string, int line);
char * get_string (Substring subs);
int indexcmp(Substring * subs1, Substring * subs2);
Substring * uniquify(Substring * sorted_substrings);


int num_substrings(int n) {                             // The number of substrings in any string is given by this formula (it's the sum of Pascal's Triangle)
    return ((n * (n + 1)) / 2);
}


char * get_string (Substring subs) {
    char * substring = malloc(subs.length + 1);     // add one so that strncpy will pad them with each with a null character
    strncpy(substring, subs.start, subs.length);
    substring[subs.length] = '\0';
    return substring;
}


int indexcmp(Substring * subs1, Substring * subs2) {
    // Need to tell strcmp how to get to the individual substrings instead of just giving it structs
    int i;
    char * subs1str = get_string(*subs1);
    char * subs2str = get_string(*subs2);    
    int answer = strcmp(subs1str, subs2str);
    free(subs1str);
    free(subs2str);
    return answer;
}


Substring * uniquify(Substring * sorted_substrings) {
    int i, uniques = 0;
    Substring * unique_substrings = malloc(sizeof (sorted_substrings));
    for (i = 0; i < (sizeof (sorted_substrings) / sizeof (Substring)); i++ ) {
        if (indexcmp(&sorted_substrings[i], &sorted_substrings[i + 1])) {
            unique_substrings[uniques] = sorted_substrings[i];
            uniques++;
        }
    }
    return unique_substrings;
}


// global
char lines[MAX_N][MAX_M + 1];


int main() {
    int i, j, n, Q, q, current_index = 0, total_substrings = 0;
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%s", lines[i]);
        total_substrings += num_substrings(strlen(lines[i]));
    }
    
    Substring list_of_substrings[total_substrings];
    for (i = 0; i < n; i++) {
        Substring * current_substrings = get_substrings(lines[i], i);
        for (j = 0; j < num_substrings(strlen(lines[i])); j++) {                //  Tried to use memcpy instead of this for loop, didn't work, idk why not
            list_of_substrings[current_index] = current_substrings[j];
            current_index++;
        }
    }

    qsort(list_of_substrings, total_substrings, sizeof (Substring), indexcmp);  // warning here is because qsort's compare is supposed to take void pointers (any type) but we can't use those
    printf("---past sorting");
    scanf("%d", &i);
    Substring * unique_substrings = uniquify(list_of_substrings);
    free(list_of_substrings);
    printf("---past uniquifying");
    scanf("%d", &i);

    scanf("%d", &Q);
    int length = (sizeof (unique_substrings) / sizeof (Substring));
    for (i = 0; i < Q; i++){
        scanf("%d", &q);
        if (!(q <= length)) {
            printf("INVALID\n");
        } else {
            char * substring = get_string(unique_substrings[q]);
            printf("%s\n", substring);
            free(substring);
        }
    }

    free(unique_substrings);
    return 0;
}


Substring * get_substrings(char * string, int line) {
    int i, j;
    size_t length = strlen(string);
    Substring * substrings = malloc(num_substrings(length) * sizeof (Substring));

    int current_substring = 0;
    for (i = 1; i < length + 1; i++) {              // i is the length of the substrings currently being added
        for (j = 0; j < length - i + 1; j++) {      // j is the index in the string that the substrings currently being added start at
            substrings[current_substring].start = &lines[line][j];
            substrings[current_substring].length = i;
            current_substring++;
        }
    }
    
    return substrings;
}
