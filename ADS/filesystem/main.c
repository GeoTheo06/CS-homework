#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"
#include "commands.h"
// Reads a command and returns the corresponding command number.
int getCommandNumber()
{
    char *commands[] = {"exit", "cd", "ls", "cat", "find", "touch", "echo", "mkdir", "mv", "cp", "rm", "ln"};
    int numCommands = 12;
    char input[10] = {0};
    scanf("%9s", input);

    for (int i = 0; i < numCommands; i++)
    {
        if (strncmp(input, commands[i], strlen(commands[i])) == 0)
        {
            return i + 1; // Command numbers start at 1.
        }
    }
    return -1;
}

int main()
{
    File *root = createFile("/", NULL, DIRECTORY);
    File *workingDir = root;
    int command = getCommandNumber();

    while (command != 1)
    {
        switch (command)
        {
        case 2:
            workingDir = executeCd(root, workingDir);
            break;
        case 3:
            executeLs(root, workingDir);
            break;
        case 4:
            executeCat(root, workingDir);
            break;
        case 5:
            executeFind(workingDir);
            break;
        case 6:
            executeTouch(root, workingDir);
            break;
        case 7:
            executeEcho(root, workingDir);
            break;
        case 8:
            executeMkdir(root, workingDir);
            break;
        case 9:
            executeMv(root, workingDir);
            break;
        case 10:
            executeCp(root, workingDir);
            break;
        case 11:
            executeRm(root, workingDir);
            break;
        case 12:
            executeLn(root, workingDir);
            break;
        }
        command = getCommandNumber();
    }

    // Exit command called.
    deleteFile(root);
    return 0;
}
