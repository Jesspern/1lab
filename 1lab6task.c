#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 255
#define MALLOC_EXC 1

typedef struct string {
	char* str;
	int c_sz;
	int r_sz;
} string;

void cr_str(string* str) {
	str->c_sz = SIZE;
	str->r_sz = 0;
	str->str = (char*)malloc(sizeof(char) * SIZE);
}

int check_size(string* str) {
	if (str->r_sz == str->c_sz - 1) {
		char* p_str = (char*)realloc(str->str, sizeof(char) * 2 * str->c_sz);
		if (p_str == NULL) {
			return MALLOC_EXC;
		}
		str->str = p_str;
		str->c_sz = 2 * str->c_sz;
	}
	return 0;
}

int is_alpha(char symbol) {
	symbol = tolower(symbol);
	return (symbol < 'a' || symbol > 'z') ? 0 : 1; 
}

int is_digit(char symbol) {
	return (symbol < '0' || symbol > '9') ? 0 : 1;
}

int is_separator(char symbol) {
	if (symbol == ' ' || symbol == '\n' || symbol == '\v' || symbol == '\r') {
		return 1;
	} else {
		return 0;
	}
}

int main(void) {
	FILE* fp;
	FILE* fo;
	fp = fopen("file.txt", "r");
	fo = fopen("fileout.txt", "w");
	if (fp == NULL) {
		printf("Problem with File");
		return 0;
	}
	if (fo == NULL) {
		printf("Problem with File");
		return 0;
	}

	char c;
	char _c;
	char max;
	string buf;
	cr_str(&buf);

	while (!feof(fp)) {
		_c = c;
		c = fgetc(fp);
		if (c == EOF) {
			if ((is_alpha(_c) || is_digit(_c))) {
				max = '1';
				for (int i = 0; i < buf.r_sz; i++) {
					if (tolower(buf.str[i]) > max) {
						max = tolower(buf.str[i]);
					}
				}
				if (is_digit(max)) {
					fprintf(fo, "Digit: %s   Number system: %d\n", buf.str, max - '0' + 1);
					free(buf.str);
					cr_str(&buf);
				} else if (is_alpha(max)) {
					fprintf(fo, "Digit: %s   Number system: %d\n", buf.str, max - 'a' + 10);
					free(buf.str);
					cr_str(&buf);
				} else {
					printf("MISAKE");
					return 0;
				}
			}
			return 0;
		}
		if (is_alpha(c) || is_digit(c)) {
			check_size(&buf);
			buf.str[buf.r_sz++] = c;
		} else if (is_separator(c) && (is_alpha(_c) || is_digit(_c))) {
			max = '1';
			for (int i = 0; i < buf.r_sz; i++) {
				if (tolower(buf.str[i]) > max) {
					max = tolower(buf.str[i]);
				}
			}
			if (is_digit(max)) {
				fprintf(fo, "Digit: %s   Number system: %d\n", buf.str, max - '0' + 1);
				free(buf.str);
				cr_str(&buf);
			} else if (is_alpha(max)) {
				fprintf(fo, "Digit: %s   Number system: %d\n", buf.str, max - 'a' + 10);
				free(buf.str);
				cr_str(&buf);
			} else {
				printf("MISTAKE");
				return 0;
			}
		}
	}

	return 0;
}