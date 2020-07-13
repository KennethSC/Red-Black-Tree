#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include "RB_Tree.h"

#define RED 1
#define BLACK 0


// Structs --------------------------------------------------------------------

typedef struct NodeObj
{
   struct NodeObj* parent;
   struct NodeObj* left;
   struct NodeObj* right;
   KEY_TYPE key;
   VAL_TYPE val;
   int color;

} NodeObj;


typedef NodeObj* Node;


typedef struct TreeObj
{
   Node root;
   Node cursor;
   Node nil;
   int style;
   int size;

} TreeObj;


// Constructors and Destructors -----------------------------------------------

// Constructor for a new Node type
Node newNode(KEY_TYPE k, VAL_TYPE v)
{
   Node N = malloc(sizeof(NodeObj));
   assert( N != NULL);
   
   N->parent = NULL;
   N->left = NULL;
   N->right = NULL;
   N->key = k;
   N->val = v;
   N->color = RED;

   return N;

}


// Destuctor for Node
void freeNode(Node* pN)
{
   if(pN != NULL  && *pN != NULL)
   {
      free(*pN);
      *pN = NULL;
   }

}


// newTree()
// Creates a new empty Tree. If unique==false (0), then the Tree 
// will accept duplicate keys, i.e. distinct pairs with identical keys. If 
// unique==true (1 or any non-zero value), then duplicate keys will not be 
// accepted. In this case, the operation insert(D, k) will enforce the 
// precondition: lookup(D, k)==VAL_UNDEF
Tree newTree(int unique)
{
   Tree D = malloc(sizeof(TreeObj));
   assert( D != NULL);
 
   D->nil = newNode(KEY_UNDEF, VAL_UNDEF); 
   D->root = D->nil;
   D->cursor = D->nil;
   D->nil->color = BLACK;
   D->style = unique;
   D->size = 0;

   return D;

}


// Helper function for makeEmpty()
// which is used in freeDictionaty()
void deleteTree(Tree D, Node N)
{
   if(N != D->nil)
   {
      deleteTree(D, N->left);
      deleteTree(D, N->right);
      freeNode(&N);
   }

}


// freeTree()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeTree(Tree* pD)
{
   if(pD != NULL && *pD != NULL)
   {
      makeEmpty(*pD);
      freeNode(&(*pD)->nil);
      free(*pD);
      *pD = NULL;
   }

}



// Access functions -----------------------------------------------------------

// size()
// Returns the number of (key, value) pairs in Tree D.
int size(Tree D)
{
   if(D == NULL)
   {
      fprintf(stderr, "Tree Error: calling size() on NULL Tree reference\n");
      exit(EXIT_FAILURE);
   }

   return D->size;

}
   

// getUnique()
// Returns true (1) if D requires that all pairs have unique keys. Returns
// false (0) if D accepts distinct pairs with identical keys.
int getUnique(Tree D)
{
   if(D == NULL)
   {
      fprintf(stderr, "Tree Error: calling getUnique() on NULL Tree reference\n");
      exit(EXIT_FAILURE);
   }

   if(D->style == 0)
   {
      return 0;
   }

   return 1;

}


// Helper function for lookup()
// that returns the node that 
// has the desired key
Node keyFinder(Tree D, Node N, KEY_TYPE k)
{
   if(N == D->nil || KEY_CMP(k, N->key) == 0)
   {
      return N;
   }
   else if( KEY_CMP(k, N->key) > 0)
   {
      return keyFinder(D, N->right, k);
   }
   else
   {
      return keyFinder(D, N->left, k);
   }

}


// lookup()
// If Tree D contains a (key, value) pair whose key matches k (i.e. if
// KEY_CMP(key, k)==0), then returns value. If D contains no such pair, then
// returns VAL_UNDEF.
VAL_TYPE lookup(Tree D, KEY_TYPE k)
{
   if(D == NULL)
   {
      fprintf(stderr, "Tree Error: calling lookup() on NULL Tree reference\n");
      exit(EXIT_FAILURE);
   }


   Node N = keyFinder(D, D->root, k);


   if(N == D->nil)
   {
      return VAL_UNDEF;
   }

   return N->val;

}



// Manipulation procedures ----------------------------------------------------

// Helper function for insert and delete
// to keep Red Black tree balanced
void LeftRotate(Tree D, Node N)
{
   Node Y = N->right;
   N->right = Y->left;

   if(Y->left != D->nil)
   {
      Y->left->parent = N;
   }   

   Y->parent = N->parent;

   if(N->parent == D->nil)
   {
      D->root = Y;
   }
   else if(N == N->parent->left)
   {
      N->parent->left = Y;
   }
   else
   {
      N->parent->right = Y;
   }

   Y->left = N;
   N->parent = Y;

}
   


// Helper function for insert and delete
// to keep Red Black tree balanced
void RightRotate(Tree D, Node N)
{
   Node Y = N->left;
   N->left = Y->right;

   if(Y->right != D->nil)
   {
      Y->right->parent = N;
   }

   Y->parent = N->parent;

   if(N->parent == D->nil)
   {
      D->root = Y;
   }
   else if(N == N->parent->right)
   {
      N->parent->right = Y;
   }
   else
   {
      N->parent->left = Y;
   }

   Y->right = N;
   N->parent = Y;

}


// Helper function for insert() to make
// sure nodes are getting inserted properly
void InsertFixUp(Tree D, Node N)
{
   while(N->parent->color == RED)
   {
      if(N->parent == N->parent->parent->left)
      {
         Node Y = N->parent->parent->right;
         
         if(Y->color == RED)
         {
            N->parent->color = BLACK;
            Y->color = BLACK;
            N->parent->parent->color = RED;
            N = N->parent->parent;
         }
         else
         {
            if(N == N->parent->right)
            {
               N = N->parent;
               LeftRotate(D, N);
            }
           
            N->parent->color = BLACK;
            N->parent->parent->color = RED;        
            RightRotate(D, N->parent->parent);
         }
      }
      else
      {
         Node Y = N->parent->parent->left;
 
         if(Y->color == RED)
         {
            N->parent->color = BLACK;
            Y->color = BLACK;
            N->parent->parent->color = RED;
            N = N->parent->parent;
         }
         else
         {
            if(N == N->parent->left)
            {
               N = N->parent;
               RightRotate(D, N);
            }

            N->parent->color = BLACK;
            N->parent->parent->color = RED;
            LeftRotate(D, N->parent->parent);
         }
      }
   
   }

   D->root->color = BLACK;
  
}   



// insert()
// Insert the pair (k,v) into Tree D. 
// If getUnique(D) is false (0), then there are no preconditions.
// If getUnique(D) is true (1), then the precondition lookup(D, k)==VAL_UNDEF
// is enforced. 
void insert(Tree D, KEY_TYPE k, VAL_TYPE v)
{
   if(D == NULL)
   {
      fprintf(stderr, "Tree Error: calling insert() on NULL Tree reference\n");
      exit(EXIT_FAILURE);
   }


   if(getUnique(D) > 0)
   {
      if(lookup(D, k) != VAL_UNDEF)
      {
         fprintf(stderr, "Tree Error: cannot insert() due to already existing duplicate key\n");
         exit(EXIT_FAILURE);
      }
   }


   Node N = newNode(k, v);
   
   Node R = D->root;

   Node temp = D->nil;

 
   while(R != D->nil)
   {
      temp = R;

      if(KEY_CMP(k, R->key) < 0)
      {
         R = R->left;
      }
      else
      {
         R = R->right;
      }

   }

   N->parent = temp;
  
   if(temp == D->nil)
   {
      D->root = N;

   }
   else if(KEY_CMP(k, temp->key) < 0)
   {
      temp->left = N;

   }
   else
   {
      temp->right = N;

   }
 
   N->left = D->nil;
   N->right = D->nil;
   N->color = RED;

   D->size++;

   InsertFixUp(D, N);

}


// Helper function that 
// finds the minimum value
// in the entire tree
Node treeMin(Tree D, Node N)
{
   while(N->left != D->nil)
   {
      N = N->left;
   }

   return N;

}


// Helper function that 
// finds the maximum value
// in the entire tree
Node treeMax(Tree D, Node N)
{
   while(N->right != D->nil)
   {
      N = N->right;
   }

   return N;

}



// Helper function for delete()
void reRoot(Tree D, Node N, Node P)
{
   if(N->parent == D->nil)
   {
      D->root = P;
   }
   else if(N == N->parent->left)
   {
      N->parent->left = P;
   }
   else
   {
      N->parent->right = P;
   }


   P->parent = N->parent;

}


// Helper function for delete to make sure
// Red Black tree properties are maintained
void DeleteFixUp(Tree D, Node N)
{
   while(N != D->root && N->color == BLACK)
   {
      if(N == N->parent->left)
      {
         Node W = N->parent->right;
         
         if(W->color == RED)
         {
            W->color = BLACK;
            N->parent->color = RED;
            LeftRotate(D, N->parent);
            W = N->parent->right;
         }

         if(W->left->color == BLACK && W->right->color == BLACK)
         {
            W->color = RED;
            N = N->parent;
         }
         else
         {
            if(W->right->color == BLACK)
            {
               W->left->color = BLACK;
               W->color = RED;
               RightRotate(D, W);
               W = N->parent->right;
            }

            W->color = N->parent->color;
            N->parent->color = BLACK;
            W->right->color = BLACK;
            LeftRotate(D, N->parent);
            N = D->root;
         }
      }
      else
      {
         Node W = N->parent->left;
         
         if(W->color == RED)
         {
            W->color = BLACK;
            N->parent->color = RED;
            RightRotate(D, N->parent);
            W = N->parent->left;
         }

         if(W->right->color == BLACK && W->left->color == BLACK)
         {
            W->color = RED;
            N = N->parent;
         }
         else
         {
            if(W->left->color == BLACK)
            {
               W->right->color = BLACK;
               W->color = RED;
               LeftRotate(D, W);
               W = N->parent->left;
            }

            W->color = N->parent->color;
            N->parent->color = BLACK;
            W->left->color = BLACK;
            RightRotate(D, N->parent);
            N = D->root;
         }

      }

   }

   N->color = BLACK;

}


// delete()
// Remove the pair whose key is k from Tree D.
// Pre: lookup(D,k)!=VAL_UNDEF (i.e. D contains a pair whose key is k.)
void delete(Tree D, KEY_TYPE k)
{
  if(D == NULL)
   {
      fprintf(stderr, "Tree Error: calling delete() on NULL Tree reference\n");
      exit(EXIT_FAILURE);
   }
 

   if(lookup(D, k) == VAL_UNDEF)
   {
      fprintf(stderr, "Tree Error: calling delete() on non-existent key\n");
      exit(EXIT_FAILURE);
   }
 

   Node N = keyFinder(D, D->root, k);

   if(D->cursor != D->nil)
   {
      if(N->key == D->cursor->key)
      {
         D->cursor = D->nil;
      }
   }


   Node Y = N;

   Node X = D->nil;

   int OG_Y_color = Y->color;


   if(N->left == D->nil)
   {
      X = N->right;
      reRoot(D, N, N->right);
   }
   else if(N->right == D->nil)
   {
      X = N->left;
      reRoot(D, N, N->left);
   }
   else
   {
      Y = treeMin(D, N->right);
      OG_Y_color = Y->color;
      X = Y->right;
     
      if(Y->parent == N)
      {
         X->parent = Y;
      }
      else
      {
         reRoot(D, Y, Y->right);
         Y->right = N->right;
         Y->right->parent = Y;
      }

      reRoot(D, N, Y);
      Y->left = N->left;
      Y->left->parent = Y;
      Y->color = N->color;
  
   }


   if(OG_Y_color == BLACK)
   {
      DeleteFixUp(D, X);
   }

   freeNode(&N);

   D->size--;

}


// makeEmpty()
// Reset Tree D to the empty state, containing no pairs.
void makeEmpty(Tree D)
{
   if(D == NULL)
   {
      fprintf(stderr, "Tree Error: calling makeEmpty() on NULL Tree reference\n");
      exit(EXIT_FAILURE);
   }


   deleteTree(D, D->root);
   D->root = D->nil;   
   D->size = 0;

   if(D->cursor != D->nil)
   {
      D->cursor = D->nil;
   }

}   


// beginForward()
// If D is non-empty, starts a forward iteration over D at the first key 
// (as defined by the order operator KEY_CMP()), then returns the first
// value. If D is empty, returns VAL_UNDEF. 
VAL_TYPE beginForward(Tree D)
{
   if(D == NULL)
   {
      fprintf(stderr, "Tree Error: calling beginForward() on NULL Tree reference\n");
      exit(EXIT_FAILURE);
   }
  
   if(D->size == 0)
   {
      return VAL_UNDEF;
   }

   Node N = D->root;

   for(; N->left != D->nil; N = N->left);

   D->cursor = N;

   return N->val;

}  


// beginReverse()
// If D is non-empty, starts a reverse iteration over D at the last key 
// (as defined by the order operator KEY_CMP()), then returns the last
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginReverse(Tree D)
{
   if(D == NULL)
   {
      fprintf(stderr, "Tree Error: calling beginReverse() on NULL Tree reference\n");
      exit(EXIT_FAILURE);
   }

   if(D->size == 0)
   {
      return VAL_UNDEF;
   }

   Node N = D->root;

   for(; N->right != D->nil; N = N->right);  

   D->cursor = N;

   return N->val;

}


// currentKey()
// If an iteration (forward or reverse) over D has started, returns the 
// the current key. If no iteration is underway, returns KEY_UNDEF.
KEY_TYPE currentKey(Tree D)
{
   if(D == NULL)
   {
      fprintf(stderr, "Tree Error: calling currentKey() on NULL Tree reference\n");
      exit(EXIT_FAILURE);
   }

   if(D->cursor == D->nil)
   {
      return KEY_UNDEF;
   }

   return D->cursor->key;

}


// currentVal()
// If an iteration (forward or reverse) over D has started, returns the 
// value corresponding to the current key. If no iteration is underway, 
// returns VAL_UNDEF.
VAL_TYPE currentVal(Tree D)
{
   if(D == NULL)
   {
      fprintf(stderr, "Tree Error: calling currentVal() on NULL Tree reference\n");
      exit(EXIT_FAILURE);
   }

   if(D->cursor == D->nil)
   {
      return VAL_UNDEF;
   }
   
   return D->cursor->val;

}



// next()
// If an iteration (forward or reverse) over D has started, and has not
// reached the last pair, moves to the next key in D (as defined by the 
// order operator KEY_CMP()), and returns the value corresponding to the 
// new key. If an iteration has started, and has reached the last pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway, 
// returns VAL_UNDEF.
VAL_TYPE next(Tree D)
{
   if(D == NULL)
   {
      fprintf(stderr, "Tree Error: calling next() on NULL Tree reference\n");
      exit(EXIT_FAILURE);
   }

   if(D->cursor == D->nil)
   {
      return VAL_UNDEF;
   }


   if(treeMax(D, D->root) == D->cursor)
   {
      D->cursor = D->nil;
      return VAL_UNDEF;
   }


   Node X = D->cursor->right;

   if(X != D->nil)
   {
      while(X->left != D->nil)
      {
         X = X->left;
      }

      D->cursor = X;    

      return X->val;

   }


   Node N = D->cursor->parent;

   while(N != D->nil && D->cursor == N->right)
   {
      D->cursor = N;
      N = N->parent;
   }

   D->cursor = N;

   return N->val;

} 


// prev()
// If an iteration (forward or reverse) over D has started, and has not
// reached the first pair, moves to the previous key in D (as defined by the 
// order operator KEY_CMP()), and returns the value corresponding to the 
// new key. If an iteration has started, and has reached the first pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway, 
// returns VAL_UNDEF. 
VAL_TYPE prev(Tree D)
{
   if(D == NULL)
   {
      fprintf(stderr, "Tree Error: calling prev() on NULL Tree reference\n");
      exit(EXIT_FAILURE);
   }

   if(D->cursor == D->nil)
   {
      return VAL_UNDEF;
   }

   if(treeMin(D, D->root) == D->cursor)
   {
      D->cursor = D->nil;
      return VAL_UNDEF;
   }


   Node X = D->cursor->left;

   if(X != D->nil)
   {
      while(X->right != D->nil)
      {
         X = X->right;
      }

      D->cursor = X;

      return X->val;

   }


   Node N = D->cursor->parent;

   while(N != D->nil && D->cursor == N->left)
   {
      D->cursor = N;
      N = N->parent;
   }

   D->cursor = N;

   return N->val;

}


// Other operations -----------------------------------------------------------

// Helper function for printTree()
// prints all the keys in the Tree 
// in a preOrder tree walk
void printPreOrder(Tree D, FILE* out, Node N)
{
   if(N != D->nil)
   {
      fprintf(out, ""KEY_FORMAT"", N->key);
      printPreOrder(D, out, N->left);
      printPreOrder(D, out, N->right);
   }

}

   
// Helper function for printTree()
// prints all the keys in the Tree 
// in an inOrder tree walk
void printInOrder(Tree D, FILE* out, Node N)
{
   if(N != D->nil)
   {
      printInOrder(D, out, N->left);
      fprintf(out, ""KEY_FORMAT"", N->key);
      printInOrder(D, out, N->right);
   }

}


// Helper function for printTree()
// prints all the keys in the Tree 
// in a postOrder tree walk
void printPostOrder(Tree D, FILE* out, Node N)
{
   if(N != D->nil)
   {  
      printPostOrder(D, out, N->left);
      printPostOrder(D, out, N->right);
      fprintf(out, ""KEY_FORMAT"", N->key);
   }

}


// printTree()
// Prints the keys (only) of D in an order determined by the parameter ord.
// If ord is "pre", "in" or "post", executes the corresponding tree traversal
// on the underlying RBT, printing keys only (no values).  If ord is some
// other string, prints nothing.
void printTree(FILE* out, Tree D, const char* ord)
{
   if(D == NULL)
   {
      fprintf(stderr, "Tree Error: calling printTree() on NULL Tree reference\n");
      exit(EXIT_FAILURE);
   }


   if(strcmp(ord, "pre") == 0)
   {
      fprintf(out, "******************************************************\n");
      fprintf(out, "PRE-ORDER: \n");
      fprintf(out, "******************************************************\n");

      printPreOrder(D, out, D->root);
      fprintf(out, "\n");

   }
   else if(strcmp(ord, "in") == 0)
   {
      fprintf(out, "******************************************************\n");
      fprintf(out, "IN-ORDER: \n");
      fprintf(out, "******************************************************\n");

      printInOrder(D, out, D->root);
      fprintf(out, "\n");

   }
   else if(strcmp(ord, "post") == 0)
   {
      fprintf(out, "******************************************************\n");
      fprintf(out, "POST-ORDER: \n");
      fprintf(out, "******************************************************\n");

      printPostOrder(D, out, D->root);
      fprintf(out, "\n");
  
   }

   fprintf(out, "\n");

}
      










