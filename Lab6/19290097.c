#include <stdio.h>
#include <stdlib.h>

typedef struct student_data
{
  int id;
  int grade;
} Student;

typedef struct tree_node
{
  Student data;
  struct tree_node *left;
  struct tree_node *right;
} Tree;

int pow_int(int base, int exponent)
{
  int result = base;
  for(int i = 1; i < exponent; ++i)
    result *= base;
  return result;
}
int max(int num1, int num2)
{
  if(num1 >= num2)
    return num1;
  return num2;
}
int height_of_tree(Tree *root)
{
  int left_hight = 0;
  int right_hight = 0;
  if(root -> left != NULL)
    left_hight += height_of_tree(root->left);
  if(root -> right != NULL)
    right_hight += height_of_tree(root->right);
  return max(left_hight, right_hight) + 1;
}

Tree* new_node(Student data)
{
  Tree *new_node = (Tree*)malloc(sizeof(Tree));
  new_node -> data = data;
  new_node -> left = NULL;
  new_node -> right = NULL;
  return new_node;
}

void insert_leaf(Tree **root, Student data)
{
  if(*root == NULL)
    *root = new_node(data);
  else if((*root) -> data.grade < data.grade)
    insert_leaf(&((*root) -> right), data);
  else if((*root) -> data.grade > data.grade)
    insert_leaf(&((*root) -> left), data);

}
void DFS_Print(Tree *root)
{
  if(root -> left != NULL)
    DFS_Print(root -> left);
  printf("%d %d\n", root -> data.id, root -> data.grade);
  if(root -> right != NULL)
    DFS_Print(root -> right);
}

void Print_Level(Tree *root, int current_level, int level)
{
  if(current_level == level)
  {
    if(root -> left != NULL)
      printf("%d %d (%d L) ", root -> left -> data.id, root -> left -> data.grade, root -> data.grade);
    if(root -> right != NULL)
      printf("%d %d (%d R) ", root -> right -> data.id, root -> right -> data.grade, root -> data.grade);
  }
  else
  {
    if(root -> left != NULL)
      Print_Level(root->left, current_level+1, level);
    if(root -> right != NULL)
      Print_Level(root->right, current_level+1, level);
  }
}

void MAP_Print(Tree *root, Student above)
{
  if(root != NULL)
  {
    printf("%d %d\n", root -> data.id, root -> data.grade);
    int num_of_levels = height_of_tree(root);
    for(int i = 0; i < num_of_levels - 1; ++i)
    {
      Print_Level(root, 0, i);
      printf("\n");
    }
  }
}

int main()
{
  Student temp = {0,0};
  Tree *head = NULL;
  scanf("%d", &temp.id);
  while (temp.id != -1)
  {
    scanf("%d", &temp.grade);
    insert_leaf(&head, temp);
    scanf("%d", &temp.id);
  }
  DFS_Print(head);
  printf("\n");
  temp.id = -1;
  temp.grade = -1;
  MAP_Print(head, temp);
  return 0;
}
