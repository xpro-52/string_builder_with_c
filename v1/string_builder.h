#ifndef STRING_BUILDER_H
#define STRING_BUILDER_H

typedef struct string_builder StringBuilder;

StringBuilder *newStringBuilder();
void appendSB(StringBuilder *sb, char *string);
char *toString(StringBuilder *sb);
#endif