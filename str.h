#ifndef CUTILS_STRING
#define CUTILS_STRING

char *str_uppercase(const char *str);
char *str_lowercase(const char *str);
char *str_invertcase(const char *str);
char *str_sub(const char *str, const char *substr, const char *new);
char *str_gsub(const char *str, const char *substr, const char *new);
char *str_format(const char *fmt, ...);
char *str_concat(const char *str1, const char *str2);
int  str_count(const char *str, const char *substr);
char **str_split(char *str, const char *separator);
int  str_include(const char *str1, const char *str2);
int  str_equal(const char *str1, const char *str2);

#endif
