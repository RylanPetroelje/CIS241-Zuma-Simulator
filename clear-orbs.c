#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>

typedef struct { // Geeks for Geeks
        char ch;
        int count;
} StackItem; // Alias

typedef struct { 
        StackItem* ptr;
        int size;
        int top;
} Stack;


void push(Stack* stack, StackItem item);
StackItem* pop(Stack* stack);
StackItem* peek(Stack* stack);
void dump(Stack* stack);

int main(void){ 
        size_t maxZuma = 0;

        char* zumaBuffer = NULL;

        while (getline(&zumaBuffer, &maxZuma, stdin) != -1){ //When EOF is reached -1 is returned
                int insertVal;
                char insertChar;

                if (scanf("%d %c", &insertVal, &insertChar) != 2) { //If two inputs arent passed, break
                        break; 
                }
                
                char* newZuma = (char*)malloc(strlen(zumaBuffer)+2); // Need two to account for null termintor and inserted char

                for (int i=0; i < (strlen(zumaBuffer) + 1); i++){
                        if(i > insertVal) newZuma[i] = zumaBuffer[i-1];
                        if(i == insertVal) newZuma[i] = insertChar;
                        if(i < insertVal) newZuma[i] = zumaBuffer[i];
                }
                newZuma[strlen(zumaBuffer) + 1] = 0;

                //printf("%s\n", newZuma);

                // This is where things get funky
                Stack stack;
                stack.top = -1; // We use this to measure the size of the stack for 
                                // later pointer arithmetic
                stack.size = strlen(newZuma);
                stack.ptr = (StackItem*)malloc(sizeof(StackItem) * stack.size);

                StackItem tmp;
                char current;
                char lastChar = newZuma[0];
                int count = 1;
                for (int i = 1; i < strlen(newZuma); i++) {
                        current = newZuma[i];
                        if (current == lastChar) {
                                count++;
                        } else {
                        if (count >= 3) {
                                // Do nothing, don't put on the stack.
                        } else {
                                // Count is less than 3, check the top item on the stack..
                                StackItem* top = peek(&stack);
                                if (top != NULL && top->ch == lastChar) {
                                        // If the top item on the stack is the same as the character
                                        // we're currently processing, then check how many we have total
                                        // (count from the stack + current count)
                                        if (top->count + count >= 3) {
                                                // If we have more than 3 total, then we can
                                                // pop this character off the stack.
                                                pop(&stack);
                                        } else {
                                                // Don't have more than 3 (yet), update the
                                                // count on the stack.
                                                top->count = top->count + count;
                                        }
                                } else {
                                        // Top is either null or a different character than
                                        // the one we are currently looking at in the string
                                        // so we need to push the current character & count
                                        // on to the stack.
                                        tmp.count = count;
                                        tmp.ch = lastChar;
                                        push(&stack, tmp);
                                }  
                        } 

                        count = 1;
                        lastChar = current;
                        }
                        //dump(&stack);
                }

                int totalCount = 0;

                if (stack.top >= 0) {
                        for (StackItem* ptr = stack.ptr; ptr <= (stack.ptr + stack.top); ptr++) {
                                totalCount += ptr->count;
                        }
                }


                printf("%d\n", totalCount);
                getchar(); // Need to account for the output char otherwise it thinks its a getline

                free(newZuma);
                free(stack.ptr);
        }

        free(zumaBuffer);
        //free(insertBuffer);
        return 0;
}

void push(Stack *stack, StackItem item) {
        if (stack->top >= (stack->size) - 1) {
                //printf("Stack Overflow");
                return;
        }

        stack->top++;
        StackItem* topPtr = stack->ptr + stack->top;
        if (topPtr != NULL){
                topPtr->ch = item.ch;
                topPtr->count = item.count;
        }
}

StackItem* pop(Stack* stack) {
        if (stack->top < 0) {
                //printf("Stack Underflow");
                return NULL;
        }

        return stack->ptr + stack->top--; //stack->ptr points to the beginning of the stack
}

StackItem* peek(Stack* stack) {
        if (stack->top < 0) {
                //printf("Stack is empty!\n");
                return NULL;
        }

        return stack->ptr + stack->top;
}
// Debugging
// void dump(Stack* stack) {
//         for(StackItem* ptr = stack->ptr; ptr <= stack->ptr + stack->top; ptr++) {
//                 printf("['%c', %d] ", ptr->ch, ptr->count);
//         }
//         printf("\n");
// }

/*
 * 1. Allocate the memory
 *      a. Have getline allocate memory for us
 *      b. 16 bytes for the second string (%d %c) (might not
 *         even have to dynamically allocate)
 *
 * 2. Read standard input
 *      a. getline for the first line because length varies
 *      b. scanf for the second string because we know it
 *         will be 3 values every time (int, space, char)
 * 
 * 3. Place the letter into the desired index
 *      a. Will have to shift every index after insertion
 *         over 1 byte in memory
 *      b. Could also make a new array. Would have to
 *         allocate more data.
 * 
 * 4. Check for runs of 3 or more of the same letter
 *      a. Keep a count, when it encounters a different
 *         char, reset counter to 1
 *      b. Can't just stop at 3, must account for runs of 4
 *         or 5 too. Will probably have to check count 
 *         upon requiring a reset to know where the run ends
 *      
 * 5. Upon deletion, shift all chars to the right over the 
 *    amount taken out.
 *      a. Could do this recursively (maybe)?
 *
 * 6. Repeat steps 4 and 5 until \0 or EOF or NULL reached.
 *
 * 7. Return the length of final string
 *      a. sizeof(arr)/sizeof(arr[0])
 *
 *
 *
 */
