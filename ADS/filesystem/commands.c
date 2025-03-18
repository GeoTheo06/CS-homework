#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"
#include "commands.h"

int peekchar(void)
{
    int c = getchar();
    if (c != EOF)
        ungetc(c, stdin);
    return c;
}

File *executeCd(File *root, File *workingDir)
{
    char ch = getchar();
    if (ch == '\n')
        return workingDir;
    char *path;
    scanf("%ms", &path);
    // Return value of nonExistingFile is not needed because cd is called on existing paths
    char nonExistingFile[256] = "+";
    return FindPath(root, workingDir, nonExistingFile, path);
}

void executeLs(File *root, File *workingDir)
{
    char ch = getchar();
    File *dir;
    if (ch == '\n')
    {
        dir = workingDir;
    }
    else
    {
        char *path;
        scanf("%ms", &path);
        char nonExistingFile[256] = "+";
        dir = FindPath(root, workingDir, nonExistingFile, path);
    }
    char fileNames[60] = {'\0'};
    // Parameter deeper determines whether the files are printed recursively
    printTrie(dir->children, fileNames, 0, 60, 0);
}

void executeCat(File *root, File *workingDir)
{
    char *path;
    scanf(" %ms", &path);
    char nonExistingFile[256] = "+";
    File *dir = FindPath(root, workingDir, nonExistingFile, path);
    if (dir->iNode->data != NULL)
    {
        printf("%s\n", dir->iNode->data);
    }
}

void executeFind(File *workingDir)
{
    char *fileNames = calloc(256, sizeof(char));
    fileNames[0] = '.';
    printf("%s\n", fileNames);
    fileNames[1] = '/';
    // Files are printed recursively
    printTrie(workingDir->children, fileNames, 2, 256, 1);
    free(fileNames);
}

void executeTouch(File *root, File *workingDir)
{
    char *path, *newFileName = calloc(60, sizeof(char));
    getchar();
    File *parent, *newFile;

    // Multiple creations allowed
    do
    {
        scanf("%ms", &path);
        parent = FindPath(root, workingDir, newFileName, path);
        newFile = createFile(newFileName, parent, REGULAR);
        addChildToTrie(newFile, parent->children);
    } while (getchar() != '\n');
    free(newFileName);
}

void executeMkdir(File *root, File *workingDir)
{
    scanf(" -p ");
    char *path;
    char *newFileName = calloc(60, sizeof(char));
    File *parent, *newFile;
    // Multiple creations allowed
    do
    {
        scanf("%ms", &path);
        parent = FindPath(root, workingDir, newFileName, path);
        // '+' indicates that the file already exists
        while (newFileName[0] != '+')
        {
            newFile = createFile(newFileName, parent, DIRECTORY);
            addChildToTrie(newFile, parent->children);
            parent = FindPath(root, workingDir, newFileName, path);
        }
    } while (getchar() != '\n');
    free(newFileName);
    free(path);
}

void executeEcho(File *root, File *workingDir)
{
    getchar();
    getchar();
    char *input = malloc(sizeof(char) * 100);
    char ch;
    int size = 100, length = 0;
    // Read new data
    while ((ch = getchar()) != '"')
    {
        if (length + 1 >= size)
        {
            size *= 2;
            input = realloc(input, sizeof(char) * size);
        }
        input[length] = ch;
        length++;
    }
    // Parsing the input
    getchar();
    getchar();
    ch = getchar();
    char *path;
    char *newFileName = malloc(sizeof(char) * 60);
    File *editedFile, *newFile;

    if (ch != '>')
    {
        scanf("%ms", &path);
        editedFile = FindPath(root, workingDir, newFileName, path);

        if (newFileName != NULL)
        {
            newFile = createFile(newFileName, editedFile, REGULAR);
            addChildToTrie(newFile, editedFile->children);
            editedFile = newFile;
        }
        editedFile->iNode->dataSize = size;
        editedFile->iNode->data = realloc(editedFile->iNode->data, sizeof(char) * editedFile->iNode->dataSize);
        strcpy(editedFile->iNode->data, input);
    }
    // ">>" case
    else
    {
        scanf(" %ms", &path);
        editedFile = FindPath(root, workingDir, newFileName, path);

        if (newFileName != NULL)
        {
            newFile = createFile(newFileName, editedFile, REGULAR);
            addChildToTrie(newFile, editedFile->children);
            editedFile = newFile;
        }
        editedFile->iNode->dataSize += size;
        editedFile->iNode->data = realloc(editedFile->iNode->data, sizeof(char) * editedFile->iNode->dataSize);
        strcat(editedFile->iNode->data, input);
    }
    free(input);
    free(newFileName);
}

void executeMv(File *root, File *workingDir)
{
    char *path1, *path2;
    char *newFileName = malloc(sizeof(char) * 60);
    File *newFile, *src, *dst;

    scanf(" %ms %ms", &path1, &path2);
    char nonExistingFile[256] = "+";
    src = FindPath(root, workingDir, nonExistingFile, path1);
    dst = FindPath(root, workingDir, newFileName, path2);

    // Remove reference from the parent folder
    Trie *parentReference = src->parent->children;
    int i = 0, c;
    while (src->fileName[i] != '\0')
    {
        c = src->fileName[i] - '-';
        parentReference = parentReference->children[c];
        i++;
    }
    parentReference->child = NULL;

    // Move the file depending on its type
    if (src->iNode->type == REGULAR)
    {
        if (newFileName != NULL)
        {
            addChildToTrie(src, dst->children);
        }
        else
        {
            dst->iNode->dataSize = src->iNode->dataSize;
            dst->iNode->data = realloc(dst->iNode->data, sizeof(char) * dst->iNode->dataSize);
            strcpy(dst->iNode->data, src->iNode->data);
            deleteFile(src);
        }
    }
    else
    {
        addChildToTrie(src, dst->children);
    }
    free(newFileName);
}

void executeCp(File *root, File *workingDir)
{
    getchar();
    if (peekchar() == '-')
    {
        getchar();
        getchar();
    }

    char *path1, *path2;
    char *newFileName = malloc(sizeof(char) * 60);
    scanf("%ms %ms", &path1, &path2);

    File *src, *dst, *parent;
    char nonExistingFile[256] = "+";
    src = FindPath(root, workingDir, nonExistingFile, path1);
    parent = FindPath(root, workingDir, newFileName, path2);

    if (src->iNode->type == REGULAR)
    {
        if (newFileName != NULL)
        {
            dst = createFile(newFileName, parent, REGULAR);
            addChildToTrie(dst, parent->children);
        }
        else
        {
            dst = parent;
        }
        dst->iNode->dataSize = src->iNode->dataSize;
        dst->iNode->data = realloc(dst->iNode->data, sizeof(char) * dst->iNode->dataSize);
        strcpy(dst->iNode->data, src->iNode->data);
    }
    else
    // DIRECTORY case
    {
        // Use recursive function copyDir
        dst = createFile(newFileName, parent, DIRECTORY);
        addChildToTrie(dst, parent->children);
        copyDir(src->children, dst);
    }
    free(newFileName);
}

void executeRm(File *root, File *workingDir)
{
    char nonExistingFile[256] = "+";
    // Consume optional -r
    getchar();
    if (peekchar() == '-')
    {
        getchar();
        getchar();
    }

    char *path;
    File *file;
    do
    {
        scanf("%ms", &path);
        file = FindPath(root, workingDir, nonExistingFile, path);
        deleteFile(file);
    } while (getchar() != '\n');
}

void executeLn(File *root, File *workingDir)
{
    char *path1, *path2, newFileName[60];
    scanf(" %ms %ms", &path1, &path2);

    File *src, *dst, *parent;
    char nonExistingFile[256] = "+";
    src = FindPath(root, workingDir, nonExistingFile, path1);
    parent = FindPath(root, workingDir, newFileName, path2);
    dst = createFile(newFileName, parent, REGULAR);
    addChildToTrie(dst, parent->children);

    free(dst->iNode->data);
    free(dst->iNode);

    dst->iNode = src->iNode;
    dst->iNode->referenceCounter++;
}