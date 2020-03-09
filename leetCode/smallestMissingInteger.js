/**
 * 44ms (<99.13%) 33.8MB (<91.67%)
 * @param {number[]} nums
 * @return {number}
 */
var firstMissingPositive = function(nums) {
    let smallest = 1;
    while(true) {
        switch(nums.includes(smallest)){ 
            case false:
                return smallest;
            case true:
                smallest++;
        }
    } return smallest;
};

/**
 * 44ms (<99.13%) 34.2MB (<83.33%)
 * @param {number[]} nums
 * @return {number}
 */
var firstMissingPositive = function(nums) {
	const obj = nums.reduce((a,b) => {a[b] = 1; return a;},{});
    let smallest = 0;
    while(obj[++smallest]) {} return smallest;
};

/**
 * 44 ms (<99.13%) 35.3MB (<16.67%)
 * @param {number[]} nums
 * @return {number}
 */
var firstMissingPositive = (arr) => {
	const nums = arr.sort((a,b) => a-b).filter((a,i,arr) => (a != arr[i-1] && a > 0));
    let smallest = 1;
    while(true){
        switch(smallest == nums[smallest-1]){
            case false:
                return smallest;
            case true:
                smallest++;
        }
    } return smallest;
};