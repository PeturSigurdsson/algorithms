/**
 * Util for permutations. Checks if the last word in the array has
 * a doppelganger. If so, this recursion can be avoided.
 * @param{char**} words: Array of strings
 * @param{unsigned short} place: Recursive position in array
 * @param{unsigned short} l: length of array
 * @return{bool} false if doppelganger is found
 */
bool need(char** words, unsigned short place, unsigned short l){
    char* s = *(words+l);
    bool result = true;
    for(unsigned short i = place; i < l && result; i++){
        result = strcmp(*(words + i), s);
    } return result;
}

/**
 * Recursive algorithm modifies array in place to create all permutations.
 * Complexity: O(n!) where n is the length of the array
 * @param{char**} words: Array of strings
 * @param{unsigned short} place: Recursive position in array
 * @param{unsigned short} l: length of array
 */
void permutations(char** words, unsigned short place, unsigned short l){   
    switch(place >= l) {
        case false:
            for (unsigned short i = place; i < l; i++) {
                switch(need(words, place, i)){
                    case true:{
                        char* tmp = *(words + place);
                        *(words + place) = *(words+i);
                        *(words+i) = tmp;
            
                        permutations(words, place + 1, l);
            
                        *(words + i) =*(words + place);
                        *(words + place) = tmp;
                        
                    } break;
                }
            } break;
        case true:{
            /* Run code on permutation */
        }
    }
}