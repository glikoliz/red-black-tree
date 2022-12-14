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
    if (tree == NULL)
        return;
    space += 10;
    print2DUtil(tree->right, space);
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d/%d\n", tree->key, tree->color);
    print2DUtil(tree->left, space);
}
struct rbtree *rbtree_add_fixup(struct rbtree *root, struct rbtree *z)
{
    while (z != root && z->parent != NULL && z->parent->color == RED && z->parent->parent != NULL) 
    {
        if (z->parent == z->parent->parent->left) //?????????????????????? ???????????? ??????????????????
        {
            struct rbtree* y = z->parent->parent->right; //????????
            if (y != NULL && y->color == RED)            //???????????? 1
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else if (y == NULL || y->color == BLACK) {
                if (z == z->parent->right) //???????????? 2
                {
                    z = z->parent;
                    left_rotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                root = right_rotate(z->parent->parent); //???????????? 3
            }
        } else if (z->parent == z->parent->parent->right) {
            struct rbtree* y = z->parent->parent->left; //????????
            if (y != NULL && y->color == RED)           //???????????? 1
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else if (y == NULL || y->color == BLACK) {
                if (z == z->parent->left) //???????????? 2
                {
                    z = z->parent;
                    right_rotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                root = left_rotate(z->parent->parent); //???????????? 3
            }
        }
    }
  root->color=BLACK;
  return root;
}
struct rbtree *rbtree_lookup(struct rbtree *tree, int key)
{
  while(tree!=NULL)
  {
    if(key==tree->key)      
      return tree;
    else if(key<tree->key)
      tree=tree->left;
    else
      tree=tree->right;
  }
  return tree;
}
struct rbtree *rbtree_delete(struct rbtree *tree, int key)
{
  struct rbtree* z = rbtree_lookup(root, key);
  struct rbtree* x = NULL;
  struct rbtree* y=z;
  int y_orig_color=y->color;
  if(z->left==NULL)
  {
    x=z->right;
    rbtree_transplantant(root, z, z->right);
  }
  else if(z->right == NULL)
  {
    x=z->left;
    rbtree_transplantant(root, z, z->left);
  }
  else // ???????? ?? ???????????? ?????? ??????????????
  {
    y=rbtree_min(z->right);
    y_orig_color=y->color;
    x=y->right;
    if(y->parent==z)
    {
      x->parent=y;
    }
    else
    {
      rbtree_transplantant(root, y, y->right);
      y->right=z->right;
      y->right->parent = y;
    }
    rbtree_transplantant(root, z, y);
    y->left=z->left;
    z->left->parent=y;
    y->color=z->color;
  }
  if(y_orig_color==BLACK)
  {
    rbtree_delete_fixup(tree, x);
  }
}
struct rbtree *rbtree_transplantant(struct rbtree *tree, struct rbtree *u, struct rbtree *v)
{
  if(u->parent==NULL)
  {
    root=v;
  }
  else if(u->parent->left==u)
  {
    u->parent->left=v;
  }
  else
  {
    u->parent->right=v;
    v->parent=u->parent;
  }
}
struct rbtree *rbtree_min(struct rbtree *tree)
{
  while(tree->left!=NULL)
    tree=tree->left;
  return tree;
}
struct rbtree *rbtree_max(struct rbtree *tree)
{
  while(tree->right!=NULL)
    tree=tree->right;
  return tree;
}
struct rbtree *rbtree_delete_fixup(struct rbtree *tree, struct rbtree *x)
{
  struct rbtree *w=NULL;
  if(x!=NULL)
  {
  while(x!=root && x->color==BLACK)
  {
    if(x==x->parent->left)
    {
      w=x->parent->right;
      if(w->color==RED)
      {
        w->color=BLACK;
        x->parent->color=RED;
        left_rotate(x->parent);
        w=x->parent->right;
      }//case 1
      if(w->left->color==BLACK && w->right->color==BLACK)
      {
        w->color=RED;
        x=x->parent;
      }//case 2
      else if(w->right->color==BLACK)
      {
        w->left->color=BLACK;
        w->color=RED;
        right_rotate(w);
        w=x->parent->right;
      }//case 3
      w->color=x->parent->color;
      x->parent->color=BLACK;
      w->right->color=BLACK;
      left_rotate(x->parent);
      x=root;//case 4
    }
    else
    {
      w=x->parent->left;
      if(w->color==RED)
      {
        w->color=BLACK;
        x->parent->color=RED;
        right_rotate(x->parent);
        w=x->parent->left;
      }//case 1
      if(w->right->color==BLACK && w->left->color==BLACK)
      {
        w->color=RED;
        x=x->parent;
      }//case 2
      else if(w->left->color==BLACK)
      {
        w->right->color=BLACK;
        w->color=RED;
        left_rotate(w);
        w=x->parent->left;
      }//case 3
      w->color=x->parent->color;
      x->parent->color=BLACK;
      w->left->color=BLACK;
      right_rotate(x->parent);
      x=root;//case 4
    }
  }
  }
}
void rbtree_free(struct rbtree *tree);
void rbtree_print_dfs(struct rbtree *tree, int level)
{
  if(level==0)
  {
    printf("%d ", tree->key);
  }
  else
  {
    if(tree->left!=NULL)
    {
      rbtree_print_dfs(tree->left, level-1);
    }
    if(tree->right!=NULL)
    {
      rbtree_print_dfs(tree->right, level-1);
    }
  }
}