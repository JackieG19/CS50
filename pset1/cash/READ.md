# Cash 
https://docs.cs50.net/2018/x/psets/1/cash/cash.html

When using a device like this, odds are you want to minimize the number of coins you’re dispensing for each customer, 
lest you have to press levers more times than are necessary. Fortunately, computer science has given cashiers everywhere 
ways to minimize numbers of coins due: greedy algorithms.

According to the National Institute of Standards and Technology (NIST), a greedy algorithm is one "that always takes the best 
immediate, or local, solution while finding an answer. Greedy algorithms find the overall, or globally, optimal solution for 
some optimization problems, but may find less-than-optimal solutions for some instances of other problems."

What’s all that mean? Well, suppose that a cashier owes a customer some change and on that cashier’s belt are levers that 
dispense quarters, dimes, nickels, and pennies. Solving this "problem" requires one or more presses of one or more levers. 
Think of a "greedy" cashier as one who wants to take, with each press, the biggest bite out of this problem as possible. 
For instance, if some customer is owed 41¢, the biggest first (i.e., best immediate, or local) bite that can be taken is 25¢. 
(That bite is "best" inasmuch as it gets us closer to 0¢ faster than any other coin would.) Note that a bite of this size would
whittle what was a 41¢ problem down to a 16¢ problem, since 41 - 25 = 16. That is, the remainder is a similar but smaller 
problem. Needless to say, another 25¢ bite would be too big (assuming the cashier prefers not to lose money), and so our greedy
cashier would move on to a bite of size 10¢, leaving him or her with a 6¢ problem. At that point, greed calls for one 5¢ bite 
followed by one 1¢ bite, at which point the problem is solved. The customer receives one quarter, one dime, one nickel, and one
penny: four coins in total.

It turns out that this greedy approach (i.e., algorithm) is not only locally optimal but also globally so for America’s 
currency (and also the European Union’s). That is, so long as a cashier has enough of each coin, this largest-to-smallest 
approach will yield the fewest coins possible. How few? Well, you tell us!
