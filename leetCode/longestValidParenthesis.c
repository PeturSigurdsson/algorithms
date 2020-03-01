/**
 * Structure I can use like a stack
 */
struct stack {
    unsigned short top;
    unsigned short size;
    short* data;
};

/**
 * Push to top of stack, increases size if necessary
 * @param{struct stack*} s: Stack holds invalid places
 * @param{unsigned short} n: Number new invalid place
 */
void push(struct stack* s, unsigned short n);

/**
 * Like pop but the value is ignored
 * @param{struct stack*} s: Stack holds invalid places
 */
void chuck(struct stack* s);

/**
 * Finds longest valid parenthesis by treating open ones as a stack.
 * If a closing parenthesis comes along, it pops an open from the 
 * stack, decreasing the negative value that is to be subtracted from the
 * final result. 
 * @param{char*} s: A string of parentheses.
 * @return{int}
 */
int longestValidParentheses(char * s){
    char initialSize = 10;                          /* Initial size can affect speed and memory */
    unsigned short i = 0;                           /* Increments with place in string */
    unsigned short max = 0;                         /* Current max valid parenthesis */
    short* d = malloc(sizeof(short)*initialSize);   /* Heap allocated array of shorts */
    struct stack place = {1, initialSize, &d[0]};   /* Stack structure initialized with top at 1 */
    place.data[1] = -1;                             /* First top value is -1 for cases where all opens are closed */
    bool o, e;                                      /* Bools for open and empty */
    while(*s){                                      /* While the char is not null char*/
        o = *s == '(';                              /* Is this an open */
        switch(o){                                  /* Switch to avoid branching */
            case true:
                push(&place,i);                     /* Push to place in string to stack */
                break;
            case false:
                chuck(&place);                      /* Pop last one from stack */
                e = place.top == 0;                 /* Check if stack is empty */
                switch(e){                          /* Only gets used if it's a close */
                    case true:
                        push(&place,i);             /* Push place to stack if empty */
                        break;
                    case false:                     /* If it's not empty max can be recalculated */
                        max = (max > i - place.data[place.top]) ? max :  i - place.data[place.top];
                        break;
                }
                break;
        }
        i++;                                        /* Increment place in string */
        s++;                                        /* Increment string pointer */
    } return max;
}

void push(struct stack* s, unsigned short n){
    s->top++;                                       /* Increment top */
    bool small = s->top >= s->size;                 /* Check if it's too small */
    switch(small){                                  /* No branching! */
        case true :{                                /* Case needs own scope to initialize variables */
            unsigned short newSize = s->size * 2;   /* Increase size of stack */
            short* data = s->data;
            short* d = malloc(sizeof(short)*newSize);
            memcpy(d,data,s->size*sizeof(short));
            s->data = &d[0];                        /* Set new array to stack */
            s->size = newSize;                      /* Set new size to stack */
            break;
        }                                           /* Don't need the other case */
    }
    s->data[s->top] = n;                            /* Finally push invalid place to stack */
}

void chuck(struct stack* s){
    s->top = (s->top > 0) ? s->top - 1 : s->top;    /* Decrement top if it is greater than zero */
}