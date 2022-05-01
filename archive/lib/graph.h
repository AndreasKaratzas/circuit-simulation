
#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <time.h>
#include <complex.h>
#include <assert.h>
#include <limits.h>

#include "utils.h"

#define MAX_FILENAME_SIZE                20
#define MAX_NUM_OF_NODES              15000
#define MAX_NUM_OF_CHARACTERS_IN_LINE   200
#define MAX_NODE_ALIAS_LEN               25
#define MAX_LOGIC_GATE_ID                10
#define MAX_FAN_OUT                      16
#define MAX_FAN_IN                        9
#define MAX_NUM_OF_PRIMARY_INPUTS       233
#define MAX_NUM_OF_PRIMARY_OUTPUTS      140
#define MAX_NUM_OF_TEST_VECTORS          10
#define MAX_NUM_OF_STUCK_AT_FAULTS       10

#define INPT 1              // Primary Input
#define AND  2
#define NAND 3
#define OR   4
#define NOR  5
#define XOR  6
#define XNOR 7
#define BUFF 8
#define NOT  9
#define FROM 10             // STEM BRANCH


typedef struct LIST_type
{
    int id;                 // id of loaded element
    struct LIST_type *next; // pointer to next element (default: NULL)
} LIST;


typedef struct NODE_type
{
    char name[MAX_NODE_ALIAS_LEN];
    int  type, num_of_fan_ins, num_of_fan_outs, primary_output;
    int  correct_value, fault_value;
    LIST *fanin, *fanout;
} NODE;

typedef struct PATTERN_type
{
    int *primary_input_vec;
    int num_of_primary_inputs;
    int current_primary_input;
} PATTERN;

typedef struct PATTERN_bak_type
{
    char primary_input_vec[MAX_NUM_OF_PRIMARY_INPUTS];
} PATTERN_bak;

typedef struct FAULT_type
{
    int address;
    int fault;
} FAULT;

typedef struct LOGGER_type
{
    int index;
    char *input_vector;
    char *correct_output;
    int fault_address;
    int fault_value;
    char *faulty_output;
    char fault_detected[20];
} LOGGER;

void insert_element(LIST **, int);
int print_list(LIST *);
void delete_element(LIST **);
int read_isc_file(FILE *, NODE *, int *);
void initialize_circuit(NODE *, int);
int map_logic_gate(char *);
void print_circuit(NODE *, int);
void delete_circuit(NODE *, int);
int read_vec_file_bak(FILE *, PATTERN_bak *);

void unknown_handler(int);
void from_handler(NODE *, char *, int);
void gate_handler(FILE *, NODE *, int, int, int*);

void map_pattern(char *, int *, int);
int read_vec_file(FILE *, PATTERN *);
void print_vectors(PATTERN *, int);
void delete_vectors(PATTERN *, int);

int read_faults_file(FILE *, FAULT *);
void print_faults(FAULT *, int);
void inject_fault(NODE *, int, int, int);

int complementary(int);
int compute_and_correct(NODE *, int);
int compute_and_fault(NODE *, int);
int compute_or_correct(NODE *, int);
int compute_or_fault(NODE *, int);
int compute_xor_correct(NODE *, int);
int compute_xor_fault(NODE *, int);
void map_not(NODE *, int);
void map_and(NODE *, int);
void map_nand(NODE *, int);
void map_or(NODE *, int);
void map_nor(NODE *, int);
void map_xor(NODE *, int);
void map_xnor(NODE *, int);
void map_buffer(NODE *, int);
void map_from(NODE *, int);

void register_simulation(NODE *, int, PATTERN *, int, int, int, int, LOGGER *, int, int);
void log_simulation(FILE *, LOGGER *, int, int, int *, char *);
int get_original_node_address(int *, int);
void log_description(FILE *, char *);
void get_benchmark_name(char *, const char *);

void apply_input(NODE *, int, PATTERN *, int);
void simulate_node(NODE *, int, PATTERN *, int);
void simulate_circuit(NODE *, PATTERN *, FAULT *, LOGGER *, int, int, int, int *, int);
void reset_circuit(NODE *, int);
void reset_pattern(PATTERN *, int);
