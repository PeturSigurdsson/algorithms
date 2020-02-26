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
        //count = same ? count : count + 1;             /* If repetition occurs don't increment */
        max = ( same > 0 && count > max ) ? count : max;    /* If rep and count is greater, set max */
        count = (same > 0) ? same : count + 1;
    } max = ( count > max ) ? count : max;
    return max;
};

var repetition = function(s, l, c) {
    for(var i = l-c; i < l; i++){
        if(s[i] == s[l]) return l - i;
    } return 0;
};