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
      //si va a la izq
      if(tree->lower_than(nodo->pair->key, nodoActual->pair->key) == 1)
      {
        
        if(nodoActual->left == NULL) {
          nodoActual->left = nodo;
          nodo->parent = nodoActual;
          tree->current = nodo;
          return;
        }
        nodoActual = nodoActual->left;
      }else{//si va a la derecha
        
        if(nodoActual->right == NULL) {
          nodo->parent = nodoActual;
          nodoActual->right = nodo;
          tree->current = nodo;
          return;
        }
        nodoActual = nodoActual->right;
      }
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
  //hoja
  if(node->left == NULL && node->right == NULL){
    node->parent->left = node->parent->right = NULL;
    return;
  }
  //1 hijo
  if(node->left == NULL && node->right != NULL){
    //tengo q saber donde esta el parent para asi ajustar los nodos
    if(node->parent->left->pair->key == node->pair->key){
      node->parent->left = node->right;
      node->right->parent = node->parent;
      return;
    }else if(node->parent->right->pair->key == node->pair->key){
      node->parent->right = node->right;
      node->right->parent = node->parent;
      return;
    }
  }else if(node->left != NULL && node->right == NULL){
    if(node->parent->left->pair->key == node->pair->key){
      node->parent->left = node->left;
      node->left->parent = node->parent;
      return;
    }else if(node->parent->right->pair->key == node->pair->key){
      node->parent->right = node->left;
      node->left->parent = node->parent;
      return;
    }
  }
  //2 hijos
  TreeNode * minimo = minimum(node->right); //obtengo el minimum
  node->pair->key = minimo->pair->key;
  node->pair->value = minimo->pair->value;
  removeNode(tree, minimo);
  return ;
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

Pair * upperBound(TreeMap * tree, void* key)
{
  if(tree == NULL) return NULL;
  TreeNode * aux = tree->root;
  Pair * mayor = NULL;

  while(aux != NULL)
    {
      //si es la clave retorno el par
      if(is_equal(tree, aux->pair->key, key) == 1){ 
        return aux->pair;
      }
      
      if(tree->lower_than(key, aux->pair->key) == 1){
        //va a la izq
        mayor = aux->pair;
        aux = aux->left;
      }else{//va a la der
        
        aux = aux->right;
          }
    }
  return mayor;
}

Pair * firstTreeMap(TreeMap * tree) {
  if(tree== NULL || tree->root == NULL) return NULL;
  TreeNode * minimo = minimum(tree->root->left); //obtengo el minimum
  return minimo->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
  if(tree== NULL || tree->root == NULL || tree->current == NULL) return NULL;

  TreeNode * aux = tree->current;

  if((aux->left == NULL && aux->right == NULL) || (aux->parent != NULL && aux->parent == aux->right)){
    aux = aux->parent;
  }
  
  if(aux->right != NULL){
    aux = aux->right;
    while(aux->left != NULL){
      aux = aux->left;
    }
  }
  
  return aux->pair;
}
