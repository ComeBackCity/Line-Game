#include <bits/stdc++.h>
#define pii pair<int, int>
#define NINF -9999
#define PINF 9999

using namespace std;

int SEARCH_DEPTH, mode;
int turn, opponent;
//int turn = 2, opponent = 1;

int pieceSquareTableInitial[8][8] = {
    {-80, -25, -20, -20, -20, -20, -25, -80},
    {-25, 10, 10, 10, 10, 10, 10, -25},
    {-20, 10, 25, 25, 25, 25, 10, -20},
    {-20, 10, 25, 50, 50, 25, 10, -20},
    {-20, 10, 25, 50, 50, 25, 10, -20},
    {-20, 10, 25, 25, 25, 25, 10, -20},
    {-25, 10, 10, 10, 10, 10, 10, -25},
    {-80, -25, -20, -20, -20, -20, -25, -80}};

vector<vector<int>> board;
vector<vector<int>> pieceSquareTable;

int _move[2][2] = {
    {-1, -1},
    {-2, -2}};

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
    if (y + horizontal < mode)
    {
        valid = true;
        for (int i = 1; i <= horizontal; i++)
        {
            if ((i != horizontal && board[x][y + i] == opponent) || (i == horizontal && board[x][y + i] == turn))
            {
                valid = false;
                break;
            }
        }

        if (valid)
        {
            moves.push_back(make_pair(x, y + horizontal));
        }
    }

    if (y - horizontal >= 0)
    {
        valid = true;
        for (int i = 1; i <= horizontal; i++)
        {
            if ((i != horizontal && board[x][y - i] == opponent) || (i == horizontal && board[x][y - i] == turn))
            {
                valid = false;
                break;
            }
        }

        if (valid)
        {
            moves.push_back(make_pair(x, y - horizontal));
        }
    }

    //vertical
    if (x + vertical < mode)
    {
        valid = true;
        for (int i = 1; i <= vertical; i++)
        {
            if ((i != vertical && board[x + i][y] == opponent) || (i == vertical && board[x + i][y] == turn))
            {
                valid = false;
                break;
            }
        }

        if (valid)
        {
            moves.push_back(make_pair(x + vertical, y));
        }
    }

    if (x - vertical >= 0)
    {
        valid = true;
        for (int i = 1; i <= vertical; i++)
        {
            if ((i != vertical && board[x - i][y] == opponent) || (i == vertical && board[x - i][y] == turn))
            {
                valid = false;
                break;
            }
        }

        if (valid)
        {
            moves.push_back(make_pair(x - vertical, y));
        }
    }

    //primary
    valid = true;
    if (x + primary < mode && y + primary < mode)
    {
        for (int i = 1; i <= primary; i++)
        {
            if ((i != primary && board[x + i][y + i] == opponent) || (i == primary && board[x + i][y + i] == turn))
            {
                valid = false;
                break;
            }
        }

        if (valid)
        {
            moves.push_back(make_pair(x + primary, y + primary));
        }
    }

    if (x - primary >= 0 && y - primary >= 0)
    {
        valid = true;
        for (int i = 1; i <= primary; i++)
        {
            if ((i != primary && board[x - i][y - i] == opponent) || (i == primary && board[x - i][y - i] == turn))
            {
                valid = false;
                break;
            }
        }

        if (valid)
        {
            moves.push_back(make_pair(x - primary, y - primary));
        }
    }

    //secondary
    if (x - secondary >= 0 && y + secondary < mode)
    {
        valid = true;
        for (int i = 1; i <= secondary; i++)
        {
            if ((i != secondary && board[x - i][y + i] == opponent) || (i == secondary && board[x - i][y + i] == turn))
            {
                valid = false;
                break;
            }
        }

        if (valid)
        {
            moves.push_back(make_pair(x - secondary, y + secondary));
        }
    }

    if (x + secondary < mode && y - secondary >= 0)
    {
        valid = true;
        for (int i = 1; i <= secondary; i++)
        {
            if ((i != secondary && board[x + i][y - i] == opponent) || (i == secondary && board[x + i][y - i] == turn))
            {
                valid = false;
                break;
            }
        }

        if (valid)
        {
            moves.push_back(make_pair(x + secondary, y - secondary));
        }
    }
    return moves;
}

int pieceSquareHeuristic()
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

int evalFunction()
{
    int eval = pieceSquareHeuristic();
    return eval;
}

void boardPrint()
{
    for (int i = 0; i < mode; i++)
    {
        for (int j = 0; j < mode; j++)
        {
            cerr << board[i][j] << " ";
        }
        cerr << endl;
    }
}

vector<pair<pii, vector<pii>>> childGen()
{
    vector<pair<pii, vector<pii>>> children;
    for (int i = 0; i < mode; i++)
    {
        for (int j = 0; j < mode; j++)
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
    if (depth == 0)
    {
        int a = evalFunction();
        return a;
    }

    if (maximizing)
    {
        int bestVal = NINF;
        vector<pair<pii, vector<pii>>> children = childGen();
        int value;
        for (int i = 0; i < children.size(); i++)
        {
            bool breakLoop = false;
            pair<pii, vector<pii>> a = children[i];
            pii source = a.first;
            vector<pii> moves = a.second;
            for (int j = 0; j < moves.size(); j++)
            {
                bool capture = false;
                pii dest = moves[j];
                board[source.first][source.second] = 0;
                if (board[dest.first][dest.second] == opponent)
                {
                    capture = true;
                }
                board[dest.first][dest.second] = turn;
                value = minimax(depth - 1, false, alpha, beta);
                if (value > bestVal && depth == SEARCH_DEPTH)
                {
                    _move[0][0] = source.first;
                    _move[0][1] = source.second;
                    _move[1][0] = dest.first;
                    _move[1][1] = dest.second;
                }
                bestVal = max(value, bestVal);
                alpha = max(alpha, bestVal);
                board[source.first][source.second] = turn;
                board[dest.first][dest.second] = (capture) ? opponent : 0;
                if (beta <= alpha)
                {
                    breakLoop = true;
                    break;
                }
            }
            if (breakLoop)
                break;
        }
        return bestVal;
    }
    else
    {
        int bestVal = PINF;
        vector<pair<pii, vector<pii>>> children = childGen();
        int value;
        for (int i = 0; i < children.size(); i++)
        {
            bool breakLoop = false;
            pair<pii, vector<pii>> a = children[i];
            pii source = a.first;
            vector<pii> moves = a.second;
            for (int j = 0; j < moves.size(); j++)
            {
                bool capture = false;
                pii dest = moves[j];
                board[source.first][source.second] = 0;
                if (board[dest.first][dest.second] == opponent)
                {
                    capture = true;
                }
                board[dest.first][dest.second] = turn;
                value = minimax(depth - 1, true, alpha, beta);
                if (value < bestVal && depth == SEARCH_DEPTH)
                {
                    _move[0][0] = source.first;
                    _move[0][1] = source.second;
                    _move[1][0] = dest.first;
                    _move[1][1] = dest.second;
                }
                bestVal = min(value, bestVal);
                beta = min(beta, bestVal);
                board[source.first][source.second] = turn;
                board[dest.first][dest.second] = (capture) ? opponent : 0;
                if (beta <= alpha)
                {
                    breakLoop = true;
                    break;
                }
            }
            if (breakLoop)
                break;
        }
        return bestVal;
    }

    return 0;
}

int main(int argc, char **argv)
{
    mode = atoi(argv[1]);
    SEARCH_DEPTH = 5;
    turn = atoi(argv[2]);
    opponent = atoi(argv[3]);
    bool maximizing = (turn == 1) ? true : false;

    board = vector<vector<int>>(mode, vector<int>(mode, 0));
    pieceSquareTable = vector<vector<int>>(mode, vector<int>(mode, 0));

    if (mode == 8)
    {
        for (int i = 0; i < mode; i++)
        {
            for (int j = 0; j < mode; j++)
            {
                pieceSquareTable[i][j] = pieceSquareTableInitial[i][j];
            }
        }
    }
    else
    {
        for (int i = 0; i < mode; i++)
        {
            for (int j = 0; j < mode; j++)
            {
                pieceSquareTable[i][j] = pieceSquareTableInitial[i + 1][j + 1];
            }
        }
        pieceSquareTable[0][0] = 0;
        pieceSquareTable[0][mode - 1] = 0;
        pieceSquareTable[mode - 1][0] = 0;
        pieceSquareTable[mode - 1][mode - 1] = 0;
    }

    for (int i = 0; i < mode; i++)
    {
        for (int j = 0; j < mode; j++)
        {
            if ((i == 0 || i == mode - 1) && (j != 0 || j != mode - 1))
            {
                board[i][j] = 2;
            }
            else if ((i != 0 || i != mode - 1) && (j == 0 || j == mode - 1))
            {
                board[i][j] = 1;
            }
            else
            {
                board[i][j] = 0;
            }
        }
    }
    board[0][0] = 0;
    board[0][mode - 1] = 0;
    board[mode - 1][0] = 0;
    board[mode - 1][mode - 1] = 0;

    string s;
    int a, b, c, d;
    getline(cin, s);
    getline(cin, s);
    while (true)
    {
        cin >> a >> b >> c >> d;
        if (a < 0 || b < 0 || c < 0 || d < 0)
        {
        }
        else
        {
            board[a][b] = 0;
            board[c][d] = opponent;
        }
        minimax(SEARCH_DEPTH, maximizing, NINF, PINF);
        board[_move[0][0]][_move[0][1]] = 0;
        board[_move[1][0]][_move[1][1]] = turn;
        cout << _move[0][0] << endl;
        cout << _move[0][1] << endl;
        cout << _move[1][0] << endl;
        cout << _move[1][1] << endl;
    }

    return 0;
}