## Description

Implementation of a Red-Black tree ADT in C. A red-black tree is a self balancing binary search tree with each node having a color property (red or black) to facilitate the balance of the tree during insertions and deletions. Also provided a test suite for the ADT with ten unit tests that displays the specific test name, whether you passed the test, displays your ouput and the expected output if you failed that test, and then gives you a score of how many test you passed out of fifteen.



## Usage

Store the folder Red_Black_Tree in your terminal and use the command "make" to make a binary executable called Order for the file called Order.c. Then, just use the command "Order in1 out1" and then open the generated file called "out1". Order.c is meant to show the user the three different tree traversals (pre-order, in-order, and post-order) by performing each tree traversal on the Red-Black-Tree that was created from the contents of the file "in1". To run the test suite and check it for memory leaks/errors using valgrind, use the command: "make check1".

