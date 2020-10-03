#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calc.h"
#include "stack.h"

double compute_rpn(char* rpn){
	// push numbers onto stack, pop off with each operation 
	struct stack* num_stack = create_stack();
	// printf("%s", "check1"); 
	char *tok = strtok(rpn, " ");
	while(tok) {
		if (unary_op(*tok)) {
			// printf("%s", "unary op called");
			double od = pop(num_stack);
			if (*tok == 's') push(num_stack, sin(od));
			else if (*tok == 'c') push(num_stack, cos(od));
			else if (*tok == 't') push(num_stack, tan(od));
			else if (*tok == 'e') push(num_stack, exp(od));
			else if (*tok == 'i' && od != 0) push(num_stack, 1/od);
			else if (*tok == 'm') push(num_stack, -1*od);
			else if (*tok == 'r') push(num_stack, sqrt(od));
			tok = strtok(NULL, " ");
		}
		else if (binary_op(*tok)) {
			double od1 = pop(num_stack);
			double od2 = pop(num_stack); 
			if (*tok == '+') push(num_stack, od1+od2);
			else if (*tok == '-') push(num_stack, od2-od1);
			else if (*tok == '*') push(num_stack, od1*od2);
			else if (*tok == '/' && od1 != 0) push(num_stack, od2/od1);
			else if (*tok == '^') push(num_stack, pow(od2, od1));
			else if (*tok == 'f'){
				push(num_stack, od1);
				push(num_stack, od2);
			}
			tok = strtok(NULL, " ");
		}
		else { // number 
			push(num_stack, atof(tok));
			tok = strtok(NULL, " ");
		}
	}
	double final = (double)num_stack->top->value;
	delete_stack(num_stack);
	return final;
}

char* get_expressions(char* filename){
	FILE *file_pointer = fopen(filename, "r");
	char file_line[256];
	char* return_arr = (char*)calloc(100, sizeof(file_line));
	int true_size = 0;
	while (fgets(file_line, sizeof(file_line), file_pointer) != NULL) {
		strcat(return_arr, file_line);
		true_size += sizeof(file_line)/sizeof(char);
	}
	// now trim what's not needed
	char* new_arr = (char*)calloc(true_size, sizeof(char));
	for (int i = 0; i < true_size; i++){
		new_arr[i] = return_arr[i]; 
	}
	free(return_arr);
	fclose(file_pointer);
	return new_arr;
}

void process_expressions(char* expressions, char* filename){
	FILE *output_pointer = fopen(filename, "w");
	// go line by line, parsing at /n to get new expressions and print each 
	char *rest = expressions; 
	char* exp = strtok_r(rest, "\n", &rest);
	while (exp){
		double n = compute_rpn(exp);
		char result[30];
		sprintf(result, "%g", n);
		fputs(result, output_pointer);
		fputs("\n", output_pointer);
		exp = strtok_r(NULL, "\n", &rest);
	}
	free(expressions);
	fclose(output_pointer); 
	
}