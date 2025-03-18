#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"

File *executeCd(File *root, File *workingDir);
void executeLs(File *root, File *workingDir);
void executeCat(File *root, File *workingDir);
void executeFind(File *workingDir);
void executeTouch(File *root, File *workingDir);
void executeMkdir(File *root, File *workingDir);
void executeEcho(File *root, File *workingDir);
void executeMv(File *root, File *workingDir);
void executeCp(File *root, File *workingDir);
void executeRm(File *root, File *workingDir);
void executeLn(File *root, File *workingDir);

#endif