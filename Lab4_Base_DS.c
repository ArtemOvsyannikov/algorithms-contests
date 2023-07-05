/*
TASK 1. Stack/Arithmetic expressions
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 10000

typedef struct Stack {
    int top;
    int size;
    int *array;
} Stack;

Stack *createStack(int size) {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->size = size;
    stack->top = -1;
    stack->array = (int *) malloc(stack->size * sizeof(int));
    return stack;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, int item) {
    stack->array[++stack->top] = item;
}

int pop(Stack *stack) {
    return stack->array[stack->top--];
}

int top(Stack *stack) {
    return stack->array[stack->top];
}

int main() {
    Stack *answer = createStack(SIZE);
    Stack *operatorStack = createStack(SIZE);
    char input[SIZE] = {0};
    fgets(input, SIZE, stdin);

    printf("Expression:\n%s\n", input);
    printf("Reverse Polish Notation:\n");

    for (int i = 0; input[i] != '\n' && input[i] != '\0'; i++) {
        if (input[i] >= '0' && input[i] <= '9') {
            int number = 0;
            while (input[i] >= '0' && input[i] <= '9') {
                number = number * 10 + (input[i] - '0');
                i++;
            }
            push(answer, number);
            printf("%d ", number);
            i--;
        } else if (input[i] == '+' || input[i] == '-') {
            while (!isEmpty(operatorStack) && top(operatorStack) != '(') {
                printf("%c ", top(operatorStack));
                push(answer, pop(operatorStack));
            }
            push(operatorStack, input[i]);
        } else if (input[i] == '*' || input[i] == '/') {
            while (!isEmpty(operatorStack) && (top(operatorStack) == '*' || top(operatorStack) == '/')) {
                printf("%c ", top(operatorStack));
                push(answer, pop(operatorStack));
            }
            push(operatorStack, input[i]);
        } else if (input[i] == '(') {
            push(operatorStack, input[i]);
        } else if (input[i] == ')') {
            while (!isEmpty(operatorStack) && top(operatorStack) != '(') {
                printf("%c ", top(operatorStack));
                push(answer, pop(operatorStack));
            }
            pop(operatorStack);
        }
    }

    while (!isEmpty(operatorStack)) {
        printf("%c ", top(operatorStack));
        push(answer, pop(operatorStack));
    }
    printf("\n");

    Stack *numberStorage = createStack(SIZE);

    for (int k = 0; k <= answer->top; k++) {
        if (answer->array[k] == '+') {
            int x1 = pop(numberStorage);
            int x2 = pop(numberStorage);
            push(numberStorage, x2 + x1);
        } else if (answer->array[k] == '*') {
            int x1 = pop(numberStorage);
            int x2 = pop(numberStorage);
            push(numberStorage, x2 * x1);
        } else if (answer->array[k] == '-') {
            int x1 = pop(numberStorage);
            int x2 = pop(numberStorage);
            push(numberStorage, x2 - x1);
        } else if (answer->array[k] == '/') {
            int x1 = pop(numberStorage);
            int x2 = pop(numberStorage);
            push(numberStorage, x2 / x1);
        } else {
            push(numberStorage, answer->array[k]);
        }
    }

    printf("Result:\n%d ", numberStorage->array[0]);

    return 0;
}

/*
TASK 2. Hash Tables
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ll long long
#define N 10000

typedef struct HashTableEntry {
    char key[N];
    ll value;
} HashTableEntry;

ll hash(char *key, ll q, ll p) {
    ll result = 0;
    ll power = 1;
    for (int i = 0; i < strlen(key); i++) {
        result += (key[i] - '`') * power;
        result = result % q;
        power *= p;
        power = power % q;
    }
    return result;
}

void get2(char *key, ll hashValue, HashTableEntry *hashTable, ll q) {
    ll linearProbing = 1;
    while (1) {
        ll newIndex = (hashValue + linearProbing) % q;
        if (linearProbing == q) {
            printf("key=%s hash=%lld operation=GET result=collision linear_probing=%lld value=no_key\n", key, hashValue, newIndex);
            break;
        }
        if (hashTable[newIndex].value == -10000) {
            printf("key=%s hash=%lld operation=GET result=collision linear_probing=%lld value=no_key\n", key, hashValue, newIndex);
            break;
        }
        if (strcmp(hashTable[newIndex].key, key) == 0) {
            printf("key=%s hash=%lld operation=GET result=collision linear_probing=%lld value=%lld\n", key, hashValue, newIndex, hashTable[newIndex].value);
            break;
        }
        linearProbing++;
    }
}

void get(char *key, ll hashValue, HashTableEntry *hashTable, ll q) {
    if (strcmp(hashTable[hashValue].key, key) == 0) {
        printf("key=%s hash=%lld operation=GET result=found value=%lld\n", key, hashValue, hashTable[hashValue].value);
    } else if (hashTable[hashValue].value == -10000) {
        printf("key=%s hash=%lld operation=GET result=no_key\n", key, hashValue);
    } else {
        get2(key, hashValue, hashTable, q);
    }
}

void put2(char *key, ll hashValue, HashTableEntry *hashTable, ll value, ll q) {
    ll linearProbing = 1;
    while (1) {
        ll newIndex = (hashValue + linearProbing) % q;
        if (linearProbing == q) {
            printf("key=%s hash=%lld operation=PUT result=overflow\n", key, hashValue);
            break;
        }
        if (hashTable[newIndex].value <= -10000) {
            printf("key=%s hash=%lld operation=PUT result=collision linear_probing=%lld value=%lld\n", key, hashValue,
                   newIndex,
                   value);
            hashTable[newIndex].value = value;
            strcpy(hashTable[newIndex].key, key);
            break;
        }
        linearProbing++;
    }
}

void put(char *key, ll hashValue,
         HashTableEntry *hashTable,
         ll value,
         ll q) {
    if (hashTable[hashValue].value <= -10000) {
        printf("key=%s hash=%lld operation=PUT result=inserted value=%lld\n", key,
               hashValue,
               value);
        hashTable[hashValue].value = value;
        strcpy(hashTable[hashValue].key,
               key);
    } else {
        put2(key,
             hashValue,
             hashTable,
             value,
             q);
    }
}

void delete2(char *key,
             ll hashValue,
             HashTableEntry *hashTable,
             ll q) {
    ll linearProbing = 1;
    while (1) {
        ll newIndex = (hashValue + linearProbing) % q;
        if (linearProbing == q || hashTable[newIndex].value == -10000) {
            printf("key=%s hash=%lld operation=DEL result=collision linear_probing=%lld value=no_key\n", key,
                   hashValue,
                   newIndex);
            break;
        }
        if (strcmp(hashTable[newIndex].key,
                   key) == 0) {
            strcpy(hashTable[newIndex].key,
                   "");
            hashTable[newIndex].value = -20000;
            printf("key=%s hash=%lld operation=DEL result=collision linear_probing=%lld value=removed\n", key,
                   hashValue,
                   newIndex);
            break;
        }
        linearProbing++;
    }
}

void delete(char *key,
            ll hashValue,
            HashTableEntry *hashTable,
            ll q) {
    if (hashTable[hashValue].value == -10000) {
        printf("key=%s hash=%lld operation=DEL result=no_key\n", key,
               hashValue);
    } else if (strcmp(hashTable[hashValue].key,
                      key) == 0) {
        printf("key=%s hash=%lld operation=DEL result=removed\n", key,
               hashValue);
        hashTable[hashValue].value = -20000;
        strcpy(hashTable[hashValue].key,
               "");
    } else {
        delete2(key,
                hashValue,
                hashTable,
                q);
    }
}

int main() {
    char operation[10];
    char key[N];
    ll q = 0, p = 0, n = 0;
    ll value = 0;
    scanf("%lld %lld %lld", &q, &p, &n);
    HashTableEntry *hashTable = (HashTableEntry *) calloc(q, sizeof(HashTableEntry));
    for (int i = 0; i < q; i++) {
        hashTable[i].value = -10000;
    }
    for (int i = 0; i < n; i++) {
        scanf("%s %s", operation, key);
        if (operation[0] == 'P') {
            scanf("%lld", &value);
            put(key, hash(key, q, p), hashTable, value, q);
        } else if (operation[0] == 'G') {
            get(key, hash(key, q, p), hashTable, q);
        } else if (operation[0] == 'D') {
            delete(key, hash(key, q, p), hashTable, q);
        }
    }
    return 0;
}
