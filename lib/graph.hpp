
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

#include "utils.hpp"

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
    int  marker, correct_value, fault_value;
    LIST *fanin, *fanout;
} NODE;

typedef struct PATTERN_type
{
    char primary_input_vec[MAX_NUM_OF_PRIMARY_INPUTS];
} PATTERN;

typedef struct FAULT_type
{
    int target_node, target_value;
} FAULT;

void insert_element(LIST **, int);
void print_list(LIST *);
void delete_element(LIST **);
int read_isc_file(FILE *, NODE *);
void initialize_circuit(NODE *, int);
int map_logic_gate(char *);
void print_circuit(NODE *, int);
void delete_circuit(NODE *, int);
int read_vec_file(FILE *, PATTERN *);