#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
struct rbtree *rbtree_add_fixup(struct rbtree *root, struct rbtree *z);
void print2DUtil(struct rbtree* tree, int space);
enum node_colors { RED, BLACK };
struct rbtree{
  int key; //номер
  char* value; //значение
  int color;  //цвет
  struct rbtree *parent, *left, *right;
};
struct rbtree *root = NULL; //основное дерево
struct rbtree *Create(int key, char* value)
{
  struct rbtree *newnode;
  newnode=(struct rbtree*) malloc(sizeof(struct rbtree));
  newnode->key=key;
  newnode->value=value;
  newnode->color=BLACK;
  newnode->parent=NULL;
  newnode->left=newnode->right=NULL;
  return newnode;
}
struct rbtree *left_rotate(struct rbtree *x)
{
  struct rbtree *y=x->right;
  x->right=y->left;
  if(y->left!=NULL)
    y->left->parent=x;
  y->parent=x->parent;
  if(x->parent==NULL)
    root=y;
  else if(x==x->parent->left)
    x->parent->left=y;
  else
    x->parent->right=y;
  y->left=x;
  x->parent=y;
  return root;
}
struct rbtree *right_rotate(struct rbtree *x)
{
  struct rbtree *y=x->left;
  x->left=y->right;
  if(y->right!=NULL)
    y->right->parent=x;
  y->parent=x->parent;
  if(x->parent==NULL)
    root=y;
  else if(x==x->parent->left)
    x->parent->left=y;
  else
    x->parent->right=y;
  y->right=x;
  x->parent=y;
  return root;
}
struct rbtree *rbtree_add(struct rbtree *root, int key, char *value)
{
  struct rbtree *tree=root;
  struct rbtree *tmp;
  while(tree!=NULL)
  {
    if(key<tree->key)
    {
      // Create(key, value);
      tmp=tree;
      tree=tree->left;
    }
    else if(key>tree->key)
    {
      tmp=tree;
      tree=tree->right;
    }
    else
    {
      return NULL;
    }
  }
  tree=(struct rbtree*) malloc(sizeof(struct rbtree));
  // tree->parent=root;
  tree->parent=tmp;
  struct rbtree *node=Create(key, value);
  if(root==NULL)
  {
    root=node;
  }
  else{
    node->parent=tmp;
    if(key<tree->parent->key)
    {
      tree->parent->left=node;
    }
    else
    {
      tree->parent->right=node;
    }
  }
  node->color=RED;
  
  return rbtree_add_fixup(root, node);
}
void print2DUtil(struct rbtree* tree, int space)
{
    // Base case
    if (tree == NULL)
        return;
 
    // Increase distance between levels
    space += 10;
 
    // Process right child first
    print2DUtil(tree->right, space);
 
    // Print current node after space
    // count
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d/%d\n", tree->key, tree->color);
 
    // Process left child
    print2DUtil(tree->left, space);
}

struct rbtree *rbtree_add_fixup(struct rbtree *root, struct rbtree *z)
{
  while(z!=root && z->color==RED && z->parent!=NULL  && z->parent->parent!=NULL)
  {
    if(z->parent==z->parent->parent->left)//принадлежит левому поддереву
    {
      struct rbtree *y=z->parent->parent->right;//дядя
      if(y!=NULL && y->color==RED)//случай 1
      {
        z->parent->color=BLACK;
        y->color=BLACK;
        z->parent->parent->color=RED;
        z=z->parent->parent;
      }
      else if(y==NULL || y->color==BLACK)
      {
        if(z==z->parent->right)//случай 2
        {
          z=z->parent;
          left_rotate(z);
        }
        z->parent->color=BLACK;
        z->parent->parent->color=RED;
        root=right_rotate(z->parent->parent);//случай 3
      }
    }
    else if (z->parent==z->parent->parent->right)
    {
      struct rbtree *y=z->parent->parent->left;//дядя
      if(y!=NULL && y->color==RED)//случай 1
      {
        z->parent->color=BLACK;
        y->color=BLACK;
        z->parent->parent->color=RED;
        z=z->parent->parent;
      }
      else if(y==NULL || y->color==BLACK)
      {
        if(z==z->parent->left)//случай 2
        {
          z=z->parent;
          right_rotate(z);
        }
        z->parent->color=BLACK;
        z->parent->parent->color=RED;
        root=left_rotate(z->parent->parent);//случай 3
      }
      break;
    }
  }
  root->color=BLACK;
  return root;
}
struct rbtree *rbtree_lookup(struct rbtree *tree, int key)
{
  
}
struct rbtree *rbtree_delete(struct rbtree *tree, int key);
struct rbtree *rbtree_min(struct rbtree *tree);
struct rbtree *rbtree_max(struct rbtree *tree);
void rbtree_free(struct rbtree *tree);
void rbtree_print_dfs(struct rbtree *tree, int level);
void inorder(struct rbtree* tree)
{
    if (tree == NULL)
        return;
    inorder(tree->left);
    printf("%d ", tree->key);
    inorder(tree->right);
}
void ok()
{
  printf(",,,,,%d\n", root->key);
}
int main()
{
  // struct rbtree *temp;
  // temp=(struct rbtree*) malloc(sizeof(struct rbtree));
  // temp->key=5;
  // temp->left=NULL;
  // temp->right=NULL;
  // temp->parent=NULL;
  // temp->color=RED;
  // root=bst(root, temp);
  // printf("%d\n", root->key);
  // temp=(struct rbtree*) malloc(sizeof(struct rbtree));
  // temp->key=7;
  // temp->left=NULL;
  // temp->right=NULL;
  // temp->parent=NULL;
  // temp->color=RED;
  // printf("%d\n", root->key);
  // root=bst(root, temp);
  // for(int i=10;i>0;i--)
  // {
  //   root=rbtree_add(root, i, "ladno");
  // }
  root=rbtree_add(root, 7, "no");
  root=rbtree_add(root, 8, "da");
  root=rbtree_add(root, 5, "ok");
  root=rbtree_add(root, 1, "1");
  root=rbtree_add(root, 2, "2");
  root=rbtree_add(root, 3, "3");
  root=rbtree_add(root, 10, "3");
  root=rbtree_add(root, 9, "3");

  // root=rbtree_add(root, 6, "3");
  // root=rbtree_add(root, 9, "daa");

  // print2DUtil(root, 0);
  // right_rotate(root->left);
  print2DUtil(root, 0);
  //printf("%s\n", root->value);
  // Create(5);
}