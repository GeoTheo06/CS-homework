#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"

// Creates a new Trie node with all children initialized to NULL
Trie *insertLetter()
{
    Trie *letter = malloc(sizeof(Trie));
    for (int i = 0; i < 78; i++)
    {
        letter->children[i] = NULL;
    }
    letter->child = NULL;
    return letter;
}

// Pre-declaration
void freeTrie(Trie *root);

// Deletes a file and frees its resources. If the file is a directory, it frees the corresponding Trie
void deleteFile(File *file)
{
    Inode *node = file->iNode;
    node->referenceCounter--;

    if (node->type == DIRECTORY)
    {
        freeTrie(file->children);
    }

    free(file);

    // Delete the inode if no more references exist
    if (node->referenceCounter == 0)
    {
        free(node->data);
        free(node);
    }
}

// Recursively frees a Trie and its associated file
void freeTrie(Trie *root)
{
    if (root == NULL)
        return;

    for (int i = 0; i < 78; i++)
    {
        freeTrie(root->children[i]);
    }

    if (root->child != NULL)
    {
        deleteFile(root->child);
    }

    free(root);
}

// Adds a file to the Trie by traversing characters in its fileName
void addChildToTrie(File *file, Trie *trie)
{
    char *fileName = file->fileName;
    int i = 0, c;
    while (fileName[i] != '\0')
    {
        c = fileName[i] - '-';
        if (trie->children[c] == NULL)
        {
            trie->children[c] = insertLetter();
        }
        trie = trie->children[c];
        i++;
    }
    trie->child = file;
}

// Frees a file's pointer from the Trie without deleting the file itself
void freeChild(File *file, Trie *trie)
{
    int i = 0, c;
    while (file->fileName[i] != '\0')
    {
        c = file->fileName[i] - '-';
        trie = trie->children[c];
        i++;
    }
    free(trie->child);
}

// Creates a new inode with a specified file type
Inode *createInode(FileType type, File *file)
{
    Inode *node = malloc(sizeof(Inode));
    node->type = type;
    node->data = malloc(1);
    node->dataSize = 1;
    node->referenceCounter = 1;
    return node;
}

// Creates a new file with the specified name, parent, and type
// For directories, a Trie is allocated
File *createFile(char *fileName, File *parent, FileType type)
{
    File *file = malloc(sizeof(File));
    strcpy(file->fileName, fileName);
    file->parent = parent;

    if (type == DIRECTORY)
    {
        file->children = insertLetter();
    }
    else
    {
        file->children = NULL;
    }

    file->iNode = createInode(type, file);
    return file;
}

// Finds a file path given a starting root, working directory, and a path string
// nonExistingFile is updated with the first non-existing file encountered
File *FindPath(File *root, File *workingDir, char *nonExistingFile, char *path)
{
    char *temp = malloc(strlen(path) + 1);
    strcpy(temp, path);

    File *result = (path[0] == '/') ? root : workingDir;
    char *prevToken = calloc(60, sizeof(char));
    // Tokenize the string between '/' characters
    char *token = strtok(temp, "/");

    while (token != NULL)
    {
        if (!strcmp(token, ".."))
        {
            result = result->parent;
        }
        else if (strcmp(token, "."))
        {
            int i = 0, c;
            Trie *childrenNames = result->children;
            // Iterate through the Trie to find the pointer to the file
            while (token[i] != '\0')
            {
                c = token[i] - '-';
                if (childrenNames->children[c] == NULL)
                {
                    if (nonExistingFile[0] != '+')
                    {
                        strcpy(nonExistingFile, token);
                    }
                    free(temp);
                    free(prevToken);
                    return result;
                }
                childrenNames = childrenNames->children[c];
                i++;
            }
            result = childrenNames->child;
        }
        strcpy(prevToken, token);
        token = strtok(NULL, "/");
    }

    // fileName can be a substring of the name of an already existing file
    if (result == NULL)
    {
        strcpy(nonExistingFile, prevToken);
    }
    else
    {
        nonExistingFile[0] = '+';
    }
    free(temp);
    free(prevToken);
    return result;
}

// Recursively prints the Trie structure as file names
void printTrie(Trie *trie, char *fileName, int pos, int strSize, int deeper)
{
    // Base case
    if (trie->child != NULL)
    {
        if (deeper && trie->child->iNode->type == DIRECTORY)
        {
            fileName[pos] = '\0';
            printf("%s\n", fileName);
            fileName[pos] = '/';

            if (pos + 1 == strSize)
            {
                strSize *= 3;
                fileName = realloc(fileName, strSize * sizeof(char));
            }
            printTrie(trie->child->children, fileName, pos + 1, strSize, deeper);
        }
        else
        {
            fileName[pos] = '\0';
            printf("%s\n", fileName);
        }
    }

    // Recursively traverse children
    for (int i = 0; i < 78; i++)
    {
        if (trie->children[i] != NULL)
        {
            char temp = fileName[pos];
            fileName[pos] = i + '-';

            if (pos + 1 == strSize)
            {
                strSize *= 3;
                fileName = realloc(fileName, strSize * sizeof(char));
            }
            printTrie(trie->children[i], fileName, pos + 1, strSize, deeper);
            fileName[pos] = temp;
        }
    }
    return;
}


// Recursively copies a directory structure
void copyDir(Trie *src, File *dst)
{
    if (src->child != NULL)
    {
        // Recursively copy the contents of directory
        if (src->child->iNode->type == DIRECTORY)
        {
            File *newFile = createFile(src->child->fileName, dst, DIRECTORY);
            addChildToTrie(newFile, dst->children);
            copyDir(src->child->children, newFile);
        }
        else
        // REGULAR case
        {
            // copy the contents
            File *newFile = createFile(src->child->fileName, dst, REGULAR);
            addChildToTrie(newFile, dst->children);
            newFile->iNode->dataSize = src->child->iNode->dataSize;
            newFile->iNode->data = realloc(newFile->iNode->data, sizeof(char) * newFile->iNode->dataSize);
            strcpy(newFile->iNode->data, src->child->iNode->data);
        }
        return;
    }

    for (int i = 0; i < 78; i++)
    {
        if (src->children[i] != NULL)
        {
            copyDir(src->children[i], dst);
        }
    }
}
