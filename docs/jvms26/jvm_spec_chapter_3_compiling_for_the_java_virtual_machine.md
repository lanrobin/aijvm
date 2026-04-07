<div id="logo">

![Oracle Logo](./images/oralogo_small.gif)  

[Java SE](https://docs.oracle.com/en/java/javase/26/) \> [Java SE
Specifications](../index.html) \> [Java Virtual Machine
Specification](index.html)

</div>

<div class="navheader">

<table style="width:100%">
<thead>
<tr>
<th colspan="3" style="text-align: center;">Chapter 3. Compiling for the
Java Virtual Machine</th>
</tr>
</thead>
<tbody>
<tr>
<td style="text-align: left; width: 20%;"><a href="jvms-2.html"
accesskey="p">Prev</a> </td>
<td style="text-align: center; width: 60%;"> </td>
<td style="text-align: right; width: 20%;"> <a href="jvms-4.html"
accesskey="n">Next</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

</div>

<div id="jvms-3" class="chapter" lang="en">

<div class="titlepage">

<div>

<div>

# Chapter 3. Compiling for the Java Virtual Machine

</div>

</div>

</div>

<div class="toc">

**Table of Contents**

<span class="section">[3.1. Format of
Examples](jvms-3.html#jvms-3.1)</span>

<span class="section">[3.2. Use of Constants, Local Variables, and
Control Constructs](jvms-3.html#jvms-3.2)</span>

<span class="section">[3.3. Arithmetic](jvms-3.html#jvms-3.3)</span>

<span class="section">[3.4. Accessing the Run-Time Constant
Pool](jvms-3.html#jvms-3.4)</span>

<span class="section">[3.5. More Control
Examples](jvms-3.html#jvms-3.5)</span>

<span class="section">[3.6. Receiving
Arguments](jvms-3.html#jvms-3.6)</span>

<span class="section">[3.7. Invoking
Methods](jvms-3.html#jvms-3.7)</span>

<span class="section">[3.8. Working with Class
Instances](jvms-3.html#jvms-3.8)</span>

<span class="section">[3.9. Arrays](jvms-3.html#jvms-3.9)</span>

<span class="section">[3.10. Compiling
Switches](jvms-3.html#jvms-3.10)</span>

<span class="section">[3.11. Operations on the Operand
Stack](jvms-3.html#jvms-3.11)</span>

<span class="section">[3.12. Throwing and Handling
Exceptions](jvms-3.html#jvms-3.12)</span>

<span class="section">[3.13. Compiling
`finally`](jvms-3.html#jvms-3.13)</span>

<span class="section">[3.14.
Synchronization](jvms-3.html#jvms-3.14)</span>

<span class="section">[3.15. Annotations](jvms-3.html#jvms-3.15)</span>

<span class="section">[3.16. Modules](jvms-3.html#jvms-3.16)</span>

</div>

The Java Virtual Machine machine is designed to support the Java
programming language. Oracle's JDK software contains a compiler from
source code written in the Java programming language to the instruction
set of the Java Virtual Machine, and a run-time system that implements
the Java Virtual Machine itself. Understanding how one compiler utilizes
the Java Virtual Machine is useful to the prospective compiler writer,
as well as to one trying to understand the Java Virtual Machine itself.
The numbered sections in this chapter are not normative.

Note that the term "compiler" is sometimes used when referring to a
translator from the instruction set of the Java Virtual Machine to the
instruction set of a specific CPU. One example of such a translator is a
just-in-time (JIT) code generator, which generates platform-specific
instructions only after Java Virtual Machine code has been loaded. This
chapter does not address issues associated with code generation, only
those associated with compiling source code written in the Java
programming language to Java Virtual Machine instructions.

<div id="jvms-3.1" class="section">

<div class="titlepage">

<div>

<div>

## 3.1. Format of Examples

</div>

</div>

</div>

This chapter consists mainly of examples of source code together with
annotated listings of the Java Virtual Machine code that the `javac`
compiler in Oracle’s JDK release 1.0.2 generates for the examples. The
Java Virtual Machine code is written in the informal “virtual machine
assembly language” output by Oracle's `javap` utility, distributed with
the JDK release. You can use `javap` to generate additional examples of
compiled methods.

The format of the examples should be familiar to anyone who has read
assembly code. Each instruction takes the form:

``` screen
<index> <opcode> [ <operand1> [ <operand2>... ]] [<comment>]
```

The `<index>` is the index of the opcode of the instruction in the array
that contains the bytes of Java Virtual Machine code for this method.
Alternatively, the `<index>` may be thought of as a byte offset from the
beginning of the method. The `<opcode>` is the mnemonic for the
instruction's opcode, and the zero or more `<operandN>` are the operands
of the instruction. The optional `<comment>` is given in end-of-line
comment syntax:

``` programlisting
8   bipush 100     // Push int constant 100
```

Some of the material in the comments is emitted by `javap`; the rest is
supplied by the authors. The `<index>` prefacing each instruction may be
used as the target of a control transfer instruction. For instance, a
<span class="emphasis">*`goto 8`*</span> instruction transfers control
to the instruction at index 8. Note that the actual operands of Java
Virtual Machine control transfer instructions are offsets from the
addresses of the opcodes of those instructions; these operands are
displayed by `javap` (and are shown in this chapter) as more easily read
offsets into their methods.

We preface an operand representing a run-time constant pool index with a
hash sign and follow the instruction by a comment identifying the
run-time constant pool item referenced, as in:

``` programlisting
10  ldc #1         // Push float constant 100.0
```

or:

``` programlisting
9   invokevirtual #4    // Method Example.addTwo(II)I
```

For the purposes of this chapter, we do not worry about specifying
details such as operand sizes.

</div>

<div id="jvms-3.2" class="section">

<div class="titlepage">

<div>

<div>

## 3.2. Use of Constants, Local Variables, and Control Constructs

</div>

</div>

</div>

Java Virtual Machine code exhibits a set of general characteristics
imposed by the Java Virtual Machine's design and use of types. In the
first example we encounter many of these, and we consider them in some
detail.

The `spin` method simply spins around an empty for loop 100 times:

``` programlisting

void spin() {
    int i;
    for (i = 0; i < 100; i++) {
        ;    // Loop body is empty
    }
}
```

A compiler might compile `spin` to:

``` programlisting
0   iconst_0       // Push int constant 0
1   istore_1       // Store into local variable 1 (i=0)
2   goto 8         // First time through don't increment
5   iinc 1 1       // Increment local variable 1 by 1 (i++)
8   iload_1        // Push local variable 1 (i)
9   bipush 100     // Push int constant 100
11  if_icmplt 5    // Compare and loop if less than (i < 100)
14  return         // Return void when done
```

The Java Virtual Machine is stack-oriented, with most operations taking
one or more operands from the operand stack of the Java Virtual
Machine's current frame or pushing results back onto the operand stack.
A new frame is created each time a method is invoked, and with it is
created a new operand stack and set of local variables for use by that
method
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>).
At any one point of the computation, there are thus likely to be many
frames and equally many operand stacks per thread of control,
corresponding to many nested method invocations. Only the operand stack
in the current frame is active.

The instruction set of the Java Virtual Machine distinguishes operand
types by using distinct bytecodes for operations on its various data
types. The method `spin` operates only on values of type `int`. The
instructions in its compiled code chosen to operate on typed data
(<span class="emphasis">*iconst_0*</span>,
<span class="emphasis">*istore_1*</span>,
<span class="emphasis">*iinc*</span>,
<span class="emphasis">*iload_1*</span>,
<span class="emphasis">*if_icmplt*</span>) are all specialized for type
`int`.

The two constants in `spin`, `0` and `100`, are pushed onto the operand
stack using two different instructions. The `0` is pushed using an
<span class="emphasis">*iconst_0*</span> instruction, one of the family
of <span class="emphasis">*iconst\_\<i\>*</span> instructions. The `100`
is pushed using a <span class="emphasis">*bipush*</span> instruction,
which fetches the value it pushes as an immediate operand.

The Java Virtual Machine frequently takes advantage of the likelihood of
certain operands (`int` constants <span class="emphasis">*-1*</span>,
<span class="emphasis">*0*</span>, <span class="emphasis">*1*</span>,
<span class="emphasis">*2*</span>, <span class="emphasis">*3*</span>,
<span class="emphasis">*4*</span> and <span class="emphasis">*5*</span>
in the case of the <span class="emphasis">*iconst\_\<i\>*</span>
instructions) by making those operands implicit in the opcode. Because
the <span class="emphasis">*iconst_0*</span> instruction knows it is
going to push an `int` `0`, <span class="emphasis">*iconst_0*</span>
does not need to store an operand to tell it what value to push, nor
does it need to fetch or decode an operand. Compiling the push of `0` as
<span class="emphasis">*bipush*</span> <span class="emphasis">*0*</span>
would have been correct, but would have made the compiled code for
`spin` one byte longer. A simple virtual machine would have also spent
additional time fetching and decoding the explicit operand each time
around the loop. Use of implicit operands makes compiled code more
compact and efficient.

The `int` `i` in `spin` is stored as Java Virtual Machine local variable
<span class="emphasis">*1*</span>. Because most Java Virtual Machine
instructions operate on values popped from the operand stack rather than
directly on local variables, instructions that transfer values between
local variables and the operand stack are common in code compiled for
the Java Virtual Machine. These operations also have special support in
the instruction set. In `spin`, values are transferred to and from local
variables using the <span class="emphasis">*istore_1*</span> and
<span class="emphasis">*iload_1*</span> instructions, each of which
implicitly operates on local variable <span class="emphasis">*1*</span>.
The <span class="emphasis">*istore_1*</span> instruction pops an `int`
from the operand stack and stores it in local variable
<span class="emphasis">*1*</span>. The
<span class="emphasis">*iload_1*</span> instruction pushes the value in
local variable <span class="emphasis">*1*</span> on to the operand
stack.

The use (and reuse) of local variables is the responsibility of the
compiler writer. The specialized load and store instructions should
encourage the compiler writer to reuse local variables as much as is
feasible. The resulting code is faster, more compact, and uses less
space in the frame.

Certain very frequent operations on local variables are catered to
specially by the Java Virtual Machine. The
<span class="emphasis">*iinc*</span> instruction increments the contents
of a local variable by a one-byte signed value. The
<span class="emphasis">*iinc*</span> instruction in `spin` increments
the first local variable (its first operand) by
<span class="emphasis">*1*</span> (its second operand). The
<span class="emphasis">*iinc*</span> instruction is very handy when
implementing looping constructs.

The `for` loop of `spin` is accomplished mainly by these instructions:

``` programlisting
5   iinc 1 1       // Increment local variable 1 by 1 (i++)
8   iload_1        // Push local variable 1 (i)
9   bipush 100     // Push int constant 100
11  if_icmplt 5    // Compare and loop if less than (i < 100)
```

The <span class="emphasis">*bipush*</span> instruction pushes the value
<span class="emphasis">*100*</span> onto the operand stack as an `int`,
then the <span class="emphasis">*if_icmplt*</span> instruction pops that
value off the operand stack and compares it against
<span class="emphasis">*i*</span>. If the comparison succeeds (the
variable `i` is less than `100`), control is transferred to index
<span class="emphasis">*5*</span> and the next iteration of the `for`
loop begins. Otherwise, control passes to the instruction following the
<span class="emphasis">*if_icmplt*</span>.

If the `spin` example had used a data type other than `int` for the loop
counter, the compiled code would necessarily change to reflect the
different data type. For instance, if instead of an `int` the `spin`
example uses a `double`, as shown:

``` programlisting

void dspin() {
    double i;
    for (i = 0.0; i < 100.0; i++) {
        ;    // Loop body is empty
    }
}
```

the compiled code is:

``` programlisting
Method void dspin()
0   dconst_0       // Push double constant 0.0
1   dstore_1       // Store into local variables 1 and 2
2   goto 9         // First time through don't increment
5   dload_1        // Push local variables 1 and 2
6   dconst_1       // Push double constant 1.0
7   dadd           // Add; there is no dinc instruction
8   dstore_1       // Store result in local variables 1 and 2
9   dload_1        // Push local variables 1 and 2
10  ldc2_w #4      // Push double constant 100.0
13  dcmpg          // There is no if_dcmplt instruction
14  iflt 5         // Compare and loop if less than (i < 100.0)
17  return         // Return void when done
```

The instructions that operate on typed data are now specialized for type
`double`. (The <span class="emphasis">*ldc2_w*</span> instruction will
be discussed later in this chapter.)

Recall that `double` values occupy two local variables, although they
are only accessed using the lesser index of the two local variables.
This is also the case for values of type `long`. Again for example,

``` programlisting

double doubleLocals(double d1, double d2) {
    return d1 + d2;
}
```

becomes

``` programlisting
Method double doubleLocals(double,double)
0   dload_1       // First argument in local variables 1 and 2
1   dload_3       // Second argument in local variables 3 and 4
2   dadd
3   dreturn
```

Note that local variables of the local variable pairs used to store
`double` values in `doubleLocals` must never be manipulated
individually.

The Java Virtual Machine's opcode size of 1 byte results in its compiled
code being very compact. However, 1-byte opcodes also mean that the Java
Virtual Machine instruction set must stay small. As a compromise, the
Java Virtual Machine does not provide equal support for all data types:
it is not completely orthogonal
(<a href="jvms-2.html#jvms-2.11.1-220" class="xref"
title="Table 2.11.1-A. Type support in the Java Virtual Machine instruction set">Table 2.11.1-A</a>).

For example, the comparison of values of type `int` in the `for`
statement of example `spin` can be implemented using a single
<span class="emphasis">*if_icmplt*</span> instruction; however, there is
no single instruction in the Java Virtual Machine instruction set that
performs a conditional branch on values of type `double`. Thus, `dspin`
must implement its comparison of values of type `double` using a
<span class="emphasis">*dcmpg*</span> instruction followed by an
<span class="emphasis">*iflt*</span> instruction.

The Java Virtual Machine provides the most direct support for data of
type `int`. This is partly in anticipation of efficient implementations
of the Java Virtual Machine's operand stacks and local variable arrays.
It is also motivated by the frequency of `int` data in typical programs.
Other integral types have less direct support. There are no `byte`,
`char`, or `short` versions of the store, load, or add instructions, for
instance. Here is the `spin` example written using a `short`:

``` programlisting

void sspin() {
    short i;
    for (i = 0; i < 100; i++) {
        ;    // Loop body is empty
    }
}
```

It must be compiled for the Java Virtual Machine, as follows, using
instructions operating on another type, most likely `int`, converting
between `short` and `int` values as necessary to ensure that the results
of operations on `short` data stay within the appropriate range:

``` programlisting
Method void sspin()
0   iconst_0
1   istore_1
2   goto 10
5   iload_1        // The short is treated as though an int
6   iconst_1
7   iadd
8   i2s            // Truncate int to short
9   istore_1
10  iload_1
11  bipush 100
13  if_icmplt 5
16  return
```

The lack of direct support for `byte`, `char`, and `short` types in the
Java Virtual Machine is not particularly painful, because values of
those types are internally promoted to `int` (`byte` and `short` are
sign-extended to `int`, `char` is zero-extended). Operations on `byte`,
`char`, and `short` data can thus be done using `int` instructions. The
only additional cost is that of truncating the values of `int`
operations to valid ranges.

The `long` and floating-point types have an intermediate level of
support in the Java Virtual Machine, lacking only the full complement of
conditional control transfer instructions.

</div>

<div id="jvms-3.3" class="section">

<div class="titlepage">

<div>

<div>

## 3.3. Arithmetic

</div>

</div>

</div>

The Java Virtual Machine generally does arithmetic on its operand stack.
(The exception is the <span class="emphasis">*iinc*</span> instruction,
which directly increments the value of a local variable.) For instance,
the `align2grain` method aligns an `int` value to a given power of 2:

``` programlisting

int align2grain(int i, int grain) {
    return ((i + grain-1) & ~(grain-1));
}
```

Operands for arithmetic operations are popped from the operand stack,
and the results of operations are pushed back onto the operand stack.
Results of arithmetic subcomputations can thus be made available as
operands of their nesting computation. For instance, the calculation of
`~(grain-1)` is handled by these instructions:

``` programlisting
5   iload_2        // Push grain
6   iconst_1       // Push int constant 1
7   isub           // Subtract; push result
8   iconst_m1      // Push int constant -1
9   ixor           // Do XOR; push result
```

First `grain-1` is calculated using the contents of local variable
<span class="emphasis">*2*</span> and an immediate `int` value `1`.
These operands are popped from the operand stack and their difference
pushed back onto the operand stack. The difference is thus immediately
available for use as one operand of the
<span class="emphasis">*ixor*</span> instruction. (Recall that
`~x == -1^x`.) Similarly, the result of the
<span class="emphasis">*ixor*</span> instruction becomes an operand for
the subsequent <span class="emphasis">*iand*</span> instruction.

The code for the entire method follows:

``` programlisting
Method int align2grain(int,int)
0   iload_1
1   iload_2
2   iadd
3   iconst_1
4   isub
5   iload_2
6   iconst_1
7   isub
8   iconst_m1
9   ixor
10  iand
11  ireturn
```

</div>

<div id="jvms-3.4" class="section">

<div class="titlepage">

<div>

<div>

## 3.4. Accessing the Run-Time Constant Pool

</div>

</div>

</div>

Many numeric constants, as well as objects, fields, and methods, are
accessed via the run-time constant pool of the current class. Object
access is considered later (<a href="jvms-3.html#jvms-3.8" class="xref"
title="3.8. Working with Class Instances">§3.8</a>). Data of types
`int`, `long`, `float`, and `double`, as well as references to instances
of class `String`, are managed using the
<span class="emphasis">*ldc*</span>,
<span class="emphasis">*ldc_w*</span>, and
<span class="emphasis">*ldc2_w*</span> instructions.

The <span class="emphasis">*ldc*</span> and
<span class="emphasis">*ldc_w*</span> instructions are used to access
values in the run-time constant pool (including instances of class
`String`) of types other than `double` and `long`. The
<span class="emphasis">*ldc_w*</span> instruction is used in place of
<span class="emphasis">*ldc*</span> only when there is a large number of
run-time constant pool items and a larger index is needed to access an
item. The <span class="emphasis">*ldc2_w*</span> instruction is used to
access all values of types `double` and `long`; there is no non-wide
variant.

Integral constants of types `byte`, `char`, or `short`, as well as small
`int` values, may be compiled using the
<span class="emphasis">*bipush*</span>,
<span class="emphasis">*sipush*</span>, or
<span class="emphasis">*iconst\_\<i\>*</span> instructions
(<a href="jvms-3.html#jvms-3.2" class="xref"
title="3.2. Use of Constants, Local Variables, and Control Constructs">§3.2</a>).
Certain small floating-point constants may be compiled using the
<span class="emphasis">*fconst\_\<f\>*</span> and
<span class="emphasis">*dconst\_\<d\>*</span> instructions.

In all of these cases, compilation is straightforward. For instance, the
constants for:

``` programlisting

void useManyNumeric() {
    int i = 100;
    int j = 1000000;
    long l1 = 1;
    long l2 = 0xffffffff;
    double d = 2.2;
    ...do some calculations...
}
```

are set up as follows:

``` programlisting
Method void useManyNumeric()
0   bipush 100   // Push small int constant with bipush
2   istore_1
3   ldc #1       // Push large int constant (1000000) with ldc
5   istore_2
6   lconst_1     // A tiny long value uses small fast lconst_1
7   lstore_3
8   ldc2_w #6    // Push long 0xffffffff (that is, an int -1)
        // Any long constant value can be pushed with ldc2_w
11  lstore 5
13  ldc2_w #8    // Push double constant 2.200000
        // Uncommon double values are also pushed with ldc2_w
16  dstore 7
...do those calculations...
```

</div>

<div id="jvms-3.5" class="section">

<div class="titlepage">

<div>

<div>

## 3.5. More Control Examples

</div>

</div>

</div>

Compilation of `for` statements was shown in an earlier section
(<a href="jvms-3.html#jvms-3.2" class="xref"
title="3.2. Use of Constants, Local Variables, and Control Constructs">§3.2</a>).
Most of the Java programming language's other control constructs
(`if-then-else`, `do`, `while`, `break`, and `continue`) are also
compiled in the obvious ways. The compilation of `switch` statements is
handled in a separate section
(<a href="jvms-3.html#jvms-3.10" class="xref"
title="3.10. Compiling Switches">§3.10</a>), as are the compilation of
exceptions (<a href="jvms-3.html#jvms-3.12" class="xref"
title="3.12. Throwing and Handling Exceptions">§3.12</a>) and the
compilation of `finally` clauses
(<a href="jvms-3.html#jvms-3.13" class="xref"
title="3.13. Compiling finally">§3.13</a>).

As a further example, a `while` loop is compiled in an obvious way,
although the specific control transfer instructions made available by
the Java Virtual Machine vary by data type. As usual, there is more
support for data of type `int`, for example:

``` programlisting

void whileInt() {
    int i = 0;
    while (i < 100) {
        i++;
    }
}
```

is compiled to:

``` programlisting
Method void whileInt()
0   iconst_0
1   istore_1
2   goto 8
5   iinc 1 1
8   iload_1
9   bipush 100
11  if_icmplt 5
14  return
```

Note that the test of the `while` statement (implemented using the
<span class="emphasis">*if_icmplt*</span> instruction) is at the bottom
of the Java Virtual Machine code for the loop. (This was also the case
in the `spin` examples earlier.) The test being at the bottom of the
loop forces the use of a <span class="emphasis">*goto*</span>
instruction to get to the test prior to the first iteration of the loop.
If that test fails, and the loop body is never entered, this extra
instruction is wasted. However, `while` loops are typically used when
their body is expected to be run, often for many iterations. For
subsequent iterations, putting the test at the bottom of the loop saves
a Java Virtual Machine instruction each time around the loop: if the
test were at the top of the loop, the loop body would need a trailing
<span class="emphasis">*goto*</span> instruction to get back to the top.

Control constructs involving other data types are compiled in similar
ways, but must use the instructions available for those data types. This
leads to somewhat less efficient code because more Java Virtual Machine
instructions are needed, for example:

``` programlisting

void whileDouble() {
    double i = 0.0;
    while (i < 100.1) {
        i++;
    }
}
```

is compiled to:

``` programlisting
Method void whileDouble()
0   dconst_0
1   dstore_1
2   goto 9
5   dload_1
6   dconst_1
7   dadd
8   dstore_1
9   dload_1
10  ldc2_w #4      // Push double constant 100.1
13  dcmpg          // To compare and branch we have to use...
14  iflt 5         // ...two instructions
17  return
```

Each floating-point type has two comparison instructions:
<span class="emphasis">*fcmpl*</span> and
<span class="emphasis">*fcmpg*</span> for type `float`, and
<span class="emphasis">*dcmpl*</span> and
<span class="emphasis">*dcmpg*</span> for type `double`. The variants
differ only in their treatment of NaN. NaN is unordered
(<a href="jvms-2.html#jvms-2.3.2" class="xref"
title="2.3.2. Floating-Point Types and Values">§2.3.2</a>), so all
floating-point comparisons fail if either of their operands is NaN. The
compiler chooses the variant of the comparison instruction for the
appropriate type that produces the same result whether the comparison
fails on non-NaN values or encounters a NaN. For instance:

``` programlisting

int lessThan100(double d) {
    if (d < 100.0) {
        return 1;
    } else {
        return -1;
    }
}
```

compiles to:

``` programlisting
Method int lessThan100(double)
0   dload_1
1   ldc2_w #4      // Push double constant 100.0
4   dcmpg          // Push 1 if d is NaN or d > 100.0;
                   // push 0 if d == 100.0
5   ifge 10        // Branch on 0 or 1
8   iconst_1
9   ireturn
10  iconst_m1
11  ireturn
```

If `d` is not NaN and is less than `100.0`, the
<span class="emphasis">*dcmpg*</span> instruction pushes an `int`
<span class="emphasis">*-1*</span> onto the operand stack, and the
<span class="emphasis">*ifge*</span> instruction does not branch.
Whether `d` is greater than `100.0` or is NaN, the
<span class="emphasis">*dcmpg*</span> instruction pushes an `int`
<span class="emphasis">*1*</span> onto the operand stack, and the
<span class="emphasis">*ifge*</span> branches. If `d` is equal to
`100.0`, the <span class="emphasis">*dcmpg*</span> instruction pushes an
`int` <span class="emphasis">*0*</span> onto the operand stack, and the
<span class="emphasis">*ifge*</span> branches.

The <span class="emphasis">*dcmpl*</span> instruction achieves the same
effect if the comparison is reversed:

``` programlisting

int greaterThan100(double d) {
    if (d > 100.0) {
        return 1;
    } else {
        return -1;
    }
}
```

becomes:

``` programlisting
Method int greaterThan100(double)
0   dload_1
1   ldc2_w #4      // Push double constant 100.0
4   dcmpl          // Push -1 if d is NaN or d < 100.0;
                   // push 0 if d == 100.0
5   ifle 10        // Branch on 0 or -1
8   iconst_1
9   ireturn
10  iconst_m1
11  ireturn
```

Once again, whether the comparison fails on a non-NaN value or because
it is passed a NaN, the <span class="emphasis">*dcmpl*</span>
instruction pushes an `int` value onto the operand stack that causes the
<span class="emphasis">*ifle*</span> to branch. If both of the
<span class="emphasis">*dcmp*</span> instructions did not exist, one of
the example methods would have had to do more work to detect NaN.

</div>

<div id="jvms-3.6" class="section">

<div class="titlepage">

<div>

<div>

## 3.6. Receiving Arguments

</div>

</div>

</div>

If <span class="emphasis">*n*</span> arguments are passed to an instance
method, they are received, by convention, in the local variables
numbered <span class="emphasis">*1*</span> through
<span class="emphasis">*n*</span> of the frame created for the new
method invocation. The arguments are received in the order they were
passed. For example:

``` programlisting

int addTwo(int i, int j) {
    return i + j;
}
```

compiles to:

``` programlisting
Method int addTwo(int,int)
0   iload_1        // Push value of local variable 1 (i)
1   iload_2        // Push value of local variable 2 (j)
2   iadd           // Add; leave int result on operand stack
3   ireturn        // Return int result
```

By convention, an instance method is passed a `reference` to its
instance in local variable <span class="emphasis">*0*</span>. In the
Java programming language the instance is accessible via the `this`
keyword.

Class (`static`) methods do not have an instance, so for them this use
of local variable <span class="emphasis">*0*</span> is unnecessary. A
class method starts using local variables at index
<span class="emphasis">*0*</span>. If the `addTwo` method were a class
method, its arguments would be passed in a similar way to the first
version:

``` programlisting

static int addTwoStatic(int i, int j) {
    return i + j;
}
```

compiles to:

``` programlisting
Method int addTwoStatic(int,int)
0   iload_0
1   iload_1
2   iadd
3   ireturn
```

The only difference is that the method arguments appear starting in
local variable <span class="emphasis">*0*</span> rather than
<span class="emphasis">*1*</span>.

</div>

<div id="jvms-3.7" class="section">

<div class="titlepage">

<div>

<div>

## 3.7. Invoking Methods

</div>

</div>

</div>

The normal method invocation for a instance method dispatches on the
run-time type of the object. (They are virtual, in C++ terms.) Such an
invocation is implemented using the
<span class="emphasis">*invokevirtual*</span> instruction, which takes
as its argument an index to a run-time constant pool entry giving the
internal form of the binary name of the class type of the object, the
name of the method to invoke, and that method's descriptor
(<a href="jvms-4.html#jvms-4.3.3" class="xref"
title="4.3.3. Method Descriptors">§4.3.3</a>). To invoke the `addTwo`
method, defined earlier as an instance method, we might write:

``` programlisting

int add12and13() {
    return addTwo(12, 13);
}
```

This compiles to:

``` programlisting
Method int add12and13()
0   aload_0             // Push local variable 0 (this)
1   bipush 12           // Push int constant 12
3   bipush 13           // Push int constant 13
5   invokevirtual #4    // Method Example.addtwo(II)I
8   ireturn             // Return int on top of operand stack;
                        // it is the int result of addTwo()
```

The invocation is set up by first pushing a `reference` to the current
instance, `this`, on to the operand stack. The method invocation's
arguments, `int` values `12` and `13`, are then pushed. When the frame
for the `addTwo` method is created, the arguments passed to the method
become the initial values of the new frame's local variables. That is,
the `reference` for `this` and the two arguments, pushed onto the
operand stack by the invoker, will become the initial values of local
variables <span class="emphasis">*0*</span>,
<span class="emphasis">*1*</span>, and <span class="emphasis">*2*</span>
of the invoked method.

Finally, `addTwo` is invoked. When it returns, its `int` return value is
pushed onto the operand stack of the frame of the invoker, the
`add12and13` method. The return value is thus put in place to be
immediately returned to the invoker of `add12and13`.

The return from `add12and13` is handled by the
<span class="emphasis">*ireturn*</span> instruction of `add12and13`. The
<span class="emphasis">*ireturn*</span> instruction takes the `int`
value returned by `addTwo`, on the operand stack of the current frame,
and pushes it onto the operand stack of the frame of the invoker. It
then returns control to the invoker, making the invoker's frame current.
The Java Virtual Machine provides distinct return instructions for many
of its numeric and `reference` data types, as well as a
<span class="emphasis">*return*</span> instruction for methods with no
return value. The same set of return instructions is used for all
varieties of method invocations.

The operand of the <span class="emphasis">*invokevirtual*</span>
instruction (in the example, the run-time constant pool index
<span class="emphasis">*\#4*</span>) is not the offset of the method in
the class instance. The compiler does not know the internal layout of a
class instance. Instead, it generates symbolic references to the methods
of an instance, which are stored in the run-time constant pool. Those
run-time constant pool items are resolved at run-time to determine the
actual method location. The same is true for all other Java Virtual
Machine instructions that access class instances.

Invoking `addTwoStatic`, a class (`static`) variant of `addTwo`, is
similar, as shown:

``` programlisting

int add12and13() {
    return addTwoStatic(12, 13);
}
```

although a different Java Virtual Machine method invocation instruction
is used:

``` programlisting
Method int add12and13()
0   bipush 12
2   bipush 13
4   invokestatic #3     // Method Example.addTwoStatic(II)I
7   ireturn
```

Compiling an invocation of a class (`static`) method is very much like
compiling an invocation of an instance method, except `this` is not
passed by the invoker. The method arguments will thus be received
beginning with local variable <span class="emphasis">*0*</span>
(<a href="jvms-3.html#jvms-3.6" class="xref"
title="3.6. Receiving Arguments">§3.6</a>). The
<span class="emphasis">*invokestatic*</span> instruction is always used
to invoke class methods.

The <span class="emphasis">*invokespecial*</span> instruction must be
used to invoke instance initialization methods
(<a href="jvms-3.html#jvms-3.8" class="xref"
title="3.8. Working with Class Instances">§3.8</a>). It is also used
when invoking methods in the superclass (`super`). For instance, given
classes `Near` and `Far` declared as:

``` programlisting

class Near {
    int it;
    int getItNear() {
        return it;
    }
}
class Far extends Near {
    int getItFar() {
        return super.getItNear();
    }
}
```

The method `Far.getItFar` (which invokes a superclass method) becomes:

``` programlisting
Method int getItFar()
0   aload_0
1   invokespecial #4    // Method Near.getItNear()I
4   ireturn
```

Note that methods called using the
<span class="emphasis">*invokespecial*</span> instruction always pass
`this` to the invoked method as its first argument. As usual, it is
received in local variable <span class="emphasis">*0*</span>.

To invoke the target of a method handle, a compiler must form a method
descriptor that records the actual argument and return types. A compiler
may not perform method invocation conversions on the arguments; instead,
it must push them on the stack according to their own unconverted types.
The compiler arranges for a `reference` to the method handle object to
be pushed on the stack before the arguments, as usual. The compiler
emits an <span class="emphasis">*invokevirtual*</span> instruction that
references a descriptor which describes the argument and return types.
By special arrangement with method resolution
(<a href="jvms-5.html#jvms-5.4.3.3" class="xref"
title="5.4.3.3. Method Resolution">§5.4.3.3</a>), an
<span class="emphasis">*invokevirtual*</span> instruction which invokes
the `invokeExact` or `invoke` methods of `java.lang.invoke.MethodHandle`
will always link, provided the method descriptor is syntactically
well-formed and the types named in the descriptor can be resolved.

</div>

<div id="jvms-3.8" class="section">

<div class="titlepage">

<div>

<div>

## 3.8. Working with Class Instances

</div>

</div>

</div>

Java Virtual Machine class instances are created using the Java Virtual
Machine's <span class="emphasis">*new*</span> instruction. Recall that
at the level of the Java Virtual Machine, a constructor appears as a
method with the compiler-supplied name `<init>`. This specially named
method is known as the instance initialization method
(<a href="jvms-2.html#jvms-2.9" class="xref"
title="2.9. Special Methods">§2.9</a>). Multiple instance initialization
methods, corresponding to multiple constructors, may exist for a given
class. Once the class instance has been created and its instance
variables, including those of the class and all of its superclasses,
have been initialized to their default values, an instance
initialization method of the new class instance is invoked. For example:

``` programlisting

Object create() {
    return new Object();
}
```

compiles to:

``` programlisting
Method java.lang.Object create()
0   new #1              // Class java.lang.Object
3   dup
4   invokespecial #4    // Method java.lang.Object.<init>()V
7   areturn
```

Class instances are passed and returned (as `reference` types) very much
like numeric values, although type `reference` has its own complement of
instructions, for example:

``` programlisting

int i;                                  // An instance variable
MyObj example() {
    MyObj o = new MyObj();
    return silly(o);
}
MyObj silly(MyObj o) {
    if (o != null) {
        return o;
    } else {
        return o;
    }
}
```

becomes:

``` programlisting
Method MyObj example()
0   new #2              // Class MyObj
3   dup
4   invokespecial #5    // Method MyObj.<init>()V
7   astore_1
8   aload_0
9   aload_1
10  invokevirtual #4    // Method Example.silly(LMyObj;)LMyObj;
13  areturn

Method MyObj silly(MyObj)
0   aload_1
1   ifnull 6
4   aload_1
5   areturn
6   aload_1
7   areturn
```

The fields of a class instance (instance variables) are accessed using
the <span class="emphasis">*getfield*</span> and
<span class="emphasis">*putfield*</span> instructions. If `i` is an
instance variable of type `int`, the methods `setIt` and `getIt`,
defined as:

``` programlisting

void setIt(int value) {
    i = value;
}
int getIt() {
    return i;
}
```

become:

``` programlisting
Method void setIt(int)
0   aload_0
1   iload_1
2   putfield #4    // Field Example.i I
5   return

Method int getIt()
0   aload_0
1   getfield #4    // Field Example.i I
4   ireturn
```

As with the operands of method invocation instructions, the operands of
the <span class="emphasis">*putfield*</span> and
<span class="emphasis">*getfield*</span> instructions (the run-time
constant pool index <span class="emphasis">*\#4*</span>) are not the
offsets of the fields in the class instance. The compiler generates
symbolic references to the fields of an instance, which are stored in
the run-time constant pool. Those run-time constant pool items are
resolved at run-time to determine the location of the field within the
referenced object.

</div>

<div id="jvms-3.9" class="section">

<div class="titlepage">

<div>

<div>

## 3.9. Arrays

</div>

</div>

</div>

Java Virtual Machine arrays are also objects. Arrays are created and
manipulated using a distinct set of instructions. The
<span class="emphasis">*newarray*</span> instruction is used to create
an array of a numeric type. The code:

``` programlisting

void createBuffer() {
    int buffer[];
    int bufsz = 100;
    int value = 12;
    buffer = new int[bufsz];
    buffer[10] = value;
    value = buffer[11];
}
```

might be compiled to:

``` programlisting
Method void createBuffer()
0   bipush 100     // Push int constant 100 (bufsz)
2   istore_2       // Store bufsz in local variable 2
3   bipush 12      // Push int constant 12 (value)
5   istore_3       // Store value in local variable 3
6   iload_2        // Push bufsz...
7   newarray int   // ...and create new int array of that length
9   astore_1       // Store new array in buffer
10  aload_1        // Push buffer
11  bipush 10      // Push int constant 10
13  iload_3        // Push value
14  iastore        // Store value at buffer[10]
15  aload_1        // Push buffer
16  bipush 11      // Push int constant 11
18  iaload         // Push value at buffer[11]...
19  istore_3       // ...and store it in value
20  return
```

The <span class="emphasis">*anewarray*</span> instruction is used to
create a one-dimensional array of object references, for example:

``` programlisting

void createThreadArray() {
    Thread threads[];
    int count = 10;
    threads = new Thread[count];
    threads[0] = new Thread();
}
```

becomes:

``` programlisting
Method void createThreadArray()
0   bipush 10           // Push int constant 10
2   istore_2            // Initialize count to that
3   iload_2             // Push count, used by anewarray
4   anewarray class #1  // Create new array of class Thread
7   astore_1            // Store new array in threads
8   aload_1             // Push value of threads
9   iconst_0            // Push int constant 0
10  new #1              // Create instance of class Thread
13  dup                 // Make duplicate reference...
14  invokespecial #5    // ...for Thread's constructor
                        // Method java.lang.Thread.<init>()V
17  aastore             // Store new Thread in array at 0
18  return
```

The <span class="emphasis">*anewarray*</span> instruction can also be
used to create the first dimension of a multidimensional array.
Alternatively, the <span class="emphasis">*multianewarray*</span>
instruction can be used to create several dimensions at once. For
example, the three-dimensional array:

``` programlisting

int[][][] create3DArray() {
    int grid[][][];
    grid = new int[10][5][];
    return grid;
}
```

is created by:

``` programlisting
Method int create3DArray()[][][]
0   bipush 10                // Push int 10 (dimension one)
2   iconst_5                 // Push int 5 (dimension two)
3   multianewarray #1 dim #2 // Class [[[I, a three-dimensional
                             // int array; only create the
                             // first two dimensions
7   astore_1                 // Store new array...
8   aload_1                  // ...then prepare to return it
9   areturn
```

The first operand of the <span class="emphasis">*multianewarray*</span>
instruction is the run-time constant pool index to the array class type
to be created. The second is the number of dimensions of that array type
to actually create. The <span class="emphasis">*multianewarray*</span>
instruction can be used to create all the dimensions of the type, as the
code for `create3DArray` shows. Note that the multidimensional array is
just an object and so is loaded and returned by an
<span class="emphasis">*aload_1*</span> and
<span class="emphasis">*areturn*</span> instruction, respectively. For
information about array class names, see
<a href="jvms-4.html#jvms-4.4.1" class="xref"
title="4.4.1. The CONSTANT_Class_info Structure">§4.4.1</a>.

All arrays have associated lengths, which are accessed via the
<span class="emphasis">*arraylength*</span> instruction.

</div>

<div id="jvms-3.10" class="section">

<div class="titlepage">

<div>

<div>

## 3.10. Compiling Switches

</div>

</div>

</div>

Compilation of `switch` statements uses the
<span class="emphasis">*tableswitch*</span> and
<span class="emphasis">*lookupswitch*</span> instructions. The
<span class="emphasis">*tableswitch*</span> instruction is used when the
cases of the `switch` can be efficiently represented as indices into a
table of target offsets. The `default` target of the `switch` is used if
the value of the expression of the `switch` falls outside the range of
valid indices. For instance:

``` programlisting

int chooseNear(int i) {
    switch (i) {
        case 0:  return  0;
        case 1:  return  1;
        case 2:  return  2;
        default: return -1;
    }
}
```

compiles to:

``` programlisting
Method int chooseNear(int)
0   iload_1             // Push local variable 1 (argument i)
1   tableswitch 0 to 2: // Valid indices are 0 through 2
      0: 28             // If i is 0, continue at 28
      1: 30             // If i is 1, continue at 30
      2: 32             // If i is 2, continue at 32
      default:34        // Otherwise, continue at 34
28  iconst_0            // i was 0; push int constant 0...
29  ireturn             // ...and return it
30  iconst_1            // i was 1; push int constant 1...
31  ireturn             // ...and return it
32  iconst_2            // i was 2; push int constant 2...
33  ireturn             // ...and return it
34  iconst_m1           // otherwise push int constant -1...
35  ireturn             // ...and return it
```

The Java Virtual Machine's <span class="emphasis">*tableswitch*</span>
and <span class="emphasis">*lookupswitch*</span> instructions operate
only on `int` data. Because operations on `byte`, `char`, or `short`
values are internally promoted to `int`, a `switch` whose expression
evaluates to one of those types is compiled as though it evaluated to
type `int`. If the `chooseNear` method had been written using type
`short`, the same Java Virtual Machine instructions would have been
generated as when using type `int`. Other numeric types must be narrowed
to type `int` for use in a `switch`.

Where the cases of the `switch` are sparse, the table representation of
the <span class="emphasis">*tableswitch*</span> instruction becomes
inefficient in terms of space. The
<span class="emphasis">*lookupswitch*</span> instruction may be used
instead. The <span class="emphasis">*lookupswitch*</span> instruction
pairs `int` keys (the values of the `case` labels) with target offsets
in a table. When a <span class="emphasis">*lookupswitch*</span>
instruction is executed, the value of the expression of the `switch` is
compared against the keys in the table. If one of the keys matches the
value of the expression, execution continues at the associated target
offset. If no key matches, execution continues at the `default` target.
For instance, the compiled code for:

``` programlisting

int chooseFar(int i) {
    switch (i) {
        case -100: return -1;
        case 0:    return  0;
        case 100:  return  1;
        default:   return -1;
    }
}
```

looks just like the code for `chooseNear`, except for the
<span class="emphasis">*lookupswitch*</span> instruction:

``` programlisting
Method int chooseFar(int)
0   iload_1
1   lookupswitch 3:
         -100: 36
            0: 38
          100: 40
      default: 42
36  iconst_m1
37  ireturn
38  iconst_0
39  ireturn
40  iconst_1
41  ireturn
42  iconst_m1
43  ireturn
```

The Java Virtual Machine specifies that the table of the
<span class="emphasis">*lookupswitch*</span> instruction must be sorted
by key so that implementations may use searches more efficient than a
linear scan. Even so, the <span class="emphasis">*lookupswitch*</span>
instruction must search its keys for a match rather than simply perform
a bounds check and index into a table like
<span class="emphasis">*tableswitch*</span>. Thus, a
<span class="emphasis">*tableswitch*</span> instruction is probably more
efficient than a <span class="emphasis">*lookupswitch*</span> where
space considerations permit a choice.

</div>

<div id="jvms-3.11" class="section">

<div class="titlepage">

<div>

<div>

## 3.11. Operations on the Operand Stack

</div>

</div>

</div>

The Java Virtual Machine has a large complement of instructions that
manipulate the contents of the operand stack as untyped values. These
are useful because of the Java Virtual Machine's reliance on deft
manipulation of its operand stack. For instance:

``` programlisting

public long nextIndex() {
    return index++;
}

private long index = 0;
```

is compiled to:

``` programlisting
Method long nextIndex()
0   aload_0        // Push this
1   dup            // Make a copy of it
2   getfield #4    // One of the copies of this is consumed
                   // pushing long field index,
                   // above the original this
5   dup2_x1        // The long on top of the operand stack is
                   // inserted into the operand stack below the
                   // original this
6   lconst_1       // Push long constant 1
7   ladd           // The index value is incremented...
8   putfield #4    // ...and the result stored in the field
11  lreturn        // The original value of index is on top of
                   // the operand stack, ready to be returned
```

Note that the Java Virtual Machine never allows its operand stack
manipulation instructions to modify or break up individual values on the
operand stack.

</div>

<div id="jvms-3.12" class="section">

<div class="titlepage">

<div>

<div>

## 3.12. Throwing and Handling Exceptions

</div>

</div>

</div>

Exceptions are thrown from programs using the `throw` keyword. Its
compilation is simple:

``` programlisting

void cantBeZero(int i) throws TestExc {
    if (i == 0) {
        throw new TestExc();
    }
}
```

becomes:

``` programlisting
Method void cantBeZero(int)
0   iload_1             // Push argument 1 (i)
1   ifne 12             // If i==0, allocate instance and throw
4   new #1              // Create instance of TestExc
7   dup                 // One reference goes to its constructor
8   invokespecial #7    // Method TestExc.<init>()V
11  athrow              // Second reference is thrown
12  return              // Never get here if we threw TestExc
```

Compilation of `try`-`catch` constructs is straightforward. For example:

``` programlisting

void catchOne() {
    try {
        tryItOut();
    } catch (TestExc e) {
        handleExc(e);
    }
}
```

is compiled as:

``` programlisting
Method void catchOne()
0   aload_0             // Beginning of try block
1   invokevirtual #6    // Method Example.tryItOut()V
4   return              // End of try block; normal return
5   astore_1            // Store thrown value in local var 1
6   aload_0             // Push this
7   aload_1             // Push thrown value
8   invokevirtual #5    // Invoke handler method:
                        // Example.handleExc(LTestExc;)V
11  return              // Return after handling TestExc
Exception table:
From    To      Target      Type
0       4       5           Class TestExc
```

Looking more closely, the `try` block is compiled just as it would be if
the `try` were not present:

``` programlisting
Method void catchOne()
0   aload_0             // Beginning of try block
1   invokevirtual #6    // Method Example.tryItOut()V
4   return              // End of try block; normal return
```

If no exception is thrown during the execution of the `try` block, it
behaves as though the `try` were not there: `tryItOut` is invoked and
`catchOne` returns.

Following the `try` block is the Java Virtual Machine code that
implements the single `catch` clause:

``` programlisting
5   astore_1            // Store thrown value in local var 1
6   aload_0             // Push this
7   aload_1             // Push thrown value
8   invokevirtual #5    // Invoke handler method:
                        // Example.handleExc(LTestExc;)V
11  return              // Return after handling TestExc
Exception table:
From    To      Target      Type
0       4       5           Class TestExc
```

The invocation of `handleExc`, the contents of the `catch` clause, is
also compiled like a normal method invocation. However, the presence of
a `catch` clause causes the compiler to generate an exception table
entry (<a href="jvms-2.html#jvms-2.10" class="xref"
title="2.10. Exceptions">§2.10</a>,
<a href="jvms-4.html#jvms-4.7.3" class="xref"
title="4.7.3. The Code Attribute">§4.7.3</a>). The exception table for
the `catchOne` method has one entry corresponding to the one argument
(an instance of class `TestExc`) that the `catch` clause of `catchOne`
can handle. If some value that is an instance of `TestExc` is thrown
during execution of the instructions between indices
<span class="emphasis">*0*</span> and <span class="emphasis">*4*</span>
in `catchOne`, control is transferred to the Java Virtual Machine code
at index <span class="emphasis">*5*</span>, which implements the block
of the `catch` clause. If the value that is thrown is not an instance of
`TestExc`, the `catch` clause of `catchOne` cannot handle it. Instead,
the value is rethrown to the invoker of `catchOne`.

A `try` may have multiple `catch` clauses:

``` programlisting

void catchTwo() {
    try {
        tryItOut();
    } catch (TestExc1 e) {
        handleExc(e);
    } catch (TestExc2 e) {
        handleExc(e);
    }
}
```

Multiple `catch` clauses of a given `try` statement are compiled by
simply appending the Java Virtual Machine code for each `catch` clause
one after the other and adding entries to the exception table, as shown:

``` programlisting
Method void catchTwo()
0   aload_0             // Begin try block
1   invokevirtual #5    // Method Example.tryItOut()V
4   return              // End of try block; normal return
5   astore_1            // Beginning of handler for TestExc1;
                        // Store thrown value in local var 1
6   aload_0             // Push this
7   aload_1             // Push thrown value
8   invokevirtual #7    // Invoke handler method:
                        // Example.handleExc(LTestExc1;)V
11  return              // Return after handling TestExc1
12  astore_1            // Beginning of handler for TestExc2;
                        // Store thrown value in local var 1
13  aload_0             // Push this
14  aload_1             // Push thrown value
15  invokevirtual #7    // Invoke handler method:
                        // Example.handleExc(LTestExc2;)V
18  return              // Return after handling TestExc2
Exception table:
From    To      Target      Type
0       4       5           Class TestExc1
0       4       12          Class TestExc2
```

If during the execution of the `try` clause (between indices
<span class="emphasis">*0*</span> and <span class="emphasis">*4*</span>)
a value is thrown that matches the parameter of one or more of the
`catch` clauses (the value is an instance of one or more of the
parameters), the first (innermost) such `catch` clause is selected.
Control is transferred to the Java Virtual Machine code for the block of
that `catch` clause. If the value thrown does not match the parameter of
any of the `catch` clauses of `catchTwo`, the Java Virtual Machine
rethrows the value without invoking code in any `catch` clause of
`catchTwo`.

Nested `try`-`catch` statements are compiled very much like a `try`
statement with multiple `catch` clauses:

``` programlisting

void nestedCatch() {
    try {
        try {
            tryItOut();
        } catch (TestExc1 e) {
            handleExc1(e);
        }
    } catch (TestExc2 e) {
        handleExc2(e);
    }
}
```

becomes:

``` programlisting
Method void nestedCatch()
0   aload_0             // Begin try block
1   invokevirtual #8    // Method Example.tryItOut()V
4   return              // End of try block; normal return
5   astore_1            // Beginning of handler for TestExc1;
                        // Store thrown value in local var 1
6   aload_0             // Push this
7   aload_1             // Push thrown value
8   invokevirtual #7    // Invoke handler method:
                        // Example.handleExc1(LTestExc1;)V
11  return              // Return after handling TestExc1
12  astore_1            // Beginning of handler for TestExc2;
                        // Store thrown value in local var 1
13  aload_0             // Push this
14  aload_1             // Push thrown value
15  invokevirtual #6    // Invoke handler method:
                        // Example.handleExc2(LTestExc2;)V
18  return              // Return after handling TestExc2
Exception table:
From    To      Target      Type
0       4       5           Class TestExc1
0       12      12          Class TestExc2
```

The nesting of `catch` clauses is represented only in the exception
table. The Java Virtual Machine does not enforce nesting of or any
ordering of the exception table entries
(<a href="jvms-2.html#jvms-2.10" class="xref"
title="2.10. Exceptions">§2.10</a>). However, because `try`-`catch`
constructs are structured, a compiler can always order the entries of
the exception handler table such that, for any thrown exception and any
program counter value in that method, the first exception handler that
matches the thrown exception corresponds to the innermost matching
`catch` clause.

For instance, if the invocation of `tryItOut` (at index
<span class="emphasis">*1*</span>) threw an instance of `TestExc1`, it
would be handled by the `catch` clause that invokes `handleExc1`. This
is so even though the exception occurs within the bounds of the outer
`catch` clause (catching `TestExc2`) and even though that outer `catch`
clause might otherwise have been able to handle the thrown value.

As a subtle point, note that the range of a `catch` clause is inclusive
on the "from" end and exclusive on the "to" end
(<a href="jvms-4.html#jvms-4.7.3" class="xref"
title="4.7.3. The Code Attribute">§4.7.3</a>). Thus, the exception table
entry for the `catch` clause catching `TestExc1` does not cover the
<span class="emphasis">*return*</span> instruction at offset
<span class="emphasis">*4*</span>. However, the exception table entry
for the `catch` clause catching `TestExc2` does cover the
<span class="emphasis">*return*</span> instruction at offset
<span class="emphasis">*11*</span>. Return instructions within nested
`catch` clauses are included in the range of instructions covered by
nesting `catch` clauses.

</div>

<div id="jvms-3.13" class="section">

<div class="titlepage">

<div>

<div>

## 3.13. Compiling `finally`

</div>

</div>

</div>

(This section assumes a compiler generates `class` files with version
number 50.0 or below, so that the <span class="emphasis">*jsr*</span>
instruction may be used. See also
<a href="jvms-4.html#jvms-4.10.2.5" class="xref"
title="4.10.2.5. Exceptions and finally">§4.10.2.5</a>.)

Compilation of a `try`-`finally` statement is similar to that of
`try`-`catch`. Prior to transferring control outside the `try`
statement, whether that transfer is normal or abrupt, because an
exception has been thrown, the `finally` clause must first be executed.
For this simple example:

``` programlisting

void tryFinally() {
    try {
        tryItOut();
    } finally {
        wrapItUp();
    }
}
```

the compiled code is:

``` programlisting
Method void tryFinally()
0   aload_0             // Beginning of try block
1   invokevirtual #6    // Method Example.tryItOut()V
4   jsr 14              // Call finally block
7   return              // End of try block
8   astore_1            // Beginning of handler for any throw
9   jsr 14              // Call finally block
12  aload_1             // Push thrown value
13  athrow              // ...and rethrow value to the invoker
14  astore_2            // Beginning of finally block
15  aload_0             // Push this
16  invokevirtual #5    // Method Example.wrapItUp()V
19  ret 2               // Return from finally block
Exception table:
From    To      Target      Type
0       4       8           any
```

There are four ways for control to pass outside of the `try` statement:
by falling through the bottom of that block, by returning, by executing
a `break` or `continue` statement, or by raising an exception. If
`tryItOut` returns without raising an exception, control is transferred
to the `finally` block using a <span class="emphasis">*jsr*</span>
instruction. The <span class="emphasis">*jsr*</span>
<span class="emphasis">*14*</span> instruction at index
<span class="emphasis">*4*</span> makes a "subroutine call" to the code
for the `finally` block at index <span class="emphasis">*14*</span> (the
`finally` block is compiled as an embedded subroutine). When the
`finally` block completes, the <span class="emphasis">*ret*</span>
<span class="emphasis">*2*</span> instruction returns control to the
instruction following the <span class="emphasis">*jsr*</span>
instruction at index <span class="emphasis">*4*</span>.

In more detail, the subroutine call works as follows: The
<span class="emphasis">*jsr*</span> instruction pushes the address of
the following instruction (<span class="emphasis">*return*</span> at
index <span class="emphasis">*7*</span>) onto the operand stack before
jumping. The <span class="emphasis">*astore_2*</span> instruction that
is the jump target stores the address on the operand stack into local
variable <span class="emphasis">*2*</span>. The code for the `finally`
block (in this case the <span class="emphasis">*aload_0*</span> and
<span class="emphasis">*invokevirtual*</span> instructions) is run.
Assuming execution of that code completes normally, the
<span class="emphasis">*ret*</span> instruction retrieves the address
from local variable <span class="emphasis">*2*</span> and resumes
execution at that address. The <span class="emphasis">*return*</span>
instruction is executed, and `tryFinally` returns normally.

A `try` statement with a `finally` clause is compiled to have a special
exception handler, one that can handle any exception thrown within the
`try` statement. If `tryItOut` throws an exception, the exception table
for `tryFinally` is searched for an appropriate exception handler. The
special handler is found, causing execution to continue at index
<span class="emphasis">*8*</span>. The
<span class="emphasis">*astore_1*</span> instruction at index
<span class="emphasis">*8*</span> stores the thrown value into local
variable <span class="emphasis">*1*</span>. The following
<span class="emphasis">*jsr*</span> instruction does a subroutine call
to the code for the `finally` block. Assuming that code returns
normally, the <span class="emphasis">*aload_1*</span> instruction at
index <span class="emphasis">*12*</span> pushes the thrown value back
onto the operand stack, and the following
<span class="emphasis">*athrow*</span> instruction rethrows the value.

Compiling a `try` statement with both a `catch` clause and a `finally`
clause is more complex:

``` programlisting

void tryCatchFinally() {
    try {
        tryItOut();
    } catch (TestExc e) {
        handleExc(e);
    } finally {
        wrapItUp();
    }
}
```

becomes:

``` programlisting
Method void tryCatchFinally()
0   aload_0             // Beginning of try block
1   invokevirtual #4    // Method Example.tryItOut()V
4   goto 16             // Jump to finally block
7   astore_3            // Beginning of handler for TestExc;
                        // Store thrown value in local var 3
8   aload_0             // Push this
9   aload_3             // Push thrown value
10  invokevirtual #6    // Invoke handler method:
                        // Example.handleExc(LTestExc;)V
13  goto 16             // This goto is unnecessary, but was
                        // generated by javac in JDK 1.0.2
16  jsr 26              // Call finally block
19  return              // Return after handling TestExc
20  astore_1            // Beginning of handler for exceptions
                        // other than TestExc, or exceptions
                        // thrown while handling TestExc
21  jsr 26              // Call finally block
24  aload_1             // Push thrown value...
25  athrow              // ...and rethrow value to the invoker
26  astore_2            // Beginning of finally block
27  aload_0             // Push this
28  invokevirtual #5    // Method Example.wrapItUp()V
31  ret 2               // Return from finally block
Exception table:
From    To      Target      Type
0       4       7           Class TestExc
0       16      20          any
```

If the `try` statement completes normally, the
<span class="emphasis">*goto*</span> instruction at index
<span class="emphasis">*4*</span> jumps to the subroutine call for the
`finally` block at index <span class="emphasis">*16*</span>. The
`finally` block at index <span class="emphasis">*26*</span> is executed,
control returns to the <span class="emphasis">*return*</span>
instruction at index <span class="emphasis">*19*</span>, and
`tryCatchFinally` returns normally.

If `tryItOut` throws an instance of `TestExc`, the first (innermost)
applicable exception handler in the exception table is chosen to handle
the exception. The code for that exception handler, beginning at index
<span class="emphasis">*7*</span>, passes the thrown value to
`handleExc` and on its return makes the same subroutine call to the
`finally` block at index <span class="emphasis">*26*</span> as in the
normal case. If an exception is not thrown by `handleExc`,
`tryCatchFinally` returns normally.

If `tryItOut` throws a value that is not an instance of `TestExc` or if
`handleExc` itself throws an exception, the condition is handled by the
second entry in the exception table, which handles any value thrown
between indices <span class="emphasis">*0*</span> and
<span class="emphasis">*16*</span>. That exception handler transfers
control to index <span class="emphasis">*20*</span>, where the thrown
value is first stored in local variable
<span class="emphasis">*1*</span>. The code for the `finally` block at
index <span class="emphasis">*26*</span> is called as a subroutine. If
it returns, the thrown value is retrieved from local variable
<span class="emphasis">*1*</span> and rethrown using the
<span class="emphasis">*athrow*</span> instruction. If a new value is
thrown during execution of the `finally` clause, the `finally` clause
aborts, and `tryCatchFinally` returns abruptly, throwing the new value
to its invoker.

</div>

<div id="jvms-3.14" class="section">

<div class="titlepage">

<div>

<div>

## 3.14. Synchronization

</div>

</div>

</div>

Synchronization in the Java Virtual Machine is implemented by monitor
entry and exit, either explicitly (by use of the
<span class="emphasis">*monitorenter*</span> and
<span class="emphasis">*monitorexit*</span> instructions) or implicitly
(by the method invocation and return instructions).

For code written in the Java programming language, perhaps the most
common form of synchronization is the `synchronized` method. A
`synchronized` method is not normally implemented using
<span class="emphasis">*monitorenter*</span> and
<span class="emphasis">*monitorexit*</span>. Rather, it is simply
distinguished in the run-time constant pool by the `ACC_SYNCHRONIZED`
flag, which is checked by the method invocation instructions
(<a href="jvms-2.html#jvms-2.11.10" class="xref"
title="2.11.10. Synchronization">§2.11.10</a>).

The <span class="emphasis">*monitorenter*</span> and
<span class="emphasis">*monitorexit*</span> instructions enable the
compilation of `synchronized` statements. For example:

``` programlisting

void onlyMe(Foo f) {
    synchronized(f) {
        doSomething();
    }
}
```

is compiled to:

``` programlisting
Method void onlyMe(Foo)
0   aload_1             // Push f
1   dup                 // Duplicate it on the stack
2   astore_2            // Store duplicate in local variable 2
3   monitorenter        // Enter the monitor associated with f
4   aload_0             // Holding the monitor, pass this and...
5   invokevirtual #5    // ...call Example.doSomething()V
8   aload_2             // Push local variable 2 (f)
9   monitorexit         // Exit the monitor associated with f
10  goto 18             // Complete the method normally
13  astore_3            // In case of any throw, end up here
14  aload_2             // Push local variable 2 (f)
15  monitorexit         // Be sure to exit the monitor!
16  aload_3             // Push thrown value...
17  athrow              // ...and rethrow value to the invoker
18  return              // Return in the normal case
Exception table:
From    To      Target      Type
4       10      13          any
13      16      13          any
```

The compiler ensures that at any method invocation completion, a
<span class="emphasis">*monitorexit*</span> instruction will have been
executed for each <span class="emphasis">*monitorenter*</span>
instruction executed since the method invocation. This is the case
whether the method invocation completes normally
(<a href="jvms-2.html#jvms-2.6.4" class="xref"
title="2.6.4. Normal Method Invocation Completion">§2.6.4</a>) or
abruptly (<a href="jvms-2.html#jvms-2.6.5" class="xref"
title="2.6.5. Abrupt Method Invocation Completion">§2.6.5</a>). To
enforce proper pairing of <span class="emphasis">*monitorenter*</span>
and <span class="emphasis">*monitorexit*</span> instructions on abrupt
method invocation completion, the compiler generates exception handlers
(<a href="jvms-2.html#jvms-2.10" class="xref"
title="2.10. Exceptions">§2.10</a>) that will match any exception and
whose associated code executes the necessary
<span class="emphasis">*monitorexit*</span> instructions.

</div>

<div id="jvms-3.15" class="section">

<div class="titlepage">

<div>

<div>

## 3.15. Annotations

</div>

</div>

</div>

The representation of annotations in `class` files is described in
<a href="jvms-4.html#jvms-4.7.16" class="xref"
title="4.7.16. The RuntimeVisibleAnnotations Attribute">§4.7.16</a>-<a href="jvms-4.html#jvms-4.7.22" class="xref"
title="4.7.22. The AnnotationDefault Attribute">§4.7.22</a>. These
sections make it clear how to represent annotations on declarations of
classes, interfaces, fields, methods, method parameters, and type
parameters, as well as annotations on types used in those declarations.
Annotations on package declarations require additional rules, given
here.

When the compiler encounters an annotated package declaration that must
be made available at run time, it emits a `class` file with the
following properties:

<div class="norm">

- The `class` file represents an interface, that is, the `ACC_INTERFACE`
  and `ACC_ABSTRACT` flags of the `ClassFile` structure are set
  (<a href="jvms-4.html#jvms-4.1" class="xref"
  title="4.1. The ClassFile Structure">§4.1</a>).

- If the `class` file version number is less than 50.0, then the
  `ACC_SYNTHETIC` flag is unset; if the `class` file version number is
  50.0 or above, then the `ACC_SYNTHETIC` flag is set.

- The interface has package access (JLS §6.6.1).

- The interface's name is the internal form
  (<a href="jvms-4.html#jvms-4.2.1" class="xref"
  title="4.2.1. Binary Class and Interface Names">§4.2.1</a>) of
  <span class="emphasis">*`package-name`*</span>`.package-info`.

- The interface has no superinterfaces.

- The interface's only members are those implied by *The Java Language
  Specification, Java SE 26 Edition* (JLS §9.2).

- The annotations on the package declaration are stored as
  `RuntimeVisibleAnnotations` and `RuntimeInvisibleAnnotations`
  attributes in the `attributes` table of the `ClassFile` structure.

</div>

</div>

<div id="jvms-3.16" class="section">

<div class="titlepage">

<div>

<div>

## 3.16. Modules

</div>

</div>

</div>

A compilation unit that contains a module declaration (JLS §7.7) is
compiled to a `class` file that contains a `Module` attribute.

By convention, the name of a compilation unit that contains a module
declaration is `module-info.java`, echoing the `package-info.java`
convention for a compilation unit that contains solely a package
declaration. Consequently, by convention, the name for the compiled form
of a module declaration is `module-info.class`.

A flag in the `access_flags` item of the `ClassFile` structure,
`ACC_MODULE` (0x8000), indicates that this `class` file declares a
module. `ACC_MODULE` plays a similar role to `ACC_ANNOTATION` (0x2000)
and `ACC_ENUM` (0x4000) in flagging this `class` file as "not an
ordinary class". `ACC_MODULE` does <span class="emphasis">*not*</span>
describe accessibility of a class or interface.

The `Module` attribute is explicit about the module's dependences; there
are no implicit `requires` directives at the `ClassFile` level. If the
`requires_count` item is zero, then the Java SE Platform does
<span class="emphasis">*not*</span> infer the existence of a `requires`
table nor any particular entry therein. `java.base` is the only module
in which a zero `requires_count` is legal, because it is the primordial
module. For every other module, the `Module` attribute must have a
`requires` table of at least length one, because every other module
depends on `java.base`. If a compilation unit contains a module
declaration (except `java.base`) that does not state its dependence on
`java.base` explicitly, then a compiler must emit an entry for
`java.base` in the `requires` table and flag it as `ACC_MANDATED` to
denote that it was implicitly declared.

For encapsulation, the `Module` attribute is explicit about the packages
exported and opened by a normal module; there are no implicit `exports`
or `opens` directives at the `ClassFile` level for a normal module. If
the `exports_count` item or `opens_count` item is zero, then the Java SE
Platform does <span class="emphasis">*not*</span> infer the existence of
an `exports` table or `opens` table, nor any particular entry therein.
On the other hand, for an open module, the `Module` attribute is
implicit about the packages opened by the module. All packages of an
open module are opened to all other modules, even though the
`opens_count` item is zero.

The `Module` attribute is explicit about the module's consumption and
provision of services; there are no implicit `uses` or `provides`
directives at the `ClassFile` level.

</div>

</div>

<div class="navfooter">

------------------------------------------------------------------------

|  |  |  |
|:---|:--:|---:|
| <a href="jvms-2.html" accesskey="p">Prev</a>  |   |  <a href="jvms-4.html" accesskey="n">Next</a> |
| Chapter 2. The Structure of the Java Virtual Machine  | <a href="index.html" accesskey="h">Home</a> |  Chapter 4. The `class` File Format |

</div>

<div class="navfooter">

------------------------------------------------------------------------

[Legal Notice](spec-frontmatter.html)

</div>
