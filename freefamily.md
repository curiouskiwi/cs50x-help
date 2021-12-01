**FAQ: I don't get how you use recursion to free the entire family?**

Perhaps look at the `print_family` function for inspiration.
See how it takes in a `person` pointer `p`  and then calls itself for `p`'s parents?
That's the same idea for `free_family`.  In order to free a person, you have to free `p`'s parents.
When you call `free_family` on the parent, that parent becomes "p" and the function runs again and
again until there is no longer a `p` because there are no more ancestors in the tree.
In our example with generations = 3, that means there are 7 people that should be freed.

```
D  E   F  G
  B     C
     A
```

we call `free_family` on A  (which is stored in `p`) That then calls `free_family`on B and on C
(ie, the `parent[0]` and `parent[1]` of `p`).

So `free_family(B)` runs and calls free_family on B's parents (ie, `parent[0]` and `parent[1]` of `p`.
On B, that then recursively calls `free_family` on D and on E (ie, the `parent[0]` and `parent[1]` of `p`),
and since D and E don't have parents, the function frees `p` which is D, rewinds to where it left off (on E),
frees E and keeps moving back down until we end up freeing every person.
