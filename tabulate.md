**FAQ:  I'm not sure how the whole Tabulate process is meant to work in Runoff. I've watched the Walkthrough but I'm still confused!**

To complete tabulate, you have to have a clear understanding of what the preferences array is showing you.  Let's review that first.

The preferences array holds the preferences for each voter.  So, voter 0 (the first voter)'s preferences are in `preferences[0]`.  Voter 1 (the second voter)'s preferences are in `preferences[1]`.  etc etc.
Now, preferences is a 2d array, which means that each voters preferences are in a row.  And the columns in that row represent the order of their preferences.  So column 0 is their first preferred candidate.  Column 1 is their second preferred candidate, etc etc
So if I have `preferences[2][3]`, that would be the 3rd voter's 4th preference.

Say we've got 4 candidates.  `candidates[0]` is Alice, `candidates[1]` is Bob, `candidates[2]` is Charlie and `candidates[3]` is David.

If voter 0 ranked his votes for Bob, then Charlie, then Alice, then David, say, in our `vote` function, we'd have set `preferences[0][0]` to  hold the index value of the candidate named Bob (1), `preferences[0][1]` to 2, `preferences[0][2]` to 0 and `preferences[0][3]` to 3.

So in **tabulate** our goal is to update the candidates vote totals based on those preferences. We want to loop over the entire preferences array (recall that the first index represents the voter and the second the rank and we'll therefore need nested loops -- first for the voters and then for the candidates) and for each one of those combinations (ie, `preferences[0][0]`, then `preferences[0][1]` ... ) we want to check if the candidate stored there has been eliminated or not.  And if not, then we want to increment the vote count for that candidate.  We don't want to count any more votes for that voter (since we only want to count the vote for the highest ranked candidate), so we need to end the inner loop (recall that `break` will let you do that).

So in our example let's assume that Bob has previously been eliminated.
My loop starts and to make for a bit less typing, I'm going to store the preference in its own variable called "voted_for".
So voted_for is set to the value in `preferences[0][0]` which is 1.  Now I check if `candidates[1]` is eliminated.  He is, so my loop runs again.  I set voted_for to the value in `preferences[0][1]`  which is 2.

Now I check if `candidates[2]` is eliminated.  He's not, so I increment `candidates[2]`'s vote total and I'm done with voter 0, so I break out of the inner loop.   Now my outer loop increments, and I start over with `preferences[1]`  and repeat the entire thing, getting voter 1's top preference, etc etc.

Once I've completed the loop for the last voter, I'm done.
