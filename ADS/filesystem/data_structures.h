#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum FileType
{
    REGULAR,
    DIRECTORY
} FileType;

// Multiple files can point to the same Inode
typedef struct Inode
{
    char *data;
    int dataSize;
    FileType type;
    int referenceCounter;
} Inode;

// Quicker to search for filenames in the trie
typedef struct Trie
{
    struct File *child;
    struct Trie *children[78];
} Trie;

typedef struct File
{
    char fileName[60];
    struct File *parent;
    Trie *children;
    Inode *iNode;
} File;

Trie *insertLetter(void);
void freeTrie(Trie *root);
void deleteFile(File *file);
void addChildToTrie(File *file, Trie *trie);
void freeChild(File *file, Trie *trie);
Inode *createInode(FileType type, File *file);
File *createFile(char *fileName, File *parent, FileType type);
File *FindPath(File *root, File *workingDir, char *nonExistingFile, char *path);
void printTrie(Trie *trie, char *fileName, int pos, int strSize, int deeper);
void copyDir(Trie *src, File *dst);

#endif
