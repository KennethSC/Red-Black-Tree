#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "RB_Tree.h"

int points = 0;
int numTests = 15;

// Correct = 0
int size_test(Tree T)
{
    int ans;
    ans = size(T);
    return ans;
}

// Correct = 0
int unique_test(Tree T)
{
    int ans;
    ans = getUnique(T);
    return ans;
}

// Expected = -1
int emptyTraverse_test(Tree T)
{
    int ans = -1;

    if (beginForward(T) != VAL_UNDEF) ans =  1;
    if (beginReverse(T) != VAL_UNDEF) ans = 2;
    if (currentVal(T) != VAL_UNDEF) ans =  3;
    if (currentKey(T) != KEY_UNDEF) ans = 4;

    return ans;
}

// Expectec = 0
int empty_test(Tree T)
{
    int ans = 0;

    makeEmpty(T);
    if(currentKey(T) != KEY_UNDEF || currentVal(T) != VAL_UNDEF || size(T) != 0) ans =  1;

    return ans;

}

// Correct = 6
int insertSize_test(Tree T, int* p)
{
    int ans;

    insert(T, "P", &p[0]);
    insert(T, "Y", &p[0]);
    insert(T, "T", &p[0]);
    insert(T, "H", &p[0]);
    insert(T, "O", &p[0]);
    insert(T, "N", &p[0]);

    ans = size(T);
    makeEmpty(T);

    return ans;
}


// Correct = 3
int deleteSize_test(Tree T, int* p)
{
    int ans;

    insert(T, "a", &p[0]);
    insert(T, "b", &p[0]);
    insert(T, "c", &p[0]);
    insert(T, "d", &p[0]);
    
    delete(T, "b");
    delete(T, "d");

    insert(T, "w", &p[0]);
    insert(T, "x", &p[0]);
    insert(T, "y", &p[0]);
    insert(T, "z", &p[0]);

    delete(T, "a");
    delete(T, "x");
    delete(T, "z");

    ans = size(T);
    makeEmpty(T);

    return ans;
}

// Correct = "x"
char* currKey_test(Tree T, int* p)
{
    char* ans;

    insert(T, "l", &p[0]);
    insert(T, "m", &p[0]);
    insert(T, "n", &p[0]);
    insert(T, "o", &p[0]);
    insert(T, "p", &p[0]);
    insert(T, "q", &p[0]);

    beginForward(T);
    
    for(int i = 0; i < 3; i++){
        next(T);
    }

    insert(T, "x", &p[0]);
    insert(T, "z", &p[0]);

    for(int i = 0; i < 3; i++){
        next(T);
    }

    ans = currentKey(T);
    makeEmpty(T);

    return ans;
}

// Correct = "n"
char* prev_test(Tree T, int* p)
{
    char* ans;

    insert(T, "k", &p[0]);
    insert(T, "e", &p[0]);
    insert(T, "n", &p[0]);
    insert(T, "n", &p[0]);
    insert(T, "e", &p[0]);
    insert(T, "t", &p[0]);
    insert(T, "h", &p[0]);

    beginReverse(T);

    prev(T);
    prev(T);
    prev(T);

    insert(T, "a", &p[0]);
    insert(T, "b", &p[0]);
    insert(T, "z", &p[0]);

    prev(T);
    prev(T);
    prev(T);

    ans = currentKey(T);
    makeEmpty(T);

    return ans;
}

// Correct = "t"
char* next_test(Tree T, int* p)
{
    char* ans;

    insert(T, "k", &p[0]);
    insert(T, "e", &p[0]);
    insert(T, "n", &p[0]);
    insert(T, "n", &p[0]);
    insert(T, "e", &p[0]);
    insert(T, "t", &p[0]);
    insert(T, "h", &p[0]);

    beginForward(T);

    next(T);
    next(T);
    next(T);

    insert(T, "a", &p[0]);
    insert(T, "b", &p[0]);
    insert(T, "z", &p[0]);

    next(T);
    next(T);
    next(T);

    ans = currentKey(T);
    makeEmpty(T);

    return ans;
}


// Correct = 9
int lookup_test(Tree T, int* p)
{
    int ans;

    insert(T, "P", &p[0]);
    insert(T, "Y", &p[4]);
    insert(T, "T", &p[7]);
    insert(T, "H", &p[6]);
    insert(T, "O", &p[9]);
    insert(T, "N", &p[0]);

    ans = *lookup(T, "O");
    makeEmpty(T);

    return ans;
}

// Expected = 0
int lookupVal_test(Tree T, int* p)
{
    int ans = 0;

    if(lookup(T, "f") != VAL_UNDEF) ans = 1;

    insert(T, "m", &p[0]);
    insert(T, "n", &p[1]);
    insert(T, "o", &p[2]);
    insert(T, "p", &p[3]);
    insert(T, "q", &p[4]);
    insert(T, "r", &p[5]);
    insert(T, "s", &p[6]);

    if(*lookup(T, "m") != p[0]) ans = 2;
    delete(T, "n");

    if(lookup(T, "n") != VAL_UNDEF) ans = 3;
    if(*lookup(T, "q") != p[4]) ans = 4;
    makeEmpty(T);

    return ans;
}


// Correct = 0
int makeEmpty_test(Tree T, int* p)
{
    int ans;

    insert(T, "m", &p[0]);
    insert(T, "d", &p[0]);
    insert(T, "c", &p[0]);
    insert(T, "d", &p[0]);
    insert(T, "e", &p[0]);
    insert(T, "f", &p[0]);
    insert(T, "g", &p[0]);
    insert(T, "h", &p[0]);

    makeEmpty(T);

    ans = size(T);
    makeEmpty(T);

    return ans;
}

// Expected = 0
int nonUniqueDelete_test(Tree T, int* p)
{
    int ans = 0;

    insert(T, "d", &p[0]);
    insert(T, "d", &p[1]);
    insert(T, "d", &p[2]);
    insert(T, "d", &p[3]);
    insert(T, "d", &p[4]);
    insert(T, "d", &p[5]);
    insert(T, "d", &p[6]);
    insert(T, "d", &p[7]);
    delete(T, "d");

    if (*lookup(T, "d") != p[4]) ans = 1;
    delete(T, "d");

    if (*lookup(T, "d") != p[5]) ans = 2;

    return ans;
}

// Correct = 6
int insertVal_test(Tree T, int* p)
{
    int ans;
    int wrong;

    insert(T, "m", &p[0]);
    insert(T, "n", &p[1]);
    insert(T, "o", &p[2]);
    beginReverse(T);
    insert(T, "p", &p[3]);
    insert(T, "q", &p[4]);
    insert(T, "f", &p[5]);
    insert(T, "e", &p[6]);


    if(*currentVal(T) != p[2]){
        wrong = *currentVal(T);
	    makeEmpty(T);

        return wrong;
    }

    beginForward(T);

    if(*currentVal(T) != p[6]){
        wrong = *currentVal(T);
     	makeEmpty(T);

        return wrong;
    }

    ans = *currentVal(T);
    makeEmpty(T);

    return ans;
}

// Correct = 4
int deleteVal_test(Tree T, int* p)
{
    int ans;
    int wrong;

    insert(T, "m", &p[0]);
    insert(T, "n", &p[1]);
    insert(T, "o", &p[2]);
    insert(T, "p", &p[3]);
    insert(T, "q", &p[4]);
    insert(T, "f", &p[5]);
    insert(T, "e", &p[6]);

    beginForward(T);
    delete(T, "e");

    insert(T, "e", &p[6]);
    delete(T, "f");
    beginForward(T);

    if(*currentVal(T) != p[6]){
        wrong = *currentVal(T);
        makeEmpty(T);
        return wrong;
    }

    insert(T, "f", &p[5]);
    delete(T, "n");
    beginReverse(T);

    if(*currentVal(T) != p[4]){
        wrong = *currentVal(T);
	    makeEmpty(T);
        return wrong;
    }

    ans = *currentVal(T);
    makeEmpty(T);

    return ans;
}

void test(int expected, int actual, char* test_name)
{
    if(expected == actual){
        printf("\n%s: PASSED", test_name);
        points++;
    }
    else{
        printf("\n%s: FAILED (expected = %d, your answer = %d)", test_name, expected, actual);
    }
}

void testChar(char* expected, char* actual, char* test_name)
{
    if(strcmp(expected, actual) == 0){
        printf("\n%s: PASSED", test_name);
        points++;
    }
    else{
        printf("\n%s: FAILED (expected = %s, your answer = %s)", test_name, expected, actual);
    }
}


int main()
{
    Tree T = newTree(0);
    int* p = calloc(10, sizeof(int));
    
    for(int i = 0; i < 10; i++) p[i] = i;  

    testChar("e", prev_test(T, p), "prev_test");
    testChar("t", next_test(T, p), "next_test");
    test(0, size_test(T), "size_test");
    test(0, empty_test(T), "empty_test");
    test(0, unique_test(T), "unique_test");
    test(9, lookup_test(T, p), "lookup_test");
    testChar("x", currKey_test(T, p), "currKey_test");
    test(0, lookupVal_test(T, p), "lookupVal_test");
    test(6, insertVal_test(T, p), "insertVal_test");
    test(4, deleteVal_test(T, p), "deleteVal_test");
    test(0, makeEmpty_test(T, p), "makeEmpty_test");
    test(6, insertSize_test(T, p), "insertSize_test");
    test(3, deleteSize_test(T, p), "deleteSize_test");
    test(-1, emptyTraverse_test(T), "emptyTraverse_test");
    test(0, nonUniqueDelete_test(T, p), "nonUniqueDelete_test");

    printf("\n\nYou passed %d out of %d tests\n\n", points, numTests);

    freeTree(&T);
    free(p);

    return 0;
}