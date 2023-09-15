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

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) 
{
  TreeMap * new = (TreeMap *) malloc(sizeof(TreeMap));
  if(new == NULL) return NULL;
  
  new->current = new->root = NULL;
  new->lower_than = lower_than;
  return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value)
{
  TreeNode* nodo = createTreeNode(key, value);
  if(nodo == NULL) return;
  
  if(tree == NULL || tree->root == NULL){
    tree->root = nodo;
    return;
  }
  
  Pair * aux = searchTreeMap(tree,key);
  if(aux != NULL) return;
  
  TreeNode* nodoActual = tree->root;
  while(1)
    {
      if(nodoActual->left == NULL) {
        nodoActual->left = nodo;
        return;
      }
      if(nodoActual->right == NULL) {
        nodoActual->right = nodo;
        return;
      }
      if(tree->lower_than(nodo->pair->key, nodoActual->pair->key) == 1)
          nodoActual = nodoActual->left;
      else nodoActual = nodoActual->right;

    }
  
  return;
}

TreeNode * minimum(TreeNode * x)
{
  if(x->left == NULL) return x;
  while(x->left != NULL)
    {
      x = x->left;
    }
  return x;
}


void removeNode(TreeMap * tree, TreeNode* node)
{
  //buscar si esta
  
  //sin hijos
  
  //con 1 hijo
  
  //con dos hijos
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}

Pair * searchTreeMap(TreeMap * tree, void* key) 
{
  if(tree == NULL) return NULL;
  
  tree->current = tree->root;


  while(tree->current != NULL)
    {
      if(is_equal(tree, tree->current->pair->key, key) == 1){
        return tree->current->pair;
      }
      if(tree->lower_than(key, tree->current->pair->key) == 1)
            tree->current = tree->current->left;
      else tree->current = tree->current->right;
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
