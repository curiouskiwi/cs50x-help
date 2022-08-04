**FAQ:  How do the functions work to do the greedy algorithm?** 

The individual functions don't "know" anything about the greedy algorithm.  They exist to simply return the number of coins for a given number of cents.  You'll see that in `main`, it is calculating how many cents to send to each function based on the number of coins it has already got (and the leftover cents amount it needs).  So if your user asks for 65 cents, then main first calls `calculate_quarters(65)`.  That function will return 2, so main then says "`2*25` is 50.  that would leave 15."  It then calls `calculate_dimes(15)` and it returns 1 etc. etc. until it's called all the functions and sums them up at the end.

Each function is entirely independent of the others.

So if I say "tell me how many nickels I can get from 50 cents" your function `calculate_nickels(50)` should return 10.
Remember, the idea with using functions is to *abstract* away the implementation so that function could be used in any circumstance.  Maybe the calling function (ie, main in this case) knew that the cashier had run out of quarters and dimes.  So main only called your calculate_nickels and calculate_pennies functions.

That's not the scenario here, of course, but you should be letting main makes those decisions.  That code was already written for you.
