#include <stdio.h>
#include <stdlib.h>
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
  newnode->color=RED;
  newnode->parent=NULL;
  newnode->left=newnode->right=NULL;
  return newnode;
}
struct rbtree* bst(struct rbtree* trav, struct rbtree* temp)
{
    // If the tree is empty,
    // return a new node
    if (trav == NULL)
        return temp;
 
    // Otherwise recur down the tree
    if (temp->key < trav->key)
    {
        trav->left = bst(trav->left, temp);
        trav->left->parent = trav;
    }
    else if (temp->key > trav->key)
    {
        trav->right = bst(trav->right, temp);
        trav->right->parent = trav;
    }
 
    // Return the (unchanged) node pointer
    return trav;
}
struct rbtree *rbtree_add(struct rbtree *root, int key, char *value)
{
  struct rbtree *tree=root;
  struct rbtree *p;
  while(tree!=NULL)
  {
    if(key<tree->key)
    {
      // Create(key, value);
      p=tree;
      tree=tree->left;
    }
    else if(key>tree->key)
    {
      tree=tree->right;
    }
    else
    {
      return NULL;
    }
  }
  tree=(struct rbtree*) malloc(sizeof(struct rbtree));
  // tree->parent=root;
  tree->parent=p;
  struct rbtree *node=Create(key, value);
  if(root==NULL)
  {
    root=node;
  }
  else{
    node->parent=p;
    if(key<tree->parent->key)
    {
      tree->parent->left=node;
    }
    else
    {
      tree->parent->right=node;
    }
  }
  return root;
}
struct rbtree *rbtree_lookup(struct rbtree *tree, int key);
struct rbtree *rbtree_delete(struct rbtree *tree, int key);
struct rbtree *rbtree_min(struct rbtree *tree);
struct rbtree *rbtree_max(struct rbtree *tree);
void rbtree_free(struct rbtree *tree);
void rbtree_print_dfs(struct rbtree *tree, int level);

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
  root=rbtree_add(root, 5, "ok");
  root=rbtree_add(root, 8, "da");
  root=rbtree_add(root, 1, "1");
  root=rbtree_add(root, 2, "2");
  root=rbtree_add(root, 3, "3");


  printf("%s\n", root->value);
  // Create(5);
}