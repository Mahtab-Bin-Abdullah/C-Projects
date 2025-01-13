#include <stdio.h>
#include <stdlib.h>

char board[3][3];
const char PLAYER1 = 'X';
const char PLAYER2 = 'O';

void resetBoard()
{
    for(int i = 0; i < 3;i++)
    {
        for(int j = 0; j < 3;j++)
        {
            board[i][j] = ' ';
        }
    }
}
void printBoard()
{
    printf(" %c | %c | %c ",board[0][0],board[0][1],board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ",board[1][0],board[1][1],board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ",board[2][0],board[2][1],board[2][2]);
    printf("\n");

}

int checkFreespace()
{
    int freespace = 9;

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board[i][j] != ' ')
            {
                freespace--;
            }
        }
    }

    return freespace;
}
void player1move()
{
    int x,y;
    
    do
    {
    printf("Enter row number(1-3): ");
    scanf("%d", &x);
    x--;

    printf("Enter column number(1-3): ");
    scanf("%d", &y);
    y--;

    if(board[x][y] != ' ')
    {
        printf("currently occupied\n");
    }
    else
    {
        board[x][y] = PLAYER1;
        break;
    }

    }
     while (board[x][y] != ' ');
    
}
void player2move()
{
    int a,b;

    do
    {
        //Taking row input from player 2
        printf("Enter row numebr(1-3): ");
        scanf("%d", &a);
        a--;

        //Taking column input from player 2
        printf("Enter column number(1-3): ");
        scanf("%d", &b);
        b--;

        if(board[a][b] != ' ')
        {
            printf("currently occupied");
        }
        else
        {
            board[a][b] = PLAYER2;
            break;
        }
    }
     while (board[a][b] != ' ');
    
}
char checkWinner()
{
    //This loop will check rows
    for(int i = 0;i < 3;i++)
    {
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2])
        {
            return board[i][0];
        }
    }
    //This loop wil check columns
    for(int i = 0;i < 3;i++)
    {
        if(board[0][i] == board[1][i] && board[0][i] == board[2][i])
        {
            return board[0][i];
        }
    }
    //This loop will check diagonals
    for(int i = 0;i < 3;i++)
    {
        if(board[0][0] == board[1][1] && board[0][0] == board[2][2])
        {
            return board[0][0];
        }
        if(board[0][2] == board[1][1] && board[0][2] == board[2][0])
        {
            return board[0][2];
        }

    }
    return ' ';

}
void printWinner(char winner)
{
    if(winner == PLAYER1)
    {
        printf("Player 1 WINS!\n");
    }
    else if (winner == PLAYER2)
    {
        printf("Player 2 WINS\n");
    }
    else
    {
        printf("It's a tie!\n");
    }
    
}
void savegame()
{
    FILE *file = fopen("tic-tac-toe_save.txt", "w");
    if(file == NULL)
    {
        printf("Error saving the game.\n");
        return;
    }
    for(int i = 0;i < 3;i++)
    {
        for(int j = 0;j < 3;j++)
        {
            fputc(board[i][j],file);
        }
    }
    fclose (file);
    printf("Game saved successfully.\n");
}

void loadgame()
{
    FILE *file = fopen("tic-tac-toe_save.txt", "r");
    if (file == NULL)
    {
        printf("No saved game found.\n");
        return;
    }
    for(int i = 0;i < 3;i++)
    {
        for(int j = 0;j < 3;j++)
        {
            board[i][j] = fgetc(file);
        }
    }
    fclose(file);
    printf("Game loaded successfully.\n");
}
int main()
{
    char winner = ' ';
    int choice;

    printf("1.Start new game\n");
    printf("2.Load game\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    if (choice == 2)
    {
        loadgame();
    }
    else
    {
        resetBoard();
    }
    
    while (winner == ' ' && checkFreespace() !=0)
    {
        //player 1's turn
        printBoard();
        player1move();
        winner = checkWinner();
        if(winner != ' ' || checkFreespace() == 0)
        {
            break;
        }
        //player 2's turn
        printBoard();
        player2move();
        winner = checkWinner();
        if(winner != ' ' || checkFreespace() == 0)
        {
            break;
        }
    }
    printBoard();
    printWinner(winner);
    printf("Do you want to save your game?(1 for yes, 0 for no): ");
    scanf("%d", &choice);
    if(choice == 1)
    {
        savegame();
    }
    return 0;
}