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
        perror("Error on read file");
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    if (size <= 0)
    {
        perror("file size is zero");
        fclose(file);
        return NULL;
    }

    char* buffer = (char*)malloc(size + 1);
    if (!buffer)
    {
        fclose(file);
        perror("Error on alloc buffer");
        return NULL;
    }

    size_t bytesRead = fread(buffer, 1, size, file);
    buffer[bytesRead] = '\0';

    fclose(file);
    return buffer;
}
#endif // READFILE_H