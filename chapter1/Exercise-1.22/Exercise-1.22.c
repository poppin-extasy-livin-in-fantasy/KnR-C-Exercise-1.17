#include <stdio.h>

#define MAXLINE 1000
#define FOLD_LIMIT 20

void fold_line(char arr[], int lim);

int main() {
    char line[MAXLINE];
    fold_line(line, MAXLINE);
}


void fold_line(char arr[], int lim) {
    int i = 0;
    int last_blank_pos = -1;
    int c;

    /* Read input stream up to the buffer limit minus terminal safety */
    while (i < lim - 1 && (c = getchar()) != EOF) {
        arr[i++] = c;

        /* Keep track of the rightmost wrapping boundary */
        if (c == ' ' || c == '\t') {
            last_blank_pos = i - 1;
        }

        /* Flush on natural newline and reset state */
        if (c == '\n') {
            for (int j = 0; j < i; j++) {
                putchar(arr[j]);
            }
            i = 0;
            last_blank_pos = -1;
            continue;
        }

        /* Line length limit reached: trigger line breaking logic */
        if (i == FOLD_LIMIT) {
            if (last_blank_pos == -1) {
                /* Case A: No spaces found (oversized word). Force break at limit. */
                for (int j = 0; j < FOLD_LIMIT; j++) {
                    putchar(arr[j]);
                }
                putchar('\n');
                i = 0;
            }
            else {
                /* Case B: Wrap at the last available whitespace */
                for (int j = 0; j < last_blank_pos; j++) {
                    putchar(arr[j]);
                }
                putchar('\n');

                /* Shift the remaining trailing substring to the head of the buffer */
                int new_i = 0;
                for (int j = last_blank_pos + 1; j < FOLD_LIMIT; j++) {
                    arr[new_i++] = arr[j];
                }
                i = new_i;
                last_blank_pos = -1;
            }
        }
    }

    /* Flush any leftover characters remaining on EOF */
    if (i > 0) {
        for (int j = 0; j < i; j++) {
            putchar(arr[j]);
        }
    }
}