#include "user.h"
#include "function.h"

int rear1 = 0;
int rear2 = 0;
int front1 = 0;
int front2 = 0;
int breakload = 0;
char bof;
int c;//計算第幾手
int tmpc;//從哪一手開始往回 因為要判定哪一手開始要讀資料
int ire ;//發現從往回的第一筆c不用剪1 做紀錄用

void load()
{
    c = 0;
    tmpc = 0;
    ire =0;
    //初始化雙方
    creat_user1(usermeptr);//usermee[0] = 原始棋盤
    creat_user2(useryouptr);//useryouu[0] = 原始棋盤
    printchess(usermeptr, useryouptr, &chess_board);

    //開始下棋
    //user1輸入
    rear1 += 1;
    userme[rear1] = userme[rear1-1];
    usermeptr = &userme[rear1];
    printf("輸入b往回一步，輸入f下一步:");
    scanf("%1s", &bof);
    if(bof == 'b')
    {
        printf("輸入不正確，請重新輸入:");
        scanf("%1s", &bof);
    }
    if(bof == 'f')
    {
        fscanf(fptr,"%1s%d%d%d", &userme[rear1].orignrow, &userme[rear1].origncol, &userme[rear1].afterrow, &userme[rear1].aftercol);
        c +=1;
        printf("%d\n", c);
        printf("%c%d%d%d", userme[rear1].orignrow, userme[rear1].origncol, userme[rear1].afterrow, userme[rear1].aftercol);
        user1move(usermeptr, useryouptr);
        printchess(usermeptr, useryouptr, &chess_board);
    }
    //第二手開始進入迴圈
    while(1)
    {
        rear2 += 1;
        //useryou[rear2] = useryou[rear2-1];
        for(int i=0;i<ROW;i++)
        {
            for(int j=0;j<COL;j++)
            {
                useryou[rear2].userchess_board[i][j] = useryou[rear2-1].userchess_board[i][j];
            }
        }
        useryouptr = &useryou[rear2];
        printf("輸入b往回一步，輸入f下一步:");
        scanf("%1s", &bof);
        while(1)
        {
            if(bof == 'b')
            {
                if(ire == 0)
                {
                    tmpc = c;
                }
                //tmpc = c;
                printf("%d %d %d\n", c,tmpc, ire);
                //user2輸入為b代表user1悔棋
                rear1 = rear1 - 1;
                if(rear1 == (-1))
                {
                    printf("\n輸入不正確，請重新輸入\n");
                    rear1 +=1;
                    break;
                }
                usermeptr = &userme[rear1];
                rear2 = rear2 - 1;
                if(rear2 == (-1))
                {
                    rear2 +=1;
                    printf("\n輸入不正確，請重新輸入\n");
                    break;
                }
                if((useryou[rear2].tmprow != (-1)) && (useryou[rear2].tmpcol != (-1)))//user1有吃掉user2的棋子
                {
                    useryou[rear2].userchess_board[useryou[rear2].tmprow][useryou[rear2].tmpcol] = useryou[rear2].tmp;
                    useryou[rear2].tmprow = (-1);
                    useryou[rear2].tmpcol = (-1);
                }
                //if(ire > 0)
                //{
                c -=1;
                //}
                printf("%d %d %d\n", c,tmpc, ire);
                ire +=1;
                //c -=1;
                useryouptr = &useryou[rear2];
                printchess(usermeptr, useryouptr, &chess_board);
                rear1 += 1;
                //userme[rear1] = userme[rear1-1];
                for(int i=0;i<ROW;i++)
                {
                    for(int j=0;j<COL;j++)
                    {
                        userme[rear1].userchess_board[i][j] = userme[rear1-1].userchess_board[i][j];
                    }
                }
                usermeptr = &userme[rear1];
                printf("輸入b往回一步，輸入f下一步:");
                scanf("%1s", &bof);
                
                //user1輸入b代表user2悔棋
                if(bof == 'b')
                {
                    rear2 -= 1;
                    if(rear2 == (-1))
                    {
                        printf("\n輸入不正確，請重新輸入\n");
                        rear2 +=1;
                        break;
                    }
                    useryouptr = &useryou[rear2];
                    rear1 -= 1;
                    if(rear1 == (-1))
                    {
                        printf("\n輸入不正確，請重新輸入\n");
                        rear1 += 1;
                        break;
                    }
                    if((userme[rear1].tmprow != (-1)) && (userme[rear1].tmpcol != (-1)))//user2走的時候有吃掉user1的棋子
                    {
                        userme[rear1].userchess_board[userme[rear1].tmprow][userme[rear1].tmpcol] = userme[rear1].tmp;
                        userme[rear1].tmprow = (-1);
                        userme[rear1].tmpcol = (-1);
                    }
                    //if(ire > 0)
                    //{
                    c -=1;
                    //}
                    printf("%d %d %d\n", c,tmpc, ire);
                    ire +=1;
                    //c -=1;
                    usermeptr = &userme[rear1];
                    printchess(usermeptr, useryouptr, &chess_board);
                }
                else
                {
                    //fscanf(fptr,"%1s%d%d%d", &userme[rear1].orignrow, &userme[rear1].origncol, &userme[rear1].afterrow, &userme[rear1].aftercol);
                    printf("%c%d%d%d", userme[rear1].orignrow, userme[rear1].origncol, userme[rear1].afterrow, userme[rear1].aftercol);
                    c +=1;
                    printf("%d %d %d\n", c,tmpc, ire);
                    user1move(usermeptr, useryouptr);
                    user1eatuser2(usermeptr,useryouptr);
                    printchess(usermeptr, useryouptr, &chess_board);
                    //判斷勝利
                    if(whowins(&chess_board) == 1)
                    {
                        breakload = 1;
                        printf("\nuser1勝利！！！！\n\n\n");
                        break;
                    }
                    else if(whowins(&chess_board) == 2)
                    {
                        breakload =1;
                        printf("\nuser2勝利！！！！\n\n\n");
                        break;
                    }
                }
                rear2 += 1;
                //useryou[rear2] = useryou[rear2-1];
                for(int i=0;i<ROW;i++)
                {
                    for(int j=0;j<COL;j++)
                    {
                        useryou[rear2].userchess_board[i][j] = useryou[rear2-1].userchess_board[i][j];
                    }
                }
                useryouptr = &useryou[rear2];
                printf("輸入b往回一步，輸入f下一步:");
                scanf("%1s", &bof);
            }
            else
            {
                break;
            }
        }
        if(breakload == 1)
        {
            break;
        }
        //rear2大於0才有辦法移動
        if(rear2>0)
        {
            c +=1;
            printf("%d %d %d\n", c,tmpc, ire);
            if(c > tmpc)
            {
                fscanf(fptr,"%1s%d%d%d", &useryou[rear2].orignrow, &useryou[rear2].origncol, &useryou[rear2].afterrow, &useryou[rear2].aftercol);
                ire = 0;
            }
            //fscanf(fptr,"%1s%d%d%d", &useryou[rear2].orignrow, &useryou[rear2].origncol, &useryou[rear2].afterrow, &useryou[rear2].aftercol);
            printf("%c%d%d%d", useryou[rear2].orignrow, useryou[rear2].origncol, useryou[rear2].afterrow, useryou[rear2].aftercol);
            //c +=1;
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

        rear1 += 1;
        //userme[rear1] = userme[rear1-1];
        for(int i=0;i<ROW;i++)
        {
            for(int j=0;j<COL;j++)
            {
                userme[rear1].userchess_board[i][j] = userme[rear1-1].userchess_board[i][j];
            }
        }
        usermeptr = &userme[rear1];
        printf("輸入b往回一步，輸入f下一步:");
        scanf("%1s", &bof);
        while(1)
        {
            if(bof == 'b')
            {
                if(ire == 0)
                {
                    tmpc = c;
                }
                //tmpc = c;
                printf("%d %d %d\n", c,tmpc, ire);
                //user1輸入為b代表user2悔棋
                rear2 -= 1;
                if(rear2 == (-1))
                {
                    printf("\n輸入不正確，請重新輸入\n");
                    rear2 +=1;
                    break;
                }
                useryouptr = &useryou[rear2];
                rear1 -= 1;
                if(rear1 == (-1))
                {
                    rear1 +=1;
                    printf("\n輸入不正確，請重新輸入\n");
                    break;
                }
                if((userme[rear1].tmprow != (-1)) && (userme[rear1].tmpcol != (-1)))
                {
                    userme[rear1].userchess_board[userme[rear1].tmprow][userme[rear1].tmpcol] = userme[rear1].tmp;
                    userme[rear1].tmprow = (-1);
                    userme[rear1].tmpcol = (-1);
                }
                //if(ire > 0)
                //{
                c -=1;
                printf("%d %d %d\n", c,tmpc,ire);
                //}
                ire +=1;
                //c -=1;
                usermeptr = &userme[rear1];
                printchess(usermeptr, useryouptr, &chess_board);
                rear2 += 1;
                //useryou[rear2] = useryou[rear2-1];
                for(int i=0;i<ROW;i++)
                {
                    for(int j=0;j<COL;j++)
                    {
                        useryou[rear2].userchess_board[i][j] = useryou[rear2-1].userchess_board[i][j];
                    }
                }
                useryouptr = &useryou[rear2];
                printf("輸入b往回一步，輸入f下一步:");
                scanf("%1s", &bof);
                
                
                //user2輸入b代表user1悔棋
                if(bof == 'b')
                {
                    rear1 = rear1 - 1;
                    if(rear1 == (-1))
                    {
                        printf("\n輸入不正確，請重新輸入\n");
                        rear1 +=1;
                        break;
                    }
                    usermeptr = &userme[rear1];
                    rear2 = rear2 - 1;
                    if(rear2 == (-1))
                    {
                        printf("\n輸入不正確，請重新輸入\n");
                        rear2 +=1;
                        break;
                    }
                    if((useryou[rear2].tmprow != (-1)) && (useryou[rear2].tmpcol != (-1)))
                    {
                        useryou[rear2].userchess_board[useryou[rear2].tmprow][useryou[rear2].tmpcol] = useryou[rear2].tmp;
                        useryou[rear2].tmprow = (-1);
                        useryou[rear2].tmpcol = (-1);
                    }
                    //if(ire > 0)
                    //{
                    c -=1;
                    //}
                    printf("%d %d %d\n", c,tmpc, ire);
                    ire +=1;
                    //c -=1;
                    useryouptr = &useryou[rear2];
                    printchess(usermeptr, useryouptr, &chess_board);
                }    
                else
                {
                    //fscanf(fptr,"%1s%d%d%d", &useryou[rear2].orignrow, &useryou[rear2].origncol, &useryou[rear2].afterrow, &useryou[rear2].aftercol);
                    printf("%c%d%d%d", useryou[rear2].orignrow, useryou[rear2].origncol, useryou[rear2].afterrow, useryou[rear2].aftercol);
                    c +=1;
                    printf("%d %d %d\n", c,tmpc, ire);
                    user2move(useryouptr, usermeptr);
                    user2eatuser1(useryouptr,usermeptr);
                    printchess(usermeptr, useryouptr, &chess_board);
                    if(whowins(&chess_board) == 1)
                    {
                        breakload += 1;
                        printf("\nuser1勝利！！！！\n\n\n");
                        break;
                    }
                    else if(whowins(&chess_board) == 2)
                    {
                        breakload += 1;
                        printf("\nuser2勝利！！！！\n\n\n");
                        break;
                    }
                }
                rear1 += 1;
                //userme[rear1] = userme [rear1-1];
                for(int i=0;i<ROW;i++)
                {
                    for(int j=0;j<COL;j++)
                    {
                        userme[rear1].userchess_board[i][j] = userme[rear1-1].userchess_board[i][j];
                    }
                }
                usermeptr = &userme[rear1];
                printf("輸入b往回一步，輸入f下一步:");
                scanf("%1s", &bof);
            }    
            else
            {
                break;
            }
        }
        if(breakload == 1)
        {
            break;
        }
        if(rear1 >0)
        {
            c +=1;
            printf("%d %d %d\n", c,tmpc, ire);
            if(c > tmpc)
            {
                fscanf(fptr,"%1s%d%d%d", &userme[rear1].orignrow, &userme[rear1].origncol, &userme[rear1].afterrow, &userme[rear1].aftercol);
                ire = 0;
            }
            //fscanf(fptr,"%1s%d%d%d", &userme[rear1].orignrow, &userme[rear1].origncol, &userme[rear1].afterrow, &userme[rear1].aftercol);
            printf("%c%d%d%d", userme[rear1].orignrow, userme[rear1].origncol, userme[rear1].afterrow, userme[rear1].aftercol);
            //c +=1;
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

/*void load()
{
    creat_user1(userme);
    creat_user2(useryou);

    //讀取資料
    rear1 += 1;
    fscanf(fptr,"%1s%d%d%d", &userme[rear1].orignrow, &userme[rear1].origncol, &userme[rear1].afterrow, &userme[rear1].aftercol);
    c+=1;
    rear2 += 1;
    fscanf(fptr,"%1s%d%d%d", &useryou[rear2].orignrow, &useryou[rear2].origncol, &useryou[rear2].afterrow, &useryou[rear2].aftercol);
    c +=1; 
    while(1)
    {
        if((useryou[rear2].orignrow != '^') && (userme[rear1].orignrow != '^'))
        {
            if(rear1 > rear2)
            {
                rear2 += 1;
                fscanf(fptr,"%1s%d%d%d", &useryou[rear2].orignrow, &useryou[rear2].origncol, &useryou[rear2].afterrow, &useryou[rear2].aftercol);
                c +=1;  
            }
            else if(rear1 <= rear2)
            {
                rear1 += 1;
                fscanf(fptr,"%1s%d%d%d", &userme[rear1].orignrow, &userme[rear1].origncol, &userme[rear1].afterrow, &userme[rear1].aftercol);
                c +=1;
            }   
        }
        else if(useryou[rear2].orignrow == '^')
        {
            rear2 -=1;
            break;
        }
        else if(userme[rear1].orignrow == '^')
        {
            rear1 -=1;
            break;
        }
    }


    //看資料對否 之後註解
    printf("%d %d %d\n", rear1, rear2, c);
    while((front1 < rear1) || (front2 <rear2 ))
    {
        front1 += 1;
        printf("front1 = %d %d  ", front1, front2);
        printf("%c %d %d %d\n", userme[front1].orignrow, userme[front1].origncol, userme[front1].afterrow, userme[front1].aftercol);
        front2 += 1;
        printf("front2 = %d %d  ", front1, front2);
        printf("%c %d %d %d\n", useryou[front2].orignrow, useryou[front2].origncol, useryou[front2].afterrow, useryou[front2].aftercol);
    }

    //寫進棋盤
    front1 = 0;
    front2 = 0;
    front1 += 1;
    for(int i=0;i<ROW;i++)
    {
        for(int j=0;j<COL;j++)
        {
            userme[front1].userchess_board[i][j] = userme[front1-1].userchess_board[i][j];
        }
    }
    usermeptr = &userme[front1];
    user1move(usermeptr, useryouptr);
    while((userme[front1].orignrow != '^') && (useryou[front2].orignrow != '^'))
    {
        front2 += 1;
        if(useryou[front2].orignrow == '^')
        {
            break;
        }
        for(int i=0;i<ROW;i++)
        {
            for(int j=0;j<COL;j++)
            {
                useryou[front2].userchess_board[i][j] = useryou[front2-1].userchess_board[i][j];
            }
        }
        printf("2 %d \n", front2);
        useryouptr = &useryou[front2];
        user2move(useryouptr, usermeptr);
        user2eatuser1(useryouptr,usermeptr);
        printchess(usermeptr, useryouptr, &chess_board);
        
        
        front1 += 1;
        if(userme[front1].orignrow == '^')
        {
            break;
        }
        for(int i=0;i<ROW;i++)
        {
            for(int j=0;j<COL;j++)
            {
                userme[front1].userchess_board[i][j] = userme[front1-1].userchess_board[i][j];
            }
        }
        printf("1 %d\n", front1);
        usermeptr = &userme[front1];
        user1move(usermeptr, useryouptr);
        user1eatuser2(usermeptr,useryouptr);
        printchess(usermeptr, useryouptr, &chess_board);
    }    
    
    int tmp = c;
    c = 0;
    front1 =0;
    front2 = 0;
    usermeptr = &userme[front1];
    useryouptr = &useryou[front2];
    
    printchess(usermeptr, useryouptr, &chess_board);

    printf("輸入f代表下一步,輸入b代表上一步：");
    scanf("%1s", &bof);
    printf("\n");
    while(loadfront <= tmp)
    {
        if((c %2)==1)
        {
            if(bof == 'f')
            {
                front1 += 1;
                usermeptr = &userme[front1];
                printchess(usermeptr, useryouptr, &chess_board);
                c += 1;
                loadfront += 1;
                printf("輸入f代表下一步,輸入b代表上一步：");
                scanf("%1s", &bof);
            }
            else if(bof == 'b')
            {
                front2 -= 1;
                if(front2 < 0)
                {
                    front2 = 0;
                    c -= 1;
                }
                useryouptr = &useryou[front2];
                printchess(usermeptr, useryouptr, &chess_board);
                c += 1;
                loadfront -= 1;
                printf("輸入f代表下一步,輸入b代表上一步：");
                scanf("%1s", &bof);

            }
        }

        else if((c % 2)==0)
        {
            if(bof == 'f')
            {
                front2 += 1;
                useryouptr = &useryou[front2];
            
                printchess(usermeptr, useryouptr, &chess_board);
                c += 1;
                loadfront += 1;
                printf("輸入f代表下一步,輸入b代表上一步：");
                scanf("%1s", &bof);
            }
            else if(bof == 'b')
            {
                front1 -= 1;
                if(front1 < 0)
                {
                    front1 = 0;
                    c -= 1;
                }
                usermeptr = &userme[front1];
                printchess(usermeptr, useryouptr, &chess_board);
                c += 1;
                loadfront -= 1;
                printf("輸入f代表下一步,輸入b代表上一步：");
                scanf("%1s", &bof);
            }
        }

        if(loadfront == (tmp +1))
        {
            if(bof == 'b')
            {
                loadfront -= 1;
            }
            else if(bof == 'f')
            {
                break;
            }
        }

        

       
    }
    printf("\n復盤結束!\n");
            

}*/