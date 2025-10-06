#include "../include/setColor.h"
#include <ncurses.h>
#include <string.h>
#include <unistd.h>

void init_colors() {
    start_color();
    init_pair(COLOR_ERROR,   COLOR_WHITE, COLOR_RED);
    init_pair(COLOR_SUCCESS, COLOR_WHITE, COLOR_GREEN);
    init_pair(COLOR_WARNING, COLOR_BLACK, COLOR_YELLOW);
    init_pair(COLOR_HELP,    COLOR_WHITE, COLOR_BLUE);
    init_pair(COLOR_NORMAL, COLOR_BLACK, COLOR_WHITE);
    init_pair(COLOR_STATUS, COLOR_BLACK, COLOR_CYAN);
}
void show_message(const char* msg, int color_type){
    // 清空消息行（固定使用 LINES-2）
    move(LINES - 2, 0);
    clrtoeol();
    
    // 显示消息
    attron(COLOR_PAIR(color_type));
    mvprintw(LINES - 2, 0, "%-*s", COLS, msg); // 占满整行
    attroff(COLOR_PAIR(color_type));
    refresh();
}


void show_status_bar(int mode, int line, int col) {
    // 清空状态栏区域（固定使用 LINES-1）
    move(LINES - 1, 0);
    clrtoeol();
    
    // 显示模式信息
    const char* mode_str;
    switch(mode) {
        case 0: mode_str = "NORMAL"; break;
        case 1: mode_str = "INSERT"; break;
        case 2: mode_str = "COMMAND"; break;
        default: mode_str = "UNKNOWN";
    }
    
    // 左侧显示模式
    attron(COLOR_PAIR(COLOR_STATUS));
    mvprintw(LINES - 1, 0, "Mode:%s", mode_str);
    
    // 右侧显示行列信息和退出提示
    mvprintw(LINES - 1, COLS - 30, "Line:%d Col:%d | Press ESC to quit", line, col);
    attroff(COLOR_PAIR(COLOR_STATUS));
    refresh();
}