#ifndef SETCOLOR_H
#define SETCOLOR_H

#include <ncurses.h>

// 颜色常量定义
#define COLOR_ERROR 1    // 错误消息（红底白字）
#define COLOR_SUCCESS 2  // 成功消息（绿底黑字）
#define COLOR_WARNING 3  // 警告消息（黄底黑字）
#define COLOR_HELP 4     // 帮助文本（蓝底白字）
#define COLOR_NORMAL 5   // 默认颜色（白底黑字）
#define COLOR_STATUS 6   // 状态栏（青底黑字）

// 颜色初始化函数
void init_colors();

void show_message(const char* msg, int color_type);

void show_status_bar(int mode, int line, int col);
#endif