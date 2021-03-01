#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

void MergeSort(int*, int, int);
void Merge(int* , int, int ,int);
void Brute_Force_Sort(int*, int);
void Reverse_array(int*, int);
char **Create_2D_Array(int, int);
void Fill_2D_Array(char **, int, int, char);
void Fill_2D_Using_indexs(char**, int, int);
void Print_2D_Array(char**, int, int);
void Delete_2D_Array(char**, int);
int recursion_traverse_through_astriks(char**, int, int, int, int);
void Find_Blobs(char**, int, int);

int main()
{
  int rows = 0;
  int columns = 0;
  scanf("%d%d", &rows, &columns);
  char **board = Create_2D_Array(rows, columns);
  Fill_2D_Array(board, rows, columns, ' ');
  Fill_2D_Using_indexs(board, rows, columns);
  //Print_2D_Array(board, rows, columns);
  Find_Blobs(board, rows, columns);
  Delete_2D_Array(board, rows);
  return 0;
}

void Merge(int* arr, int left, int middle, int right)
{
  int len_arr_left = middle - left +1;
  int len_arr_right = right - middle;

  int left_arr[len_arr_left], right_arr[len_arr_right];

  for(int i = 0; i < len_arr_left; ++i)
    left_arr[i] = arr[left+i];
  for(int j = 0; j < len_arr_right; ++j)
    right_arr[j] = arr[middle + 1 + j];

  int i = 0;
  int j = 0;
  int k = left;

  while(i < len_arr_left && j < len_arr_right)
  {
    if(left_arr[i] <= right_arr[j])
    {
      arr[k] = left_arr[i];
      ++i;
    }
    else
    {
      arr[k] = right_arr[j];
      ++j;
    }
    ++k;
  }

  while(i < len_arr_left)
  {
    arr[k] = left_arr[i];
    ++i;
    ++k;
  }

  while(j < len_arr_right)
  {
    arr[k] = right_arr[j];
    ++j;
    ++k;
  }
}

void MergeSort(int* arr, int left, int right)
{
  if(left < right)
  {
    int middle = left + (right - left) / 2;

    MergeSort(arr, left, middle);
    MergeSort(arr, middle+1, right);

    Merge(arr, left, middle, right);
  }
}

void Brute_Force_Sort(int *arr, int size)
{
  for(int i = 0; i < size; ++i)
    for(int j = 0; j < size; ++j)
      if(arr[i] >= arr[j])
      {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
}

void Reverse_array(int* arr, int size)
{
  for(int i = 0, j = size -1; i < j; ++i, --j)
  {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }
}

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
  if (defualt == '\0')
    for (int i = 0; i < rows; ++i)
      for (int j = 0; j < columns; ++j)
        scanf(" %c", &arr[i][j]);
  else
    for (int i = 0; i < rows; ++i)
      for (int j = 0; j < columns; ++j)
        arr[i][j] = defualt;
}

void Fill_2D_Using_indexs(char **arr, int rows, int columns)
{
  int temp_row = 0;
  int temp_column = 0;
  while(1)
  {
    scanf("%d%d", &temp_row, &temp_column);
    assert(temp_row < rows || temp_column < columns);  //assert.h is being used in this line for range checking
    if (temp_row == -1)
      break;
    arr[temp_row][temp_column] = '*';
  }
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

int recursion_traverse_through_astriks(char** arr, int rows, int columns, int row_index, int column_index)
{
  int astriks = 1;
  arr[row_index][column_index] = ' ';
  if(row_index + 1 != rows && arr[row_index + 1][column_index] == '*')
    astriks += recursion_traverse_through_astriks(arr, rows, columns, row_index+1, column_index);

  if(row_index - 1 >= 0 && arr[row_index - 1][column_index] == '*')
      astriks += recursion_traverse_through_astriks(arr, rows, columns, row_index-1, column_index);

  if(column_index + 1 != columns && arr[row_index][column_index + 1] == '*')
      astriks += recursion_traverse_through_astriks(arr, rows, columns, row_index, column_index+1);

  if(column_index - 1 >= 0 && arr[row_index][column_index - 1] == '*')
      astriks += recursion_traverse_through_astriks(arr, rows, columns, row_index, column_index-1);

  if(row_index + 1 != rows && column_index + 1 != columns && arr[row_index + 1][column_index + 1] == '*')
      astriks += recursion_traverse_through_astriks(arr, rows, columns, row_index+1, column_index+1);

  if(row_index - 1 >= 0 && column_index - 1 >= 0 && arr[row_index - 1][column_index - 1] == '*')
      astriks += recursion_traverse_through_astriks(arr, rows, columns, row_index-1, column_index-1);

  if(row_index + 1 != rows && column_index - 1 >= 0 && arr[row_index + 1][column_index - 1] == '*')
      astriks += recursion_traverse_through_astriks(arr, rows, columns, row_index+1, column_index-1);

  if(row_index - 1 >= 0 && column_index + 1 != columns && arr[row_index - 1][column_index + 1] == '*')
      astriks += recursion_traverse_through_astriks(arr, rows, columns, row_index-1, column_index+1);

  return astriks;
}

void Find_Blobs(char** arr, int rows, int columns)
{
  int num_of_bolbs = 0;
  int len_arr = rows*columns;
  int* num_of_astriks_in_a_bolb = (int*)calloc(len_arr, sizeof(int));
  int index = 0;
  for(int i = 0; i < rows; ++i)
    for(int j = 0; j < columns; ++j)
      if(arr[i][j] == '*')
      {
        num_of_astriks_in_a_bolb[index] = recursion_traverse_through_astriks(arr, rows, columns, i, j);
        ++num_of_bolbs;
        ++index;
      }
  MergeSort(num_of_astriks_in_a_bolb, 0, len_arr-1);
  Reverse_array(num_of_astriks_in_a_bolb, len_arr);
  Reverse_array(num_of_astriks_in_a_bolb, num_of_bolbs);
  printf("%d", num_of_bolbs);
  for(int i = 0; num_of_astriks_in_a_bolb[i] != 0; ++i)
    printf(" %d", num_of_astriks_in_a_bolb[i]);
  printf("\n");
  free(num_of_astriks_in_a_bolb);
}
