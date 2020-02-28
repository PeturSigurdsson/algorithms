struct stack {
    unsigned short top;
    unsigned short size;
    short* data;
};

void push(struct stack* s, unsigned short n);

void chuck(struct stack* s);

int longestValidParentheses(char * s){
    char initialSize = 10;
    unsigned short i = 0;
    unsigned short max = 0;
    short* d = malloc(sizeof(short)*initialSize);
    struct stack place = {1, initialSize, &d[0]};
    place.data[1] = -1;
    bool o, e;
    while(*s){
        o = *s == '(';
        switch(o){
            case true:
                push(&place,i);
                break;
            case false:
                chuck(&place);
                e = place.top == 0;
                switch(e){
                    case true:
                        push(&place,i);
                        break;
                    case false:
                        max = (max > i - place.data[place.top]) ? max :  i - place.data[place.top];
                        break;
                }
                break;
        }
        i++;
        s++;
    } return max;
}

void push(struct stack* s, unsigned short n){
    s->top++;
    bool small = s->top >= s->size;
    switch(small){
        case true :{
            unsigned short newSize = s->size * 2;
            short* data = s->data;
            short* d = malloc(sizeof(short)*newSize);
            memcpy(d,data,s->size*sizeof(short));
            s->data = &d[0];
            s->size = newSize;
            break;
            }
            case false:
            break;
    }
    s->data[s->top] = n;
}

void chuck(struct stack* s){
    s->top = (s->top > 0) ? s->top - 1 : s->top;
}