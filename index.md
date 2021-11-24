## Hints for CS50x problem sets

### Problem Set 3 - Tabulate

[FAQ: I'm not sure how the whole Tabulate process is meant to work in Runoff. I've watched the Walkthrough but I'm still confused!](tabulate.md)


### Problem Set 4 - Filter

You may find it easier to debug your filters using a smaller bitmap file than the ones given in the distribution code.

* A small [3x3 bitmap](3x3.bmp) 
* A small [3x3 bitmap for Edges](3e.bmp)
* A small [4x4 bitmap](4x4.bmp)
* A small [4x4 bitmap for Edges](4e.bmp)

### Problem Set 4 - Recover

[FAQ: What does that final condition in the JPG signature check mean?](bitwise.md)


### Problem Set 5 - Speller

A simple [hash function you can try](hash.c)

### Problem Set 7 - Finance

Sometimes you may want to test your quote/buy/sell/index functions using prices/stocks that you know won't change.  Or, the IEX API may be acting up and isn't returning any values.  In these cases, a temporary `lookup` function in `helpers.py` works well.  Open `helpers.py` and comment out the `lookup` function and then paste in this [lookup function for testing](lookup_finance.py)


## Final Project

Be sure that your README.md is comprehensive enough, per the requirements shown in the specification.  Here's an [example of a project README file](finalproject_sampleREADME.md) that I did for my own project years ago. 

## Other Concepts you might need to know

I created a string like `string word = "hello";`[Why do I segfault when trying to change a character in that string?](stringliteral.md)

## Just for Fun ##

Wondering how to display the binary representation of a hex number?  Here's my [hex to binary converter in C](hexbin.c).
