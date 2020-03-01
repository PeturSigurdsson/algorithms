unsigned short min(unsigned short a, unsigned short b, unsigned short c);
int iterativeLev(char* s1, char* s2);

/**
 * MinDistance calls levenstein algorithm to calculate edit distance between two strings
 * @param{char*} word1: word to edit
 * @param{char*} word2: word to reproduce
 * @return{int} number of insert, replace or deletes necessary to reproduce word1 with 2
*/
int minDistance(char * word1, char * word2){
    return iterativeLev(word1, word2);
}

/**
 * Gives minimum value of three. Since edit distance has three possibilities.
 * @param{unsigned short} a: First  value
 * @param{unsigned short} b: Second value
 * @param{unsigned short} c: Third  value
 * @return{unsigned short} smallest value
*/
unsigned short min(unsigned short a, unsigned short b, unsigned short c){ 
    return (a < b) ? (a < c) ? a : c : (b < c) ? b : c;         /* 33.3% chance of correct branch prediction */
}

/**
 * Used for debugging. Prints out given matrix of unsigned short values.
 * @param{unsigned short*} m: Flat matrix reference
 * @param{unsigned short} l1: Number of rows
 * @param{unsigned short} l2: Number of columns
 */
void printMatrix(unsigned short* m, unsigned short l1, unsigned short l2){
    unsigned short i, j;
    for(i = 0; i < l1; i++){
        for(j = 0; j < l2; j++)
            printf(" %u ",m[i*l2 + j]);
        printf("\n");
    }
}

/**
 * Iterative implementation of levenstein algorithm.
 * Builds array on the stack to hold edit distances
 * @param{char*} s1: String to edit
 * @param{char*} s2: String to reproduce
 * @return{int}  Returns the last value in array.
 */
int iterativeLev(char* s1, char* s2){
    unsigned short l1 = strlen(s1) + 1, l2 = strlen(s2) + 1;    /* Size of strings + 1 */
    unsigned int size = l1 * l2;                                /* Size of array */
    /* Flat matrix holds initial position of each letter 
     * on the top and left edges.
     * e.g:       h o p e
     *           0 1 2 3 4   for s1 of length 2 and 
     *         o 1 0 0 0 0   s2 of length 4.
     *         r 2 0 0 0 0
     */
    unsigned short mat [size];
    memset(mat, 0x0, sizeof(mat));                              /* Set array values to zero */
    
    unsigned short i,j;                                         /* Instantiate incrementors */
    unsigned int r;                                             /* Instantiate row position */
    
    for(i = 1; i < l2; i++) mat[i] = i;                         /* Set the edge values */
    for(j = 1; j < l1; j++) mat[j*l2] = j;

    char cost;                                                  /* Variable cost if letter match or not */
    for(i = 1; i < l1; i++){
        r = i * l2;                                             /* Set row position */
        for(j = 1; j < l2; j++){
            cost = (s1[i-1] == s2[j-1]) ? 0 : 1;                /* Find cost */
            mat[r+j] = min(                                     /* Edit distance is the minimum of  */
                mat[r - l2 + j  ] + 1,                          /* all adjacent distances that have */
                mat[r      + j-1] + 1,                          /* previously been evaluated e.g.   */
                mat[r - l2 + j-1] + cost                        /*     h o p e    insert h          */
            );                                                  /*   0 1 2 3 4    /                 */
        }                                                       /* o 1 1 1 2 3    replace r with p  */
    } return mat[size-1];                                       /* r 2 2 2 2 3    insert e          */
}


