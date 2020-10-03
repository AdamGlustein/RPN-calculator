#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


struct stack* create_stack(){ 
    struct stack* pointer = (struct stack*)malloc(sizeof(struct stack));
    pointer->top = NULL;
    pointer->size = 0;
    return pointer;
}

void delete_stack(struct stack* st){
    // delete recursively
    // base case: size = 0, delete pointer to stack
    if (st->size == 0){
        free(st);
    }
    else{ // remove pointer to last entry
        struct stack_entry* last = st->top;
        for (int i = 0; i < st->size-1; i++){
            last = last->next;
        }
        free(last);
        st->size--;
        delete_stack(st); // recursive call
    }
}

double pop(struct stack* st){
    // remove top of stack and return
    if (st->size == 0 || st->top == NULL || st == NULL){
        return 0;
    }
    else {
        // retrieve first element, first pointer, change stack's pointer to 2nd (freeing first) and return stored el
        double popper = (double)st->top->value; // typecast from float to double
        struct stack_entry* tmp = st->top; 
        st->top = st->top->next; 
        free(tmp);
        st->size--; 
        return popper; 
    }
}

int push(struct stack* s, double e){
    if (s == NULL){
        return -1;
    }
    // create stack_entry, change pointers accordingly 
    struct stack_entry* new = (struct stack_entry*)malloc(sizeof(struct stack_entry));
    new->value = (float)e;
    new->next = s->top; 
    s->top = new;
    s->size++;
    return 0; 
}
