#ifndef COMMAND_H
#define COMMAND_H

#include <stdbool.h>
#include "setColor.h"  // 包含颜色定义
#define MAX_LEN 256

//打开命令模式与执行
void open_CMD();
void execute_CMD(const char* cmd);
void _quit();

void unknown();

//file edit
void _save(const char* filename);
void _load(const char* filename);

//help
void _help();

void _status();

#endif

