#include "user.h"
#include "function.h"

int breaking = 0;
int savedone = 0;

void game(int * rear1, int * rear2, int *front1, int *front2, int *count)
{
    //初始化雙方
    creat_user1(usermeptr);//usermee[0] = 原始棋盤
    creat_user2(useryouptr);//useryouu[0] = 原始棋盤
    printchess(usermeptr, useryouptr, &chess_board);

    //開始下棋
    //user1輸入
    *rear1 += 1;
    userme[*rear1] = userme[*rear1-1];
    usermeptr = &userme[*rear1];
    printf("依據圖上座標 User1 輸入想移動的棋子的原始座標空格移動後的位置座標:");
    scanf("%1s%d%d%d", &userme[*rear1].orignrow, &userme[*rear1].origncol, &userme[*rear1].afterrow, &userme[*rear1].aftercol);
    if(userme[*rear1].orignrow == 115)
    {
        *front1 +=1;//因為第一筆資料在rear = 1的時候 所以事先動再移 
        fprintf(fptr, "%c %d %d %d\n", userme[*front1].orignrow, userme[*front1].origncol, userme[*front1].afterrow, userme[*front1].aftercol);
        *front1 -=1;//front指著有效的資料
        printf("依據圖上座標 User1 輸入想移動的棋子的原始座標空格移動後的位置座標:");
        scanf("%1s%d%d%d", &userme[*rear1].orignrow, &userme[*rear1].origncol, &userme[*rear1].afterrow, &userme[*rear1].aftercol);
    }
    user1move(usermeptr, useryouptr);
    printchess(usermeptr, useryouptr, &chess_board);
    //第二手開始進入迴圈
    while(1)
    {
        *rear2 += 1;
        useryou[*rear2] = useryou[*rear2-1];
        useryouptr = &useryou[*rear2];
        printf("依據圖上座標 User2 輸入想移動的棋子的原始座標空格移動後的位置座標:");
        scanf("%1s%d%d%d", &useryou[*rear2].orignrow, &useryou[*rear2].origncol, &useryou[*rear2].afterrow, &useryou[*rear2].aftercol);
        while(1)
        {
            if(useryou[*rear2].orignrow == 48)
            {
                //user2輸入為0代表user1悔棋
                *rear1 = *rear1 - 1;
                if(*rear1 == (-1))
                {

                    printf("\n輸入不正確，請重新輸入\n");
                    *rear1 +=1;
                    break;
                }
                usermeptr = &userme[*rear1];
                *rear2 = *rear2 - 1;
                if(*rear2 == (-1))
                {
                    *rear2 +=1;
                    printf("\n輸入不正確，請重新輸入\n");
                    break;
                }
                if((useryou[*rear2].tmprow != (-1)) && (useryou[*rear2].tmpcol != (-1)))//user1有吃掉user2的棋子
                {
                    useryou[*rear2].userchess_board[useryou[*rear2].tmprow][useryou[*rear2].tmpcol] = useryou[*rear2].tmp;
                    useryou[*rear2].tmprow = (-1);
                    useryou[*rear2].tmpcol = (-1);
                }
                useryouptr = &useryou[*rear2];
                printchess(usermeptr, useryouptr, &chess_board);
                *rear1 += 1;
                userme[*rear1] = userme[*rear1-1];
                usermeptr = &userme[*rear1];
                printf("依據圖上座標 User1 輸入想移動的棋子的原始座標空格移動後的位置座標:");
                scanf("%1s%d%d%d", &userme[*rear1].orignrow, &userme[*rear1].origncol, &userme[*rear1].afterrow, &userme[*rear1].aftercol);
                
                //user1輸入0代表user2悔棋
                if((userme[*rear1].orignrow == 48))
                {
                    *rear2 -= 1;
                    if(*rear2 == (-1))
                    {
                        printf("\n輸入不正確，請重新輸入\n");
                        *rear2 +=1;
                        break;
                    }
                    useryouptr = &useryou[*rear2];
                    *rear1 -= 1;
                    if(*rear1 == (-1))
                    {
                        printf("\n輸入不正確，請重新輸入\n");
                        *rear1 += 1;
                        break;
                    }
                    if((userme[*rear1].tmprow != (-1)) && (userme[*rear1].tmpcol != (-1)))//user2走的時候有吃掉user1的棋子
                    {
                        userme[*rear1].userchess_board[userme[*rear1].tmprow][userme[*rear1].tmpcol] = userme[*rear1].tmp;
                        userme[*rear1].tmprow = (-1);
                        userme[*rear1].tmpcol = (-1);
                    }
                    usermeptr = &userme[*rear1];
                    printchess(usermeptr, useryouptr, &chess_board);
                }
                //user1輸入s表示儲存 不儲存s
                else if(userme[*rear1].orignrow == 115)
                {
                    savedone = 0;
                    printf("\nrear1,rear2:%d %d\n", *rear1, *rear2);
                    while((*front1 < (*rear1-1)) || (*front2 < *rear2))
                    {
                        if(*front1 > *front2)
                        {
                            *front2 +=1;
                            //fprintf(fptr, "%c %d %d %d\n", useryou[*front2].orignrow, useryou[*front2].origncol, useryou[*front2].afterrow, useryou[*front2].aftercol);
                            userload[*count].orignrow = useryou[*front2].orignrow;//先寫到站存記憶體
                            userload[*count].origncol = useryou[*front2].origncol;
                            userload[*count].afterrow = useryou[*front2].afterrow;
                            userload[*count].aftercol = useryou[*front2].aftercol;
                            *count +=1;
                            printf("front2:%d\n", *front2);
                        }
                        else if(*front1 <= *front2)
                        {
                            *front1 +=1;//因為第一筆資料在rear = 1的時候 所以事先動再移 
                            //fprintf(fptr, "%c %d %d %d\n", userme[*front1].orignrow, userme[*front1].origncol, userme[*front1].afterrow, userme[*front1].aftercol);
                            userload[*count].orignrow = userme[*front1].orignrow;
                            userload[*count].origncol = userme[*front1].origncol;
                            userload[*count].afterrow = userme[*front1].afterrow;
                            userload[*count].aftercol = userme[*front1].aftercol;
                            *count +=1;
                            printf("front1:%d\n", *front1);
                        }   
                        savedone = 1;
                    }
                    //*front1 -=1;
                    //userme[*rear1] = userme[*rear1-1];
                    usermeptr = &userme[*rear1];
                    printf("依據圖上座標 User1 輸入想移動的棋子的原始座標空格移動後的位置座標:");
                    scanf("%1s%d%d%d", &userme[*rear1].orignrow, &userme[*rear1].origncol, &userme[*rear1].afterrow, &userme[*rear1].aftercol);
                }    
                else
                {
                    user1move(usermeptr, useryouptr);
                    user1eatuser2(usermeptr,useryouptr);
                    printchess(usermeptr, useryouptr, &chess_board);
                    //判斷勝利
                    if(whowins(&chess_board) == 1)
                    {
                        breaking = 1;
                        printf("\nuser1勝利！！！！\n\n\n");
                        break;
                    }
                    else if(whowins(&chess_board) == 2)
                    {
                        breaking =1;
                        printf("\nuser2勝利！！！！\n\n\n");
                        break;
                    }
                }
                *rear2 += 1;
                useryou[*rear2] = useryou[*rear2-1];
                useryouptr = &useryou[*rear2];
                printf("依據圖上座標 User2 輸入想移動的棋子的原始座標空格移動後的位置座標:");
                scanf("%1s%d%d%d", &useryou[*rear2].orignrow, &useryou[*rear2].origncol, &useryou[*rear2].afterrow, &useryou[*rear2].aftercol);
            }
            //user2輸入s表示儲存
            else if(useryou[*rear2].orignrow == 115)
            {
                savedone = 0;
                while((*front1 < *rear1) || (*front2 < (*rear2-1)))
                {
                    printf("\nrear1,rear2:%d %d\n", *rear1, *rear2);
                    if(*front1 > *front2)
                    {
                        *front2 +=1;
                        userload[*count].orignrow = useryou[*front2].orignrow;//先寫到站存記憶體
                        userload[*count].origncol = useryou[*front2].origncol;
                        userload[*count].afterrow = useryou[*front2].afterrow;
                        userload[*count].aftercol = useryou[*front2].aftercol;
                        *count +=1;
                        //fprintf(fptr, "%c %d %d %d\n", useryou[*front2].orignrow, useryou[*front2].origncol, useryou[*front2].afterrow, useryou[*front2].aftercol);
                        printf("front2:%d\n", *front2);
                    }
                    else if(*front1 <= *front2)
                    {
                        *front1 +=1;//因為第一筆資料在rear = 1的時候 所以事先動再移 
                        userload[*count].orignrow = userme[*front1].orignrow;//先寫到站存記憶體
                        userload[*count].origncol = userme[*front1].origncol;
                        userload[*count].afterrow = userme[*front1].afterrow;
                        userload[*count].aftercol = userme[*front1].aftercol;
                        *count +=1;
                        //fprintf(fptr, "%c %d %d %d\n", userme[*front1].orignrow, userme[*front1].origncol, userme[*front1].afterrow, userme[*front1].aftercol);
                        printf("front1:%d\n", *front1);
                    }
                    savedone = 1;
                }
                //*front2 -=1;
                //useryou[*rear2] = useryou[*rear2-1];
                useryouptr = &useryou[*rear2];
                printf("依據圖上座標 User2 輸入想移動的棋子的原始座標空格移動後的位置座標:");
                scanf("%1s%d%d%d", &useryou[*rear2].orignrow, &useryou[*rear2].origncol, &useryou[*rear2].afterrow, &useryou[*rear2].aftercol);
            }    
            else
            {
                break;
            }
        }
        if(breaking == 1)
        {
            break;
        }
        //rear2大於0才有辦法移動
        if(*rear2>0)
        {
            user2move(useryouptr, usermeptr);
            user2eatuser1(useryouptr,usermeptr);
        }
        printchess(usermeptr, useryouptr, &chess_board);
        //判斷勝利
        if(whowins(&chess_board) == 1)
        {
            printf("\nuser1勝利！！！！\n\n\n");
            break;
        }
        else if(whowins(&chess_board) == 2)
        {
            printf("\nuser2勝利！！！！\n\n\n");
            break;
        }

        *rear1 += 1;
        userme[*rear1] = userme[*rear1-1];
        usermeptr = &userme[*rear1];
        printf("依據圖上座標 User1 輸入想移動的棋子的原始座標空格移動後的位置座標:");
        scanf("%1s%d%d%d", &userme[*rear1].orignrow, &userme[*rear1].origncol, &userme[*rear1].afterrow, &userme[*rear1].aftercol);
        while(1)
        {
            if((userme[*rear1].orignrow == 48))
            {
                //user1輸入為0代表user2悔棋
                *rear2 -= 1;
                if(*rear2 == (-1))
                {
                    printf("\n輸入不正確，請重新輸入\n");
                    *rear2 +=1;
                    break;
                }
                useryouptr = &useryou[*rear2];
                *rear1 -= 1;
                if(*rear1 == (-1))
                {
                    *rear1 +=1;
                    printf("\n輸入不正確，請重新輸入\n");
                    break;
                }
                if((userme[*rear1].tmprow != (-1)) && (userme[*rear1].tmpcol != (-1)))
                {
                    userme[*rear1].userchess_board[userme[*rear1].tmprow][userme[*rear1].tmpcol] = userme[*rear1].tmp;
                    userme[*rear1].tmprow = (-1);
                    userme[*rear1].tmpcol = (-1);
                }
                usermeptr = &userme[*rear1];
                printchess(usermeptr, useryouptr, &chess_board);
                *rear2 += 1;
                useryou[*rear2] = useryou[*rear2-1];
                useryouptr = &useryou[*rear2];
                printf("依據圖上座標 User2 輸入想移動的棋子的原始座標空格移動後的位置座標:");
                scanf("%1s%d%d%d", &useryou[*rear2].orignrow, &useryou[*rear2].origncol, &useryou[*rear2].afterrow, &useryou[*rear2].aftercol);
                
                
                //user2輸入0代表user1悔棋
                if((useryou[*rear2].orignrow == 48))
                {
                    *rear1 = *rear1 - 1;
                    if(*rear1 == (-1))
                    {
                        printf("\n輸入不正確，請重新輸入\n");
                        *rear1 +=1;
                        break;
                    }
                    usermeptr = &userme[*rear1];
                    *rear2 = *rear2 - 1;
                    if(*rear2 == (-1))
                    {
                        printf("\n輸入不正確，請重新輸入\n");
                        *rear2 +=1;
                        break;
                    }
                    if((useryou[*rear2].tmprow != (-1)) && (useryou[*rear2].tmpcol != (-1)))
                    {
                        useryou[*rear2].userchess_board[useryou[*rear2].tmprow][useryou[*rear2].tmpcol] = useryou[*rear2].tmp;
                        useryou[*rear2].tmprow = (-1);
                        useryou[*rear2].tmpcol = (-1);
                    }
                    useryouptr = &useryou[*rear2];
                    printchess(usermeptr, useryouptr, &chess_board);
                }
                //user2輸入s儲存
                else if(useryou[*rear2].orignrow == 115)
                {
                    savedone = 0;
                    while((*front1 < *rear1)|| (*front2 < (*rear2-1)))
                    {
                        printf("\nrear1,rear2:%d %d\n", *rear1, *rear2);
                        if(*front1 > *front2)
                        {
                            *front2 +=1;
                            userload[*count].orignrow = useryou[*front2].orignrow;//先寫到站存記憶體
                            userload[*count].origncol = useryou[*front2].origncol;
                            userload[*count].afterrow = useryou[*front2].afterrow;
                            userload[*count].aftercol = useryou[*front2].aftercol;
                            *count +=1;
                            //fprintf(fptr, "%c %d %d %d\n", useryou[*front2].orignrow, useryou[*front2].origncol, useryou[*front2].afterrow, useryou[*front2].aftercol);
                            printf("front2:%d\n", *front2);
                        }
                        else if(*front1 <= *front2)
                        {
                            *front1 +=1;//因為第一筆資料在rear = 1的時候 所以是先動再移 
                            userload[*count].orignrow = userme[*front1].orignrow;//先寫到站存記憶體
                            userload[*count].origncol = userme[*front1].origncol;
                            userload[*count].afterrow = userme[*front1].afterrow;
                            userload[*count].aftercol = userme[*front1].aftercol;
                            *count +=1;
                            //fprintf(fptr, "%c %d %d %d\n", userme[*front1].orignrow, userme[*front1].origncol, userme[*front1].afterrow, userme[*front1].aftercol);
                            printf("front1:%d\n", *front1);
                        }
                        savedone =1;
                    }
                    //*front2 -=1;
                    //useryou[*rear2] = useryou[*rear2-1];
                    useryouptr = &useryou[*rear2];
                    printf("依據圖上座標 User2 輸入想移動的棋子的原始座標空格移動後的位置座標:");
                    scanf("%1s%d%d%d", &useryou[*rear2].orignrow, &useryou[*rear2].origncol, &useryou[*rear2].afterrow, &useryou[*rear2].aftercol);
                }    
                else
                {
                    user2move(useryouptr, usermeptr);
                    user2eatuser1(useryouptr,usermeptr);
                    printchess(usermeptr, useryouptr, &chess_board);
                    if(whowins(&chess_board) == 1)
                    {
                        breaking += 1;
                        printf("\nuser1勝利！！！！\n\n\n");
                        break;
                    }
                    else if(whowins(&chess_board) == 2)
                    {
                        breaking += 1;
                        printf("\nuser2勝利！！！！\n\n\n");
                        break;
                    }
                }
                *rear1 += 1;
                userme[*rear1] = userme [*rear1-1];
                usermeptr = &userme[*rear1];
                printf("依據圖上座標 User1 輸入想移動的棋子的原始座標空格移動後的位置座標:");
                scanf("%1s%d%d%d", &userme[*rear1].orignrow, &userme[*rear1].origncol, &userme[*rear1].afterrow, &userme[*rear1].aftercol);
            }
            //user1輸入s表示儲存
            else if(userme[*rear1].orignrow == 115)
            {
                savedone = 0;
                while((*front1 < (*rear1-1)) || (*front2 < *rear2))
                {
                    printf("\nrear1,rear2:%d %d\n", *rear1, *rear2);
                    if(*front1 > *front2)
                    {
                        *front2 +=1;
                        userload[*count].orignrow = useryou[*front2].orignrow;//先寫到站存記憶體
                        userload[*count].origncol = useryou[*front2].origncol;
                        userload[*count].afterrow = useryou[*front2].afterrow;
                        userload[*count].aftercol = useryou[*front2].aftercol;
                        *count +=1;
                        //fprintf(fptr, "%c %d %d %d\n", useryou[*front2].orignrow, useryou[*front2].origncol, useryou[*front2].afterrow, useryou[*front2].aftercol);
                        printf("front2:%d\n", *front2);
                    }
                    else if(*front1 <= *front2)
                    {
                        *front1 +=1;//因為第一筆資料在rear = 1的時候 所以事先動再移 
                        userload[*count].orignrow = userme[*front1].orignrow;//先寫到站存記憶體
                        userload[*count].origncol = userme[*front1].origncol;
                        userload[*count].afterrow = userme[*front1].afterrow;
                        userload[*count].aftercol = userme[*front1].aftercol;
                        *count +=1;
                        //fprintf(fptr, "%c %d %d %d\n", userme[*front1].orignrow, userme[*front1].origncol, userme[*front1].afterrow, userme[*front1].aftercol);
                        printf("front1:%d\n", *front1);
                    }
                    savedone =1;
                }
                //*front1 -=1;
                //userme[*rear1] = userme[*rear1-1];
                usermeptr = &userme[*rear1];
                printf("依據圖上座標 User1 輸入想移動的棋子的原始座標空格移動後的位置座標:");
                scanf("%1s%d%d%d", &userme[*rear1].orignrow, &userme[*rear1].origncol, &userme[*rear1].afterrow, &userme[*rear1].aftercol);
            }    
            else
            {
                break;
            }
        }
        if(breaking == 1)
        {
            break;
        }
        if(*rear1 >0)
        {
            user1move(usermeptr, useryouptr);
            user1eatuser2(usermeptr,useryouptr);
        }
        printchess(usermeptr, useryouptr, &chess_board);
        if(whowins(&chess_board) == 1)//判斷誰贏
        {
            printf("\nuser1勝利！！！！\n\n\n");
            break;
        }
        else if(whowins(&chess_board) == 2)
        {
            printf("\nuser2勝利！！！！\n\n\n");
            break;
        }
    }
}

