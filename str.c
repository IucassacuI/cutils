#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "memory.h"

char *str_uppercase(const char *str){
	char *new = mem_alloc(strlen(str)+1);
	mem_copy(new, str);

	for(size_t i = 0; i < strlen(new); i++)
		mem_at(new, 1, i) = toupper(mem_at(new, 1, i));

	return new;
}

char *str_lowercase(const char *str){
	char *new = mem_alloc(strlen(str)+1);
	mem_copy(new, str);

	for(size_t i = 0; i < strlen(new); i++)
		mem_at(new, 1, i) = tolower(mem_at(new, 1, i));

	return new;
}

char *str_invertcase(const char *str){
	char *new = mem_alloc(strlen(str)+1);
	mem_copy(new, str);

	for(size_t i = 0; i < strlen(new); i++)
		mem_at(new, 1, i) = isalpha(mem_at(str, 1, i)) ? mem_at(str, 1, i) ^ 32 : mem_at(str, 1, i);

	return new;
}

char *str_sub(const char *str, const char *substr, const char *new){
	int bufsize = strlen(str)+strlen(new)+1;
	char *final = mem_alloc(bufsize);

	int pos = strstr(str, substr)-str;

	for(int i = 0; i < pos; i++)
		mem_at(final, 1, i) = mem_at(str, 1, i);

	final = strncat(final, new, bufsize);

	const char *end = str+pos+strlen(substr);
	final = strncat(final, end, bufsize);

	return final;
}

char *str_gsub(const char *str, const char *substr, const char *new){
	char *state = str_sub(str, substr, new);

	if(strstr(state, substr) != NULL)
		state = str_gsub(state, substr, new);

	return state;
}

char *str_format(const char *fmt, ...){
	va_list args;
	va_start(args, fmt);

	int bufsize = vsnprintf(NULL, 0, fmt, args) + 1;

	char *buf = mem_alloc(bufsize + 1);

	va_end(args);

	va_start(args, fmt);

	vsnprintf(buf, bufsize, fmt, args);

	va_end(args);

	return buf;
}

char *str_concat(const char *str1, const char *str2){
	int bufsize = strlen(str1) + strlen(str2) + 1;
	char *buf = mem_alloc(bufsize);

	mem_copy(buf, str1);

	strncat(buf, str2, bufsize);

	return buf;
}

int str_count(const char *str, const char *substr){
	char *strcopy = mem_alloc(strlen(str)+1);
	mem_copy(strcopy, str);

	int count = 0;

	while(strstr(strcopy, substr)){
		count++;
		strcopy = strstr(strcopy, substr) + strlen(substr);
	}

	return count;
}

char **str_split(const char *str, const char *separator){
	char *copy = mem_alloc(strlen(str)+1);
	mem_copy(copy, str);

	int count = str_count(copy, separator);
	char **strings = (char **) mem_alloc((count + 1) * sizeof(char *));

	char *token = strtok(copy, separator);

	for(int i = 0; token != NULL; i++){
		mem_at(strings, sizeof(char *), i) = token;
		token = strtok(NULL, separator);
	}

	return strings;
}

int str_include(const char *str1, const char *str2){
	return strstr(str1, str2) != NULL;
}

int str_equal(const char *str1, const char *str2){
	return strcmp(str1, str2) == 0;
}
