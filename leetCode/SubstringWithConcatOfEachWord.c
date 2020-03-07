struct node{
    char* key;
    char value;
    struct node* next;
};

struct node* get(char* key, struct node** table, unsigned short l);
struct node* add(char* key, struct node** table, unsigned short l);
unsigned short digest(char* s, unsigned short l);

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findSubstring(char * s, char ** words, int wordsSize, int* returnSize){
    *returnSize = 0;
    int* result;
    unsigned short sl = strlen(s);                              /* String length of s */
    if(sl == 0 || wordsSize == 0) return result;                
    char wl = strlen(*words);                                   /* Length of individual words */
    unsigned short pl = wordsSize * wl;                         /* Permutation length */
    if(pl > sl) return result;
    unsigned short ssl = sl - pl;                               /* Number of possible substrings */
    unsigned short hl = wordsSize * 18;
    
    struct node** table = calloc(hl, sizeof(struct node*));     /* Keep hashtable of words */

    for(unsigned short i = 0; i < wordsSize; i++){
        struct node* n = add(words[i], table, hl);              /* Add every word to hashtable */
        n->value += 1;                                          /* Increment value for each repetition */
    }

    char** ssarr[sl*(wl+1)];                                    /* Keep all possible substrings in array */
    char* ss;
    for(unsigned short i = 0; i < sl-wl+1; i++){ 
        ss = malloc((wl+1));
        strncpy(ss, s + i, wl);
        ss[wl] = '\0';
        ssarr[i] = ss;    
    }
    result = malloc((ssl+1)*sizeof(int));                       /* Allocate for all possible indices*/


    unsigned short sel = sl - pl + 1;                           /* search length */


    unsigned short i = 0, j, k;                                 /* initialize incrementors */

    while(i < sel) {                                            /* shortest search loop */
        ss = ssarr[i];              
        struct node* ssn = get(ss,table,hl);                    /* Substring node */

        if(ssn){                
            struct node* narr[wordsSize];                       /* Node array */
            narr[0] = ssn;                                      /* Keep all modified nodes in array */
            ssn->value -= 1;                                    /* Modify node of found strings */
            for(j = 1; j < wordsSize; j++){             
                ss = ssarr[i+j*wl];                             /* Compare substrings with proper interval */
                ssn = get(ss,table,hl);                         /* Look for word in hashmap */
                switch(ssn && ssn->value > 0) {
                    case false:
                        for(k = 0; k < j; k++) {
                            ssn = narr[k];                      /* Undo changes to nodes */
                            if(ssn) ssn->value += 1;
                        }
                        j--;
                        break;
                    case true:
                        ssn->value -= 1;                        /* Modify node if it is not empty */
                        narr[j] = ssn;                          /* Keep it for reset later */
                        continue;
                }
                break;
            }
            if(j >= wordsSize - 1){
                result[*returnSize] = i;               
                *returnSize += 1;
                for(k = 0; k < j; k++) {
                    ssn = narr[k];
                    if(ssn) ssn->value += 1;                    /* Reset all nodes */
                }
            } 
        }
        i++;
    }
    
    return result;
}

/**
 * Finds node with correct key and returns pointer to it or null pointer
 * @param{char*} key: string used as key for hashmap
 * @param{strct node*} table: array of linked list nodes
 * @param{unsigned short} l: length of table
 * @return{ struct node*} linked list node
 */
struct node* get(char* key, struct node** table, unsigned short l){
    unsigned short hash = digest(key, l);
    struct node* current = table[hash];
    if(current){
        while(current && strcmp(current->key, key) != 0) current = current->next;
    } return current;
}

/**
 * Adds node to hashtable if it's not present and returns it.
 * @param{char*} key: string used as key for hashmap
 * @param{strct node*} table: array of linked list nodes
 * @param{unsigned short} l: length of table
 * @return{ struct node*} linked list node
 */
struct node* add(char* key, struct node** table, unsigned short l){
    
    unsigned short hash = digest(key, l);
    
    struct node* newNode = (struct node*) malloc(sizeof(struct node));    /* Create new node */
    newNode->key = key;
    newNode->value = 0;
    newNode->next = NULL;
    struct node* current = table[hash];             /* Get current node in table */
    if(current){                                    /* If it's not null */
        struct node* prev;
        while(current) {                            /* Look for the key, */
            if(strcmp(current->key, key) == 0){     
                return current;
            }
            prev = current;                         /* if it's not found, append it */
            current = (current->next) ? current->next : NULL;
        } prev->next = newNode;
    } else table[hash] = newNode; 
    return newNode;
}

/**
 * xors every char in s together and return the result mod l
 * @param{char*} s: string to digest
 * @param{unsigned short} l: length og hashmap
 * @return{unsigned short} hash
 */
unsigned short digest(char* s, unsigned short l){
    unsigned short result = *s;
    char i = 1;
    while(*(s + i) != '\0'){
        result ^= *(s + i);
        i++;
    } return result % l;
}