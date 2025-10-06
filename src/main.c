
#include "../include/editor.h"
#include "../include/command.h"

#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

#include <ctype.h>
#include "../include/setColor.h"

#define Gunmu " "
/*
currentMode == 1 插入模式
currentMode == 2 命令模式
currentMode == 0 等待输入a或者按下“:”的空白模式
*/
int show_welcome = 1;
int currentMode;
char status_msg[256] = "";
int status_color = COLOR_NORMAL;
char text[MLINES][MCOLS];  // 文本缓冲区
int curX = 0, curY = 0;

void center_print(int line, const char* msg) {
    int length = strlen(msg);
    int x = (COLS - length) / 2;
    if (x < 0) x = 0;
    mvprintw(line, x, "%s", msg);
}//我来组成居中打印！


void welcome(){
	//此处编写欢迎信息
	center_print(1,"SmniCIM Alpha 0.0.1 - By Smnic");
	center_print(2,"arrowKey to move cur; Type to edit; Press ESC to quit.");
	center_print(3,"Help the overworked GRADE 12 students of Changchun Experimental High School!");

}

void init_text(){
	/*
	 * 初始化一下编辑区 每行都为空
	 * */
	//text[i][0] = '\0';
	for(int i = 0; i < MLINES; i++){

		text[i][MCOLS - 1] = '\0'; //糊
	
	}

}



void display_text(){
	clear();
    
	
	if (show_welcome) {
        welcome();
    } else {
        // 显示编辑内容
        for(int i = 0; i < LINES - 1; i++) {
            if(i < MLINES && text[i][0] != '\0') {
                mvprintw(i, 0, "%s", text[i]);
            }
        }
    }
    show_status_bar(currentMode, curY+1, curX+1);
    move(curY, curX);
    refresh();


}

void move_cursor(int y, int x) {
    	//Y
	if(y < 0) curY = 0;
	else if (y >=MLINES) curY = MLINES - 1;
	else curY = y;
	//X
	if(x < 0) curX = 0;
	else if(x >=MCOLS) curX = MCOLS - 1;
	else curX = x;

	//more check
	if(curX > strlen(text[curY])) curX = strlen(text[curY]);

	//移动光标就关闭欢迎提示
	if (show_welcome && (curY != 0 || curX != 0)) {
        show_welcome = 0;
    }
}


void insert_char(char chars){
	int length = strlen(text[curY]);	
	if(length < MCOLS - 1){
		memmove(&text[curY][curX + 1],&text[curY][curX],length - curX + 1);
		text[curY][curX] = chars;
		curX ++;
		show_welcome = 0;
	}


}


void del_char(){
	int length = strlen(text[curY]);

	if(length > 0){
		memmove(&text[curY][curX - 1],&text[curY][curX],length - curX + 1);
		curX --;
		show_welcome = 0;
	}
	

}


//逆天
//

int main(){
	initscr();
	cbreak();
	noecho();
	keypad(stdscr,TRUE);

	init_colors();

	init_text();
	display_text();

	int chars;
	// main loop
	while(1){
		chars = getch();
		//处理ESC
		if(chars == 27){
			if(currentMode == 1 || currentMode == 2){ 
				currentMode = 0;
				mvprintw(LINES-1,0,Gunmu);//清空状态栏
			}
			else{
			break;
			}
		}	
		
		//处理模式切换
		if(currentMode == 0){
			if(chars == 'a'){
				currentMode = 1;
				mvprintw(LINES-1,0,"INSERT MODE");
			}
			else if (chars == ':'){
                open_CMD();
			
			}      // 直接调用命令模式函数

		}

		switch(chars){
			case KEY_UP: move_cursor(curY-1,curX);break;
			case KEY_DOWN: move_cursor(curY+1,curX); break;
			case KEY_LEFT: move_cursor(curY,curX-1); break;
			case KEY_RIGHT: move_cursor(curY,curX+1); break;
			case 8:   // Backspace
            case 127: // Delete (某些系统) 
            case KEY_BACKSPACE:  del_char();break; // backSpace（?
			case 10:
				if(curY < MLINES - 1) {
						int length = strlen(text[curY]);
						// 下移所有行
						for(int i = MLINES - 1; i > curY + 1; i--) {
							strcpy(text[i], text[i - 1]);
						}
						// 分割行
						strcpy(text[curY + 1], &text[curY][curX]);
						text[curY][curX] = '\0';
						move_cursor(curY + 1, 0);
					}
			
				break; //enter!
			//case 
			default: if(isprint(chars)) insert_char(chars);
		}

		display_text(); 



	}
	endwin();
	return 0;
}



