#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY  10
#define TIMES 1.5


typedef struct string_builder{
    char *string;
    unsigned int size;
    unsigned int cap;
} StringBuilder;


void failMemoryAllocateError(void *v);

StringBuilder *newStringBuilder() {
    StringBuilder *sb = (StringBuilder *)malloc(sizeof(StringBuilder));
    sb->string = (char *)calloc(sizeof(char), DEFAULT_CAPACITY);
    sb->cap = DEFAULT_CAPACITY;
    sb->size = 0;
    return sb;
}

void appendSB(StringBuilder *sb, char *string) {
    sb->size += strlen(string);
    unsigned int old_cap = sb->cap;
    while (sb->cap < sb->size) {
        sb->cap *= TIMES;
    }
    if (sb->cap != old_cap) {
        sb->string = (char *)realloc(sb->string, sizeof(char) * sb->cap + 1);
        failMemoryAllocateError(sb->string);
    }
    strcat(sb->string, string);
}

char *toString(StringBuilder *sb) {
    char *string = (char *)calloc(sizeof(char), sb->size);
    failMemoryAllocateError(string);
    strcpy(string, sb->string);
    free(sb->string);
    free(sb);
    return string;
}

void failMemoryAllocateError(void* v) {
    if (v == NULL) {
        printf("error: couldn't allocate memory.");
        exit(1);
    }
}
