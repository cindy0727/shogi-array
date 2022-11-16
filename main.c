#include "user.h"
#include "function.h"

//getopt要用到的
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
extern char *optarg;
extern int optind;
extern int optopt;
extern int opterr;
extern int optreset;
int getopt(int argc, char * const *argv, const char *optstring);

int c;//getopt要用的
int mode = 0;//模式選項 1等於開新局 2等於讀檔

int main(int argc, char ** argv)
{
    //宣告一些位置
    usermeptr =  &userme[0];   
    useryouptr = &useryou[0];
    userloadptr = &userload[0];
    rearone = 0;
    reartwo = 0;
    frontone = 0;
    fronttwo = 0;
    loadfront = 0;
    
    //開始getopt
    opterr = 0;
    while((c = getopt(argc, argv, "ns:l:")) != -1)
    {
        switch(c)
        {
            case 'n':

                mode = 1;
                break;

            case 's':
                if((fptr = fopen(optarg, "w")) == NULL)
                {
                    printf("File could not be open.\n");
                    return 0;
                }
                mode = 1;
                break;

            case 'l':
                if((fptr = fopen(optarg, "r")) == NULL)
                {
                    printf("File could not be open.\n");
                    return 0;
                }
                mode = 2;
                break;

                

        }

    }

    
    //開始遊戲
    if(mode == 1)
    {
        initgame(&chess_board);
        game(&rearone, &reartwo, &frontone, &fronttwo);
        while((frontone != rearone) && (frontone != reartwo))
        {
            frontone +=1;
            fprintf(fptr, "%c %d %d %d\n", userme[frontone].orignrow, userme[frontone].origncol, userme[frontone].afterrow, userme[frontone].aftercol);
            fronttwo +=1;
            fprintf(fptr, "%c %d %d %d\n", useryou[fronttwo].orignrow, useryou[fronttwo].origncol, useryou[fronttwo].afterrow, useryou[fronttwo].aftercol);
        }

    }

    if(mode == 2)
    {
        initgame(&chess_board);
        //load();
    }
    

    fclose(fptr);

    return 0;
}

void initgame (user * chessboard)
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        chessboard->userchess_board[i][j] = ' ';
    }
    
}

