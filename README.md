# CS4280 — Project P0 (BST by Frequency)

Build a binary search tree from input tokens where the key is the token frequency. Tokens with the same frequency share a node whose payload is an ordered list of the tokens (in first-appearance order).

## Invocation
```
P0               # read tokens from keyboard/STDIN until EOF; outputs: out.*
P0 < somefile    # same as above but via shell redirection
P0 baseName      # reads tokens from baseName.fs25s2; outputs: baseName.*
```

## Build
```
make
make clean
```

## Notes
- Validation: non-alphanumeric tokens are skipped with a warning.
- BST not balanced, keyed only by frequency.
