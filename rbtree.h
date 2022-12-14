struct rbtree *rbtree_min(struct rbtree *tree);
struct rbtree *rbtree_max(struct rbtree *tree);
void rbtree_free(struct rbtree *tree);
void rbtree_print_dfs(struct rbtree *tree, int level);
struct rbtree *rbtree_delete(struct rbtree *tree, int key);
struct rbtree *rbtree_lookup(struct rbtree *tree, int key);
struct rbtree *rbtree_add_fixup(struct rbtree *root, struct rbtree *z);
void print2DUtil(struct rbtree* tree, int space);
struct rbtree *rbtree_add(struct rbtree *root, int key, char *value);
struct rbtree *right_rotate(struct rbtree *x);
struct rbtree *left_rotate(struct rbtree *x);
struct rbtree *Create(int key, char* value);
enum node_colors { RED, BLACK };
struct rbtree{
  int key; //номер
  char* value; //значение
  int color;  //цвет
  struct rbtree *parent, *left, *right;
};
struct rbtree *root = NULL; //основное дерево;
struct rbtree *rbtree_transplantant(struct rbtree *root, struct rbtree *u, struct rbtree *v);
struct rbtree *rbtree_delete_fixup(struct rbtree *root, struct rbtree *x);