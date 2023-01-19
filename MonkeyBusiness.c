#include <stdio.h>
#include <stdlib.h>
/*
 * Yuto Kikuchi
 * COP3502C
 */
#define INVALID -1
typedef struct Node Node;
typedef struct Stack Stack;
typedef struct answer answer;
Node * createNode(int id,int nmonkey);
Node * insertHead(Node * head, int value, int nmonkey);
void push(Stack * s, int id, int nmonkey);
Node * removeHead(Node * head);
void pop(Stack *);
int top(Stack * s);
struct Node {
    int ID; // each node contains ID and num monkeys
    int nmonkey;
    Node * next; // set to next
};
struct Stack { // create head
    Node * head;
};
struct answer { // stores ans
    int ans;
};
Node * insertHead(Node * head, int value, int nmonkey) { //Functions from meades notes
    Node * newHead = createNode(value, nmonkey);
    newHead->next = head;
    return newHead;
}
Node * createNode(int id,int nmonkey) { // take in id and monkey
    Node * res = (Node *) malloc(sizeof(Node));
    res->next = NULL;
    res->ID = id;
    res->nmonkey = nmonkey;
    return res;
}
void push(Stack * s, int id,int nmonkey) { // push into stack id and monkey
    s->head = insertHead(s->head, id, nmonkey);
}
void pop(Stack * s) { // pops
    s->head = removeHead(s->head);
}
Node * removeHead(Node * head) { //remove head for pop
    if (head == NULL)
        return NULL;
    Node * newHead = head->next;
    free(head);
    return newHead;
}
int top(Stack * s) {
    if (s->head == NULL) return INVALID;
    return s->head->nmonkey;
}


int main() {
    int nexhibit; // # of exhibits
    int id; // the id
    int nmonk; // # of monkeys
    Stack *stack = (Stack *)malloc(sizeof(Stack)); // create a stack
    stack->head = NULL; //set head = NULL
    int track =0; // tracks the # of monkeys

    scanf("%d", &nexhibit); // scanf
    answer *result = (answer*)malloc(sizeof(answer)*nexhibit); // stores the monkeys to each exhibit
    result[0].ans = 0; // set the first ans to 0
    stack->head = (Node*)malloc(sizeof(Node)*nexhibit); //create stack based on num of exhibits
    for (int i=0; i<(2*nexhibit)-1; i++) { // for loop
        scanf("%d", &id); // scan id
        if (id != -1) { // if id does not = -1
            //push
            scanf("%d", &nmonk); // scan the second part
            push(stack, id, nmonk); // push both values

            result[id].ans = nmonk + track;
            track += nmonk;
        } else {
            //pop
            track -= top(stack); // subtract the top stack to get previous
            pop(stack); // then pop

        }
    }
    int visit;
    int guest =0;
    scanf("%d", &guest); //scans how many guests
    for (int i=0; i<guest; i++) { //for loop
        scanf("%d", &visit); // scan visit
        printf("%d\n", result[visit].ans); // output visit
    }

    for (int i=0; i<nexhibit; i++) { // free stack
        pop(stack);
    }
    free(stack); // free
    free(result); // free the results
    return 0;
}