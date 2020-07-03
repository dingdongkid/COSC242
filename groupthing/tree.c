#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "mylib.h"
#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

/**
  Class for ADT tree structures.
  @author Andrew Daw, Makoto McLennan, Nicholas Dong.
 */

static tree_t tree_type;

struct tree_node {
    char *key;
    tree_colour colour;
    tree left;
    tree right;
    int frequency;
};

/**
 * Frees a tree and its contents.
 * @param t given tree.
 * @return empty tree
 */
tree tree_free(tree t) {
    if(t == NULL) {
        return t;
    }
    tree_free(t->left);
    tree_free(t->right);
    free(t->key);
    free(t);
    return NULL;
}

/**
 * Iterates through tree in order.
 * @param r given tree.
 * @param f(char *str) function to run.
 */
void tree_inorder(tree r, void f(int frequency, char *str)) {
    if(r == NULL) {
        return;
    } else {
        tree_inorder(r->left, f);
        f(r->frequency, r->key);
        tree_inorder(r->right, f);
    }
    return;
}

/**
 * Creates a new tree.
 * @param type sets tree type; BST or RBT.
 * @return returns a new empty tree.
 */
tree set_black(tree t) {
    t->colour = BLACK;
    return t;
}
tree tree_new(tree_t type) {
    tree r = emalloc(sizeof *r);
    r->key = NULL;
    r->left = NULL;
    r->right = NULL;
    tree_type = type;

    r->colour = RED;
    r->frequency = 0;
    
    return r;
}

/**
 * Iterates through tree preorder.
 * @param r given tree.
 * @param f(char *str) function to run.
 */

void tree_preorder(tree r, void f(int freqs, char *str)) {
    if(r == NULL) {
        return;
    } else {
        f(r->frequency, r->key);
        tree_preorder(r->left, f);
        tree_preorder(r->right, f);
    }
    return;
}



/**
 * Searches tree for a node with given string.
 * @param r given tree.
 * @param  *str string to search for.
 * @return 0 if tree is null, 1 if found, recursive.
 */

int tree_search(tree r, char *str) {
    if(r == NULL) {
        return 0;
    } else if(strcmp(r->key, str) == 0) {
        return 1;
    } else if(strcmp(r-> key, str) > 0) {
        return tree_search(r->left, str);
    } else {
        return tree_search(r->right, str);
    }
}

/**
 * Prints a string from node.
 * @param *s a string.
 */

void print_key(char *s) {
    printf("%s\n", s);
}

/**
 * Carries out right rotation on node of RBT.
 * @param r given tree.
 * @return rotated tree.
 */

static tree right_rotate(tree r) {
    tree temp = r->left;
    r->left = temp->right;
    temp->right = r;
    return temp;
}

/**
 * Carries out left rotation on node of RBT.
 * @param r given tree.
 * @return rotated tree.
 */

static tree left_rotate(tree r) {
    tree temp = r->right;
    r->right = temp->left;
    temp->left = r;
    return temp;
}
/**
 * Fixes tree according to RBT rules.
 * @param r given tree.
 * @return RBT tree.
 */

static tree tree_fix(tree r) {
    if(IS_RED(r->left) && IS_RED(r->left->left) && IS_RED(r->right)){
        r->colour = RED;
        r->left->colour = BLACK;
        r->right->colour = BLACK;
    }
    if(IS_RED(r->left) && IS_RED(r->left->left) && IS_BLACK(r->right)){
        r = right_rotate(r);
        r->colour = BLACK;
        r->right->colour = RED;
    }
    if(IS_RED(r->left) && IS_RED(r->left->right) && IS_RED(r->right)){
        r->colour = RED;
        r->left->colour = BLACK;
        r->right->colour = BLACK;
    }
    if(IS_RED(r->left) && IS_RED(r->left->right) && IS_BLACK(r->right)){
        r->left = left_rotate(r->left);
        r = right_rotate(r);
        r->colour = BLACK;
        r->right->colour = RED;
    }
    if(IS_RED(r->right) && IS_RED(r->right->left) && IS_RED(r->left)){
        r->colour = RED;
        r->left->colour = BLACK;
        r->right->colour = BLACK;
    }
    if(IS_RED(r->right) && IS_RED(r->right->left) && IS_BLACK(r->left)){
        r->right = right_rotate(r->right);
        r = left_rotate(r);
        r->colour = BLACK;
        r->left->colour = RED;
    }
    if(IS_RED(r->right) && IS_RED(r->right->right) && IS_RED(r->left)){
        r->colour = RED;
        r->left->colour = BLACK;
        r->right->colour = BLACK;
    }
    if(IS_RED(r->right) && IS_RED(r->right->right) && IS_BLACK(r->left)){
        r = left_rotate(r);
        r->colour = BLACK;
        r->left->colour = RED;
    }
    return r;
}

/**
 * Inserts nodes into tree.
 * @param r given tree.
 * @param *str string to enter into node.
 * @return returns a tree with node inserted.
 */

tree tree_insert(tree r, char *str) {
    if(r == NULL) {
        tree r = tree_new(tree_type);
        /* tree r = emalloc(sizeof *r);*/
        r->key = emalloc((strlen(str)+1) * sizeof str[0]);
        strcpy(r->key,str);
        /*  r->left = NULL;
        r->right = NULL;
        r->colour = RED;*/
        return r;
    } else if(r->key == NULL) {
        r->key = emalloc((strlen(str)+1) * sizeof str[0]);
        strcpy(r->key,str);
        return r;
    } else {
        if(strcmp(r->key, str) > 0) {
            r->left = tree_insert(r->left, str);
        } else if(strcmp(r->key,str) < 0) {
            r->right = tree_insert(r->right, str);
        } else {
            r->frequency++;
        }
        if (tree_type == RBT){
            r = tree_fix(r);
        }
        return r;
    }
}

/* These functions should be added to your tree.c file */

/**
 * Traverses the tree writing a DOT description about connections, and
 * possibly colours, to the given output stream.
 *
 * @param t the tree to output a DOT description of.
 * @param out the stream to write the DOT output to.
 */
static void tree_output_dot_aux(tree t, FILE *out) {
    if(t->key != NULL) {
        fprintf(out, "\"%s\"[label=\"{<f0>%s:%d|{<f1>|<f2>}}\"color=%s];\n",
                t->key, t->key, t->frequency,
                (RBT == tree_type && RED == t->colour) ? "red":"black");
    }
    if(t->left != NULL) {
        tree_output_dot_aux(t->left, out);
        fprintf(out, "\"%s\":f1 -> \"%s\":f0;\n", t->key, t->left->key);
    }
    if(t->right != NULL) {
        tree_output_dot_aux(t->right, out);
        fprintf(out, "\"%s\":f2 -> \"%s\":f0;\n", t->key, t->right->key);
    }
}

/**
 * Output a DOT description of this tree to the given output stream.
 * DOT is a plain text graph description language (see www.graphviz.org).
 * You can create a viewable graph with the command
 *
 *    dot -Tpdf < graphfile.dot > graphfile.pdf
 *
 * You can also use png, ps, jpg, svg... instead of pdf
 *
 * @param t the tree to output the DOT description of.
 * @param out the stream to write the DOT description to.
 */
void tree_output_dot(tree t, FILE *out) {
    fprintf(out, "digraph tree {\nnode [shape = Mrecord, penwidth = 2];\n");
    tree_output_dot_aux(t, out);
    fprintf(out, "}\n");
}

