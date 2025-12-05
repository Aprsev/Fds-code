# Binary Search Tree (BST) Pair Sum Program

This program implements Binary Search Trees (BST) and finds pairs of values from two different BSTs that sum up to a given target value.

## Files Included
- `bst.h`: Header file containing the BST node structure and function prototypes
- `bst.c`: Implementation of the BST operations
- `main.c`: Main program that handles input/output and uses the BST operations
- `Makefile`: Build configuration for compiling the program

## Prerequisites
- GCC compiler (or another C compiler)
- Make utility (for using the Makefile)

## Building the Program
To build the executable, follow these steps:

1. Open a terminal in the directory containing the source files
2. Run the following command:
   ```
   make
   ```
3. This will compile the program and create an executable named `bst_program`

If you want to clean up the compiled object files and executable, use:
```
make clean
```

## Running the Program
To run the program:
```
./bst_program
```

## Input Format
The program expects input in the following format:

1. First line: `n1` (number of nodes in the first BST)
2. Next `n1` lines: `value parent_index` for each node in the first BST
   - `parent_index` is -1 for the root node
3. Next line: `n2` (number of nodes in the second BST)
4. Next `n2` lines: `value parent_index` for each node in the second BST
   - `parent_index` is -1 for the root node
5. Last line: `target` (the target sum value)

### Example Input:
```
3
10 -1
5 0
15 0
4
20 -1
10 0
30 0
25 2
35
```

## Output Format
The program outputs:

1. "true" if at least one pair of values summing to the target exists, "false" otherwise
2. For each pair found: `target = value1 + value2`
3. Preorder traversal of the first BST
4. Preorder traversal of the second BST

### Example Output:
```
true
35 = 5 + 30
35 = 10 + 25
35 = 15 + 20
10 5 15
20 10 30 25
```

## Program Description
This program:
1. Constructs two Binary Search Trees from the input values and parent indices
2. Searches for pairs of values (one from each tree) that sum to the given target
3. Sorts and displays the found pairs
4. Displays the preorder traversal of both trees
5. Properly frees allocated memory