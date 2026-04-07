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
<th colspan="3" style="text-align: center;">Chapter 2. The Structure of
the Java Virtual Machine</th>
</tr>
</thead>
<tbody>
<tr>
<td style="text-align: left; width: 20%;"><a href="jvms-1.html"
accesskey="p">Prev</a> </td>
<td style="text-align: center; width: 60%;"> </td>
<td style="text-align: right; width: 20%;"> <a href="jvms-3.html"
accesskey="n">Next</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

</div>

<div id="jvms-2" class="chapter" lang="en">

<div class="titlepage">

<div>

<div>

# Chapter 2. The Structure of the Java Virtual Machine

</div>

</div>

</div>

<div class="toc">

**Table of Contents**

<span class="section">[2.1. The `class` File
Format](jvms-2.html#jvms-2.1)</span>

<span class="section">[2.2. Data Types](jvms-2.html#jvms-2.2)</span>

<span class="section">[2.3. Primitive Types and
Values](jvms-2.html#jvms-2.3)</span>

<span class="section">[2.3.1. Integral Types and
Values](jvms-2.html#jvms-2.3.1)</span>

<span class="section">[2.3.2. Floating-Point Types and
Values](jvms-2.html#jvms-2.3.2)</span>

<span class="section">[2.3.3. The `returnAddress` Type and
Values](jvms-2.html#jvms-2.3.3)</span>

<span class="section">[2.3.4. The `boolean`
Type](jvms-2.html#jvms-2.3.4)</span>

<span class="section">[2.4. Reference Types and
Values](jvms-2.html#jvms-2.4)</span>

<span class="section">[2.5. Run-Time Data
Areas](jvms-2.html#jvms-2.5)</span>

<span class="section">[2.5.1. The `pc`
Register](jvms-2.html#jvms-2.5.1)</span>

<span class="section">[2.5.2. Java Virtual Machine
Stacks](jvms-2.html#jvms-2.5.2)</span>

<span class="section">[2.5.3. Heap](jvms-2.html#jvms-2.5.3)</span>

<span class="section">[2.5.4. Method
Area](jvms-2.html#jvms-2.5.4)</span>

<span class="section">[2.5.5. Run-Time Constant
Pool](jvms-2.html#jvms-2.5.5)</span>

<span class="section">[2.5.6. Native Method
Stacks](jvms-2.html#jvms-2.5.6)</span>

<span class="section">[2.6. Frames](jvms-2.html#jvms-2.6)</span>

<span class="section">[2.6.1. Local
Variables](jvms-2.html#jvms-2.6.1)</span>

<span class="section">[2.6.2. Operand
Stacks](jvms-2.html#jvms-2.6.2)</span>

<span class="section">[2.6.3. Dynamic
Linking](jvms-2.html#jvms-2.6.3)</span>

<span class="section">[2.6.4. Normal Method Invocation
Completion](jvms-2.html#jvms-2.6.4)</span>

<span class="section">[2.6.5. Abrupt Method Invocation
Completion](jvms-2.html#jvms-2.6.5)</span>

<span class="section">[2.7. Representation of
Objects](jvms-2.html#jvms-2.7)</span>

<span class="section">[2.8. Floating-Point
Arithmetic](jvms-2.html#jvms-2.8)</span>

<span class="section">[2.9. Special
Methods](jvms-2.html#jvms-2.9)</span>

<span class="section">[2.9.1. Instance Initialization
Methods](jvms-2.html#jvms-2.9.1)</span>

<span class="section">[2.9.2. Class Initialization
Methods](jvms-2.html#jvms-2.9.2)</span>

<span class="section">[2.9.3. Signature Polymorphic
Methods](jvms-2.html#jvms-2.9.3)</span>

<span class="section">[2.10. Exceptions](jvms-2.html#jvms-2.10)</span>

<span class="section">[2.11. Instruction Set
Summary](jvms-2.html#jvms-2.11)</span>

<span class="section">[2.11.1. Types and the Java Virtual
Machine](jvms-2.html#jvms-2.11.1)</span>

<span class="section">[2.11.2. Load and Store
Instructions](jvms-2.html#jvms-2.11.2)</span>

<span class="section">[2.11.3. Arithmetic
Instructions](jvms-2.html#jvms-2.11.3)</span>

<span class="section">[2.11.4. Type Conversion
Instructions](jvms-2.html#jvms-2.11.4)</span>

<span class="section">[2.11.5. Object Creation and
Manipulation](jvms-2.html#jvms-2.11.5)</span>

<span class="section">[2.11.6. Operand Stack Management
Instructions](jvms-2.html#jvms-2.11.6)</span>

<span class="section">[2.11.7. Control Transfer
Instructions](jvms-2.html#jvms-2.11.7)</span>

<span class="section">[2.11.8. Method Invocation and Return
Instructions](jvms-2.html#jvms-2.11.8)</span>

<span class="section">[2.11.9. Throwing
Exceptions](jvms-2.html#jvms-2.11.9)</span>

<span class="section">[2.11.10.
Synchronization](jvms-2.html#jvms-2.11.10)</span>

<span class="section">[2.12. Class
Libraries](jvms-2.html#jvms-2.12)</span>

<span class="section">[2.13. Public Design, Private
Implementation](jvms-2.html#jvms-2.13)</span>

</div>

This document specifies an abstract machine. It does not describe any
particular implementation of the Java Virtual Machine.

To implement the Java Virtual Machine correctly, you need only be able
to read the `class` file format and correctly perform the operations
specified therein. Implementation details that are not part of the Java
Virtual Machine's specification would unnecessarily constrain the
creativity of implementors. For example, the memory layout of run-time
data areas, the garbage-collection algorithm used, and any internal
optimization of the Java Virtual Machine instructions (for example,
translating them into machine code) are left to the discretion of the
implementor.

All references to Unicode in this specification are given with respect
to *The Unicode Standard, Version 17.0.0*, available at
<a href="https://www.unicode.org/" class="link" target="_top"><code
class="uri">https://www.unicode.org/</code></a>.

<div id="jvms-2.1" class="section">

<div class="titlepage">

<div>

<div>

## 2.1. The `class` File Format

</div>

</div>

</div>

Compiled code to be executed by the Java Virtual Machine is represented
using a hardware- and operating system-independent binary format,
typically (but not necessarily) stored in a file, known as the `class`
file format. The `class` file format precisely defines the
representation of a class or interface, including details such as byte
ordering that might be taken for granted in a platform-specific object
file format.

Chapter 4, "The `class` File Format", covers the `class` file format in
detail.

</div>

<div id="jvms-2.2" class="section">

<div class="titlepage">

<div>

<div>

## 2.2. Data Types

</div>

</div>

</div>

Like the Java programming language, the Java Virtual Machine operates on
two kinds of types: <span class="emphasis">*primitive types*</span> and
<span class="emphasis">*reference types*</span>. There are,
correspondingly, two kinds of values that can be stored in variables,
passed as arguments, returned by methods, and operated upon:
<span class="emphasis">*primitive values*</span> and
<span class="emphasis">*reference values*</span>.

The Java Virtual Machine expects that nearly all type checking is done
prior to run time, typically by a compiler, and does not have to be done
by the Java Virtual Machine itself. Values of primitive types need not
be tagged or otherwise be inspectable to determine their types at run
time, or to be distinguished from values of reference types. Instead,
the instruction set of the Java Virtual Machine distinguishes its
operand types using instructions intended to operate on values of
specific types. For instance, <span class="emphasis">*iadd*</span>,
<span class="emphasis">*ladd*</span>,
<span class="emphasis">*fadd*</span>, and
<span class="emphasis">*dadd*</span> are all Java Virtual Machine
instructions that add two numeric values and produce numeric results,
but each is specialized for its operand type: `int`, `long`, `float`,
and `double`, respectively. For a summary of type support in the Java
Virtual Machine instruction set, see
<a href="jvms-2.html#jvms-2.11.1" class="xref"
title="2.11.1. Types and the Java Virtual Machine">§2.11.1</a>.

The Java Virtual Machine contains explicit support for objects. An
object is either a dynamically allocated class instance or an array. A
reference to an object is considered to have Java Virtual Machine type
`reference`. References are polymorphic: a single reference may also be
a value of multiple class types, interface types, or array types. Values
of type `reference` can be thought of as pointers to objects. More than
one reference to an object may exist. Objects are always operated on,
passed, and tested via values of type `reference`.

</div>

<div id="jvms-2.3" class="section">

<div class="titlepage">

<div>

<div>

## 2.3. Primitive Types and Values

</div>

</div>

</div>

The primitive data types supported by the Java Virtual Machine are the
<span class="emphasis">*numeric types*</span>, the `boolean` type
(<a href="jvms-2.html#jvms-2.3.4" class="xref"
title="2.3.4. The boolean Type">§2.3.4</a>), and the `returnAddress`
type (<a href="jvms-2.html#jvms-2.3.3" class="xref"
title="2.3.3. The returnAddress Type and Values">§2.3.3</a>).

The numeric types consist of the <span class="emphasis">*integral
types*</span> (<a href="jvms-2.html#jvms-2.3.1" class="xref"
title="2.3.1. Integral Types and Values">§2.3.1</a>) and the
<span class="emphasis">*floating-point types*</span>
(<a href="jvms-2.html#jvms-2.3.2" class="xref"
title="2.3.2. Floating-Point Types and Values">§2.3.2</a>).

The integral types are:

<div class="norm">

- `byte`, whose values are 8-bit signed two's-complement integers, and
  whose default value is zero

- `short`, whose values are 16-bit signed two's-complement integers, and
  whose default value is zero

- `int`, whose values are 32-bit signed two's-complement integers, and
  whose default value is zero

- `long`, whose values are 64-bit signed two's-complement integers, and
  whose default value is zero

- `char`, whose values are 16-bit unsigned integers representing Unicode
  code points in the Basic Multilingual Plane, encoded with UTF-16, and
  whose default value is the null code point (`'\u0000'`)

</div>

The floating-point types are:

<div class="norm">

- `float`, whose values exactly correspond to the values representable
  in the 32-bit IEEE 754 binary32 format, and whose default value is
  positive zero

- `double`, whose values exactly correspond to the values of the 64-bit
  IEEE 754 binary64 format, and whose default value is positive zero

</div>

The values of the `boolean` type encode the truth values `true` and
`false`, and the default value is `false`.

The First Edition of *The <span class="trademark">Java</span>® Virtual
Machine Specification* did not consider `boolean` to be a Java Virtual
Machine type. However, `boolean` values do have limited support in the
Java Virtual Machine. The Second Edition of *The
<span class="trademark">Java</span>® Virtual Machine Specification*
clarified the issue by treating `boolean` as a type.

The values of the `returnAddress` type are pointers to the opcodes of
Java Virtual Machine instructions. Of the primitive types, only the
`returnAddress` type is not directly associated with a Java programming
language type.

<div id="jvms-2.3.1" class="section">

<div class="titlepage">

<div>

<div>

### 2.3.1. Integral Types and Values

</div>

</div>

</div>

The values of the integral types of the Java Virtual Machine are:

<div class="norm">

- For `byte`, from -128 to 127 (-2<sup>7</sup> to 2<sup>7</sup> - 1),
  inclusive

- For `short`, from -32768 to 32767 (-2<sup>15</sup> to 2<sup>15</sup> -
  1), inclusive

- For `int`, from -2147483648 to 2147483647 (-2<sup>31</sup> to
  2<sup>31</sup> - 1), inclusive

- For `long`, from -9223372036854775808 to 9223372036854775807
  (-2<sup>63</sup> to 2<sup>63</sup> - 1), inclusive

- For `char`, from 0 to 65535 inclusive

</div>

</div>

<div id="jvms-2.3.2" class="section">

<div class="titlepage">

<div>

<div>

### 2.3.2. Floating-Point Types and Values

</div>

</div>

</div>

The floating-point types are `float` and `double`, which are
conceptually associated with the 32-bit binary32 and 64-bit binary64
floating-point formats for IEEE 754 values and operations, as specified
in the IEEE 754 Standard (JLS §1.7).

In Java SE 15 and later, the Java Virtual Machine uses the 2019 version
of the IEEE 754 Standard. Prior to Java SE 15, the Java Virtual Machine
used the 1985 version of the IEEE 754 Standard, where the binary32
format was known as the single format and the binary64 format was known
as the double format.

IEEE 754 includes not only positive and negative numbers that consist of
a sign and magnitude, but also positive and negative zeros, positive and
negative <span class="emphasis">*infinities*</span>, and special
<span class="emphasis">*Not-a-Number*</span> values (hereafter
abbreviated NaN). A NaN value is used to represent the result of certain
invalid operations such as dividing zero by zero. NaN constants of both
`float` and `double` type are predefined as `Float.NaN` and
`Double.NaN`.

The finite nonzero values of a floating-point type can all be expressed
in the form <span class="emphasis">*s*</span>
<span class="symbol">⋅</span> <span class="emphasis">*m*</span>
<span class="symbol">⋅</span> 2<sup>(<span class="emphasis">*e*</span> -
`N` + 1)</sup>, where:

<div class="norm">

- <span class="emphasis">*s*</span> is +1 or -1,

- <span class="emphasis">*m*</span> is a positive integer less than
  2<sup>`N`</sup>,

- <span class="emphasis">*e*</span> is an integer between
  <span class="emphasis">*E<sub>min</sub>*</span> =
  -(2<sup><span class="type">K</span>-1</sup>-2) and
  <span class="emphasis">*E<sub>max</sub>*</span> =
  2<sup><span class="type">K</span>-1</sup>-1, inclusive, and

- `N` and <span class="type">K</span> are parameters that depend on the
  type.

</div>

Some values can be represented in this form in more than one way. For
example, supposing that a value `v` of a floating-point type might be
represented in this form using certain values for
<span class="emphasis">*s*</span>, <span class="emphasis">*m*</span>,
and <span class="emphasis">*e*</span>, then if it happened that
<span class="emphasis">*m*</span> were even and
<span class="emphasis">*e*</span> were less than
2<sup><span class="type">K</span>-1</sup>, one could halve
<span class="emphasis">*m*</span> and increase
<span class="emphasis">*e*</span> by 1 to produce a second
representation for the same value `v`.

A representation in this form is called
<span class="emphasis">*normalized*</span> if
<span class="emphasis">*m*</span> <span class="symbol">≥</span>
2<sup>`N`-1</sup>; otherwise the representation is said to be
<span class="emphasis">*subnormal*</span>. If a value of a
floating-point type cannot be represented in such a way that
<span class="emphasis">*m*</span> <span class="symbol">≥</span>
2<sup>`N`-1</sup>, then the value is said to be a
<span class="emphasis">*subnormal value*</span>, because its magnitude
is below the magnitude of the smallest normalized value.

The constraints on the parameters `N` and <span class="type">K</span>
(and on the derived parameters
<span class="emphasis">*E<sub>min</sub>*</span> and
<span class="emphasis">*E<sub>max</sub>*</span>) for `float` and
`double` are summarized in
<a href="jvms-2.html#jvms-2.3.2-150-A" class="xref"
title="Table 2.3.2-A. Floating-point parameters">Table 2.3.2-A</a>.

<div id="jvms-2.3.2-150-A" class="table">

**Table 2.3.2-A. Floating-point parameters**

<div class="table-contents">

| Parameter                                       | `float` | `double` |
|-------------------------------------------------|---------|----------|
| `N`                                             | 24      | 53       |
| <span class="type">K</span>                     | 8       | 11       |
| <span class="emphasis">*E<sub>max</sub>*</span> | +127    | +1023    |
| <span class="emphasis">*E<sub>min</sub>*</span> | -126    | -1022    |

</div>

</div>

  

Except for NaN, floating-point values are
<span class="emphasis">*ordered*</span>. When arranged from smallest to
largest, they are negative infinity, negative finite nonzero values,
positive and negative zero, positive finite nonzero values, and positive
infinity.

IEEE 754 allows multiple distinct NaN values for each of its binary32
and binary64 floating-point formats. However, the Java SE Platform
generally treats NaN values of a given floating-point type as though
collapsed into a single canonical value, and hence this specification
normally refers to an arbitrary NaN as though to a canonical value.

Under IEEE 754, a floating-point operation with non-NaN arguments may
generate a NaN result. IEEE 754 specifies a set of NaN bit patterns, but
does not mandate which particular NaN bit pattern is used to represent a
NaN result; this is left to the hardware architecture. A programmer can
create NaNs with different bit patterns to encode, for example,
retrospective diagnostic information. These NaN values can be created
with the `Float.intBitsToFloat` and `Double.longBitsToDouble` methods
for `float` and `double`, respectively. Conversely, to inspect the bit
patterns of NaN values, the `Float.floatToRawIntBits` and
`Double.doubleToRawLongBits` methods can be used for `float` and
`double`, respectively.

Positive zero and negative zero compare equal, but there are other
operations that can distinguish them; for example, dividing `1.0` by
`0.0` produces positive infinity, but dividing `1.0` by `-0.0` produces
negative infinity.

NaN is <span class="emphasis">*unordered*</span>, so numerical
comparisons and tests for numerical equality have the value `false` if
either or both of their operands are NaN. In particular, a test for
numerical equality of a value against itself has the value `false` if
and only if the value is NaN. A test for numerical inequality has the
value `true` if either operand is NaN.

</div>

<div id="jvms-2.3.3" class="section">

<div class="titlepage">

<div>

<div>

### 2.3.3. The `returnAddress` Type and Values

</div>

</div>

</div>

The `returnAddress` type is used by the Java Virtual Machine's
<span class="emphasis">*jsr*</span>,
<span class="emphasis">*ret*</span>, and
<span class="emphasis">*jsr_w*</span> instructions
(<a href="jvms-6.html#jvms-6.5.jsr" class="xref" title="jsr">§<span
class="emphasis"><em>jsr</em></span></a>,
<a href="jvms-6.html#jvms-6.5.ret" class="xref" title="ret">§<span
class="emphasis"><em>ret</em></span></a>,
<a href="jvms-6.html#jvms-6.5.jsr_w" class="xref" title="jsr_w">§<span
class="emphasis"><em>jsr_w</em></span></a>). The values of the
`returnAddress` type are pointers to the opcodes of Java Virtual Machine
instructions. Unlike the numeric primitive types, the `returnAddress`
type does not correspond to any Java programming language type and
cannot be modified by the running program.

</div>

<div id="jvms-2.3.4" class="section">

<div class="titlepage">

<div>

<div>

### 2.3.4. The `boolean` Type

</div>

</div>

</div>

Although the Java Virtual Machine defines a `boolean` type, it only
provides very limited support for it. There are no Java Virtual Machine
instructions solely dedicated to operations on `boolean` values.
Instead, expressions in the Java programming language that operate on
`boolean` values are compiled to use values of the Java Virtual Machine
`int` data type.

The Java Virtual Machine does directly support `boolean` arrays. Its
<span class="emphasis">*newarray*</span> instruction
(<a href="jvms-6.html#jvms-6.5.newarray" class="xref"
title="newarray">§<span class="emphasis"><em>newarray</em></span></a>)
enables creation of `boolean` arrays. Arrays of type `boolean` are
accessed and modified using the `byte` array instructions
<span class="emphasis">*baload*</span> and
<span class="emphasis">*bastore*</span>
(<a href="jvms-6.html#jvms-6.5.baload" class="xref" title="baload">§<span
class="emphasis"><em>baload</em></span></a>,
<a href="jvms-6.html#jvms-6.5.bastore" class="xref"
title="bastore">§<span class="emphasis"><em>bastore</em></span></a>).

In Oracle’s Java Virtual Machine implementation, `boolean` arrays in the
Java programming language are encoded as Java Virtual Machine `byte`
arrays, using 8 bits per `boolean` element.

The Java Virtual Machine encodes `boolean` array components using `1` to
represent `true` and `0` to represent `false`. Where Java programming
language `boolean` values are mapped by compilers to values of Java
Virtual Machine type `int`, the compilers must use the same encoding.

</div>

</div>

<div id="jvms-2.4" class="section">

<div class="titlepage">

<div>

<div>

## 2.4. Reference Types and Values

</div>

</div>

</div>

There are three kinds of `reference` types: class types, array types,
and interface types. Their values are references to dynamically created
class instances, arrays, or class instances or arrays that implement
interfaces, respectively.

An array type consists of a <span class="emphasis">*component
type*</span> with a single dimension (whose length is not given by the
type). The component type of an array type may itself be an array type.
If, starting from any array type, one considers its component type, and
then (if that is also an array type) the component type of that type,
and so on, eventually one must reach a component type that is not an
array type; this is called the <span class="emphasis">*element
type*</span> of the array type. The element type of an array type is
necessarily either a primitive type, or a class type, or an interface
type.

A `reference` value may also be the special null reference, a reference
to no object, which will be denoted here by `null`. The `null` reference
initially has no run-time type, but may be cast to any type. The default
value of a `reference` type is `null`.

This specification does not mandate a concrete value encoding `null`.

</div>

<div id="jvms-2.5" class="section">

<div class="titlepage">

<div>

<div>

## 2.5. Run-Time Data Areas

</div>

</div>

</div>

The Java Virtual Machine defines various run-time data areas that are
used during execution of a program. Some of these data areas are created
on Java Virtual Machine start-up and are destroyed only when the Java
Virtual Machine terminates. Other data areas are per thread. Per-thread
data areas are created when a thread is created and destroyed when the
thread terminates.

<div id="jvms-2.5.1" class="section">

<div class="titlepage">

<div>

<div>

### 2.5.1. The `pc` Register

</div>

</div>

</div>

The Java Virtual Machine can support many threads of execution at once
(JLS §17). Each Java Virtual Machine thread has its own `pc` (program
counter) register. At any point, each Java Virtual Machine thread is
executing the code of a single method, namely the current method
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>)
for that thread. If that method is not `native`, the `pc` register
contains the address of the Java Virtual Machine instruction currently
being executed. If the method currently being executed by the thread is
`native`, the value of the Java Virtual Machine's `pc` register is
undefined. The Java Virtual Machine's `pc` register is wide enough to
hold a `returnAddress` or a native pointer on the specific platform.

</div>

<div id="jvms-2.5.2" class="section">

<div class="titlepage">

<div>

<div>

### 2.5.2. Java Virtual Machine Stacks

</div>

</div>

</div>

Each Java Virtual Machine thread has a private
<span class="emphasis">*Java Virtual Machine stack*</span>, created at
the same time as the thread. A Java Virtual Machine stack stores frames
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>).
A Java Virtual Machine stack is analogous to the stack of a conventional
language such as C: it holds local variables and partial results, and
plays a part in method invocation and return. Because the Java Virtual
Machine stack is never manipulated directly except to push and pop
frames, frames may be heap allocated. The memory for a Java Virtual
Machine stack does not need to be contiguous.

In the First Edition of *The <span class="trademark">Java</span>®
Virtual Machine Specification*, the Java Virtual Machine stack was known
as the <span class="emphasis">*Java stack*</span>.

This specification permits Java Virtual Machine stacks either to be of a
fixed size or to dynamically expand and contract as required by the
computation. If the Java Virtual Machine stacks are of a fixed size, the
size of each Java Virtual Machine stack may be chosen independently when
that stack is created.

A Java Virtual Machine implementation may provide the programmer or the
user control over the initial size of Java Virtual Machine stacks, as
well as, in the case of dynamically expanding or contracting Java
Virtual Machine stacks, control over the maximum and minimum sizes.

The following exceptional conditions are associated with Java Virtual
Machine stacks:

<div class="norm">

- If the computation in a thread requires a larger Java Virtual Machine
  stack than is permitted, the Java Virtual Machine throws a
  `StackOverflowError`.

- If Java Virtual Machine stacks can be dynamically expanded, and
  expansion is attempted but insufficient memory can be made available
  to effect the expansion, or if insufficient memory can be made
  available to create the initial Java Virtual Machine stack for a new
  thread, the Java Virtual Machine throws an `OutOfMemoryError`.

</div>

</div>

<div id="jvms-2.5.3" class="section">

<div class="titlepage">

<div>

<div>

### 2.5.3. Heap

</div>

</div>

</div>

The Java Virtual Machine has a <span class="emphasis">*heap*</span> that
is shared among all Java Virtual Machine threads. The heap is the
run-time data area from which memory for all class instances and arrays
is allocated.

The heap is created on virtual machine start-up. Heap storage for
objects is reclaimed by an automatic storage management system (known as
a <span class="emphasis">*garbage collector*</span>); objects are never
explicitly deallocated. The Java Virtual Machine assumes no particular
type of automatic storage management system, and the storage management
technique may be chosen according to the implementor's system
requirements. The heap may be of a fixed size or may be expanded as
required by the computation and may be contracted if a larger heap
becomes unnecessary. The memory for the heap does not need to be
contiguous.

A Java Virtual Machine implementation may provide the programmer or the
user control over the initial size of the heap, as well as, if the heap
can be dynamically expanded or contracted, control over the maximum and
minimum heap size.

The following exceptional condition is associated with the heap:

<div class="norm">

- If a computation requires more heap than can be made available by the
  automatic storage management system, the Java Virtual Machine throws
  an `OutOfMemoryError`.

</div>

</div>

<div id="jvms-2.5.4" class="section">

<div class="titlepage">

<div>

<div>

### 2.5.4. Method Area

</div>

</div>

</div>

The Java Virtual Machine has a <span class="emphasis">*method
area*</span> that is shared among all Java Virtual Machine threads. The
method area is analogous to the storage area for compiled code of a
conventional language or analogous to the "text" segment in an operating
system process. It stores per-class structures such as the run-time
constant pool, field and method data, and the code for methods and
constructors, including the special methods used in class and interface
initialization and in instance initialization
(<a href="jvms-2.html#jvms-2.9" class="xref"
title="2.9. Special Methods">§2.9</a>).

The method area is created on virtual machine start-up. Although the
method area is logically part of the heap, simple implementations may
choose not to either garbage collect or compact it. This specification
does not mandate the location of the method area or the policies used to
manage compiled code. The method area may be of a fixed size or may be
expanded as required by the computation and may be contracted if a
larger method area becomes unnecessary. The memory for the method area
does not need to be contiguous.

A Java Virtual Machine implementation may provide the programmer or the
user control over the initial size of the method area, as well as, in
the case of a varying-size method area, control over the maximum and
minimum method area size.

The following exceptional condition is associated with the method area:

<div class="norm">

- If memory in the method area cannot be made available to satisfy an
  allocation request, the Java Virtual Machine throws an
  `OutOfMemoryError`.

</div>

</div>

<div id="jvms-2.5.5" class="section">

<div class="titlepage">

<div>

<div>

### 2.5.5. Run-Time Constant Pool

</div>

</div>

</div>

A <span class="emphasis">*run-time constant pool*</span> is a per-class
or per-interface run-time representation of the `constant_pool` table in
a `class` file (<a href="jvms-4.html#jvms-4.4" class="xref"
title="4.4. The Constant Pool">§4.4</a>). It contains several kinds of
constants, ranging from numeric literals known at compile-time to method
and field references that must be resolved at run-time. The run-time
constant pool serves a function similar to that of a symbol table for a
conventional programming language, although it contains a wider range of
data than a typical symbol table.

Each run-time constant pool is allocated from the Java Virtual Machine's
method area (<a href="jvms-2.html#jvms-2.5.4" class="xref"
title="2.5.4. Method Area">§2.5.4</a>). The run-time constant pool for a
class or interface is constructed when the class or interface is created
(<a href="jvms-5.html#jvms-5.3" class="xref"
title="5.3. Creation and Loading">§5.3</a>) by the Java Virtual Machine.

The following exceptional condition is associated with the construction
of the run-time constant pool for a class or interface:

<div class="norm">

- When creating a class or interface, if the construction of the
  run-time constant pool requires more memory than can be made available
  in the method area of the Java Virtual Machine, the Java Virtual
  Machine throws an `OutOfMemoryError`.

</div>

See <a href="jvms-5.html" class="xref"
title="Chapter 5. Loading, Linking, and Initializing">§5 (<em>Loading,
Linking, and Initializing</em>)</a> for information about the
construction of the run-time constant pool.

</div>

<div id="jvms-2.5.6" class="section">

<div class="titlepage">

<div>

<div>

### 2.5.6. Native Method Stacks

</div>

</div>

</div>

An implementation of the Java Virtual Machine may use conventional
stacks, colloquially called "C stacks," to support `native` methods
(methods written in a language other than the Java programming
language). Native method stacks may also be used by the implementation
of an interpreter for the Java Virtual Machine's instruction set in a
language such as C. Java Virtual Machine implementations that cannot
load `native` methods and that do not themselves rely on conventional
stacks need not supply native method stacks. If supplied, native method
stacks are typically allocated per thread when each thread is created.

This specification permits native method stacks either to be of a fixed
size or to dynamically expand and contract as required by the
computation. If the native method stacks are of a fixed size, the size
of each native method stack may be chosen independently when that stack
is created.

A Java Virtual Machine implementation may provide the programmer or the
user control over the initial size of the native method stacks, as well
as, in the case of varying-size native method stacks, control over the
maximum and minimum method stack sizes.

The following exceptional conditions are associated with native method
stacks:

<div class="norm">

- If the computation in a thread requires a larger native method stack
  than is permitted, the Java Virtual Machine throws a
  `StackOverflowError`.

- If native method stacks can be dynamically expanded and native method
  stack expansion is attempted but insufficient memory can be made
  available, or if insufficient memory can be made available to create
  the initial native method stack for a new thread, the Java Virtual
  Machine throws an `OutOfMemoryError`.

</div>

</div>

</div>

<div id="jvms-2.6" class="section">

<div class="titlepage">

<div>

<div>

## 2.6. Frames

</div>

</div>

</div>

A <span class="emphasis">*frame*</span> is used to store data and
partial results, as well as to perform dynamic linking, return values
for methods, and dispatch exceptions.

A new frame is created each time a method is invoked. A frame is
destroyed when its method invocation completes, whether that completion
is normal or abrupt (it throws an uncaught exception). Frames are
allocated from the Java Virtual Machine stack
(<a href="jvms-2.html#jvms-2.5.2" class="xref"
title="2.5.2. Java Virtual Machine Stacks">§2.5.2</a>) of the thread
creating the frame. Each frame has its own array of local variables
(<a href="jvms-2.html#jvms-2.6.1" class="xref"
title="2.6.1. Local Variables">§2.6.1</a>), its own operand stack
(<a href="jvms-2.html#jvms-2.6.2" class="xref"
title="2.6.2. Operand Stacks">§2.6.2</a>), and a reference to the
run-time constant pool (<a href="jvms-2.html#jvms-2.5.5" class="xref"
title="2.5.5. Run-Time Constant Pool">§2.5.5</a>) of the class of the
current method.

A frame may be extended with additional implementation-specific
information, such as debugging information.

The sizes of the local variable array and the operand stack are
determined at compile-time and are supplied along with the code for the
method associated with the frame
(<a href="jvms-4.html#jvms-4.7.3" class="xref"
title="4.7.3. The Code Attribute">§4.7.3</a>). Thus the size of the
frame data structure depends only on the implementation of the Java
Virtual Machine, and the memory for these structures can be allocated
simultaneously on method invocation.

Only one frame, the frame for the executing method, is active at any
point in a given thread of control. This frame is referred to as the
<span class="emphasis">*current frame*</span>, and its method is known
as the <span class="emphasis">*current method*</span>. The class in
which the current method is defined is the
<span class="emphasis">*current class*</span>. Operations on local
variables and the operand stack are typically with reference to the
current frame.

A frame ceases to be current if its method invokes another method or if
its method completes. When a method is invoked, a new frame is created
and becomes current when control transfers to the new method. On method
return, the current frame passes back the result of its method
invocation, if any, to the previous frame. The current frame is then
discarded as the previous frame becomes the current one.

Note that a frame created by a thread is local to that thread and cannot
be referenced by any other thread.

<div id="jvms-2.6.1" class="section">

<div class="titlepage">

<div>

<div>

### 2.6.1. Local Variables

</div>

</div>

</div>

Each frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>)
contains an array of variables known as its
<span class="emphasis">*local variables*</span>. The length of the local
variable array of a frame is determined at compile-time and supplied in
the binary representation of a class or interface along with the code
for the method associated with the frame
(<a href="jvms-4.html#jvms-4.7.3" class="xref"
title="4.7.3. The Code Attribute">§4.7.3</a>).

A single local variable can hold a value of type `int`, `float`,
`reference`, or `returnAddress`. A pair of local variables can hold a
value of type `long` or `double`.

Local variables are addressed by indexing. The index of the first local
variable is zero. An integer is considered to be an index into the local
variable array if and only if that integer is between zero and one less
than the size of the local variable array.

A value of type `long` or type `double` occupies two consecutive local
variables. Such a value may only be addressed using the lesser index.
For example, a value of type `double` stored in the local variable array
at index <span class="emphasis">*n*</span> actually occupies the local
variables with indices <span class="emphasis">*n*</span> and
<span class="emphasis">*n*</span>+1; however, the local variable at
index <span class="emphasis">*n*</span>+1 cannot be loaded from. It can
be stored into. However, doing so invalidates the contents of local
variable <span class="emphasis">*n*</span>.

The Java Virtual Machine does not require
<span class="emphasis">*n*</span> to be even. In intuitive terms, values
of types `long` and `double` need not be 64-bit aligned in the local
variables array. Implementors are free to decide the appropriate way to
represent such values using the two local variables reserved for the
value.

The Java Virtual Machine uses local variables to pass parameters on
method invocation. On class method invocation, any parameters are passed
in consecutive local variables starting from local variable
<span class="emphasis">*0*</span>. On instance method invocation, local
variable <span class="emphasis">*0*</span> is always used to pass a
reference to the object on which the instance method is being invoked
(`this` in the Java programming language). Any parameters are
subsequently passed in consecutive local variables starting from local
variable <span class="emphasis">*1*</span>.

</div>

<div id="jvms-2.6.2" class="section">

<div class="titlepage">

<div>

<div>

### 2.6.2. Operand Stacks

</div>

</div>

</div>

Each frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>)
contains a last-in-first-out (LIFO) stack known as its
<span class="emphasis">*operand stack*</span>. The maximum depth of the
operand stack of a frame is determined at compile-time and is supplied
along with the code for the method associated with the frame
(<a href="jvms-4.html#jvms-4.7.3" class="xref"
title="4.7.3. The Code Attribute">§4.7.3</a>).

Where it is clear by context, we will sometimes refer to the operand
stack of the current frame as simply the operand stack.

The operand stack is empty when the frame that contains it is created.
The Java Virtual Machine supplies instructions to load constants or
values from local variables or fields onto the operand stack. Other Java
Virtual Machine instructions take operands from the operand stack,
operate on them, and push the result back onto the operand stack. The
operand stack is also used to prepare parameters to be passed to methods
and to receive method results.

For example, the <span class="emphasis">*iadd*</span> instruction
(<a href="jvms-6.html#jvms-6.5.iadd" class="xref" title="iadd">§<span
class="emphasis"><em>iadd</em></span></a>) adds two `int` values
together. It requires that the `int` values to be added be the top two
values of the operand stack, pushed there by previous instructions. Both
of the `int` values are popped from the operand stack. They are added,
and their sum is pushed back onto the operand stack. Subcomputations may
be nested on the operand stack, resulting in values that can be used by
the encompassing computation.

Each entry on the operand stack can hold a value of any Java Virtual
Machine type, including a value of type `long` or type `double`.

Values from the operand stack must be operated upon in ways appropriate
to their types. It is not possible, for example, to push two `int`
values and subsequently treat them as a `long` or to push two `float`
values and subsequently add them with an
<span class="emphasis">*iadd*</span> instruction. A small number of Java
Virtual Machine instructions (the <span class="emphasis">*dup*</span>
instructions
(<a href="jvms-6.html#jvms-6.5.dup" class="xref" title="dup">§<span
class="emphasis"><em>dup</em></span></a>) and
<span class="emphasis">*swap*</span>
(<a href="jvms-6.html#jvms-6.5.swap" class="xref" title="swap">§<span
class="emphasis"><em>swap</em></span></a>)) operate on run-time data
areas as raw values without regard to their specific types; these
instructions are defined in such a way that they cannot be used to
modify or break up individual values. These restrictions on operand
stack manipulation are enforced through `class` file verification
(<a href="jvms-4.html#jvms-4.10" class="xref"
title="4.10. Verification of class Files">§4.10</a>).

At any point in time, an operand stack has an associated depth, where a
value of type `long` or `double` contributes two units to the depth and
a value of any other type contributes one unit.

</div>

<div id="jvms-2.6.3" class="section">

<div class="titlepage">

<div>

<div>

### 2.6.3. Dynamic Linking

</div>

</div>

</div>

Each frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>)
contains a reference to the run-time constant pool
(<a href="jvms-2.html#jvms-2.5.5" class="xref"
title="2.5.5. Run-Time Constant Pool">§2.5.5</a>) for the type of the
current method to support <span class="emphasis">*dynamic
linking*</span> of the method code. The `class` file code for a method
refers to methods to be invoked and variables to be accessed via
symbolic references. Dynamic linking translates these symbolic method
references into concrete method references, loading classes as necessary
to resolve as-yet-undefined symbols, and translates variable accesses
into appropriate offsets in storage structures associated with the
run-time location of these variables.

This late binding of the methods and variables makes changes in other
classes that a method uses less likely to break this code.

</div>

<div id="jvms-2.6.4" class="section">

<div class="titlepage">

<div>

<div>

### 2.6.4. Normal Method Invocation Completion

</div>

</div>

</div>

A method invocation <span class="emphasis">*completes normally*</span>
if that invocation does not cause an exception
(<a href="jvms-2.html#jvms-2.10" class="xref"
title="2.10. Exceptions">§2.10</a>) to be thrown, either directly from
the Java Virtual Machine or as a result of executing an explicit `throw`
statement. If the invocation of the current method completes normally,
then a value may be returned to the invoking method. This occurs when
the invoked method executes one of the return instructions
(<a href="jvms-2.html#jvms-2.11.8" class="xref"
title="2.11.8. Method Invocation and Return Instructions">§2.11.8</a>),
the choice of which must be appropriate for the type of the value being
returned (if any).

The current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>)
is used in this case to restore the state of the invoker, including its
local variables and operand stack, with the program counter of the
invoker appropriately incremented to skip past the method invocation
instruction. Execution then continues normally in the invoking method's
frame with the returned value (if any) pushed onto the operand stack of
that frame.

</div>

<div id="jvms-2.6.5" class="section">

<div class="titlepage">

<div>

<div>

### 2.6.5. Abrupt Method Invocation Completion

</div>

</div>

</div>

A method invocation <span class="emphasis">*completes abruptly*</span>
if execution of a Java Virtual Machine instruction within the method
causes the Java Virtual Machine to throw an exception
(<a href="jvms-2.html#jvms-2.10" class="xref"
title="2.10. Exceptions">§2.10</a>), and that exception is not handled
within the method. Execution of an
<span class="emphasis">*athrow*</span> instruction
(<a href="jvms-6.html#jvms-6.5.athrow" class="xref" title="athrow">§<span
class="emphasis"><em>athrow</em></span></a>) also causes an exception to
be explicitly thrown and, if the exception is not caught by the current
method, results in abrupt method invocation completion. A method
invocation that completes abruptly never returns a value to its invoker.

</div>

</div>

<div id="jvms-2.7" class="section">

<div class="titlepage">

<div>

<div>

## 2.7. Representation of Objects

</div>

</div>

</div>

The Java Virtual Machine does not mandate any particular internal
structure for objects.

In some of Oracle’s implementations of the Java Virtual Machine, a
reference to a class instance is a pointer to a
<span class="emphasis">*handle*</span> that is itself a pair of
pointers: one to a table containing the methods of the object and a
pointer to the `Class` object that represents the type of the object,
and the other to the memory allocated from the heap for the object data.

</div>

<div id="jvms-2.8" class="section">

<div class="titlepage">

<div>

<div>

## 2.8. Floating-Point Arithmetic

</div>

</div>

</div>

The Java Virtual Machine incorporates a subset of the floating-point
arithmetic specified in the IEEE 754 Standard (JLS §1.7).

In Java SE 15 and later, the Java Virtual Machine uses the 2019 version
of the IEEE 754 Standard. Prior to Java SE 15, the Java Virtual Machine
used the 1985 version of the IEEE 754 Standard, where the binary32
format was known as the single format and the binary64 format was known
as the double format.

Many of the Java Virtual Machine instructions for arithmetic
(<a href="jvms-2.html#jvms-2.11.3" class="xref"
title="2.11.3. Arithmetic Instructions">§2.11.3</a>) and type conversion
(<a href="jvms-2.html#jvms-2.11.4" class="xref"
title="2.11.4. Type Conversion Instructions">§2.11.4</a>) work with
floating-point numbers. These instructions typically correspond to IEEE
754 operations (<a href="jvms-2.html#jvms-2.8-200-A" class="xref"
title="Table 2.8-A. Correspondence with IEEE 754 operations">Table 2.8-A</a>),
except for certain instructions described below.

<div id="jvms-2.8-200-A" class="table">

**Table 2.8-A. Correspondence with IEEE 754 operations**

<div class="table-contents">

| Instruction | IEEE 754 operation |
|----|----|
| <span class="emphasis">*dcmp\<op\>*</span> (<a href="jvms-6.html#jvms-6.5.dcmp_op" class="xref"
title="dcmp&lt;op&gt;">§<span
class="emphasis"><em>dcmp&lt;op&gt;</em></span></a>), <span class="emphasis">*fcmp\<op\>*</span> (<a href="jvms-6.html#jvms-6.5.fcmp_op" class="xref"
title="fcmp&lt;op&gt;">§<span
class="emphasis"><em>fcmp&lt;op&gt;</em></span></a>) | compareQuietLess, compareQuietLessEqual, compareQuietGreater, compareQuietGreaterEqual, compareQuietEqual, compareQuietNotEqual |
| <span class="emphasis">*dadd*</span> (<a href="jvms-6.html#jvms-6.5.dadd" class="xref" title="dadd">§<span
class="emphasis"><em>dadd</em></span></a>), <span class="emphasis">*fadd*</span> (<a href="jvms-6.html#jvms-6.5.fadd" class="xref" title="fadd">§<span
class="emphasis"><em>fadd</em></span></a>) | addition |
| <span class="emphasis">*dsub*</span> (<a href="jvms-6.html#jvms-6.5.dsub" class="xref" title="dsub">§<span
class="emphasis"><em>dsub</em></span></a>), <span class="emphasis">*fsub*</span> (<a href="jvms-6.html#jvms-6.5.fsub" class="xref" title="fsub">§<span
class="emphasis"><em>fsub</em></span></a>) | subtraction |
| <span class="emphasis">*dmul*</span> (<a href="jvms-6.html#jvms-6.5.dmul" class="xref" title="dmul">§<span
class="emphasis"><em>dmul</em></span></a>), <span class="emphasis">*fmul*</span> (<a href="jvms-6.html#jvms-6.5.fmul" class="xref" title="fmul">§<span
class="emphasis"><em>fmul</em></span></a>) | multiplication |
| <span class="emphasis">*ddiv*</span> (<a href="jvms-6.html#jvms-6.5.ddiv" class="xref" title="ddiv">§<span
class="emphasis"><em>ddiv</em></span></a>), <span class="emphasis">*fdiv*</span> (<a href="jvms-6.html#jvms-6.5.fdiv" class="xref" title="fdiv">§<span
class="emphasis"><em>fdiv</em></span></a>) | division |
| <span class="emphasis">*dneg*</span> (<a href="jvms-6.html#jvms-6.5.dneg" class="xref" title="dneg">§<span
class="emphasis"><em>dneg</em></span></a>), <span class="emphasis">*fneg*</span> (<a href="jvms-6.html#jvms-6.5.fneg" class="xref" title="fneg">§<span
class="emphasis"><em>fneg</em></span></a>) | negate |
| <span class="emphasis">*i2d*</span> (<a href="jvms-6.html#jvms-6.5.i2d" class="xref" title="i2d">§<span
class="emphasis"><em>i2d</em></span></a>), <span class="emphasis">*i2f*</span> (<a href="jvms-6.html#jvms-6.5.i2f" class="xref" title="i2f">§<span
class="emphasis"><em>i2f</em></span></a>), <span class="emphasis">*l2d*</span> (<a href="jvms-6.html#jvms-6.5.l2d" class="xref" title="l2d">§<span
class="emphasis"><em>l2d</em></span></a>), <span class="emphasis">*l2f*</span> (<a href="jvms-6.html#jvms-6.5.l2f" class="xref" title="l2f">§<span
class="emphasis"><em>l2f</em></span></a>) | convertFromInt |
| <span class="emphasis">*d2i*</span> (<a href="jvms-6.html#jvms-6.5.d2i" class="xref" title="d2i">§<span
class="emphasis"><em>d2i</em></span></a>), <span class="emphasis">*d2l*</span> (<a href="jvms-6.html#jvms-6.5.d2l" class="xref" title="d2l">§<span
class="emphasis"><em>d2l</em></span></a>), <span class="emphasis">*f2i*</span> (<a href="jvms-6.html#jvms-6.5.f2i" class="xref" title="f2i">§<span
class="emphasis"><em>f2i</em></span></a>), <span class="emphasis">*f2l*</span> (<a href="jvms-6.html#jvms-6.5.f2l" class="xref" title="f2l">§<span
class="emphasis"><em>f2l</em></span></a>) | convertToIntegerTowardZero |
| <span class="emphasis">*d2f*</span> (<a href="jvms-6.html#jvms-6.5.d2f" class="xref" title="d2f">§<span
class="emphasis"><em>d2f</em></span></a>), <span class="emphasis">*f2d*</span> (<a href="jvms-6.html#jvms-6.5.f2d" class="xref" title="f2d">§<span
class="emphasis"><em>f2d</em></span></a>) | convertFormat |

</div>

</div>

  

The key differences between the floating-point arithmetic supported by
the Java Virtual Machine and the IEEE 754 Standard are:

<div class="norm">

- The floating-point remainder instructions
  <span class="emphasis">*drem*</span>
  (<a href="jvms-6.html#jvms-6.5.drem" class="xref" title="drem">§<span
  class="emphasis"><em>drem</em></span></a>) and
  <span class="emphasis">*frem*</span>
  (<a href="jvms-6.html#jvms-6.5.frem" class="xref" title="frem">§<span
  class="emphasis"><em>frem</em></span></a>) do not correspond to the
  IEEE 754 remainder operation. The instructions are based on an implied
  division using the round toward zero rounding policy; the IEEE 754
  remainder is instead based on an implied division using the round to
  nearest rounding policy. (Rounding policies are discussed below.)

- The floating-point negate instructions
  <span class="emphasis">*dneg*</span>
  (<a href="jvms-6.html#jvms-6.5.dneg" class="xref" title="dneg">§<span
  class="emphasis"><em>dneg</em></span></a>) and
  <span class="emphasis">*fneg*</span>
  (<a href="jvms-6.html#jvms-6.5.fneg" class="xref" title="fneg">§<span
  class="emphasis"><em>fneg</em></span></a>) do not correspond precisely
  to the IEEE 754 negate operation. In particular, the instructions do
  not require the sign bit of a NaN operand to be inverted.

- The floating-point instructions of the Java Virtual Machine do not
  throw exceptions, trap, or otherwise signal the IEEE 754 exceptional
  conditions of invalid operation, division by zero, overflow,
  underflow, or inexact.

- The Java Virtual Machine does not support IEEE 754 signaling
  floating-point comparisons, and has no signaling NaN value.

- IEEE 754 includes rounding-direction attributes that do not correspond
  to a rounding policy in the Java Virtual Machine. The Java Virtual
  Machine does not provide any means to change the rounding policy used
  by a given floating-point instruction.

- The Java Virtual Machine does not support the binary32 extended and
  binary64 extended floating-point formats defined by IEEE 754. Neither
  extended range nor extended precision beyond those specified for the
  `float` and `double` types may be used when operating on or storing
  floating-point values.

</div>

Some IEEE 754 operations without corresponding instructions in the Java
Virtual Machine are provided via methods in the `Math` and `StrictMath`
classes, including the `sqrt` method for the IEEE 754 squareRoot
operation, the `fma` method for the IEEE 754 fusedMultiplyAdd operation,
and the `IEEEremainder` method for the IEEE 754 remainder operation.

The Java Virtual Machine requires support of IEEE 754
<span class="emphasis">*subnormal*</span> floating-point numbers and
<span class="emphasis">*gradual underflow*</span>, which make it easier
to prove desirable properties of particular numerical algorithms.

Floating-point arithmetic is an approximation to real arithmetic. While
there are an infinite number of real numbers, a particular
floating-point format only has a finite number of values. In the Java
Virtual Machine, a <span class="emphasis">*rounding policy*</span> is a
function used to map from a real number to a floating-point value in a
given format. For real numbers in the representable range of a
floating-point format, a continuous segment of the real number line is
mapped to a single floating-point value. The real number whose value is
numerically equal to a floating-point value is mapped to that
floating-point value; for example, the real number 1.5 is mapped to the
floating-point value 1.5 in a given format. The Java Virtual Machine
defines two rounding policies, as follows:

<div class="norm">

- The <span class="emphasis">*round to nearest*</span> rounding policy
  applies to all floating-point instructions except for (i) conversion
  to an integer value and (ii) remainder. Under the round to nearest
  rounding policy, inexact results must be rounded to the representable
  value nearest to the infinitely precise result; if the two nearest
  representable values are equally near, then the value whose least
  significant bit is zero is chosen.

  The round to nearest rounding policy corresponds to the default
  rounding-direction attribute for binary arithmetic in IEEE 754,
  <span class="emphasis">*roundTiesToEven*</span>.

  The <span class="emphasis">*roundTiesToEven*</span> rounding-direction
  attribute was known as the "round to nearest" rounding mode in the
  1985 version of the IEEE 754 Standard. The rounding policy in the Java
  Virtual Machine is named after this rounding mode.

- The <span class="emphasis">*round toward zero*</span> rounding policy
  applies to (i) conversion of a floating-point value to an integer
  value by the <span class="emphasis">*d2i*</span>,
  <span class="emphasis">*d2l*</span>,
  <span class="emphasis">*f2i*</span>, and
  <span class="emphasis">*f2l*</span> instructions
  (<a href="jvms-6.html#jvms-6.5.d2i" class="xref" title="d2i">§<span
  class="emphasis"><em>d2i</em></span></a>,
  <a href="jvms-6.html#jvms-6.5.d2l" class="xref" title="d2l">§<span
  class="emphasis"><em>d2l</em></span></a>,
  <a href="jvms-6.html#jvms-6.5.f2i" class="xref" title="f2i">§<span
  class="emphasis"><em>f2i</em></span></a>,
  <a href="jvms-6.html#jvms-6.5.f2l" class="xref" title="f2l">§<span
  class="emphasis"><em>f2l</em></span></a>), and (ii) the floating-point
  remainder instructions <span class="emphasis">*drem*</span> and
  <span class="emphasis">*frem*</span>
  (<a href="jvms-6.html#jvms-6.5.drem" class="xref" title="drem">§<span
  class="emphasis"><em>drem</em></span></a>,
  <a href="jvms-6.html#jvms-6.5.frem" class="xref" title="frem">§<span
  class="emphasis"><em>frem</em></span></a>). Under the round toward
  zero rounding policy, inexact results are rounded to the nearest
  representable value that is not greater in magnitude than the
  infinitely precise result. For conversion to integer, the round toward
  zero rounding policy is equivalent to truncation where fractional
  significand bits are discarded.

  The round toward zero rounding policy corresponds to the
  <span class="emphasis">*roundTowardZero*</span> rounding-direction
  attribute for binary arithmetic in IEEE 754.

  The <span class="emphasis">*roundTowardZero*</span> rounding-direction
  attribute was known as the "round toward zero" rounding mode in the
  1985 version of the IEEE 754 Standard. The rounding policy in the Java
  Virtual Machine is named after this rounding mode.

</div>

The Java Virtual Machine requires that every floating-point instruction
rounds its floating-point result to the result precision. The rounding
policy used by each instruction is either round to nearest or round
toward zero, as specified above.

Java 1.0 and 1.1 required <span class="emphasis">*strict*</span>
evaluation of floating-point expressions. Strict evaluation means that
each `float` operand corresponds to a value representable in the IEEE
754 binary32 format, each `double` operand corresponds to a value
representable in the IEEE 754 binary64 format, and each floating-point
operator with a corresponding IEEE 754 operation matches the IEEE 754
result for the same operands.

Strict evaluation provides predictable results, but caused performance
problems in the Java Virtual Machine implementations for some processor
families common in the Java 1.0/1.1 era. Consequently, in Java 1.2
through Java SE 16, the Java SE Platform allowed a Java Virtual Machine
implementation to have one or two <span class="emphasis">*value
sets*</span> associated with each floating-point type. The `float` type
was associated with the <span class="emphasis">*float value set*</span>
and the <span class="emphasis">*float-extended-exponent value
set*</span>, while the `double` type was associated with the
<span class="emphasis">*double value set*</span> and the
<span class="emphasis">*double-extended-exponent value set*</span>. The
float value set corresponded to the values representable in the IEEE 754
binary32 format; the float-extended-exponent value set had the same
number of precision bits but larger exponent range. Similarly, the
double value set corresponded to the values representable in the IEEE
754 binary64 format; the double-extended-exponent value set had the same
number of precision bits but larger exponent range. Allowing use of the
extended-exponent value sets by default ameliorated the performance
problems on some processor families.

For compatibility, Java 1.2 allowed a `class` file to forbid an
implementation from using the extended-exponent value sets. A `class`
file expressed this by setting the `ACC_STRICT` flag on the declaration
of a method. `ACC_STRICT` constrained the floating-point semantics of
the method's instructions to use the float value set for `float`
operands and the double value set for `double` operands, ensuring the
results of such instructions were fully predictable. Methods flagged as
`ACC_STRICT` thus had the same floating-point semantics as specified in
Java 1.0 and 1.1.

In Java SE 17 and later, the Java SE Platform always requires strict
evaluation of floating-point expressions. Newer members of the processor
families that had performance problems implementing strict evaluation no
longer have that difficulty. This specification no longer associates
`float` and `double` with the four value sets described above, and the
`ACC_STRICT` flag no longer affects the evaluation of floating-point
operations. For compatibility, the bit pattern assigned to denote
`ACC_STRICT` in a `class` file whose major version number is 46-60 is
unassigned (that is, does not denote any flag) in a `class` file whose
major version number is greater than 60
(<a href="jvms-4.html#jvms-4.6" class="xref"
title="4.6. Methods">§4.6</a>). Future versions of the Java Virtual
Machine may assign a different meaning to the bit pattern in future
`class` files.

</div>

<div id="jvms-2.9" class="section">

<div class="titlepage">

<div>

<div>

## 2.9. Special Methods

</div>

</div>

</div>

<div id="jvms-2.9.1" class="section">

<div class="titlepage">

<div>

<div>

### 2.9.1. Instance Initialization Methods

</div>

</div>

</div>

A class has zero or more <span class="emphasis">*instance initialization
methods*</span>, each typically corresponding to a constructor written
in the Java programming language.

A method is an instance initialization method if all of the following
are true:

<div class="norm">

- It is defined in a class (not an interface).

- It has the special name `<init>`.

- It is `void` (<a href="jvms-4.html#jvms-4.3.3" class="xref"
  title="4.3.3. Method Descriptors">§4.3.3</a>).

</div>

In a class, any non-`void` method named `<init>` is not an instance
initialization method. In an interface, any method named `<init>` is not
an instance initialization method. Such methods cannot be invoked by any
Java Virtual Machine instruction
(<a href="jvms-4.html#jvms-4.4.2" class="xref"
title="4.4.2. The CONSTANT_Fieldref_info, CONSTANT_Methodref_info, and CONSTANT_InterfaceMethodref_info Structures">§4.4.2</a>,
<a href="jvms-4.html#jvms-4.9.2" class="xref"
title="4.9.2. Structural Constraints">§4.9.2</a>) and are rejected by
format checking (<a href="jvms-4.html#jvms-4.6" class="xref"
title="4.6. Methods">§4.6</a>,
<a href="jvms-4.html#jvms-4.8" class="xref"
title="4.8. Format Checking">§4.8</a>).

The declaration and use of an instance initialization method is
constrained by the Java Virtual Machine. For the declaration, the
method's `access_flags` item and `code` array are constrained
(<a href="jvms-4.html#jvms-4.6" class="xref"
title="4.6. Methods">§4.6</a>,
<a href="jvms-4.html#jvms-4.9.2" class="xref"
title="4.9.2. Structural Constraints">§4.9.2</a>). For a use, an
instance initialization method may be invoked only by the
<span class="emphasis">*invokespecial*</span> instruction on an
uninitialized class instance
(<a href="jvms-4.html#jvms-4.10.1.9" class="xref"
title="4.10.1.9. Type Checking Instructions">§4.10.1.9</a>).

Because the name `<init>` is not a valid identifier in the Java
programming language, it cannot be used directly in a program written in
the Java programming language.

</div>

<div id="jvms-2.9.2" class="section">

<div class="titlepage">

<div>

<div>

### 2.9.2. Class Initialization Methods

</div>

</div>

</div>

A class or interface has at most one <span class="emphasis">*class or
interface initialization method*</span> and is initialized by the Java
Virtual Machine invoking that method
(<a href="jvms-5.html#jvms-5.5" class="xref"
title="5.5. Initialization">§5.5</a>).

A method is a <span class="emphasis">*class or interface initialization
method*</span> if all of the following are true:

<div class="norm">

- It has the special name `<clinit>`.

- It is `void` (<a href="jvms-4.html#jvms-4.3.3" class="xref"
  title="4.3.3. Method Descriptors">§4.3.3</a>).

- In a `class` file whose version number is 51.0 or above, the method
  has its `ACC_STATIC` flag set and takes no arguments
  (<a href="jvms-4.html#jvms-4.6" class="xref"
  title="4.6. Methods">§4.6</a>).

  The requirement for `ACC_STATIC` was introduced in Java SE 7, and for
  taking no arguments in Java SE 9. In a class file whose version number
  is 50.0 or below, a method named `<clinit>` that is `void` is
  considered the class or interface initialization method regardless of
  the setting of its `ACC_STATIC` flag or whether it takes arguments.

</div>

Other methods named `<clinit>` in a `class` file are not class or
interface initialization methods. They are never invoked by the Java
Virtual Machine itself, cannot be invoked by any Java Virtual Machine
instruction (<a href="jvms-4.html#jvms-4.9.1" class="xref"
title="4.9.1. Static Constraints">§4.9.1</a>), and are rejected by
format checking (<a href="jvms-4.html#jvms-4.6" class="xref"
title="4.6. Methods">§4.6</a>,
<a href="jvms-4.html#jvms-4.8" class="xref"
title="4.8. Format Checking">§4.8</a>).

Because the name `<clinit>` is not a valid identifier in the Java
programming language, it cannot be used directly in a program written in
the Java programming language.

</div>

<div id="jvms-2.9.3" class="section">

<div class="titlepage">

<div>

<div>

### 2.9.3. Signature Polymorphic Methods

</div>

</div>

</div>

A method is <span class="emphasis">*signature polymorphic*</span> if all
of the following are true:

<div class="norm">

- It is declared in the `java.lang.invoke.MethodHandle` class or the
  `java.lang.invoke.VarHandle` class.

- It has a single formal parameter of type `Object``[]`.

- It has the `ACC_VARARGS` and `ACC_NATIVE` flags set.

</div>

The Java Virtual Machine gives special treatment to signature
polymorphic methods in the <span class="emphasis">*invokevirtual*</span>
instruction (<a href="jvms-6.html#jvms-6.5.invokevirtual" class="xref"
title="invokevirtual">§<span
class="emphasis"><em>invokevirtual</em></span></a>), in order to effect
invocation of a <span class="emphasis">*method handle*</span> or to
effect access to a variable referenced by an instance of
`java.lang.invoke.VarHandle`.

A method handle is a dynamically strongly typed and directly executable
reference to an underlying method, constructor, field, or similar
low-level operation (<a href="jvms-5.html#jvms-5.4.3.5" class="xref"
title="5.4.3.5. Method Type and Method Handle Resolution">§5.4.3.5</a>),
with optional transformations of arguments or return values. An instance
of `java.lang.invoke.VarHandle` is a dynamically strongly typed
reference to a variable or family of variables, including `static`
fields, non-`static` fields, array elements, or components of an
off-heap data structure. See the `java.lang.invoke` package in the Java
SE Platform API for more information.

</div>

</div>

<div id="jvms-2.10" class="section">

<div class="titlepage">

<div>

<div>

## 2.10. Exceptions

</div>

</div>

</div>

An exception in the Java Virtual Machine is represented by an instance
of the class `Throwable` or one of its subclasses. Throwing an exception
results in an immediate nonlocal transfer of control from the point
where the exception was thrown.

Most exceptions occur synchronously as a result of an action by the
thread in which they occur. An asynchronous exception, by contrast, can
potentially occur at any point in the execution of a program. The Java
Virtual Machine throws an exception for one of three reasons:

<div class="norm">

- An <span class="emphasis">*athrow*</span> instruction
  (<a href="jvms-6.html#jvms-6.5.athrow" class="xref" title="athrow">§<span
  class="emphasis"><em>athrow</em></span></a>) was executed.

- An abnormal execution condition was synchronously detected by the Java
  Virtual Machine. These exceptions are not thrown at an arbitrary point
  in the program, but only synchronously after execution of an
  instruction that either:

  <div class="norm">

  - Specifies the exception as a possible result, such as:

    <div class="norm">

    - When the instruction embodies an operation that violates the
      semantics of the Java programming language, for example indexing
      outside the bounds of an array.

    - When an error occurs in loading or linking part of the program.

    </div>

  - Causes some limit on a resource to be exceeded, for example when too
    much memory is used.

  </div>

- An asynchronous exception occurred because an internal error occurred
  in the Java Virtual Machine implementation
  (<a href="jvms-6.html#jvms-6.3" class="xref"
  title="6.3. Virtual Machine Errors">§6.3</a>).

</div>

A Java Virtual Machine implementation may permit a small but bounded
amount of execution to occur before an asynchronous exception is thrown.
This delay is permitted to allow optimized code to detect and throw
these exceptions at points where it is practical to handle them while
obeying the semantics of the Java programming language.

A simple implementation might poll for asynchronous exceptions at the
point of each control transfer instruction. Since a program has a finite
size, this provides a bound on the total delay in detecting an
asynchronous exception. Since no asynchronous exception will occur
between control transfers, the code generator has some flexibility to
reorder computation between control transfers for greater performance.
The paper *Polling Efficiently on Stock Hardware* by Marc Feeley, *Proc.
1993 Conference on Functional Programming and Computer Architecture*,
Copenhagen, Denmark, pp. 179–187, is recommended as further reading.

Exceptions thrown by the Java Virtual Machine are precise: when the
transfer of control takes place, all effects of the instructions
executed before the point from which the exception is thrown must appear
to have taken place. No instructions that occur after the point from
which the exception is thrown may appear to have been evaluated. If
optimized code has speculatively executed some of the instructions which
follow the point at which the exception occurs, such code must be
prepared to hide this speculative execution from the user-visible state
of the program.

Each method in the Java Virtual Machine may be associated with zero or
more <span class="emphasis">*exception handlers*</span>. An exception
handler specifies the range of offsets into the Java Virtual Machine
code implementing the method for which the exception handler is active,
describes the type of exception that the exception handler is able to
handle, and specifies the location of the code that is to handle that
exception. An exception matches an exception handler if the offset of
the instruction that caused the exception is in the range of offsets of
the exception handler and the exception type is the same class as or a
subclass of the class of exception that the exception handler handles.
When an exception is thrown, the Java Virtual Machine searches for a
matching exception handler in the current method. If a matching
exception handler is found, the system branches to the exception
handling code specified by the matched handler.

If no such exception handler is found in the current method, the current
method invocation completes abruptly
(<a href="jvms-2.html#jvms-2.6.5" class="xref"
title="2.6.5. Abrupt Method Invocation Completion">§2.6.5</a>). On
abrupt completion, the operand stack and local variables of the current
method invocation are discarded, and its frame is popped, reinstating
the frame of the invoking method. The exception is then rethrown in the
context of the invoker's frame and so on, continuing up the method
invocation chain. If no suitable exception handler is found before the
top of the method invocation chain is reached, the execution of the
thread in which the exception was thrown is terminated. Before
termination of the thread, the uncaught exception is handled according
to the following rules:

<div class="norm">

- If the thread has an uncaught exception handler set, then that handler
  is executed.

- Otherwise, the method `uncaughtException` is invoked for the
  `ThreadGroup` that is the parent of the thread. If the `ThreadGroup`
  and its parent `ThreadGroup`s do not override `uncaughtException`,
  then the default handler's `uncaughtException` method is invoked.

</div>

The order in which the exception handlers of a method are searched for a
match is important. Within a `class` file, the exception handlers for
each method are stored in a table
(<a href="jvms-4.html#jvms-4.7.3" class="xref"
title="4.7.3. The Code Attribute">§4.7.3</a>). At run time, when an
exception is thrown, the Java Virtual Machine searches the exception
handlers of the current method in the order that they appear in the
corresponding exception handler table in the `class` file, starting from
the beginning of that table.

Note that the Java Virtual Machine does not enforce nesting of or any
ordering of the exception table entries of a method. The exception
handling semantics of the Java programming language are implemented only
through cooperation with the compiler
(<a href="jvms-3.html#jvms-3.12" class="xref"
title="3.12. Throwing and Handling Exceptions">§3.12</a>). When `class`
files are generated by some other means, the defined search procedure
ensures that all Java Virtual Machine implementations will behave
consistently.

</div>

<div id="jvms-2.11" class="section">

<div class="titlepage">

<div>

<div>

## 2.11. Instruction Set Summary

</div>

</div>

</div>

A Java Virtual Machine instruction consists of a one-byte
<span class="emphasis">*opcode*</span> specifying the operation to be
performed, followed by zero or more
<span class="emphasis">*operands*</span> supplying arguments or data
that are used by the operation. Many instructions have no operands and
consist only of an opcode.

Ignoring exceptions, the inner loop of a Java Virtual Machine
interpreter is effectively

``` screen
do {
    atomically calculate pc and fetch opcode at pc;
    if (operands) fetch operands;
    execute the action for the opcode;
} while (there is more to do);
```

The number and size of the operands are determined by the opcode. If an
operand is more than one byte in size, then it is stored in
<span class="emphasis">*big-endian*</span> order - high-order byte
first. For example, an unsigned 16-bit index into the local variables is
stored as two unsigned bytes, <span class="emphasis">*byte1*</span> and
<span class="emphasis">*byte2*</span>, such that its value is
(<span class="emphasis">*byte1*</span> `<<` 8) \|
<span class="emphasis">*byte2*</span>.

The bytecode instruction stream is only single-byte aligned. The two
exceptions are the <span class="emphasis">*lookupswitch*</span> and
<span class="emphasis">*tableswitch*</span> instructions
(<a href="jvms-6.html#jvms-6.5.lookupswitch" class="xref"
title="lookupswitch">§<span
class="emphasis"><em>lookupswitch</em></span></a>,
<a href="jvms-6.html#jvms-6.5.tableswitch" class="xref"
title="tableswitch">§<span
class="emphasis"><em>tableswitch</em></span></a>), which are padded to
force internal alignment of some of their operands on 4-byte boundaries.

The decision to limit the Java Virtual Machine opcode to a byte and to
forgo data alignment within compiled code reflects a conscious bias in
favor of compactness, possibly at the cost of some performance in naive
implementations. A one-byte opcode also limits the size of the
instruction set. Not assuming data alignment means that immediate data
larger than a byte must be constructed from bytes at run time on many
machines.

<div id="jvms-2.11.1" class="section">

<div class="titlepage">

<div>

<div>

### 2.11.1. Types and the Java Virtual Machine

</div>

</div>

</div>

Most of the instructions in the Java Virtual Machine instruction set
encode type information about the operations they perform. For instance,
the <span class="emphasis">*iload*</span> instruction
(<a href="jvms-6.html#jvms-6.5.iload" class="xref" title="iload">§<span
class="emphasis"><em>iload</em></span></a>) loads the contents of a
local variable, which must be an `int`, onto the operand stack. The
<span class="emphasis">*fload*</span> instruction
(<a href="jvms-6.html#jvms-6.5.fload" class="xref" title="fload">§<span
class="emphasis"><em>fload</em></span></a>) does the same with a `float`
value. The two instructions may have identical implementations, but have
distinct opcodes.

For the majority of typed instructions, the instruction type is
represented explicitly in the opcode mnemonic by a letter:
<span class="emphasis">*i*</span> for an `int` operation,
<span class="emphasis">*l*</span> for `long`,
<span class="emphasis">*s*</span> for `short`,
<span class="emphasis">*b*</span> for `byte`,
<span class="emphasis">*c*</span> for `char`,
<span class="emphasis">*f*</span> for `float`,
<span class="emphasis">*d*</span> for `double`, and
<span class="emphasis">*a*</span> for `reference`. Some instructions for
which the type is unambiguous do not have a type letter in their
mnemonic. For instance, <span class="emphasis">*arraylength*</span>
always operates on an object that is an array. Some instructions, such
as <span class="emphasis">*goto*</span>, an unconditional control
transfer, do not operate on typed operands.

Given the Java Virtual Machine's one-byte opcode size, encoding types
into opcodes places pressure on the design of its instruction set. If
each typed instruction supported all of the Java Virtual Machine's
run-time data types, there would be more instructions than could be
represented in a byte. Instead, the instruction set of the Java Virtual
Machine provides a reduced level of type support for certain operations.
In other words, the instruction set is intentionally not orthogonal.
Separate instructions can be used to convert between unsupported and
supported data types as necessary.

<a href="jvms-2.html#jvms-2.11.1-220" class="xref"
title="Table 2.11.1-A. Type support in the Java Virtual Machine instruction set">Table 2.11.1-A</a>
summarizes the type support in the instruction set of the Java Virtual
Machine. A specific instruction, with type information, is built by
replacing the <span class="emphasis">*T*</span> in the instruction
template in the opcode column by the letter in the type column. If the
type column for some instruction template and type is blank, then no
instruction exists supporting that type of operation. For instance,
there is a load instruction for type `int`,
<span class="emphasis">*iload*</span>, but there is no load instruction
for type `byte`.

Note that most instructions in
<a href="jvms-2.html#jvms-2.11.1-220" class="xref"
title="Table 2.11.1-A. Type support in the Java Virtual Machine instruction set">Table 2.11.1-A</a>
do not have forms for the integral types `byte`, `char`, and `short`.
None have forms for the `boolean` type. Whenever values of types `byte`
and `short` are loaded onto the operand stack, they are implicitly
converted by sign extension to values of type `int`. Similarly, whenever
values of types `boolean` and `char` are loaded onto the operand stack,
they are implicitly converted by zero extension to values of type `int`.
Thus, most operations on values originally stored in variables of types
`boolean`, `byte`, `char`, and `short` are correctly performed by
instructions operating on values of computational type `int`.

<div id="jvms-2.11.1-220" class="table">

**Table 2.11.1-A. Type support in the Java Virtual Machine instruction
set**

<div class="table-contents">

| opcode | `byte` | `short` | `int` | `long` | `float` | `double` | `char` | `reference` |
|----|----|----|----|----|----|----|----|----|
| <span class="emphasis">*Tipush*</span> | <span class="emphasis">*bipush*</span> | <span class="emphasis">*sipush*</span> |   |   |   |   |   |   |
| <span class="emphasis">*Tconst*</span> |   |   | <span class="emphasis">*iconst*</span> | <span class="emphasis">*lconst*</span> | <span class="emphasis">*fconst*</span> | <span class="emphasis">*dconst*</span> |   | <span class="emphasis">*aconst*</span> |
| <span class="emphasis">*Tload*</span> |   |   | <span class="emphasis">*iload*</span> | <span class="emphasis">*lload*</span> | <span class="emphasis">*fload*</span> | <span class="emphasis">*dload*</span> |   | <span class="emphasis">*aload*</span> |
| <span class="emphasis">*Tstore*</span> |   |   | <span class="emphasis">*istore*</span> | <span class="emphasis">*lstore*</span> | <span class="emphasis">*fstore*</span> | <span class="emphasis">*dstore*</span> |   | <span class="emphasis">*astore*</span> |
| <span class="emphasis">*Tinc*</span> |   |   | <span class="emphasis">*iinc*</span> |   |   |   |   |   |
| <span class="emphasis">*Taload*</span> | <span class="emphasis">*baload*</span> | <span class="emphasis">*saload*</span> | <span class="emphasis">*iaload*</span> | <span class="emphasis">*laload*</span> | <span class="emphasis">*faload*</span> | <span class="emphasis">*daload*</span> | <span class="emphasis">*caload*</span> | <span class="emphasis">*aaload*</span> |
| <span class="emphasis">*Tastore*</span> | <span class="emphasis">*bastore*</span> | <span class="emphasis">*sastore*</span> | <span class="emphasis">*iastore*</span> | <span class="emphasis">*lastore*</span> | <span class="emphasis">*fastore*</span> | <span class="emphasis">*dastore*</span> | <span class="emphasis">*castore*</span> | <span class="emphasis">*aastore*</span> |
| <span class="emphasis">*Tadd*</span> |   |   | <span class="emphasis">*iadd*</span> | <span class="emphasis">*ladd*</span> | <span class="emphasis">*fadd*</span> | <span class="emphasis">*dadd*</span> |   |   |
| <span class="emphasis">*Tsub*</span> |   |   | <span class="emphasis">*isub*</span> | <span class="emphasis">*lsub*</span> | <span class="emphasis">*fsub*</span> | <span class="emphasis">*dsub*</span> |   |   |
| <span class="emphasis">*Tmul*</span> |   |   | <span class="emphasis">*imul*</span> | <span class="emphasis">*lmul*</span> | <span class="emphasis">*fmul*</span> | <span class="emphasis">*dmul*</span> |   |   |
| <span class="emphasis">*Tdiv*</span> |   |   | <span class="emphasis">*idiv*</span> | <span class="emphasis">*ldiv*</span> | <span class="emphasis">*fdiv*</span> | <span class="emphasis">*ddiv*</span> |   |   |
| <span class="emphasis">*Trem*</span> |   |   | <span class="emphasis">*irem*</span> | <span class="emphasis">*lrem*</span> | <span class="emphasis">*frem*</span> | <span class="emphasis">*drem*</span> |   |   |
| <span class="emphasis">*Tneg*</span> |   |   | <span class="emphasis">*ineg*</span> | <span class="emphasis">*lneg*</span> | <span class="emphasis">*fneg*</span> | <span class="emphasis">*dneg*</span> |   |   |
| <span class="emphasis">*Tshl*</span> |   |   | <span class="emphasis">*ishl*</span> | <span class="emphasis">*lshl*</span> |   |   |   |   |
| <span class="emphasis">*Tshr*</span> |   |   | <span class="emphasis">*ishr*</span> | <span class="emphasis">*lshr*</span> |   |   |   |   |
| <span class="emphasis">*Tushr*</span> |   |   | <span class="emphasis">*iushr*</span> | <span class="emphasis">*lushr*</span> |   |   |   |   |
| <span class="emphasis">*Tand*</span> |   |   | <span class="emphasis">*iand*</span> | <span class="emphasis">*land*</span> |   |   |   |   |
| <span class="emphasis">*Tor*</span> |   |   | <span class="emphasis">*ior*</span> | <span class="emphasis">*lor*</span> |   |   |   |   |
| <span class="emphasis">*Txor*</span> |   |   | <span class="emphasis">*ixor*</span> | <span class="emphasis">*lxor*</span> |   |   |   |   |
| <span class="emphasis">*i2T*</span> | <span class="emphasis">*i2b*</span> | <span class="emphasis">*i2s*</span> |   | <span class="emphasis">*i2l*</span> | <span class="emphasis">*i2f*</span> | <span class="emphasis">*i2d*</span> | <span class="emphasis">*i2c*</span> |   |
| <span class="emphasis">*l2T*</span> |   |   | <span class="emphasis">*l2i*</span> |   | <span class="emphasis">*l2f*</span> | <span class="emphasis">*l2d*</span> |   |   |
| <span class="emphasis">*f2T*</span> |   |   | <span class="emphasis">*f2i*</span> | <span class="emphasis">*f2l*</span> |   | <span class="emphasis">*f2d*</span> |   |   |
| <span class="emphasis">*d2T*</span> |   |   | <span class="emphasis">*d2i*</span> | <span class="emphasis">*d2l*</span> | <span class="emphasis">*d2f*</span> |   |   |   |
| <span class="emphasis">*Tcmp*</span> |   |   |   | <span class="emphasis">*lcmp*</span> |   |   |   |   |
| <span class="emphasis">*Tcmpl*</span> |   |   |   |   | <span class="emphasis">*fcmpl*</span> | <span class="emphasis">*dcmpl*</span> |   |   |
| <span class="emphasis">*Tcmpg*</span> |   |   |   |   | <span class="emphasis">*fcmpg*</span> | <span class="emphasis">*dcmpg*</span> |   |   |
| <span class="emphasis">*if_TcmpOP*</span> |   |   | <span class="emphasis">*if_icmpOP*</span> |   |   |   |   | <span class="emphasis">*if_acmpOP*</span> |
| <span class="emphasis">*Treturn*</span> |   |   | <span class="emphasis">*ireturn*</span> | <span class="emphasis">*lreturn*</span> | <span class="emphasis">*freturn*</span> | <span class="emphasis">*dreturn*</span> |   | <span class="emphasis">*areturn*</span> |

</div>

</div>

  

The mapping between Java Virtual Machine storage types and Java Virtual
Machine computational types is summarized by
<a href="jvms-2.html#jvms-2.11.1-320" class="xref"
title="Table 2.11.1-B. Storage and Computational types in the Java Virtual Machine">Table 2.11.1-B</a>.

Certain Java Virtual Machine instructions such as
<span class="emphasis">*pop*</span> and
<span class="emphasis">*swap*</span> operate on the operand stack
without regard to type; however, such instructions are constrained to
use only on values of certain categories of computational types, also
given in <a href="jvms-2.html#jvms-2.11.1-320" class="xref"
title="Table 2.11.1-B. Storage and Computational types in the Java Virtual Machine">Table 2.11.1-B</a>.

<div id="jvms-2.11.1-320" class="table">

**Table 2.11.1-B. Storage and Computational types in the Java Virtual
Machine**

<div class="table-contents">

| Storage type    | Computational type | Category |
|-----------------|--------------------|----------|
| `boolean`       | `int`              | 1        |
| `byte`          | `int`              | 1        |
| `char`          | `int`              | 1        |
| `short`         | `int`              | 1        |
| `int`           | `int`              | 1        |
| `float`         | `float`            | 1        |
| `reference`     | `reference`        | 1        |
| `returnAddress` | `returnAddress`    | 1        |
| `long`          | `long`             | 2        |
| `double`        | `double`           | 2        |

</div>

</div>

  

</div>

<div id="jvms-2.11.2" class="section">

<div class="titlepage">

<div>

<div>

### 2.11.2. Load and Store Instructions

</div>

</div>

</div>

The load and store instructions transfer values between the local
variables (<a href="jvms-2.html#jvms-2.6.1" class="xref"
title="2.6.1. Local Variables">§2.6.1</a>) and the operand stack
(<a href="jvms-2.html#jvms-2.6.2" class="xref"
title="2.6.2. Operand Stacks">§2.6.2</a>) of a Java Virtual Machine
frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>):

<div class="norm">

- Load a local variable onto the operand stack:
  <span class="emphasis">*iload*</span>,
  <span class="emphasis">*iload\_\<n\>*</span>,
  <span class="emphasis">*lload*</span>,
  <span class="emphasis">*lload\_\<n\>*</span>,
  <span class="emphasis">*fload*</span>,
  <span class="emphasis">*fload\_\<n\>*</span>,
  <span class="emphasis">*dload*</span>,
  <span class="emphasis">*dload\_\<n\>*</span>,
  <span class="emphasis">*aload*</span>,
  <span class="emphasis">*aload\_\<n\>*</span>.

- Store a value from the operand stack into a local variable:
  <span class="emphasis">*istore*</span>,
  <span class="emphasis">*istore\_\<n\>*</span>,
  <span class="emphasis">*lstore*</span>,
  <span class="emphasis">*lstore\_\<n\>*</span>,
  <span class="emphasis">*fstore*</span>,
  <span class="emphasis">*fstore\_\<n\>*</span>,
  <span class="emphasis">*dstore*</span>,
  <span class="emphasis">*dstore\_\<n\>*</span>,
  <span class="emphasis">*astore*</span>,
  <span class="emphasis">*astore\_\<n\>*</span>.

- Load a constant on to the operand stack:
  <span class="emphasis">*bipush*</span>,
  <span class="emphasis">*sipush*</span>,
  <span class="emphasis">*ldc*</span>,
  <span class="emphasis">*ldc_w*</span>,
  <span class="emphasis">*ldc2_w*</span>,
  <span class="emphasis">*aconst_null*</span>,
  <span class="emphasis">*iconst_m1*</span>,
  <span class="emphasis">*iconst\_\<i\>*</span>,
  <span class="emphasis">*lconst\_\<l\>*</span>,
  <span class="emphasis">*fconst\_\<f\>*</span>,
  <span class="emphasis">*dconst\_\<d\>*</span>.

- Gain access to more local variables using a wider index, or to a
  larger immediate operand: <span class="emphasis">*wide*</span>.

</div>

Instructions that access fields of objects and elements of arrays
(<a href="jvms-2.html#jvms-2.11.5" class="xref"
title="2.11.5. Object Creation and Manipulation">§2.11.5</a>) also
transfer data to and from the operand stack.

Instruction mnemonics shown above with trailing letters between angle
brackets (for instance, <span class="emphasis">*iload\_\<n\>*</span>)
denote families of instructions (with members
<span class="emphasis">*iload_0*</span>,
<span class="emphasis">*iload_1*</span>,
<span class="emphasis">*iload_2*</span>, and
<span class="emphasis">*iload_3*</span> in the case of
<span class="emphasis">*iload\_\<n\>*</span>). Such families of
instructions are specializations of an additional generic instruction
(<span class="emphasis">*iload*</span>) that takes one operand. For the
specialized instructions, the operand is implicit and does not need to
be stored or fetched. The semantics are otherwise the same
(<span class="emphasis">*iload_0*</span> means the same thing as
<span class="emphasis">*iload*</span> with the operand
<span class="emphasis">*0*</span>). The letter between the angle
brackets specifies the type of the implicit operand for that family of
instructions: for <span class="emphasis">*\<n\>*</span>, a nonnegative
integer; for <span class="emphasis">*\<i\>*</span>, an `int`; for
<span class="emphasis">*\<l\>*</span>, a `long`; for
<span class="emphasis">*\<f\>*</span>, a `float`; and for
<span class="emphasis">*\<d\>*</span>, a `double`.

This notation for instruction families is used throughout this
specification.

</div>

<div id="jvms-2.11.3" class="section">

<div class="titlepage">

<div>

<div>

### 2.11.3. Arithmetic Instructions

</div>

</div>

</div>

The arithmetic instructions compute a result that is typically a
function of two values on the operand stack, pushing the result back on
the operand stack. There are two main kinds of arithmetic instructions:
those operating on integer values and those operating on floating-point
values. Within each of these kinds, the arithmetic instructions are
specialized to Java Virtual Machine numeric types. There is no direct
support for integer arithmetic on values of the `byte`, `short`, and
`char` types (<a href="jvms-2.html#jvms-2.11.1" class="xref"
title="2.11.1. Types and the Java Virtual Machine">§2.11.1</a>), or for
values of the `boolean` type; those operations are handled by
instructions operating on type `int`. Integer and floating-point
instructions also differ in their behavior on overflow and
divide-by-zero. The arithmetic instructions are as follows:

<div class="norm">

- Add: <span class="emphasis">*iadd*</span>,
  <span class="emphasis">*ladd*</span>,
  <span class="emphasis">*fadd*</span>,
  <span class="emphasis">*dadd*</span>.

- Subtract: <span class="emphasis">*isub*</span>,
  <span class="emphasis">*lsub*</span>,
  <span class="emphasis">*fsub*</span>,
  <span class="emphasis">*dsub*</span>.

- Multiply: <span class="emphasis">*imul*</span>,
  <span class="emphasis">*lmul*</span>,
  <span class="emphasis">*fmul*</span>,
  <span class="emphasis">*dmul*</span>.

- Divide: <span class="emphasis">*idiv*</span>,
  <span class="emphasis">*ldiv*</span>,
  <span class="emphasis">*fdiv*</span>,
  <span class="emphasis">*ddiv*</span>.

- Remainder: <span class="emphasis">*irem*</span>,
  <span class="emphasis">*lrem*</span>,
  <span class="emphasis">*frem*</span>,
  <span class="emphasis">*drem*</span>.

- Negate: <span class="emphasis">*ineg*</span>,
  <span class="emphasis">*lneg*</span>,
  <span class="emphasis">*fneg*</span>,
  <span class="emphasis">*dneg*</span>.

- Shift: <span class="emphasis">*ishl*</span>,
  <span class="emphasis">*ishr*</span>,
  <span class="emphasis">*iushr*</span>,
  <span class="emphasis">*lshl*</span>,
  <span class="emphasis">*lshr*</span>,
  <span class="emphasis">*lushr*</span>.

- Bitwise OR: <span class="emphasis">*ior*</span>,
  <span class="emphasis">*lor*</span>.

- Bitwise AND: <span class="emphasis">*iand*</span>,
  <span class="emphasis">*land*</span>.

- Bitwise exclusive OR: <span class="emphasis">*ixor*</span>,
  <span class="emphasis">*lxor*</span>.

- Local variable increment: <span class="emphasis">*iinc*</span>.

- Comparison: <span class="emphasis">*dcmpg*</span>,
  <span class="emphasis">*dcmpl*</span>,
  <span class="emphasis">*fcmpg*</span>,
  <span class="emphasis">*fcmpl*</span>,
  <span class="emphasis">*lcmp*</span>.

</div>

The semantics of the Java programming language operators on integer and
floating-point values (JLS §4.2.2, JLS §4.2.4) are directly supported by
the semantics of the Java Virtual Machine instruction set.

The Java Virtual Machine does not indicate overflow during operations on
integer data types. The only integer operations that can throw an
exception are the integer divide instructions
(<span class="emphasis">*idiv*</span> and
<span class="emphasis">*ldiv*</span>) and the integer remainder
instructions (<span class="emphasis">*irem*</span> and
<span class="emphasis">*lrem*</span>), which throw an
`ArithmeticException` if the divisor is zero.

The Java Virtual Machine does not indicate overflow or underflow during
operations on floating-point data types. That is, floating-point
instructions never cause the Java Virtual Machine to throw a run-time
exception (not to be confused with an IEEE 754 floating-point
exception). An operation that overflows produces a signed infinity; an
operation that underflows produces a subnormal value or a signed zero;
an operation that has no unique mathematically defined result produces
NaN. All numeric operations with NaN as an operand produce NaN as a
result.

Comparisons on values of type `long`
(<span class="emphasis">*lcmp*</span>) perform a signed comparison.

Comparisons on values of floating-point types
(<span class="emphasis">*dcmpg*</span>,
<span class="emphasis">*dcmpl*</span>,
<span class="emphasis">*fcmpg*</span>,
<span class="emphasis">*fcmpl*</span>) are performed using IEEE 754
nonsignaling comparisons.

</div>

<div id="jvms-2.11.4" class="section">

<div class="titlepage">

<div>

<div>

### 2.11.4. Type Conversion Instructions

</div>

</div>

</div>

The type conversion instructions allow conversion between Java Virtual
Machine numeric types. These may be used to implement explicit
conversions in user code or to mitigate the lack of orthogonality in the
instruction set of the Java Virtual Machine.

The Java Virtual Machine directly supports the following widening
numeric conversions:

<div class="norm">

- `int` to `long`, `float`, or `double`

- `long` to `float` or `double`

- `float` to `double`

</div>

The widening numeric conversion instructions are
<span class="emphasis">*i2l*</span>,
<span class="emphasis">*i2f*</span>,
<span class="emphasis">*i2d*</span>,
<span class="emphasis">*l2f*</span>,
<span class="emphasis">*l2d*</span>, and
<span class="emphasis">*f2d*</span>. The mnemonics for these opcodes are
straightforward given the naming conventions for typed instructions and
the punning use of 2 to mean "to." For instance, the
<span class="emphasis">*i2d*</span> instruction converts an `int` value
to a `double`.

Most widening numeric conversions do not lose information about the
overall magnitude of a numeric value. Indeed, conversions widening from
`int` to `long` and `int` to `double` do not lose any information at
all; the numeric value is preserved exactly. Conversions widening from
`float` to `double` also preserve the numeric value exactly.

Conversions from `int` to `float`, or from `long` to `float`, or from
`long` to `double`, may lose <span class="emphasis">*precision*</span>,
that is, may lose some of the least significant bits of the value; the
resulting floating-point value is a correctly rounded version of the
integer value, using the round to nearest rounding policy
(<a href="jvms-2.html#jvms-2.8" class="xref"
title="2.8. Floating-Point Arithmetic">§2.8</a>).

Despite the fact that loss of precision may occur, widening numeric
conversions never cause the Java Virtual Machine to throw a run-time
exception (not to be confused with an IEEE 754 floating-point
exception).

A widening numeric conversion of an `int` to a `long` simply
sign-extends the two's-complement representation of the `int` value to
fill the wider format. A widening numeric conversion of a `char` to an
integral type zero-extends the representation of the `char` value to
fill the wider format.

Note that widening numeric conversions do not exist from integral types
`byte`, `char`, and `short` to type `int`. As noted in
<a href="jvms-2.html#jvms-2.11.1" class="xref"
title="2.11.1. Types and the Java Virtual Machine">§2.11.1</a>, values
of type `byte`, `char`, and `short` are internally widened to type
`int`, making these conversions implicit.

The Java Virtual Machine also directly supports the following narrowing
numeric conversions:

<div class="norm">

- `int` to `byte`, `short`, or `char`

- `long` to `int`

- `float` to `int` or `long`

- `double` to `int`, `long`, or `float`

</div>

The narrowing numeric conversion instructions are
<span class="emphasis">*i2b*</span>,
<span class="emphasis">*i2c*</span>,
<span class="emphasis">*i2s*</span>,
<span class="emphasis">*l2i*</span>,
<span class="emphasis">*f2i*</span>,
<span class="emphasis">*f2l*</span>,
<span class="emphasis">*d2i*</span>,
<span class="emphasis">*d2l*</span>, and
<span class="emphasis">*d2f*</span>. A narrowing numeric conversion can
result in a value of different sign, a different order of magnitude, or
both; it may thereby lose precision.

A narrowing numeric conversion of an `int` or `long` to an integral type
<span class="type">T</span> simply discards all but the
<span class="emphasis">*n*</span> lowest-order bits, where
<span class="emphasis">*n*</span> is the number of bits used to
represent type <span class="type">T</span>. This may cause the resulting
value not to have the same sign as the input value.

In a narrowing numeric conversion of a floating-point value to an
integral type <span class="type">T</span>, where
<span class="type">T</span> is either `int` or `long`, the
floating-point value is converted as follows:

<div class="norm">

- If the floating-point value is NaN, the result of the conversion is an
  `int` or `long` `0`.

- Otherwise, if the floating-point value is not an infinity, the
  floating-point value is rounded to an integer value
  <span class="type">V</span> using the round toward zero rounding
  policy (<a href="jvms-2.html#jvms-2.8" class="xref"
  title="2.8. Floating-Point Arithmetic">§2.8</a>). There are two cases:

  <div class="norm">

  - If <span class="type">T</span> is `long` and this integer value can
    be represented as a `long`, then the result is the `long` value
    <span class="type">V</span>.

  - If <span class="type">T</span> is of type `int` and this integer
    value can be represented as an `int`, then the result is the `int`
    value <span class="type">V</span>.

  </div>

- Otherwise:

  <div>

  - Either the value must be too small (a negative value of large
    magnitude or negative infinity), and the result is the smallest
    representable value of type `int` or `long`.

  - Or the value must be too large (a positive value of large magnitude
    or positive infinity), and the result is the largest representable
    value of type `int` or `long`.

  </div>

</div>

A narrowing numeric conversion from `double` to `float` behaves in
accordance with IEEE 754. The result is correctly rounded using the
round to nearest rounding policy
(<a href="jvms-2.html#jvms-2.8" class="xref"
title="2.8. Floating-Point Arithmetic">§2.8</a>). A value too small to
be represented as a `float` is converted to a positive or negative zero
of type `float`; a value too large to be represented as a `float` is
converted to a positive or negative infinity. A `double` NaN is always
converted to a `float` NaN.

Despite the fact that overflow, underflow, or loss of precision may
occur, narrowing conversions among numeric types never cause the Java
Virtual Machine to throw a run-time exception (not to be confused with
an IEEE 754 floating-point exception).

</div>

<div id="jvms-2.11.5" class="section">

<div class="titlepage">

<div>

<div>

### 2.11.5. Object Creation and Manipulation

</div>

</div>

</div>

Although both class instances and arrays are objects, the Java Virtual
Machine creates and manipulates class instances and arrays using
distinct sets of instructions:

<div class="norm">

- Create a new class instance: <span class="emphasis">*new*</span>.

- Create a new array: <span class="emphasis">*newarray*</span>,
  <span class="emphasis">*anewarray*</span>,
  <span class="emphasis">*multianewarray*</span>.

- Access fields of classes (`static` fields, known as class variables)
  and fields of class instances (non-`static` fields, known as instance
  variables): <span class="emphasis">*getstatic*</span>,
  <span class="emphasis">*putstatic*</span>,
  <span class="emphasis">*getfield*</span>,
  <span class="emphasis">*putfield*</span>.

- Load an array component onto the operand stack:
  <span class="emphasis">*baload*</span>,
  <span class="emphasis">*caload*</span>,
  <span class="emphasis">*saload*</span>,
  <span class="emphasis">*iaload*</span>,
  <span class="emphasis">*laload*</span>,
  <span class="emphasis">*faload*</span>,
  <span class="emphasis">*daload*</span>,
  <span class="emphasis">*aaload*</span>.

- Store a value from the operand stack as an array component:
  <span class="emphasis">*bastore*</span>,
  <span class="emphasis">*castore*</span>,
  <span class="emphasis">*sastore*</span>,
  <span class="emphasis">*iastore*</span>,
  <span class="emphasis">*lastore*</span>,
  <span class="emphasis">*fastore*</span>,
  <span class="emphasis">*dastore*</span>,
  <span class="emphasis">*aastore*</span>.

- Get the length of array: <span class="emphasis">*arraylength*</span>.

- Check properties of class instances or arrays:
  <span class="emphasis">*instanceof*</span>,
  <span class="emphasis">*checkcast*</span>.

</div>

</div>

<div id="jvms-2.11.6" class="section">

<div class="titlepage">

<div>

<div>

### 2.11.6. Operand Stack Management Instructions

</div>

</div>

</div>

A number of instructions are provided for the direct manipulation of the
operand stack: <span class="emphasis">*pop*</span>,
<span class="emphasis">*pop2*</span>,
<span class="emphasis">*dup*</span>,
<span class="emphasis">*dup2*</span>,
<span class="emphasis">*dup_x1*</span>,
<span class="emphasis">*dup2_x1*</span>,
<span class="emphasis">*dup_x2*</span>,
<span class="emphasis">*dup2_x2*</span>,
<span class="emphasis">*swap*</span>.

</div>

<div id="jvms-2.11.7" class="section">

<div class="titlepage">

<div>

<div>

### 2.11.7. Control Transfer Instructions

</div>

</div>

</div>

The control transfer instructions conditionally or unconditionally cause
the Java Virtual Machine to continue execution with an instruction other
than the one following the control transfer instruction. They are:

<div class="norm">

- Conditional branch: <span class="emphasis">*ifeq*</span>,
  <span class="emphasis">*ifne*</span>,
  <span class="emphasis">*iflt*</span>,
  <span class="emphasis">*ifle*</span>,
  <span class="emphasis">*ifgt*</span>,
  <span class="emphasis">*ifge*</span>,
  <span class="emphasis">*ifnull*</span>,
  <span class="emphasis">*ifnonnull*</span>,
  <span class="emphasis">*if_icmpeq*</span>,
  <span class="emphasis">*if_icmpne*</span>,
  <span class="emphasis">*if_icmplt*</span>,
  <span class="emphasis">*if_icmple*</span>,
  <span class="emphasis">*if_icmpgt*</span>
  <span class="emphasis">*if_icmpge*</span>,
  <span class="emphasis">*if_acmpeq*</span>,
  <span class="emphasis">*if_acmpne*</span>.

- Compound conditional branch:
  <span class="emphasis">*tableswitch*</span>,
  <span class="emphasis">*lookupswitch*</span>.

- Unconditional branch: <span class="emphasis">*goto*</span>,
  <span class="emphasis">*goto_w*</span>,
  <span class="emphasis">*jsr*</span>,
  <span class="emphasis">*jsr_w*</span>,
  <span class="emphasis">*ret*</span>.

</div>

The Java Virtual Machine has distinct sets of instructions that
conditionally branch on comparison with data of `int` and `reference`
types. It also has distinct conditional branch instructions that test
for the null reference and thus it is not required to specify a concrete
value for `null` (<a href="jvms-2.html#jvms-2.4" class="xref"
title="2.4. Reference Types and Values">§2.4</a>).

Conditional branches on comparisons between data of types `boolean`,
`byte`, `char`, and `short` are performed using `int` comparison
instructions (<a href="jvms-2.html#jvms-2.11.1" class="xref"
title="2.11.1. Types and the Java Virtual Machine">§2.11.1</a>). A
conditional branch on a comparison between data of types `long`,
`float`, or `double` is initiated using an instruction that compares the
data and produces an `int` result of the comparison
(<a href="jvms-2.html#jvms-2.11.3" class="xref"
title="2.11.3. Arithmetic Instructions">§2.11.3</a>). A subsequent `int`
comparison instruction tests this result and effects the conditional
branch. Because of its emphasis on `int` comparisons, the Java Virtual
Machine provides a rich complement of conditional branch instructions
for type `int`.

All `int` conditional control transfer instructions perform signed
comparisons.

</div>

<div id="jvms-2.11.8" class="section">

<div class="titlepage">

<div>

<div>

### 2.11.8. Method Invocation and Return Instructions

</div>

</div>

</div>

The following five instructions invoke methods:

<div class="norm">

- <span class="emphasis">*invokevirtual*</span> invokes an instance
  method of an object, dispatching on the (virtual) type of the object.

- <span class="emphasis">*invokeinterface*</span> invokes an interface
  method, searching the methods implemented by the particular run-time
  object to find the appropriate method.

- <span class="emphasis">*invokespecial*</span> invokes an instance
  method requiring special handling, either an instance initialization
  method (<a href="jvms-2.html#jvms-2.9.1" class="xref"
  title="2.9.1. Instance Initialization Methods">§2.9.1</a>) or a method
  of the current class or its supertypes.

- <span class="emphasis">*invokestatic*</span> invokes a class
  (`static`) method in a named class.

- <span class="emphasis">*invokedynamic*</span> invokes the method which
  is the target of the call site object bound to the
  <span class="emphasis">*invokedynamic*</span> instruction. The call
  site object was bound to a specific lexical occurrence of the
  <span class="emphasis">*invokedynamic*</span> instruction by the Java
  Virtual Machine as a result of running a bootstrap method before the
  first execution of the instruction. Therefore, each occurrence of an
  <span class="emphasis">*invokedynamic*</span> instruction has a unique
  linkage state, unlike the other instructions which invoke methods.

</div>

The method return instructions, which are distinguished by return type,
are <span class="emphasis">*ireturn*</span> (used for return types
`boolean`, `byte`, `char`, `short`, and `int`),
<span class="emphasis">*lreturn*</span>,
<span class="emphasis">*freturn*</span>,
<span class="emphasis">*dreturn*</span>, and
<span class="emphasis">*areturn*</span>. In addition, the
<span class="emphasis">*return*</span> instruction is used to return
from methods declared to be void, instance initialization methods, and
class or interface initialization methods.

</div>

<div id="jvms-2.11.9" class="section">

<div class="titlepage">

<div>

<div>

### 2.11.9. Throwing Exceptions

</div>

</div>

</div>

An exception is thrown programmatically using the
<span class="emphasis">*athrow*</span> instruction. Exceptions can also
be thrown by various Java Virtual Machine instructions if they detect an
abnormal condition.

</div>

<div id="jvms-2.11.10" class="section">

<div class="titlepage">

<div>

<div>

### 2.11.10. Synchronization

</div>

</div>

</div>

The Java Virtual Machine supports synchronization of both methods and
sequences of instructions within a method by a single synchronization
construct: the <span class="emphasis">*monitor*</span>.

Method-level synchronization is performed implicitly, as part of method
invocation and return (<a href="jvms-2.html#jvms-2.11.8" class="xref"
title="2.11.8. Method Invocation and Return Instructions">§2.11.8</a>).
A `synchronized` method is distinguished in the run-time constant pool's
`method_info` structure (<a href="jvms-4.html#jvms-4.6" class="xref"
title="4.6. Methods">§4.6</a>) by the `ACC_SYNCHRONIZED` flag, which is
checked by the method invocation instructions. When invoking a method
for which `ACC_SYNCHRONIZED` is set, the executing thread enters a
monitor, invokes the method itself, and exits the monitor whether the
method invocation completes normally or abruptly. During the time the
executing thread owns the monitor, no other thread may enter it. If an
exception is thrown during invocation of the `synchronized` method and
the `synchronized` method does not handle the exception, the monitor for
the method is automatically exited before the exception is rethrown out
of the `synchronized` method.

Synchronization of sequences of instructions is typically used to encode
the `synchronized` block of the Java programming language. The Java
Virtual Machine supplies the
<span class="emphasis">*monitorenter*</span> and
<span class="emphasis">*monitorexit*</span> instructions to support such
language constructs. Proper implementation of `synchronized` blocks
requires cooperation from a compiler targeting the Java Virtual Machine
(<a href="jvms-3.html#jvms-3.14" class="xref"
title="3.14. Synchronization">§3.14</a>).

<span class="emphasis">*Structured locking*</span> is the situation
when, during a method invocation, every exit on a given monitor matches
a preceding entry on that monitor. Since there is no assurance that all
code submitted to the Java Virtual Machine will perform structured
locking, implementations of the Java Virtual Machine are permitted but
not required to enforce both of the following two rules guaranteeing
structured locking. Let <span class="emphasis">*T*</span> be a thread
and <span class="emphasis">*M*</span> be a monitor. Then:

<div class="orderedlist">

1.  The number of monitor entries performed by
    <span class="emphasis">*T*</span> on
    <span class="emphasis">*M*</span> during a method invocation must
    equal the number of monitor exits performed by
    <span class="emphasis">*T*</span> on
    <span class="emphasis">*M*</span> during the method invocation
    whether the method invocation completes normally or abruptly.

2.  At no point during a method invocation may the number of monitor
    exits performed by <span class="emphasis">*T*</span> on
    <span class="emphasis">*M*</span> since the method invocation exceed
    the number of monitor entries performed by
    <span class="emphasis">*T*</span> on
    <span class="emphasis">*M*</span> since the method invocation.

</div>

Note that the monitor entry and exit automatically performed by the Java
Virtual Machine when invoking a `synchronized` method are considered to
occur during the calling method's invocation.

</div>

</div>

<div id="jvms-2.12" class="section">

<div class="titlepage">

<div>

<div>

## 2.12. Class Libraries

</div>

</div>

</div>

The Java Virtual Machine must provide sufficient support for the
implementation of the class libraries of the Java SE Platform. Some of
the classes in these libraries cannot be implemented without the
cooperation of the Java Virtual Machine.

Classes that might require special support from the Java Virtual Machine
include those that support:

<div class="norm">

- Reflection, such as the classes in the package `java.lang.reflect` and
  the class `Class`.

- Loading and creation of a class or interface. The most obvious example
  is the class `ClassLoader`.

- Linking and initialization of a class or interface. The example
  classes cited above fall into this category as well.

- The module system, such as the class `ModuleLayer`.

- Multithreading, such as the class `Thread`.

- Weak references, such as the classes in the package `java.lang.ref`.

</div>

The list above is meant to be illustrative rather than comprehensive. An
exhaustive list of these classes or of the functionality they provide is
beyond the scope of this specification. See the specifications of the
Java SE Platform class libraries for details.

</div>

<div id="jvms-2.13" class="section">

<div class="titlepage">

<div>

<div>

## 2.13. Public Design, Private Implementation

</div>

</div>

</div>

Thus far this specification has sketched the public view of the Java
Virtual Machine: the `class` file format and the instruction set. These
components are vital to the hardware-, operating system-, and
implementation-independence of the Java Virtual Machine. The implementor
may prefer to think of them as a means to securely communicate fragments
of programs between hosts each implementing the Java SE Platform, rather
than as a blueprint to be followed exactly.

It is important to understand where the line between the public design
and the private implementation lies. A Java Virtual Machine
implementation must be able to read `class` files and must exactly
implement the semantics of the Java Virtual Machine code therein. One
way of doing this is to take this document as a specification and to
implement that specification literally. But it is also perfectly
feasible and desirable for the implementor to modify or optimize the
implementation within the constraints of this specification. So long as
the `class` file format can be read and the semantics of its code are
maintained, the implementor may implement these semantics in any way.
What is "under the hood" is the implementor's business, as long as the
correct external interface is carefully maintained.

There are some exceptions: debuggers, profilers, and just-in-time code
generators can each require access to elements of the Java Virtual
Machine that are normally considered to be “under the hood.” Where
appropriate, Oracle works with other Java Virtual Machine implementors
and with tool vendors to develop common interfaces to the Java Virtual
Machine for use by such tools, and to promote those interfaces across
the industry.

The implementor can use this flexibility to tailor Java Virtual Machine
implementations for high performance, low memory use, or portability.
What makes sense in a given implementation depends on the goals of that
implementation. The range of implementation options includes the
following:

<div class="norm">

- Translating Java Virtual Machine code at load-time or during execution
  into the instruction set of another virtual machine.

- Translating Java Virtual Machine code at load-time or during execution
  into the native instruction set of the host CPU (sometimes referred to
  as <span class="emphasis">*just-in-time*</span>, or
  <span class="emphasis">*JIT*</span>, code generation).

</div>

The existence of a precisely defined virtual machine and object file
format need not significantly restrict the creativity of the
implementor. The Java Virtual Machine is designed to support many
different implementations, providing new and interesting solutions while
retaining compatibility between implementations.

</div>

</div>

<div class="navfooter">

------------------------------------------------------------------------

|  |  |  |
|:---|:--:|---:|
| <a href="jvms-1.html" accesskey="p">Prev</a>  |   |  <a href="jvms-3.html" accesskey="n">Next</a> |
| Chapter 1. Introduction  | <a href="index.html" accesskey="h">Home</a> |  Chapter 3. Compiling for the Java Virtual Machine |

</div>

<div class="navfooter">

------------------------------------------------------------------------

[Legal Notice](spec-frontmatter.html)

</div>
