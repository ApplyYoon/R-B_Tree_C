#include "rbtree.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *NIL = (node_t *)calloc(1, sizeof(node_t));
  
  // NIL self
  NIL->color = RBTREE_BLACK;
  NIL->left = NIL;
  NIL->right = NIL;
  NIL->parent = NIL;

  p->nil = NIL;
  p->root = NIL;  
  // p->root->parent = NULL;

  printf("( !! New Tree !! )\n");
  return p;
}

void delete_rbtree(rbtree *t) {
  free(t->nil);
  free(t);
}

char getColorName(color_t nodeColor) {
  if (nodeColor == 0) return 'R';
  else return 'B';
}
int case3(rbtree *t) {

  return 0;
}

int case2(rbtree *t) {
  return 0;
}

void case1(rbtree *t, node_t *cur, char parentDirect) {
  node_t *NIL = t->nil;

  bool condition = ((cur != NIL && cur->parent != NIL && cur->parent->parent != NIL));

  printf("condition %d\n", condition);

  if (!condition) return;
  if (parentDirect == 'L' && cur->parent->parent->left == NIL) return;
  if (parentDirect == 'R' && cur->parent->parent->right == NIL) return;

  // change condition
  printf("parent: %c\n", parentDirect);

  if (parentDirect == 'R') {
    condition = (((cur->color == RBTREE_RED) && (cur->parent->color == RBTREE_RED)) && cur->parent->parent->left->color == RBTREE_BLACK);
  }
  else if (parentDirect == 'L') {
    condition = (((cur->color == RBTREE_RED) && (cur->parent->color == RBTREE_RED)) && cur->parent->parent->right->color == RBTREE_BLACK);
  }

  if (!condition) return;


  // for debuging  
  printf("---------------[ INFO ]--------------\n");
  printf("cur -> key: %d, color: %c\n", cur->key, getColorName(cur->color));
  printf("WELCOME TO CASE1\n");

  cur->color = RBTREE_BLACK;
  cur->parent->color = RBTREE_BLACK;

  if (parentDirect == 'L') {
    cur->parent->right = RBTREE_RED;
  }
  // else {    // if curDirect == 'R'
  //   cur->parent->left = RBTREE_RED;
  // }
  return;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t *cur = t->root; 
  node_t *NIL = t->nil;

  // Set new node
  node_t *p = (node_t *)calloc(1, sizeof(node_t));
  char parentDiret;

  p->key = key;
  p->color = RBTREE_RED;
  p->left = NIL;
  p->right = NIL;

  // root is black
  t->root->color = RBTREE_BLACK;

  printf("[insert] root: %d\n", t->root->key);
  printf("[insert] cur: %d\n", cur->key);
  printf("[insert] key: %d\n", key);
  
  // printf("NIL: %d\n", NIL->key);

  // root
  if (t->root == NIL) {
    t->root = p;
    t->root->left = NIL;
    t->root->right = NIL;
    t->root->parent = NIL;
    t->root->color = RBTREE_BLACK;
    return t->root;
  }
  else {
    while (cur != NIL)
    {
      // need to the same-number case

      // the key is in the left subtree
      if (key < cur->key) {
        if (cur->left != NIL) {
          printf("[inesrt] Move to left\n");
          cur = cur->left;
          parentDiret = 'L';
        }
        else if (cur->left == NIL) {
          printf("[insert](left) key: %d \n", cur->key);

          p->parent = cur;  // link parent
          cur->left = p;
    
          printf("[insert](new) key: %d \n", cur->right->key);


          // move to new node
          cur = cur->left;

          // case 1
          case1(t, cur, parentDiret);

          return cur; 
        }
      }
      // the key is in the right subtree
      else if (key > cur->key) {
        if (cur->right != NIL) {
          printf("[inesrt] Move to right\n");
          cur = cur->right;
          parentDiret = 'R';
        }
        else if (cur->right == NIL) {
          printf("[insert](right) key: %d \n", cur->key);

          p->parent = cur;  // link parent
          cur->right = p;

          printf("[insert](new) key: %d \n", cur->right->key);

          // move to new node
          cur = cur->right;
          

          // case 1
          case1(t, cur, parentDiret);
          
          
          return cur;
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
