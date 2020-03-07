/**
 * @param {string} s
 * @return {number}
 */
var lengthOfLongestSubstring = function(s) {
    let max = 0, count = 1, l = s.length;
    if(l == 0) return 0;
    if(l == 1) return 1;
    for(var i = 1; i < l; i++){
        let same = repetition(s, i, count);
        max = ( same > 0 && count > max ) ? count : max;    /* If rep and count is greater, set max */
        count = ( same > 0 ) ? same : count + 1;            /* If rep reset count else increment it */
    } max = ( count > max ) ? count : max;
    return max;
};

/**
 * Iterate over characters within count and find repetitions
 * @param {string} s
 * @param {num} l
 * @param {num} c
 * @return {num}
 */
var repetition = function(s, l, c) {
    for(var i = l-c; i < l; i++){
        if(s[i] == s[l]) return l - i;                      /* If repetition is found return difference */
    } return 0;
};