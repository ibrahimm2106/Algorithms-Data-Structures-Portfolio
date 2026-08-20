# Testing

## Python

Run all automated tests from the repository root:

```bash
python -m unittest discover -s tests -v
```

The test suite covers:

- all four String Processor coursework cases;
- Merge, Quick and Insertion Sort against Python's reference `sorted` result;
- Dijkstra distances and the `A → C → F` shortest path;
- hash-table chaining and membership;
- BST ordering and duplicate handling.

## C++

```bash
cmake -S cpp -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

The C++ test checks the full coursework workflow: add nine purchases, return the first purchase, sort by customer ID, process positions 2 and 4, and search for customer ID 25.

## Continuous integration

GitHub Actions repeats the Python and C++ checks on every push and pull request to `main`.
