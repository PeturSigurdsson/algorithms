/**
 * Divides two integers by left shifting |divisor| while it is <= half 
 * the value of the |dividend|, shifting the quotient with it.
 *  Then it right shifts the quotient to further add to it, right 
 * shifting the divisor and subtracting from  the dividend
 * until the divisor is greater than the  the dividend. 
 * @param{int} dividend
 * @param{int} divisor
 * @return{int} resulting quotient of integer division
*/
int divide(int dividend, int divisor){
    /* Special cases */
    if(divisor == 0 || (dividend == INT_MIN && divisor == -1)) return INT_MAX;
    
    /* transform to unsigned long */
    bool sign = (dividend > 0)^(divisor > 0);
    unsigned long A = labs(divisor);
    unsigned long B = labs(dividend);
    
    /* Can't divide */
    if(B < A) return 0;
    
    unsigned long Q = 1;            /* Special cases dealt with if it's here it's at least 1 */
    unsigned long run = A;          /* Used to left shift unsigned copy of divisor */
    unsigned long goal = B >> 1;    /* Half of unsigned dividend */
    
    while(run <= goal){             /* Compares run to precalculated goal */
        run <<= 1;
        Q <<= 1;
    } 
    unsigned long r = Q;            /* Reference quotient after left shifting */
    Q = 0;                          /* We will add to it from zero in loop */
    while(run){
        switch(B >= run){           /* Add to Q if dividend is >= than divisor */
            case true:
                Q += r;             /* Add reference to quotient */
                B -= run;           /* Subtract left shifted divisor from dividend (copies) */
                break;
        }
        run >>= 1;                  /* Right shift left shifted divisor */
        r >>= 1;                    /* Right shift reference */
    } return sign ? -Q : Q;
}

