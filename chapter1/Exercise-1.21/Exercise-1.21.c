#include <stdio.h>

#define MAXLINE 1000
#define TAB_WIDTH 8

int main() {
	char line[MAXLINE];

	while (entab(line, MAXLINE) > 0)
		printf("%s", line);
}

int entab(char s[], int lim) {
	int i = 0;
	int col = 0;
	int spaces = 0;
	int c = 0;


	while (i < lim - 1 && (c = getchar()) != EOF) {

		if (c == ' ') {
			spaces++;
			col++;

			if (col % TAB_WIDTH == 0) {
				s[i++] = '\t';
				spaces = 0;
			}
		}
		else if (c == '\n') {
			for (int k = 0; k < spaces; ++k) {
				if (i < lim - 1) {
					s[i++] = ' ';
				}
			}
			spaces = 0;

			if (i < lim - 1) {
				s[i++] = c;
			}
			col = 0;
			break;
		}
		else {
			for (int j = 0; j < spaces; ++j) {
				if (i < lim - 1) {
					s[i++] = ' ';
				}
			}
			spaces = 0;


			if (i < lim - 1) {
				s[i++] = c;
			}
			col++;
		}
	}
	s[i] = '\0';
	return i;
}