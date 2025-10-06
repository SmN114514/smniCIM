/*
    这是编辑器的核心头文件

*/

#ifndef EDITOR_H
#define EDITOR_H

// 编辑器配置
#define MLINES 1024  // 最大行数
#define MCOLS 1024      // 每行最大字符数


#include "setColor.h"  // 包含颜色定义
// 全局变量声明
extern char text[MLINES][MCOLS];  // 文本缓冲区
extern int curX, curY;
extern int currentMode;
// 核心函数声明
void init_text();
void insert_char(char c);
void delete_char();
void new_line();
void move_cursor(int y,int x);


void display_status_bar();      // 显示状态栏（行列信息）
void display_status_message();  // 显示状态消息（错误/成功等）
void display_main_content();    // 显示主要内容（欢迎界面或文本内容）
#endif