#ifndef READFILE_H
#define READFILE_H

#include <stdio.h>
#include <stdlib.h>

// read file and store it into buffer

char* eng_readFile(const char* path)
{
    FILE* file = fopen(path, "r");
    if (!file)
    {
        printf("Error on read file\n");
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    if (size <= 0)
    {
        fclose(file);
        return NULL;
    }

    char* buffer = (char*)malloc(size + 1);
    if (!buffer)
    {
        fclose(file);
        printf("Error on alloc buffer\n");
        return NULL;
    }

    size_t bytesRead = fread(buffer, 1, size, file);
    buffer[bytesRead] = '\0';

    fclose(file);
    return buffer;
}
#endif // READFILE_H