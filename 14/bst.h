#ifndef BST_NODE_H_
#define BST_NODE_H_

typedef struct bst_node *bst;

extern bst  bst_delete(bst b, char *str);
extern bst  bst_free(bst b);
extern void bst_inorder(bst b, void f(char *str));
extern bst  bst_insert(bst b, char *str);
extern bst  bst_new();
extern void bst_preorder(bst b, void f(char *str));
extern int  bst_search(bst b, char *str);

#endif
