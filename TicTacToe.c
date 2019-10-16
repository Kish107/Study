#include <stdio.h>
#include <stdbool.h>
#define max_table_size 10
#define ROW 0
#define COL 1

// Getting the table size from the user.
int get_current_table_length()
{
    
    int tmp;
    printf("\nEnter the TicTacToe table size (1-10):\n");
    scanf("%d", &tmp);
    return tmp;
}

// Prints a table.
void print_table(int len, char table[len][len])
{
    for(int i = 0; i < len; i++)
    {
        for(int j = 0; j < len; j++)
        {
            printf("%c ", table[i][j]);
        }
        printf("\n");
    }
}

// Checking if there is a winner. Returns ints accordingly ( 0 == tie, 1 == player 1, 2 == player 2) 
bool is_win(int len, char table[len][len])
{
    bool win_row;
    bool win_col;
    bool win_sln_one = true;
    bool win_sln_two = true;

    for(int i = 0; i < len; i++)
    {
        win_row = true;
        win_col = true;

        // Rows and columns
        for(int j = 0; j < len - 1; j++)
        {

            // Escape if
            if(table[i][j] == '_' || (!win_row && !win_col))
            {
                win_row = false;
                win_col = false;
                break;

            }   

            // Rows
            win_row = (table[i][j] != table[i][j + 1]);

            // columns
            win_col = (table[j][i] != table[j + 1][i]);
               
        }

        // Slants
        if(i < len - 1)
            win_sln_one = (table[i][i] != table[i + 1][i + 1] && win_sln_one);
            win_sln_two = (table[i][len - i - 1] != table[i + 1][len - i - 2] && win_sln_two);
    }

    return (win_col || win_row || win_sln_one) || win_sln_two;
}

// Checking if the place is free.
bool is_free(int len, char table[len][len], int row, int col)
{
    if(table[row][col] == '_')
        return true;

    return false;
}

// Create the first table.
void format_table(int len, char table[len][len])
{
    for(int i = 0; i < len * len; i++)
        for(int j = 0; j < len * len; j++)
            table[i][j] = '_';
}

// Prepare the table for the next turn.
void update_table(int len, char table[len][len], int all_turns[][2], int turn)
{
    format_table(len, table);

    for(int i = 0; i < turn; i++)
    {
         printf("\n%d %d\n", all_turns[i][ROW], all_turns[i][COL]);
         // Output: 1600085855 1600085855

        if((i + 1) % 2 != 0)
            table[all_turns[i][ROW]][all_turns[i][COL]] = 'X';
            
        else
            table[all_turns[i][ROW]][all_turns[i][COL]] = 'O';
    }
}

// Getting coordinates, validate them and insert.
bool check_coordinates(int len, char table[len][len], int all_turns[][2], int turn, int row, int col)
{   
    if(!is_free(len, table, row, col))
        return false;

    all_turns[turn - 1][ROW] = row;
    all_turns[turn - 1][COL] = col;
    
    return true;
}

// The whole flow of a player's turn
int decision_tree(int len, char table[len][len], int all_turns[][2], int turn)
{
    int row;

    printf("\nEnter the TicTacToe coordinates (1-10):\n");
    bool valid = false;
    do
    {
        scanf("%d", &row);

        // Regular turn
        if(row >= 1 && row <= len)
        {
            int col;

            scanf("%d", &col);
            if(row >= 1 && row <= len)
                if(check_coordinates(len, table, all_turns, turn, row - 1, col - 1))
                    return turn;
            else
                printf("\nBad turn.");
        }

        // Return
        else if(row + turn >= 0 && row < 0)
            return turn + row; 


        // Bad input
        printf("\nBad turn.");
            
    }
    while(!valid);
     

}

int main()
{
    const int len = get_current_table_length();
    const int max_turn_num = len * len;
    int all_turns[max_turn_num][2];
    char table[len][len];
    format_table(len, table);

	for(int turn = 1; turn <= max_turn_num; turn++)
    {
        printf("\nPlayer %d:\n", (turn % 2 == 0)? 2:1);
        print_table(len, table);
        turn = decision_tree(len, table, all_turns, turn);
        
        printf("\n%d %d\n", all_turns[i][ROW], all_turns[i][COL]);
         // Output: True values

        update_table(len, table, all_turns, turn);
        if(is_win(len, table))
        {
            printf("\nPlayer %d won!\n", (turn % 2 + 1));
            return 1;
        }
    }
    printf("\nTie!\n");
	return 0;
}