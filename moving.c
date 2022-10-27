#include "user.h"
#include "function.h"

int i, j;


//哪個棋子和如何移動 符合規則回傳1 不符合回傳0
int user1chessandmove(user  * user1, user * user2)
{
    switch(user1->userchess_board[(user1->orignrow)-1][(user1->origncol)-1])
    {
        //步兵只能向前1格
        case 'B':
            if((((user1->aftercol)-(user1->origncol)) != 0) || (((user1->afterrow)-(user1->orignrow))!=(-1)))
            {
                return 0;
            }
            else if(user1->afterrow == 1)//判斷是否不能走
            {
                return 0;
            }
            else
            {
                return 1;
            }
            break;

        //香車只能向前衝刺且不能跨越其他人
        case 'H':
    
            if((((user1->aftercol)-(user1->origncol)) != 0) || (((user1->afterrow)-(user1->orignrow))>=0))
            {
                return 0;
            }
            else if(user1->afterrow == 1)//判斷是否不能走
            {
                return 0;
            }
            else
            {
                for(i=((user1->afterrow)); i < ((user1->orignrow)-1); i++)   
                {
                    if((user1->userchess_board[i][(user1->origncol)-1] != ' ') || (user2->userchess_board[i][(user1->origncol)-1]) != ' ')
                    {
                        return 0;
                    }
                }
                if(user1->userchess_board[(user1->afterrow)-1][(user1->origncol)-1] != ' ')
                {
                    return 0;
                }
                return 1;
            }
            break;

        //桂馬只能往前2格且往右或往左1格
        case 'G':
            if((((user1->afterrow)-(user1->orignrow)) == (-2)) && ((((user1->aftercol)-(user1->origncol)) == 1) || (((user1->aftercol)-(user1->origncol)) == (-1))))
            {
                return 1;
            }
            else if(user1->afterrow == 2)//判斷是否不能走
            {
                return 0;
            }
            else 
            {
                return 0;
            }
            break;

        //銀將只能斜角方向一格或是前方一格
        case 'I':
            if((((((user1->afterrow)-(user1->orignrow)) == 1) || (((user1->afterrow)-(user1->orignrow)) == (-1))) && ((((user1->aftercol)-(user1->origncol)) == 1) || (((user1->aftercol)-(user1->origncol)) == (-1)))) || ((((user1->afterrow)-(user1->orignrow)) == (-1)) && (((user1->aftercol)-(user1->origncol))== 0))) 
            {
                return 1;
            }
            else
            {
                return 0;
            }
            break;

        //金將只能向前後左右左前右前一格
        case 'K':
            if((((user1->afterrow)-(user1->orignrow)) >= 2) || (((user1->afterrow)-(user1->orignrow)) <= (-2)) || (((user1->aftercol)-(user1->origncol)) >= 2) || (((user1->aftercol)-(user1->origncol)) <= (-2)))
            {
                return 0;
            }
            else 
            {
                if((((user1->afterrow)-(user1->orignrow)) == 1))
                {
                    if((((user1->aftercol)-(user1->origncol)) ==0))
                    {
                        return 1;
                    }
                    return 0;
                }
                return 1;
            }
            break;

        //角行只能斜向衝刺且不可繞過棋子
        case 'J':
            if(((double)(((user1->afterrow)-(user1->orignrow))/((user1->aftercol)-(user1->origncol))) ==1.0) || ((double)(((user1->afterrow)-(user1->orignrow))/((user1->aftercol)-(user1->origncol))) ==(-1.0)))
            {
                if((user1->afterrow < user1->orignrow) && (user1->aftercol > user1->origncol))
                {
                    for(i = (user1->orignrow-2), j = (user1->origncol);i >= (user1->afterrow), j <= (user1->aftercol-2); i--,j++)
                    {
                        if((user1->userchess_board[i][j] != ' ') || (user2->userchess_board[i][j]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user1->userchess_board[user1->afterrow-1][user1->aftercol-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                    
                }
                    
                
                if((user1->afterrow > user1->orignrow) && (user1->aftercol > user1->origncol))
                {
                    for(i = (user1->orignrow), j = (user1->origncol);i <= (user1->afterrow-2), j <= (user1->aftercol-2); i++,j++)
                    {
                        if((user1->userchess_board[i][j] != ' ') || (user2->userchess_board[i][j]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user1->userchess_board[user1->afterrow-1][user1->aftercol-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                }
                
                if((user1->afterrow < user1->orignrow) && (user1->aftercol < user1->origncol))
                {
                    for(i = (user1->orignrow-2), j = (user1->origncol-2);i >= (user1->afterrow), j >= (user1->aftercol); i--,j--)
                    {
                        if((user1->userchess_board[i][j] != ' ') || (user2->userchess_board[i][j]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user1->userchess_board[user1->afterrow-1][user1->aftercol-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                    
                }

                if((user1->afterrow > user1->orignrow) && (user1->aftercol < user1->origncol))
                {
                    for(i = (user1->orignrow), j = (user1->origncol-2);i <= (user1->afterrow-2), j >= (user1->aftercol); i++,j--)
                    {
                        if((user1->userchess_board[i][j] != ' ') || (user2->userchess_board[i][j]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user1->userchess_board[user1->afterrow-1][user1->aftercol-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                    
                }
            }
            else
            {
                return 0;
            }
            break;

        //飛車只能橫向或縱向移動 不可跨過棋子
        case 'F':
            if((((user1->afterrow)-(user1->orignrow)) == 0) || (((user1->aftercol)-(user1->origncol)) == 0))
            {
                
                if(user1->afterrow < user1->orignrow)
                {
                    for(i=(user1->orignrow-2); i >= (user1->afterrow); i--)   
                    {
                        if((user1->userchess_board[i][(user1->origncol)-1] != ' ') || (user2->userchess_board[i][(user1->origncol)-1]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user1->userchess_board[user1->afterrow-1][(user1->origncol)-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                }
                if(user1->afterrow > user1->orignrow)
                {
                    for(i=(user1->orignrow); i <= (user1->afterrow-2); i++)   
                    {
                        if((user1->userchess_board[i][(user1->origncol)-1] != ' ') || (user2->userchess_board[i][(user1->origncol)-1]) != ' ')
                        {
                            return 0;
                            
                        }
                    }
                    if(user1->userchess_board[user1->afterrow-1][(user1->origncol)-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                }
                if(user1->aftercol > user1->origncol)
                {
                    for(i=(user1->origncol); i <= (user1->aftercol-2); i++)   
                    {
                        if((user1->userchess_board[((user1->orignrow)-1)][i] != ' ') || (user2->userchess_board[((user1->orignrow)-1)][i]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user1->userchess_board[((user1->orignrow)-1)][user1->afterrow-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                }
                if(user1->aftercol < user1->origncol)
                {
                    for(i=(user1->origncol-2); i >= (user1->aftercol); i--)   
                    {
                        if((user1->userchess_board[((user1->orignrow)-1)][i] != ' ') || (user2->userchess_board[((user1->orignrow)-1)][i]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user1->userchess_board[((user1->orignrow)-1)][user1->afterrow-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                }
            }
            else
            {
                return 0;
            }
            break;

        //玉將八方一格
        default:
            if((((user1->afterrow)-(user1->orignrow)) >= 2) || (((user1->afterrow)-(user1->orignrow)) <= (-2)) || (((user1->aftercol)-(user1->origncol)) >= 2) || (((user1->aftercol)-(user1->origncol)) <= (-2)))
            {
                return 0;
            }
            else
            {
                return 1;
            }
            break;
    }
}

//哪個棋子和如何移動
int user2chessandmove(user * user2, user * user1)
{
    switch(user2->userchess_board[(user2->orignrow)-1][(user2->origncol)-1])
    {
        //步兵只能向前1格
        case 'b':
            if((((user2->aftercol)-(user2->origncol)) != 0) || (((user2->afterrow)-(user2->orignrow))!= 1 ))
            {
                return 0;
            }
            else if(user2->afterrow == 9)//判斷是否不能走
            {
                return 0;
            }
            else
            {
                return 1;
            }
            break;

        //香車只能向前衝刺且不能跨越其他人
        case 'h':
            if((((user2->aftercol)-(user2->origncol)) != 0) || (((user2->afterrow)-(user2->orignrow))<=0))
            {
                return 0;
            }
            else if(user2->afterrow == 9)//判斷是否不能走
            {
                return 0;
            }
            else
            {

                for(i=(user2->orignrow); i<=(user2->afterrow-2); i++)   
                {
                    if((user1->userchess_board[i][(user2->origncol)-1] != ' ') || (user2->userchess_board[i][(user2->origncol)-1]) != ' ')
                    {
                        return 0;
                    }
                }
                if(user2->userchess_board[user2->afterrow-1][user2->aftercol-1] != ' ')
                {
                return 0;
                }
                return 1;
            }
            break;

        //桂馬只能往前2格且往右或往左1格
        case 'g':
            if((((user2->afterrow)-(user2->orignrow)) == 2) && ((((user2->aftercol)-(user2->origncol)) == 1) || (((user2->aftercol)-(user2->origncol)) == (-1))))
            {
                return 1;
            }
            else if(user2->afterrow == 8)//判斷是否不能走
            {
                return 0;
            }
            else 
            {
                return 0;
            }
            break;

        //銀將只能斜角方向一格或是前方一格
        case 'i':
            if((((((user2->afterrow)-(user2->orignrow)) == 1) || (((user2->afterrow)-(user2->orignrow)) == (-1))) && ((((user2->aftercol)-(user2->origncol)) == 1) || (((user2->aftercol)-(user2->origncol)) == (-1)))) || ((((user2->afterrow)-(user2->orignrow)) == 1) && (((user2->aftercol)-(user2->origncol))== 0))) 
            {
                return 1;
            }
            else
            {
                return 0;
            }
            break;

        //金將只能向前後左右左前右前一格
        case 'k':
            if((((user2->afterrow)-(user2->orignrow)) >= 2) || (((user2->afterrow)-(user2->orignrow)) <= (-2)) || (((user2->aftercol)-(user2->origncol)) >= 2) || (((user2->aftercol)-(user2->origncol)) <= (-2)))
            {
                return 0;
            }
            else 
            {
                if((((user2->afterrow)-(user2->orignrow)) == (-1)))
                {
                    if((((user1->aftercol)-(user1->origncol)) ==0))
                    {
                        return 1;
                    }
                    return 0;
                }
                return 1;
            }
            break;

        //角行只能斜向衝刺且不可繞過棋子
        case 'j':
            if(((double)(((user2->afterrow)-(user2->orignrow))/((user2->aftercol)-(user2->origncol))) ==1.0) || ((double)(((user2->afterrow)-(user2->orignrow))/((user2->aftercol)-(user2->origncol))) ==(-1.0)))
            {
                if((user2->afterrow < user2->orignrow) && (user2->aftercol > user2->origncol))
                {
                    for(i = (user2->orignrow-2), j = (user2->origncol);i >= (user2->afterrow), j <= (user2->aftercol-2); i--,j++)
                    {
                        if((user1->userchess_board[i][j] != ' ') || (user2->userchess_board[i][j]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user2->userchess_board[user2->afterrow-1][user2->aftercol-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                }
                if((user2->afterrow > user2->orignrow) && (user2->aftercol > user2->origncol))
                {
                    for(i = (user2->orignrow), j = (user2->origncol);i <= (user2->afterrow-2), j <= (user2->aftercol-2); i++,j++)
                    {
                        if((user1->userchess_board[i][j] != ' ') || (user2->userchess_board[i][j]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user2->userchess_board[user2->afterrow-1][user2->aftercol-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                }
                if((user2->afterrow < user2->orignrow) && (user2->aftercol < user2->origncol))
                {
                    for(i = (user2->orignrow-2), j = (user2->origncol-2);i >= (user2->afterrow), j >= (user2->aftercol); i--,j--)
                    {
                        if((user1->userchess_board[i][j] != ' ') || (user2->userchess_board[i][j]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user2->userchess_board[user2->afterrow-1][user2->aftercol-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                }
                if((user2->afterrow > user2->orignrow) && (user2->aftercol < user2->origncol))
                {
                    for(i = (user2->orignrow), j = (user2->origncol-2);i <= (user2->afterrow-2), j >= (user2->aftercol); i++,j--)
                    {
                        if((user1->userchess_board[i][j] != ' ') || (user2->userchess_board[i][j]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user2->userchess_board[user2->afterrow-1][user2->aftercol-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                }
            }
            else
            {
                return 0;
            }
            break;

        //飛車只能橫向或縱向移動 不可跨過棋子
        case 'f':
            if(((user2->afterrow)-(user2->orignrow) == 0) || (((user2->aftercol)-(user2->origncol)) == 0))
            {
                if(user2->afterrow < user2->orignrow)
                {
                    for(i=(user2->orignrow-2); i >= (user2->afterrow); i--)   
                    {
                        if((user1->userchess_board[i][(user2->origncol)-1] != ' ') || (user2->userchess_board[i][(user2->origncol)-1]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user2->userchess_board[user2->afterrow-1][user2->origncol-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                }
                if(user2->afterrow > user2->orignrow)
                {
                    for(i=(user2->orignrow); i <= (user2->afterrow-2); i++)   
                    {
                        if((user1->userchess_board[i][(user2->origncol)-1] != ' ') || (user2->userchess_board[i][(user2->origncol)-1]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user2->userchess_board[user2->afterrow-1][user2->origncol-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                }
                if(user2->aftercol > user2->origncol)
                {
                    for(i=(user2->origncol); i <= (user2->aftercol-2); i++)   
                    {
                        if((user1->userchess_board[(user2->afterrow-1)][i] != ' ') || (user2->userchess_board[(user2->afterrow-1)][i]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user2->userchess_board[user2->orignrow-1][user2->aftercol-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                }
                if(user2->aftercol < user2->origncol)
                {
                    for(i=(user2->origncol-2); i >= (user2->aftercol); i--)   
                    {
                        if((user1->userchess_board[(user2->afterrow-1)][i] != ' ') || (user2->userchess_board[(user2->afterrow-1)][i]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user2->userchess_board[user2->afterrow-1][user2->origncol-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                }
            }
            else
            {
                return 0;
            }
            break;
        
        //玉將八方一格
        default:
            if((((user2->afterrow)-(user2->orignrow)) >= 2) || (((user2->afterrow)-(user2->orignrow)) <= (-2)) || (((user2->aftercol)-(user2->origncol)) >= 2) || (((user2->aftercol)-(user2->origncol)) <= (-2)))
            {
                return 0;
            }
            else
            {
                return 1;
            }
            break;
    }
}



