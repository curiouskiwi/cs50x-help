**FAQ: I don't understand the Caesar formula and how the modulo 26 fits in.  Why do we use that?**

The caesar cipher formula  `(p + k) % 26` works on the premise that `p` (the plain text character) has a value of 0 - 25  (representing a - z or A - Z)

So if your plain char is 'x', that would have a value of 23, and if your key was 2, then the ciphered char would be 
  ``` 
    (23 + 2) % 26
    (  25  ) % 26
    = 25  'z'
```
If the key was 10
```
    (23 + 10) % 26
    (  33   ) % 26
    = 7   'h'
```
The modulo works here in the same way it works on an analog clock, which is  `% 12` because if it's 10 o'clock and you had 4 hours, you don't get 14 o'clock, you get 14%12 = 2 o'clock.

So your code should take the plainchar, convert it from the ASCII range down to a value from 0 to 25  (simply through subtraction), add the key, modulo the result by 26, and then convert that back up to the ASCII range for printing.
