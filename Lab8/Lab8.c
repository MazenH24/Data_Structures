#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node
{
  struct tree_node *left;
  struct tree_node *right;
  struct tree_node *parent;
  int balance_factor;
  char color;
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

Tree* new_node(int data, Tree* parent)
{
  Tree *new_node = (Tree*)malloc(sizeof(Tree));
  new_node -> data = data;
  new_node -> left = NULL;
  new_node -> right = NULL;
  new_node -> parent = parent;
  new_node -> color = 'R';
  return new_node;
}

void LLR(Tree **node)
{
  Tree *temp = *node;
  Tree *temp2 = (*node) -> left -> right;
  *node = temp -> left;
  (*node) -> parent = temp -> parent;
  (*node) -> right = temp;
  temp -> parent = *node;
  (*node) -> right -> left = temp2;
  if(temp2 != NULL)
    temp2 -> parent = temp;
  (*node) -> color = 'B';
  (*node) -> left -> color = 'R';
  (*node) -> right -> color = 'R';
}

void LRR(Tree **node)
{
  Tree *temp = (*node) -> left;
  Tree *temp2 = (*node) -> left -> right -> left;
  (*node) -> left = (*node) -> left -> right;
  if((*node) -> left -> right != NULL)
    (*node) -> left -> right -> parent = *node;
  (*node) -> left -> left = temp;
  temp -> parent = (*node) -> left;
  temp -> right = temp2;
  if(temp2 != NULL)
    temp2 -> parent = temp;
  LLR(node);
}

void RRR(Tree **node)
{
  Tree *temp = *node;
  Tree *temp2 = (*node) -> right -> left;
  *node = temp -> right;
  (*node) -> parent = temp -> parent;
  (*node) -> left = temp;
  temp -> parent = *node;
  (*node) -> left -> right = temp2;
  if(temp2 != NULL)
    temp2 -> parent = temp;
  (*node) -> color = 'B';
  (*node) -> left -> color = 'R';
  (*node) -> right -> color = 'R';
}

void RLR(Tree **node)
{
  Tree *temp = (*node) -> right;
  Tree *temp2 = (*node) -> right -> left -> right;
  (*node) -> right = (*node) -> right -> left;
  if((*node) -> right -> left != NULL)
    (*node) -> right -> left -> parent = *node;
  (*node) -> right -> right = temp;
  temp -> parent = (*node) -> right;
  temp -> left = temp2;
  if(temp2 != NULL)
    temp2 -> parent = temp;
  RRR(node);
}

void Balance(Tree **node)
{
  if(*node != NULL)
  {
    Tree *p = (*node) -> parent;
    if(p == NULL)
      (*node) -> color = 'B';
    if((*node) -> left != NULL && (*node) -> left -> color == 'R' &&
      (*node) -> right != NULL && (*node) -> right -> color == 'R' &&
      (*node) -> right -> right != NULL && (*node) -> right -> right -> color == 'R' )
    {
      (*node) -> color = 'R';
      (*node) -> left -> color = 'B';
      (*node) -> right -> color = 'B';
    }
    if((*node) -> right != NULL && (*node) -> right -> color == 'R' &&
      (*node) -> left != NULL && (*node) -> left -> color == 'R' &&
      (*node) -> left -> left != NULL && (*node) -> left -> left -> color == 'R')
    {
      (*node) -> color = 'R';
      (*node) -> right -> color = 'B';
      (*node) -> left -> color = 'B';
    }

    if((*node) -> right != NULL && (*node) -> right -> color == 'R' &&
      (*node) -> left != NULL && (*node) -> left -> color == 'R' &&
      (*node) -> left -> right != NULL && (*node) -> left -> right -> color == 'R')
    {
      (*node) -> color = 'R';
      (*node) -> right -> color = 'B';
      (*node) -> left -> color = 'B';
    }

    if((*node) -> left != NULL && (*node) -> left -> color == 'R' &&
      (*node) -> right != NULL && (*node) -> right -> color == 'R' &&
      (*node) -> right -> left != NULL && (*node) -> right -> left -> color == 'R' )
    {
      (*node) -> color = 'R';
      (*node) -> left -> color = 'B';
      (*node) -> right -> color = 'B';
    }
    if(((*node) -> left == NULL || ((*node) -> left != NULL &&
            (*node) -> left -> color =='B')) &&
            (*node)  -> right != NULL &&
            (*node)  -> right -> color == 'R' &&
            (*node) -> right -> right != NULL &&
            (*node) -> right -> right -> color == 'R')
            RRR(node);
    if(((*node) -> right == NULL || ((*node) -> right != NULL &&
            (*node) -> right -> color =='B')) &&
            (*node)  -> left != NULL &&
            (*node)  -> left -> color == 'R' &&
            (*node) -> left -> left != NULL &&
            (*node) -> left -> left -> color == 'R')
            LLR(node);
    if(((*node) -> left == NULL || ((*node) -> left != NULL &&
            (*node) -> left -> color =='B')) &&
            (*node)  -> right != NULL &&
            (*node)  -> right -> color == 'R' &&
            (*node) -> right -> left != NULL &&
            (*node) -> right -> left -> color == 'R')
            RLR(node);

    if(((*node) -> right == NULL || ((*node) -> right != NULL &&
            (*node) -> right -> color =='B')) &&
            (*node)  -> left != NULL &&
            (*node)  -> left -> color == 'R' &&
            (*node) -> left -> right != NULL &&
            (*node) -> left -> right -> color == 'R')
            LRR(node);


  }
}
void insert_leaf(Tree **root, Tree *parent, int data)
{
  if(*root == NULL)
    *root = new_node(data, parent);
  else if((*root) -> data < data)
    insert_leaf(&((*root) -> right), *root, data);
  else if((*root) -> data > data)
    insert_leaf(&((*root) -> left), *root, data);
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
      printf("%d %c (%d L) ", root -> left -> data, root -> left -> color, root -> data);
    if(root -> right != NULL)
      printf("%d %c (%d R) ", root -> right -> data, root -> right -> color, root -> data);
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
    printf("%d %c\n", root -> data, root -> color);
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
    insert_leaf(&head, NULL, temp);
    scanf("%d", &temp);
  }
  DFS_Print(head);
  printf("\n");
  MAP_Print(head);
  return 0;
}
