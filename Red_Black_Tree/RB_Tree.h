#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#ifndef RB_TREE_H_INCLUDE_
#define RB_TREE_H_INCLUDE_

#define KEY_TYPE char*
#define VAL_TYPE int*
#define KEY_UNDEF NULL
#define VAL_UNDEF NULL
#define KEY_FORMAT "%s"
#define VAL_FORMAT "%p"
#define KEY_CMP(x,y) strcmp(x,y)


// Exported type --------------------------------------------------------------
typedef struct TreeObj* Tree;


// Constructors-Destructors ---------------------------------------------------

// newTree()
// Creates a new empty Tree. If unique==false (0), then the Tree 
// will accept duplicate keys, i.e. distinct pairs with identical keys. If 
// unique==true (1 or any non-zero value), then duplicate keys will not be 
// accepted. In this case, the operation insert(D, k) will enforce the 
// precondition: lookup(D, k)==VAL_UNDEF
Tree newTree(int unique);

// freeTree()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeTree(Tree* pD);


// Access functions -----------------------------------------------------------

// size()
// Returns the number of (key, value) pairs in Tree D.
int size(Tree D);

// getUnique()
// Returns true (1) if D requires that all pairs have unique keys. Returns
// false (0) if D accepts distinct pairs with identical keys.
int getUnique(Tree D);

// lookup()
// If Tree D contains a (key, value) pair whose key matches k (i.e. if
// KEY_CMP(key, k)==0), then returns value. If D contains no such pair, then
// returns VAL_UNDEF.
VAL_TYPE lookup(Tree D, KEY_TYPE k);


// Manipulation procedures ----------------------------------------------------

// insert()
// Insert the pair (k,v) into Tree D. 
// If getUnique(D) is false (0), then there are no preconditions.
// If getUnique(D) is true (1), then the precondition lookup(D, k)==VAL_UNDEF
// is enforced. 
void insert(Tree D, KEY_TYPE k, VAL_TYPE v);

// delete()
// Remove the pair whose key is k from Tree D.
// Pre: lookup(D,k)!=VAL_UNDEF (i.e. D contains a pair whose key is k.)
void delete(Tree D, KEY_TYPE k);

// makeEmpty()
// Reset Tree D to the empty state, containing no pairs.
void makeEmpty(Tree D);

// beginForward()
// If D is non-empty, starts a forward iteration over D at the first key 
// (as defined by the order operator KEY_CMP()), then returns the first
// value. If D is empty, returns VAL_UNDEF. 
VAL_TYPE beginForward(Tree D);

// beginReverse()
// If D is non-empty, starts a reverse iteration over D at the last key 
// (as defined by the order operator KEY_CMP()), then returns the last
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginReverse(Tree D);

// currentKey()
// If an iteration (forward or reverse) over D has started, returns the 
// the current key. If no iteration is underway, returns KEY_UNDEF.
KEY_TYPE currentKey(Tree D);

// currentVal()
// If an iteration (forward or reverse) over D has started, returns the 
// value corresponding to the current key. If no iteration is underway, 
// returns VAL_UNDEF.
VAL_TYPE currentVal(Tree D);

// next()
// If an iteration (forward or reverse) over D has started, and has not
// reached the last pair, moves to the next key in D (as defined by the 
// order operator KEY_CMP()), and returns the value corresponding to the 
// new key. If an iteration has started, and has reached the last pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway, 
// returns VAL_UNDEF.
VAL_TYPE next(Tree D);


// prev()
// If an iteration (forward or reverse) over D has started, and has not
// reached the first pair, moves to the previous key in D (as defined by the 
// order operator KEY_CMP()), and returns the value corresponding to the 
// new key. If an iteration has started, and has reached the first pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway, 
// returns VAL_UNDEF. 
VAL_TYPE prev(Tree D);


// Other operations -----------------------------------------------------------

// printTree()
// Prints the keys (only) of D in an order determined by the parameter ord.
// If ord is "pre", "in" or "post", executes the corresponding tree traversal
// on the underlying RBT, printing keys only (no values).  If ord is some
// other string, prints nothing.
void printTree(FILE* out, Tree D, const char* ord);



#endif









