#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_builder.h"

typedef struct block {
    char *string;
    struct block *prev;
    struct block *next;
} Block;

typedef struct string_builder{
    Block *first;
    Block *last;
    int size;
} StringBuilder;

Block *newBlock(char *string, int len, Block *prev, Block *next);
void failMemoryAllocateError(void *v);

Block *newBlock(char *string, int len, Block *prev, Block *next) {
    Block *block = (Block *)malloc(sizeof(Block));
    failMemoryAllocateError(block);
    block->string = (char *)calloc(len, sizeof(char));
    failMemoryAllocateError(block->string);
    strcpy(block->string, string);
    block->prev = prev;
    block->next = next;
    return block;
}

StringBuilder *newStringBuilder() {
    StringBuilder *sb = (StringBuilder *)malloc(sizeof(StringBuilder));
    sb->first = NULL;
    sb->last = NULL;
    sb->size = 0;
    return sb;
}

void appendSB(StringBuilder *sb, char *string) {
    int block_size = strlen(string);
    sb->size += block_size;
    Block *last = sb->last;
    Block *block = newBlock(string, block_size, last, NULL);
    sb->last = block;
    if (last == NULL) {
        sb->first = block;
    } else {
        last->next = block;
    }
}

char *toString(StringBuilder *sb) {
    char *string = (char *)calloc(sb->size + 1, sizeof(char));
    Block *block = sb->first;
    while (block != NULL) {
        strcat(string, block->string);
        free(block->string);
        Block* curr = block;
        block = block->next;
        free(curr);
    }
    free(sb);
    return string;
}

void failMemoryAllocateError(void* v) {
    if (v == NULL) {
        printf("error: couldn't allocate memory.");
        exit(1);
    }
}

