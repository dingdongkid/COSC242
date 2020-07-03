#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rbt.h"
#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

typedef enum { RED, BLACK } rbt_colour;

struct rbt_node {
    char *key;
    rbt_colour colour;
    rbt left;
    rbt right;
};

void *emalloc(size_t s) {
    void *result = malloc(s);
    if(NULL == result) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

static rbt left_rotate(rbt r) {
    rbt temp = r->right;
    r->right = temp->left;
    temp->left = r;
    return temp;
}

static rbt right_rotate(rbt r) {
    rbt temp = r->left;
    r->left = temp->right;
    temp->right = r;
    return temp;
}

/**
 * Fixes rbt according to RBT rules.
 * @param r given rbt.
 * @return RBT rbt.
 */

static rbt rbt_fix(rbt r) {
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

/*
  rbt findMin(rbt r) {
  if(r == NULL) {
  return NULL;
  } else if(r->left == NULL) {
  return r;
  } else {
        return findMin(r->left);
        }
}

rbt rbt_delete(rbt r, char *str) {
    if (r == NULL) {
        return r;
    }
    if(strcmp(r->key, str) > 0) {
        rbt_delete(r->left, str);
    } else if(strcmp(r->key, str) < 0) {
        rbt_delete(r->right, str);
    } else {
        if(r->left == NULL && r->right == NULL) {
            r = rbt_free(r);
            r = NULL;
            return r;
        } else if(r->left == NULL) {
            rbt temp = rbt_new();
            temp = r->right;
            rbt_free(r);
            return temp;
        } else if(r->right == NULL) {
            rbt temp = rbt_new();
            temp = r->left;
            rbt_free(r);
            return temp;
        } else {
            rbt successor = rbt_new();
            successor = findMin(r->right);
            strcpy(r->key,successor->key);
            r->right = rbt_delete(r->right, successor->key);
        }
    }
    return r;
}

rbt rbt_free(rbt r) {
    free(r->key);
    free(r->colour);
    free(r);
    return r;
}

static rbt right_rotate(rbt r) {
    rbt temp = rbt_new();
    temp = r;
    r = temp->left;
    temp->left = r->right;
    r->right = temp;
    return r;
}
*/

/**
 * Frees a rbt and its contents.
 * @param t given rbt.
 * @return empty rbt
 */
rbt rbt_free(rbt t) {
    if(t == NULL) {
        return t;
    }
    rbt_free(t->left);
    rbt_free(t->right);
    free(t->key);
    free(t);
    return NULL;
}
                 
void rbt_inorder(rbt r, void f(char *str)) {
    if(r == NULL) {
        return;
    } else {
        rbt_inorder(r->left, f);
        f(r->key);
        rbt_inorder(r->right, f);
    }
    return;
}
  
rbt rbt_insert(rbt r, char *str) {
    if(r == NULL) {
        rbt r = emalloc(sizeof *r);
        r->key = emalloc((strlen(str)+1) * sizeof r->key[0]);
        r->left = NULL;
        r->right = NULL;
        strcpy(r->key,str);
        r->colour = RED;
        r = rbt_fix(r);
        return r;
    } else {
        if(strcmp(r->key,str) > 0) {
            r->left = rbt_insert(r->left, str);
        } else {
            r->right = rbt_insert(r->right, str);
        }
        return r;
    }
}

rbt rbt_new(){
    return NULL;
}

void rbt_preorder(rbt r, void f(char *str)) {
    if(r == NULL) {
        return;
    } else {
        f(r->key);
        rbt_preorder(r->left, f);
        rbt_preorder(r->right, f);
    }
    return;
}

int rbt_search(rbt r, char *str) {
    if(r == NULL) {
        return 0;
    } else if(r->key == str) {
        return 1;
    } else if(r-> key > str) {
        return rbt_search(r->left, str);
    } else {
        return rbt_search(r->right, str);
    }
}

void print_key(char *s) {
    printf("%s\n", s);
}

int main(void){
    rbt r = rbt_new();
    char *c[12] = {"h", "l", "i", "f", "j", "g", "k", "d", "a", "e", "b", "c"};
    int i;
    for(i = 0; i < 12; i++) {
        r = rbt_insert(r, c[i]);
    }

    rbt_preorder(r, print_key);
    r = left_rotate(r);
    rbt_preorder(r, print_key);    
    return EXIT_SUCCESS;
}
