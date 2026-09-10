# Best Time to Buy and Sell Stock

Problem: [LeetCode](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/)

You are given an array `prices` where `prices[i]` is the price of a given stock on the i-th day.

You want to maximize your profit by choosing a **single day** to buy one stock and choosing a **different day in the future** to sell that stock.

Return the *maximum profit you can achieve* from this transaction. If you cannot achieve any profit, return `0`.

Example 1:  
Input: $prices = [7,1,5,3,6,4]$  
Output: $5$  
Explanation: Buy on day 2 ($price = 1$) and sell on day 5 ($price = 6$), profit = $6-1 = 5$.  
Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.

Example 2:  
Input: $prices = [7,6,4,3,1]$  
Output: $0$  
Explanation: In this case, no transactions are done and the max profit $= 0$.

## Solution
We are told that $1 \le \text{prices.length} \le 10^{5}$ and that $0 \le \text{prices[i]} \le 10^{4}$.  

Since we must buy before selling, we can use two local variables `minPrice` and `maxProfit`.  
These are initially set as `minPrice = INT_MAX` and `maxProfit = 0`.  

We then scan the array `prices` and update them whenever we find a lower price to buy, or we find a day to sell on which we obtain a higher profit.  

#### Pseudocode
```cpp
int maxProfit(vector<int>& prices) {

    if (prices.empty()) {
        return 0;
    }

    int minPrice = INT_MAX;
    int maxProfit = 0;

    for (int i = 0; i < (int)prices.size(); i++) {

        if (prices[i] < minPrice) {
            minPrice = prices[i];
        }
        else if (prices[i] - minPrice > maxProfit) {
            maxProfit = prices[i] - minPrice;
        }
    }

    return maxProfit;
}
```

#### Complexity
Since we are only doing a linear scan, the total **time complexity** is $\Theta(n)$,  
where $n$ is the total number of elements in `prices`.

Since we pass `prices` by reference, the total **space complexity** remains constant $\Theta(1)$.
