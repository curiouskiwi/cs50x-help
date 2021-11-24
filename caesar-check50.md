**FAQ: Caesar `check50` says I'm failing, but it looks right to me**

If you get a `check50` result that looks like you are printing exactly what is required (like this screenshot), the most common problem is that your program might be printing "invisible" characters.

When the terminal is in your caesar directory, try running this command:

```./caesar 13 <<< 'Hello, world' | cat -A```

The `<<<` operator sends a string (on its right) into the command on its left, as though the user had typed it in after starting the program.

The vertical bar (`|`) is called the "pipe" operator because it pipes the output of one command into the input of another. In the above example, the second of those commands is `cat -A`. It simply emits its input as output, except that for characters that don't normally show up on the screen, it substitutes visible alternatives.

If all is well, you'd expect to see 

```
plaintext: ciphertext: Tqxxa, iadxp$
```

The `$` at the end signifies the end of the output.

If you see anything else after `iadxp`, then you are printing extra char(s). If this is the case, have a look at your loop that controls the printing of the ciphered text.  Are you sure it is running the correct number of times?
