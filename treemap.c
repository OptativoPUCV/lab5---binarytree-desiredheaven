#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {

    TreeMap* map = (TreeMap *)malloc(sizeof(TreeMap));
    map->current = NULL;
    map->root = NULL;
    map->lower_than = lower_than;
  
    return map;
}


void insertTreeMap(TreeMap *tree, void* key, void* value) {
    TreeNode* new_node = createTreeNode(key, value);

    if (tree->root == NULL) {
        tree->root = new_node;
        return;
    }

    TreeNode* current = tree->root;

    while (current != NULL) {
        int compare = tree->lower_than(key, current->pair->key);

        if (compare == 0) {
            free(new_node);
            return;
        } else if (compare < 0) {
            if (current->left == NULL) {
                current->left = new_node;
                new_node->parent = current;
                return;
            }
            current = current->left;
        } else {
            if (current->right == NULL) {
                current->right = new_node;
                new_node->parent = current;
                return;
            }
            current = current->right;
        }
    }
}

TreeNode * minimum(TreeNode * x){
  while (x->left != NULL)
    {
      x = x -> left;
    }
    return x;
}


void removeNode(TreeMap *tree, TreeNode* node) 
{
  if (tree == NULL || node == NULL)
    return;

  if (node->right == NULL && node->left == NULL)
  {
    if (node->parent != NULL)
    {
      if (node->parent->left == node)
        node->parent->left = NULL;
      else
        node->parent->right = NULL;
    }
    else
    {
      tree->root = NULL; 
    }
    free(node);
  }
  else
  {
    if (node->right == NULL || node->left == NULL)
    {
      TreeNode* child;
      if (node->right !=  NULL)
        child = node->right;
      else
        child = node->left;
      
      if (child != NULL)
        child->parent = node->parent;
    }
    else
    {
      TreeNode* minimumNum = minimum(node->right);
      void* auxValue = node->pair->value;
      void* auxKey = node->pair->key;
      node->pair->value = minimumNum->pair->value;
      node->pair->key = minimumNum->pair->key;
      minimumNum->pair->value = auxValue;
      minimumNum->pair->key = auxKey;

      removeNode(tree, minimumNum);
    }
  }
}




void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}

Pair * searchTreeMap(TreeMap * tree, void* key) {

  tree->current = tree->root;
  while (tree->current != NULL)
    {
      if (is_equal(tree, key, tree->current->pair->key)==1)
      {
        return tree->current->pair;
      }
      if (tree->lower_than(key, tree->current->pair->key) == 1)
      {
        tree->current = tree->current->left;
      }
      else
      {
        tree->current = tree->current->right;
      }
    }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
