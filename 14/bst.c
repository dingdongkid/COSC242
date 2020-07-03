#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

struct bst_node {
    char *key;
    bst left;
    bst right;
};

void *emalloc(size_t s) {
    void *result = malloc(s);
    if(NULL == result) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

bst findMin(bst b) {
    if(b == NULL) {
        return NULL;
    } else if(b->left == NULL) {
        return b;
    } else {
        return findMin(b->left);
    }
}

bst bst_delete(bst b, char *str) {
    if (b == NULL) {
        return b;
    }
    if(strcmp(b->key, str) > 0) {
        bst_delete(b->left, str);
    } else if(strcmp(b->key, str) < 0) {
        bst_delete(b->right, str);
    } else {
        if(b->left == NULL && b->right == NULL) {
            b = bst_free(b);
            b = NULL;
            return b;
        } else if(b->left == NULL) {
            bst temp = bst_new();
            temp = b->right;
            bst_free(b);
            return temp;
        } else if(b->right == NULL) {
            bst temp = bst_new();
            temp = b->left;
            bst_free(b);
            return temp;
        } else {
            bst successor = bst_new();
            successor = findMin(b->right);
            strcpy(b->key,successor->key);
            b->right = bst_delete(b->right, successor->key);
        }
    }
    return b;
}

bst bst_free(bst b) {
    if(b == NULL) {
        return b;
    }
    bst_free(b->left);
    bst_free(b->right);
    free(b->key);
    free(b);
    return NULL;
}

void bst_inorder(bst b, void f(char *str)) {
    if(b == NULL) {
        return;
    } else {
        bst_inorder(b->left, f);
        f(b->key);
        bst_inorder(b->right, f);
    }
    return;
}
    
bst bst_insert(bst b, char *str) {
    if(b == NULL) {
        bst b = emalloc(sizeof *b);
        b->key = emalloc((strlen(str)+1) * sizeof b->key[0]);
        strcpy(b->key,str);
        return b;
    } else {
        if(strcmp(b->key,str) > 0) {
            b->left = bst_insert(b->left, str);
        } else {
            b->right = bst_insert(b->right, str);
        }
        return b;
    }
}

bst bst_new(){
    return NULL;
}

void bst_preorder(bst b, void f(char *str)) {
    if(b == NULL) {
        return;
    } else {
        f(b->key);
        bst_preorder(b->left, f);
        bst_preorder(b->right, f);
    }
    return;
}

int bst_search(bst b, char *str) {
    if(b == NULL) {
        return 0;
    } else if(strcmp(b->key, str) == 0) {
        return 1;
    } else if(strcmp(b->key, str) > 0) {
        return bst_search(b->left, str);
    } else {
        return bst_search(b->right, str);
    }
}

void print_key(char *s) {
    if(s != NULL) {
        printf("%s\n", s);
    }
}

int main(void){
    bst b = bst_new();
    b = bst_insert(b, "one");
    b = bst_insert(b, "two");
    b = bst_insert(b, "asd");
    bst_inorder(b, print_key);
    bst_preorder(b, print_key);
    b = bst_delete(b, "asd");
    b = bst_delete(b, "one");
    bst_inorder(b, print_key);    
    return EXIT_SUCCESS;
}
