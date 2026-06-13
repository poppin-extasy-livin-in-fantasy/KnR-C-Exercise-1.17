#include <stdio.h>

#define MAXLIM 1000
#define MINCHAR 80

int getline(char arr[], int lim);
void copy(char from[], char to[]);

int main() {
	int line, min, len;
	char minline[MAXLIM];
	int curleng = 0;
	char currentline[MAXLIM];

	min = MINCHAR;
	while ((len = getline(currentline, MAXLIM)) > 0) {
		if (len >= min) {
			copy(currentline, minline);
			while (minline[curleng] != '\0')
				++curleng;
			printf("\nline is:  %s\nlengh is: %d", minline, curleng);
		}
		else {
			printf("your line have to be longer then 80 characters\n");
		}
	}
}


int getline(char arr[], int lim) {
	int c, i;
	c = 0;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		arr[i] = c;
	}
	if (c == '\n') {
		arr[i] = c;
		++i;
	}
	arr[i] = '\0';
	return i;
}

void copy(char from[], char to[]) {
	int i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}