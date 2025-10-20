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

/*
1. y의 왼쪽 서브 트리를 x의 오른쪽 서브트리로 회전
2. if y의 왼쪽 서브 트리가 비어 있지 않은 경우 -> x는 서브 트리 루트의 부모가 됨
3. x의 부모가 y의 부모가 됨
4. if x가 루트인 경우 -> y가 루트가 됨
5. else if x가 왼쪽 자식인 경우 -> y는 왼쪽 자식이 됨
6. else x가 오른쪽 자식인 경우 -> y는 오른쪽 자식이 됨
7. x를 y의 왼쪽 자식이 되게 함
8. x의 부모는 y가 됨
*/
void turn_left(rbtree *t, node_t *std) {
  printf("Turn left YEEEEEEEEEEEEEEEEEAH\n");
  node_t *x = std->parent;
  node_t *y;
  node_t *NIL = t->nil;

  y = x->right;

  x->right = y->left;
  if (y->left != NIL) {
    y->left->parent = x;
  }

  y->parent = x->parent;
  if (x->parent == NIL) { // if root
    t->root = y;
  }
  else if (x == x->parent->left) {
    x->parent->left = y;
  }
  else {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;

  return;
}

int case3(rbtree *t, node_t *cur) {
  node_t *NIL = t->nil;
  node_t *temp;
  node_t *lost;
  return 0;
}

int case2(rbtree *t, node_t *cur) {
  return 0;
}



/*
case 1-1
    B
  R   R
        N

case 1-2
    B
  R   R
     N 

case 1-3
    B
  R   R
 N

case 1-4
    B
  R    R
   N
*/

void case1(rbtree *t, node_t *cur, char parentDirect) {
  node_t *NIL = t->nil;
  printf("---------------[ INFO ]--------------\n");
  printf("cur -> key: %d, color: %c\n", cur->key, getColorName(cur->color));
  printf("WELCOME TO CASE1\n");
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

          printf("When the cur's value is %d, gonna the case3\n", cur->key);
          // case3(t, cur->parent);

          // printf("When the cur is %d, gonna the case1\n", cur->key);
      
          
          // case1(t, cur, parentDiret);
          

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
        
          // printf("When the cur's value is %d, gonna the case3\n", cur->key);
          // case3(t, cur->parent);
          turn_left(t, cur);
          // case1(t, cur, parentDiret);
          
          
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
