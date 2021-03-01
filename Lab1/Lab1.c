#include<stdio.h>
#include<stdlib.h>

char** Create_2D_Array(int rows,int columns)
{
  char **arr = NULL;
  arr = (char**)malloc(sizeof(char*)*rows);
  for (int i = 0; i < rows; i++)
    arr[i] = (char*)malloc(sizeof(char)*columns);
  return arr;
}

void Fill_2D_Array(char **arr, int rows, int columns, char defualt)
{
  if (defualt == ' ')
    for (int i = 0; i < rows; ++i)
      for (int j = 0; j < columns; ++j)
        scanf(" %c", &arr[i][j]);
  else
    for (int i = 0; i < rows; ++i)
      for (int j = 0; j < columns; ++j)
        arr[i][j] = defualt;
}

void Print_2D_Array(char **arr, int rows, int columns)
{
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < columns; ++j)
      printf("%c", arr[i][j]);
    printf("\n");
  }
}

void Delete_2D_Array(char **arr, int rows)
{
  for (int i = 0; i < rows; i++)
    free(arr[i]);
  free(arr);
  arr = NULL;
}

void Scan_horizantallyLTR(char **board, char **board_to_be_printed, char*target, int rows,int columns)
{
  for(int i = 0; i < rows; ++i)
    for(int j = 0; j < columns; ++j)
    {
      int array_column_index = j;
      int target_index = 0;
      if(target[target_index] == board[i][j])
      {
        while(1)
        {
          if(target[target_index] == '\0')
          {
            int num = 0;
            while(target[num] != '\0')
            {
              board_to_be_printed[i][j+num] = target[num];
              ++num;
            }
            break;
          }
          else if(array_column_index == columns)
            break;
          else if(target[target_index] != board[i][array_column_index])
              break;
            ++target_index;
            ++array_column_index;
        }
      }
    }
}

void Scan_horizantallyRTL(char **board, char **board_to_be_printed, char*target, int rows,int columns)
{
  for(int i = 0; i < rows; ++i)
    for(int j = 0; j < columns; ++j)
    {
      int array_column_index = j;
      int target_index = 0;
      if(target[target_index] == board[i][j])
      {
        while(1)
        {
          if(target[target_index] == '\0')
          {
            int num = 0;
            while(target[num] != '\0')
            {
              board_to_be_printed[i][j-num] = target[num];
              ++num;
            }
            break;
          }
          else if(array_column_index < 0)
            break;
          else if(target[target_index] != board[i][array_column_index])
              break;
            ++target_index;
            --array_column_index;
        }
      }
    }
}

void Scan_verticallyTTB(char **board, char **board_to_be_printed, char*target, int rows,int columns)
{
  for(int j = 0; j < columns; ++j)
    for(int i = 0; i < rows; ++i)
    {
      int array_row_index = i;
      int target_index = 0;
      if(target[target_index] == board[i][j])
      {
        while(1)
        {
          if(target[target_index] == '\0')
          {
            int num = 0;
            while(target[num] != '\0')
            {
              board_to_be_printed[i+num][j] = target[num];
              ++num;
            }
            break;
          }
        else if(array_row_index == rows)
          break;
        else if(target[target_index] != board[array_row_index][j])
            break;
          ++target_index;
          ++array_row_index;
        }
      }
    }
}

void Scan_verticallyBTT(char **board, char **board_to_be_printed, char*target, int rows,int columns)
{
  for(int j = 0; j < columns; ++j)
    for(int i = 0; i < rows; ++i)
    {
      int array_row_index = i;
      int target_index = 0;
      if(target[target_index] == board[i][j])
      {
        while(1)
        {
          if(target[target_index] == '\0')
          {
            int num = 0;
            while(target[num] != '\0')
            {
              board_to_be_printed[i-num][j] = target[num];
              ++num;
            }
            break;
          }
          else if(array_row_index < 0)
            break;
          else if(target[target_index] != board[array_row_index][j])
            break;
          ++target_index;
          --array_row_index;
        }
      }
    }
}

void Scan_diagonallyTLTBR(char **board, char **board_to_be_printed, char*target, int rows,int columns)
{
  for(int i = 0; i < rows; ++i)
    for(int j = 0; j < columns; ++j)
    {
      int array_row_index = i;
      int array_column_index = j;
      int target_index = 0;
      if(target[target_index] == board[i][j])
      {
        while(1)
        {
          if(target[target_index] == '\0')
          {
            int num = 0;
            while(target[num] != '\0')
            {
              board_to_be_printed[i+num][j+num] = target[num];
              ++num;
            }
            break;
          }
          else if(array_row_index == rows || array_column_index == columns)
            break;
          else if(target[target_index] != board[array_row_index][array_column_index])
            break;
          ++target_index;
          ++array_row_index;
          ++array_column_index;
        }
      }

    }
}

void Scan_diagonallyTRTBL(char **board, char **board_to_be_printed, char*target, int rows,int columns)
{
  for(int i = 0; i < rows; ++i)
    for(int j = 0; j < columns; ++j)
    {
      int array_row_index = i;
      int array_column_index = j;
      int target_index = 0;
      if(target[target_index] == board[i][j])
      {
        while(1)
        {
          if(target[target_index] == '\0')
          {
            int num = 0;
            while(target[num] != '\0')
            {
              board_to_be_printed[i+num][j-num] = target[num];
              ++num;
            }
            break;
          }
          else if(array_row_index == rows || array_column_index < 0)
            break;
          else if(target[target_index] != board[array_row_index][array_column_index])
            break;
          ++target_index;
          ++array_row_index;
          --array_column_index;
        }
      }
    }
}

void Scan_diagonallyBRTTL(char **board, char **board_to_be_printed, char*target, int rows,int columns)
{
  for(int i = 0; i < rows; ++i)
    for(int j = 0; j < columns; ++j)
    {
      int array_row_index = i;
      int array_column_index = j;
      int target_index = 0;
      if(target[target_index] == board[i][j])
      {
        while(1)
        {
          if(target[target_index] == '\0')
          {
            int num = 0;
            while(target[num] != '\0')
            {
              board_to_be_printed[i-num][j-num] = target[num];
              ++num;
            }
            break;
          }
          else if(array_row_index < 0 || array_column_index < 0)
            break;
          else if(target[target_index] != board[array_row_index][array_column_index])
            break;
          ++target_index;
          --array_row_index;
          --array_column_index;
        }
      }
    }
}

void Scan_diagonallyBLTTR(char **board, char **board_to_be_printed, char*target, int rows,int columns)
{
  for(int i = 0; i < rows; ++i)
    for(int j = 0; j < columns; ++j)
    {
      int array_row_index = i;
      int array_column_index = j;
      int target_index = 0;
      if(target[target_index] == board[i][j])
      {
        while(1)
        {
          if(target[target_index] == '\0')
          {
            int num = 0;
            while(target[num] != '\0')
            {
              board_to_be_printed[i-num][j+num] = target[num];
              ++num;
            }
            break;
          }
          else if(array_row_index < 0 || array_column_index == columns)
            break;
          else if(target[target_index] != board[array_row_index][array_column_index])
            break;
          ++target_index;
          --array_row_index;
          ++array_column_index;
        }
      }
    }
}

int main()
{
  int rows = 15, columns = 15 ,char_in_a_row = 15;
  char **board = Create_2D_Array(rows, columns);
  char **board_to_be_printed = Create_2D_Array(rows,columns);
  char *word = (char*)malloc(sizeof(char)*char_in_a_row);
  Fill_2D_Array(board, rows, columns, ' ');
  Fill_2D_Array(board_to_be_printed, rows, columns, '*');
  scanf("%s", word);
  Scan_horizantallyLTR(board, board_to_be_printed, word, rows, columns);
  Scan_horizantallyRTL(board, board_to_be_printed, word, rows, columns);
  Scan_verticallyTTB(board, board_to_be_printed, word, rows, columns);
  Scan_verticallyBTT(board, board_to_be_printed, word, rows, columns);
  Scan_diagonallyTLTBR(board, board_to_be_printed, word, rows, columns);
  Scan_diagonallyTRTBL(board, board_to_be_printed, word, rows, columns);
  Scan_diagonallyBRTTL(board, board_to_be_printed, word, rows, columns);
  Scan_diagonallyBLTTR(board, board_to_be_printed, word, rows, columns);
  Print_2D_Array(board_to_be_printed,rows,columns);
  Delete_2D_Array(board, rows);
  Delete_2D_Array(board_to_be_printed, rows);
  return 0;
}
