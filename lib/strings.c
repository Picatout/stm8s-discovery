/* 
 *  strings functions
*/ 

#include "../inc/discovery.h"

void upper(char *buff){
	while (*buff){
	   if ((*buff>='a') && (*buff<='z')) *buff-=32;
	   buff++;
	}
}

int8_t strcmp(const char *s1, const char *s2){
	while (*s1 && *s2){
		if (*s1<*s2) return -1;
		if (*s1>*s2) return 1;
		s1++;
		s2++;
	}
	if (*s2) return -1;
	if (*s1) return 1;
	return 0;
}

char *strcpy(char *dest, const char *src){
	char *d=dest;
	while (*src){
		*d++=*src++;
	};
	*d=0;
	return dest;
}

int strlen(const char* str){
	int len=0;
	while (*str++)len++;
	return len;
}

void memset(char *str,char c, int16_t count){
	while (count){
		*str++=c;
		count--;
	}
}
