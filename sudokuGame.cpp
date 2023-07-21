#include <iostream>
#include <stdlib.h>
#define N 9
using namespace std;
int board[N][N] = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}};
class GameSolver
{
public:
    void printSudoko();
    bool presentInRow(int row, int num);
    bool presentInCol(int col, int num);
    bool presentInBox(int boxRow, int boxCol, int num);
    bool isEmpty(int &row, int &col);
    bool isValid(int row, int col, int num);
    bool sudokoSolve();
};
void GameSolver::printSudoko()
{
    cout << "--------------------" << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << board[i][j] << " ";
            if (j == 2 || j == 5)
                cout << "|";
        }
        cout << endl;
        if (i == 2 || i == 5)
            cout << "--------------------" << endl;
    }
    cout << "--------------------" << endl;
}
bool GameSolver::presentInRow(int row, int num)
{
    for (int col = 0; col < N; col++)
    {
        if (board[row][col] == num)
        {
            return true;
        }
    }
    return false;
}
bool GameSolver::presentInCol(int col, int num)
{
    for (int row = 0; row < N; row++)
    {
        if (board[row][col] == num)
        {
            return true;
        }
    }
    return false;
}
bool GameSolver::presentInBox(int boxRow, int boxCol, int num)
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (board[row + boxRow][col + boxCol] == num)
            {
                return true;
            }
        }
    }
    return false;
}
bool GameSolver::isEmpty(int &row, int &col)
{

    for (row = 0; row < N; row++)
    {
        for (col = 0; col < N; col++)
        {
            if (board[row][col] == 0)
            {
                return true;
            }
        }
    }
    return false;
}
bool GameSolver::isValid(int row, int col, int num)
{
    return !presentInRow(row, num) && !presentInCol(col, num) &&
           !presentInBox(row - row % 3, col - col % 3, num);
}
bool GameSolver::sudokoSolve()
{
    int row, col;
    if (!isEmpty(row, col))
    {
        return true;
    }
    for (int num = 1; num <= N; num++)
    {
        if (isValid(row, col, num))
        {
            board[row][col] = num;
            if (sudokoSolve())
            {
                return true;
            }
            board[row][col] = 0;
        }
    }
    return false;
}
class UserSolver : public GameSolver
{
public:
    void displayConsole(int copyBoard[N][N]);

    void solveConsole(int copyBoard[N][N]);
    bool check(int copyBoard[N][N]);
};
void UserSolver::displayConsole(int copyBoard[N][N])
{
    int x = 0, y = 0;
    cout << "\033[1m\033[34m";
    cout << "--------------------" << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (copyBoard[i][j] != 0)
            {
                cout << "\033[1m\033[34m" << copyBoard[i][j] << " ";
                y++;
            }
            else if (copyBoard[i][j] == 0 && i == x && j == y)
            {
                cout << "\033[32m"
                     << "X"
                     << " ";
            }
            else
            {
                cout << "\033[1m\033[34m"
                     << "_ ";
            }
            if (j == 2 || j == 5)
            {
                cout << "\033[1m\033[34m"
                     << "|";
            }
        }
        if (y == 9)
        {
            x++;
        }
        y = 0;
        cout << endl;
        if (i == 2 || i == 5)
            cout << "--------------------" << endl;
    }

    cout << "--------------------" << endl;
}
void UserSolver::solveConsole(int copyBoard[N][N])
{
    int row, col;
    for (row = 0; row < N; row++)
    {
        for (col = 0; col < N; col++)
        {
            if (copyBoard[row][col] == 0)
            {
                int value;
                cin >> value;
                copyBoard[row][col] = value;
                system("CLS");
                displayConsole(copyBoard);
            }
        }
    }
}
bool UserSolver::check(int copyBoard[N][N])
{
    int i, j;
    bool flag = true;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (board[i][j] != copyBoard[i][j])
            {
                flag = false;
                break;
            }
        }
    }
    return flag;
}
int main()
{
    int copyBoard[N][N];
    for (int i = 0; i < N; i++)

    {
        for (int j = 0; j < N; j++)
        {
            copyBoard[i][j] = board[i][j];
        }
    }
    UserSolver g;
    g.sudokoSolve();
    g.displayConsole(copyBoard);
    g.solveConsole(copyBoard);
    if (g.check(copyBoard))
    {
        system("CLS");
        cout << "You Won" << endl;
        g.printSudoko();
    }
    else
    {
        system("CLS");
        cout << "Sorry! You lost..." << endl;
        cout << "Solved Sudoku: " << endl;
        g.printSudoko();
    }
    return 0;
}