
# Combinational Circuit Logic Simulation Tool

### Objective

Implement a logic simulation tool in `C` language for combinational circuits. Logic simulation is defined as the process of applying values at the primary inputs (input vector) and observe and report the values at the primary outputs (output response).

### Input Files

1. `.isc`: This file is the encoding of the combinational circuit layout.
2. `.vec`: This file contains information about the input vectors (values at the primary inputs). Each line in this file is a input vector. Each character is an input of the circuit. A character can take values:
    * `0`: logic zero
    * `1`: logic one
    * `x`: don't care value. During simulation, the `x` is interpreted as `2`.
3. `.faults`: This file contains information about the fault nodes and its struck at value of a particular circuit. Each line in this file is about the single stuck-at fault. Example:
    * `3\1` &#8594; gate with the id `3` has struck-at the value `1`

### Exercises

1. Understand how the data structures and graphs have been programed. Structure `NODE` is an adjacency list where for each node we have linked lists of all its predecessor and successor nodes that represent `Fan_in` and `Fan_out` of that node.

![adjacency-list](docs/adjacency-list-representation.webp)

2. Traverse the graph `G`. The nodes are already labeled in topological order. The focus will be to learn how to traverse a linked list for each node `V`.

3. Create arrays to store the truth tables for the three basic functions:
    * AND
    * NAND
    * OR
    * NOR
    * XOR
    * XNOR
    * INV
    * BUFFER

4. Determine the logic values at the output of node `V` after traversing the linked list of its predecessors.

5. Apply the input pattern to the primary input of circuit and propagate these values to the primary output of the circuit.

6. Write a function to read the `.faults` file and store the information in the `FAULT` structure.

7. Take a single input vector in the `PATTERN` structure

8. Apply the input pattern to the primary input of the circuit (`x` is mapped to `2`) and propagate these values to the primary output of the circuit. The response obtained at the primary outputs is called __fault free__ response of the circuit.

9. Print the input vector, input vector after `x` has been mapped, and output response for each pattern in the output file.

10. Build a single fault in the `FAULT` structure. Inject the faut in the particular node and propagate the faulty value to the primary output. The output response obtained after injecting the fault is called __faulty__ response of the circuit.

11. Compare the __fault free__ and the __faulty__ response to identify whether the fault at particular node is identified by the given input pattern or not.

12. Log whether the fault is detected or not in the output file.

13. Repeat the steps 10 - 12 for each fault in the `FAULT` structure for the single input pattern. 

14. Repeat steps 7 - 12 for each input vector in the `PATTERN` structure of the given circuit.

### Submission

Simulate every input vector and report the corresponding logic responses at the primary outputs for all given circuits. The input pattern and its output response should be saved in an output file. Submission requires:
1. All the program code files.
2. Generated result file for each combinational circuit (one file with input pattern and its output response). The output file contains all the information in the order exactly as the given .vec file.

## TODO

- [ ] create a `PATTERN` structure
- [ ] create a `FAULT` structure
- [ ] `traverse_circuit()`
- [ ] `cache_logic_gates()`
- [ ] `forward_propagate()`
- [ ] `simulate_circuit()`
- [ ] `load_circuit()`
- [ ] `load_test_vector()`
- [ ] `read_faults_file()` : Ignore whitespace
- [ ] `load_pattern()`
- [ ] `load_fault()`
- [ ] `trace_error()`
- [ ] `test_circuit()`
- [ ] `log_pattern_simulation()`
- [ ] `log_faults_simulation()`
- [ ] `store_results()`
- [ ] `main()`
