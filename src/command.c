/*
    我豆 大工程，太搞了
*/


#include "../include/command.h"
#include "../include/editor.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <ctype.h>

static char command_buf[MAX_LEN]; 
static int cmd_posit;


void open_CMD(){
    memset(command_buf, 0, sizeof(command_buf));
    cmd_posit = 0;
    currentMode = 2;

    // 清空命令输入行
    move(LINES-2, 0);
    clrtoeol();
    mvprintw(LINES-2, 0, "COMMAND>");
    refresh();

    int ch;
    while ((ch = getch()) != '\n' && ch != 27) {
        if (ch == 127 || ch == KEY_BACKSPACE) {
            // 退格键处理
            if (cmd_posit > 0) {
                cmd_posit--;
                command_buf[cmd_posit] = '\0';
                
                // 重新显示整个命令提示符和当前内容
                move(LINES-2, 0);
                clrtoeol();
                mvprintw(LINES-2, 0, "COMMAND>%s", command_buf);
            }
        } 
        else if (cmd_posit < MAX_LEN-1 && isprint(ch)) {
            // 普通字符输入
            command_buf[cmd_posit] = ch;
            command_buf[cmd_posit + 1] = '\0';
            cmd_posit++;
            
            // 显示当前字符
            mvprintw(LINES-2, 8 + cmd_posit - 1, "%c", ch);
        }
        refresh();
    }
    
    if (ch == '\n') {
        execute_CMD(command_buf);
    }
    
    currentMode = 0;
    // 清空命令区域
    move(LINES-2, 0);
    clrtoeol();
    move(LINES-1, 0);
    clrtoeol();
}

void execute_CMD(const char* cmd){
    //执行命令

    //检查是否为无效的空命令
    if(!cmd || strlen(cmd) == 0) return;
    //退出，写，读,保存并退出巴拉巴拉巴拉.....
    if(strcmp(cmd,"q") == 0 || strcmp(cmd,"quit") == 0) _quit();
    else if(strncmp(cmd, "w ", 2) == 0) _save(cmd+2);
    
    else if(strncmp(cmd,"wq ",3) == 0){
        _save(cmd+3);
        _quit();
    }
    else if (strcmp(cmd, "wq") == 0) {  // 新增无参数版本
        _save("default.txt");
        _quit();
    }

    else if(strcmp(cmd,"h")==0 || strcmp(cmd,"help")==0)
        _help();

    else
        unknown();
    


}

void unknown(){
    show_message("Unknown command !", COLOR_ERROR);
    napms(1300);
    refresh();
}

//保存方法的实现，实在有点懒蛋了我了，让AI帮了一下
void _save(const char* filename) {
    // 1. 确定文件名，检查权限
    const char* target = filename ? filename : "default.txt";
    
    if(access(target, W_OK) == -1 && access(target, W_OK) == 0) {
        attron(COLOR_PAIR(COLOR_ERROR));
        mvprintw(LINES-3, 0, "Error: You can not edit this file");
        attroff(COLOR_PAIR(COLOR_ERROR));
        return;
    }
    // 2. 打开文件
    FILE* fp = fopen(target, "w");
    if (!fp) {
        attron(COLOR_PAIR(COLOR_ERROR));
        mvprintw(LINES - 3, 0, "Error: Failed to save this file");
        attroff(COLOR_PAIR(COLOR_ERROR));
        return;
    }

    // 3. 逐行写入
    for (int i = 0; i < MLINES && text[i][0] != '\0'; i++) {
        fprintf(fp, "%s\n", text[i]);
    }
    // 4. 关闭文件
    fclose(fp);

    // 5. 显示状态 这个特么不太好改
    show_message("File saved successfully", COLOR_SUCCESS);

    refresh();
}

//加载方法的视线，我有点不会写,AI助我
void _load(const char* filename){
    if (!filename || strlen(filename) == 0) {
       show_message("Error: No filename specified", COLOR_ERROR);
        return;
    }

    //检查文件是否存在
    if(access(filename, R_OK) == -1) {
        // attron(COLOR_PAIR(COLOR_ERROR));
        // mvprintw(LINES-3, 0, "Error: File '%s' not found or no read permission", filename);
        // attroff(COLOR_PAIR(COLOR_ERROR));
         show_message("Error: The file can not found or no read permission", COLOR_ERROR);
        return;
    }

    // 打开
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        show_message("Error: Can not open this file", COLOR_ERROR);
        return;
    }

    //清空当前内容
    init_text();

    //读取
    char line[MCOLS];
    int i = 0;
    while (fgets(line, sizeof(line), fp) && i < MLINES) {
        line[strcspn(line, "\n")] = '\0'; // 去除换行符
        strncpy(text[i], line, MCOLS - 1);
        text[i][MCOLS - 1] = '\0';
        i++;
    }

    // 5. 关闭文件
    fclose(fp);

    // 6. 显示状态
    show_message("File loaded successfully", COLOR_STATUS);
    
    refresh();

}
void _help(){
    _load("help.txt");
    
}
void _quit(){
    endwin();    // 关闭ncurses
    exit(0);     // 退出程序
}

