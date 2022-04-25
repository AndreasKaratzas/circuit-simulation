
# Combinational Circuit Logic Simulation Tool

### Objective

Implement a logic simulation tool in `C` language for combinational circuits. Logic simulation is defined as the process of applying values at the primary inputs (input vector) and observe and report the values at the primary outputs (output response).

### Input Files

1. `.isc`: This file is the encoding of the combinational circuit layout.
2. `.vec`: This file contains information about the input vectors (values at the primary inputs). Each line in this file is a input vector. Each character is an input of the circuit. A character can take values:
    * `0`: logic zero
    * `1`: logic one
    * `x`: don't care value. During simulation, the `x` is interpreted as `2`.

### Exercises

1. Understand how the data structures and graphs have been programed. Structure `NODE` is an adjacency list where for each node we have linked lists of all its predecessor and successor nodes that represent `Fan_in` and `Fan_out` of that node.

![adjacency-list](docs/adjacency-list-representation.webp)

2. Traverse the graph `G`. The nodes are already labeled in topological order. The focus will be to learn how to traverse a linked list for each node `V`.

3. Create arrays to store the truth tables for the three basic functions:
    * OR
    * AND
    * NOT

4. Determine the logic values at the output of node `V` after traversing the linked list of its predecessors.

5. Apply the input pattern to the primary input of circuit and propagate these values to the primary output of the circuit.

### Submission

Simulate every input vector and report the corresponding logic responses at the primary outputs for all given circuits. The input pattern and its output response should be saved in an output file. Submission requires:
1. All the program code files.
2. Generated result file for each combinational circuit (one file with input pattern and its output response). The output file contains all the information in the order exactly as the given .vec file.

## TODO

- [ ] `traverse_circuit()`
- [ ] `cache_or_truth_table()`
- [ ] `cache_and_truth_table()`
- [ ] `cache_not_truth_table()`
- [ ] `forward_propagate()`
- [ ] `simulate_circuit()`
- [ ] `load_circuit()`
- [ ] `load_test_vector()`
- [ ] `main()`
