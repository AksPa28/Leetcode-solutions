/*
    You are given an integer n.

    A number is called digitorial if the sum of the factorials of its digits is equal to the number itself.

    Determine whether any permutation of n (including the original order) forms a digitorial number.

    Return true if such a permutation exists, otherwise return false.

    Note:

    The factorial of a non-negative integer x, denoted as x!, is the product of all positive integers 
    less than or equal to x, and 0! = 1.
    A permutation is a rearrangement of all the digits of a number that does not start with zero. 
    Any arrangement starting with zero is invalid.
    

    Example 1:
    Input: n = 145
    Output: true
    Explanation:
    The number 145 itself is digitorial since 1! + 4! + 5! = 1 + 24 + 120 = 145. Thus, the answer is true.

    Example 2:
    Input: n = 10
    Output: false
    Explanation:​​​​​​​
    10 is not digitorial since 1! + 0! = 2 is not equal to 10, and the permutation "01" is invalid 
    because it starts with zero.

    Constraints:

    1 <= n <= 109
*/

#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define mod 1000000007

static int factorial[10] = {1,1,2,6,24,120,720,5040,40320,362880};

class Solution {
public:
    bool isDigitorialPermutation(int n) {
        int temp = n;
        int factorial_sum = 0;
        vector<int> digit_count(10, 0);
        while(temp){
            int digit = temp % 10;
            factorial_sum += factorial[digit];
            temp /= 10;
            digit_count[digit]++;
        }
        while(factorial_sum){
            int digit = factorial_sum % 10;
            if(digit_count[digit] == 0){
                return false;
            }
            digit_count[digit]--;
            factorial_sum /= 10;
        }
        for(int i = 0; i<10; i++){
            if(digit_count[i] != 0){
                return false;
            }
        }
        return true;
    }
};