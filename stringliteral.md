**Why do I segfault when trying to change the string?**

Let's look at this sample program called uppercase.c:

```C
#include <stdio.h>
#include <ctype.h>

int main(void)
{
    // create a string and initialize to "hello"
    char *name = "hello, world!";

    // capitalize the first letter
    name[0] = toupper(name[0]);
 }
```

If we were to run this, it would segfault.  Why?

What you've done is to declare a "string literal" (literally hardcoding it in your code).  When you do so, it gets stored in "read-only" memory, which can't be changed. 
You can see evidence of this by compiling your code with `clang -S uppercase.c` (which will produce the assembler code). Open `uppercase.s and you should see:   

```asm
	.text
	.file	"uppercase.c"
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movabsq	$.L.str, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movsbl	(%rax), %edi
	callq	toupper
	xorl	%edi, %edi
	movb	%al, %cl
	movq	-8(%rbp), %rdx
	movb	%cl, (%rdx)
	movl	%edi, %eax
	addq	$16, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"hello, world!"
	.size	.L.str, 14


	.ident	"clang version 7.0.0 "
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym toupper
```

The key lines to pay attention to are these near the bottom: 

```asm
.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"hello, world!"
	.size	.L.str, 14
```

Notice how `"hello, world!"` is in the `.rodata` section of the program, aka read-only data. 

Attempting to change read-only data will result in a segmentation fault.

More here: https://en.wikipedia.org/wiki/Data_segment.

So how to solve this?  If you want a string that you can change, you can declare it as a char array instead:

```C
char name[] = "hello";
```
