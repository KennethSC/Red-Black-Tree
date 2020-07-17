#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>

#include "RB_Tree.h"

int points = 0;
int numTests = 10;


// Correct = 0
int empty_test()
{
    Tree T = newTree(0);
    int ans;
    
    ans = size(T);
    freeTree(&T);
    return ans;

}

// Correct = -1
int emptyTraverse_test()
{
    Tree T = newTree(0);
    int ans = -1;

    if (beginForward(T) != VAL_UNDEF) ans =  1;
    if (beginReverse(T) != VAL_UNDEF) ans = 2;
    if (currentVal(T) != VAL_UNDEF) ans =  3;
    if (currentKey(T) != KEY_UNDEF) ans = 4;

    freeTree(&T);
    return ans;

}

// Correct = 6
int insertSize_test()
{
    Tree T = newTree(0);
    int ans;

    int* p = calloc(10, sizeof(int));
    for(int x = 0; x < 10; x++) p[x] = x;

    insert(T, "P", &p[0]);
    insert(T, "Y", &p[0]);
    insert(T, "T", &p[0]);
    insert(T, "H", &p[0]);
    insert(T, "O", &p[0]);
    insert(T, "N", &p[0]);

    ans = size(T);
    freeTree(&T);
    free(p);
    return ans;
}


// Correct = 3
int deleteSize_test()
{
    Tree T = newTree(0);
    int ans;

    int* p = calloc(10, sizeof(int));
    for(int x = 0; x < 10; x++) p[x] = x;

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
    freeTree(&T);
    free(p);
    return ans;

}


// Correct = "x"
char* currKey_test()
{
    Tree T = newTree(0);
    char* ans;

    int* p = calloc(10, sizeof(int));
    for(int x = 0; x < 10; x++) p[x] = x;

    insert(T, "l", &p[0]);
    insert(T, "m", &p[0]);
    insert(T, "n", &p[0]);
    insert(T, "o", &p[0]);
    insert(T, "p", &p[0]);
    insert(T, "q", &p[0]);

    beginForward(T);
    
    for(int i = 0; i < 3; i++)
    {
        next(T);
    }

    insert(T, "x", &p[0]);
    insert(T, "z", &p[0]);

    for(int i = 0; i < 3; i++)
    {
        next(T);
    }

    ans = currentKey(T);
    freeTree(&T);
    free(p);
    return ans;

}


// Correct = "e"
char* prev_test()
{
    Tree T = newTree(0);
    char* ans;

    int* p = calloc(10, sizeof(int));
    for(int x = 0; x < 10; x++) p[x] = x;

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


    insert(T, "a", &p[0]);
    insert(T, "b", &p[0]);
    insert(T, "z", &p[0]);

    prev(T);
    prev(T);
    prev(T);

    ans = currentKey(T);
    freeTree(&T);
    free(p);
    return ans;

}


// Correct = 9
int lookup_test()
{
    Tree T = newTree(0);
    int ans;

    int* p = calloc(10, sizeof(int));
    for(int x = 0; x < 10; x++) p[x] = x;

    insert(T, "P", &p[0]);
    insert(T, "Y", &p[4]);
    insert(T, "T", &p[7]);
    insert(T, "H", &p[6]);
    insert(T, "O", &p[9]);
    insert(T, "N", &p[0]);

    ans = *lookup(T, "O");
    freeTree(&T);
    free(p);
    return ans;

}

// Correct = 0
int makeEmpty_test()
{
    Tree T = newTree(0);
    int ans;

    int* p = calloc(10, sizeof(int));
    for(int x = 0; x < 10; x++) p[x] = x;

    insert(T, "m", &p[0]);
    insert(T, "d", &p[0]);
    insert(T, "c", &p[0]);
    insert(T, "d", &p[0]);
    insert(T, "e", &p[0]);
    insert(T, "f", &p[0]);
    insert(T, "g", &p[0]);
    insert(T, "h", &p[0]);

    beginForward(T);
    makeEmpty(T);

    ans = size(T);
    freeTree(&T);
    free(p);
    return ans;

}

// Correct = 6
int insertVal_test()
{
    Tree T = newTree(0);
    int ans;
    int wrong;

    int* p = calloc(10, sizeof(int));
    for(int x = 0; x < 10; x++) p[x] = x;

    insert(T, "m", &p[0]);
    insert(T, "n", &p[1]);
    insert(T, "o", &p[2]);
    beginReverse(T);
    insert(T, "p", &p[3]);
    insert(T, "q", &p[4]);
    insert(T, "f", &p[5]);
    insert(T, "e", &p[6]);


    if(*currentVal(T) != p[2])
    {
        wrong = *currentVal(T);
        freeTree(&T);
        free(p);
        return wrong;
    }

    beginForward(T);

    if(*currentVal(T) != p[6])
    {
        wrong = *currentVal(T);
        freeTree(&T);
        free(p);
        return wrong;
    }

    ans = *currentVal(T);
    freeTree(&T);
    free(p);
    return ans;

}

// Correct = 4
int deleteVal_test()
{
    Tree T = newTree(0);
    int ans;
    int wrong;

    int* p = calloc(10, sizeof(int));
    for(int x = 0; x < 10; x++) p[x] = x;


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

    if(*currentVal(T) != p[6])
    {
        wrong = *currentVal(T);
        freeTree(&T);
        free(p);
        return wrong;
    }

    insert(T, "f", &p[5]);
    delete(T, "n");
    beginReverse(T);

    if(*currentVal(T) != p[4])
    {
        wrong = *currentVal(T);
        freeTree(&T);
        free(p);
        return wrong;
    }

    ans = *currentVal(T);
    freeTree(&T);
    free(p);
    return ans;

}


void test(int expected, int actual, char* test_name)
{
    if(expected == actual)
    {
        printf("\n%s: PASSED", test_name);
        points++;
    }
    else
    {
        printf("\n%s: FAILED (expected = %d, actual = %d)", test_name, expected, actual);
    }

}

void testChar(char* expected, char* actual, char* test_name)
{
    if(strcmp(expected, actual) == 0)
    {
        printf("\n%s: PASSED", test_name);
        points++;
    }
    else
    {
        printf("\n%s: FAILED (expected = %s, actual = %s)", test_name, expected, actual);
    }

}


int main()
{
    testChar("e", prev_test(), "prev_test");
    test(0, empty_test(), "empty_test");
    test(9, lookup_test(), "lookup_test");
    testChar("x", currKey_test(), "currKey_test");
    test(6, insertVal_test(), "insertVal_test");
    test(4, deleteVal_test(), "deleteVal_test");
    test(0, makeEmpty_test(), "makeEmpty_test");
    test(6, insertSize_test(), "insertSize_test");
    test(3, deleteSize_test(), "deleteSize_test");
    test(-1, emptyTraverse_test(), "emptyTraverse_test");

    printf("\n\nYou passed %d out of %d tests", points, numTests);
    printf("\n\n");

    return 0;
}
