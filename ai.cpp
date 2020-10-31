#include <bits/stdc++.h>
#define pii pair<int, int>
#define NINF -9999
#define PINF 9999
#define SEARCH_DEPTH 5

using namespace std;

int mode = 8, turn = 2, opponent = 1;

int pieceSquareTable[8][8] = {
    {-80, -25, -20, -20, -20, -20, -25, -80},
    {-25, 10, 10, 10, 10, 10, 10, -25},
    {-20, 10, 25, 25, 25, 25, 10, -20},
    {-20, 10, 25, 50, 50, 25, 10, -20},
    {-20, 10, 25, 50, 50, 25, 10, -20},
    {-20, 10, 25, 25, 25, 25, 10, -20},
    {-25, 10, 10, 10, 10, 10, 10, -25},
    {-80, -25, -20, -20, -20, -20, -25, -80}};

int board[8][8] = {
    {0, 2, 2, 2, 2, 2, 2, 0},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {0, 2, 2, 2, 2, 2, 2, 0}};

int _move[2][2] = {
    {-1, -1},
    {-2, -2}
};

vector<pii> findMoves(int x, int y)
{
    int horizontal = 0, vertical = 0, primary = 0, secondary = 0;
    vector<pii> moves;

    //hozizontal
    for (int i = 0; i < mode; i++)
    {
        if (board[x][i] != 0)
            horizontal++;
    }

    //vertical
    for (int i = 0; i < mode; i++)
    {
        if (board[i][y] != 0)
            vertical++;
    }

    //primary
    int a = x, b = y;
    while (a < mode && b < mode)
    {
        if (board[a][b] != 0)
            primary++;
        a++;
        b++;
    }

    a = x - 1, b = y - 1;
    while (a >= 0 && b >= 0)
    {
        if (board[a][b] != 0)
            primary++;
        a--;
        b--;
    }

    //secondary
    a = x, b = y;
    while (a >= 0 && b < mode)
    {
        if (board[a][b] != 0)
            secondary++;
        a--;
        b++;
    }

    a = x + 1, b = y - 1;
    while (a < mode && b >= 0)
    {
        if (board[a][b] != 0)
            secondary++;
        a++;
        b--;
    }

    //finding valid moves
    //horizontal
    bool valid = true;
    for (int i = 1; i <= horizontal; i++)
    {
        if ((y + i >= mode) || (i != horizontal && board[x][y + i] == opponent) || (i == horizontal && board[x][y + i] == turn))
        {
            valid = false;
            break;
        }
    }

    if (valid)
    {
        moves.push_back(make_pair(x, y + horizontal));
    }

    valid = true;
    for (int i = 1; i <= horizontal; i++)
    {
        if ((y - i < 0) || (i != horizontal && board[x][y - i] == opponent) || (i == horizontal && board[x][y - i] == turn))
        {
            valid = false;
            break;
        }
    }

    if (valid)
    {
        moves.push_back(make_pair(x, y - horizontal));
    }

    //vertical
    valid = true;
    for (int i = 1; i <= vertical; i++)
    {
        if ((x + i >= mode) || (i != vertical && board[x + i][y] == opponent) || (i == vertical && board[x + i][y] == turn))
        {
            valid = false;
            break;
        }
    }

    if (valid)
    {
        moves.push_back(make_pair(x + vertical, y));
    }

    valid = true;
    for (int i = 1; i <= vertical; i++)
    {
        if ((x - i < 0) || (i != vertical && board[x - i][y] == opponent) || (i == vertical && board[x - i][y] == turn))
        {
            valid = false;
            break;
        }
    }

    if (valid)
    {
        moves.push_back(make_pair(x - vertical, y));
    }

    //primary
    valid = true;
    for (int i = 1; i <= primary; i++)
    {
        if ((x + i >= mode || y + i >= mode) || (i != primary && board[x + i][y + i] ==opponent) || (i == primary && board[x + i][y + i] == turn))
        {
            valid = false;
            break;
        }
    }

    if (valid)
    {
        moves.push_back(make_pair(x + primary, y + primary));
    }

    valid = true;
    for (int i = 1; i <= primary; i++)
    {
        if ((x - i < 0 || y - i < 0) || (i != primary && board[x - i][y - i] == opponent) || (i == primary && board[x - i][y - i] == turn))
        {
            valid = false;
            break;
        }
    }

    if (valid)
    {
        moves.push_back(make_pair(x - primary, y - primary));
    }

    //secondary
    valid = true;
    for (int i = 1; i <= secondary; i++)
    {
        if ((x - i < 0 || y + i >= mode) || (i != secondary && board[x - i][y + i] == opponent) || (i == secondary && board[x - i][y + i] == turn))
        {
            valid = false;
            break;
        }
    }

    if (valid)
    {
        moves.push_back(make_pair(x - secondary, y + secondary));
    }

    valid = true;
    for (int i = 1; i <= secondary; i++)
    {
        if ((x + i >= mode || y - i < 0) || (i != secondary && board[x + i][y - i] == opponent) || (i == secondary && board[x + i][y - i] == turn))
        {
            valid = false;
            break;
        }
    }

    if (valid)
    {
        moves.push_back(make_pair(x + secondary, y - secondary));
    }

    return moves;
}

int evalFunction()
{
    int eval = 0, player1val = 0, player2val = 0;
    for (int i = 0; i < mode; i++)
    {
        for (int j = 0; j < mode; j++)
        {
            if (board[i][j] == 2)
            {
                player2val += pieceSquareTable[i][j];
            }
            if (board[i][j] == 1)
            {
                player1val += pieceSquareTable[i][j];
            }
        }
    }
    eval = player1val - player2val;
    return eval;
}

void boardPrint()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cerr << board[i][j] << " ";
        }
        cerr << endl;
    }
}

vector<pair<pii, vector<pii>>> childGen()
{
    vector<pair<pii, vector<pii>>> children;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] == turn)
            {
                vector<pii> moves = findMoves(i, j);
                children.push_back(make_pair(make_pair(i, j), moves));
            }
        }
    }

    return children;
}

int minimax(int depth, bool maximizing, int alpha, int beta)
{
    if (depth == 0){
        int a = evalFunction();
        /*cout << "Here1 at depth " << depth << endl;
        cout << a << endl;*/
        return a;
    }

    if (maximizing)
    {
        //cout << "Here1 at depth " << depth << endl;
        int bestVal = NINF;
        vector<pair<pii, vector<pii>>> children = childGen();
        int value;
        for (int i = 0; i < children.size(); i++)
        {
            bool breakLoop = false;
            pair<pii, vector<pii>> a = children[i];
            pii source = a.first;
            //cout << "Sorce: " << source.first << " " << source.second << endl;
            vector<pii> moves = a.second;
            for (int j = 0; j < moves.size(); j++)
            {
                bool capture = false;
                pii dest = moves[j];
                //cout << "Dest: " << dest.first << " " << dest.second << endl;
                board[source.first][source.second] = 0;
                if(board[dest.first][dest.second] == opponent){
                    capture = true;
                }
                board[dest.first][dest.second] = turn;
                //boardPrint();
                value = minimax(depth - 1, false, alpha, beta);
                if (value>bestVal && depth == SEARCH_DEPTH){
                    _move[0][0] = source.first;
                    _move[0][1] = source.second;
                    _move[1][0] = dest.first;
                    _move[1][1] = dest.second;
                }
                bestVal = max(value, bestVal);
                alpha = max(alpha, bestVal);
                board[source.first][source.second] = turn;
                board[dest.first][dest.second] = (capture) ? opponent : 0;
                if (beta <= alpha){
                    breakLoop = true;
                    break;
                }
            }
            if(breakLoop)
                break;
        }
        return bestVal;
    }
    else
    {
        //cout << "Here1 at depth " << depth << endl;
        int bestVal = PINF;
        vector<pair<pii, vector<pii>>> children = childGen();
        int value;
        for (int i = 0; i < children.size(); i++)
        {
            bool breakLoop = false;
            pair<pii, vector<pii>> a = children[i];
            pii source = a.first;
            //cout << "Sorce: " << source.first << " " << source.second << endl;
            vector<pii> moves = a.second;
            for (int j = 0; j < moves.size(); j++)
            {
                bool capture = false;
                pii dest = moves[j];
                //cout << "Dest: " << dest.first << " " << dest.second << endl;
                board[source.first][source.second] = 0;
                if(board[dest.first][dest.second] == opponent){
                    capture = true;
                }
                board[dest.first][dest.second] = turn;
                //boardPrint();
                value = minimax(depth - 1, true, alpha, beta);
                if (value<bestVal && depth == SEARCH_DEPTH){
                    _move[0][0] = source.first;
                    _move[0][1] = source.second;
                    _move[1][0] = dest.first;
                    _move[1][1] = dest.second;
                }
                bestVal = min(value, bestVal);
                beta = min(beta, bestVal);
                board[source.first][source.second] = turn;
                board[dest.first][dest.second] = (capture) ? opponent : 0;
                if (beta <= alpha){
                    breakLoop = true;
                    break;
                }
            }
            if(breakLoop)
                break;
        }
        return bestVal;
    }

    return 0;
}

int main()
{
    string s;
    int a, b, c, d;
    getline(cin, s);
    getline(cin, s);
    while (true)
    {
        cin >> a >> b >> c >> d;
        board[a][b] = 0;
        board[c][d] = opponent;
        minimax(SEARCH_DEPTH, false, NINF, PINF);
        board[_move[0][0]][_move[0][1]] = 0;
        board[_move[1][0]][_move[1][1]] = turn;
        cout << _move[0][0] << endl;
        cout << _move[0][1] << endl;
        cout << _move[1][0] << endl;
        cout << _move[1][1] << endl;
    }

    // turn = 2;

    return 0;
}