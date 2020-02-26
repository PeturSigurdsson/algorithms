/**
 * @param {string} s
 * @return {string}
 */
var longestPalindrome = function(s) {
    var l = s.length;                           /* Modifyable length */
    if(l < 2) return s;                         /* Empty string and single char return as is */
    var max = { half: 0, size: 0, place: 0 },   /* Max holds index, size and size/2 */
        sso = { same: 0, size: 0, place: 0 };   /* Substring holds repetitions, size and index */
    for(var i = 0; i < l; i++){
        l = (l-i < max.half)? i : l;            /* Avoids branching */
        checkIndex(s, i, sso);                  /* Build palindrome from s[i] */
        checkMax(max, sso)                      /* Check if it beats max */
        i += sso.same;                          /* Don't check repetitions */
    } return s.slice(                           /* Slice string with info in max and return it */
        max.place-((max.size-max.same)>>1), 
        1+max.place+max.same+((max.size-max.same)>>1)
    );
};

/**
 * Calls up and expand to set members of sso
 * @param {string} s
 * @param {num} i
 * @param {object} sso
 */
var checkIndex = function(s, i, sso) {
    var o = up(s, i);                           /* Gives number of repetitions */
    sso.place = i;                              /* Set current index */
    sso.size = expand(s, i, o);                 /* Set size of palindrome */
    sso.same = o;                               /* Set repetition offset */
}

/**
 * Checks if sso holds longer palindrome than max
 * @param {object} max
 * @param {object} sso
 */
var checkMax = function(max, sso) {
    if(sso.size < max.size) return;             /* Retrun if not longer */
    max.size = sso.size;                        /* Set members of max with sso */
    max.half = sso.size >> 1;                   /* Fast division by 2 */
    max.same = sso.same;
    max.place = sso.place;
}

/**
 * Expands up and down string to find size of palindrome
 * @param {string} s
 * @param {num} i
 * @param {num} o
 * @return {num}
 */
var expand = function(s, i, o){
    var ss = o + 1;                             /* Size is repetion offset + current char */
    var j = 1;                                  /* Start by expanding by 1 in both dirs */
    const r = i + o;                            /* Current index + offset */
    var l = s.length;
    while(r+j < l){
        var same = (s[r+j] == s[i-j]);          /* Check if both sides are equal */
        ss = same ? ss + 2 : ss;                /* if so add to substring size */
        l = same ? l : 0;                       /* if not destroy loop condition*/
        j++;                                    /* increment expansion */
    } return ss;
};

/**
 * Count length of repetitions from index i
 * @param {string} s
 * @param {num} i
 * @return {num}
 */
var up = function(s, i){
    var l = 0;                                  /* start count at 0 */
    while(s[i++] == s[i]) l++;                  /* while next char == current char increment length */
    return l;                                   
};