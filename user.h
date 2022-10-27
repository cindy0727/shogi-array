#ifndef USER_H
#define USER_H

#define ROW 9
#define COL 9

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<time.h>

typedef struct user_t
{
    unsigned front, rear;
    char userchess_board[ROW][COL];
    char tmp;
    int tmprow, tmpcol;

    //原本和改動的棋子位置
    int orignrow, origncol, afterrow, aftercol;

} user;

void creat_user1(user *user1);//建立user1
void creat_user2(user *user2);//建立user2

void chineseuser1 (char letter);//轉換成中文字並印出藍色字
void chineseuser2 (char letter);//轉換成中文字並印出紅色字

#endif

