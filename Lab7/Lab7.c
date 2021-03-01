#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node
{
  struct tree_node *left;
  struct tree_node *right;
  int balance_factor;
  int data;
} Tree;

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

int Balance_Value(Tree *node)
{
  int height_left = -1;
  int height_right = -1;
  if(node -> right != NULL)
    height_right = height_of_tree(node -> right);
  else
    height_right = 0;
  if(node -> left != NULL)
    height_left = height_of_tree(node -> left);
  else
    height_left = 0;
  return height_left - height_right;
}

Tree* new_node(int data)
{
  Tree *new_node = (Tree*)malloc(sizeof(Tree));
  new_node -> data = data;
  new_node -> left = NULL;
  new_node -> right = NULL;
  new_node -> balance_factor = 0;
  return new_node;
}

void LLR(Tree **node)
{
  Tree *temp = *node;
  Tree *temp2 = (*node) -> left -> right;
  *node = temp -> left;
  (*node) -> right = temp;
  (*node) -> right -> left = temp2;
}

void LRR(Tree **node)
{
  Tree *temp = (*node) -> left;
  Tree *temp2 = (*node) -> left -> right -> left;
  (*node) -> left = (*node) -> left -> right;
  (*node) -> left -> left = temp;
  temp -> right = temp2;
  LLR(node);
}

void RRR(Tree **node)
{
  Tree *temp = *node;
  Tree *temp2 = (*node) -> right -> left;
  *node = temp -> right;
  (*node) -> left = temp;
  (*node) -> left -> right = temp2;
}

void RLR(Tree **node)
{
  Tree *temp = (*node) -> right;
  Tree *temp2 = (*node) -> right -> left -> right;
  (*node) -> right = (*node) -> right -> left;
  (*node) -> right -> right = temp;
  temp -> left = temp2;
  RRR(node);
}

void Initialize_Balance_Factors(Tree *root)
{
  if(root != NULL)
    root -> balance_factor = Balance_Value(root);
  if(root -> left != NULL)
    root -> left -> balance_factor = Balance_Value(root -> left);
  if(root -> right != NULL)
    root -> right -> balance_factor = Balance_Value(root -> right);
  if(root -> left -> left != NULL)
    root -> left -> left -> balance_factor = Balance_Value(root -> left -> left);
  if(root -> left -> right != NULL)
    root -> left -> right -> balance_factor = Balance_Value(root -> left -> right);
  if(root -> right -> left != NULL)
    root -> right -> left -> balance_factor = Balance_Value(root -> right -> left);
  if(root -> right -> right != NULL)
    root -> right -> right -> balance_factor = Balance_Value(root -> right -> right);
}

void Balance(Tree **root)
{
  int bf = 0;
  int bf_left = 0;
  int bf_right = 0;
  (*root) -> balance_factor = Balance_Value(*root);
  bf = (*root) -> balance_factor;
  if(bf > 1 || bf < -1)
  {
    if((*root) -> left != NULL)
      bf_left = Balance_Value((*root) -> left);
    if((*root) -> right != NULL)
      bf_right = Balance_Value((*root) -> right);
    if(bf == 2 && bf_left == 1)
      LLR(root);
    else if(bf == 2 && bf_left == -1)
      LRR(root);
    else if(bf == -2 && bf_right == -1)
      RRR(root);
    else if(bf == -2 && bf_right == 1)
      RLR(root);
    Initialize_Balance_Factors(*root);
  }
}

void insert_leaf(Tree **root, int data)
{
  if(*root == NULL)
    *root = new_node(data);
  else if((*root) -> data < data)
    insert_leaf(&((*root) -> right), data);
  else if((*root) -> data > data)
    insert_leaf(&((*root) -> left), data);
  Balance(root);
}

void DFS_Print(Tree *root)
{
  if(root -> left != NULL)
    DFS_Print(root -> left);
  printf("%d\n", root -> data);
  if(root -> right != NULL)
    DFS_Print(root -> right);
}


void Print_Level(Tree *root, int current_level, int level)
{
  if(current_level == level)
  {
    if(root -> left != NULL)
      printf("%d (%d L) (%d B) ", root -> left -> data, root -> data,
                                  root -> left -> balance_factor);
    if(root -> right != NULL)
      printf("%d (%d R) (%d B) ", root -> right -> data, root -> data,
                                  root -> right -> balance_factor);
  }
  else
  {
    if(root -> left != NULL)
      Print_Level(root->left, current_level+1, level);
    if(root -> right != NULL)
      Print_Level(root->right, current_level+1, level);
  }
}

void MAP_Print(Tree *root)
{
  if(root != NULL)
  {
    printf("%d (%d B)\n", root -> data, root -> balance_factor);
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
  int temp = 0;
  Tree *head = NULL;
  scanf("%d", &temp);
  while (temp != -1)
  {
    insert_leaf(&head, temp);
    scanf("%d", &temp);
  }
  DFS_Print(head);
  printf("\n");
  MAP_Print(head);
  return 0;
}
