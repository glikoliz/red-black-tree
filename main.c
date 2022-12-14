#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "rbtree.h"
#include "rbtree.c"

int main()
{
  // root=rbtree_add(root, 16, "no");
  // root=rbtree_add(root, 3, "da");
  // root=rbtree_add(root, 21, "ok");
  // root=rbtree_add(root, 2, "1");
  // root=rbtree_add(root, 7, "2");
  // root=rbtree_add(root, 24, "3");
  // root=rbtree_add(root, 5, "3");
  // root=rbtree_add(root, 9, "3");
  // root=rbtree_add(root, 4, "1");
  for(int i=0;i<=50000;i++)
  {
    root=rbtree_add(root, i, "a");
  }
  // left_rotate(root->right);
  rbtree_print_dfs(root, 3);
  // print2DUtil(root, 0);
}