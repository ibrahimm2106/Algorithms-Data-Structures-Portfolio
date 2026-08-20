# Data structures

## Queue — String Processor

Coursework 1 processes tokens strictly from left to right, so a FIFO queue is a natural fit.

```mermaid
flowchart LR
    A[Input tokens] --> B[Queue]
    B --> C[Read first string]
    C --> D{Next operator}
    D -->|+| E[Concatenate operand]
    D -->|-| F[Remove operand characters]
    E --> G{More tokens?}
    F --> G
    G -->|Yes| D
    G -->|No| H[Final string]
```

## Linked lists — Online Store

Three singly linked lists model the state of purchases:

```mermaid
flowchart LR
    A[Current purchases] -->|processPurchase| B[Processed purchases]
    A -->|returnPurchase| C[Returned purchases]
```

Each purchase node stores customer ID, customer name, purchased item, purchase date and a pointer to the next node.

## Hash table

The alphabet hash table has 26 buckets. The hash function is:

```text
index = ord(lowercase_letter) - ord('a')
```

Repeated letters are retained in the bucket, demonstrating **chaining**.

## Binary search tree

Unique letters are inserted according to lexical order:

- smaller → left subtree
- greater → right subtree
- duplicate → ignored

An in-order traversal therefore returns the stored letters in sorted order.
