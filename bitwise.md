**FAQ:  What does that final condition in the JPG signature check mean?**

```C
if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
```

The `&` is the bitwise AND operator.  It can be used as a "mask" to let us concentrate on only some bits in a number.  When you AND two bits together, the result is 1 if both bits are set to 1, otherwise it's 0.  

Per the spec:
> The fourth byte, meanwhile, is either `0xe0`, `0xe1`, `0xe2`, `0xe3`, `0xe4`, `0xe5`, `0xe6`, `0xe7`, `0xe8`, `0xe9`, `0xea`, `0xeb`, `0xec`, `0xed`, `0xee`, or `0xef`. Put another way, the fourth byte’s first four bits are `1110`.

So, in other words, we want to check that the first 4 bits of the byte are `1110`.  We can do this by 'masking' away the final four bits.  The value `0xf0`  (`11110000`) works well for this since it has all first 4 bits and last 4 bits off.  So the result of any number ANDed with it will have its last 4 bits off no matter what, so we can concentrate on the first 4 bits only.  

Let's look at an example.  Say that `buffer[3]` is equal to `0xe6`.

```
0xe6        11100110
0xf0        11110000
0xe6 & 0xf0 11100000 (that's 0xe0)  so that's a match
```

or, say that `buffer[3]` is `0xc7`

```
0xc7        11000111
0xf0        11110000
0xc7 & 0xf0 11000000 (that's 0xc0) so that's not a match
```
Using the bitwise AND in our condition is a quick way to compare one number to a range of others in one step.

More information about bitwise in C: https://en.wikipedia.org/wiki/Bitwise_operations_in_C
