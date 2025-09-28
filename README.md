
# CS 4280 (P0) — BST by Frequency (C)

Builds a Binary Search Tree (BST) whose keys are **frequencies** (how many times a token appears).
Each node holds all strings that occurred exactly that many times, listed in the order of their **first appearance** in the input.

## Invocation

```bash
# Read from keyboard (stdin) until EOF
./P0

# Redirect from a file (tests keyboard input path)
./P0 < somefile.fs25s2

# Read from a named file (the program appends the required extension .fs25s2)
./P0 somename     # reads somename.fs25s2
```
Output files:
- `out.preorder`, `out.inorder`, `out.postorder` when reading from stdin
- `<somename>.preorder`, `<somename>.inorder`, `<somename>.postorder` when reading from the file

## Build (Delmar/UMSL Linux)

```bash
make clean && make
```

- Uses `gcc` with `-std=c11 -Wall -Wextra -O2`.
- No external libraries.

## Behavior and Assumptions

- Input is whitespace-separated **tokens** (spaces, tabs, newlines).
- Tokens must be **alphanumeric only** (`[A-Za-z0-9]+`). Invalid tokens are **warned** to `stderr` and **skipped** (+validation).
- The tree’s structure is a BST keyed by **frequency** only.
  - All tokens that ultimately occur `k` times live in the node with key `k`.
  - Within a node, tokens are printed in the order of their **first appearance** in the whole input.
- The program never rebalances the tree. Nodes are created per frequency as needed.

## Files

- `P0.c` — main, CLI parsing, input handling, file naming, error handling
- `tree.h`, `tree.c` — BST by frequency with traversals/printing
- `node.h` — Node type definition
- `Makefile` — builds `P0`

## Submission

Use the course-provided submit command (adjust path as required):

```bash
/accounts/classes/janikowc/submitProject/submit_cs4280s2_P0 P0_project
```

Or if submitting the single binary with sources, package as directed by your instructor.

## Testing

```bash
# Example:
echo "a a b c c c d1 D1 e e f2 f2 f2 f2 bad$token Z" | ./P0

# Produces:
# out.preorder
# out.inorder
# out.postorder
# and prints warnings for invalid tokens to stderr
```
