#include "rbtree.h"

#include <stdlib.h>
#include <stdio.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *NIL = (node_t *)calloc(1, sizeof(node_t));
  
  NIL->color = RBTREE_BLACK;

  p->nil = NIL;
  p->root = NIL;  
  p->root->parent = NULL;

  printf("( !! New Tree !! )\n");
  return p;
}

void delete_rbtree(rbtree *t) {
  free(t->nil);
  free(t);
}

int case3(rbtree *t) {

  return 0;
}

int case2(rbtree *t) {
  return 0;
}

int case1(rbtree *t) {
  node_t *cur = t->root;

  return 0;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  printf("!\n");
  node_t *cur = t->root; 
  printf("!\n");
  node_t *NIL = t->nil;
  printf("!\n");
  rbtree *p = (node_t *)calloc(1, sizeof(node_t));

  printf("[insert] root: %d\n", t->root->key);
  printf("[insert] cur: %d\n", cur->key);
  printf("[insert] key: %d\n", key);
  // printf("NIL: %d\n", NIL->key);

  // root
  if (t->root->key == NULL) {
    t->root->key = key;
    t->nil = NULL;
    t->root->color = RBTREE_BLACK;
    return t->root;
  }
  else {
    while (cur != NULL)
    {
      // need to the same-number case

      // the key is in the left subtree
      if (key < cur->key) {
        if (cur->left != NIL) {
          printf("[inesrt] Move to left\n");
          cur = cur->left;
        }
        else {
          printf("[insert](left) key: %d \n", cur->key);
          cur->left = p;
          cur->left->key = key;
          cur->left->color = RBTREE_RED;
          
          cur->left->left = NIL;
          cur->left->right = NIL;
          return cur->left;
        }
      }

      // the key is in the right subtree
      else if (key > cur->key) {
        if (cur->right != NIL) {
          printf("[inesrt] Move to right\n");
          cur = cur->right;
        }
        else {
          printf("[insert](right) key: %d \n", cur->key);
          cur->right = p;
          cur->right->key = key;
          cur->right->color = RBTREE_RED;
          
          cur->right->left = NIL;
          cur->right->right = NIL;
          printf("[insert](new) key: %d \n", cur->right->key);
          return cur->right;
        }
      }
    }
  }

  // If not inserted -> free
  free(p);

  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  node_t *cur = t->root;
  node_t *NIL = t->nil;

  // key == root
  if (key == cur->key) return t->root;

  while (cur != NIL)
  {
    // find the node
    if (key == cur->key){
      return cur;
    }

    // the key is in the left subtree
    if (key < cur->key) {
      cur = cur->left;
    }

    // the key is in the right subtree
    else if (key > cur->key) {
      cur = cur->right;
    }
  }
  // printf("!!!!!!!!!! Not found\n");
  return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // printf("rbtree_erase\n");
  node_t *find = rbtree_find(t, p->key);
  node_t *NIL = t->nil;
  node_t *cur = t->root;
  int key = p->key;

  // key == root
  if (key == cur->key) {
    t->root = NIL;
    return 0;
  }

  // else {
  //   printf("!\n");
  //   while (cur != NIL)
  //   {
  //     // find the node
  //     if (key == cur->key){
  //       return cur;
  //     }

  //     // the key is in the left subtree
  //     if (key < cur->key) {
  //       cur = cur->left;
  //     }

  //     // the key is in the right subtree
  //     else if (key > cur->key) {
  //       cur = cur->right;
  //     }
  //   }    
  // }
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
