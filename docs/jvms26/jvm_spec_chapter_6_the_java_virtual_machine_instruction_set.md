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
<th colspan="3" style="text-align: center;">Chapter 6. The Java Virtual
Machine Instruction Set</th>
</tr>
</thead>
<tbody>
<tr>
<td style="text-align: left; width: 20%;"><a href="jvms-5.html"
accesskey="p">Prev</a> </td>
<td style="text-align: center; width: 60%;"> </td>
<td style="text-align: right; width: 20%;"> <a href="jvms-7.html"
accesskey="n">Next</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

</div>

<div id="jvms-6" class="chapter" lang="en">

<div class="titlepage">

<div>

<div>

# Chapter 6. The Java Virtual Machine Instruction Set

</div>

</div>

</div>

<div class="toc">

**Table of Contents**

<span class="section">[6.1. Assumptions: The Meaning of
"Must"](jvms-6.html#jvms-6.1)</span>

<span class="section">[6.2. Reserved
Opcodes](jvms-6.html#jvms-6.2)</span>

<span class="section">[6.3. Virtual Machine
Errors](jvms-6.html#jvms-6.3)</span>

<span class="section">[6.4. Format of Instruction
Descriptions](jvms-6.html#jvms-6.4)</span>

<span class="section">[mnemonic](jvms-6.html#jvms-6.4-mnemonic)</span>

<span class="section">[6.5. Instructions](jvms-6.html#jvms-6.5)</span>

<span class="section">[<span class="emphasis">*aaload*</span>](jvms-6.html#jvms-6.5.aaload)</span>

<span class="section">[<span class="emphasis">*aastore*</span>](jvms-6.html#jvms-6.5.aastore)</span>

<span class="section">[<span class="emphasis">*aconst_null*</span>](jvms-6.html#jvms-6.5.aconst_null)</span>

<span class="section">[<span class="emphasis">*aload*</span>](jvms-6.html#jvms-6.5.aload)</span>

<span class="section">[<span class="emphasis">*aload\_\<n\>*</span>](jvms-6.html#jvms-6.5.aload_n)</span>

<span class="section">[<span class="emphasis">*anewarray*</span>](jvms-6.html#jvms-6.5.anewarray)</span>

<span class="section">[<span class="emphasis">*areturn*</span>](jvms-6.html#jvms-6.5.areturn)</span>

<span class="section">[<span class="emphasis">*arraylength*</span>](jvms-6.html#jvms-6.5.arraylength)</span>

<span class="section">[<span class="emphasis">*astore*</span>](jvms-6.html#jvms-6.5.astore)</span>

<span class="section">[<span class="emphasis">*astore\_\<n\>*</span>](jvms-6.html#jvms-6.5.astore_n)</span>

<span class="section">[<span class="emphasis">*athrow*</span>](jvms-6.html#jvms-6.5.athrow)</span>

<span class="section">[<span class="emphasis">*baload*</span>](jvms-6.html#jvms-6.5.baload)</span>

<span class="section">[<span class="emphasis">*bastore*</span>](jvms-6.html#jvms-6.5.bastore)</span>

<span class="section">[<span class="emphasis">*bipush*</span>](jvms-6.html#jvms-6.5.bipush)</span>

<span class="section">[<span class="emphasis">*caload*</span>](jvms-6.html#jvms-6.5.caload)</span>

<span class="section">[<span class="emphasis">*castore*</span>](jvms-6.html#jvms-6.5.castore)</span>

<span class="section">[<span class="emphasis">*checkcast*</span>](jvms-6.html#jvms-6.5.checkcast)</span>

<span class="section">[<span class="emphasis">*d2f*</span>](jvms-6.html#jvms-6.5.d2f)</span>

<span class="section">[<span class="emphasis">*d2i*</span>](jvms-6.html#jvms-6.5.d2i)</span>

<span class="section">[<span class="emphasis">*d2l*</span>](jvms-6.html#jvms-6.5.d2l)</span>

<span class="section">[<span class="emphasis">*dadd*</span>](jvms-6.html#jvms-6.5.dadd)</span>

<span class="section">[<span class="emphasis">*daload*</span>](jvms-6.html#jvms-6.5.daload)</span>

<span class="section">[<span class="emphasis">*dastore*</span>](jvms-6.html#jvms-6.5.dastore)</span>

<span class="section">[<span class="emphasis">*dcmp\<op\>*</span>](jvms-6.html#jvms-6.5.dcmp_op)</span>

<span class="section">[<span class="emphasis">*dconst\_\<d\>*</span>](jvms-6.html#jvms-6.5.dconst_d)</span>

<span class="section">[<span class="emphasis">*ddiv*</span>](jvms-6.html#jvms-6.5.ddiv)</span>

<span class="section">[<span class="emphasis">*dload*</span>](jvms-6.html#jvms-6.5.dload)</span>

<span class="section">[<span class="emphasis">*dload\_\<n\>*</span>](jvms-6.html#jvms-6.5.dload_n)</span>

<span class="section">[<span class="emphasis">*dmul*</span>](jvms-6.html#jvms-6.5.dmul)</span>

<span class="section">[<span class="emphasis">*dneg*</span>](jvms-6.html#jvms-6.5.dneg)</span>

<span class="section">[<span class="emphasis">*drem*</span>](jvms-6.html#jvms-6.5.drem)</span>

<span class="section">[<span class="emphasis">*dreturn*</span>](jvms-6.html#jvms-6.5.dreturn)</span>

<span class="section">[<span class="emphasis">*dstore*</span>](jvms-6.html#jvms-6.5.dstore)</span>

<span class="section">[<span class="emphasis">*dstore\_\<n\>*</span>](jvms-6.html#jvms-6.5.dstore_n)</span>

<span class="section">[<span class="emphasis">*dsub*</span>](jvms-6.html#jvms-6.5.dsub)</span>

<span class="section">[<span class="emphasis">*dup*</span>](jvms-6.html#jvms-6.5.dup)</span>

<span class="section">[<span class="emphasis">*dup_x1*</span>](jvms-6.html#jvms-6.5.dup_x1)</span>

<span class="section">[<span class="emphasis">*dup_x2*</span>](jvms-6.html#jvms-6.5.dup_x2)</span>

<span class="section">[<span class="emphasis">*dup2*</span>](jvms-6.html#jvms-6.5.dup2)</span>

<span class="section">[<span class="emphasis">*dup2_x1*</span>](jvms-6.html#jvms-6.5.dup2_x1)</span>

<span class="section">[<span class="emphasis">*dup2_x2*</span>](jvms-6.html#jvms-6.5.dup2_x2)</span>

<span class="section">[<span class="emphasis">*f2d*</span>](jvms-6.html#jvms-6.5.f2d)</span>

<span class="section">[<span class="emphasis">*f2i*</span>](jvms-6.html#jvms-6.5.f2i)</span>

<span class="section">[<span class="emphasis">*f2l*</span>](jvms-6.html#jvms-6.5.f2l)</span>

<span class="section">[<span class="emphasis">*fadd*</span>](jvms-6.html#jvms-6.5.fadd)</span>

<span class="section">[<span class="emphasis">*faload*</span>](jvms-6.html#jvms-6.5.faload)</span>

<span class="section">[<span class="emphasis">*fastore*</span>](jvms-6.html#jvms-6.5.fastore)</span>

<span class="section">[<span class="emphasis">*fcmp\<op\>*</span>](jvms-6.html#jvms-6.5.fcmp_op)</span>

<span class="section">[<span class="emphasis">*fconst\_\<f\>*</span>](jvms-6.html#jvms-6.5.fconst_f)</span>

<span class="section">[<span class="emphasis">*fdiv*</span>](jvms-6.html#jvms-6.5.fdiv)</span>

<span class="section">[<span class="emphasis">*fload*</span>](jvms-6.html#jvms-6.5.fload)</span>

<span class="section">[<span class="emphasis">*fload\_\<n\>*</span>](jvms-6.html#jvms-6.5.fload_n)</span>

<span class="section">[<span class="emphasis">*fmul*</span>](jvms-6.html#jvms-6.5.fmul)</span>

<span class="section">[<span class="emphasis">*fneg*</span>](jvms-6.html#jvms-6.5.fneg)</span>

<span class="section">[<span class="emphasis">*frem*</span>](jvms-6.html#jvms-6.5.frem)</span>

<span class="section">[<span class="emphasis">*freturn*</span>](jvms-6.html#jvms-6.5.freturn)</span>

<span class="section">[<span class="emphasis">*fstore*</span>](jvms-6.html#jvms-6.5.fstore)</span>

<span class="section">[<span class="emphasis">*fstore\_\<n\>*</span>](jvms-6.html#jvms-6.5.fstore_n)</span>

<span class="section">[<span class="emphasis">*fsub*</span>](jvms-6.html#jvms-6.5.fsub)</span>

<span class="section">[<span class="emphasis">*getfield*</span>](jvms-6.html#jvms-6.5.getfield)</span>

<span class="section">[<span class="emphasis">*getstatic*</span>](jvms-6.html#jvms-6.5.getstatic)</span>

<span class="section">[<span class="emphasis">*goto*</span>](jvms-6.html#jvms-6.5.goto)</span>

<span class="section">[<span class="emphasis">*goto_w*</span>](jvms-6.html#jvms-6.5.goto_w)</span>

<span class="section">[<span class="emphasis">*i2b*</span>](jvms-6.html#jvms-6.5.i2b)</span>

<span class="section">[<span class="emphasis">*i2c*</span>](jvms-6.html#jvms-6.5.i2c)</span>

<span class="section">[<span class="emphasis">*i2d*</span>](jvms-6.html#jvms-6.5.i2d)</span>

<span class="section">[<span class="emphasis">*i2f*</span>](jvms-6.html#jvms-6.5.i2f)</span>

<span class="section">[<span class="emphasis">*i2l*</span>](jvms-6.html#jvms-6.5.i2l)</span>

<span class="section">[<span class="emphasis">*i2s*</span>](jvms-6.html#jvms-6.5.i2s)</span>

<span class="section">[<span class="emphasis">*iadd*</span>](jvms-6.html#jvms-6.5.iadd)</span>

<span class="section">[<span class="emphasis">*iaload*</span>](jvms-6.html#jvms-6.5.iaload)</span>

<span class="section">[<span class="emphasis">*iand*</span>](jvms-6.html#jvms-6.5.iand)</span>

<span class="section">[<span class="emphasis">*iastore*</span>](jvms-6.html#jvms-6.5.iastore)</span>

<span class="section">[<span class="emphasis">*iconst\_\<i\>*</span>](jvms-6.html#jvms-6.5.iconst_i)</span>

<span class="section">[<span class="emphasis">*idiv*</span>](jvms-6.html#jvms-6.5.idiv)</span>

<span class="section">[<span class="emphasis">*if_acmp\<cond\>*</span>](jvms-6.html#jvms-6.5.if_acmp_cond)</span>

<span class="section">[<span class="emphasis">*if_icmp\<cond\>*</span>](jvms-6.html#jvms-6.5.if_icmp_cond)</span>

<span class="section">[<span class="emphasis">*if\<cond\>*</span>](jvms-6.html#jvms-6.5.if_cond)</span>

<span class="section">[<span class="emphasis">*ifnonnull*</span>](jvms-6.html#jvms-6.5.ifnonnull)</span>

<span class="section">[<span class="emphasis">*ifnull*</span>](jvms-6.html#jvms-6.5.ifnull)</span>

<span class="section">[<span class="emphasis">*iinc*</span>](jvms-6.html#jvms-6.5.iinc)</span>

<span class="section">[<span class="emphasis">*iload*</span>](jvms-6.html#jvms-6.5.iload)</span>

<span class="section">[<span class="emphasis">*iload\_\<n\>*</span>](jvms-6.html#jvms-6.5.iload_n)</span>

<span class="section">[<span class="emphasis">*imul*</span>](jvms-6.html#jvms-6.5.imul)</span>

<span class="section">[<span class="emphasis">*ineg*</span>](jvms-6.html#jvms-6.5.ineg)</span>

<span class="section">[<span class="emphasis">*instanceof*</span>](jvms-6.html#jvms-6.5.instanceof)</span>

<span class="section">[<span class="emphasis">*invokedynamic*</span>](jvms-6.html#jvms-6.5.invokedynamic)</span>

<span class="section">[<span class="emphasis">*invokeinterface*</span>](jvms-6.html#jvms-6.5.invokeinterface)</span>

<span class="section">[<span class="emphasis">*invokespecial*</span>](jvms-6.html#jvms-6.5.invokespecial)</span>

<span class="section">[<span class="emphasis">*invokestatic*</span>](jvms-6.html#jvms-6.5.invokestatic)</span>

<span class="section">[<span class="emphasis">*invokevirtual*</span>](jvms-6.html#jvms-6.5.invokevirtual)</span>

<span class="section">[<span class="emphasis">*ior*</span>](jvms-6.html#jvms-6.5.ior)</span>

<span class="section">[<span class="emphasis">*irem*</span>](jvms-6.html#jvms-6.5.irem)</span>

<span class="section">[<span class="emphasis">*ireturn*</span>](jvms-6.html#jvms-6.5.ireturn)</span>

<span class="section">[<span class="emphasis">*ishl*</span>](jvms-6.html#jvms-6.5.ishl)</span>

<span class="section">[<span class="emphasis">*ishr*</span>](jvms-6.html#jvms-6.5.ishr)</span>

<span class="section">[<span class="emphasis">*istore*</span>](jvms-6.html#jvms-6.5.istore)</span>

<span class="section">[<span class="emphasis">*istore\_\<n\>*</span>](jvms-6.html#jvms-6.5.istore_n)</span>

<span class="section">[<span class="emphasis">*isub*</span>](jvms-6.html#jvms-6.5.isub)</span>

<span class="section">[<span class="emphasis">*iushr*</span>](jvms-6.html#jvms-6.5.iushr)</span>

<span class="section">[<span class="emphasis">*ixor*</span>](jvms-6.html#jvms-6.5.ixor)</span>

<span class="section">[<span class="emphasis">*jsr*</span>](jvms-6.html#jvms-6.5.jsr)</span>

<span class="section">[<span class="emphasis">*jsr_w*</span>](jvms-6.html#jvms-6.5.jsr_w)</span>

<span class="section">[<span class="emphasis">*l2d*</span>](jvms-6.html#jvms-6.5.l2d)</span>

<span class="section">[<span class="emphasis">*l2f*</span>](jvms-6.html#jvms-6.5.l2f)</span>

<span class="section">[<span class="emphasis">*l2i*</span>](jvms-6.html#jvms-6.5.l2i)</span>

<span class="section">[<span class="emphasis">*ladd*</span>](jvms-6.html#jvms-6.5.ladd)</span>

<span class="section">[<span class="emphasis">*laload*</span>](jvms-6.html#jvms-6.5.laload)</span>

<span class="section">[<span class="emphasis">*land*</span>](jvms-6.html#jvms-6.5.land)</span>

<span class="section">[<span class="emphasis">*lastore*</span>](jvms-6.html#jvms-6.5.lastore)</span>

<span class="section">[<span class="emphasis">*lcmp*</span>](jvms-6.html#jvms-6.5.lcmp)</span>

<span class="section">[<span class="emphasis">*lconst\_\<l\>*</span>](jvms-6.html#jvms-6.5.lconst_l)</span>

<span class="section">[<span class="emphasis">*ldc*</span>](jvms-6.html#jvms-6.5.ldc)</span>

<span class="section">[<span class="emphasis">*ldc_w*</span>](jvms-6.html#jvms-6.5.ldc_w)</span>

<span class="section">[<span class="emphasis">*ldc2_w*</span>](jvms-6.html#jvms-6.5.ldc2_w)</span>

<span class="section">[<span class="emphasis">*ldiv*</span>](jvms-6.html#jvms-6.5.ldiv)</span>

<span class="section">[<span class="emphasis">*lload*</span>](jvms-6.html#jvms-6.5.lload)</span>

<span class="section">[<span class="emphasis">*lload\_\<n\>*</span>](jvms-6.html#jvms-6.5.lload_n)</span>

<span class="section">[<span class="emphasis">*lmul*</span>](jvms-6.html#jvms-6.5.lmul)</span>

<span class="section">[<span class="emphasis">*lneg*</span>](jvms-6.html#jvms-6.5.lneg)</span>

<span class="section">[<span class="emphasis">*lookupswitch*</span>](jvms-6.html#jvms-6.5.lookupswitch)</span>

<span class="section">[<span class="emphasis">*lor*</span>](jvms-6.html#jvms-6.5.lor)</span>

<span class="section">[<span class="emphasis">*lrem*</span>](jvms-6.html#jvms-6.5.lrem)</span>

<span class="section">[<span class="emphasis">*lreturn*</span>](jvms-6.html#jvms-6.5.lreturn)</span>

<span class="section">[<span class="emphasis">*lshl*</span>](jvms-6.html#jvms-6.5.lshl)</span>

<span class="section">[<span class="emphasis">*lshr*</span>](jvms-6.html#jvms-6.5.lshr)</span>

<span class="section">[<span class="emphasis">*lstore*</span>](jvms-6.html#jvms-6.5.lstore)</span>

<span class="section">[<span class="emphasis">*lstore\_\<n\>*</span>](jvms-6.html#jvms-6.5.lstore_n)</span>

<span class="section">[<span class="emphasis">*lsub*</span>](jvms-6.html#jvms-6.5.lsub)</span>

<span class="section">[<span class="emphasis">*lushr*</span>](jvms-6.html#jvms-6.5.lushr)</span>

<span class="section">[<span class="emphasis">*lxor*</span>](jvms-6.html#jvms-6.5.lxor)</span>

<span class="section">[<span class="emphasis">*monitorenter*</span>](jvms-6.html#jvms-6.5.monitorenter)</span>

<span class="section">[<span class="emphasis">*monitorexit*</span>](jvms-6.html#jvms-6.5.monitorexit)</span>

<span class="section">[<span class="emphasis">*multianewarray*</span>](jvms-6.html#jvms-6.5.multianewarray)</span>

<span class="section">[<span class="emphasis">*new*</span>](jvms-6.html#jvms-6.5.new)</span>

<span class="section">[<span class="emphasis">*newarray*</span>](jvms-6.html#jvms-6.5.newarray)</span>

<span class="section">[<span class="emphasis">*nop*</span>](jvms-6.html#jvms-6.5.nop)</span>

<span class="section">[<span class="emphasis">*pop*</span>](jvms-6.html#jvms-6.5.pop)</span>

<span class="section">[<span class="emphasis">*pop2*</span>](jvms-6.html#jvms-6.5.pop2)</span>

<span class="section">[<span class="emphasis">*putfield*</span>](jvms-6.html#jvms-6.5.putfield)</span>

<span class="section">[<span class="emphasis">*putstatic*</span>](jvms-6.html#jvms-6.5.putstatic)</span>

<span class="section">[<span class="emphasis">*ret*</span>](jvms-6.html#jvms-6.5.ret)</span>

<span class="section">[<span class="emphasis">*return*</span>](jvms-6.html#jvms-6.5.return)</span>

<span class="section">[<span class="emphasis">*saload*</span>](jvms-6.html#jvms-6.5.saload)</span>

<span class="section">[<span class="emphasis">*sastore*</span>](jvms-6.html#jvms-6.5.sastore)</span>

<span class="section">[<span class="emphasis">*sipush*</span>](jvms-6.html#jvms-6.5.sipush)</span>

<span class="section">[<span class="emphasis">*swap*</span>](jvms-6.html#jvms-6.5.swap)</span>

<span class="section">[<span class="emphasis">*tableswitch*</span>](jvms-6.html#jvms-6.5.tableswitch)</span>

<span class="section">[<span class="emphasis">*wide*</span>](jvms-6.html#jvms-6.5.wide)</span>

</div>

A Java Virtual Machine instruction consists of an opcode specifying the
operation to be performed, followed by zero or more operands embodying
values to be operated upon. This chapter gives details about the format
of each Java Virtual Machine instruction and the operation it performs.

<div id="jvms-6.1" class="section">

<div class="titlepage">

<div>

<div>

## 6.1. Assumptions: The Meaning of "Must"

</div>

</div>

</div>

The description of each instruction is always given in the context of
Java Virtual Machine code that satisfies the static and structural
constraints of <a href="jvms-4.html" class="xref"
title="Chapter 4. The class File Format">§4 (<em>The <code
class="literal">class</code> File Format</em>)</a>. In the description
of individual Java Virtual Machine instructions, we frequently state
that some situation "must" or "must not" be the case: "The
<span class="emphasis">*value2*</span> must be of type `int`." The
constraints of <a href="jvms-4.html" class="xref"
title="Chapter 4. The class File Format">§4 (<em>The <code
class="literal">class</code> File Format</em>)</a> guarantee that all
such expectations will in fact be met. If some constraint (a "must" or
"must not") in an instruction description is not satisfied at run time,
the behavior of the Java Virtual Machine is undefined.

The Java Virtual Machine checks that Java Virtual Machine code satisfies
the static and structural constraints at link time using a `class` file
verifier (<a href="jvms-4.html#jvms-4.10" class="xref"
title="4.10. Verification of class Files">§4.10</a>). Thus, the Java
Virtual Machine will only attempt to execute code from valid `class`
files. Performing verification at link time is attractive in that the
checks are performed just once, substantially reducing the amount of
work that must be done at run time. Other implementation strategies are
possible, provided that they comply with *The Java Language
Specification, Java SE 26 Edition* and *The Java Virtual Machine
Specification, Java SE 26 Edition*.

</div>

<div id="jvms-6.2" class="section">

<div class="titlepage">

<div>

<div>

## 6.2. Reserved Opcodes

</div>

</div>

</div>

In addition to the opcodes of the instructions specified later in this
chapter, which are used in `class` files
(<a href="jvms-4.html" class="xref"
title="Chapter 4. The class File Format">§4 (<em>The <code
class="literal">class</code> File Format</em>)</a>), three opcodes are
reserved for internal use by a Java Virtual Machine implementation. If
the instruction set of the Java Virtual Machine is extended in the
future, these reserved opcodes are guaranteed not to be used.

Two of the reserved opcodes, numbers 254 (0xfe) and 255 (0xff), have the
mnemonics <span class="emphasis">*impdep1*</span> and
<span class="emphasis">*impdep2*</span>, respectively. These
instructions are intended to provide "back doors" or traps to
implementation-specific functionality implemented in software and
hardware, respectively. The third reserved opcode, number 202 (0xca),
has the mnemonic <span class="emphasis">*breakpoint*</span> and is
intended to be used by debuggers to implement breakpoints.

Although these opcodes have been reserved, they may be used only inside
a Java Virtual Machine implementation. They cannot appear in valid
`class` files. Tools such as debuggers or JIT code generators
(<a href="jvms-2.html#jvms-2.13" class="xref"
title="2.13. Public Design, Private Implementation">§2.13</a>) that
might directly interact with Java Virtual Machine code that has been
already loaded and executed may encounter these opcodes. Such tools
should attempt to behave gracefully if they encounter any of these
reserved instructions.

</div>

<div id="jvms-6.3" class="section">

<div class="titlepage">

<div>

<div>

## 6.3. Virtual Machine Errors

</div>

</div>

</div>

A Java Virtual Machine implementation throws an object that is an
instance of a subclass of the class `VirtualMachineError` when an
internal error or resource limitation prevents it from implementing the
semantics described in this chapter. This specification cannot predict
where internal errors or resource limitations may be encountered and
does not mandate precisely when they can be reported. Thus, any of the
`VirtualMachineError` subclasses defined below may be thrown at any time
during the operation of the Java Virtual Machine:

<div class="norm">

- `InternalError`: An internal error has occurred in the Java Virtual
  Machine implementation because of a fault in the software implementing
  the virtual machine, a fault in the underlying host system software,
  or a fault in the hardware. This error is delivered asynchronously
  (<a href="jvms-2.html#jvms-2.10" class="xref"
  title="2.10. Exceptions">§2.10</a>) when it is detected and may occur
  at any point in a program.

- `OutOfMemoryError`: The Java Virtual Machine implementation has run
  out of either virtual or physical memory, and the automatic storage
  manager was unable to reclaim enough memory to satisfy an object
  creation request.

- `StackOverflowError`: The Java Virtual Machine implementation has run
  out of stack space for a thread, typically because the thread is doing
  an unbounded number of recursive invocations as a result of a fault in
  the executing program.

- `UnknownError`: An exception or error has occurred, but the Java
  Virtual Machine implementation is unable to report the actual
  exception or error.

</div>

</div>

<div id="jvms-6.4" class="section">

<div class="titlepage">

<div>

<div>

## 6.4. Format of Instruction Descriptions

</div>

</div>

</div>

Java Virtual Machine instructions are represented in this chapter by
entries of the form shown below, in alphabetical order and each
beginning on a new page.

<div id="jvms-6.4-mnemonic" class="section-execution">

<div class="titlepage">

<div>

<div>

### mnemonic

</div>

</div>

</div>

<div id="d5e16770" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Short description of the instruction

</div>

<div id="d5e16773" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*mnemonic*</span>  
<span class="emphasis">*operand1*</span>  
<span class="emphasis">*operand2*</span>  
...  

</div>

</div>

<div id="d5e16779" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*mnemonic*</span> = opcode

</div>

<div id="d5e16783" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*value3*</span>

</div>

<div id="d5e16791" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

A longer description detailing constraints on operand stack contents or
constant pool entries, the operation performed, the type of the results,
etc.

</div>

<div id="d5e16794" class="section">

<div class="titlepage">

<div>

<div>

#### Linking Exceptions

</div>

</div>

</div>

If any linking exceptions may be thrown by the execution of this
instruction, they are set off one to a line, in the order in which they
must be thrown.

</div>

<div id="d5e16797" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

If any run-time exceptions can be thrown by the execution of an
instruction, they are set off one to a line, in the order in which they
must be thrown.

Other than the linking and run-time exceptions, if any, listed for an
instruction, that instruction must not throw any run-time exceptions
except for instances of `VirtualMachineError` or its subclasses.

</div>

<div id="d5e16802" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

Comments not strictly part of the specification of an instruction are
set aside as notes at the end of the description.

</div>

</div>

Each cell in the instruction format diagram represents a single 8-bit
byte. The instruction's <span class="emphasis">*mnemonic*</span> is its
name. Its opcode is its numeric representation and is given in both
decimal and hexadecimal forms. Only the numeric representation is
actually present in the Java Virtual Machine code in a `class` file.

Keep in mind that there are "operands" generated at compile time and
embedded within Java Virtual Machine instructions, as well as "operands"
calculated at run time and supplied on the operand stack. Although they
are supplied from several different areas, all these operands represent
the same thing: values to be operated upon by the Java Virtual Machine
instruction being executed. By implicitly taking many of its operands
from its operand stack, rather than representing them explicitly in its
compiled code as additional operand bytes, register numbers, etc., the
Java Virtual Machine's code stays compact.

Some instructions are presented as members of a family of related
instructions sharing a single description, format, and operand stack
diagram. As such, a family of instructions includes several opcodes and
opcode mnemonics; only the family mnemonic appears in the instruction
format diagram, and a separate forms line lists all member mnemonics and
opcodes. For example, the Forms line for the
<span class="emphasis">*lconst\_\<l\>*</span> family of instructions,
giving mnemonic and opcode information for the two instructions in that
family (<span class="emphasis">*lconst_0*</span> and
<span class="emphasis">*lconst_1*</span>), is

<span class="emphasis">*lconst_0*</span> = 9 (0x9)

<span class="emphasis">*lconst_1*</span> = 10 (0xa)

In the description of the Java Virtual Machine instructions, the effect
of an instruction's execution on the operand stack
(<a href="jvms-2.html#jvms-2.6.2" class="xref"
title="2.6.2. Operand Stacks">§2.6.2</a>) of the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>)
is represented textually, with the stack growing from left to right and
each value represented separately. Thus,

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

shows an operation that begins by having
<span class="emphasis">*value2*</span> on top of the operand stack with
<span class="emphasis">*value1*</span> just beneath it. As a result of
the execution of the instruction, <span class="emphasis">*value1*</span>
and <span class="emphasis">*value2*</span> are popped from the operand
stack and replaced by <span class="emphasis">*result*</span> value,
which has been calculated by the instruction. The remainder of the
operand stack, represented by an ellipsis (...), is unaffected by the
instruction's execution.

Values of types `long` and `double` are represented by a single entry on
the operand stack.

In the First Edition of *The <span class="trademark">Java</span>®
Virtual Machine Specification*, values on the operand stack of types
`long` and `double` were each represented in the stack diagram by two
entries.

</div>

<div id="jvms-6.5" class="section">

<div class="titlepage">

<div>

<div>

## 6.5. Instructions

</div>

</div>

</div>

<div id="jvms-6.5.aaload" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*aaload*</span>

</div>

</div>

</div>

<div id="d5e16845" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Load `reference` from array

</div>

<div id="d5e16849" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*aaload*</span>  

</div>

</div>

<div id="d5e16853" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*aaload*</span> = 50 (0x32)

</div>

<div id="d5e16857" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*arrayref*</span>,
<span class="emphasis">*index*</span> <span class="symbol">→</span>

..., <span class="emphasis">*value*</span>

</div>

<div id="jvms-6.5.aaload.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*arrayref*</span> must be of type `reference`
and must refer to an array whose components are of type `reference`. The
<span class="emphasis">*index*</span> must be of type `int`. Both
<span class="emphasis">*arrayref*</span> and
<span class="emphasis">*index*</span> are popped from the operand stack.
The `reference` <span class="emphasis">*value*</span> in the component
of the array at <span class="emphasis">*index*</span> is retrieved and
pushed onto the operand stack.

</div>

<div id="jvms-6.5.aaload.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

If <span class="emphasis">*arrayref*</span> is `null`,
<span class="emphasis">*aaload*</span> throws a `NullPointerException`.

Otherwise, if <span class="emphasis">*index*</span> is not within the
bounds of the array referenced by
<span class="emphasis">*arrayref*</span>, the
<span class="emphasis">*aaload*</span> instruction throws an
`ArrayIndexOutOfBoundsException`.

</div>

</div>

<div id="jvms-6.5.aastore" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*aastore*</span>

</div>

</div>

</div>

<div id="d5e16893" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Store into `reference` array

</div>

<div id="d5e16897" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*aastore*</span>  

</div>

</div>

<div id="d5e16901" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*aastore*</span> = 83 (0x53)

</div>

<div id="d5e16905" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*arrayref*</span>,
<span class="emphasis">*index*</span>,
<span class="emphasis">*value*</span> <span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.aastore.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*arrayref*</span> must be of type `reference`
and must refer to an array whose components are of type `reference`. The
<span class="emphasis">*index*</span> must be of type `int`, and
<span class="emphasis">*value*</span> must be of type `reference`. The
<span class="emphasis">*arrayref*</span>,
<span class="emphasis">*index*</span>, and
<span class="emphasis">*value*</span> are popped from the operand stack.

If <span class="emphasis">*value*</span> is `null`, then
<span class="emphasis">*value*</span> is stored as the component of the
array at <span class="emphasis">*index*</span>.

Otherwise, <span class="emphasis">*value*</span> is non-`null`. If
<span class="emphasis">*value*</span> is a value of the component type
of the array referenced by <span class="emphasis">*arrayref*</span>,
then <span class="emphasis">*value*</span> is stored as the component of
the array at <span class="emphasis">*index*</span>.

Whether <span class="emphasis">*value*</span> is a value of the array
component type is determined according to the rules given for
<a href="jvms-6.html#jvms-6.5.checkcast" class="xref"
title="checkcast">§<span class="emphasis"><em>checkcast</em></span></a>.

</div>

<div id="jvms-6.5.aastore.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

If <span class="emphasis">*arrayref*</span> is `null`,
<span class="emphasis">*aastore*</span> throws a `NullPointerException`.

Otherwise, if <span class="emphasis">*index*</span> is not within the
bounds of the array referenced by
<span class="emphasis">*arrayref*</span>, the
<span class="emphasis">*aastore*</span> instruction throws an
`ArrayIndexOutOfBoundsException`.

Otherwise, if the non-`null` <span class="emphasis">*value*</span> is
not a value of the array component type,
<span class="emphasis">*aastore*</span> throws an `ArrayStoreException`.

</div>

</div>

<div id="jvms-6.5.aconst_null" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*aconst_null*</span>

</div>

</div>

</div>

<div id="d5e16963" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Push `null`

</div>

<div id="d5e16967" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*aconst_null*</span>  

</div>

</div>

<div id="d5e16971" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*aconst_null*</span> = 1 (0x1)

</div>

<div id="d5e16975" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

... <span class="symbol">→</span>

..., `null`

</div>

<div id="jvms-6.5.aconst_null.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Push the `null` object `reference` onto the operand stack.

</div>

<div id="jvms-6.5.aconst_null.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The Java Virtual Machine does not mandate a concrete value for `null`.

</div>

</div>

<div id="jvms-6.5.aload" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*aload*</span>

</div>

</div>

</div>

<div id="d5e16993" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Load `reference` from local variable

</div>

<div id="d5e16997" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*aload*</span>  
<span class="emphasis">*index*</span>  

</div>

</div>

<div id="d5e17002" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*aload*</span> = 25 (0x19)

</div>

<div id="d5e17006" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

... <span class="symbol">→</span>

..., <span class="emphasis">*objectref*</span>

</div>

<div id="jvms-6.5.aload.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*index*</span> is an unsigned byte that must
be an index into the local variable array of the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>).
The local variable at <span class="emphasis">*index*</span> must contain
a `reference`. The <span class="emphasis">*objectref*</span> in the
local variable at <span class="emphasis">*index*</span> is pushed onto
the operand stack.

</div>

<div id="jvms-6.5.aload.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*aload*</span> instruction cannot be used to
load a value of type `returnAddress` from a local variable onto the
operand stack. This asymmetry with the
<span class="emphasis">*astore*</span> instruction
(<a href="jvms-6.html#jvms-6.5.astore" class="xref" title="astore">§<span
class="emphasis"><em>astore</em></span></a>) is intentional.

The <span class="emphasis">*aload*</span> opcode can be used in
conjunction with the <span class="emphasis">*wide*</span> instruction
(<a href="jvms-6.html#jvms-6.5.wide" class="xref" title="wide">§<span
class="emphasis"><em>wide</em></span></a>) to access a local variable
using a two-byte unsigned index.

</div>

</div>

<div id="jvms-6.5.aload_n" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*aload\_\<n\>*</span>

</div>

</div>

</div>

<div id="d5e17035" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Load `reference` from local variable

</div>

<div id="d5e17039" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*aload\_\<n\>*</span>  

</div>

</div>

<div id="d5e17043" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*aload_0*</span> = 42 (0x2a)

<span class="emphasis">*aload_1*</span> = 43 (0x2b)

<span class="emphasis">*aload_2*</span> = 44 (0x2c)

<span class="emphasis">*aload_3*</span> = 45 (0x2d)

</div>

<div id="d5e17053" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

... <span class="symbol">→</span>

..., <span class="emphasis">*objectref*</span>

</div>

<div id="jvms-6.5.aload_n.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The \<<span class="emphasis">*n*</span>\> must be an index into the
local variable array of the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>).
The local variable at \<<span class="emphasis">*n*</span>\> must contain
a `reference`. The <span class="emphasis">*objectref*</span> in the
local variable at \<<span class="emphasis">*n*</span>\> is pushed onto
the operand stack.

</div>

<div id="jvms-6.5.aload_n.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

An <span class="emphasis">*aload\_\<n\>*</span> instruction cannot be
used to load a value of type `returnAddress` from a local variable onto
the operand stack. This asymmetry with the corresponding
<span class="emphasis">*astore\_\<n\>*</span> instruction
(<a href="jvms-6.html#jvms-6.5.astore_n" class="xref"
title="astore_&lt;n&gt;">§<span
class="emphasis"><em>astore_&lt;n&gt;</em></span></a>) is intentional.

Each of the <span class="emphasis">*aload\_\<n\>*</span> instructions is
the same as <span class="emphasis">*aload*</span> with an
<span class="emphasis">*index*</span> of
\<<span class="emphasis">*n*</span>\>, except that the operand
\<<span class="emphasis">*n*</span>\> is implicit.

</div>

</div>

<div id="jvms-6.5.anewarray" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*anewarray*</span>

</div>

</div>

</div>

<div id="d5e17084" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Create new array of `reference`

</div>

<div id="d5e17088" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*anewarray*</span>  
<span class="emphasis">*indexbyte1*</span>  
<span class="emphasis">*indexbyte2*</span>  

</div>

</div>

<div id="d5e17094" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

anewarray = 189 (0xbd)

</div>

<div id="d5e17097" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*count*</span> <span class="symbol">→</span>

..., <span class="emphasis">*arrayref*</span>

</div>

<div id="jvms-6.5.anewarray.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*count*</span> must be of type `int`. It is
popped off the operand stack. The <span class="emphasis">*count*</span>
represents the number of components of the array to be created. The
unsigned <span class="emphasis">*indexbyte1*</span> and
<span class="emphasis">*indexbyte2*</span> are used to construct an
index into the run-time constant pool of the current class
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>),
where the value of the index is
(<span class="emphasis">*indexbyte1*</span> `<<` 8) \|
<span class="emphasis">*indexbyte2*</span>. The run-time constant pool
entry at the index must be a symbolic reference to a class, array, or
interface type. The named class, array, or interface type is resolved
(<a href="jvms-5.html#jvms-5.4.3.1" class="xref"
title="5.4.3.1. Class and Interface Resolution">§5.4.3.1</a>). A new
array with components of that type, of length
<span class="emphasis">*count*</span>, is allocated from the
garbage-collected heap, and a `reference`
<span class="emphasis">*arrayref*</span> to this new array object is
pushed onto the operand stack. All components of the new array are
initialized to `null`, the default value for `reference` types
(<a href="jvms-2.html#jvms-2.4" class="xref"
title="2.4. Reference Types and Values">§2.4</a>).

</div>

<div id="jvms-6.5.anewarray.linking" class="section">

<div class="titlepage">

<div>

<div>

#### Linking Exceptions

</div>

</div>

</div>

During resolution of the symbolic reference to the class, array, or
interface type, any of the exceptions documented in
<a href="jvms-5.html#jvms-5.4.3.1" class="xref"
title="5.4.3.1. Class and Interface Resolution">§5.4.3.1</a> can be
thrown.

</div>

<div id="jvms-6.5.anewarray.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

Otherwise, if <span class="emphasis">*count*</span> is less than zero,
the <span class="emphasis">*anewarray*</span> instruction throws a
`NegativeArraySizeException`.

</div>

<div id="jvms-6.5.anewarray.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*anewarray*</span> instruction is used to
create a single dimension of an array of object references or part of a
multidimensional array.

</div>

</div>

<div id="jvms-6.5.areturn" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*areturn*</span>

</div>

</div>

</div>

<div id="d5e17140" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Return `reference` from method

</div>

<div id="d5e17144" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*areturn*</span>  

</div>

</div>

<div id="d5e17148" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*areturn*</span> = 176 (0xb0)

</div>

<div id="d5e17152" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*objectref*</span>
<span class="symbol">→</span>

\[empty\]

</div>

<div id="jvms-6.5.areturn.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*objectref*</span> must be of type
`reference` and must refer to an object of a type that is assignment
compatible (JLS §5.2) with the type represented by the return descriptor
(<a href="jvms-4.html#jvms-4.3.3" class="xref"
title="4.3.3. Method Descriptors">§4.3.3</a>) of the current method. If
the current method is a `synchronized` method, the monitor entered or
reentered on invocation of the method is updated and possibly exited as
if by execution of a <span class="emphasis">*monitorexit*</span>
instruction (<a href="jvms-6.html#jvms-6.5.monitorexit" class="xref"
title="monitorexit">§<span
class="emphasis"><em>monitorexit</em></span></a>) in the current thread.
If no exception is thrown, <span class="emphasis">*objectref*</span> is
popped from the operand stack of the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>)
and pushed onto the operand stack of the frame of the invoker. Any other
values on the operand stack of the current method are discarded.

The interpreter then reinstates the frame of the invoker and returns
control to the invoker.

</div>

<div id="jvms-6.5.areturn.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

If the Java Virtual Machine implementation does not enforce the rules on
structured locking described in
<a href="jvms-2.html#jvms-2.11.10" class="xref"
title="2.11.10. Synchronization">§2.11.10</a>, then if the current
method is a `synchronized` method and the current thread is not the
owner of the monitor entered or reentered on invocation of the method,
<span class="emphasis">*areturn*</span> throws an
`IllegalMonitorStateException`. This can happen, for example, if a
`synchronized` method contains a
<span class="emphasis">*monitorexit*</span> instruction, but no
<span class="emphasis">*monitorenter*</span> instruction, on the object
on which the method is synchronized.

Otherwise, if the Java Virtual Machine implementation enforces the rules
on structured locking described in
<a href="jvms-2.html#jvms-2.11.10" class="xref"
title="2.11.10. Synchronization">§2.11.10</a> and if the first of those
rules is violated during invocation of the current method, then
<span class="emphasis">*areturn*</span> throws an
`IllegalMonitorStateException`.

</div>

</div>

<div id="jvms-6.5.arraylength" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*arraylength*</span>

</div>

</div>

</div>

<div id="d5e17187" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Get length of array

</div>

<div id="d5e17190" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*arraylength*</span>  

</div>

</div>

<div id="d5e17194" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*arraylength*</span> = 190 (0xbe)

</div>

<div id="d5e17198" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*arrayref*</span>
<span class="symbol">→</span>

..., <span class="emphasis">*length*</span>

</div>

<div id="jvms-6.5.arraylength.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*arrayref*</span> must be of type `reference`
and must refer to an array. It is popped from the operand stack. The
<span class="emphasis">*length*</span> of the array it references is
determined. That <span class="emphasis">*length*</span> is pushed onto
the operand stack as an `int`.

</div>

<div id="jvms-6.5.arraylength.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

If the <span class="emphasis">*arrayref*</span> is `null`, the
<span class="emphasis">*arraylength*</span> instruction throws a
`NullPointerException`.

</div>

</div>

<div id="jvms-6.5.astore" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*astore*</span>

</div>

</div>

</div>

<div id="d5e17223" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Store `reference` into local variable

</div>

<div id="d5e17227" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*astore*</span>  
<span class="emphasis">*index*</span>  

</div>

</div>

<div id="d5e17232" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*astore*</span> = 58 (0x3a)

</div>

<div id="d5e17236" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*objectref*</span>
<span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.astore.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*index*</span> is an unsigned byte that must
be an index into the local variable array of the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>).
The <span class="emphasis">*objectref*</span> on the top of the operand
stack must be of type `returnAddress` or of type `reference`. It is
popped from the operand stack, and the value of the local variable at
<span class="emphasis">*index*</span> is set to
<span class="emphasis">*objectref*</span>.

</div>

<div id="jvms-6.5.astore.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*astore*</span> instruction is used with an
<span class="emphasis">*objectref*</span> of type `returnAddress` when
implementing the `finally` clause of the Java programming language
(<a href="jvms-3.html#jvms-3.13" class="xref"
title="3.13. Compiling finally">§3.13</a>).

The <span class="emphasis">*aload*</span> instruction
(<a href="jvms-6.html#jvms-6.5.aload" class="xref" title="aload">§<span
class="emphasis"><em>aload</em></span></a>) cannot be used to load a
value of type `returnAddress` from a local variable onto the operand
stack. This asymmetry with the <span class="emphasis">*astore*</span>
instruction is intentional.

The <span class="emphasis">*astore*</span> opcode can be used in
conjunction with the <span class="emphasis">*wide*</span> instruction
(<a href="jvms-6.html#jvms-6.5.wide" class="xref" title="wide">§<span
class="emphasis"><em>wide</em></span></a>) to access a local variable
using a two-byte unsigned index.

</div>

</div>

<div id="jvms-6.5.astore_n" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*astore\_\<n\>*</span>

</div>

</div>

</div>

<div id="d5e17272" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Store `reference` into local variable

</div>

<div id="d5e17276" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*astore\_\<n\>*</span>  

</div>

</div>

<div id="d5e17280" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*astore_0*</span> = 75 (0x4b)

<span class="emphasis">*astore_1*</span> = 76 (0x4c)

<span class="emphasis">*astore_2*</span> = 77 (0x4d)

<span class="emphasis">*astore_3*</span> = 78 (0x4e)

</div>

<div id="d5e17290" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*objectref*</span>
<span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.astore_n.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The \<<span class="emphasis">*n*</span>\> must be an index into the
local variable array of the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>).
The <span class="emphasis">*objectref*</span> on the top of the operand
stack must be of type `returnAddress` or of type `reference`. It is
popped from the operand stack, and the value of the local variable at
\<<span class="emphasis">*n*</span>\> is set to
<span class="emphasis">*objectref*</span>.

</div>

<div id="jvms-6.5.astore_n.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

An <span class="emphasis">*astore\_\<n\>*</span> instruction is used
with an <span class="emphasis">*objectref*</span> of type
`returnAddress` when implementing the `finally` clauses of the Java
programming language (<a href="jvms-3.html#jvms-3.13" class="xref"
title="3.13. Compiling finally">§3.13</a>).

An <span class="emphasis">*aload\_\<n\>*</span> instruction
(<a href="jvms-6.html#jvms-6.5.aload_n" class="xref"
title="aload_&lt;n&gt;">§<span
class="emphasis"><em>aload_&lt;n&gt;</em></span></a>) cannot be used to
load a value of type `returnAddress` from a local variable onto the
operand stack. This asymmetry with the corresponding
<span class="emphasis">*astore\_\<n\>*</span> instruction is
intentional.

Each of the <span class="emphasis">*astore\_\<n\>*</span> instructions
is the same as <span class="emphasis">*astore*</span> with an
<span class="emphasis">*index*</span> of
\<<span class="emphasis">*n*</span>\>, except that the operand
\<<span class="emphasis">*n*</span>\> is implicit.

</div>

</div>

<div id="jvms-6.5.athrow" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*athrow*</span>

</div>

</div>

</div>

<div id="d5e17328" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Throw exception or error

</div>

<div id="d5e17331" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*athrow*</span>  

</div>

</div>

<div id="d5e17335" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*athrow*</span> = 191 (0xbf)

</div>

<div id="d5e17339" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*objectref*</span>
<span class="symbol">→</span>

<span class="emphasis">*objectref*</span>

</div>

<div id="jvms-6.5.athrow.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*objectref*</span> must be of type
`reference` and must refer to an object that is an instance of class
`Throwable` or of a subclass of `Throwable`. It is popped from the
operand stack. The <span class="emphasis">*objectref*</span> is then
thrown by searching the current method
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>)
for the first exception handler that matches the class of
<span class="emphasis">*objectref*</span>, as given by the algorithm in
<a href="jvms-2.html#jvms-2.10" class="xref"
title="2.10. Exceptions">§2.10</a>.

If an exception handler that matches
<span class="emphasis">*objectref*</span> is found, it contains the
location of the code intended to handle this exception. The `pc`
register is reset to that location, the operand stack of the current
frame is cleared, <span class="emphasis">*objectref*</span> is pushed
back onto the operand stack, and execution continues.

If no matching exception handler is found in the current frame, that
frame is popped. If the current frame represents an invocation of a
`synchronized` method, the monitor entered or reentered on invocation of
the method is exited as if by execution of a
<span class="emphasis">*monitorexit*</span> instruction
(<a href="jvms-6.html#jvms-6.5.monitorexit" class="xref"
title="monitorexit">§<span
class="emphasis"><em>monitorexit</em></span></a>). Finally, the frame of
its invoker is reinstated, if such a frame exists, and the
<span class="emphasis">*objectref*</span> is rethrown. If no such frame
exists, the current thread exits.

</div>

<div id="jvms-6.5.athrow.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

If <span class="emphasis">*objectref*</span> is `null`,
<span class="emphasis">*athrow*</span> throws a `NullPointerException`
instead of <span class="emphasis">*objectref*</span>.

Otherwise, if the Java Virtual Machine implementation does not enforce
the rules on structured locking described in
<a href="jvms-2.html#jvms-2.11.10" class="xref"
title="2.11.10. Synchronization">§2.11.10</a>, then if the method of the
current frame is a `synchronized` method and the current thread is not
the owner of the monitor entered or reentered on invocation of the
method, <span class="emphasis">*athrow*</span> throws an
`IllegalMonitorStateException` instead of the object previously being
thrown. This can happen, for example, if an abruptly completing
`synchronized` method contains a
<span class="emphasis">*monitorexit*</span> instruction, but no
<span class="emphasis">*monitorenter*</span> instruction, on the object
on which the method is synchronized.

Otherwise, if the Java Virtual Machine implementation enforces the rules
on structured locking described in
<a href="jvms-2.html#jvms-2.11.10" class="xref"
title="2.11.10. Synchronization">§2.11.10</a> and if the first of those
rules is violated during invocation of the current method, then
<span class="emphasis">*athrow*</span> throws an
`IllegalMonitorStateException` instead of the object previously being
thrown.

</div>

<div id="jvms-6.5.athrow.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The operand stack diagram for the <span class="emphasis">*athrow*</span>
instruction may be misleading: If a handler for this exception is
matched in the current method, the
<span class="emphasis">*athrow*</span> instruction discards all the
values on the operand stack, then pushes the thrown object onto the
operand stack. However, if no handler is matched in the current method
and the exception is thrown farther up the method invocation chain, then
the operand stack of the method (if any) that handles the exception is
cleared and <span class="emphasis">*objectref*</span> is pushed onto
that empty operand stack. All intervening frames from the method that
threw the exception up to, but not including, the method that handles
the exception are discarded.

</div>

</div>

<div id="jvms-6.5.baload" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*baload*</span>

</div>

</div>

</div>

<div id="d5e17395" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Load `byte` or `boolean` from array

</div>

<div id="d5e17400" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*baload*</span>  

</div>

</div>

<div id="d5e17404" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*baload*</span> = 51 (0x33)

</div>

<div id="d5e17408" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*arrayref*</span>,
<span class="emphasis">*index*</span> <span class="symbol">→</span>

..., <span class="emphasis">*value*</span>

</div>

<div id="jvms-6.5.baload.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*arrayref*</span> must be of type `reference`
and must refer to an array whose components are of type `byte` or of
type `boolean`. The <span class="emphasis">*index*</span> must be of
type `int`. Both <span class="emphasis">*arrayref*</span> and
<span class="emphasis">*index*</span> are popped from the operand stack.
The `byte` <span class="emphasis">*value*</span> in the component of the
array at <span class="emphasis">*index*</span> is retrieved,
sign-extended to an `int` <span class="emphasis">*value*</span>, and
pushed onto the top of the operand stack.

</div>

<div id="jvms-6.5.baload.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

If <span class="emphasis">*arrayref*</span> is `null`,
<span class="emphasis">*baload*</span> throws a `NullPointerException`.

Otherwise, if <span class="emphasis">*index*</span> is not within the
bounds of the array referenced by
<span class="emphasis">*arrayref*</span>, the
<span class="emphasis">*baload*</span> instruction throws an
`ArrayIndexOutOfBoundsException`.

</div>

<div id="jvms-6.5.baload.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*baload*</span> instruction is used to load
values from both `byte` and `boolean` arrays. In Oracle's Java Virtual
Machine implementation, `boolean` arrays - that is, arrays of type
`T_BOOLEAN` (<a href="jvms-2.html#jvms-2.2" class="xref"
title="2.2. Data Types">§2.2</a>,
<a href="jvms-6.html#jvms-6.5.newarray" class="xref"
title="newarray">§<span class="emphasis"><em>newarray</em></span></a>) -
are implemented as arrays of 8-bit values. Other implementations may
implement packed `boolean` arrays; the
<span class="emphasis">*baload*</span> instruction of such
implementations must be used to access those arrays.

</div>

</div>

<div id="jvms-6.5.bastore" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*bastore*</span>

</div>

</div>

</div>

<div id="d5e17459" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Store into `byte` or `boolean` array

</div>

<div id="d5e17464" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*bastore*</span>  

</div>

</div>

<div id="d5e17468" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*bastore*</span> = 84 (0x54)

</div>

<div id="d5e17472" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*arrayref*</span>,
<span class="emphasis">*index*</span>,
<span class="emphasis">*value*</span> <span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.bastore.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*arrayref*</span> must be of type `reference`
and must refer to an array whose components are of type `byte` or of
type `boolean`. The <span class="emphasis">*index*</span> and the
<span class="emphasis">*value*</span> must both be of type `int`. The
<span class="emphasis">*arrayref*</span>,
<span class="emphasis">*index*</span>, and
<span class="emphasis">*value*</span> are popped from the operand stack.

If the <span class="emphasis">*arrayref*</span> refers to an array whose
components are of type `byte`, then the `int`
<span class="emphasis">*value*</span> is truncated to a `byte` and
stored as the component of the array indexed by
<span class="emphasis">*index*</span>.

If the <span class="emphasis">*arrayref*</span> refers to an array whose
components are of type `boolean`, then the `int`
<span class="emphasis">*value*</span> is narrowed by taking the bitwise
AND of <span class="emphasis">*value*</span> and 1; the result is stored
as the component of the array indexed by
<span class="emphasis">*index*</span>.

</div>

<div id="jvms-6.5.bastore.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

If <span class="emphasis">*arrayref*</span> is `null`,
<span class="emphasis">*bastore*</span> throws a `NullPointerException`.

Otherwise, if <span class="emphasis">*index*</span> is not within the
bounds of the array referenced by
<span class="emphasis">*arrayref*</span>, the
<span class="emphasis">*bastore*</span> instruction throws an
`ArrayIndexOutOfBoundsException`.

</div>

<div id="jvms-6.5.bastore.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*bastore*</span> instruction is used to store
values into both `byte` and `boolean` arrays. In Oracle's Java Virtual
Machine implementation, `boolean` arrays - that is, arrays of type
`T_BOOLEAN` (<a href="jvms-2.html#jvms-2.2" class="xref"
title="2.2. Data Types">§2.2</a>,
<a href="jvms-6.html#jvms-6.5.newarray" class="xref"
title="newarray">§<span class="emphasis"><em>newarray</em></span></a>) -
are implemented as arrays of 8-bit values. Other implementations may
implement packed `boolean` arrays; in such implementations the
<span class="emphasis">*bastore*</span> instruction must be able to
store `boolean` values into packed `boolean` arrays as well as `byte`
values into `byte` arrays.

</div>

</div>

<div id="jvms-6.5.bipush" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*bipush*</span>

</div>

</div>

</div>

<div id="d5e17538" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Push `byte`

</div>

<div id="d5e17542" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*bipush*</span>  
<span class="emphasis">*byte*</span>  

</div>

</div>

<div id="d5e17547" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*bipush*</span> = 16 (0x10)

</div>

<div id="d5e17551" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

... <span class="symbol">→</span>

..., <span class="emphasis">*value*</span>

</div>

<div id="jvms-6.5.bipush.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The immediate <span class="emphasis">*byte*</span> is sign-extended to
an `int` <span class="emphasis">*value*</span>. That
<span class="emphasis">*value*</span> is pushed onto the operand stack.

</div>

</div>

<div id="jvms-6.5.caload" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*caload*</span>

</div>

</div>

</div>

<div id="d5e17567" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Load `char` from array

</div>

<div id="d5e17571" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*caload*</span>  

</div>

</div>

<div id="d5e17575" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*caload*</span> = 52 (0x34)

</div>

<div id="d5e17579" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*arrayref*</span>,
<span class="emphasis">*index*</span> <span class="symbol">→</span>

..., <span class="emphasis">*value*</span>

</div>

<div id="jvms-6.5.caload.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*arrayref*</span> must be of type `reference`
and must refer to an array whose components are of type `char`. The
<span class="emphasis">*index*</span> must be of type `int`. Both
<span class="emphasis">*arrayref*</span> and
<span class="emphasis">*index*</span> are popped from the operand stack.
The component of the array at <span class="emphasis">*index*</span> is
retrieved and zero-extended to an `int`
<span class="emphasis">*value*</span>. That
<span class="emphasis">*value*</span> is pushed onto the operand stack.

</div>

<div id="jvms-6.5.caload.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

If <span class="emphasis">*arrayref*</span> is `null`,
<span class="emphasis">*caload*</span> throws a `NullPointerException`.

Otherwise, if <span class="emphasis">*index*</span> is not within the
bounds of the array referenced by
<span class="emphasis">*arrayref*</span>, the
<span class="emphasis">*caload*</span> instruction throws an
`ArrayIndexOutOfBoundsException`.

</div>

</div>

<div id="jvms-6.5.castore" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*castore*</span>

</div>

</div>

</div>

<div id="d5e17616" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Store into `char` array

</div>

<div id="d5e17620" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*castore*</span>  

</div>

</div>

<div id="d5e17624" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*castore*</span> = 85 (0x55)

</div>

<div id="d5e17628" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*arrayref*</span>,
<span class="emphasis">*index*</span>,
<span class="emphasis">*value*</span> <span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.castore.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*arrayref*</span> must be of type `reference`
and must refer to an array whose components are of type `char`. The
<span class="emphasis">*index*</span> and the
<span class="emphasis">*value*</span> must both be of type `int`. The
<span class="emphasis">*arrayref*</span>,
<span class="emphasis">*index*</span>, and
<span class="emphasis">*value*</span> are popped from the operand stack.
The `int` <span class="emphasis">*value*</span> is truncated to a `char`
and stored as the component of the array indexed by
<span class="emphasis">*index*</span>.

</div>

<div id="jvms-6.5.castore.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

If <span class="emphasis">*arrayref*</span> is `null`,
<span class="emphasis">*castore*</span> throws a `NullPointerException`.

Otherwise, if <span class="emphasis">*index*</span> is not within the
bounds of the array referenced by
<span class="emphasis">*arrayref*</span>, the
<span class="emphasis">*castore*</span> instruction throws an
`ArrayIndexOutOfBoundsException`.

</div>

</div>

<div id="jvms-6.5.checkcast" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*checkcast*</span>

</div>

</div>

</div>

<div id="d5e17667" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Check whether object is of given type

</div>

<div id="d5e17670" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*checkcast*</span>  
<span class="emphasis">*indexbyte1*</span>  
<span class="emphasis">*indexbyte2*</span>  

</div>

</div>

<div id="d5e17676" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*checkcast*</span> = 192 (0xc0)

</div>

<div id="d5e17680" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*objectref*</span>
<span class="symbol">→</span>

..., <span class="emphasis">*objectref*</span>

</div>

<div id="jvms-6.5.checkcast.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*objectref*</span> must be of type
`reference`. The unsigned <span class="emphasis">*indexbyte1*</span> and
<span class="emphasis">*indexbyte2*</span> are used to construct an
index into the run-time constant pool of the current class
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>),
where the value of the index is
(<span class="emphasis">*indexbyte1*</span> `<<` 8) \|
<span class="emphasis">*indexbyte2*</span>. The run-time constant pool
entry at the index must be a symbolic reference to a class, array, or
interface type.

If <span class="emphasis">*objectref*</span> is `null`, then the operand
stack is unchanged.

Otherwise, the named class, array, or interface type is resolved
(<a href="jvms-5.html#jvms-5.4.3.1" class="xref"
title="5.4.3.1. Class and Interface Resolution">§5.4.3.1</a>). If
<span class="emphasis">*objectref*</span> is a value of the type given
by the resolved class, array, or interface type, the operand stack is
unchanged.

The following rules are used to determine whether a non-`null` reference
to an object is a value of a reference type,
<span class="type">T</span>.

<div class="norm">

- If the reference is to an instance of a class
  <span class="type">C</span>, then:

  <div class="norm">

  - If <span class="type">T</span> is the type of a class
    <span class="type">D</span>, then the reference is a value of
    <span class="type">T</span> if <span class="type">C</span> is
    <span class="type">D</span> or a subclass of
    <span class="type">D</span>;

  - If <span class="type">T</span> is the type of an interface
    <span class="type">I</span>, then the reference is a value of
    <span class="type">T</span> if <span class="type">C</span>
    implements <span class="type">I</span>.

  </div>

- If the reference is to an array with component type
  <span class="type">SC</span>, then:

  <div class="norm">

  - If <span class="type">T</span> is a class type, then the reference
    is a value of <span class="type">T</span> if
    <span class="type">T</span> is `Object`;

  - If <span class="type">T</span> is an interface type, then the
    reference is a value of <span class="type">T</span> if
    <span class="type">T</span> is `Cloneable` or
    `java.io.Serializable`, as defined by the bootstrap class loader
    (<a href="jvms-5.html#jvms-5.3" class="xref"
    title="5.3. Creation and Loading">§5.3</a>);

  - If <span class="type">T</span> is an array type
    <span class="type">TC</span>`[]`, that is, an array of components of
    type <span class="type">TC</span>, then the reference is a value of
    <span class="type">T</span> if one of the following is true:

    <div class="norm">

    - <span class="type">TC</span> and <span class="type">SC</span> are
      the same type;

    - <span class="type">TC</span> is the class type `Object`;

    - <span class="type">TC</span> is a class or interface type,
      <span class="type">SC</span> is a class or interface type, and the
      class or interface named by <span class="type">SC</span> extends
      or implements the class or interface named by
      <span class="type">TC</span>;

    - <span class="type">SC</span> is an array type
      <span class="type">SCC</span>`[]`, and (applying these rules
      recursively) a reference to an array with component type
      <span class="type">SCC</span> is a value of type
      <span class="type">TC</span>.

    </div>

  </div>

</div>

</div>

<div id="jvms-6.5.checkcast.linking" class="section">

<div class="titlepage">

<div>

<div>

#### Linking Exceptions

</div>

</div>

</div>

During resolution of the symbolic reference to the class, array, or
interface type, any of the exceptions documented in
<a href="jvms-5.html#jvms-5.4.3.1" class="xref"
title="5.4.3.1. Class and Interface Resolution">§5.4.3.1</a> can be
thrown.

</div>

<div id="jvms-6.5.checkcast.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exception

</div>

</div>

</div>

Otherwise, if <span class="emphasis">*objectref*</span> is not `null`
and is not a value of the type given by the resolved class, array, or
interface type, the <span class="emphasis">*checkcast*</span>
instruction throws a `ClassCastException`.

</div>

<div id="jvms-6.5.checkcast.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*checkcast*</span> instruction is very
similar to the <span class="emphasis">*instanceof*</span> instruction
(<a href="jvms-6.html#jvms-6.5.instanceof" class="xref"
title="instanceof">§<span
class="emphasis"><em>instanceof</em></span></a>). It differs in its
treatment of `null`, its behavior when its test fails
(<span class="emphasis">*checkcast*</span> throws an exception,
<span class="emphasis">*instanceof*</span> pushes a result code), and
its effect on the operand stack.

</div>

</div>

<div id="jvms-6.5.d2f" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*d2f*</span>

</div>

</div>

</div>

<div id="d5e17797" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Convert `double` to `float`

</div>

<div id="d5e17802" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*d2f*</span>  

</div>

</div>

<div id="d5e17806" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*d2f*</span> = 144 (0x90)

</div>

<div id="d5e17810" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.d2f.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*value*</span> on the top of the operand
stack must be of type `double`. It is popped from the operand stack and
converted to a `float` <span class="emphasis">*result*</span> using the
round to nearest rounding policy
(<a href="jvms-2.html#jvms-2.8" class="xref"
title="2.8. Floating-Point Arithmetic">§2.8</a>). The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

A finite <span class="emphasis">*value*</span> too small to be
represented as a `float` is converted to a zero of the same sign; a
finite <span class="emphasis">*value*</span> too large to be represented
as a `float` is converted to an infinity of the same sign. A `double`
NaN is converted to a `float` NaN.

</div>

<div id="jvms-6.5.d2f.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*d2f*</span> instruction performs a narrowing
primitive conversion (JLS §5.1.3). It may lose information about the
overall magnitude of <span class="emphasis">*value*</span> and may also
lose precision.

</div>

</div>

<div id="jvms-6.5.d2i" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*d2i*</span>

</div>

</div>

</div>

<div id="d5e17841" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Convert `double` to `int`

</div>

<div id="d5e17846" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*d2i*</span>  

</div>

</div>

<div id="d5e17850" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*d2i*</span> = 142 (0x8e)

</div>

<div id="d5e17854" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.d2i.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*value*</span> on the top of the operand
stack must be of type `double`. It is popped from the operand stack and
converted to an `int` <span class="emphasis">*result*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack:

<div class="norm">

- If the <span class="emphasis">*value*</span> is NaN, the result of the
  conversion is an `int` 0.

- Otherwise, if the <span class="emphasis">*value*</span> is not an
  infinity, it is rounded to an integer value
  <span class="type">V</span> using the round toward zero rounding
  policy (<a href="jvms-2.html#jvms-2.8" class="xref"
  title="2.8. Floating-Point Arithmetic">§2.8</a>). If this integer
  value <span class="type">V</span> can be represented as an `int`, then
  the result is the `int` value <span class="type">V</span>.

- Otherwise, either the <span class="emphasis">*value*</span> must be
  too small (a negative value of large magnitude or negative infinity),
  and the result is the smallest representable value of type `int`, or
  the <span class="emphasis">*value*</span> must be too large (a
  positive value of large magnitude or positive infinity), and the
  result is the largest representable value of type `int`.

</div>

</div>

<div id="jvms-6.5.d2i.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*d2i*</span> instruction performs a narrowing
primitive conversion (JLS §5.1.3). It may lose information about the
overall magnitude of <span class="emphasis">*value*</span> and may also
lose precision.

</div>

</div>

<div id="jvms-6.5.d2l" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*d2l*</span>

</div>

</div>

</div>

<div id="d5e17897" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Convert `double` to `long`

</div>

<div id="d5e17902" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*d2l*</span>  

</div>

</div>

<div id="d5e17906" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*d2l*</span> = 143 (0x8f)

</div>

<div id="d5e17910" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.d2l.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*value*</span> on the top of the operand
stack must be of type `double`. It is popped from the operand stack and
converted to a `long`. The <span class="emphasis">*result*</span> is
pushed onto the operand stack:

<div class="norm">

- If the <span class="emphasis">*value*</span> is NaN, the result of the
  conversion is a `long` 0.

- Otherwise, if the <span class="emphasis">*value*</span> is not an
  infinity, it is rounded to an integer value
  <span class="type">V</span> using the round toward zero rounding
  policy (<a href="jvms-2.html#jvms-2.8" class="xref"
  title="2.8. Floating-Point Arithmetic">§2.8</a>). If this integer
  value <span class="type">V</span> can be represented as a `long`, then
  the result is the `long` value <span class="type">V</span>.

- Otherwise, either the <span class="emphasis">*value*</span> must be
  too small (a negative value of large magnitude or negative infinity),
  and the result is the smallest representable value of type `long`, or
  the <span class="emphasis">*value*</span> must be too large (a
  positive value of large magnitude or positive infinity), and the
  result is the largest representable value of type `long`.

</div>

</div>

<div id="jvms-6.5.d2l.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*d2l*</span> instruction performs a narrowing
primitive conversion (JLS §5.1.3). It may lose information about the
overall magnitude of <span class="emphasis">*value*</span> and may also
lose precision.

</div>

</div>

<div id="jvms-6.5.dadd" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*dadd*</span>

</div>

</div>

</div>

<div id="d5e17952" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Add `double`

</div>

<div id="d5e17956" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*dadd*</span>  

</div>

</div>

<div id="d5e17960" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*dadd*</span> = 99 (0x63)

</div>

<div id="d5e17964" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.dadd.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `double`. The
values are popped from the operand stack. The `double`
<span class="emphasis">*result*</span> is
<span class="emphasis">*value1*</span> +
<span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

The result of a <span class="emphasis">*dadd*</span> instruction is
governed by the rules of IEEE 754 arithmetic:

<div class="norm">

- If either <span class="emphasis">*value1*</span> or
  <span class="emphasis">*value2*</span> is NaN, the result is NaN.

- The sum of two infinities of opposite sign is NaN.

- The sum of two infinities of the same sign is the infinity of that
  sign.

- The sum of an infinity and any finite value is equal to the infinity.

- The sum of two zeroes of opposite sign is positive zero.

- The sum of two zeroes of the same sign is the zero of that sign.

- The sum of a zero and a nonzero finite value is equal to the nonzero
  value.

- The sum of two nonzero finite values of the same magnitude and
  opposite sign is positive zero.

- In the remaining cases, where neither operand is an infinity, a zero,
  or NaN and the values have the same sign or have different magnitudes,
  the sum is computed and rounded to the nearest representable value
  using the round to nearest rounding policy
  (<a href="jvms-2.html#jvms-2.8" class="xref"
  title="2.8. Floating-Point Arithmetic">§2.8</a>). If the magnitude is
  too large to represent as a `double`, we say the operation overflows;
  the result is then an infinity of appropriate sign. If the magnitude
  is too small to represent as a `double`, we say the operation
  underflows; the result is then a zero of appropriate sign.

</div>

The Java Virtual Machine requires support of gradual underflow. Despite
the fact that overflow, underflow, or loss of precision may occur,
execution of a <span class="emphasis">*dadd*</span> instruction never
throws a run-time exception.

</div>

</div>

<div id="jvms-6.5.daload" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*daload*</span>

</div>

</div>

</div>

<div id="d5e18014" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Load `double` from array

</div>

<div id="d5e18018" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*daload*</span>  

</div>

</div>

<div id="d5e18022" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*daload*</span> = 49 (0x31)

</div>

<div id="d5e18026" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*arrayref*</span>,
<span class="emphasis">*index*</span> <span class="symbol">→</span>

..., <span class="emphasis">*value*</span>

</div>

<div id="jvms-6.5.daload.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*arrayref*</span> must be of type `reference`
and must refer to an array whose components are of type `double`. The
<span class="emphasis">*index*</span> must be of type `int`. Both
<span class="emphasis">*arrayref*</span> and
<span class="emphasis">*index*</span> are popped from the operand stack.
The `double` <span class="emphasis">*value*</span> in the component of
the array at <span class="emphasis">*index*</span> is retrieved and
pushed onto the operand stack.

</div>

<div id="jvms-6.5.daload.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

If <span class="emphasis">*arrayref*</span> is `null`,
<span class="emphasis">*daload*</span> throws a `NullPointerException`.

Otherwise, if <span class="emphasis">*index*</span> is not within the
bounds of the array referenced by
<span class="emphasis">*arrayref*</span>, the
<span class="emphasis">*daload*</span> instruction throws an
`ArrayIndexOutOfBoundsException`.

</div>

</div>

<div id="jvms-6.5.dastore" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*dastore*</span>

</div>

</div>

</div>

<div id="d5e18062" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Store into `double` array

</div>

<div id="d5e18066" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*dastore*</span>  

</div>

</div>

<div id="d5e18070" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*dastore*</span> = 82 (0x52)

</div>

<div id="d5e18074" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*arrayref*</span>,
<span class="emphasis">*index*</span>,
<span class="emphasis">*value*</span> <span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.dastore.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*arrayref*</span> must be of type `reference`
and must refer to an array whose components are of type `double`. The
<span class="emphasis">*index*</span> must be of type `int`, and value
must be of type `double`. The <span class="emphasis">*arrayref*</span>,
<span class="emphasis">*index*</span>, and
<span class="emphasis">*value*</span> are popped from the operand stack.
The `double` <span class="emphasis">*value*</span> is stored as the
component of the array indexed by <span class="emphasis">*index*</span>.

</div>

<div id="jvms-6.5.dastore.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

If <span class="emphasis">*arrayref*</span> is `null`,
<span class="emphasis">*dastore*</span> throws a `NullPointerException`.

Otherwise, if <span class="emphasis">*index*</span> is not within the
bounds of the array referenced by
<span class="emphasis">*arrayref*</span>, the
<span class="emphasis">*dastore*</span> instruction throws an
`ArrayIndexOutOfBoundsException`.

</div>

</div>

<div id="jvms-6.5.dcmp_op" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*dcmp\<op\>*</span>

</div>

</div>

</div>

<div id="d5e18112" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Compare `double`

</div>

<div id="d5e18116" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*dcmp\<op\>*</span>  

</div>

</div>

<div id="d5e18120" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*dcmpg*</span> = 152 (0x98)

<span class="emphasis">*dcmpl*</span> = 151 (0x97)

</div>

<div id="d5e18126" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.dcmp_op.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `double`. The
values are popped from the operand stack and a floating-point comparison
is performed:

<div class="norm">

- If <span class="emphasis">*value1*</span> is greater than
  <span class="emphasis">*value2*</span>, the `int` value 1 is pushed
  onto the operand stack.

- Otherwise, if <span class="emphasis">*value1*</span> is equal to
  <span class="emphasis">*value2*</span>, the `int` value 0 is pushed
  onto the operand stack.

- Otherwise, if <span class="emphasis">*value1*</span> is less than
  <span class="emphasis">*value2*</span>, the `int` value -1 is pushed
  onto the operand stack.

- Otherwise, at least one of <span class="emphasis">*value1*</span> or
  <span class="emphasis">*value2*</span> is NaN. The
  <span class="emphasis">*dcmpg*</span> instruction pushes the `int`
  value 1 onto the operand stack and the
  <span class="emphasis">*dcmpl*</span> instruction pushes the `int`
  value -1 onto the operand stack.

</div>

Floating-point comparison is performed in accordance with IEEE 754. All
values other than NaN are ordered, with negative infinity less than all
finite values and positive infinity greater than all finite values.
Positive zero and negative zero are considered equal.

</div>

<div id="jvms-6.5.dcmp_op.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*dcmpg*</span> and
<span class="emphasis">*dcmpl*</span> instructions differ only in their
treatment of a comparison involving NaN. NaN is unordered, so any
`double` comparison fails if either or both of its operands are NaN.
With both <span class="emphasis">*dcmpg*</span> and
<span class="emphasis">*dcmpl*</span> available, any `double` comparison
may be compiled to push the same <span class="emphasis">*result*</span>
onto the operand stack whether the comparison fails on non-NaN values or
fails because it encountered a NaN. For more information, see
<a href="jvms-3.html#jvms-3.5" class="xref"
title="3.5. More Control Examples">§3.5</a>.

</div>

</div>

<div id="jvms-6.5.dconst_d" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*dconst\_\<d\>*</span>

</div>

</div>

</div>

<div id="d5e18179" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Push `double`

</div>

<div id="d5e18183" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*dconst\_\<d\>*</span>  

</div>

</div>

<div id="d5e18187" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*dconst_0*</span> = 14 (0xe)

<span class="emphasis">*dconst_1*</span> = 15 (0xf)

</div>

<div id="d5e18193" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

... <span class="symbol">→</span>

..., \<<span class="emphasis">*d*</span>\>

</div>

<div id="jvms-6.5.dconst_d.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Push the `double` constant \<<span class="emphasis">*d*</span>\> (0.0 or
1.0) onto the operand stack.

</div>

</div>

<div id="jvms-6.5.ddiv" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*ddiv*</span>

</div>

</div>

</div>

<div id="d5e18207" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Divide `double`

</div>

<div id="d5e18211" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*ddiv*</span>  

</div>

</div>

<div id="d5e18215" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*ddiv*</span> = 111 (0x6f)

</div>

<div id="d5e18219" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.ddiv.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `double`. The
values are popped from the operand stack. The `double`
<span class="emphasis">*result*</span> is
<span class="emphasis">*value1*</span> /
<span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

The result of a <span class="emphasis">*ddiv*</span> instruction is
governed by the rules of IEEE 754 arithmetic:

<div class="norm">

- If either <span class="emphasis">*value1*</span> or
  <span class="emphasis">*value2*</span> is NaN, the result is NaN.

- If neither <span class="emphasis">*value1*</span> nor
  <span class="emphasis">*value2*</span> is NaN, the sign of the result
  is positive if both values have the same sign, negative if the values
  have different signs.

- Division of an infinity by an infinity results in NaN.

- Division of an infinity by a finite value results in a signed
  infinity, with the sign-producing rule just given.

- Division of a finite value by an infinity results in a signed zero,
  with the sign-producing rule just given.

- Division of a zero by a zero results in NaN; division of zero by any
  other finite value results in a signed zero, with the sign-producing
  rule just given.

- Division of a nonzero finite value by a zero results in a signed
  infinity, with the sign-producing rule just given.

- In the remaining cases, where neither operand is an infinity, a zero,
  or NaN, the quotient is computed and rounded to the nearest `double`
  using the round to nearest rounding policy
  (<a href="jvms-2.html#jvms-2.8" class="xref"
  title="2.8. Floating-Point Arithmetic">§2.8</a>). If the magnitude is
  too large to represent as a `double`, we say the operation overflows;
  the result is then an infinity of appropriate sign. If the magnitude
  is too small to represent as a `double`, we say the operation
  underflows; the result is then a zero of appropriate sign.

</div>

The Java Virtual Machine requires support of gradual underflow. Despite
the fact that overflow, underflow, division by zero, or loss of
precision may occur, execution of a <span class="emphasis">*ddiv*</span>
instruction never throws a run-time exception.

</div>

</div>

<div id="jvms-6.5.dload" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*dload*</span>

</div>

</div>

</div>

<div id="d5e18270" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Load `double` from local variable

</div>

<div id="d5e18274" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*dload*</span>  
<span class="emphasis">*index*</span>  

</div>

</div>

<div id="d5e18279" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*dload*</span> = 24 (0x18)

</div>

<div id="d5e18283" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

... <span class="symbol">→</span>

..., <span class="emphasis">*value*</span>

</div>

<div id="jvms-6.5.dload.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*index*</span> is an unsigned byte. Both
<span class="emphasis">*index*</span> and
<span class="emphasis">*index*</span>+1 must be indices into the local
variable array of the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>).
The local variable at <span class="emphasis">*index*</span> must contain
a `double`. The <span class="emphasis">*value*</span> of the local
variable at <span class="emphasis">*index*</span> is pushed onto the
operand stack.

</div>

<div id="jvms-6.5.dload.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*dload*</span> opcode can be used in
conjunction with the <span class="emphasis">*wide*</span> instruction
(<a href="jvms-6.html#jvms-6.5.wide" class="xref" title="wide">§<span
class="emphasis"><em>wide</em></span></a>) to access a local variable
using a two-byte unsigned index.

</div>

</div>

<div id="jvms-6.5.dload_n" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*dload\_\<n\>*</span>

</div>

</div>

</div>

<div id="d5e18309" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Load `double` from local variable

</div>

<div id="d5e18313" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*dload\_\<n\>*</span>  

</div>

</div>

<div id="d5e18317" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*dload_0*</span> = 38 (0x26)

<span class="emphasis">*dload_1*</span> = 39 (0x27)

<span class="emphasis">*dload_2*</span> = 40 (0x28)

<span class="emphasis">*dload_3*</span> = 41 (0x29)

</div>

<div id="d5e18327" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

... <span class="symbol">→</span>

..., <span class="emphasis">*value*</span>

</div>

<div id="jvms-6.5.dload_n.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both \<<span class="emphasis">*n*</span>\> and
\<<span class="emphasis">*n*</span>\>+1 must be indices into the local
variable array of the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>).
The local variable at \<<span class="emphasis">*n*</span>\> must contain
a `double`. The <span class="emphasis">*value*</span> of the local
variable at \<<span class="emphasis">*n*</span>\> is pushed onto the
operand stack.

</div>

<div id="jvms-6.5.dload_n.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

Each of the <span class="emphasis">*dload\_\<n\>*</span> instructions is
the same as <span class="emphasis">*dload*</span> with an
<span class="emphasis">*index*</span> of
\<<span class="emphasis">*n*</span>\>, except that the operand
\<<span class="emphasis">*n*</span>\> is implicit.

</div>

</div>

<div id="jvms-6.5.dmul" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*dmul*</span>

</div>

</div>

</div>

<div id="d5e18354" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Multiply `double`

</div>

<div id="d5e18358" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*dmul*</span>  

</div>

</div>

<div id="d5e18362" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*dmul*</span> = 107 (0x6b)

</div>

<div id="d5e18366" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.dmul.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `double`. The
values are popped from the operand stack. The `double`
<span class="emphasis">*result*</span> is
<span class="emphasis">*value1*</span> \*
<span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

The result of a <span class="emphasis">*dmul*</span> instruction is
governed by the rules of IEEE 754 arithmetic:

<div class="norm">

- If either <span class="emphasis">*value1*</span> or
  <span class="emphasis">*value2*</span> is NaN, the result is NaN.

- If neither <span class="emphasis">*value1*</span> nor
  <span class="emphasis">*value2*</span> is NaN, the sign of the result
  is positive if both values have the same sign and negative if the
  values have different signs.

- Multiplication of an infinity by a zero results in NaN.

- Multiplication of an infinity by a finite value results in a signed
  infinity, with the sign-producing rule just given.

- In the remaining cases, where neither an infinity nor NaN is involved,
  the product is computed and rounded to the nearest representable value
  using the round to nearest rounding policy
  (<a href="jvms-2.html#jvms-2.8" class="xref"
  title="2.8. Floating-Point Arithmetic">§2.8</a>). If the magnitude is
  too large to represent as a `double`, we say the operation overflows;
  the result is then an infinity of appropriate sign. If the magnitude
  is too small to represent as a `double`, we say the operation
  underflows; the result is then a zero of appropriate sign.

</div>

The Java Virtual Machine requires support of gradual underflow. Despite
the fact that overflow, underflow, or loss of precision may occur,
execution of a <span class="emphasis">*dmul*</span> instruction never
throws a run-time exception.

</div>

</div>

<div id="jvms-6.5.dneg" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*dneg*</span>

</div>

</div>

</div>

<div id="d5e18410" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Negate `double`

</div>

<div id="d5e18414" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*dneg*</span>  

</div>

</div>

<div id="d5e18418" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*dneg*</span> = 119 (0x77)

</div>

<div id="d5e18422" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.dneg.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The value must be of type `double`. It is popped from the operand stack.
The `double` <span class="emphasis">*result*</span> is the arithmetic
negation of <span class="emphasis">*value*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

For `double` values, negation is not the same as subtraction from zero.
If `x` is `+0.0`, then `0.0-x` equals `+0.0`, but `-x` equals `-0.0`.
Unary minus merely inverts the sign of a `double`.

Special cases of interest:

<div class="norm">

- If the operand is NaN, the result is NaN (recall that NaN has no
  sign).

  The Java Virtual Machine has not adopted the stronger requirement from
  the 2019 version of the IEEE 754 Standard that negation inverts the
  sign bit for all inputs, including NaN.

- If the operand is an infinity, the result is the infinity of opposite
  sign.

- If the operand is a zero, the result is the zero of opposite sign.

</div>

</div>

</div>

<div id="jvms-6.5.drem" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*drem*</span>

</div>

</div>

</div>

<div id="d5e18458" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Remainder `double`

</div>

<div id="d5e18462" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*drem*</span>  

</div>

</div>

<div id="d5e18466" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*drem*</span> = 115 (0x73)

</div>

<div id="d5e18470" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.drem.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `double`. The
values are popped from the operand stack. The `double`
<span class="emphasis">*result*</span> is calculated and pushed onto the
operand stack.

The result of a <span class="emphasis">*drem*</span> instruction is not
the same as the result of the remainder operation defined by IEEE 754,
due to the choice of rounding policy in the Java Virtual Machine
(<a href="jvms-2.html#jvms-2.8" class="xref"
title="2.8. Floating-Point Arithmetic">§2.8</a>). The IEEE 754 remainder
operation computes the remainder from a rounding division, not a
truncating division, and so its behavior is
<span class="emphasis">*not*</span> analogous to that of the usual
integer remainder operator. Instead, the Java Virtual Machine defines
<span class="emphasis">*drem*</span> to behave in a manner analogous to
that of the integer remainder instructions
<span class="emphasis">*irem*</span> and
<span class="emphasis">*lrem*</span>, with an implied division using the
round toward zero rounding policy; this may be compared with the C
library function `fmod`.

The result of a <span class="emphasis">*drem*</span> instruction is
governed by the following rules, which match IEEE 754 arithmetic except
for how the implied division is computed:

<div class="norm">

- If either <span class="emphasis">*value1*</span> or
  <span class="emphasis">*value2*</span> is NaN, the result is NaN.

- If neither <span class="emphasis">*value1*</span> nor
  <span class="emphasis">*value2*</span> is NaN, the sign of the result
  equals the sign of the dividend.

- If the dividend is an infinity or the divisor is a zero or both, the
  result is NaN.

- If the dividend is finite and the divisor is an infinity, the result
  equals the dividend.

- If the dividend is a zero and the divisor is finite, the result equals
  the dividend.

- In the remaining cases, where neither operand is an infinity, a zero,
  or NaN, the floating-point remainder
  <span class="emphasis">*result*</span> from a dividend
  <span class="emphasis">*value1*</span> and a divisor
  <span class="emphasis">*value2*</span> is defined by the mathematical
  relation <span class="emphasis">*result*</span> =
  <span class="emphasis">*value1*</span> -
  (<span class="emphasis">*value2*</span> \*
  <span class="emphasis">*q*</span>), where
  <span class="emphasis">*q*</span> is an integer that is negative only
  if <span class="emphasis">*value1*</span> /
  <span class="emphasis">*value2*</span> is negative, and positive only
  if <span class="emphasis">*value1*</span> /
  <span class="emphasis">*value2*</span> is positive, and whose
  magnitude is as large as possible without exceeding the magnitude of
  the true mathematical quotient of
  <span class="emphasis">*value1*</span> and
  <span class="emphasis">*value2*</span>.

</div>

Despite the fact that division by zero may occur, evaluation of a
<span class="emphasis">*drem*</span> instruction never throws a run-time
exception. Overflow, underflow, or loss of precision cannot occur.

</div>

<div id="jvms-6.5.drem.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The IEEE 754 remainder operation may be computed by the library routine
`Math.IEEEremainder` or `StrictMath.IEEEremainder`.

</div>

</div>

<div id="jvms-6.5.dreturn" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*dreturn*</span>

</div>

</div>

</div>

<div id="d5e18537" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Return `double` from method

</div>

<div id="d5e18541" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*dreturn*</span>  

</div>

</div>

<div id="d5e18545" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*dreturn*</span> = 175 (0xaf)

</div>

<div id="d5e18549" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

\[empty\]

</div>

<div id="jvms-6.5.dreturn.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The current method must have return type `double`. The
<span class="emphasis">*value*</span> must be of type `double`. If the
current method is a `synchronized` method, the monitor entered or
reentered on invocation of the method is updated and possibly exited as
if by execution of a <span class="emphasis">*monitorexit*</span>
instruction (<a href="jvms-6.html#jvms-6.5.monitorexit" class="xref"
title="monitorexit">§<span
class="emphasis"><em>monitorexit</em></span></a>) in the current thread.
If no exception is thrown, <span class="emphasis">*value*</span> is
popped from the operand stack of the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>)
and pushed onto the operand stack of the frame of the invoker. Any other
values on the operand stack of the current method are discarded.

The interpreter then returns control to the invoker of the method,
reinstating the frame of the invoker.

</div>

<div id="jvms-6.5.dreturn.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

If the Java Virtual Machine implementation does not enforce the rules on
structured locking described in
<a href="jvms-2.html#jvms-2.11.10" class="xref"
title="2.11.10. Synchronization">§2.11.10</a>, then if the current
method is a `synchronized` method and the current thread is not the
owner of the monitor entered or reentered on invocation of the method,
<span class="emphasis">*dreturn*</span> throws an
`IllegalMonitorStateException`. This can happen, for example, if a
`synchronized` method contains a
<span class="emphasis">*monitorexit*</span> instruction, but no
<span class="emphasis">*monitorenter*</span> instruction, on the object
on which the method is synchronized.

Otherwise, if the Java Virtual Machine implementation enforces the rules
on structured locking described in
<a href="jvms-2.html#jvms-2.11.10" class="xref"
title="2.11.10. Synchronization">§2.11.10</a> and if the first of those
rules is violated during invocation of the current method, then
<span class="emphasis">*dreturn*</span> throws an
`IllegalMonitorStateException`.

</div>

</div>

<div id="jvms-6.5.dstore" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*dstore*</span>

</div>

</div>

</div>

<div id="d5e18584" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Store `double` into local variable

</div>

<div id="d5e18588" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*dstore*</span>  
<span class="emphasis">*index*</span>  

</div>

</div>

<div id="d5e18593" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*dstore*</span> = 57 (0x39)

</div>

<div id="d5e18597" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.dstore.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*index*</span> is an unsigned byte. Both
<span class="emphasis">*index*</span> and
<span class="emphasis">*index*</span>+1 must be indices into the local
variable array of the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>).
The <span class="emphasis">*value*</span> on the top of the operand
stack must be of type `double`. It is popped from the operand stack. The
local variables at <span class="emphasis">*index*</span> and
<span class="emphasis">*index*</span>+1 are set to
<span class="emphasis">*value*</span>.

</div>

<div id="jvms-6.5.dstore.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*dstore*</span> opcode can be used in
conjunction with the <span class="emphasis">*wide*</span> instruction
(<a href="jvms-6.html#jvms-6.5.wide" class="xref" title="wide">§<span
class="emphasis"><em>wide</em></span></a>) to access a local variable
using a two-byte unsigned index.

</div>

</div>

<div id="jvms-6.5.dstore_n" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*dstore\_\<n\>*</span>

</div>

</div>

</div>

<div id="d5e18624" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Store `double` into local variable

</div>

<div id="d5e18628" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*dstore\_\<n\>*</span>  

</div>

</div>

<div id="d5e18632" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*dstore_0*</span> = 71 (0x47)

<span class="emphasis">*dstore_1*</span> = 72 (0x48)

<span class="emphasis">*dstore_2*</span> = 73 (0x49)

<span class="emphasis">*dstore_3*</span> = 74 (0x4a)

</div>

<div id="d5e18642" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.dstore_n.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both \<<span class="emphasis">*n*</span>\> and
\<<span class="emphasis">*n*</span>\>+1 must be indices into the local
variable array of the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>).
The <span class="emphasis">*value*</span> on the top of the operand
stack must be of type `double`. It is popped from the operand stack. The
local variables at \<<span class="emphasis">*n*</span>\> and
\<<span class="emphasis">*n*</span>\>+1 are set to
<span class="emphasis">*value*</span>.

</div>

<div id="jvms-6.5.dstore_n.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

Each of the <span class="emphasis">*dstore\_\<n\>*</span> instructions
is the same as <span class="emphasis">*dstore*</span> with an
<span class="emphasis">*index*</span> of
\<<span class="emphasis">*n*</span>\>, except that the operand
\<<span class="emphasis">*n*</span>\> is implicit.

</div>

</div>

<div id="jvms-6.5.dsub" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*dsub*</span>

</div>

</div>

</div>

<div id="d5e18670" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Subtract `double`

</div>

<div id="d5e18674" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*dsub*</span>  

</div>

</div>

<div id="d5e18678" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*dsub*</span> = 103 (0x67)

</div>

<div id="d5e18682" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.dsub.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `double`. The
values are popped from the operand stack. The `double`
<span class="emphasis">*result*</span> is
<span class="emphasis">*value1*</span> -
<span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

For `double` subtraction, it is always the case that `a-b` produces the
same result as `a+(-b)`. However, for the
<span class="emphasis">*dsub*</span> instruction, subtraction from zero
is not the same as negation, because if `x` is `+0.0`, then `0.0-x`
equals `+0.0`, but `-x` equals `-0.0`.

The Java Virtual Machine requires support of gradual underflow. Despite
the fact that overflow, underflow, or loss of precision may occur,
execution of a <span class="emphasis">*dsub*</span> instruction never
throws a run-time exception.

</div>

</div>

<div id="jvms-6.5.dup" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*dup*</span>

</div>

</div>

</div>

<div id="d5e18717" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Duplicate the top operand stack value

</div>

<div id="d5e18720" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*dup*</span>  

</div>

</div>

<div id="d5e18724" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*dup*</span> = 89 (0x59)

</div>

<div id="d5e18728" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

..., <span class="emphasis">*value*</span>,
<span class="emphasis">*value*</span>

</div>

<div id="jvms-6.5.dup.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Duplicate the top value on the operand stack and push the duplicated
value onto the operand stack.

The <span class="emphasis">*dup*</span> instruction must not be used
unless <span class="emphasis">*value*</span> is a value of a category 1
computational type (<a href="jvms-2.html#jvms-2.11.1" class="xref"
title="2.11.1. Types and the Java Virtual Machine">§2.11.1</a>).

</div>

</div>

<div id="jvms-6.5.dup_x1" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*dup_x1*</span>

</div>

</div>

</div>

<div id="d5e18746" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Duplicate the top operand stack value and insert two values down

</div>

<div id="d5e18749" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*dup_x1*</span>  

</div>

</div>

<div id="d5e18753" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*dup_x1*</span> = 90 (0x5a)

</div>

<div id="d5e18757" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value2*</span>,
<span class="emphasis">*value1*</span> <span class="symbol">→</span>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span>,
<span class="emphasis">*value1*</span>

</div>

<div id="jvms-6.5.dup_x1.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Duplicate the top value on the operand stack and insert the duplicated
value two values down in the operand stack.

The <span class="emphasis">*dup_x1*</span> instruction must not be used
unless both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> are values of a category 1
computational type (<a href="jvms-2.html#jvms-2.11.1" class="xref"
title="2.11.1. Types and the Java Virtual Machine">§2.11.1</a>).

</div>

</div>

<div id="jvms-6.5.dup_x2" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*dup_x2*</span>

</div>

</div>

</div>

<div id="d5e18778" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Duplicate the top operand stack value and insert two or three values
down

</div>

<div id="d5e18781" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*dup_x2*</span>  

</div>

</div>

<div id="d5e18785" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*dup_x2*</span> = 91 (0x5b)

</div>

<div id="jvms-6.5.dup_x2.stack" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

Form 1:

..., <span class="emphasis">*value3*</span>,
<span class="emphasis">*value2*</span>,
<span class="emphasis">*value1*</span> <span class="symbol">→</span>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value3*</span>,
<span class="emphasis">*value2*</span>,
<span class="emphasis">*value1*</span>

where <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span>, and
<span class="emphasis">*value3*</span> are all values of a category 1
computational type (<a href="jvms-2.html#jvms-2.11.1" class="xref"
title="2.11.1. Types and the Java Virtual Machine">§2.11.1</a>).

Form 2:

..., <span class="emphasis">*value2*</span>,
<span class="emphasis">*value1*</span> <span class="symbol">→</span>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span>,
<span class="emphasis">*value1*</span>

where <span class="emphasis">*value1*</span> is a value of a category 1
computational type and <span class="emphasis">*value2*</span> is a value
of a category 2 computational type
(<a href="jvms-2.html#jvms-2.11.1" class="xref"
title="2.11.1. Types and the Java Virtual Machine">§2.11.1</a>).

</div>

<div id="jvms-6.5.dup_x2.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Duplicate the top value on the operand stack and insert the duplicated
value two or three values down in the operand stack.

</div>

</div>

<div id="jvms-6.5.dup2" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*dup2*</span>

</div>

</div>

</div>

<div id="d5e18826" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Duplicate the top one or two operand stack values

</div>

<div id="d5e18829" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*dup2*</span>  

</div>

</div>

<div id="d5e18833" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*dup2*</span> = 92 (0x5c)

</div>

<div id="jvms-6.5.dup2.stack" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

Form 1:

..., <span class="emphasis">*value2*</span>,
<span class="emphasis">*value1*</span> <span class="symbol">→</span>

..., <span class="emphasis">*value2*</span>,
<span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span>,
<span class="emphasis">*value1*</span>

where both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> are values of a category 1
computational type (<a href="jvms-2.html#jvms-2.11.1" class="xref"
title="2.11.1. Types and the Java Virtual Machine">§2.11.1</a>).

Form 2:

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

..., <span class="emphasis">*value*</span>,
<span class="emphasis">*value*</span>

where <span class="emphasis">*value*</span> is a value of a category 2
computational type (<a href="jvms-2.html#jvms-2.11.1" class="xref"
title="2.11.1. Types and the Java Virtual Machine">§2.11.1</a>).

</div>

<div id="jvms-6.5.dup2.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Duplicate the top one or two values on the operand stack and push the
duplicated value or values back onto the operand stack in the original
order.

</div>

</div>

<div id="jvms-6.5.dup2_x1" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*dup2_x1*</span>

</div>

</div>

</div>

<div id="d5e18869" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Duplicate the top one or two operand stack values and insert two or
three values down

</div>

<div id="d5e18872" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*dup2_x1*</span>  

</div>

</div>

<div id="d5e18876" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*dup2_x1*</span> = 93 (0x5d)

</div>

<div id="jvms-6.5.dup2_x1.stack" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

Form 1:

..., <span class="emphasis">*value3*</span>,
<span class="emphasis">*value2*</span>,
<span class="emphasis">*value1*</span> <span class="symbol">→</span>

..., <span class="emphasis">*value2*</span>,
<span class="emphasis">*value1*</span>,
<span class="emphasis">*value3*</span>,
<span class="emphasis">*value2*</span>,
<span class="emphasis">*value1*</span>

where <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span>, and
<span class="emphasis">*value3*</span> are all values of a category 1
computational type (<a href="jvms-2.html#jvms-2.11.1" class="xref"
title="2.11.1. Types and the Java Virtual Machine">§2.11.1</a>).

Form 2:

..., <span class="emphasis">*value2*</span>,
<span class="emphasis">*value1*</span> <span class="symbol">→</span>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span>,
<span class="emphasis">*value1*</span>

where <span class="emphasis">*value1*</span> is a value of a category 2
computational type and <span class="emphasis">*value2*</span> is a value
of a category 1 computational type
(<a href="jvms-2.html#jvms-2.11.1" class="xref"
title="2.11.1. Types and the Java Virtual Machine">§2.11.1</a>).

</div>

<div id="jvms-6.5.dup2_x1.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Duplicate the top one or two values on the operand stack and insert the
duplicated values, in the original order, one value beneath the original
value or values in the operand stack.

</div>

</div>

<div id="jvms-6.5.dup2_x2" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*dup2_x2*</span>

</div>

</div>

</div>

<div id="d5e18918" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Duplicate the top one or two operand stack values and insert two, three,
or four values down

</div>

<div id="d5e18921" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*dup2_x2*</span>  

</div>

</div>

<div id="d5e18925" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*dup2_x2*</span> = 94 (0x5e)

</div>

<div id="jvms-6.5.dup2_x2.stack" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

Form 1:

..., <span class="emphasis">*value4*</span>,
<span class="emphasis">*value3*</span>,
<span class="emphasis">*value2*</span>,
<span class="emphasis">*value1*</span> <span class="symbol">→</span>

..., <span class="emphasis">*value2*</span>,
<span class="emphasis">*value1*</span>,
<span class="emphasis">*value4*</span>,
<span class="emphasis">*value3*</span>,
<span class="emphasis">*value2*</span>,
<span class="emphasis">*value1*</span>

where <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span>,
<span class="emphasis">*value3*</span>, and
<span class="emphasis">*value4*</span> are all values of a category 1
computational type (<a href="jvms-2.html#jvms-2.11.1" class="xref"
title="2.11.1. Types and the Java Virtual Machine">§2.11.1</a>).

Form 2:

..., <span class="emphasis">*value3*</span>,
<span class="emphasis">*value2*</span>,
<span class="emphasis">*value1*</span> <span class="symbol">→</span>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value3*</span>,
<span class="emphasis">*value2*</span>,
<span class="emphasis">*value1*</span>

where <span class="emphasis">*value1*</span> is a value of a category 2
computational type and <span class="emphasis">*value2*</span> and
<span class="emphasis">*value3*</span> are both values of a category 1
computational type (<a href="jvms-2.html#jvms-2.11.1" class="xref"
title="2.11.1. Types and the Java Virtual Machine">§2.11.1</a>).

Form 3:

..., <span class="emphasis">*value3*</span>,
<span class="emphasis">*value2*</span>,
<span class="emphasis">*value1*</span> <span class="symbol">→</span>

..., <span class="emphasis">*value2*</span>,
<span class="emphasis">*value1*</span>,
<span class="emphasis">*value3*</span>,
<span class="emphasis">*value2*</span>,
<span class="emphasis">*value1*</span>

where <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> are both values of a category 1
computational type and <span class="emphasis">*value3*</span> is a value
of a category 2 computational type
(<a href="jvms-2.html#jvms-2.11.1" class="xref"
title="2.11.1. Types and the Java Virtual Machine">§2.11.1</a>).

Form 4:

..., <span class="emphasis">*value2*</span>,
<span class="emphasis">*value1*</span> <span class="symbol">→</span>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span>,
<span class="emphasis">*value1*</span>

where <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> are both values of a category 2
computational type (<a href="jvms-2.html#jvms-2.11.1" class="xref"
title="2.11.1. Types and the Java Virtual Machine">§2.11.1</a>).

</div>

<div id="jvms-6.5.dup2_x2.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Duplicate the top one or two values on the operand stack and insert the
duplicated values, in the original order, into the operand stack.

</div>

</div>

<div id="jvms-6.5.f2d" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*f2d*</span>

</div>

</div>

</div>

<div id="d5e19003" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Convert `float` to `double`

</div>

<div id="d5e19008" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*f2d*</span>  

</div>

</div>

<div id="d5e19012" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*f2d*</span> = 141 (0x8d)

</div>

<div id="d5e19016" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.f2d.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*value*</span> on the top of the operand
stack must be of type `float`. It is popped from the operand stack and
converted to a `double` <span class="emphasis">*result*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

</div>

<div id="jvms-6.5.f2d.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*f2d*</span> instruction performs a widening
primitive conversion (JLS §5.1.2).

</div>

</div>

<div id="jvms-6.5.f2i" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*f2i*</span>

</div>

</div>

</div>

<div id="d5e19038" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Convert `float` to `int`

</div>

<div id="d5e19043" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*f2i*</span>  

</div>

</div>

<div id="d5e19047" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*f2i*</span> = 139 (0x8b)

</div>

<div id="d5e19051" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.f2i.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*value*</span> on the top of the operand
stack must be of type `float`. It is popped from the operand stack and
converted to an `int` <span class="emphasis">*result*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack:

<div class="norm">

- If the <span class="emphasis">*value*</span> is NaN, the
  <span class="emphasis">*result*</span> of the conversion is an `int`
  0.

- Otherwise, if the <span class="emphasis">*value*</span> is not an
  infinity, it is rounded to an integer value
  <span class="type">V</span> using the round toward zero rounding
  policy (<a href="jvms-2.html#jvms-2.8" class="xref"
  title="2.8. Floating-Point Arithmetic">§2.8</a>). If this integer
  value <span class="type">V</span> can be represented as an `int`, then
  the <span class="emphasis">*result*</span> is the `int` value
  <span class="type">V</span>.

- Otherwise, either the <span class="emphasis">*value*</span> must be
  too small (a negative value of large magnitude or negative infinity),
  and the <span class="emphasis">*result*</span> is the smallest
  representable value of type `int`, or the
  <span class="emphasis">*value*</span> must be too large (a positive
  value of large magnitude or positive infinity), and the
  <span class="emphasis">*result*</span> is the largest representable
  value of type `int`.

</div>

</div>

<div id="jvms-6.5.f2i.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*f2i*</span> instruction performs a narrowing
primitive conversion (JLS §5.1.3). It may lose information about the
overall magnitude of <span class="emphasis">*value*</span> and may also
lose precision.

</div>

</div>

<div id="jvms-6.5.f2l" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*f2l*</span>

</div>

</div>

</div>

<div id="d5e19098" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Convert `float` to `long`

</div>

<div id="d5e19103" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*f2l*</span>  

</div>

</div>

<div id="d5e19107" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*f2l*</span> = 140 (0x8c)

</div>

<div id="d5e19111" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.f2l.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*value*</span> on the top of the operand
stack must be of type `float`. It is popped from the operand stack and
converted to a `long` <span class="emphasis">*result*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack:

<div class="norm">

- If the <span class="emphasis">*value*</span> is NaN, the result of the
  conversion is a `long` 0.

- Otherwise, if the <span class="emphasis">*value*</span> is not an
  infinity, it is rounded to an integer value
  <span class="type">V</span> using the round toward zero rounding
  policy (<a href="jvms-2.html#jvms-2.8" class="xref"
  title="2.8. Floating-Point Arithmetic">§2.8</a>). If this integer
  value <span class="type">V</span> can be represented as a `long`, then
  the <span class="emphasis">*result*</span> is the `long` value
  <span class="type">V</span>.

- Otherwise, either the <span class="emphasis">*value*</span> must be
  too small (a negative value of large magnitude or negative infinity),
  and the <span class="emphasis">*result*</span> is the smallest
  representable value of type `long`, or the
  <span class="emphasis">*value*</span> must be too large (a positive
  value of large magnitude or positive infinity), and the
  <span class="emphasis">*result*</span> is the largest representable
  value of type `long`.

</div>

</div>

<div id="jvms-6.5.f2l.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*f2l*</span> instruction performs a narrowing
primitive conversion (JLS §5.1.3). It may lose information about the
overall magnitude of <span class="emphasis">*value*</span> and may also
lose precision.

</div>

</div>

<div id="jvms-6.5.fadd" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*fadd*</span>

</div>

</div>

</div>

<div id="d5e19157" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Add `float`

</div>

<div id="d5e19161" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*fadd*</span>  

</div>

</div>

<div id="d5e19165" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*fadd*</span> = 98 (0x62)

</div>

<div id="d5e19169" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.fadd.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `float`. The
values are popped from the operand stack. The `float`
<span class="emphasis">*result*</span> is
<span class="emphasis">*value1*</span> +
<span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

The result of an <span class="emphasis">*fadd*</span> instruction is
governed by the rules of IEEE 754 arithmetic:

<div class="norm">

- If either <span class="emphasis">*value1*</span> or
  <span class="emphasis">*value2*</span> is NaN, the result is NaN.

- The sum of two infinities of opposite sign is NaN.

- The sum of two infinities of the same sign is the infinity of that
  sign.

- The sum of an infinity and any finite value is equal to the infinity.

- The sum of two zeroes of opposite sign is positive zero.

- The sum of two zeroes of the same sign is the zero of that sign.

- The sum of a zero and a nonzero finite value is equal to the nonzero
  value.

- The sum of two nonzero finite values of the same magnitude and
  opposite sign is positive zero.

- In the remaining cases, where neither operand is an infinity, a zero,
  or NaN and the values have the same sign or have different magnitudes,
  the sum is computed and rounded to the nearest representable value
  using the round to nearest rounding policy
  (<a href="jvms-2.html#jvms-2.8" class="xref"
  title="2.8. Floating-Point Arithmetic">§2.8</a>). If the magnitude is
  too large to represent as a `float`, we say the operation overflows;
  the result is then an infinity of appropriate sign. If the magnitude
  is too small to represent as a `float`, we say the operation
  underflows; the result is then a zero of appropriate sign.

</div>

The Java Virtual Machine requires support of gradual underflow. Despite
the fact that overflow, underflow, or loss of precision may occur,
execution of an <span class="emphasis">*fadd*</span> instruction never
throws a run-time exception.

</div>

</div>

<div id="jvms-6.5.faload" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*faload*</span>

</div>

</div>

</div>

<div id="d5e19219" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Load `float` from array

</div>

<div id="d5e19223" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*faload*</span>  

</div>

</div>

<div id="d5e19227" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*faload*</span> = 48 (0x30)

</div>

<div id="d5e19231" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*arrayref*</span>,
<span class="emphasis">*index*</span> <span class="symbol">→</span>

..., <span class="emphasis">*value*</span>

</div>

<div id="jvms-6.5.faload.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*arrayref*</span> must be of type `reference`
and must refer to an array whose components are of type `float`. The
<span class="emphasis">*index*</span> must be of type `int`. Both
<span class="emphasis">*arrayref*</span> and
<span class="emphasis">*index*</span> are popped from the operand stack.
The `float` value in the component of the array at
<span class="emphasis">*index*</span> is retrieved and pushed onto the
operand stack.

</div>

<div id="jvms-6.5.faload.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

If <span class="emphasis">*arrayref*</span> is `null`,
<span class="emphasis">*faload*</span> throws a `NullPointerException`.

Otherwise, if <span class="emphasis">*index*</span> is not within the
bounds of the array referenced by
<span class="emphasis">*arrayref*</span>, the
<span class="emphasis">*faload*</span> instruction throws an
`ArrayIndexOutOfBoundsException`.

</div>

</div>

<div id="jvms-6.5.fastore" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*fastore*</span>

</div>

</div>

</div>

<div id="d5e19266" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Store into `float` array

</div>

<div id="d5e19270" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*fastore*</span>  

</div>

</div>

<div id="d5e19274" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*fastore*</span> = 81 (0x51)

</div>

<div id="d5e19278" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*arrayref*</span>,
<span class="emphasis">*index*</span>,
<span class="emphasis">*value*</span> <span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.fastore.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*arrayref*</span> must be of type `reference`
and must refer to an array whose components are of type `float`. The
<span class="emphasis">*index*</span> must be of type `int`, and the
<span class="emphasis">*value*</span> must be of type `float`. The
<span class="emphasis">*arrayref*</span>,
<span class="emphasis">*index*</span>, and
<span class="emphasis">*value*</span> are popped from the operand stack.
The `float` <span class="emphasis">*value*</span> is stored as the
component of the array indexed by <span class="emphasis">*index*</span>.

</div>

<div id="jvms-6.5.fastore.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

If <span class="emphasis">*arrayref*</span> is `null`,
<span class="emphasis">*fastore*</span> throws a `NullPointerException`.

Otherwise, if <span class="emphasis">*index*</span> is not within the
bounds of the array referenced by
<span class="emphasis">*arrayref*</span>, the
<span class="emphasis">*fastore*</span> instruction throws an
`ArrayIndexOutOfBoundsException`.

</div>

</div>

<div id="jvms-6.5.fcmp_op" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*fcmp\<op\>*</span>

</div>

</div>

</div>

<div id="d5e19317" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Compare `float`

</div>

<div id="d5e19321" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*fcmp\<op\>*</span>  

</div>

</div>

<div id="d5e19325" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*fcmpg*</span> = 150 (0x96)

<span class="emphasis">*fcmpl*</span> = 149 (0x95)

</div>

<div id="d5e19331" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.fcmp_op.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `float`. The
values are popped from the operand stack and a floating-point comparison
is performed:

<div class="norm">

- If <span class="emphasis">*value1*</span> is greater than
  <span class="emphasis">*value2*</span>, the `int` value 1 is pushed
  onto the operand stack.

- Otherwise, if <span class="emphasis">*value1*</span> is equal to
  <span class="emphasis">*value2*</span>, the `int` value 0 is pushed
  onto the operand stack.

- Otherwise, if <span class="emphasis">*value1*</span> is less than
  <span class="emphasis">*value2*</span>, the `int` value -1 is pushed
  onto the operand stack.

- Otherwise, at least one of <span class="emphasis">*value1*</span> or
  <span class="emphasis">*value2*</span> is NaN. The
  <span class="emphasis">*fcmpg*</span> instruction pushes the `int`
  value 1 onto the operand stack and the
  <span class="emphasis">*fcmpl*</span> instruction pushes the `int`
  value -1 onto the operand stack.

</div>

Floating-point comparison is performed in accordance with IEEE 754. All
values other than NaN are ordered, with negative infinity less than all
finite values and positive infinity greater than all finite values.
Positive zero and negative zero are considered equal.

</div>

<div id="jvms-6.5.fcmp_op.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*fcmpg*</span> and
<span class="emphasis">*fcmpl*</span> instructions differ only in their
treatment of a comparison involving NaN. NaN is unordered, so any
`float` comparison fails if either or both of its operands are NaN. With
both <span class="emphasis">*fcmpg*</span> and
<span class="emphasis">*fcmpl*</span> available, any `float` comparison
may be compiled to push the same <span class="emphasis">*result*</span>
onto the operand stack whether the comparison fails on non-NaN values or
fails because it encountered a NaN. For more information, see
<a href="jvms-3.html#jvms-3.5" class="xref"
title="3.5. More Control Examples">§3.5</a>.

</div>

</div>

<div id="jvms-6.5.fconst_f" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*fconst\_\<f\>*</span>

</div>

</div>

</div>

<div id="d5e19384" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Push `float`

</div>

<div id="d5e19388" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*fconst\_\<f\>*</span>  

</div>

</div>

<div id="d5e19392" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*fconst_0*</span> = 11 (0xb)

<span class="emphasis">*fconst_1*</span> = 12 (0xc)

<span class="emphasis">*fconst_2*</span> = 13 (0xd)

</div>

<div id="d5e19400" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

... <span class="symbol">→</span>

..., \<<span class="emphasis">*f*</span>\>

</div>

<div id="jvms-6.5.fconst_f.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Push the `float` constant \<<span class="emphasis">*f*</span>\> (0.0,
1.0, or 2.0) onto the operand stack.

</div>

</div>

<div id="jvms-6.5.fdiv" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*fdiv*</span>

</div>

</div>

</div>

<div id="d5e19414" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Divide `float`

</div>

<div id="d5e19418" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*fdiv*</span>  

</div>

</div>

<div id="d5e19422" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*fdiv*</span> = 110 (0x6e)

</div>

<div id="d5e19426" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.fdiv.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `float`. The
values are popped from the operand stack. The `float`
<span class="emphasis">*result*</span> is
<span class="emphasis">*value1*</span> /
<span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

The result of an <span class="emphasis">*fdiv*</span> instruction is
governed by the rules of IEEE 754 arithmetic:

<div class="norm">

- If either <span class="emphasis">*value1*</span> or
  <span class="emphasis">*value2*</span> is NaN, the result is NaN.

- If neither <span class="emphasis">*value1*</span> nor
  <span class="emphasis">*value2*</span> is NaN, the sign of the result
  is positive if both values have the same sign, negative if the values
  have different signs.

- Division of an infinity by an infinity results in NaN.

- Division of an infinity by a finite value results in a signed
  infinity, with the sign-producing rule just given.

- Division of a finite value by an infinity results in a signed zero,
  with the sign-producing rule just given.

- Division of a zero by a zero results in NaN; division of zero by any
  other finite value results in a signed zero, with the sign-producing
  rule just given.

- Division of a nonzero finite value by a zero results in a signed
  infinity, with the sign-producing rule just given.

- In the remaining cases, where neither operand is an infinity, a zero,
  or NaN, the quotient is computed and rounded to the nearest `float`
  using the round to nearest rounding policy
  (<a href="jvms-2.html#jvms-2.8" class="xref"
  title="2.8. Floating-Point Arithmetic">§2.8</a>). If the magnitude is
  too large to represent as a `float`, we say the operation overflows;
  the result is then an infinity of appropriate sign. If the magnitude
  is too small to represent as a `float`, we say the operation
  underflows; the result is then a zero of appropriate sign.

</div>

The Java Virtual Machine requires support of gradual underflow. Despite
the fact that overflow, underflow, division by zero, or loss of
precision may occur, execution of an
<span class="emphasis">*fdiv*</span> instruction never throws a run-time
exception.

</div>

</div>

<div id="jvms-6.5.fload" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*fload*</span>

</div>

</div>

</div>

<div id="d5e19477" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Load `float` from local variable

</div>

<div id="d5e19481" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*fload*</span>  
<span class="emphasis">*index*</span>  

</div>

</div>

<div id="d5e19486" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*fload*</span> = 23 (0x17)

</div>

<div id="d5e19490" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

... <span class="symbol">→</span>

..., <span class="emphasis">*value*</span>

</div>

<div id="jvms-6.5.fload.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*index*</span> is an unsigned byte that must
be an index into the local variable array of the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>).
The local variable at <span class="emphasis">*index*</span> must contain
a `float`. The <span class="emphasis">*value*</span> of the local
variable at <span class="emphasis">*index*</span> is pushed onto the
operand stack.

</div>

<div id="jvms-6.5.fload.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*fload*</span> opcode can be used in
conjunction with the <span class="emphasis">*wide*</span> instruction
(<a href="jvms-6.html#jvms-6.5.wide" class="xref" title="wide">§<span
class="emphasis"><em>wide</em></span></a>) to access a local variable
using a two-byte unsigned index.

</div>

</div>

<div id="jvms-6.5.fload_n" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*fload\_\<n\>*</span>

</div>

</div>

</div>

<div id="d5e19514" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Load `float` from local variable

</div>

<div id="d5e19518" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*fload\_\<n\>*</span>  

</div>

</div>

<div id="d5e19522" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*fload_0*</span> = 34 (0x22)

<span class="emphasis">*fload_1*</span> = 35 (0x23)

<span class="emphasis">*fload_2*</span> = 36 (0x24)

<span class="emphasis">*fload_3*</span> = 37 (0x25)

</div>

<div id="d5e19532" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

... <span class="symbol">→</span>

..., <span class="emphasis">*value*</span>

</div>

<div id="jvms-6.5.fload_n.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The \<<span class="emphasis">*n*</span>\> must be an index into the
local variable array of the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>).
The local variable at \<<span class="emphasis">*n*</span>\> must contain
a `float`. The <span class="emphasis">*value*</span> of the local
variable at \<<span class="emphasis">*n*</span>\> is pushed onto the
operand stack.

</div>

<div id="jvms-6.5.fload_n.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

Each of the <span class="emphasis">*fload\_\<n\>*</span> instructions is
the same as <span class="emphasis">*fload*</span> with an
<span class="emphasis">*index*</span> of
\<<span class="emphasis">*n*</span>\>, except that the operand
\<<span class="emphasis">*n*</span>\> is implicit.

</div>

</div>

<div id="jvms-6.5.fmul" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*fmul*</span>

</div>

</div>

</div>

<div id="d5e19558" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Multiply `float`

</div>

<div id="d5e19562" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*fmul*</span>  

</div>

</div>

<div id="d5e19566" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*fmul*</span> = 106 (0x6a)

</div>

<div id="d5e19570" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.fmul.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `float`. The
values are popped from the operand stack. The `float`
<span class="emphasis">*result*</span> is
<span class="emphasis">*value1*</span> \*
<span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

The result of an <span class="emphasis">*fmul*</span> instruction is
governed by the rules of IEEE 754 arithmetic:

<div class="norm">

- If either <span class="emphasis">*value1*</span> or
  <span class="emphasis">*value2*</span> is NaN, the result is NaN.

- If neither <span class="emphasis">*value1*</span> nor
  <span class="emphasis">*value2*</span> is NaN, the sign of the result
  is positive if both values have the same sign, and negative if the
  values have different signs.

- Multiplication of an infinity by a zero results in NaN.

- Multiplication of an infinity by a finite value results in a signed
  infinity, with the sign-producing rule just given.

- In the remaining cases, where neither an infinity nor NaN is involved,
  the product is computed and rounded to the nearest representable value
  using the round to nearest rounding policy
  (<a href="jvms-2.html#jvms-2.8" class="xref"
  title="2.8. Floating-Point Arithmetic">§2.8</a>). If the magnitude is
  too large to represent as a `float`, we say the operation overflows;
  the result is then an infinity of appropriate sign. If the magnitude
  is too small to represent as a `float`, we say the operation
  underflows; the result is then a zero of appropriate sign.

</div>

The Java Virtual Machine requires support of gradual underflow. Despite
the fact that overflow, underflow, or loss of precision may occur,
execution of an <span class="emphasis">*fmul*</span> instruction never
throws a run-time exception.

</div>

</div>

<div id="jvms-6.5.fneg" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*fneg*</span>

</div>

</div>

</div>

<div id="d5e19614" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Negate `float`

</div>

<div id="d5e19618" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*fneg*</span>  

</div>

</div>

<div id="d5e19622" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*fneg*</span> = 118 (0x76)

</div>

<div id="d5e19626" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.fneg.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*value*</span> must be of type `float`. It is
popped from the operand stack. The `float`
<span class="emphasis">*result*</span> is the arithmetic negation of
<span class="emphasis">*value*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

For `float` values, negation is not the same as subtraction from zero.
If `x` is `+0.0`, then `0.0-x` equals `+0.0`, but `-x` equals `-0.0`.
Unary minus merely inverts the sign of a `float`.

Special cases of interest:

<div class="norm">

- If the operand is NaN, the result is NaN (recall that NaN has no
  sign).

  The Java Virtual Machine has not adopted the stronger requirement from
  the 2019 version of the IEEE 754 Standard that negation inverts the
  sign bit for all inputs, including NaN.

- If the operand is an infinity, the result is the infinity of opposite
  sign.

- If the operand is a zero, the result is the zero of opposite sign.

</div>

</div>

</div>

<div id="jvms-6.5.frem" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*frem*</span>

</div>

</div>

</div>

<div id="d5e19663" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Remainder `float`

</div>

<div id="d5e19667" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*frem*</span>  

</div>

</div>

<div id="d5e19671" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*frem*</span> = 114 (0x72)

</div>

<div id="d5e19675" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.frem.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `float`. The
values are popped from the operand stack. The `float`
<span class="emphasis">*result*</span> is calculated and pushed onto the
operand stack.

The result of an <span class="emphasis">*frem*</span> instruction is not
the same as the result of the remainder operation defined by IEEE 754,
due to the choice of rounding policy in the Java Virtual Machine
(<a href="jvms-2.html#jvms-2.8" class="xref"
title="2.8. Floating-Point Arithmetic">§2.8</a>). The IEEE 754 remainder
operation computes the remainder from a rounding division, not a
truncating division, and so its behavior is
<span class="emphasis">*not*</span> analogous to that of the usual
integer remainder operator. Instead, the Java Virtual Machine defines
<span class="emphasis">*frem*</span> to behave in a manner analogous to
that of the integer remainder instructions
<span class="emphasis">*irem*</span> and
<span class="emphasis">*lrem*</span>, with an implied division using the
round toward zero rounding policy; this may be compared with the C
library function `fmod`.

The result of an <span class="emphasis">*frem*</span> instruction is
governed by the following rules, which match IEEE 754 arithmetic except
for how the implied division is computed:

<div class="norm">

- If either <span class="emphasis">*value1*</span> or
  <span class="emphasis">*value2*</span> is NaN, the result is NaN.

- If neither <span class="emphasis">*value1*</span> nor
  <span class="emphasis">*value2*</span> is NaN, the sign of the result
  equals the sign of the dividend.

- If the dividend is an infinity or the divisor is a zero or both, the
  result is NaN.

- If the dividend is finite and the divisor is an infinity, the result
  equals the dividend.

- If the dividend is a zero and the divisor is finite, the result equals
  the dividend.

- In the remaining cases, where neither operand is an infinity, a zero,
  or NaN, the floating-point remainder
  <span class="emphasis">*result*</span> from a dividend
  <span class="emphasis">*value1*</span> and a divisor
  <span class="emphasis">*value2*</span> is defined by the mathematical
  relation <span class="emphasis">*result*</span> =
  <span class="emphasis">*value1*</span> -
  (<span class="emphasis">*value2*</span> \*
  <span class="emphasis">*q*</span>), where
  <span class="emphasis">*q*</span> is an integer that is negative only
  if <span class="emphasis">*value1*</span> /
  <span class="emphasis">*value2*</span> is negative, and positive only
  if <span class="emphasis">*value1*</span> /
  <span class="emphasis">*value2*</span> is positive, and whose
  magnitude is as large as possible without exceeding the magnitude of
  the true mathematical quotient of
  <span class="emphasis">*value1*</span> and
  <span class="emphasis">*value2*</span>.

</div>

Despite the fact that division by zero may occur, evaluation of an
<span class="emphasis">*frem*</span> instruction never throws a run-time
exception. Overflow, underflow, or loss of precision cannot occur.

</div>

<div id="jvms-6.5.frem.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The IEEE 754 remainder operation may be computed by the library routine
`Math.IEEEremainder` or `StrictMath.IEEEremainder`.

</div>

</div>

<div id="jvms-6.5.freturn" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*freturn*</span>

</div>

</div>

</div>

<div id="d5e19742" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Return `float` from method

</div>

<div id="d5e19746" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*freturn*</span>  

</div>

</div>

<div id="d5e19750" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*freturn*</span> = 174 (0xae)

</div>

<div id="d5e19754" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

\[empty\]

</div>

<div id="jvms-6.5.freturn.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The current method must have return type `float`. The
<span class="emphasis">*value*</span> must be of type `float`. If the
current method is a `synchronized` method, the monitor entered or
reentered on invocation of the method is updated and possibly exited as
if by execution of a <span class="emphasis">*monitorexit*</span>
instruction (<a href="jvms-6.html#jvms-6.5.monitorexit" class="xref"
title="monitorexit">§<span
class="emphasis"><em>monitorexit</em></span></a>) in the current thread.
If no exception is thrown, <span class="emphasis">*value*</span> is
popped from the operand stack of the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>)
and pushed onto the operand stack of the frame of the invoker. Any other
values on the operand stack of the current method are discarded.

The interpreter then returns control to the invoker of the method,
reinstating the frame of the invoker.

</div>

<div id="jvms-6.5.freturn.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

If the Java Virtual Machine implementation does not enforce the rules on
structured locking described in
<a href="jvms-2.html#jvms-2.11.10" class="xref"
title="2.11.10. Synchronization">§2.11.10</a>, then if the current
method is a `synchronized` method and the current thread is not the
owner of the monitor entered or reentered on invocation of the method,
<span class="emphasis">*freturn*</span> throws an
`IllegalMonitorStateException`. This can happen, for example, if a
`synchronized` method contains a
<span class="emphasis">*monitorexit*</span> instruction, but no
<span class="emphasis">*monitorenter*</span> instruction, on the object
on which the method is synchronized.

Otherwise, if the Java Virtual Machine implementation enforces the rules
on structured locking described in
<a href="jvms-2.html#jvms-2.11.10" class="xref"
title="2.11.10. Synchronization">§2.11.10</a> and if the first of those
rules is violated during invocation of the current method, then
<span class="emphasis">*freturn*</span> throws an
`IllegalMonitorStateException`.

</div>

</div>

<div id="jvms-6.5.fstore" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*fstore*</span>

</div>

</div>

</div>

<div id="d5e19789" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Store `float` into local variable

</div>

<div id="d5e19793" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*fstore*</span>  
<span class="emphasis">*index*</span>  

</div>

</div>

<div id="d5e19798" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*fstore*</span> = 56 (0x38)

</div>

<div id="d5e19802" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.fstore.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*index*</span> is an unsigned byte that must
be an index into the local variable array of the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>).
The <span class="emphasis">*value*</span> on the top of the operand
stack must be of type `float`. It is popped from the operand stack, and
the value of the local variable at <span class="emphasis">*index*</span>
is set to <span class="emphasis">*value*</span>.

</div>

<div id="jvms-6.5.fstore.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*fstore*</span> opcode can be used in
conjunction with the <span class="emphasis">*wide*</span> instruction
(<a href="jvms-6.html#jvms-6.5.wide" class="xref" title="wide">§<span
class="emphasis"><em>wide</em></span></a>) to access a local variable
using a two-byte unsigned index.

</div>

</div>

<div id="jvms-6.5.fstore_n" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*fstore\_\<n\>*</span>

</div>

</div>

</div>

<div id="d5e19826" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Store `float` into local variable

</div>

<div id="d5e19830" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*fstore\_\<n\>*</span>  

</div>

</div>

<div id="d5e19834" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*fstore_0*</span> = 67 (0x43)

<span class="emphasis">*fstore_1*</span> = 68 (0x44)

<span class="emphasis">*fstore_2*</span> = 69 (0x45)

<span class="emphasis">*fstore_3*</span> = 70 (0x46)

</div>

<div id="d5e19844" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.fstore_n.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The \<<span class="emphasis">*n*</span>\> must be an index into the
local variable array of the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>).
The <span class="emphasis">*value*</span> on the top of the operand
stack must be of type `float`. It is popped from the operand stack, and
the value of the local variable at \<<span class="emphasis">*n*</span>\>
is set to <span class="emphasis">*value*</span>.

</div>

<div id="jvms-6.5.fstore_n.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

Each of the <span class="emphasis">*fstore\_\<n\>*</span> instructions
is the same as <span class="emphasis">*fstore*</span> with an
<span class="emphasis">*index*</span> of
\<<span class="emphasis">*n*</span>\>, except that the operand
\<<span class="emphasis">*n*</span>\> is implicit.

</div>

</div>

<div id="jvms-6.5.fsub" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*fsub*</span>

</div>

</div>

</div>

<div id="d5e19870" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Subtract `float`

</div>

<div id="d5e19874" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*fsub*</span>  

</div>

</div>

<div id="d5e19878" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*fsub*</span> = 102 (0x66)

</div>

<div id="d5e19882" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.fsub.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `float`. The
values are popped from the operand stack. The `float`
<span class="emphasis">*result*</span> is
<span class="emphasis">*value1*</span> -
<span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

For `float` subtraction, it is always the case that `a-b` produces the
same result as `a+(-b)`. However, for the
<span class="emphasis">*fsub*</span> instruction, subtraction from zero
is not the same as negation, because if `x` is `+0.0`, then `0.0-x`
equals `+0.0`, but `-x` equals `-0.0`.

The Java Virtual Machine requires support of gradual underflow. Despite
the fact that overflow, underflow, or loss of precision may occur,
execution of an <span class="emphasis">*fsub*</span> instruction never
throws a run-time exception.

</div>

</div>

<div id="jvms-6.5.getfield" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*getfield*</span>

</div>

</div>

</div>

<div id="d5e19917" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Fetch field from object

</div>

<div id="d5e19920" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*getfield*</span>  
<span class="emphasis">*indexbyte1*</span>  
<span class="emphasis">*indexbyte2*</span>  

</div>

</div>

<div id="d5e19926" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*getfield*</span> = 180 (0xb4)

</div>

<div id="d5e19930" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*objectref*</span>
<span class="symbol">→</span>

..., <span class="emphasis">*value*</span>

</div>

<div id="jvms-6.5.getfield.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The unsigned <span class="emphasis">*indexbyte1*</span> and
<span class="emphasis">*indexbyte2*</span> are used to construct an
index into the run-time constant pool of the current class
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>),
where the value of the index is
(<span class="emphasis">*indexbyte1*</span> `<<` 8) \|
<span class="emphasis">*indexbyte2*</span>. The run-time constant pool
entry at the index must be a symbolic reference to a field
(<a href="jvms-5.html#jvms-5.1" class="xref"
title="5.1. The Run-Time Constant Pool">§5.1</a>), which gives the name
and descriptor of the field as well as a symbolic reference to the class
in which the field is to be found. The referenced field is resolved
(<a href="jvms-5.html#jvms-5.4.3.2" class="xref"
title="5.4.3.2. Field Resolution">§5.4.3.2</a>).

The <span class="emphasis">*objectref*</span>, which must be of type
`reference` but not an array type, is popped from the operand stack. The
<span class="emphasis">*value*</span> of the referenced field in
<span class="emphasis">*objectref*</span> is fetched and pushed onto the
operand stack.

</div>

<div id="jvms-6.5.getfield.linking" class="section">

<div class="titlepage">

<div>

<div>

#### Linking Exceptions

</div>

</div>

</div>

During resolution of the symbolic reference to the field, any of the
errors pertaining to field resolution
(<a href="jvms-5.html#jvms-5.4.3.2" class="xref"
title="5.4.3.2. Field Resolution">§5.4.3.2</a>) can be thrown.

Otherwise, if the resolved field is a `static` field,
<span class="emphasis">*getfield*</span> throws an
`IncompatibleClassChangeError`.

</div>

<div id="jvms-6.5.getfield.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exception

</div>

</div>

</div>

Otherwise, if <span class="emphasis">*objectref*</span> is `null`, the
<span class="emphasis">*getfield*</span> instruction throws a
`NullPointerException`.

</div>

<div id="jvms-6.5.getfield.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*getfield*</span> instruction cannot be used
to access the `length` field of an array. The
<span class="emphasis">*arraylength*</span> instruction
(<a href="jvms-6.html#jvms-6.5.arraylength" class="xref"
title="arraylength">§<span
class="emphasis"><em>arraylength</em></span></a>) is used instead.

</div>

</div>

<div id="jvms-6.5.getstatic" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*getstatic*</span>

</div>

</div>

</div>

<div id="d5e19978" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Get `static` field from class

</div>

<div id="d5e19982" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*getstatic*</span>  
<span class="emphasis">*indexbyte1*</span>  
<span class="emphasis">*indexbyte2*</span>  

</div>

</div>

<div id="d5e19988" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*getstatic*</span> = 178 (0xb2)

</div>

<div id="d5e19992" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="symbol">→</span>

..., <span class="emphasis">*value*</span>

</div>

<div id="jvms-6.5.getstatic.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The unsigned <span class="emphasis">*indexbyte1*</span> and
<span class="emphasis">*indexbyte2*</span> are used to construct an
index into the run-time constant pool of the current class
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>),
where the value of the index is
(<span class="emphasis">*indexbyte1*</span> `<<` 8) \|
<span class="emphasis">*indexbyte2*</span>. The run-time constant pool
entry at the index must be a symbolic reference to a field
(<a href="jvms-5.html#jvms-5.1" class="xref"
title="5.1. The Run-Time Constant Pool">§5.1</a>), which gives the name
and descriptor of the field as well as a symbolic reference to the class
or interface in which the field is to be found. The referenced field is
resolved (<a href="jvms-5.html#jvms-5.4.3.2" class="xref"
title="5.4.3.2. Field Resolution">§5.4.3.2</a>).

On successful resolution of the field, the class or interface that
declared the resolved field is initialized if that class or interface
has not already been initialized
(<a href="jvms-5.html#jvms-5.5" class="xref"
title="5.5. Initialization">§5.5</a>).

The <span class="emphasis">*value*</span> of the class or interface
field is fetched and pushed onto the operand stack.

</div>

<div id="jvms-6.5.getstatic.linking" class="section">

<div class="titlepage">

<div>

<div>

#### Linking Exceptions

</div>

</div>

</div>

During resolution of the symbolic reference to the class or interface
field, any of the exceptions pertaining to field resolution
(<a href="jvms-5.html#jvms-5.4.3.2" class="xref"
title="5.4.3.2. Field Resolution">§5.4.3.2</a>) can be thrown.

Otherwise, if the resolved field is not a `static` (class) field or an
interface field, <span class="emphasis">*getstatic*</span> throws an
`IncompatibleClassChangeError`.

</div>

<div id="jvms-6.5.getstatic.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exception

</div>

</div>

</div>

Otherwise, if execution of this
<span class="emphasis">*getstatic*</span> instruction causes
initialization of the referenced class or interface,
<span class="emphasis">*getstatic*</span> may throw an `Error` as
detailed in <a href="jvms-5.html#jvms-5.5" class="xref"
title="5.5. Initialization">§5.5</a>.

</div>

</div>

<div id="jvms-6.5.goto" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*goto*</span>

</div>

</div>

</div>

<div id="d5e20031" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Branch always

</div>

<div id="d5e20034" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*goto*</span>  
<span class="emphasis">*branchbyte1*</span>  
<span class="emphasis">*branchbyte2*</span>  

</div>

</div>

<div id="d5e20040" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*goto*</span> = 167 (0xa7)

</div>

<div id="d5e20044" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

No change

</div>

<div id="jvms-6.5.goto.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The unsigned bytes <span class="emphasis">*branchbyte1*</span> and
<span class="emphasis">*branchbyte2*</span> are used to construct a
signed 16-bit <span class="emphasis">*branchoffset*</span>, where
<span class="emphasis">*branchoffset*</span> is
(<span class="emphasis">*branchbyte1*</span> `<<` 8) \|
<span class="emphasis">*branchbyte2*</span>. Execution proceeds at that
offset from the address of the opcode of this
<span class="emphasis">*goto*</span> instruction. The target address
must be that of an opcode of an instruction within the method that
contains this <span class="emphasis">*goto*</span> instruction.

</div>

</div>

<div id="jvms-6.5.goto_w" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*goto_w*</span>

</div>

</div>

</div>

<div id="d5e20062" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Branch always (wide index)

</div>

<div id="d5e20065" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*goto_w*</span>  
<span class="emphasis">*branchbyte1*</span>  
<span class="emphasis">*branchbyte2*</span>  
<span class="emphasis">*branchbyte3*</span>  
<span class="emphasis">*branchbyte4*</span>  

</div>

</div>

<div id="d5e20073" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*goto_w*</span> = 200 (0xc8)

</div>

<div id="d5e20077" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

No change

</div>

<div id="jvms-6.5.goto_w.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The unsigned bytes <span class="emphasis">*branchbyte1*</span>,
<span class="emphasis">*branchbyte2*</span>,
<span class="emphasis">*branchbyte3*</span>, and
<span class="emphasis">*branchbyte4*</span> are used to construct a
signed 32-bit <span class="emphasis">*branchoffset*</span>, where
<span class="emphasis">*branchoffset*</span> is
(<span class="emphasis">*branchbyte1*</span> `<<` 24) \|
(<span class="emphasis">*branchbyte2*</span> `<<` 16) \|
(<span class="emphasis">*branchbyte3*</span> `<<` 8) \|
<span class="emphasis">*branchbyte4*</span>. Execution proceeds at that
offset from the address of the opcode of this
<span class="emphasis">*goto_w*</span> instruction. The target address
must be that of an opcode of an instruction within the method that
contains this <span class="emphasis">*goto_w*</span> instruction.

</div>

<div id="jvms-6.5.goto_w.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

Although the <span class="emphasis">*goto_w*</span> instruction takes a
4-byte branch offset, other factors limit the size of a method to 65535
bytes (<a href="jvms-4.html#jvms-4.11" class="xref"
title="4.11. Limitations of the Java Virtual Machine">§4.11</a>). This
limit may be raised in a future release of the Java Virtual Machine.

</div>

</div>

<div id="jvms-6.5.i2b" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*i2b*</span>

</div>

</div>

</div>

<div id="d5e20106" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Convert `int` to `byte`

</div>

<div id="d5e20111" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*i2b*</span>  

</div>

</div>

<div id="d5e20115" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*i2b*</span> = 145 (0x91)

</div>

<div id="d5e20119" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.i2b.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*value*</span> on the top of the operand
stack must be of type `int`. It is popped from the operand stack,
truncated to a `byte`, then sign-extended to an `int`
<span class="emphasis">*result*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

</div>

<div id="jvms-6.5.i2b.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*i2b*</span> instruction performs a narrowing
primitive conversion (JLS §5.1.3). It may lose information about the
overall magnitude of <span class="emphasis">*value*</span>. The
<span class="emphasis">*result*</span> may also not have the same sign
as <span class="emphasis">*value*</span>.

</div>

</div>

<div id="jvms-6.5.i2c" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*i2c*</span>

</div>

</div>

</div>

<div id="d5e20145" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Convert `int` to `char`

</div>

<div id="d5e20150" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*i2c*</span>  

</div>

</div>

<div id="d5e20154" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*i2c*</span> = 146 (0x92)

</div>

<div id="d5e20158" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.i2c.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*value*</span> on the top of the operand
stack must be of type `int`. It is popped from the operand stack,
truncated to `char`, then zero-extended to an `int`
<span class="emphasis">*result*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

</div>

<div id="jvms-6.5.i2c.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*i2c*</span> instruction performs a narrowing
primitive conversion (JLS §5.1.3). It may lose information about the
overall magnitude of <span class="emphasis">*value*</span>. The
<span class="emphasis">*result*</span> (which is always positive) may
also not have the same sign as <span class="emphasis">*value*</span>.

</div>

</div>

<div id="jvms-6.5.i2d" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*i2d*</span>

</div>

</div>

</div>

<div id="d5e20184" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Convert `int` to `double`

</div>

<div id="d5e20189" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*i2d*</span>  

</div>

</div>

<div id="d5e20193" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*i2d*</span> = 135 (0x87)

</div>

<div id="d5e20197" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.i2d.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*value*</span> on the top of the operand
stack must be of type `int`. It is popped from the operand stack and
converted to a `double` <span class="emphasis">*result*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

</div>

<div id="jvms-6.5.i2d.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*i2d*</span> instruction performs a widening
primitive conversion (JLS §5.1.2). Because all values of type `int` are
exactly representable by type `double`, the conversion is exact.

</div>

</div>

<div id="jvms-6.5.i2f" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*i2f*</span>

</div>

</div>

</div>

<div id="d5e20221" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Convert `int` to `float`

</div>

<div id="d5e20226" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*i2f*</span>  

</div>

</div>

<div id="d5e20230" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*i2f*</span> = 134 (0x86)

</div>

<div id="d5e20234" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.i2f.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*value*</span> on the top of the operand
stack must be of type `int`. It is popped from the operand stack and
converted to a `float` <span class="emphasis">*result*</span> using the
round to nearest rounding policy
(<a href="jvms-2.html#jvms-2.8" class="xref"
title="2.8. Floating-Point Arithmetic">§2.8</a>). The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

</div>

<div id="jvms-6.5.i2f.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*i2f*</span> instruction performs a widening
primitive conversion (JLS §5.1.2), but may result in a loss of precision
because values of type `float` have only 24 significand bits.

</div>

</div>

<div id="jvms-6.5.i2l" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*i2l*</span>

</div>

</div>

</div>

<div id="d5e20258" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Convert `int` to `long`

</div>

<div id="d5e20263" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*i2l*</span>  

</div>

</div>

<div id="d5e20267" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*i2l*</span> = 133 (0x85)

</div>

<div id="d5e20271" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.i2l.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*value*</span> on the top of the operand
stack must be of type `int`. It is popped from the operand stack and
sign-extended to a `long` <span class="emphasis">*result*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

</div>

<div id="jvms-6.5.i2l.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*i2l*</span> instruction performs a widening
primitive conversion (JLS §5.1.2). Because all values of type `int` are
exactly representable by type `long`, the conversion is exact.

</div>

</div>

<div id="jvms-6.5.i2s" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*i2s*</span>

</div>

</div>

</div>

<div id="d5e20295" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Convert `int` to `short`

</div>

<div id="d5e20300" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*i2s*</span>  

</div>

</div>

<div id="d5e20304" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*i2s*</span> = 147 (0x93)

</div>

<div id="d5e20308" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.i2s.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*value*</span> on the top of the operand
stack must be of type `int`. It is popped from the operand stack,
truncated to a `short`, then sign-extended to an `int`
<span class="emphasis">*result*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

</div>

<div id="jvms-6.5.i2s.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*i2s*</span> instruction performs a narrowing
primitive conversion (JLS §5.1.3). It may lose information about the
overall magnitude of <span class="emphasis">*value*</span>. The
<span class="emphasis">*result*</span> may also not have the same sign
as <span class="emphasis">*value*</span>.

</div>

</div>

<div id="jvms-6.5.iadd" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*iadd*</span>

</div>

</div>

</div>

<div id="d5e20334" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Add `int`

</div>

<div id="d5e20338" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*iadd*</span>  

</div>

</div>

<div id="d5e20342" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*iadd*</span> = 96 (0x60)

</div>

<div id="d5e20346" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.iadd.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `int`. The values
are popped from the operand stack. The `int`
<span class="emphasis">*result*</span> is
<span class="emphasis">*value1*</span> +
<span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

The result is the 32 low-order bits of the true mathematical result in a
sufficiently wide two's-complement format, represented as a value of
type `int`. If overflow occurs, then the sign of the result may not be
the same as the sign of the mathematical sum of the two values.

Despite the fact that overflow may occur, execution of an
<span class="emphasis">*iadd*</span> instruction never throws a run-time
exception.

</div>

</div>

<div id="jvms-6.5.iaload" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*iaload*</span>

</div>

</div>

</div>

<div id="d5e20372" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Load `int` from array

</div>

<div id="d5e20376" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*iaload*</span>  

</div>

</div>

<div id="d5e20380" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*iaload*</span> = 46 (0x2e)

</div>

<div id="d5e20384" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*arrayref*</span>,
<span class="emphasis">*index*</span> <span class="symbol">→</span>

..., <span class="emphasis">*value*</span>

</div>

<div id="jvms-6.5.iaload.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*arrayref*</span> must be of type `reference`
and must refer to an array whose components are of type `int`. The
<span class="emphasis">*index*</span> must be of type `int`. Both
<span class="emphasis">*arrayref*</span> and
<span class="emphasis">*index*</span> are popped from the operand stack.
The `int` <span class="emphasis">*value*</span> in the component of the
array at <span class="emphasis">*index*</span> is retrieved and pushed
onto the operand stack.

</div>

<div id="jvms-6.5.iaload.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

If <span class="emphasis">*arrayref*</span> is `null`,
<span class="emphasis">*iaload*</span> throws a `NullPointerException`.

Otherwise, if <span class="emphasis">*index*</span> is not within the
bounds of the array referenced by
<span class="emphasis">*arrayref*</span>, the
<span class="emphasis">*iaload*</span> instruction throws an
`ArrayIndexOutOfBoundsException`.

</div>

</div>

<div id="jvms-6.5.iand" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*iand*</span>

</div>

</div>

</div>

<div id="d5e20420" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Bitwise AND `int`

</div>

<div id="d5e20424" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*iand*</span>  

</div>

</div>

<div id="d5e20428" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*iand*</span> = 126 (0x7e)

</div>

<div id="d5e20432" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.iand.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `int`. They are
popped from the operand stack. An `int`
<span class="emphasis">*result*</span> is calculated by taking the
bitwise AND (conjunction) of <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

</div>

</div>

<div id="jvms-6.5.iastore" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*iastore*</span>

</div>

</div>

</div>

<div id="d5e20454" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Store into `int` array

</div>

<div id="d5e20458" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*iastore*</span>  

</div>

</div>

<div id="d5e20462" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*iastore*</span> = 79 (0x4f)

</div>

<div id="d5e20466" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*arrayref*</span>,
<span class="emphasis">*index*</span>,
<span class="emphasis">*value*</span> <span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.iastore.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*arrayref*</span> must be of type `reference`
and must refer to an array whose components are of type `int`. Both
<span class="emphasis">*index*</span> and
<span class="emphasis">*value*</span> must be of type `int`. The
<span class="emphasis">*arrayref*</span>,
<span class="emphasis">*index*</span>, and
<span class="emphasis">*value*</span> are popped from the operand stack.
The `int` <span class="emphasis">*value*</span> is stored as the
component of the array indexed by <span class="emphasis">*index*</span>.

</div>

<div id="jvms-6.5.iastore.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

If <span class="emphasis">*arrayref*</span> is `null`,
<span class="emphasis">*iastore*</span> throws a `NullPointerException`.

Otherwise, if <span class="emphasis">*index*</span> is not within the
bounds of the array referenced by
<span class="emphasis">*arrayref*</span>, the
<span class="emphasis">*iastore*</span> instruction throws an
`ArrayIndexOutOfBoundsException`.

</div>

</div>

<div id="jvms-6.5.iconst_i" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*iconst\_\<i\>*</span>

</div>

</div>

</div>

<div id="d5e20504" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Push `int` constant

</div>

<div id="d5e20508" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*iconst\_\<i\>*</span>  

</div>

</div>

<div id="d5e20512" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*iconst_m1*</span> = 2 (0x2)

<span class="emphasis">*iconst_0*</span> = 3 (0x3)

<span class="emphasis">*iconst_1*</span> = 4 (0x4)

<span class="emphasis">*iconst_2*</span> = 5 (0x5)

<span class="emphasis">*iconst_3*</span> = 6 (0x6)

<span class="emphasis">*iconst_4*</span> = 7 (0x7)

<span class="emphasis">*iconst_5*</span> = 8 (0x8)

</div>

<div id="d5e20528" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

... <span class="symbol">→</span>

..., \<<span class="emphasis">*i*</span>\>

</div>

<div id="jvms-6.5.iconst_i.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Push the `int` constant \<<span class="emphasis">*i*</span>\> (-1, 0, 1,
2, 3, 4 or 5) onto the operand stack.

</div>

<div id="jvms-6.5.iconst_i.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

Each of this family of instructions is equivalent to
<span class="emphasis">*bipush*</span>
\<<span class="emphasis">*i*</span>\> for the respective value of
\<<span class="emphasis">*i*</span>\>, except that the operand
\<<span class="emphasis">*i*</span>\> is implicit.

</div>

</div>

<div id="jvms-6.5.idiv" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*idiv*</span>

</div>

</div>

</div>

<div id="d5e20549" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Divide `int`

</div>

<div id="d5e20553" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*idiv*</span>  

</div>

</div>

<div id="d5e20557" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*idiv*</span> = 108 (0x6c)

</div>

<div id="d5e20561" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.idiv.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `int`. The values
are popped from the operand stack. The `int`
<span class="emphasis">*result*</span> is the value of the Java
programming language expression <span class="emphasis">*value1*</span> /
<span class="emphasis">*value2*</span> (JLS §15.17.2). The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

An `int` division rounds towards 0; that is, the quotient produced for
`int` values in
<span class="emphasis">*n*</span>/<span class="emphasis">*d*</span> is
an `int` value <span class="emphasis">*q*</span> whose magnitude is as
large as possible while satisfying \|<span class="emphasis">*d*</span>
<span class="symbol">⋅</span> <span class="emphasis">*q*</span>\|
<span class="symbol">≤</span> \|<span class="emphasis">*n*</span>\|.
Moreover, <span class="emphasis">*q*</span> is positive when
\|<span class="emphasis">*n*</span>\| <span class="symbol">≥</span>
\|<span class="emphasis">*d*</span>\| and
<span class="emphasis">*n*</span> and <span class="emphasis">*d*</span>
have the same sign, but <span class="emphasis">*q*</span> is negative
when \|<span class="emphasis">*n*</span>\| <span class="symbol">≥</span>
\|<span class="emphasis">*d*</span>\| and
<span class="emphasis">*n*</span> and <span class="emphasis">*d*</span>
have opposite signs.

There is one special case that does not satisfy this rule: if the
dividend is the negative integer of largest possible magnitude for the
`int` type, and the divisor is -1, then overflow occurs, and the result
is equal to the dividend. Despite the overflow, no exception is thrown
in this case.

</div>

<div id="jvms-6.5.idiv.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exception

</div>

</div>

</div>

If the value of the divisor in an `int` division is 0,
<span class="emphasis">*idiv*</span> throws an `ArithmeticException`.

</div>

</div>

<div id="jvms-6.5.if_acmp_cond" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*if_acmp\<cond\>*</span>

</div>

</div>

</div>

<div id="d5e20615" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Branch if `reference` comparison succeeds

</div>

<div id="d5e20619" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*if_acmp\<cond\>*</span>  
<span class="emphasis">*branchbyte1*</span>  
<span class="emphasis">*branchbyte2*</span>  

</div>

</div>

<div id="d5e20625" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*if_acmpeq*</span> = 165 (0xa5)

<span class="emphasis">*if_acmpne*</span> = 166 (0xa6)

</div>

<div id="d5e20631" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.if_acmp_cond.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `reference`. They
are both popped from the operand stack and compared. The results of the
comparison are as follows:

<div class="norm">

- <span class="emphasis">*if_acmpeq*</span> succeeds if and only if
  <span class="emphasis">*value1*</span> =
  <span class="emphasis">*value2*</span>

- <span class="emphasis">*if_acmpne*</span> succeeds if and only if
  <span class="emphasis">*value1*</span> <span class="symbol">≠</span>
  <span class="emphasis">*value2*</span>

</div>

If the comparison succeeds, the unsigned
<span class="emphasis">*branchbyte1*</span> and
<span class="emphasis">*branchbyte2*</span> are used to construct a
signed 16-bit offset, where the offset is calculated to be
(<span class="emphasis">*branchbyte1*</span> `<<` 8) \|
<span class="emphasis">*branchbyte2*</span>. Execution then proceeds at
that offset from the address of the opcode of this
<span class="emphasis">*if_acmp\<cond\>*</span> instruction. The target
address must be that of an opcode of an instruction within the method
that contains this <span class="emphasis">*if_acmp\<cond\>*</span>
instruction.

Otherwise, if the comparison fails, execution proceeds at the address of
the instruction following this
<span class="emphasis">*if_acmp\<cond\>*</span> instruction.

</div>

</div>

<div id="jvms-6.5.if_icmp_cond" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*if_icmp\<cond\>*</span>

</div>

</div>

</div>

<div id="d5e20669" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Branch if `int` comparison succeeds

</div>

<div id="d5e20673" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*if_icmp\<cond\>*</span>  
<span class="emphasis">*branchbyte1*</span>  
<span class="emphasis">*branchbyte2*</span>  

</div>

</div>

<div id="d5e20679" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*if_icmpeq*</span> = 159 (0x9f)

<span class="emphasis">*if_icmpne*</span> = 160 (0xa0)

<span class="emphasis">*if_icmplt*</span> = 161 (0xa1)

<span class="emphasis">*if_icmpge*</span> = 162 (0xa2)

<span class="emphasis">*if_icmpgt*</span> = 163 (0xa3)

<span class="emphasis">*if_icmple*</span> = 164 (0xa4)

</div>

<div id="d5e20693" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.if_icmp_cond.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `int`. They are
both popped from the operand stack and compared. All comparisons are
signed. The results of the comparison are as follows:

<div class="norm">

- <span class="emphasis">*if_icmpeq*</span> succeeds if and only if
  <span class="emphasis">*value1*</span> =
  <span class="emphasis">*value2*</span>

- <span class="emphasis">*if_icmpne*</span> succeeds if and only if
  <span class="emphasis">*value1*</span> <span class="symbol">≠</span>
  <span class="emphasis">*value2*</span>

- <span class="emphasis">*if_icmplt*</span> succeeds if and only if
  <span class="emphasis">*value1*</span> \<
  <span class="emphasis">*value2*</span>

- <span class="emphasis">*if_icmple*</span> succeeds if and only if
  <span class="emphasis">*value1*</span> <span class="symbol">≤</span>
  <span class="emphasis">*value2*</span>

- <span class="emphasis">*if_icmpgt*</span> succeeds if and only if
  <span class="emphasis">*value1*</span> \>
  <span class="emphasis">*value2*</span>

- <span class="emphasis">*if_icmpge*</span> succeeds if and only if
  <span class="emphasis">*value1*</span> <span class="symbol">≥</span>
  <span class="emphasis">*value2*</span>

</div>

If the comparison succeeds, the unsigned
<span class="emphasis">*branchbyte1*</span> and
<span class="emphasis">*branchbyte2*</span> are used to construct a
signed 16-bit offset, where the offset is calculated to be
(<span class="emphasis">*branchbyte1*</span> `<<` 8) \|
<span class="emphasis">*branchbyte2*</span>. Execution then proceeds at
that offset from the address of the opcode of this
<span class="emphasis">*if_icmp\<cond\>*</span> instruction. The target
address must be that of an opcode of an instruction within the method
that contains this <span class="emphasis">*if_icmp\<cond\>*</span>
instruction.

Otherwise, execution proceeds at the address of the instruction
following this <span class="emphasis">*if_icmp\<cond\>*</span>
instruction.

</div>

</div>

<div id="jvms-6.5.if_cond" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*if\<cond\>*</span>

</div>

</div>

</div>

<div id="d5e20753" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Branch if `int` comparison with zero succeeds

</div>

<div id="d5e20757" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*if\<cond\>*</span>  
<span class="emphasis">*branchbyte1*</span>  
<span class="emphasis">*branchbyte2*</span>  

</div>

</div>

<div id="d5e20763" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*ifeq*</span> = 153 (0x99)

<span class="emphasis">*ifne*</span> = 154 (0x9a)

<span class="emphasis">*iflt*</span> = 155 (0x9b)

<span class="emphasis">*ifge*</span> = 156 (0x9c)

<span class="emphasis">*ifgt*</span> = 157 (0x9d)

<span class="emphasis">*ifle*</span> = 158 (0x9e)

</div>

<div id="d5e20777" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.if_cond.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*value*</span> must be of type `int`. It is
popped from the operand stack and compared against zero. All comparisons
are signed. The results of the comparisons are as follows:

<div class="norm">

- <span class="emphasis">*ifeq*</span> succeeds if and only if
  <span class="emphasis">*value*</span> = 0

- <span class="emphasis">*ifne*</span> succeeds if and only if
  <span class="emphasis">*value*</span> <span class="symbol">≠</span> 0

- <span class="emphasis">*iflt*</span> succeeds if and only if
  <span class="emphasis">*value*</span> \< 0

- <span class="emphasis">*ifle*</span> succeeds if and only if
  <span class="emphasis">*value*</span> <span class="symbol">≤</span> 0

- <span class="emphasis">*ifgt*</span> succeeds if and only if
  <span class="emphasis">*value*</span> \> 0

- <span class="emphasis">*ifge*</span> succeeds if and only if
  <span class="emphasis">*value*</span> <span class="symbol">≥</span> 0

</div>

If the comparison succeeds, the unsigned
<span class="emphasis">*branchbyte1*</span> and
<span class="emphasis">*branchbyte2*</span> are used to construct a
signed 16-bit offset, where the offset is calculated to be
(<span class="emphasis">*branchbyte1*</span> `<<` 8) \|
<span class="emphasis">*branchbyte2*</span>. Execution then proceeds at
that offset from the address of the opcode of this
<span class="emphasis">*if\<cond\>*</span> instruction. The target
address must be that of an opcode of an instruction within the method
that contains this <span class="emphasis">*if\<cond\>*</span>
instruction.

Otherwise, execution proceeds at the address of the instruction
following this <span class="emphasis">*if\<cond\>*</span> instruction.

</div>

</div>

<div id="jvms-6.5.ifnonnull" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*ifnonnull*</span>

</div>

</div>

</div>

<div id="d5e20829" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Branch if `reference` not `null`

</div>

<div id="d5e20834" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*ifnonnull*</span>  
<span class="emphasis">*branchbyte1*</span>  
<span class="emphasis">*branchbyte2*</span>  

</div>

</div>

<div id="d5e20840" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*ifnonnull*</span> = 199 (0xc7)

</div>

<div id="d5e20844" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.ifnonnull.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*value*</span> must be of type `reference`.
It is popped from the operand stack. If
<span class="emphasis">*value*</span> is not `null`, the unsigned
<span class="emphasis">*branchbyte1*</span> and
<span class="emphasis">*branchbyte2*</span> are used to construct a
signed 16-bit offset, where the offset is calculated to be
(<span class="emphasis">*branchbyte1*</span> `<<` 8) \|
<span class="emphasis">*branchbyte2*</span>. Execution then proceeds at
that offset from the address of the opcode of this
<span class="emphasis">*ifnonnull*</span> instruction. The target
address must be that of an opcode of an instruction within the method
that contains this <span class="emphasis">*ifnonnull*</span>
instruction.

Otherwise, execution proceeds at the address of the instruction
following this <span class="emphasis">*ifnonnull*</span> instruction.

</div>

</div>

<div id="jvms-6.5.ifnull" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*ifnull*</span>

</div>

</div>

</div>

<div id="d5e20869" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Branch if `reference` is `null`

</div>

<div id="d5e20874" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*ifnull*</span>  
<span class="emphasis">*branchbyte1*</span>  
<span class="emphasis">*branchbyte2*</span>  

</div>

</div>

<div id="d5e20880" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*ifnull*</span> = 198 (0xc6)

</div>

<div id="d5e20884" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.ifnull.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*value*</span> must of type `reference`. It
is popped from the operand stack. If
<span class="emphasis">*value*</span> is `null`, the unsigned
<span class="emphasis">*branchbyte1*</span> and
<span class="emphasis">*branchbyte2*</span> are used to construct a
signed 16-bit offset, where the offset is calculated to be
(<span class="emphasis">*branchbyte1*</span> `<<` 8) \|
<span class="emphasis">*branchbyte2*</span>. Execution then proceeds at
that offset from the address of the opcode of this
<span class="emphasis">*ifnull*</span> instruction. The target address
must be that of an opcode of an instruction within the method that
contains this <span class="emphasis">*ifnull*</span> instruction.

Otherwise, execution proceeds at the address of the instruction
following this <span class="emphasis">*ifnull*</span> instruction.

</div>

</div>

<div id="jvms-6.5.iinc" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*iinc*</span>

</div>

</div>

</div>

<div id="d5e20909" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Increment local variable by constant

</div>

<div id="d5e20912" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*iinc*</span>  
<span class="emphasis">*index*</span>  
<span class="emphasis">*const*</span>  

</div>

</div>

<div id="d5e20918" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*iinc*</span> = 132 (0x84)

</div>

<div id="d5e20922" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

No change

</div>

<div id="jvms-6.5.iinc.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*index*</span> is an unsigned byte that must
be an index into the local variable array of the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>).
The <span class="emphasis">*const*</span> is an immediate signed byte.
The local variable at <span class="emphasis">*index*</span> must contain
an `int`. The value <span class="emphasis">*const*</span> is first
sign-extended to an `int`, and then the local variable at
<span class="emphasis">*index*</span> is incremented by that amount.

</div>

<div id="jvms-6.5.iinc.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*iinc*</span> opcode can be used in
conjunction with the <span class="emphasis">*wide*</span> instruction
(<a href="jvms-6.html#jvms-6.5.wide" class="xref" title="wide">§<span
class="emphasis"><em>wide</em></span></a>) to access a local variable
using a two-byte unsigned index and to increment it by a two-byte
immediate signed value.

</div>

</div>

<div id="jvms-6.5.iload" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*iload*</span>

</div>

</div>

</div>

<div id="d5e20945" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Load `int` from local variable

</div>

<div id="d5e20949" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*iload*</span>  
<span class="emphasis">*index*</span>  

</div>

</div>

<div id="d5e20954" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*iload*</span> = 21 (0x15)

</div>

<div id="d5e20958" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

... <span class="symbol">→</span>

..., <span class="emphasis">*value*</span>

</div>

<div id="jvms-6.5.iload.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*index*</span> is an unsigned byte that must
be an index into the local variable array of the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>).
The local variable at <span class="emphasis">*index*</span> must contain
an `int`. The <span class="emphasis">*value*</span> of the local
variable at <span class="emphasis">*index*</span> is pushed onto the
operand stack.

</div>

<div id="jvms-6.5.iload.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*iload*</span> opcode can be used in
conjunction with the <span class="emphasis">*wide*</span> instruction
(<a href="jvms-6.html#jvms-6.5.wide" class="xref" title="wide">§<span
class="emphasis"><em>wide</em></span></a>) to access a local variable
using a two-byte unsigned index.

</div>

</div>

<div id="jvms-6.5.iload_n" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*iload\_\<n\>*</span>

</div>

</div>

</div>

<div id="d5e20982" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Load `int` from local variable

</div>

<div id="d5e20986" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*iload\_\<n\>*</span>  

</div>

</div>

<div id="d5e20990" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*iload_0*</span> = 26 (0x1a)

<span class="emphasis">*iload_1*</span> = 27 (0x1b)

<span class="emphasis">*iload_2*</span> = 28 (0x1c)

<span class="emphasis">*iload_3*</span> = 29 (0x1d)

</div>

<div id="d5e21000" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

... <span class="symbol">→</span>

..., <span class="emphasis">*value*</span>

</div>

<div id="jvms-6.5.iload_n.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The \<<span class="emphasis">*n*</span>\> must be an index into the
local variable array of the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>).
The local variable at \<<span class="emphasis">*n*</span>\> must contain
an `int`. The <span class="emphasis">*value*</span> of the local
variable at \<<span class="emphasis">*n*</span>\> is pushed onto the
operand stack.

</div>

<div id="jvms-6.5.iload_n.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

Each of the <span class="emphasis">*iload\_\<n\>*</span> instructions is
the same as <span class="emphasis">*iload*</span> with an
<span class="emphasis">*index*</span> of
\<<span class="emphasis">*n*</span>\>, except that the operand
\<<span class="emphasis">*n*</span>\> is implicit.

</div>

</div>

<div id="jvms-6.5.imul" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*imul*</span>

</div>

</div>

</div>

<div id="d5e21026" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Multiply `int`

</div>

<div id="d5e21030" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*imul*</span>  

</div>

</div>

<div id="d5e21034" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*imul*</span> = 104 (0x68)

</div>

<div id="d5e21038" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.imul.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `int`. The values
are popped from the operand stack. The `int`
<span class="emphasis">*result*</span> is
<span class="emphasis">*value1*</span> \*
<span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

The result is the 32 low-order bits of the true mathematical result in a
sufficiently wide two's-complement format, represented as a value of
type `int`. If overflow occurs, then the sign of the result may not be
the same as the sign of the mathematical multiplication of the two
values.

Despite the fact that overflow may occur, execution of an
<span class="emphasis">*imul*</span> instruction never throws a run-time
exception.

</div>

</div>

<div id="jvms-6.5.ineg" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*ineg*</span>

</div>

</div>

</div>

<div id="d5e21064" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Negate `int`

</div>

<div id="d5e21068" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*ineg*</span>  

</div>

</div>

<div id="d5e21072" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*ineg*</span> = 116 (0x74)

</div>

<div id="d5e21076" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.ineg.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*value*</span> must be of type `int`. It is
popped from the operand stack. The `int`
<span class="emphasis">*result*</span> is the arithmetic negation of
<span class="emphasis">*value*</span>,
-<span class="emphasis">*value*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

For `int` values, negation is the same as subtraction from zero. Because
the Java Virtual Machine uses two's-complement representation for
integers and the range of two's-complement values is not symmetric, the
negation of the maximum negative `int` results in that same maximum
negative number. Despite the fact that overflow has occurred, no
exception is thrown.

For all `int` values `x`, `-x` equals `(~x)+1`.

</div>

</div>

<div id="jvms-6.5.instanceof" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*instanceof*</span>

</div>

</div>

</div>

<div id="d5e21104" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Determine if object is of given type

</div>

<div id="d5e21107" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*instanceof*</span>  
<span class="emphasis">*indexbyte1*</span>  
<span class="emphasis">*indexbyte2*</span>  

</div>

</div>

<div id="d5e21113" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*instanceof*</span> = 193 (0xc1)

</div>

<div id="d5e21117" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*objectref*</span>
<span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.instanceof.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*objectref*</span>, which must be of type
`reference`, is popped from the operand stack. The unsigned
<span class="emphasis">*indexbyte1*</span> and
<span class="emphasis">*indexbyte2*</span> are used to construct an
index into the run-time constant pool of the current class
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>),
where the value of the index is
(<span class="emphasis">*indexbyte1*</span> `<<` 8) \|
<span class="emphasis">*indexbyte2*</span>. The run-time constant pool
entry at the index must be a symbolic reference to a class, array, or
interface type.

If <span class="emphasis">*objectref*</span> is `null`, the
<span class="emphasis">*instanceof*</span> instruction pushes an `int`
<span class="emphasis">*result*</span> of 0 onto the operand stack.

Otherwise, the named class, array, or interface type is resolved
(<a href="jvms-5.html#jvms-5.4.3.1" class="xref"
title="5.4.3.1. Class and Interface Resolution">§5.4.3.1</a>). If
<span class="emphasis">*objectref*</span> is a value of the type given
by the resolved class, array, or interface type, the
<span class="emphasis">*instanceof*</span> instruction pushes an `int`
<span class="emphasis">*result*</span> of 1 onto the operand stack;
otherwise, it pushes an `int` <span class="emphasis">*result*</span> of
0.

Whether <span class="emphasis">*objectref*</span> is a value of the type
given by the resolved class, array, or interface type is determined
according to the rules given for
<a href="jvms-6.html#jvms-6.5.checkcast" class="xref"
title="checkcast">§<span class="emphasis"><em>checkcast</em></span></a>.

</div>

<div id="jvms-6.5.instanceof.linking" class="section">

<div class="titlepage">

<div>

<div>

#### Linking Exceptions

</div>

</div>

</div>

During resolution of the symbolic reference to the class, array, or
interface type, any of the exceptions documented in
<a href="jvms-5.html#jvms-5.4.3.1" class="xref"
title="5.4.3.1. Class and Interface Resolution">§5.4.3.1</a> can be
thrown.

</div>

<div id="jvms-6.5.instanceof.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*instanceof*</span> instruction is very
similar to the <span class="emphasis">*checkcast*</span> instruction
(<a href="jvms-6.html#jvms-6.5.checkcast" class="xref"
title="checkcast">§<span class="emphasis"><em>checkcast</em></span></a>).
It differs in its treatment of `null`, its behavior when its test fails
(<span class="emphasis">*checkcast*</span> throws an exception,
<span class="emphasis">*instanceof*</span> pushes a result code), and
its effect on the operand stack.

</div>

</div>

<div id="jvms-6.5.invokedynamic" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*invokedynamic*</span>

</div>

</div>

</div>

<div id="d5e21168" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Invoke a dynamically-computed call site

</div>

<div id="d5e21171" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*invokedynamic*</span>  
<span class="emphasis">*indexbyte1*</span>  
<span class="emphasis">*indexbyte2*</span>  
<span class="emphasis">*0*</span>  
<span class="emphasis">*0*</span>  

</div>

</div>

<div id="d5e21179" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*invokedynamic*</span> = 186 (0xba)

</div>

<div id="d5e21183" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., \[<span class="emphasis">*arg1*</span>,
\[<span class="emphasis">*arg2*</span> ...\]\]
<span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.invokedynamic.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

First, the unsigned <span class="emphasis">*indexbyte1*</span> and
<span class="emphasis">*indexbyte2*</span> are used to construct an
index into the run-time constant pool of the current class
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>),
where the value of the index is
(<span class="emphasis">*indexbyte1*</span> `<<` 8) \|
<span class="emphasis">*indexbyte2*</span>. The run-time constant pool
entry at the index must be a symbolic reference to a
dynamically-computed call site
(<a href="jvms-5.html#jvms-5.1" class="xref"
title="5.1. The Run-Time Constant Pool">§5.1</a>). The values of the
third and fourth operand bytes must always be zero.

The symbolic reference is resolved
(<a href="jvms-5.html#jvms-5.4.3.6" class="xref"
title="5.4.3.6. Dynamically-Computed Constant and Call Site Resolution">§5.4.3.6</a>)
<span class="emphasis">*for this specific*</span>
<span class="emphasis">*invokedynamic*</span>
<span class="emphasis">*instruction*</span> to obtain a `reference` to
an instance of `java.lang.invoke.CallSite`. The instance of
`java.lang.invoke.CallSite` is considered "bound" to this specific
<span class="emphasis">*invokedynamic*</span> instruction.

The instance of `java.lang.invoke.CallSite` indicates a
<span class="emphasis">*target method handle*</span>. The
<span class="emphasis">*nargs*</span> argument values are popped from
the operand stack, and the target method handle is invoked. The
invocation occurs as if by execution of an
<span class="emphasis">*invokevirtual*</span> instruction that indicates
a run-time constant pool index to a symbolic reference
<span class="type">R</span> where:

<div class="norm">

- <span class="type">R</span> is a symbolic reference to a method of a
  class;

- for the symbolic reference to the class in which the method is to be
  found, <span class="type">R</span> specifies
  `java.lang.invoke.MethodHandle`;

- for the name of the method, <span class="type">R</span> specifies
  `invokeExact`;

- for the descriptor of the method, <span class="type">R</span>
  specifies the method descriptor in the dynamically-computed call site.

</div>

and where it is as if the following items were pushed, in order, onto
the operand stack:

<div class="norm">

- a `reference` to the target method handle;

- the <span class="emphasis">*nargs*</span> argument values, where the
  number, type, and order of the values must be consistent with the
  method descriptor in the dynamically-computed call site.

</div>

</div>

<div id="jvms-6.5.invokedynamic.linking" class="section">

<div class="titlepage">

<div>

<div>

#### Linking Exceptions

</div>

</div>

</div>

During resolution of the symbolic reference to a dynamically-computed
call site, any of the exceptions pertaining to dynamically-computed call
site resolution can be thrown.

</div>

<div id="jvms-6.5.invokedynamic.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

If the symbolic reference to the dynamically-computed call site can be
resolved, it implies that a non-`null` `reference` to an instance of
`java.lang.invoke.CallSite` is bound to the
<span class="emphasis">*invokedynamic*</span> instruction. Therefore,
the target method handle, indicated by the instance of
`java.lang.invoke.CallSite`, is non-`null`.

Similarly, successful resolution implies that the method descriptor in
the symbolic reference is semantically equal to the type descriptor of
the target method handle.

Together, these invariants mean that an
<span class="emphasis">*invokedynamic*</span> instruction which is bound
to an instance of `java.lang.invoke.CallSite` never throws a
`NullPointerException` or a `java.lang.invoke.WrongMethodTypeException`.

</div>

</div>

<div id="jvms-6.5.invokeinterface" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*invokeinterface*</span>

</div>

</div>

</div>

<div id="d5e21259" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Invoke interface method

</div>

<div id="d5e21262" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*invokeinterface*</span>  
<span class="emphasis">*indexbyte1*</span>  
<span class="emphasis">*indexbyte2*</span>  
<span class="emphasis">*count*</span>  
<span class="emphasis">*0*</span>  

</div>

</div>

<div id="d5e21270" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*invokeinterface*</span> = 185 (0xb9)

</div>

<div id="d5e21274" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*objectref*</span>,
\[<span class="emphasis">*arg1*</span>,
\[<span class="emphasis">*arg2*</span> ...\]\]
<span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.invokeinterface.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The unsigned <span class="emphasis">*indexbyte1*</span> and
<span class="emphasis">*indexbyte2*</span> are used to construct an
index into the run-time constant pool of the current class
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>),
where the value of the index is
(<span class="emphasis">*indexbyte1*</span> `<<` 8) \|
<span class="emphasis">*indexbyte2*</span>. The run-time constant pool
entry at the index must be a symbolic reference to an interface method
(<a href="jvms-5.html#jvms-5.1" class="xref"
title="5.1. The Run-Time Constant Pool">§5.1</a>), which gives the name
and descriptor (<a href="jvms-4.html#jvms-4.3.3" class="xref"
title="4.3.3. Method Descriptors">§4.3.3</a>) of the interface method as
well as a symbolic reference to the interface in which the interface
method is to be found. The named interface method is resolved
(<a href="jvms-5.html#jvms-5.4.3.4" class="xref"
title="5.4.3.4. Interface Method Resolution">§5.4.3.4</a>).

The resolved interface method must not be an instance initialization
method, or the class or interface initialization method
(<a href="jvms-2.html#jvms-2.9.1" class="xref"
title="2.9.1. Instance Initialization Methods">§2.9.1</a>,
<a href="jvms-2.html#jvms-2.9.2" class="xref"
title="2.9.2. Class Initialization Methods">§2.9.2</a>).

The <span class="emphasis">*count*</span> operand is an unsigned byte
that must not be zero. The <span class="emphasis">*objectref*</span>
must be of type `reference` and must be followed on the operand stack by
<span class="emphasis">*nargs*</span> argument values, where the number,
type, and order of the values must be consistent with the descriptor of
the resolved interface method. The value of the fourth operand byte must
always be zero.

Let <span class="type">C</span> be the class of
<span class="emphasis">*objectref*</span>. A method is selected with
respect to <span class="type">C</span> and the resolved method
(<a href="jvms-5.html#jvms-5.4.6" class="xref"
title="5.4.6. Method Selection">§5.4.6</a>). This is the
<span class="emphasis">*method to be invoked*</span>.

If the method to be invoked is `synchronized`, the monitor associated
with <span class="emphasis">*objectref*</span> is entered or reentered
as if by execution of a <span class="emphasis">*monitorenter*</span>
instruction (<a href="jvms-6.html#jvms-6.5.monitorenter" class="xref"
title="monitorenter">§<span
class="emphasis"><em>monitorenter</em></span></a>) in the current
thread.

If the method to be invoked is not `native`, the
<span class="emphasis">*nargs*</span> argument values and
<span class="emphasis">*objectref*</span> are popped from the operand
stack. A new frame is created on the Java Virtual Machine stack for the
method being invoked. The <span class="emphasis">*objectref*</span> and
the argument values are consecutively made the values of local variables
of the new frame, with <span class="emphasis">*objectref*</span> in
local variable 0, <span class="emphasis">*arg1*</span> in local variable
1 (or, if <span class="emphasis">*arg1*</span> is of type `long` or
`double`, in local variables 1 and 2), and so on. The new frame is then
made current, and the Java Virtual Machine `pc` is set to the opcode of
the first instruction of the method to be invoked. Execution continues
with the first instruction of the method.

If the method to be invoked is `native` and the platform-dependent code
that implements it has not yet been bound
(<a href="jvms-5.html#jvms-5.6" class="xref"
title="5.6. Binding Native Method Implementations">§5.6</a>) into the
Java Virtual Machine, then that is done. The
<span class="emphasis">*nargs*</span> argument values and
<span class="emphasis">*objectref*</span> are popped from the operand
stack and are passed as parameters to the code that implements the
method. The parameters are passed and the code is invoked in an
implementation-dependent manner. When the platform-dependent code
returns:

<div class="norm">

- If the `native` method is `synchronized`, the monitor associated with
  <span class="emphasis">*objectref*</span> is updated and possibly
  exited as if by execution of a
  <span class="emphasis">*monitorexit*</span> instruction
  (<a href="jvms-6.html#jvms-6.5.monitorexit" class="xref"
  title="monitorexit">§<span
  class="emphasis"><em>monitorexit</em></span></a>) in the current
  thread.

- If the `native` method returns a value, the return value of the
  platform-dependent code is converted in an implementation-dependent
  way to the return type of the `native` method and pushed onto the
  operand stack.

</div>

</div>

<div id="jvms-6.5.invokeinterface.linking" class="section">

<div class="titlepage">

<div>

<div>

#### Linking Exceptions

</div>

</div>

</div>

During resolution of the symbolic reference to the interface method, any
of the exceptions pertaining to interface method resolution
(<a href="jvms-5.html#jvms-5.4.3.4" class="xref"
title="5.4.3.4. Interface Method Resolution">§5.4.3.4</a>) can be
thrown.

Otherwise, if the resolved method is `static`, the
<span class="emphasis">*invokeinterface*</span> instruction throws an
`IncompatibleClassChangeError`.

Note that <span class="emphasis">*invokeinterface*</span> may refer to
`private` methods declared in interfaces, including nestmate interfaces.

</div>

<div id="jvms-6.5.invokeinterface.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

Otherwise, if <span class="emphasis">*objectref*</span> is `null`, the
<span class="emphasis">*invokeinterface*</span> instruction throws a
`NullPointerException`.

Otherwise, if the class of <span class="emphasis">*objectref*</span>
does not implement the resolved interface,
<span class="emphasis">*invokeinterface*</span> throws an
`IncompatibleClassChangeError`.

Otherwise, if the selected method is neither `public` nor `private`,
<span class="emphasis">*invokeinterface*</span> throws an
`IllegalAccessError`.

Otherwise, if the selected method is `abstract`,
<span class="emphasis">*invokeinterface*</span> throws an
`AbstractMethodError`.

Otherwise, if the selected method is `native` and the code that
implements the method cannot be bound,
<span class="emphasis">*invokeinterface*</span> throws an
`UnsatisfiedLinkError`.

Otherwise, if no method is selected, and there are multiple
maximally-specific superinterface methods of <span class="type">C</span>
that match the resolved method's name and descriptor and are not
`abstract`, <span class="emphasis">*invokeinterface*</span> throws an
`IncompatibleClassChangeError`

Otherwise, if no method is selected, and there are no maximally-specific
superinterface methods of <span class="type">C</span> that match the
resolved method's name and descriptor and are not `abstract`,
<span class="emphasis">*invokeinterface*</span> throws an
`AbstractMethodError`.

</div>

<div id="jvms-6.5.invokeinterface.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*count*</span> operand of the
<span class="emphasis">*invokeinterface*</span> instruction records a
measure of the number of argument values, where an argument value of
type `long` or type `double` contributes two units to the
<span class="emphasis">*count*</span> value and an argument of any other
type contributes one unit. This information can also be derived from the
descriptor of the selected method. The redundancy is historical.

The fourth operand byte exists to reserve space for an additional
operand used in certain of Oracle's Java Virtual Machine
implementations, which replace the
<span class="emphasis">*invokeinterface*</span> instruction by a
specialized pseudo-instruction at run time. It must be retained for
backwards compatibility.

The <span class="emphasis">*nargs*</span> argument values and
<span class="emphasis">*objectref*</span> are not one-to-one with the
first <span class="emphasis">*nargs*</span>+1 local variables. Argument
values of types `long` and `double` must be stored in two consecutive
local variables, thus more than <span class="emphasis">*nargs*</span>
local variables may be required to pass
<span class="emphasis">*nargs*</span> argument values to the invoked
method.

The selection logic allows a non-`abstract` method declared in a
superinterface to be selected. Methods in interfaces are only considered
if there is no matching method in the class hierarchy. In the event that
there are two non-`abstract` methods in the superinterface hierarchy,
with neither more specific than the other, an error occurs; there is no
attempt to disambiguate (for example, one may be the referenced method
and one may be unrelated, but we do not prefer the referenced method).
On the other hand, if there are many `abstract` methods but only one
non-`abstract` method, the non-`abstract` method is selected (unless an
`abstract` method is more specific).

</div>

</div>

<div id="jvms-6.5.invokespecial" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*invokespecial*</span>

</div>

</div>

</div>

<div id="d5e21415" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Invoke instance method; direct invocation of instance initialization
methods and methods of the current class and its supertypes

</div>

<div id="d5e21418" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*invokespecial*</span>  
<span class="emphasis">*indexbyte1*</span>  
<span class="emphasis">*indexbyte2*</span>  

</div>

</div>

<div id="d5e21424" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*invokespecial*</span> = 183 (0xb7)

</div>

<div id="d5e21428" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*objectref*</span>,
\[<span class="emphasis">*arg1*</span>,
\[<span class="emphasis">*arg2*</span> ...\]\]
<span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.invokespecial.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The unsigned <span class="emphasis">*indexbyte1*</span> and
<span class="emphasis">*indexbyte2*</span> are used to construct an
index into the run-time constant pool of the current class
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>),
where the value of the index is
(<span class="emphasis">*indexbyte1*</span> `<<` 8) \|
<span class="emphasis">*indexbyte2*</span>. The run-time constant pool
entry at the index must be a symbolic reference to a method or an
interface method (<a href="jvms-5.html#jvms-5.1" class="xref"
title="5.1. The Run-Time Constant Pool">§5.1</a>), which gives the name
and descriptor (<a href="jvms-4.html#jvms-4.3.3" class="xref"
title="4.3.3. Method Descriptors">§4.3.3</a>) of the method or interface
method as well as a symbolic reference to the class or interface in
which the method or interface method is to be found. The named method is
resolved (<a href="jvms-5.html#jvms-5.4.3.3" class="xref"
title="5.4.3.3. Method Resolution">§5.4.3.3</a>,
<a href="jvms-5.html#jvms-5.4.3.4" class="xref"
title="5.4.3.4. Interface Method Resolution">§5.4.3.4</a>).

If all of the following are true, let <span class="type">C</span> be the
direct superclass of the current class:

<div class="norm">

- The resolved method is not an instance initialization method
  (<a href="jvms-2.html#jvms-2.9.1" class="xref"
  title="2.9.1. Instance Initialization Methods">§2.9.1</a>).

- The symbolic reference names a class (not an interface), and that
  class is a superclass of the current class.

- The `ACC_SUPER` flag is set for the `class` file
  (<a href="jvms-4.html#jvms-4.1" class="xref"
  title="4.1. The ClassFile Structure">§4.1</a>).

</div>

Otherwise, let <span class="type">C</span> be the class or interface
named by the symbolic reference.

The actual method to be invoked is selected by the following lookup
procedure:

<div class="orderedlist">

1.  If <span class="type">C</span> contains a declaration for an
    instance method with the same name and descriptor as the resolved
    method, then it is the method to be invoked.

2.  Otherwise, if <span class="type">C</span> is a class and has a
    superclass, a search for a declaration of an instance method with
    the same name and descriptor as the resolved method is performed,
    starting with the direct superclass of <span class="type">C</span>
    and continuing with the direct superclass of that class, and so
    forth, until a match is found or no further superclasses exist. If a
    match is found, then it is the method to be invoked.

3.  Otherwise, if <span class="type">C</span> is an interface and the
    class `Object` contains a declaration of a `public` instance method
    with the same name and descriptor as the resolved method, then it is
    the method to be invoked.

4.  Otherwise, if there is exactly one maximally-specific method
    (<a href="jvms-5.html#jvms-5.4.3.3" class="xref"
    title="5.4.3.3. Method Resolution">§5.4.3.3</a>) in the
    superinterfaces of <span class="type">C</span> that matches the
    resolved method's name and descriptor and is not `abstract`, then it
    is the method to be invoked.

</div>

The <span class="emphasis">*objectref*</span> must be of type
`reference` and must be followed on the operand stack by
<span class="emphasis">*nargs*</span> argument values, where the number,
type, and order of the values must be consistent with the descriptor of
the selected instance method.

If the method is `synchronized`, the monitor associated with
<span class="emphasis">*objectref*</span> is entered or reentered as if
by execution of a <span class="emphasis">*monitorenter*</span>
instruction (<a href="jvms-6.html#jvms-6.5.monitorenter" class="xref"
title="monitorenter">§<span
class="emphasis"><em>monitorenter</em></span></a>) in the current
thread.

If the method is not `native`, the <span class="emphasis">*nargs*</span>
argument values and <span class="emphasis">*objectref*</span> are popped
from the operand stack. A new frame is created on the Java Virtual
Machine stack for the method being invoked. The
<span class="emphasis">*objectref*</span> and the argument values are
consecutively made the values of local variables of the new frame, with
<span class="emphasis">*objectref*</span> in local variable 0,
<span class="emphasis">*arg1*</span> in local variable 1 (or, if
<span class="emphasis">*arg1*</span> is of type `long` or `double`, in
local variables 1 and 2), and so on. The new frame is then made current,
and the Java Virtual Machine `pc` is set to the opcode of the first
instruction of the method to be invoked. Execution continues with the
first instruction of the method.

If the method is `native` and the platform-dependent code that
implements it has not yet been bound
(<a href="jvms-5.html#jvms-5.6" class="xref"
title="5.6. Binding Native Method Implementations">§5.6</a>) into the
Java Virtual Machine, that is done. The
<span class="emphasis">*nargs*</span> argument values and
<span class="emphasis">*objectref*</span> are popped from the operand
stack and are passed as parameters to the code that implements the
method. The parameters are passed and the code is invoked in an
implementation-dependent manner. When the platform-dependent code
returns, the following take place:

<div class="norm">

- If the `native` method is `synchronized`, the monitor associated with
  <span class="emphasis">*objectref*</span> is updated and possibly
  exited as if by execution of a
  <span class="emphasis">*monitorexit*</span> instruction
  (<a href="jvms-6.html#jvms-6.5.monitorexit" class="xref"
  title="monitorexit">§<span
  class="emphasis"><em>monitorexit</em></span></a>) in the current
  thread.

- If the `native` method returns a value, the return value of the
  platform-dependent code is converted in an implementation-dependent
  way to the return type of the `native` method and pushed onto the
  operand stack.

</div>

</div>

<div id="jvms-6.5.invokespecial.linking" class="section">

<div class="titlepage">

<div>

<div>

#### Linking Exceptions

</div>

</div>

</div>

During resolution of the symbolic reference to the method, any of the
exceptions pertaining to method resolution
(<a href="jvms-5.html#jvms-5.4.3.3" class="xref"
title="5.4.3.3. Method Resolution">§5.4.3.3</a>) can be thrown.

Otherwise, if the resolved method is an instance initialization method,
and the class in which it is declared is not the class symbolically
referenced by the instruction, a `NoSuchMethodError` is thrown.

Otherwise, if the resolved method is a class (`static`) method, the
<span class="emphasis">*invokespecial*</span> instruction throws an
`IncompatibleClassChangeError`.

</div>

<div id="jvms-6.5.invokespecial.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

Otherwise, if <span class="emphasis">*objectref*</span> is `null`, the
<span class="emphasis">*invokespecial*</span> instruction throws a
`NullPointerException`.

Otherwise, if step 1, step 2, or step 3 of the lookup procedure selects
an `abstract` method, <span class="emphasis">*invokespecial*</span>
throws an `AbstractMethodError`.

Otherwise, if step 1, step 2, or step 3 of the lookup procedure selects
a `native` method and the code that implements the method cannot be
bound, <span class="emphasis">*invokespecial*</span> throws an
`UnsatisfiedLinkError`.

Otherwise, if step 4 of the lookup procedure determines there are
multiple maximally-specific superinterface methods of
<span class="type">C</span> that match the resolved method's name and
descriptor and are not `abstract`,
<span class="emphasis">*invokespecial*</span> throws an
`IncompatibleClassChangeError`

Otherwise, if step 4 of the lookup procedure determines there are no
maximally-specific superinterface methods of <span class="type">C</span>
that match the resolved method's name and descriptor and are not
`abstract`, <span class="emphasis">*invokespecial*</span> throws an
`AbstractMethodError`.

</div>

<div id="jvms-6.5.invokespecial.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The difference between the <span class="emphasis">*invokespecial*</span>
instruction and the <span class="emphasis">*invokevirtual*</span>
instruction (<a href="jvms-6.html#jvms-6.5.invokevirtual" class="xref"
title="invokevirtual">§<span
class="emphasis"><em>invokevirtual</em></span></a>) is that
<span class="emphasis">*invokevirtual*</span> invokes a method based on
the class of the object. The
<span class="emphasis">*invokespecial*</span> instruction is used to
directly invoke instance initialization methods
(<a href="jvms-2.html#jvms-2.9.1" class="xref"
title="2.9.1. Instance Initialization Methods">§2.9.1</a>) as well as
methods of the current class and its supertypes.

The <span class="emphasis">*invokespecial*</span> instruction was named
`invokenonvirtual` prior to JDK release 1.0.2.

The <span class="emphasis">*nargs*</span> argument values and
<span class="emphasis">*objectref*</span> are not one-to-one with the
first <span class="emphasis">*nargs*</span>+1 local variables. Argument
values of types `long` and `double` must be stored in two consecutive
local variables, thus more than <span class="emphasis">*nargs*</span>
local variables may be required to pass
<span class="emphasis">*nargs*</span> argument values to the invoked
method.

The <span class="emphasis">*invokespecial*</span> instruction handles
invocation of a non-`abstract` interface method, referenced either via a
direct superinterface or via a superclass. In these cases, the rules for
selection are essentially the same as those for
<span class="emphasis">*invokeinterface*</span> (except that the search
starts from a different class).

</div>

</div>

<div id="jvms-6.5.invokestatic" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*invokestatic*</span>

</div>

</div>

</div>

<div id="d5e21583" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Invoke a class (`static`) method

</div>

<div id="d5e21587" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*invokestatic*</span>  
<span class="emphasis">*indexbyte1*</span>  
<span class="emphasis">*indexbyte2*</span>  

</div>

</div>

<div id="d5e21593" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*invokestatic*</span> = 184 (0xb8)

</div>

<div id="d5e21597" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., \[<span class="emphasis">*arg1*</span>,
\[<span class="emphasis">*arg2*</span> ...\]\]
<span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.invokestatic.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The unsigned <span class="emphasis">*indexbyte1*</span> and
<span class="emphasis">*indexbyte2*</span> are used to construct an
index into the run-time constant pool of the current class
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>),
where the value of the index is
(<span class="emphasis">*indexbyte1*</span> `<<` 8) \|
<span class="emphasis">*indexbyte2*</span>. The run-time constant pool
entry at the index must be a symbolic reference to a method or an
interface method (<a href="jvms-5.html#jvms-5.1" class="xref"
title="5.1. The Run-Time Constant Pool">§5.1</a>), which gives the name
and descriptor (<a href="jvms-4.html#jvms-4.3.3" class="xref"
title="4.3.3. Method Descriptors">§4.3.3</a>) of the method or interface
method as well as a symbolic reference to the class or interface in
which the method or interface method is to be found. The named method is
resolved (<a href="jvms-5.html#jvms-5.4.3.3" class="xref"
title="5.4.3.3. Method Resolution">§5.4.3.3</a>,
<a href="jvms-5.html#jvms-5.4.3.4" class="xref"
title="5.4.3.4. Interface Method Resolution">§5.4.3.4</a>).

The resolved method must not be an instance initialization method, or
the class or interface initialization method
(<a href="jvms-2.html#jvms-2.9.1" class="xref"
title="2.9.1. Instance Initialization Methods">§2.9.1</a>,
<a href="jvms-2.html#jvms-2.9.2" class="xref"
title="2.9.2. Class Initialization Methods">§2.9.2</a>).

The resolved method must be `static`, and therefore cannot be
`abstract`.

On successful resolution of the method, the class or interface that
declared the resolved method is initialized if that class or interface
has not already been initialized
(<a href="jvms-5.html#jvms-5.5" class="xref"
title="5.5. Initialization">§5.5</a>).

The operand stack must contain <span class="emphasis">*nargs*</span>
argument values, where the number, type, and order of the values must be
consistent with the descriptor of the resolved method.

If the method is `synchronized`, the monitor associated with the
resolved `Class` object is entered or reentered as if by execution of a
<span class="emphasis">*monitorenter*</span> instruction
(<a href="jvms-6.html#jvms-6.5.monitorenter" class="xref"
title="monitorenter">§<span
class="emphasis"><em>monitorenter</em></span></a>) in the current
thread.

If the method is not `native`, the <span class="emphasis">*nargs*</span>
argument values are popped from the operand stack. A new frame is
created on the Java Virtual Machine stack for the method being invoked.
The <span class="emphasis">*nargs*</span> argument values are
consecutively made the values of local variables of the new frame, with
<span class="emphasis">*arg1*</span> in local variable 0 (or, if
<span class="emphasis">*arg1*</span> is of type `long` or `double`, in
local variables 0 and 1) and so on. The new frame is then made current,
and the Java Virtual Machine `pc` is set to the opcode of the first
instruction of the method to be invoked. Execution continues with the
first instruction of the method.

If the method is `native` and the platform-dependent code that
implements it has not yet been bound
(<a href="jvms-5.html#jvms-5.6" class="xref"
title="5.6. Binding Native Method Implementations">§5.6</a>) into the
Java Virtual Machine, that is done. The
<span class="emphasis">*nargs*</span> argument values are popped from
the operand stack and are passed as parameters to the code that
implements the method. The parameters are passed and the code is invoked
in an implementation-dependent manner. When the platform-dependent code
returns, the following take place:

<div class="norm">

- If the `native` method is `synchronized`, the monitor associated with
  the resolved `Class` object is updated and possibly exited as if by
  execution of a <span class="emphasis">*monitorexit*</span> instruction
  (<a href="jvms-6.html#jvms-6.5.monitorexit" class="xref"
  title="monitorexit">§<span
  class="emphasis"><em>monitorexit</em></span></a>) in the current
  thread.

- If the `native` method returns a value, the return value of the
  platform-dependent code is converted in an implementation-dependent
  way to the return type of the `native` method and pushed onto the
  operand stack.

</div>

</div>

<div id="jvms-6.5.invokestatic.linking" class="section">

<div class="titlepage">

<div>

<div>

#### Linking Exceptions

</div>

</div>

</div>

During resolution of the symbolic reference to the method, any of the
exceptions pertaining to method resolution
(<a href="jvms-5.html#jvms-5.4.3.3" class="xref"
title="5.4.3.3. Method Resolution">§5.4.3.3</a>) can be thrown.

Otherwise, if the resolved method is an instance method, the
<span class="emphasis">*invokestatic*</span> instruction throws an
`IncompatibleClassChangeError`.

</div>

<div id="jvms-6.5.invokestatic.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

Otherwise, if execution of this
<span class="emphasis">*invokestatic*</span> instruction causes
initialization of the referenced class or interface,
<span class="emphasis">*invokestatic*</span> may throw an `Error` as
detailed in <a href="jvms-5.html#jvms-5.5" class="xref"
title="5.5. Initialization">§5.5</a>.

Otherwise, if the resolved method is `native` and the code that
implements the method cannot be bound,
<span class="emphasis">*invokestatic*</span> throws an
`UnsatisfiedLinkError`.

</div>

<div id="jvms-6.5.invokestatic.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*nargs*</span> argument values are not
one-to-one with the first <span class="emphasis">*nargs*</span> local
variables. Argument values of types `long` and `double` must be stored
in two consecutive local variables, thus more than
<span class="emphasis">*nargs*</span> local variables may be required to
pass <span class="emphasis">*nargs*</span> argument values to the
invoked method.

</div>

</div>

<div id="jvms-6.5.invokevirtual" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*invokevirtual*</span>

</div>

</div>

</div>

<div id="d5e21687" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Invoke instance method; dispatch based on class

</div>

<div id="d5e21690" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*invokevirtual*</span>  
<span class="emphasis">*indexbyte1*</span>  
<span class="emphasis">*indexbyte2*</span>  

</div>

</div>

<div id="d5e21696" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*invokevirtual*</span> = 182 (0xb6)

</div>

<div id="d5e21700" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*objectref*</span>,
\[<span class="emphasis">*arg1*</span>,
\[<span class="emphasis">*arg2*</span> ...\]\]
<span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.invokevirtual.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The unsigned <span class="emphasis">*indexbyte1*</span> and
<span class="emphasis">*indexbyte2*</span> are used to construct an
index into the run-time constant pool of the current class
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>),
where the value of the index is
(<span class="emphasis">*indexbyte1*</span> `<<` 8) \|
<span class="emphasis">*indexbyte2*</span>. The run-time constant pool
entry at the index must be a symbolic reference to a method
(<a href="jvms-5.html#jvms-5.1" class="xref"
title="5.1. The Run-Time Constant Pool">§5.1</a>), which gives the name
and descriptor (<a href="jvms-4.html#jvms-4.3.3" class="xref"
title="4.3.3. Method Descriptors">§4.3.3</a>) of the method as well as a
symbolic reference to the class in which the method is to be found. The
named method is resolved
(<a href="jvms-5.html#jvms-5.4.3.3" class="xref"
title="5.4.3.3. Method Resolution">§5.4.3.3</a>).

<span class="emphasis">*If the resolved method is not signature
polymorphic*</span> (<a href="jvms-2.html#jvms-2.9.3" class="xref"
title="2.9.3. Signature Polymorphic Methods">§2.9.3</a>), then the
<span class="emphasis">*invokevirtual*</span> instruction proceeds as
follows.

Let <span class="type">C</span> be the class of
<span class="emphasis">*objectref*</span>. A method is selected with
respect to <span class="type">C</span> and the resolved method
(<a href="jvms-5.html#jvms-5.4.6" class="xref"
title="5.4.6. Method Selection">§5.4.6</a>). This is the
<span class="emphasis">*method to be invoked*</span>.

The <span class="emphasis">*objectref*</span> must be followed on the
operand stack by <span class="emphasis">*nargs*</span> argument values,
where the number, type, and order of the values must be consistent with
the descriptor of the selected instance method.

If the method to be invoked is `synchronized`, the monitor associated
with <span class="emphasis">*objectref*</span> is entered or reentered
as if by execution of a <span class="emphasis">*monitorenter*</span>
instruction (<a href="jvms-6.html#jvms-6.5.monitorenter" class="xref"
title="monitorenter">§<span
class="emphasis"><em>monitorenter</em></span></a>) in the current
thread.

If the method to be invoked is not `native`, the
<span class="emphasis">*nargs*</span> argument values and
<span class="emphasis">*objectref*</span> are popped from the operand
stack. A new frame is created on the Java Virtual Machine stack for the
method being invoked. The <span class="emphasis">*objectref*</span> and
the argument values are consecutively made the values of local variables
of the new frame, with <span class="emphasis">*objectref*</span> in
local variable 0, <span class="emphasis">*arg1*</span> in local variable
1 (or, if <span class="emphasis">*arg1*</span> is of type `long` or
`double`, in local variables 1 and 2), and so on. The new frame is then
made current, and the Java Virtual Machine `pc` is set to the opcode of
the first instruction of the method to be invoked. Execution continues
with the first instruction of the method.

If the method to be invoked is `native` and the platform-dependent code
that implements it has not yet been bound
(<a href="jvms-5.html#jvms-5.6" class="xref"
title="5.6. Binding Native Method Implementations">§5.6</a>) into the
Java Virtual Machine, that is done. The
<span class="emphasis">*nargs*</span> argument values and
<span class="emphasis">*objectref*</span> are popped from the operand
stack and are passed as parameters to the code that implements the
method. The parameters are passed and the code is invoked in an
implementation-dependent manner. When the platform-dependent code
returns, the following take place:

<div class="norm">

- If the `native` method is `synchronized`, the monitor associated with
  <span class="emphasis">*objectref*</span> is updated and possibly
  exited as if by execution of a
  <span class="emphasis">*monitorexit*</span> instruction
  (<a href="jvms-6.html#jvms-6.5.monitorexit" class="xref"
  title="monitorexit">§<span
  class="emphasis"><em>monitorexit</em></span></a>) in the current
  thread.

- If the `native` method returns a value, the return value of the
  platform-dependent code is converted in an implementation-dependent
  way to the return type of the `native` method and pushed onto the
  operand stack.

</div>

<span class="emphasis">*If the resolved method is signature
polymorphic*</span> (<a href="jvms-2.html#jvms-2.9.3" class="xref"
title="2.9.3. Signature Polymorphic Methods">§2.9.3</a>),
<span class="emphasis">*and declared in the
`java.lang.invoke.MethodHandle` class*</span>, then the
<span class="emphasis">*invokevirtual*</span> instruction proceeds as
follows, where <span class="type">D</span> is the descriptor of the
method symbolically referenced by the instruction.

First, a `reference` to an instance of `java.lang.invoke.MethodType` is
obtained as if by resolution of a symbolic reference to a method type
(<a href="jvms-5.html#jvms-5.4.3.5" class="xref"
title="5.4.3.5. Method Type and Method Handle Resolution">§5.4.3.5</a>)
with the same parameter and return types as <span class="type">D</span>.

<div class="norm">

- If the named method is `invokeExact`, the instance of
  `java.lang.invoke.MethodType` must be semantically equal to the type
  descriptor of the receiving method handle
  <span class="emphasis">*objectref*</span>. The
  <span class="emphasis">*method handle to be invoked*</span> is
  <span class="emphasis">*objectref*</span>.

- If the named method is `invoke`, and the instance of
  `java.lang.invoke.MethodType` is semantically equal to the type
  descriptor of the receiving method handle
  <span class="emphasis">*objectref*</span>, then the
  <span class="emphasis">*method handle to be invoked*</span> is
  <span class="emphasis">*objectref*</span>.

- If the named method is `invoke`, and the instance of
  `java.lang.invoke.MethodType` is not semantically equal to the type
  descriptor of the receiving method handle
  <span class="emphasis">*objectref*</span>, then the Java Virtual
  Machine attempts to adjust the type descriptor of the receiving method
  handle, as if by invocation of the `asType` method of
  `java.lang.invoke.MethodHandle`, to obtain an exactly invokable method
  handle `m`. The <span class="emphasis">*method handle to be
  invoked*</span> is `m`.

</div>

The <span class="emphasis">*objectref*</span> must be followed on the
operand stack by <span class="emphasis">*nargs*</span> argument values,
where the number, type, and order of the values must be consistent with
the type descriptor of the method handle to be invoked. (This type
descriptor will correspond to the method descriptor appropriate for the
kind of the method handle to be invoked, as specified in
<a href="jvms-5.html#jvms-5.4.3.5" class="xref"
title="5.4.3.5. Method Type and Method Handle Resolution">§5.4.3.5</a>.)

Then, if the method handle to be invoked has bytecode behavior, the Java
Virtual Machine invokes the method handle as if by execution of the
bytecode behavior associated with the method handle's kind. If the kind
is 5 (`REF_invokeVirtual`), 6 (`REF_invokeStatic`), 7
(`REF_invokeSpecial`), 8 (`REF_newInvokeSpecial`), or 9
(`REF_invokeInterface`), then a frame will be created and made current
<span class="emphasis">*in the course of executing the bytecode
behavior*</span>; however, this frame is not visible, and when the
method invoked by the bytecode behavior completes (normally or
abruptly), the <span class="emphasis">*frame of its invoker*</span> is
considered to be the frame for the method containing this
<span class="emphasis">*invokevirtual*</span> instruction.

Otherwise, if the method handle to be invoked has no bytecode behavior,
the Java Virtual Machine invokes it in an implementation-dependent
manner.

<span class="emphasis">*If the resolved method is signature polymorphic
and declared in the `java.lang.invoke.VarHandle` class*</span>, then the
<span class="emphasis">*invokevirtual*</span> instruction proceeds as
follows, where `N` and <span class="type">D</span> are the name and
descriptor of the method symbolically referenced by the instruction.

First, a `reference` to an instance of
`java.lang.invoke.VarHandle.AccessMode` is obtained as if by invocation
of the `valueFromMethodName` method of
`java.lang.invoke.VarHandle.AccessMode` with a `String` argument
denoting `N`.

Second, a `reference` to an instance of `java.lang.invoke.MethodType` is
obtained as if by invocation of the `accessModeType` method of
`java.lang.invoke.VarHandle` on the instance
<span class="emphasis">*objectref*</span>, with the instance of
`java.lang.invoke.VarHandle.AccessMode` as the argument.

Third, a `reference` to an instance of `java.lang.invoke.MethodHandle`
is obtained as if by invocation of the `varHandleExactInvoker` method of
`java.lang.invoke.MethodHandles` with the instance of
`java.lang.invoke.VarHandle.AccessMode` as the first argument and the
instance of `java.lang.invoke.MethodType` as the second argument. The
resulting instance is called the <span class="emphasis">*invoker method
handle*</span>.

Finally, the <span class="emphasis">*nargs*</span> argument values and
<span class="emphasis">*objectref*</span> are popped from the operand
stack, and the invoker method handle is invoked. The invocation occurs
as if by execution of an <span class="emphasis">*invokevirtual*</span>
instruction that indicates a run-time constant pool index to a symbolic
reference <span class="type">R</span> where:

<div class="norm">

- <span class="type">R</span> is a symbolic reference to a method of a
  class;

- for the symbolic reference to the class in which the method is to be
  found, <span class="type">R</span> specifies
  `java.lang.invoke.MethodHandle`;

- for the name of the method, <span class="type">R</span> specifies
  `invoke`;

- for the descriptor of the method, <span class="type">R</span>
  specifies a return type indicated by the return descriptor of
  <span class="type">D</span>, and specifies a first parameter type of
  `java.lang.invoke.VarHandle` followed by the parameter types indicated
  by the parameter descriptors of <span class="type">D</span> (if any)
  in order.

</div>

and where it is as if the following items were pushed, in order, onto
the operand stack:

<div class="norm">

- a `reference` to the instance of `java.lang.invoke.MethodHandle` (the
  invoker method handle);

- <span class="emphasis">*objectref*</span>;

- the <span class="emphasis">*nargs*</span> argument values, where the
  number, type, and order of the values must be consistent with the type
  descriptor of the invoker method handle.

</div>

</div>

<div id="jvms-6.5.invokevirtual.linking" class="section">

<div class="titlepage">

<div>

<div>

#### Linking Exceptions

</div>

</div>

</div>

During resolution of the symbolic reference to the method, any of the
exceptions pertaining to method resolution
(<a href="jvms-5.html#jvms-5.4.3.3" class="xref"
title="5.4.3.3. Method Resolution">§5.4.3.3</a>) can be thrown.

Otherwise, if the resolved method is a class (`static`) method, the
<span class="emphasis">*invokevirtual*</span> instruction throws an
`IncompatibleClassChangeError`.

Otherwise, if the resolved method is signature polymorphic and declared
in the `java.lang.invoke.MethodHandle` class, then during resolution of
the method type derived from the descriptor in the symbolic reference to
the method, any of the exceptions pertaining to method type resolution
(<a href="jvms-5.html#jvms-5.4.3.5" class="xref"
title="5.4.3.5. Method Type and Method Handle Resolution">§5.4.3.5</a>)
can be thrown.

Otherwise, if the resolved method is signature polymorphic and declared
in the `java.lang.invoke.VarHandle` class, then any linking exception
that may arise from invocation of the invoker method handle can be
thrown. No linking exceptions are thrown from invocation of the
`valueFromMethodName`, `accessModeType`, and `varHandleExactInvoker`
methods.

</div>

<div id="jvms-6.5.invokevirtual.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

Otherwise, if <span class="emphasis">*objectref*</span> is `null`, the
<span class="emphasis">*invokevirtual*</span> instruction throws a
`NullPointerException`.

Otherwise, if the resolved method is not signature polymorphic:

<div class="norm">

- If the selected method is `abstract`,
  <span class="emphasis">*invokevirtual*</span> throws an
  `AbstractMethodError`.

- Otherwise, if the selected method is `native` and the code that
  implements the method cannot be bound,
  <span class="emphasis">*invokevirtual*</span> throws an
  `UnsatisfiedLinkError`.

- Otherwise, if no method is selected, and there are multiple
  maximally-specific superinterface methods of
  <span class="type">C</span> that match the resolved method's name and
  descriptor and are not `abstract`,
  <span class="emphasis">*invokevirtual*</span> throws an
  `IncompatibleClassChangeError`

- Otherwise, if no method is selected, and there are no
  maximally-specific superinterface methods of
  <span class="type">C</span> that match the resolved method's name and
  descriptor and are not `abstract`,
  <span class="emphasis">*invokevirtual*</span> throws an
  `AbstractMethodError`.

</div>

Otherwise, if the resolved method is signature polymorphic and declared
in the `java.lang.invoke.MethodHandle` class, then:

<div class="norm">

- If the method name is `invokeExact`, and the obtained instance of
  `java.lang.invoke.MethodType` is not semantically equal to the type
  descriptor of the receiving method handle
  <span class="emphasis">*objectref*</span>, the
  <span class="emphasis">*invokevirtual*</span> instruction throws a
  `java.lang.invoke.WrongMethodTypeException`.

- If the method name is `invoke`, and the obtained instance of
  `java.lang.invoke.MethodType` is not a valid argument to the `asType`
  method of `java.lang.invoke.MethodHandle` invoked on the receiving
  method handle <span class="emphasis">*objectref*</span>, the
  <span class="emphasis">*invokevirtual*</span> instruction throws a
  `java.lang.invoke.WrongMethodTypeException`.

</div>

Otherwise, if the resolved method is signature polymorphic and declared
in the `java.lang.invoke.VarHandle` class, then any run-time exception
that may arise from invocation of the invoker method handle can be
thrown. No run-time exceptions are thrown from invocation of the
`valueFromMethodName`, `accessModeType`, and `varHandleExactInvoker`
methods, except `NullPointerException` if
<span class="emphasis">*objectref*</span> is `null`.

</div>

<div id="jvms-6.5.invokevirtual.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*nargs*</span> argument values and
<span class="emphasis">*objectref*</span> are not one-to-one with the
first <span class="emphasis">*nargs*</span>+1 local variables. Argument
values of types `long` and `double` must be stored in two consecutive
local variables, thus more than <span class="emphasis">*nargs*</span>
local variables may be required to pass
<span class="emphasis">*nargs*</span> argument values to the invoked
method.

It is possible that the symbolic reference of an
<span class="emphasis">*invokevirtual*</span> instruction resolves to an
interface method. In this case, it is possible that there is no
overriding method in the class hierarchy, but that a non-`abstract`
interface method matches the resolved method's descriptor. The selection
logic matches such a method, using the same rules as for
<span class="emphasis">*invokeinterface*</span>.

</div>

</div>

<div id="jvms-6.5.ior" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*ior*</span>

</div>

</div>

</div>

<div id="d5e21971" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Bitwise OR `int`

</div>

<div id="d5e21975" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*ior*</span>  

</div>

</div>

<div id="d5e21979" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*ior*</span> = 128 (0x80)

</div>

<div id="d5e21983" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.ior.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `int`. They are
popped from the operand stack. An `int`
<span class="emphasis">*result*</span> is calculated by taking the
bitwise inclusive OR of <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

</div>

</div>

<div id="jvms-6.5.irem" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*irem*</span>

</div>

</div>

</div>

<div id="d5e22005" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Remainder `int`

</div>

<div id="d5e22009" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*irem*</span>  

</div>

</div>

<div id="d5e22013" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*irem*</span> = 112 (0x70)

</div>

<div id="d5e22017" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.irem.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `int`. The values
are popped from the operand stack. The `int`
<span class="emphasis">*result*</span> is
<span class="emphasis">*value1*</span> -
(<span class="emphasis">*value1*</span> /
<span class="emphasis">*value2*</span>) \*
<span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

The result of the <span class="emphasis">*irem*</span> instruction is
such that `(a/b)*b + (a%b)` is equal to `a`. This identity holds even in
the special case in which the dividend is the negative `int` of largest
possible magnitude for its type and the divisor is -1 (the remainder is
0). It follows from this rule that the result of the remainder operation
can be negative only if the dividend is negative and can be positive
only if the dividend is positive. Moreover, the magnitude of the result
is always less than the magnitude of the divisor.

</div>

<div id="jvms-6.5.irem.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exception

</div>

</div>

</div>

If the value of the divisor for an `int` remainder operator is 0,
<span class="emphasis">*irem*</span> throws an `ArithmeticException`.

</div>

</div>

<div id="jvms-6.5.ireturn" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*ireturn*</span>

</div>

</div>

</div>

<div id="d5e22052" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Return `int` from method

</div>

<div id="d5e22056" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*ireturn*</span>  

</div>

</div>

<div id="d5e22060" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*ireturn*</span> = 172 (0xac)

</div>

<div id="d5e22064" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

\[empty\]

</div>

<div id="jvms-6.5.ireturn.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The current method must have return type `boolean`, `byte`, `char`,
`short`, or `int`. The <span class="emphasis">*value*</span> must be of
type `int`. If the current method is a `synchronized` method, the
monitor entered or reentered on invocation of the method is updated and
possibly exited as if by execution of a
<span class="emphasis">*monitorexit*</span> instruction
(<a href="jvms-6.html#jvms-6.5.monitorexit" class="xref"
title="monitorexit">§<span
class="emphasis"><em>monitorexit</em></span></a>) in the current thread.
If no exception is thrown, <span class="emphasis">*value*</span> is
popped from the operand stack of the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>)
and pushed onto the operand stack of the frame of the invoker. Any other
values on the operand stack of the current method are discarded.

Prior to pushing <span class="emphasis">*value*</span> onto the operand
stack of the frame of the invoker, it may have to be converted. If the
return type of the invoked method was `byte`, `char`, or `short`, then
<span class="emphasis">*value*</span> is converted from `int` to the
return type as if by execution of <span class="emphasis">*i2b*</span>,
<span class="emphasis">*i2c*</span>, or
<span class="emphasis">*i2s*</span>, respectively. If the return type of
the invoked method was `boolean`, then
<span class="emphasis">*value*</span> is narrowed from `int` to
`boolean` by taking the bitwise AND of
<span class="emphasis">*value*</span> and 1.

The interpreter then returns control to the invoker of the method,
reinstating the frame of the invoker.

</div>

<div id="jvms-6.5.ireturn.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

If the Java Virtual Machine implementation does not enforce the rules on
structured locking described in
<a href="jvms-2.html#jvms-2.11.10" class="xref"
title="2.11.10. Synchronization">§2.11.10</a>, then if the current
method is a `synchronized` method and the current thread is not the
owner of the monitor entered or reentered on invocation of the method,
<span class="emphasis">*ireturn*</span> throws an
`IllegalMonitorStateException`. This can happen, for example, if a
`synchronized` method contains a
<span class="emphasis">*monitorexit*</span> instruction, but no
<span class="emphasis">*monitorenter*</span> instruction, on the object
on which the method is synchronized.

Otherwise, if the Java Virtual Machine implementation enforces the rules
on structured locking described in
<a href="jvms-2.html#jvms-2.11.10" class="xref"
title="2.11.10. Synchronization">§2.11.10</a> and if the first of those
rules is violated during invocation of the current method, then
<span class="emphasis">*ireturn*</span> throws an
`IllegalMonitorStateException`.

</div>

</div>

<div id="jvms-6.5.ishl" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*ishl*</span>

</div>

</div>

</div>

<div id="d5e22118" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Shift left `int`

</div>

<div id="d5e22122" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*ishl*</span>  

</div>

</div>

<div id="d5e22126" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*ishl*</span> = 120 (0x78)

</div>

<div id="d5e22130" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.ishl.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `int`. The values
are popped from the operand stack. An `int`
<span class="emphasis">*result*</span> is calculated by shifting
<span class="emphasis">*value1*</span> left by
<span class="emphasis">*s*</span> bit positions, where
<span class="emphasis">*s*</span> is the value of the low 5 bits of
<span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

</div>

<div id="jvms-6.5.ishl.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

This is equivalent (even if overflow occurs) to multiplication by 2 to
the power <span class="emphasis">*s*</span>. The shift distance actually
used is always in the range 0 to 31, inclusive, as if
<span class="emphasis">*value2*</span> were subjected to a bitwise
logical AND with the mask value 0x1f.

</div>

</div>

<div id="jvms-6.5.ishr" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*ishr*</span>

</div>

</div>

</div>

<div id="d5e22159" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Arithmetic shift right `int`

</div>

<div id="d5e22163" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*ishr*</span>  

</div>

</div>

<div id="d5e22167" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*ishr*</span> = 122 (0x7a)

</div>

<div id="d5e22171" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.ishr.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `int`. The values
are popped from the operand stack. An `int`
<span class="emphasis">*result*</span> is calculated by shifting
<span class="emphasis">*value1*</span> right by
<span class="emphasis">*s*</span> bit positions, with sign extension,
where <span class="emphasis">*s*</span> is the value of the low 5 bits
of <span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

</div>

<div id="jvms-6.5.ishr.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The resulting value is
<span class="emphasis">*floor*</span>(<span class="emphasis">*value1*</span>
/ 2<sup><span class="emphasis">*s*</span></sup>), where
<span class="emphasis">*s*</span> is
<span class="emphasis">*value2*</span> & 0x1f. For non-negative
<span class="emphasis">*value1*</span>, this is equivalent to truncating
`int` division by 2 to the power <span class="emphasis">*s*</span>. The
shift distance actually used is always in the range 0 to 31, inclusive,
as if <span class="emphasis">*value2*</span> were subjected to a bitwise
logical AND with the mask value 0x1f.

</div>

</div>

<div id="jvms-6.5.istore" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*istore*</span>

</div>

</div>

</div>

<div id="d5e22208" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Store `int` into local variable

</div>

<div id="d5e22212" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*istore*</span>  
<span class="emphasis">*index*</span>  

</div>

</div>

<div id="d5e22217" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*istore*</span> = 54 (0x36)

</div>

<div id="d5e22221" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.istore.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*index*</span> is an unsigned byte that must
be an index into the local variable array of the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>).
The <span class="emphasis">*value*</span> on the top of the operand
stack must be of type `int`. It is popped from the operand stack, and
the value of the local variable at <span class="emphasis">*index*</span>
is set to <span class="emphasis">*value*</span>.

</div>

<div id="jvms-6.5.istore.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*istore*</span> opcode can be used in
conjunction with the <span class="emphasis">*wide*</span> instruction
(<a href="jvms-6.html#jvms-6.5.wide" class="xref" title="wide">§<span
class="emphasis"><em>wide</em></span></a>) to access a local variable
using a two-byte unsigned index.

</div>

</div>

<div id="jvms-6.5.istore_n" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*istore\_\<n\>*</span>

</div>

</div>

</div>

<div id="d5e22245" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Store `int` into local variable

</div>

<div id="d5e22249" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*istore\_\<n\>*</span>  

</div>

</div>

<div id="d5e22253" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*istore_0*</span> = 59 (0x3b)

<span class="emphasis">*istore_1*</span> = 60 (0x3c)

<span class="emphasis">*istore_2*</span> = 61 (0x3d)

<span class="emphasis">*istore_3*</span> = 62 (0x3e)

</div>

<div id="d5e22263" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.istore_n.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The \<<span class="emphasis">*n*</span>\> must be an index into the
local variable array of the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>).
The <span class="emphasis">*value*</span> on the top of the operand
stack must be of type `int`. It is popped from the operand stack, and
the value of the local variable at \<<span class="emphasis">*n*</span>\>
is set to <span class="emphasis">*value*</span>.

</div>

<div id="jvms-6.5.istore_n.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

Each of the <span class="emphasis">*istore\_\<n\>*</span> instructions
is the same as <span class="emphasis">*istore*</span> with an
<span class="emphasis">*index*</span> of
\<<span class="emphasis">*n*</span>\>, except that the operand
\<<span class="emphasis">*n*</span>\> is implicit.

</div>

</div>

<div id="jvms-6.5.isub" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*isub*</span>

</div>

</div>

</div>

<div id="d5e22289" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Subtract `int`

</div>

<div id="d5e22293" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*isub*</span>  

</div>

</div>

<div id="d5e22297" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*isub*</span> = 100 (0x64)

</div>

<div id="d5e22301" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.isub.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `int`. The values
are popped from the operand stack. The `int`
<span class="emphasis">*result*</span> is
<span class="emphasis">*value1*</span> -
<span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

For `int` subtraction, `a-b` produces the same result as `a+(-b)`. For
`int` values, subtraction from zero is the same as negation.

The result is the 32 low-order bits of the true mathematical result in a
sufficiently wide two's-complement format, represented as a value of
type `int`. If overflow occurs, then the sign of the result may not be
the same as the sign of the mathematical difference of the two values.

Despite the fact that overflow may occur, execution of an
<span class="emphasis">*isub*</span> instruction never throws a run-time
exception.

</div>

</div>

<div id="jvms-6.5.iushr" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*iushr*</span>

</div>

</div>

</div>

<div id="d5e22332" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Logical shift right `int`

</div>

<div id="d5e22336" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*iushr*</span>  

</div>

</div>

<div id="d5e22340" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*iushr*</span> = 124 (0x7c)

</div>

<div id="d5e22344" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.iushr.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `int`. The values
are popped from the operand stack. An `int`
<span class="emphasis">*result*</span> is calculated by shifting
<span class="emphasis">*value1*</span> right by
<span class="emphasis">*s*</span> bit positions, with zero extension,
where <span class="emphasis">*s*</span> is the value of the low 5 bits
of <span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

</div>

<div id="jvms-6.5.iushr.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

If <span class="emphasis">*value1*</span> is positive and
<span class="emphasis">*s*</span> is
<span class="emphasis">*value2*</span> & 0x1f, the result is the same as
that of <span class="emphasis">*value1*</span> `>>`
<span class="emphasis">*s*</span>; if
<span class="emphasis">*value1*</span> is negative, the result is equal
to the value of the expression (<span class="emphasis">*value1*</span>
`>>` <span class="emphasis">*s*</span>) + (2 `<<`
~<span class="emphasis">*s*</span>). The addition of the (2 `<<`
~<span class="emphasis">*s*</span>) term cancels out the propagated sign
bit. The shift distance actually used is always in the range 0 to 31,
inclusive.

</div>

</div>

<div id="jvms-6.5.ixor" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*ixor*</span>

</div>

</div>

</div>

<div id="d5e22385" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Bitwise XOR `int`

</div>

<div id="d5e22389" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*ixor*</span>  

</div>

</div>

<div id="d5e22393" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*ixor*</span> = 130 (0x82)

</div>

<div id="d5e22397" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.ixor.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `int`. They are
popped from the operand stack. An `int`
<span class="emphasis">*result*</span> is calculated by taking the
bitwise exclusive OR of <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

</div>

</div>

<div id="jvms-6.5.jsr" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*jsr*</span>

</div>

</div>

</div>

<div id="d5e22419" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Jump subroutine

</div>

<div id="d5e22422" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*jsr*</span>  
<span class="emphasis">*branchbyte1*</span>  
<span class="emphasis">*branchbyte2*</span>  

</div>

</div>

<div id="d5e22428" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*jsr*</span> = 168 (0xa8)

</div>

<div id="d5e22432" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

... <span class="symbol">→</span>

..., <span class="emphasis">*address*</span>

</div>

<div id="jvms-6.5.jsr.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*address*</span> of the opcode of the
instruction immediately following this
<span class="emphasis">*jsr*</span> instruction is pushed onto the
operand stack as a value of type `returnAddress`. The unsigned
<span class="emphasis">*branchbyte1*</span> and
<span class="emphasis">*branchbyte2*</span> are used to construct a
signed 16-bit offset, where the offset is
(<span class="emphasis">*branchbyte1*</span> `<<` 8) \|
<span class="emphasis">*branchbyte2*</span>. Execution proceeds at that
offset from the address of this <span class="emphasis">*jsr*</span>
instruction. The target address must be that of an opcode of an
instruction within the method that contains this
<span class="emphasis">*jsr*</span> instruction.

</div>

<div id="jvms-6.5.jsr.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

Note that <span class="emphasis">*jsr*</span> pushes the address onto
the operand stack and <span class="emphasis">*ret*</span>
(<a href="jvms-6.html#jvms-6.5.ret" class="xref" title="ret">§<span
class="emphasis"><em>ret</em></span></a>) gets it out of a local
variable. This asymmetry is intentional.

In Oracle's implementation of a compiler for the Java programming
language prior to Java SE 6, the <span class="emphasis">*jsr*</span>
instruction was used with the <span class="emphasis">*ret*</span>
instruction in the implementation of the `finally` clause
(<a href="jvms-3.html#jvms-3.13" class="xref"
title="3.13. Compiling finally">§3.13</a>,
<a href="jvms-4.html#jvms-4.10.2.5" class="xref"
title="4.10.2.5. Exceptions and finally">§4.10.2.5</a>).

</div>

</div>

<div id="jvms-6.5.jsr_w" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*jsr_w*</span>

</div>

</div>

</div>

<div id="d5e22466" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Jump subroutine (wide index)

</div>

<div id="d5e22469" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*jsr_w*</span>  
<span class="emphasis">*branchbyte1*</span>  
<span class="emphasis">*branchbyte2*</span>  
<span class="emphasis">*branchbyte3*</span>  
<span class="emphasis">*branchbyte4*</span>  

</div>

</div>

<div id="d5e22477" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*jsr_w*</span> = 201 (0xc9)

</div>

<div id="d5e22481" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

... <span class="symbol">→</span>

..., <span class="emphasis">*address*</span>

</div>

<div id="jvms-6.5.jsr_w.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*address*</span> of the opcode of the
instruction immediately following this
<span class="emphasis">*jsr_w*</span> instruction is pushed onto the
operand stack as a value of type `returnAddress`. The unsigned
<span class="emphasis">*branchbyte1*</span>,
<span class="emphasis">*branchbyte2*</span>,
<span class="emphasis">*branchbyte3*</span>, and
<span class="emphasis">*branchbyte4*</span> are used to construct a
signed 32-bit offset, where the offset is
(<span class="emphasis">*branchbyte1*</span> `<<` 24) \|
(<span class="emphasis">*branchbyte2*</span> `<<` 16) \|
(<span class="emphasis">*branchbyte3*</span> `<<` 8) \|
<span class="emphasis">*branchbyte4*</span>. Execution proceeds at that
offset from the address of this <span class="emphasis">*jsr_w*</span>
instruction. The target address must be that of an opcode of an
instruction within the method that contains this
<span class="emphasis">*jsr_w*</span> instruction.

</div>

<div id="jvms-6.5.jsr_w.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

Note that <span class="emphasis">*jsr_w*</span> pushes the address onto
the operand stack and <span class="emphasis">*ret*</span>
(<a href="jvms-6.html#jvms-6.5.ret" class="xref" title="ret">§<span
class="emphasis"><em>ret</em></span></a>) gets it out of a local
variable. This asymmetry is intentional.

In Oracle's implementation of a compiler for the Java programming
language prior to Java SE 6, the <span class="emphasis">*jsr_w*</span>
instruction was used with the <span class="emphasis">*ret*</span>
instruction in the implementation of the `finally` clause
(<a href="jvms-3.html#jvms-3.13" class="xref"
title="3.13. Compiling finally">§3.13</a>,
<a href="jvms-4.html#jvms-4.10.2.5" class="xref"
title="4.10.2.5. Exceptions and finally">§4.10.2.5</a>).

Although the <span class="emphasis">*jsr_w*</span> instruction takes a
4-byte branch offset, other factors limit the size of a method to 65535
bytes (<a href="jvms-4.html#jvms-4.11" class="xref"
title="4.11. Limitations of the Java Virtual Machine">§4.11</a>). This
limit may be raised in a future release of the Java Virtual Machine.

</div>

</div>

<div id="jvms-6.5.l2d" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*l2d*</span>

</div>

</div>

</div>

<div id="d5e22524" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Convert `long` to `double`

</div>

<div id="d5e22529" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*l2d*</span>  

</div>

</div>

<div id="d5e22533" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*l2d*</span> = 138 (0x8a)

</div>

<div id="d5e22537" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.l2d.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*value*</span> on the top of the operand
stack must be of type `long`. It is popped from the operand stack and
converted to a `double` <span class="emphasis">*result*</span> using the
round to nearest rounding policy
(<a href="jvms-2.html#jvms-2.8" class="xref"
title="2.8. Floating-Point Arithmetic">§2.8</a>). The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

</div>

<div id="jvms-6.5.l2d.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*l2d*</span> instruction performs a widening
primitive conversion (JLS §5.1.2) that may lose precision because values
of type `double` have only 53 significand bits.

</div>

</div>

<div id="jvms-6.5.l2f" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*l2f*</span>

</div>

</div>

</div>

<div id="d5e22561" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Convert `long` to `float`

</div>

<div id="d5e22566" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*l2f*</span>  

</div>

</div>

<div id="d5e22570" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*l2f*</span> = 137 (0x89)

</div>

<div id="d5e22574" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.l2f.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*value*</span> on the top of the operand
stack must be of type `long`. It is popped from the operand stack and
converted to a `float` <span class="emphasis">*result*</span> using the
round to nearest rounding policy
(<a href="jvms-2.html#jvms-2.8" class="xref"
title="2.8. Floating-Point Arithmetic">§2.8</a>). The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

</div>

<div id="jvms-6.5.l2f.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*l2f*</span> instruction performs a widening
primitive conversion (JLS §5.1.2) that may lose precision because values
of type `float` have only 24 significand bits.

</div>

</div>

<div id="jvms-6.5.l2i" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*l2i*</span>

</div>

</div>

</div>

<div id="d5e22598" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Convert `long` to `int`

</div>

<div id="d5e22603" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*l2i*</span>  

</div>

</div>

<div id="d5e22607" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*l2i*</span> = 136 (0x88)

</div>

<div id="d5e22611" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.l2i.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*value*</span> on the top of the operand
stack must be of type `long`. It is popped from the operand stack and
converted to an `int` <span class="emphasis">*result*</span> by taking
the low-order 32 bits of the `long` value and discarding the high-order
32 bits. The <span class="emphasis">*result*</span> is pushed onto the
operand stack.

</div>

<div id="jvms-6.5.l2i.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*l2i*</span> instruction performs a narrowing
primitive conversion (JLS §5.1.3). It may lose information about the
overall magnitude of <span class="emphasis">*value*</span>. The
<span class="emphasis">*result*</span> may also not have the same sign
as value.

</div>

</div>

<div id="jvms-6.5.ladd" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*ladd*</span>

</div>

</div>

</div>

<div id="d5e22636" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Add `long`

</div>

<div id="d5e22640" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*ladd*</span>  

</div>

</div>

<div id="d5e22644" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*ladd*</span> = 97 (0x61)

</div>

<div id="d5e22648" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.ladd.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `long`. The
values are popped from the operand stack. The `long`
<span class="emphasis">*result*</span> is
<span class="emphasis">*value1*</span> +
<span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

The result is the 64 low-order bits of the true mathematical result in a
sufficiently wide two's-complement format, represented as a value of
type `long`. If overflow occurs, the sign of the result may not be the
same as the sign of the mathematical sum of the two values.

Despite the fact that overflow may occur, execution of an
<span class="emphasis">*ladd*</span> instruction never throws a run-time
exception.

</div>

</div>

<div id="jvms-6.5.laload" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*laload*</span>

</div>

</div>

</div>

<div id="d5e22674" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Load `long` from array

</div>

<div id="d5e22678" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*laload*</span>  

</div>

</div>

<div id="d5e22682" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*laload*</span> = 47 (0x2f)

</div>

<div id="d5e22686" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*arrayref*</span>,
<span class="emphasis">*index*</span> <span class="symbol">→</span>

..., <span class="emphasis">*value*</span>

</div>

<div id="jvms-6.5.laload.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*arrayref*</span> must be of type `reference`
and must refer to an array whose components are of type `long`. The
<span class="emphasis">*index*</span> must be of type `int`. Both
<span class="emphasis">*arrayref*</span> and
<span class="emphasis">*index*</span> are popped from the operand stack.
The `long` <span class="emphasis">*value*</span> in the component of the
array at <span class="emphasis">*index*</span> is retrieved and pushed
onto the operand stack.

</div>

<div id="jvms-6.5.laload.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

If <span class="emphasis">*arrayref*</span> is `null`,
<span class="emphasis">*laload*</span> throws a `NullPointerException`.

Otherwise, if <span class="emphasis">*index*</span> is not within the
bounds of the array referenced by
<span class="emphasis">*arrayref*</span>, the
<span class="emphasis">*laload*</span> instruction throws an
`ArrayIndexOutOfBoundsException`.

</div>

</div>

<div id="jvms-6.5.land" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*land*</span>

</div>

</div>

</div>

<div id="d5e22722" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Bitwise AND `long`

</div>

<div id="d5e22726" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*land*</span>  

</div>

</div>

<div id="d5e22730" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*land*</span> = 127 (0x7f)

</div>

<div id="d5e22734" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.land.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `long`. They are
popped from the operand stack. A `long`
<span class="emphasis">*result*</span> is calculated by taking the
bitwise AND of <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

</div>

</div>

<div id="jvms-6.5.lastore" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*lastore*</span>

</div>

</div>

</div>

<div id="d5e22756" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Store into `long` array

</div>

<div id="d5e22760" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*lastore*</span>  

</div>

</div>

<div id="d5e22764" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*lastore*</span> = 80 (0x50)

</div>

<div id="d5e22768" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*arrayref*</span>,
<span class="emphasis">*index*</span>,
<span class="emphasis">*value*</span> <span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.lastore.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*arrayref*</span> must be of type `reference`
and must refer to an array whose components are of type `long`. The
<span class="emphasis">*index*</span> must be of type `int`, and
<span class="emphasis">*value*</span> must be of type `long`. The
<span class="emphasis">*arrayref*</span>,
<span class="emphasis">*index*</span>, and
<span class="emphasis">*value*</span> are popped from the operand stack.
The `long` <span class="emphasis">*value*</span> is stored as the
component of the array indexed by <span class="emphasis">*index*</span>.

</div>

<div id="jvms-6.5.lastore.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

If <span class="emphasis">*arrayref*</span> is `null`,
<span class="emphasis">*lastore*</span> throws a `NullPointerException`.

Otherwise, if <span class="emphasis">*index*</span> is not within the
bounds of the array referenced by
<span class="emphasis">*arrayref*</span>, the
<span class="emphasis">*lastore*</span> instruction throws an
`ArrayIndexOutOfBoundsException`.

</div>

</div>

<div id="jvms-6.5.lcmp" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*lcmp*</span>

</div>

</div>

</div>

<div id="d5e22807" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Compare `long`

</div>

<div id="d5e22811" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*lcmp*</span>  

</div>

</div>

<div id="d5e22815" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*lcmp*</span> = 148 (0x94)

</div>

<div id="d5e22819" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.lcmp.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `long`. They are
both popped from the operand stack, and a signed integer comparison is
performed. If <span class="emphasis">*value1*</span> is greater than
<span class="emphasis">*value2*</span>, the `int` value 1 is pushed onto
the operand stack. If <span class="emphasis">*value1*</span> is equal to
<span class="emphasis">*value2*</span>, the `int` value 0 is pushed onto
the operand stack. If <span class="emphasis">*value1*</span> is less
than <span class="emphasis">*value2*</span>, the `int` value -1 is
pushed onto the operand stack.

</div>

</div>

<div id="jvms-6.5.lconst_l" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*lconst\_\<l\>*</span>

</div>

</div>

</div>

<div id="d5e22845" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Push `long` constant

</div>

<div id="d5e22849" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*lconst\_\<l\>*</span>  

</div>

</div>

<div id="d5e22853" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*lconst_0*</span> = 9 (0x9)

<span class="emphasis">*lconst_1*</span> = 10 (0xa)

</div>

<div id="d5e22859" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

... <span class="symbol">→</span>

..., \<<span class="emphasis">*l*</span>\>

</div>

<div id="jvms-6.5.lconst_l.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Push the `long` constant \<<span class="emphasis">*l*</span>\> (0 or 1)
onto the operand stack.

</div>

</div>

<div id="jvms-6.5.ldc" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*ldc*</span>

</div>

</div>

</div>

<div id="d5e22873" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Push item from run-time constant pool

</div>

<div id="d5e22876" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*ldc*</span>  
<span class="emphasis">*index*</span>  

</div>

</div>

<div id="d5e22881" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*ldc*</span> = 18 (0x12)

</div>

<div id="d5e22885" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

... <span class="symbol">→</span>

..., <span class="emphasis">*value*</span>

</div>

<div id="jvms-6.5.ldc.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*index*</span> is an unsigned byte that must
be a valid index into the run-time constant pool of the current class
(<a href="jvms-2.html#jvms-2.5.5" class="xref"
title="2.5.5. Run-Time Constant Pool">§2.5.5</a>). The run-time constant
pool entry at <span class="emphasis">*index*</span> must be loadable
(<a href="jvms-5.html#jvms-5.1" class="xref"
title="5.1. The Run-Time Constant Pool">§5.1</a>), and not any of the
following:

<div class="norm">

- A numeric constant of type `long` or `double`.

- A symbolic reference to a dynamically-computed constant whose field
  descriptor is `J` (denoting `long`) or `D` (denoting `double`).

</div>

If the run-time constant pool entry is a numeric constant of type `int`
or `float`, then the <span class="emphasis">*value*</span> of that
numeric constant is pushed onto the operand stack as an `int` or
`float`, respectively.

Otherwise, if the run-time constant pool entry is a string constant,
that is, a `reference` to an instance of class `String`, then
<span class="emphasis">*value*</span>, a `reference` to that instance,
is pushed onto the operand stack.

Otherwise, if the run-time constant pool entry is a symbolic reference
to a class or interface, then the named class or interface is resolved
(<a href="jvms-5.html#jvms-5.4.3.1" class="xref"
title="5.4.3.1. Class and Interface Resolution">§5.4.3.1</a>) and
<span class="emphasis">*value*</span>, a `reference` to the `Class`
object representing that class or interface, is pushed onto the operand
stack.

Otherwise, the run-time constant pool entry is a symbolic reference to a
method type, a method handle, or a dynamically-computed constant. The
symbolic reference is resolved
(<a href="jvms-5.html#jvms-5.4.3.5" class="xref"
title="5.4.3.5. Method Type and Method Handle Resolution">§5.4.3.5</a>,
<a href="jvms-5.html#jvms-5.4.3.6" class="xref"
title="5.4.3.6. Dynamically-Computed Constant and Call Site Resolution">§5.4.3.6</a>)
and <span class="emphasis">*value*</span>, the result of resolution, is
pushed onto the operand stack.

</div>

<div id="jvms-6.5.ldc.linking" class="section">

<div class="titlepage">

<div>

<div>

#### Linking Exceptions

</div>

</div>

</div>

During resolution of a symbolic reference, any of the exceptions
pertaining to resolution of that kind of symbolic reference can be
thrown.

</div>

</div>

<div id="jvms-6.5.ldc_w" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*ldc_w*</span>

</div>

</div>

</div>

<div id="d5e22935" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Push item from run-time constant pool (wide index)

</div>

<div id="d5e22938" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*ldc_w*</span>  
<span class="emphasis">*indexbyte1*</span>  
<span class="emphasis">*indexbyte2*</span>  

</div>

</div>

<div id="d5e22944" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*ldc_w*</span> = 19 (0x13)

</div>

<div id="d5e22948" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

... <span class="symbol">→</span>

..., <span class="emphasis">*value*</span>

</div>

<div id="jvms-6.5.ldc_w.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The unsigned <span class="emphasis">*indexbyte1*</span> and
<span class="emphasis">*indexbyte2*</span> are assembled into an
unsigned 16-bit index into the run-time constant pool of the current
class (<a href="jvms-2.html#jvms-2.5.5" class="xref"
title="2.5.5. Run-Time Constant Pool">§2.5.5</a>), where the value of
the index is calculated as (<span class="emphasis">*indexbyte1*</span>
`<<` 8) \| <span class="emphasis">*indexbyte2*</span>. The index must be
a valid index into the run-time constant pool of the current class. The
run-time constant pool entry at the index must be loadable
(<a href="jvms-5.html#jvms-5.1" class="xref"
title="5.1. The Run-Time Constant Pool">§5.1</a>), and not any of the
following:

<div class="norm">

- A numeric constant of type `long` or `double`.

- A symbolic reference to a dynamically-computed constant whose field
  descriptor is `J` (denoting `long`) or `D` (denoting `double`).

</div>

If the run-time constant pool entry is a numeric constant of type `int`
or `float`, or a string constant, then
<span class="emphasis">*value*</span> is determined and pushed onto the
operand stack according to the rules given for the
<span class="emphasis">*ldc*</span> instruction.

Otherwise, the run-time constant pool entry is a symbolic reference to a
class, interface, method type, method handle, or dynamically-computed
constant. It is resolved and <span class="emphasis">*value*</span> is
determined and pushed onto the operand stack according to the rules
given for the <span class="emphasis">*ldc*</span> instruction.

</div>

<div id="jvms-6.5.ldc_w.linking" class="section">

<div class="titlepage">

<div>

<div>

#### Linking Exceptions

</div>

</div>

</div>

During resolution of a symbolic reference, any of the exceptions
pertaining to resolution of that kind of symbolic reference can be
thrown.

</div>

<div id="jvms-6.5.ldc_w.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*ldc_w*</span> instruction is identical to
the <span class="emphasis">*ldc*</span> instruction
(<a href="jvms-6.html#jvms-6.5.ldc" class="xref" title="ldc">§<span
class="emphasis"><em>ldc</em></span></a>) except for its wider run-time
constant pool index.

</div>

</div>

<div id="jvms-6.5.ldc2_w" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*ldc2_w*</span>

</div>

</div>

</div>

<div id="d5e22995" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Push `long` or `double` from run-time constant pool (wide index)

</div>

<div id="d5e23000" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*ldc2_w*</span>  
<span class="emphasis">*indexbyte1*</span>  
<span class="emphasis">*indexbyte2*</span>  

</div>

</div>

<div id="d5e23006" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*ldc2_w*</span> = 20 (0x14)

</div>

<div id="d5e23010" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

... <span class="symbol">→</span>

..., <span class="emphasis">*value*</span>

</div>

<div id="jvms-6.5.ldc2_w.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The unsigned <span class="emphasis">*indexbyte1*</span> and
<span class="emphasis">*indexbyte2*</span> are assembled into an
unsigned 16-bit index into the run-time constant pool of the current
class (<a href="jvms-2.html#jvms-2.5.5" class="xref"
title="2.5.5. Run-Time Constant Pool">§2.5.5</a>), where the value of
the index is calculated as (<span class="emphasis">*indexbyte1*</span>
`<<` 8) \| <span class="emphasis">*indexbyte2*</span>. The index must be
a valid index into the run-time constant pool of the current class. The
run-time constant pool entry at the index must be loadable
(<a href="jvms-5.html#jvms-5.1" class="xref"
title="5.1. The Run-Time Constant Pool">§5.1</a>), and in particular one
of the following:

<div class="norm">

- A numeric constant of type `long` or `double`.

- A symbolic reference to a dynamically-computed constant whose field
  descriptor is `J` (denoting `long`) or `D` (denoting `double`).

</div>

If the run-time constant pool entry is a numeric constant of type `long`
or `double`, then the <span class="emphasis">*value*</span> of that
numeric constant is pushed onto the operand stack as a `long` or
`double`, respectively.

Otherwise, the run-time constant pool entry is a symbolic reference to a
dynamically-computed constant. The symbolic reference is resolved
(<a href="jvms-5.html#jvms-5.4.3.6" class="xref"
title="5.4.3.6. Dynamically-Computed Constant and Call Site Resolution">§5.4.3.6</a>)
and <span class="emphasis">*value*</span>, the result of resolution, is
pushed onto the operand stack.

</div>

<div id="jvms-6.5.ldc2_w.linking" class="section">

<div class="titlepage">

<div>

<div>

#### Linking Exceptions

</div>

</div>

</div>

During resolution of a symbolic reference to a dynamically-computed
constant, any of the exceptions pertaining to dynamically-computed
constant resolution can be thrown.

</div>

<div id="jvms-6.5.ldc2_w.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

Only a wide-index version of the <span class="emphasis">*ldc2_w*</span>
instruction exists; there is no <span class="emphasis">*ldc2*</span>
instruction that pushes a `long` or `double` with a single-byte index.

</div>

</div>

<div id="jvms-6.5.ldiv" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*ldiv*</span>

</div>

</div>

</div>

<div id="d5e23059" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Divide `long`

</div>

<div id="d5e23063" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*ldiv*</span>  

</div>

</div>

<div id="d5e23067" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*ldiv*</span> = 109 (0x6d)

</div>

<div id="d5e23071" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.ldiv.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `long`. The
values are popped from the operand stack. The `long`
<span class="emphasis">*result*</span> is the value of the Java
programming language expression <span class="emphasis">*value1*</span> /
<span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

A `long` division rounds towards 0; that is, the quotient produced for
`long` values in <span class="emphasis">*n*</span> /
<span class="emphasis">*d*</span> is a `long` value
<span class="emphasis">*q*</span> whose magnitude is as large as
possible while satisfying \|<span class="emphasis">*d*</span>
<span class="symbol">⋅</span> <span class="emphasis">*q*</span>\|
<span class="symbol">≤</span> \|<span class="emphasis">*n*</span>\|.
Moreover, <span class="emphasis">*q*</span> is positive when
\|<span class="emphasis">*n*</span>\| <span class="symbol">≥</span>
\|<span class="emphasis">*d*</span>\| and
<span class="emphasis">*n*</span> and <span class="emphasis">*d*</span>
have the same sign, but <span class="emphasis">*q*</span> is negative
when \|<span class="emphasis">*n*</span>\| <span class="symbol">≥</span>
\|<span class="emphasis">*d*</span>\| and
<span class="emphasis">*n*</span> and <span class="emphasis">*d*</span>
have opposite signs.

There is one special case that does not satisfy this rule: if the
dividend is the negative integer of largest possible magnitude for the
`long` type and the divisor is -1, then overflow occurs and the result
is equal to the dividend; despite the overflow, no exception is thrown
in this case.

</div>

<div id="jvms-6.5.ldiv.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exception

</div>

</div>

</div>

If the value of the divisor in a `long` division is 0,
<span class="emphasis">*ldiv*</span> throws an `ArithmeticException`.

</div>

</div>

<div id="jvms-6.5.lload" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*lload*</span>

</div>

</div>

</div>

<div id="d5e23125" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Load `long` from local variable

</div>

<div id="d5e23129" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*lload*</span>  
<span class="emphasis">*index*</span>  

</div>

</div>

<div id="d5e23134" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*lload*</span> = 22 (0x16)

</div>

<div id="d5e23138" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

... <span class="symbol">→</span>

..., <span class="emphasis">*value*</span>

</div>

<div id="jvms-6.5.lload.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*index*</span> is an unsigned byte. Both
<span class="emphasis">*index*</span> and
<span class="emphasis">*index*</span>+1 must be indices into the local
variable array of the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>).
The local variable at <span class="emphasis">*index*</span> must contain
a `long`. The <span class="emphasis">*value*</span> of the local
variable at <span class="emphasis">*index*</span> is pushed onto the
operand stack.

</div>

<div id="jvms-6.5.lload.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*lload*</span> opcode can be used in
conjunction with the <span class="emphasis">*wide*</span> instruction
(<a href="jvms-6.html#jvms-6.5.wide" class="xref" title="wide">§<span
class="emphasis"><em>wide</em></span></a>) to access a local variable
using a two-byte unsigned index.

</div>

</div>

<div id="jvms-6.5.lload_n" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*lload\_\<n\>*</span>

</div>

</div>

</div>

<div id="d5e23164" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Load `long` from local variable

</div>

<div id="d5e23168" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*lload\_\<n\>*</span>  

</div>

</div>

<div id="d5e23172" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*lload_0*</span> = 30 (0x1e)

<span class="emphasis">*lload_1*</span> = 31 (0x1f)

<span class="emphasis">*lload_2*</span> = 32 (0x20)

<span class="emphasis">*lload_3*</span> = 33 (0x21)

</div>

<div id="d5e23182" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

... <span class="symbol">→</span>

..., <span class="emphasis">*value*</span>

</div>

<div id="jvms-6.5.lload_n.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both \<<span class="emphasis">*n*</span>\> and
\<<span class="emphasis">*n*</span>\>+1 must be indices into the local
variable array of the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>).
The local variable at \<<span class="emphasis">*n*</span>\> must contain
a `long`. The <span class="emphasis">*value*</span> of the local
variable at \<<span class="emphasis">*n*</span>\> is pushed onto the
operand stack.

</div>

<div id="jvms-6.5.lload_n.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

Each of the <span class="emphasis">*lload\_\<n\>*</span> instructions is
the same as <span class="emphasis">*lload*</span> with an
<span class="emphasis">*index*</span> of
\<<span class="emphasis">*n*</span>\>, except that the operand
\<<span class="emphasis">*n*</span>\> is implicit.

</div>

</div>

<div id="jvms-6.5.lmul" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*lmul*</span>

</div>

</div>

</div>

<div id="d5e23209" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Multiply `long`

</div>

<div id="d5e23213" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*lmul*</span>  

</div>

</div>

<div id="d5e23217" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*lmul*</span> = 105 (0x69)

</div>

<div id="d5e23221" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.lmul.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `long`. The
values are popped from the operand stack. The `long`
<span class="emphasis">*result*</span> is
<span class="emphasis">*value1*</span> \*
<span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

The result is the 64 low-order bits of the true mathematical result in a
sufficiently wide two's-complement format, represented as a value of
type `long`. If overflow occurs, the sign of the result may not be the
same as the sign of the mathematical multiplication of the two values.

Despite the fact that overflow may occur, execution of an
<span class="emphasis">*lmul*</span> instruction never throws a run-time
exception.

</div>

</div>

<div id="jvms-6.5.lneg" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*lneg*</span>

</div>

</div>

</div>

<div id="d5e23247" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Negate `long`

</div>

<div id="d5e23251" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*lneg*</span>  

</div>

</div>

<div id="d5e23255" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*lneg*</span> = 117 (0x75)

</div>

<div id="d5e23259" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.lneg.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*value*</span> must be of type `long`. It is
popped from the operand stack. The `long`
<span class="emphasis">*result*</span> is the arithmetic negation of
<span class="emphasis">*value*</span>,
-<span class="emphasis">*value*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

For `long` values, negation is the same as subtraction from zero.
Because the Java Virtual Machine uses two's-complement representation
for integers and the range of two's-complement values is not symmetric,
the negation of the maximum negative `long` results in that same maximum
negative number. Despite the fact that overflow has occurred, no
exception is thrown.

For all `long` values `x`, `-x` equals `(~x)+1`.

</div>

</div>

<div id="jvms-6.5.lookupswitch" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*lookupswitch*</span>

</div>

</div>

</div>

<div id="d5e23287" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Access jump table by key match and jump

</div>

<div id="d5e23290" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*lookupswitch*</span>  
<span class="emphasis">*\<0-3 byte pad\>*</span>  
<span class="emphasis">*defaultbyte1*</span>  
<span class="emphasis">*defaultbyte2*</span>  
<span class="emphasis">*defaultbyte3*</span>  
<span class="emphasis">*defaultbyte4*</span>  
<span class="emphasis">*npairs1*</span>  
<span class="emphasis">*npairs2*</span>  
<span class="emphasis">*npairs3*</span>  
<span class="emphasis">*npairs4*</span>  
<span class="emphasis">*match-offset pairs...*</span>  

</div>

</div>

<div id="d5e23304" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*lookupswitch*</span> = 171 (0xab)

</div>

<div id="d5e23308" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*key*</span> <span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.lookupswitch.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

A <span class="emphasis">*lookupswitch*</span> is a variable-length
instruction. Immediately after the
<span class="emphasis">*lookupswitch*</span> opcode, between zero and
three bytes must act as padding, such that
<span class="emphasis">*defaultbyte1*</span> begins at an address that
is a multiple of four bytes from the start of the current method (the
opcode of its first instruction). Immediately after the padding follow a
series of signed 32-bit values: <span class="emphasis">*default*</span>,
<span class="emphasis">*npairs*</span>, and then
<span class="emphasis">*npairs*</span> pairs of signed 32-bit values.
The <span class="emphasis">*npairs*</span> must be greater than or equal
to 0. Each of the <span class="emphasis">*npairs*</span> pairs consists
of an `int` <span class="emphasis">*match*</span> and a signed 32-bit
<span class="emphasis">*offset*</span>. Each of these signed 32-bit
values is constructed from four unsigned bytes as
(<span class="emphasis">*byte1*</span> `<<` 24) \|
(<span class="emphasis">*byte2*</span> `<<` 16) \|
(<span class="emphasis">*byte3*</span> `<<` 8) \|
<span class="emphasis">*byte4*</span>.

The table <span class="emphasis">*match-offset*</span> pairs of the
<span class="emphasis">*lookupswitch*</span> instruction must be sorted
in increasing numerical order by <span class="emphasis">*match*</span>.

The <span class="emphasis">*key*</span> must be of type `int` and is
popped from the operand stack. The <span class="emphasis">*key*</span>
is compared against the <span class="emphasis">*match*</span> values. If
it is equal to one of them, then a target address is calculated by
adding the corresponding <span class="emphasis">*offset*</span> to the
address of the opcode of this
<span class="emphasis">*lookupswitch*</span> instruction. If the
<span class="emphasis">*key*</span> does not match any of the
<span class="emphasis">*match*</span> values, the target address is
calculated by adding <span class="emphasis">*default*</span> to the
address of the opcode of this
<span class="emphasis">*lookupswitch*</span> instruction. Execution then
continues at the target address.

The target address that can be calculated from the
<span class="emphasis">*offset*</span> of each
<span class="emphasis">*match-offset*</span> pair, as well as the one
calculated from <span class="emphasis">*default*</span>, must be the
address of an opcode of an instruction within the method that contains
this <span class="emphasis">*lookupswitch*</span> instruction.

</div>

<div id="jvms-6.5.lookupswitch.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The alignment required of the 4-byte operands of the
<span class="emphasis">*lookupswitch*</span> instruction guarantees
4-byte alignment of those operands if and only if the method that
contains the <span class="emphasis">*lookupswitch*</span> is positioned
on a 4-byte boundary.

The <span class="emphasis">*match-offset*</span> pairs are sorted to
support lookup routines that are quicker than linear search.

</div>

</div>

<div id="jvms-6.5.lor" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*lor*</span>

</div>

</div>

</div>

<div id="d5e23365" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Bitwise OR `long`

</div>

<div id="d5e23369" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*lor*</span>  

</div>

</div>

<div id="d5e23373" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*lor*</span> = 129 (0x81)

</div>

<div id="d5e23377" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.lor.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `long`. They are
popped from the operand stack. A `long`
<span class="emphasis">*result*</span> is calculated by taking the
bitwise inclusive OR of <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

</div>

</div>

<div id="jvms-6.5.lrem" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*lrem*</span>

</div>

</div>

</div>

<div id="d5e23399" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Remainder `long`

</div>

<div id="d5e23403" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*lrem*</span>  

</div>

</div>

<div id="d5e23407" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*lrem*</span> = 113 (0x71)

</div>

<div id="d5e23411" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.lrem.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `long`. The
values are popped from the operand stack. The `long`
<span class="emphasis">*result*</span> is
<span class="emphasis">*value1*</span> -
(<span class="emphasis">*value1*</span> /
<span class="emphasis">*value2*</span>) \*
<span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

The result of the <span class="emphasis">*lrem*</span> instruction is
such that `(a/b)*b + (a%b)` is equal to `a`. This identity holds even in
the special case in which the dividend is the negative `long` of largest
possible magnitude for its type and the divisor is -1 (the remainder is
0). It follows from this rule that the result of the remainder operation
can be negative only if the dividend is negative and can be positive
only if the dividend is positive; moreover, the magnitude of the result
is always less than the magnitude of the divisor.

</div>

<div id="jvms-6.5.lrem.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exception

</div>

</div>

</div>

If the value of the divisor for a `long` remainder operator is 0,
<span class="emphasis">*lrem*</span> throws an `ArithmeticException`.

</div>

</div>

<div id="jvms-6.5.lreturn" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*lreturn*</span>

</div>

</div>

</div>

<div id="d5e23446" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Return `long` from method

</div>

<div id="d5e23450" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*lreturn*</span>  

</div>

</div>

<div id="d5e23454" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*lreturn*</span> = 173 (0xad)

</div>

<div id="d5e23458" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

\[empty\]

</div>

<div id="jvms-6.5.lreturn.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The current method must have return type `long`. The
<span class="emphasis">*value*</span> must be of type `long`. If the
current method is a `synchronized` method, the monitor entered or
reentered on invocation of the method is updated and possibly exited as
if by execution of a <span class="emphasis">*monitorexit*</span>
instruction (<a href="jvms-6.html#jvms-6.5.monitorexit" class="xref"
title="monitorexit">§<span
class="emphasis"><em>monitorexit</em></span></a>) in the current thread.
If no exception is thrown, <span class="emphasis">*value*</span> is
popped from the operand stack of the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>)
and pushed onto the operand stack of the frame of the invoker. Any other
values on the operand stack of the current method are discarded.

The interpreter then returns control to the invoker of the method,
reinstating the frame of the invoker.

</div>

<div id="jvms-6.5.lreturn.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

If the Java Virtual Machine implementation does not enforce the rules on
structured locking described in
<a href="jvms-2.html#jvms-2.11.10" class="xref"
title="2.11.10. Synchronization">§2.11.10</a>, then if the current
method is a `synchronized` method and the current thread is not the
owner of the monitor entered or reentered on invocation of the method,
<span class="emphasis">*lreturn*</span> throws an
`IllegalMonitorStateException`. This can happen, for example, if a
`synchronized` method contains a
<span class="emphasis">*monitorexit*</span> instruction, but no
<span class="emphasis">*monitorenter*</span> instruction, on the object
on which the method is `synchronized`.

Otherwise, if the Java Virtual Machine implementation enforces the rules
on structured locking described in
<a href="jvms-2.html#jvms-2.11.10" class="xref"
title="2.11.10. Synchronization">§2.11.10</a> and if the first of those
rules is violated during invocation of the current method, then
<span class="emphasis">*lreturn*</span> throws an
`IllegalMonitorStateException`.

</div>

</div>

<div id="jvms-6.5.lshl" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*lshl*</span>

</div>

</div>

</div>

<div id="d5e23494" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Shift left `long`

</div>

<div id="d5e23498" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*lshl*</span>  

</div>

</div>

<div id="d5e23502" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*lshl*</span> = 121 (0x79)

</div>

<div id="d5e23506" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.lshl.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*value1*</span> must be of type `long`, and
<span class="emphasis">*value2*</span> must be of type `int`. The values
are popped from the operand stack. A `long`
<span class="emphasis">*result*</span> is calculated by shifting
<span class="emphasis">*value1*</span> left by
<span class="emphasis">*s*</span> bit positions, where
<span class="emphasis">*s*</span> is the low 6 bits of
<span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

</div>

<div id="jvms-6.5.lshl.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

This is equivalent (even if overflow occurs) to multiplication by 2 to
the power <span class="emphasis">*s*</span>. The shift distance actually
used is therefore always in the range 0 to 63, inclusive, as if
<span class="emphasis">*value2*</span> were subjected to a bitwise
logical AND with the mask value 0x3f.

</div>

</div>

<div id="jvms-6.5.lshr" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*lshr*</span>

</div>

</div>

</div>

<div id="d5e23536" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Arithmetic shift right `long`

</div>

<div id="d5e23540" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*lshr*</span>  

</div>

</div>

<div id="d5e23544" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*lshr*</span> = 123 (0x7b)

</div>

<div id="d5e23548" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.lshr.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*value1*</span> must be of type `long`, and
<span class="emphasis">*value2*</span> must be of type `int`. The values
are popped from the operand stack. A `long`
<span class="emphasis">*result*</span> is calculated by shifting
<span class="emphasis">*value1*</span> right by
<span class="emphasis">*s*</span> bit positions, with sign extension,
where <span class="emphasis">*s*</span> is the value of the low 6 bits
of <span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

</div>

<div id="jvms-6.5.lshr.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The resulting value is
<span class="emphasis">*floor*</span>(<span class="emphasis">*value1*</span>
/ 2<sup><span class="emphasis">*s*</span></sup>), where
<span class="emphasis">*s*</span> is
<span class="emphasis">*value2*</span> & 0x3f. For non-negative
<span class="emphasis">*value1*</span>, this is equivalent to truncating
`long` division by 2 to the power <span class="emphasis">*s*</span>. The
shift distance actually used is therefore always in the range 0 to 63,
inclusive, as if <span class="emphasis">*value2*</span> were subjected
to a bitwise logical AND with the mask value 0x3f.

</div>

</div>

<div id="jvms-6.5.lstore" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*lstore*</span>

</div>

</div>

</div>

<div id="d5e23586" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Store `long` into local variable

</div>

<div id="d5e23590" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*lstore*</span>  
<span class="emphasis">*index*</span>  

</div>

</div>

<div id="d5e23595" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*lstore*</span> = 55 (0x37)

</div>

<div id="d5e23599" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.lstore.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*index*</span> is an unsigned byte. Both
<span class="emphasis">*index*</span> and
<span class="emphasis">*index*</span>+1 must be indices into the local
variable array of the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>).
The <span class="emphasis">*value*</span> on the top of the operand
stack must be of type `long`. It is popped from the operand stack, and
the local variables at <span class="emphasis">*index*</span> and
<span class="emphasis">*index*</span>+1 are set to
<span class="emphasis">*value*</span>.

</div>

<div id="jvms-6.5.lstore.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*lstore*</span> opcode can be used in
conjunction with the <span class="emphasis">*wide*</span> instruction
(<a href="jvms-6.html#jvms-6.5.wide" class="xref" title="wide">§<span
class="emphasis"><em>wide</em></span></a>) to access a local variable
using a two-byte unsigned index.

</div>

</div>

<div id="jvms-6.5.lstore_n" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*lstore\_\<n\>*</span>

</div>

</div>

</div>

<div id="d5e23626" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Store `long` into local variable

</div>

<div id="d5e23630" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*lstore\_\<n\>*</span>  

</div>

</div>

<div id="d5e23634" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*lstore_0*</span> = 63 (0x3f)

<span class="emphasis">*lstore_1*</span> = 64 (0x40)

<span class="emphasis">*lstore_2*</span> = 65 (0x41)

<span class="emphasis">*lstore_3*</span> = 66 (0x42)

</div>

<div id="d5e23644" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.lstore_n.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both \<<span class="emphasis">*n*</span>\> and
\<<span class="emphasis">*n*</span>\>+1 must be indices into the local
variable array of the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>).
The <span class="emphasis">*value*</span> on the top of the operand
stack must be of type `long`. It is popped from the operand stack, and
the local variables at \<<span class="emphasis">*n*</span>\> and
\<<span class="emphasis">*n*</span>\>+1 are set to
<span class="emphasis">*value*</span>.

</div>

<div id="jvms-6.5.lstore_n.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

Each of the <span class="emphasis">*lstore\_\<n\>*</span> instructions
is the same as <span class="emphasis">*lstore*</span> with an
<span class="emphasis">*index*</span> of
\<<span class="emphasis">*n*</span>\>, except that the operand
\<<span class="emphasis">*n*</span>\> is implicit.

</div>

</div>

<div id="jvms-6.5.lsub" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*lsub*</span>

</div>

</div>

</div>

<div id="d5e23672" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Subtract `long`

</div>

<div id="d5e23676" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*lsub*</span>  

</div>

</div>

<div id="d5e23680" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*lsub*</span> = 101 (0x65)

</div>

<div id="d5e23684" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.lsub.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `long`. The
values are popped from the operand stack. The `long`
<span class="emphasis">*result*</span> is
<span class="emphasis">*value1*</span> -
<span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

For `long` subtraction, `a-b` produces the same result as `a+(-b)`. For
`long` values, subtraction from zero is the same as negation.

The result is the 64 low-order bits of the true mathematical result in a
sufficiently wide two's-complement format, represented as a value of
type `long`. If overflow occurs, then the sign of the result may not be
the same as the sign of the mathematical difference of the two values.

Despite the fact that overflow may occur, execution of an
<span class="emphasis">*lsub*</span> instruction never throws a run-time
exception.

</div>

</div>

<div id="jvms-6.5.lushr" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*lushr*</span>

</div>

</div>

</div>

<div id="d5e23715" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Logical shift right `long`

</div>

<div id="d5e23719" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*lushr*</span>  

</div>

</div>

<div id="d5e23723" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*lushr*</span> = 125 (0x7d)

</div>

<div id="d5e23727" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.lushr.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*value1*</span> must be of type `long`, and
<span class="emphasis">*value2*</span> must be of type `int`. The values
are popped from the operand stack. A `long`
<span class="emphasis">*result*</span> is calculated by shifting
<span class="emphasis">*value1*</span> right logically by
<span class="emphasis">*s*</span> bit positions, with zero extension,
where <span class="emphasis">*s*</span> is the value of the low 6 bits
of <span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

</div>

<div id="jvms-6.5.lushr.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

If <span class="emphasis">*value1*</span> is positive and
<span class="emphasis">*s*</span> is
<span class="emphasis">*value2*</span> & 0x3f, the result is the same as
that of <span class="emphasis">*value1*</span> `>>`
<span class="emphasis">*s*</span>; if
<span class="emphasis">*value1*</span> is negative, the result is equal
to the value of the expression (<span class="emphasis">*value1*</span>
`>>` <span class="emphasis">*s*</span>) + (2L `<<`
~<span class="emphasis">*s*</span>). The addition of the (2L `<<`
~<span class="emphasis">*s*</span>) term cancels out the propagated sign
bit. The shift distance actually used is always in the range 0 to 63,
inclusive.

</div>

</div>

<div id="jvms-6.5.lxor" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*lxor*</span>

</div>

</div>

</div>

<div id="d5e23769" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Bitwise XOR `long`

</div>

<div id="d5e23773" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*lxor*</span>  

</div>

</div>

<div id="d5e23777" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*lxor*</span> = 131 (0x83)

</div>

<div id="d5e23781" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span> <span class="symbol">→</span>

..., <span class="emphasis">*result*</span>

</div>

<div id="jvms-6.5.lxor.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Both <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> must be of type `long`. They are
popped from the operand stack. A `long`
<span class="emphasis">*result*</span> is calculated by taking the
bitwise exclusive OR of <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span>. The
<span class="emphasis">*result*</span> is pushed onto the operand stack.

</div>

</div>

<div id="jvms-6.5.monitorenter" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*monitorenter*</span>

</div>

</div>

</div>

<div id="d5e23803" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Enter monitor for object

</div>

<div id="d5e23806" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*monitorenter*</span>  

</div>

</div>

<div id="d5e23810" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*monitorenter*</span> = 194 (0xc2)

</div>

<div id="d5e23814" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*objectref*</span>
<span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.monitorenter.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*objectref*</span> must be of type
`reference`.

Each object is associated with a monitor. A monitor is locked if and
only if it has an owner. The thread that executes
<span class="emphasis">*monitorenter*</span> attempts to gain ownership
of the monitor associated with
<span class="emphasis">*objectref*</span>, as follows:

<div class="norm">

- If the entry count of the monitor associated with
  <span class="emphasis">*objectref*</span> is zero, the thread enters
  the monitor and sets its entry count to one. The thread is then the
  owner of the monitor.

- If the thread already owns the monitor associated with
  <span class="emphasis">*objectref*</span>, it reenters the monitor,
  incrementing its entry count.

- If another thread already owns the monitor associated with
  <span class="emphasis">*objectref*</span>, the thread blocks until the
  monitor's entry count is zero, then tries again to gain ownership.

</div>

</div>

<div id="jvms-6.5.monitorenter.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exception

</div>

</div>

</div>

If <span class="emphasis">*objectref*</span> is `null`,
<span class="emphasis">*monitorenter*</span> throws a
`NullPointerException`.

</div>

<div id="jvms-6.5.monitorenter.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

A <span class="emphasis">*monitorenter*</span> instruction may be used
with one or more <span class="emphasis">*monitorexit*</span>
instructions (<a href="jvms-6.html#jvms-6.5.monitorexit" class="xref"
title="monitorexit">§<span
class="emphasis"><em>monitorexit</em></span></a>) to implement a
`synchronized` statement in the Java programming language
(<a href="jvms-3.html#jvms-3.14" class="xref"
title="3.14. Synchronization">§3.14</a>). The
<span class="emphasis">*monitorenter*</span> and
<span class="emphasis">*monitorexit*</span> instructions are not used in
the implementation of `synchronized` methods, although they can be used
to provide equivalent locking semantics. Monitor entry on invocation of
a `synchronized` method, and monitor exit on its return, are handled
implicitly by the Java Virtual Machine's method invocation and return
instructions, as if <span class="emphasis">*monitorenter*</span> and
<span class="emphasis">*monitorexit*</span> were used.

The association of a monitor with an object may be managed in various
ways that are beyond the scope of this specification. For instance, the
monitor may be allocated and deallocated at the same time as the object.
Alternatively, it may be dynamically allocated at the time when a thread
attempts to gain exclusive access to the object and freed at some later
time when no thread remains in the monitor for the object.

The synchronization constructs of the Java programming language require
support for operations on monitors besides entry and exit. These include
waiting on a monitor (`Object.wait`) and notifying other threads waiting
on a monitor (`Object.notifyAll` and `Object.notify`). These operations
are supported in the standard package `java.lang` supplied with the Java
Virtual Machine. No explicit support for these operations appears in the
instruction set of the Java Virtual Machine.

</div>

</div>

<div id="jvms-6.5.monitorexit" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*monitorexit*</span>

</div>

</div>

</div>

<div id="d5e23868" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Exit monitor for object

</div>

<div id="d5e23871" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*monitorexit*</span>  

</div>

</div>

<div id="d5e23875" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*monitorexit*</span> = 195 (0xc3)

</div>

<div id="d5e23879" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*objectref*</span>
<span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.monitorexit.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*objectref*</span> must be of type
`reference`.

The thread that executes <span class="emphasis">*monitorexit*</span>
must be the owner of the monitor associated with the instance referenced
by <span class="emphasis">*objectref*</span>.

The thread decrements the entry count of the monitor associated with
<span class="emphasis">*objectref*</span>. If as a result the value of
the entry count is zero, the thread exits the monitor and is no longer
its owner. Other threads that are blocking to enter the monitor are
allowed to attempt to do so.

</div>

<div id="jvms-6.5.monitorexit.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

If <span class="emphasis">*objectref*</span> is `null`,
<span class="emphasis">*monitorexit*</span> throws a
`NullPointerException`.

Otherwise, if the thread that executes
<span class="emphasis">*monitorexit*</span> is not the owner of the
monitor associated with the instance referenced by
<span class="emphasis">*objectref*</span>,
<span class="emphasis">*monitorexit*</span> throws an
`IllegalMonitorStateException`.

Otherwise, if the Java Virtual Machine implementation enforces the rules
on structured locking described in
<a href="jvms-2.html#jvms-2.11.10" class="xref"
title="2.11.10. Synchronization">§2.11.10</a> and if the second of those
rules is violated by the execution of this
<span class="emphasis">*monitorexit*</span> instruction, then
<span class="emphasis">*monitorexit*</span> throws an
`IllegalMonitorStateException`.

</div>

<div id="jvms-6.5.monitorexit.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

One or more <span class="emphasis">*monitorexit*</span> instructions may
be used with a <span class="emphasis">*monitorenter*</span> instruction
(<a href="jvms-6.html#jvms-6.5.monitorenter" class="xref"
title="monitorenter">§<span
class="emphasis"><em>monitorenter</em></span></a>) to implement a
`synchronized` statement in the Java programming language
(<a href="jvms-3.html#jvms-3.14" class="xref"
title="3.14. Synchronization">§3.14</a>). The
<span class="emphasis">*monitorenter*</span> and
<span class="emphasis">*monitorexit*</span> instructions are not used in
the implementation of `synchronized` methods, although they can be used
to provide equivalent locking semantics.

The Java Virtual Machine supports exceptions thrown within
`synchronized` methods and `synchronized` statements differently:

<div class="norm">

- Monitor exit on normal `synchronized` method completion is handled by
  the Java Virtual Machine's return instructions. Monitor exit on abrupt
  `synchronized` method completion is handled implicitly by the Java
  Virtual Machine's <span class="emphasis">*athrow*</span> instruction.

- When an exception is thrown from within a `synchronized` statement,
  exit from the monitor entered prior to the execution of the
  `synchronized` statement is achieved using the Java Virtual Machine's
  exception handling mechanism
  (<a href="jvms-3.html#jvms-3.14" class="xref"
  title="3.14. Synchronization">§3.14</a>).

</div>

</div>

</div>

<div id="jvms-6.5.multianewarray" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*multianewarray*</span>

</div>

</div>

</div>

<div id="d5e23940" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Create new multidimensional array

</div>

<div id="d5e23943" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*multianewarray*</span>  
<span class="emphasis">*indexbyte1*</span>  
<span class="emphasis">*indexbyte2*</span>  
<span class="emphasis">*dimensions*</span>  

</div>

</div>

<div id="d5e23950" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*multianewarray*</span> = 197 (0xc5)

</div>

<div id="d5e23954" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*count1*</span>,
\[<span class="emphasis">*count2*</span>, ...\]
<span class="symbol">→</span>

..., <span class="emphasis">*arrayref*</span>

</div>

<div id="jvms-6.5.multianewarray.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*dimensions*</span> operand is an unsigned
byte that must be greater than or equal to 1. It represents the number
of dimensions of the array to be created. The operand stack must contain
<span class="emphasis">*dimensions*</span> values. Each such value
represents the number of components in a dimension of the array to be
created, must be of type `int`, and must be non-negative. The
<span class="emphasis">*count1*</span> is the desired length in the
first dimension, <span class="emphasis">*count2*</span> in the second,
etc.

All of the <span class="emphasis">*count*</span> values are popped off
the operand stack. The unsigned
<span class="emphasis">*indexbyte1*</span> and
<span class="emphasis">*indexbyte2*</span> are used to construct an
index into the run-time constant pool of the current class
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>),
where the value of the index is
(<span class="emphasis">*indexbyte1*</span> `<<` 8) \|
<span class="emphasis">*indexbyte2*</span>. The run-time constant pool
entry at the index must be a symbolic reference to a class, array, or
interface type. The named class, array, or interface type is resolved
(<a href="jvms-5.html#jvms-5.4.3.1" class="xref"
title="5.4.3.1. Class and Interface Resolution">§5.4.3.1</a>). The
resulting entry must be an array class type of dimensionality greater
than or equal to <span class="emphasis">*dimensions*</span>.

A new multidimensional array of the array type is allocated from the
garbage-collected heap. If any <span class="emphasis">*count*</span>
value is zero, no subsequent dimensions are allocated. The components of
the array in the first dimension are initialized to subarrays of the
type of the second dimension, and so on. The components of the last
allocated dimension of the array are initialized to the default initial
value (<a href="jvms-2.html#jvms-2.3" class="xref"
title="2.3. Primitive Types and Values">§2.3</a>,
<a href="jvms-2.html#jvms-2.4" class="xref"
title="2.4. Reference Types and Values">§2.4</a>) for the element type
of the array type. A `reference`
<span class="emphasis">*arrayref*</span> to the new array is pushed onto
the operand stack.

</div>

<div id="jvms-6.5.multianewarray.linking" class="section">

<div class="titlepage">

<div>

<div>

#### Linking Exceptions

</div>

</div>

</div>

During resolution of the symbolic reference to the class, array, or
interface type, any of the exceptions documented in
<a href="jvms-5.html#jvms-5.4.3.1" class="xref"
title="5.4.3.1. Class and Interface Resolution">§5.4.3.1</a> can be
thrown.

Otherwise, if the current class does not have permission to access the
element type of the resolved array class,
<span class="emphasis">*multianewarray*</span> throws an
`IllegalAccessError`.

</div>

<div id="jvms-6.5.multianewarray.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exception

</div>

</div>

</div>

Otherwise, if any of the <span class="emphasis">*dimensions*</span>
values on the operand stack are less than zero, the
<span class="emphasis">*multianewarray*</span> instruction throws a
`NegativeArraySizeException`.

</div>

<div id="jvms-6.5.multianewarray.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

It may be more efficient to use <span class="emphasis">*newarray*</span>
or <span class="emphasis">*anewarray*</span>
(<a href="jvms-6.html#jvms-6.5.newarray" class="xref"
title="newarray">§<span class="emphasis"><em>newarray</em></span></a>,
<a href="jvms-6.html#jvms-6.5.anewarray" class="xref"
title="anewarray">§<span class="emphasis"><em>anewarray</em></span></a>)
when creating an array of a single dimension.

The array class referenced via the run-time constant pool may have more
dimensions than the <span class="emphasis">*dimensions*</span> operand
of the <span class="emphasis">*multianewarray*</span> instruction. In
that case, only the first <span class="emphasis">*dimensions*</span> of
the dimensions of the array are created.

</div>

</div>

<div id="jvms-6.5.new" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*new*</span>

</div>

</div>

</div>

<div id="d5e24013" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Create new object

</div>

<div id="d5e24016" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*new*</span>  
<span class="emphasis">*indexbyte1*</span>  
<span class="emphasis">*indexbyte2*</span>  

</div>

</div>

<div id="d5e24022" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*new*</span> = 187 (0xbb)

</div>

<div id="d5e24026" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

... <span class="symbol">→</span>

..., <span class="emphasis">*objectref*</span>

</div>

<div id="jvms-6.5.new.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The unsigned <span class="emphasis">*indexbyte1*</span> and
<span class="emphasis">*indexbyte2*</span> are used to construct an
index into the run-time constant pool of the current class
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>),
where the value of the index is
(<span class="emphasis">*indexbyte1*</span> `<<` 8) \|
<span class="emphasis">*indexbyte2*</span>. The run-time constant pool
entry at the index must be a symbolic reference to a class or interface
type. The named class or interface type is resolved
(<a href="jvms-5.html#jvms-5.4.3.1" class="xref"
title="5.4.3.1. Class and Interface Resolution">§5.4.3.1</a>) and should
result in a class type. Memory for a new instance of that class is
allocated from the garbage-collected heap, and the instance variables of
the new object are initialized to their default initial values
(<a href="jvms-2.html#jvms-2.3" class="xref"
title="2.3. Primitive Types and Values">§2.3</a>,
<a href="jvms-2.html#jvms-2.4" class="xref"
title="2.4. Reference Types and Values">§2.4</a>). The
<span class="emphasis">*objectref*</span>, a `reference` to the
instance, is pushed onto the operand stack.

On successful resolution of the class, it is initialized if it has not
already been initialized (<a href="jvms-5.html#jvms-5.5" class="xref"
title="5.5. Initialization">§5.5</a>).

</div>

<div id="jvms-6.5.new.linking" class="section">

<div class="titlepage">

<div>

<div>

#### Linking Exceptions

</div>

</div>

</div>

During resolution of the symbolic reference to the class or interface
type, any of the exceptions documented in
<a href="jvms-5.html#jvms-5.4.3.1" class="xref"
title="5.4.3.1. Class and Interface Resolution">§5.4.3.1</a> can be
thrown.

Otherwise, if the symbolic reference to the class or interface type
resolves to an interface or an `abstract` class,
<span class="emphasis">*new*</span> throws an `InstantiationError`.

</div>

<div id="jvms-6.5.new.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exception

</div>

</div>

</div>

Otherwise, if execution of this <span class="emphasis">*new*</span>
instruction causes initialization of the referenced class,
<span class="emphasis">*new*</span> may throw an `Error` as detailed in
JLS §15.9.4.

</div>

<div id="jvms-6.5.new.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The <span class="emphasis">*new*</span> instruction does not completely
create a new instance; instance creation is not completed until an
instance initialization method
(<a href="jvms-2.html#jvms-2.9.1" class="xref"
title="2.9.1. Instance Initialization Methods">§2.9.1</a>) has been
invoked on the uninitialized instance.

</div>

</div>

<div id="jvms-6.5.newarray" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*newarray*</span>

</div>

</div>

</div>

<div id="d5e24070" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Create new array

</div>

<div id="d5e24073" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*newarray*</span>  
<span class="emphasis">*atype*</span>  

</div>

</div>

<div id="d5e24078" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*newarray*</span> = 188 (0xbc)

</div>

<div id="d5e24082" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*count*</span> <span class="symbol">→</span>

..., <span class="emphasis">*arrayref*</span>

</div>

<div id="jvms-6.5.newarray.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*count*</span> must be of type `int`. It is
popped off the operand stack. The <span class="emphasis">*count*</span>
represents the number of elements in the array to be created.

The <span class="emphasis">*atype*</span> is a code that indicates the
type of array to create. It must take one of the following values:

<div id="jvms-6.5.newarray.desc-120" class="table">

**Table 6.5.newarray-A. Array type codes**

<div class="table-contents">

| Array Type  | <span class="emphasis">*atype*</span> |
|-------------|---------------------------------------|
| `T_BOOLEAN` | 4                                     |
| `T_CHAR`    | 5                                     |
| `T_FLOAT`   | 6                                     |
| `T_DOUBLE`  | 7                                     |
| `T_BYTE`    | 8                                     |
| `T_SHORT`   | 9                                     |
| `T_INT`     | 10                                    |
| `T_LONG`    | 11                                    |

</div>

</div>

  

A new array whose components are of type
<span class="emphasis">*atype*</span> and of length
<span class="emphasis">*count*</span> is allocated from the
garbage-collected heap. A `reference`
<span class="emphasis">*arrayref*</span> to this new array object is
pushed into the operand stack. Each of the elements of the new array is
initialized to the default initial value
(<a href="jvms-2.html#jvms-2.3" class="xref"
title="2.3. Primitive Types and Values">§2.3</a>,
<a href="jvms-2.html#jvms-2.4" class="xref"
title="2.4. Reference Types and Values">§2.4</a>) for the element type
of the array type.

</div>

<div id="jvms-6.5.newarray.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exception

</div>

</div>

</div>

If <span class="emphasis">*count*</span> is less than zero,
<span class="emphasis">*newarray*</span> throws a
`NegativeArraySizeException`.

</div>

<div id="jvms-6.5.newarray.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

In Oracle's Java Virtual Machine implementation, arrays of type
`boolean` (<span class="emphasis">*atype*</span> is `T_BOOLEAN`) are
stored as arrays of 8-bit values and are manipulated using the
<span class="emphasis">*baload*</span> and
<span class="emphasis">*bastore*</span> instructions
(<a href="jvms-6.html#jvms-6.5.baload" class="xref" title="baload">§<span
class="emphasis"><em>baload</em></span></a>,
<a href="jvms-6.html#jvms-6.5.bastore" class="xref"
title="bastore">§<span class="emphasis"><em>bastore</em></span></a>)
which also access arrays of type `byte`. Other implementations may
implement packed `boolean` arrays; the
<span class="emphasis">*baload*</span> and
<span class="emphasis">*bastore*</span> instructions must still be used
to access those arrays.

</div>

</div>

<div id="jvms-6.5.nop" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*nop*</span>

</div>

</div>

</div>

<div id="d5e24168" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Do nothing

</div>

<div id="d5e24171" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*nop*</span>  

</div>

</div>

<div id="d5e24175" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*nop*</span> = 0 (0x0)

</div>

<div id="d5e24179" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

No change

</div>

<div id="jvms-6.5.nop.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Do nothing.

</div>

</div>

<div id="jvms-6.5.pop" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*pop*</span>

</div>

</div>

</div>

<div id="d5e24188" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Pop the top operand stack value

</div>

<div id="d5e24191" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*pop*</span>  

</div>

</div>

<div id="d5e24195" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*pop*</span> = 87 (0x57)

</div>

<div id="d5e24199" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.pop.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Pop the top value from the operand stack.

The <span class="emphasis">*pop*</span> instruction must not be used
unless <span class="emphasis">*value*</span> is a value of a category 1
computational type (<a href="jvms-2.html#jvms-2.11.1" class="xref"
title="2.11.1. Types and the Java Virtual Machine">§2.11.1</a>).

</div>

</div>

<div id="jvms-6.5.pop2" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*pop2*</span>

</div>

</div>

</div>

<div id="d5e24215" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Pop the top one or two operand stack values

</div>

<div id="d5e24218" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*pop2*</span>  

</div>

</div>

<div id="d5e24222" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*pop2*</span> = 88 (0x58)

</div>

<div id="jvms-6.5.pop2.stack" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

Form 1:

..., <span class="emphasis">*value2*</span>,
<span class="emphasis">*value1*</span> <span class="symbol">→</span>

...

where each of <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> is a value of a category 1
computational type (<a href="jvms-2.html#jvms-2.11.1" class="xref"
title="2.11.1. Types and the Java Virtual Machine">§2.11.1</a>).

Form 2:

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

...

where <span class="emphasis">*value*</span> is a value of a category 2
computational type (<a href="jvms-2.html#jvms-2.11.1" class="xref"
title="2.11.1. Types and the Java Virtual Machine">§2.11.1</a>).

</div>

<div id="jvms-6.5.pop2.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Pop the top one or two values from the operand stack.

</div>

</div>

<div id="jvms-6.5.putfield" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*putfield*</span>

</div>

</div>

</div>

<div id="d5e24252" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Set field in object

</div>

<div id="d5e24255" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*putfield*</span>  
<span class="emphasis">*indexbyte1*</span>  
<span class="emphasis">*indexbyte2*</span>  

</div>

</div>

<div id="d5e24261" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*putfield*</span> = 181 (0xb5)

</div>

<div id="d5e24265" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*objectref*</span>,
<span class="emphasis">*value*</span> <span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.putfield.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The unsigned <span class="emphasis">*indexbyte1*</span> and
<span class="emphasis">*indexbyte2*</span> are used to construct an
index into the run-time constant pool of the current class
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>),
where the value of the index is
(<span class="emphasis">*indexbyte1*</span> `<<` 8) \|
<span class="emphasis">*indexbyte2*</span>. The run-time constant pool
entry at the index must be a symbolic reference to a field
(<a href="jvms-5.html#jvms-5.1" class="xref"
title="5.1. The Run-Time Constant Pool">§5.1</a>), which gives the name
and descriptor of the field as well as a symbolic reference to the class
in which the field is to be found. The referenced field is resolved
(<a href="jvms-5.html#jvms-5.4.3.2" class="xref"
title="5.4.3.2. Field Resolution">§5.4.3.2</a>).

The type of a <span class="emphasis">*value*</span> stored by a
<span class="emphasis">*putfield*</span> instruction must be compatible
with the descriptor of the referenced field
(<a href="jvms-4.html#jvms-4.3.2" class="xref"
title="4.3.2. Field Descriptors">§4.3.2</a>). If the field descriptor
type is `boolean`, `byte`, `char`, `short`, or `int`, then the
<span class="emphasis">*value*</span> must be an `int`. If the field
descriptor type is `float`, `long`, or `double`, then the
<span class="emphasis">*value*</span> must be a `float`, `long`, or
`double`, respectively. If the field descriptor type is a class type or
an array type, then the <span class="emphasis">*value*</span> must be a
value of the field descriptor type. If the field is `final`, it must be
declared in the current class, and the instruction must occur in an
instance initialization method of the current class
(<a href="jvms-2.html#jvms-2.9.1" class="xref"
title="2.9.1. Instance Initialization Methods">§2.9.1</a>).

The <span class="emphasis">*value*</span> and
<span class="emphasis">*objectref*</span> are popped from the operand
stack.

The <span class="emphasis">*objectref*</span> must be of type
`reference` but not an array type.

If the <span class="emphasis">*value*</span> is of type `int` and the
field descriptor type is one of `byte`, `char`, `short`, or `boolean`,
then the `int` <span class="emphasis">*value*</span> is converted to the
field descriptor type as follows. If the field descriptor type is
`byte`, `char`, or `short`, then the `int`
<span class="emphasis">*value*</span> is truncated to a value of the
field descriptor type, <span class="emphasis">*value*</span>'. If the
field descriptor type is `boolean`, then the `int`
<span class="emphasis">*value*</span> is narrowed by taking the bitwise
AND of <span class="emphasis">*value*</span> and 1, resulting in
<span class="emphasis">*value*</span>'. The referenced field in
<span class="emphasis">*objectref*</span> is set to
<span class="emphasis">*value*</span>'.

Otherwise, the referenced field in
<span class="emphasis">*objectref*</span> is set to
<span class="emphasis">*value*</span>.

</div>

<div id="jvms-6.5.putfield.linking" class="section">

<div class="titlepage">

<div>

<div>

#### Linking Exceptions

</div>

</div>

</div>

During resolution of the symbolic reference to the field, any of the
exceptions pertaining to field resolution
(<a href="jvms-5.html#jvms-5.4.3.2" class="xref"
title="5.4.3.2. Field Resolution">§5.4.3.2</a>) can be thrown.

Otherwise, if the resolved field is a `static` field,
<span class="emphasis">*putfield*</span> throws an
`IncompatibleClassChangeError`.

Otherwise, if the resolved field is `final`, it must be declared in the
current class, and the instruction must occur in an instance
initialization method of the current class. Otherwise, an
`IllegalAccessError` is thrown.

</div>

<div id="jvms-6.5.putfield.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exception

</div>

</div>

</div>

Otherwise, if <span class="emphasis">*objectref*</span> is `null`, the
<span class="emphasis">*putfield*</span> instruction throws a
`NullPointerException`.

</div>

</div>

<div id="jvms-6.5.putstatic" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*putstatic*</span>

</div>

</div>

</div>

<div id="d5e24358" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Set static field in class

</div>

<div id="d5e24361" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*putstatic*</span>  
<span class="emphasis">*indexbyte1*</span>  
<span class="emphasis">*indexbyte2*</span>  

</div>

</div>

<div id="d5e24367" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*putstatic*</span> = 179 (0xb3)

</div>

<div id="d5e24371" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value*</span> <span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.putstatic.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The unsigned <span class="emphasis">*indexbyte1*</span> and
<span class="emphasis">*indexbyte2*</span> are used to construct an
index into the run-time constant pool of the current class
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>),
where the value of the index is
(<span class="emphasis">*indexbyte1*</span> `<<` 8) \|
<span class="emphasis">*indexbyte2*</span>. The run-time constant pool
entry at the index must be a symbolic reference to a field
(<a href="jvms-5.html#jvms-5.1" class="xref"
title="5.1. The Run-Time Constant Pool">§5.1</a>), which gives the name
and descriptor of the field as well as a symbolic reference to the class
or interface in which the field is to be found. The referenced field is
resolved (<a href="jvms-5.html#jvms-5.4.3.2" class="xref"
title="5.4.3.2. Field Resolution">§5.4.3.2</a>).

On successful resolution of the field, the class or interface that
declared the resolved field is initialized if that class or interface
has not already been initialized
(<a href="jvms-5.html#jvms-5.5" class="xref"
title="5.5. Initialization">§5.5</a>).

The type of a <span class="emphasis">*value*</span> stored by a
<span class="emphasis">*putstatic*</span> instruction must be compatible
with the descriptor of the referenced field
(<a href="jvms-4.html#jvms-4.3.2" class="xref"
title="4.3.2. Field Descriptors">§4.3.2</a>). If the field descriptor
type is `boolean`, `byte`, `char`, `short`, or `int`, then the
<span class="emphasis">*value*</span> must be an `int`. If the field
descriptor type is `float`, `long`, or `double`, then the
<span class="emphasis">*value*</span> must be a `float`, `long`, or
`double`, respectively. If the field descriptor type is a class type or
an array type, then the <span class="emphasis">*value*</span> must be a
value of the field descriptor type. If the field is `final`, it must be
declared in the current class or interface, and the instruction must
occur in the class or interface initialization method of the current
class or interface (<a href="jvms-2.html#jvms-2.9.2" class="xref"
title="2.9.2. Class Initialization Methods">§2.9.2</a>).

The <span class="emphasis">*value*</span> is popped from the operand
stack.

If the <span class="emphasis">*value*</span> is of type `int` and the
field descriptor type is one of `byte`, `char`, `short`, or `boolean`,
then the `int` <span class="emphasis">*value*</span> is converted to the
field descriptor type as follows. If the field descriptor type is
`byte`, `char`, or `short`, then the `int`
<span class="emphasis">*value*</span> is truncated to a value of the
field descriptor type, <span class="emphasis">*value*</span>'. If the
field descriptor type is `boolean`, then the `int`
<span class="emphasis">*value*</span> is narrowed by taking the bitwise
AND of <span class="emphasis">*value*</span> and 1, resulting in
<span class="emphasis">*value*</span>'. The referenced field in the
class or interface is set to <span class="emphasis">*value*</span>'.

Otherwise, the referenced field in the class or interface is set to
<span class="emphasis">*value*</span>.

</div>

<div id="jvms-6.5.putstatic.linking" class="section">

<div class="titlepage">

<div>

<div>

#### Linking Exceptions

</div>

</div>

</div>

During resolution of the symbolic reference to the class or interface
field, any of the exceptions pertaining to field resolution
(<a href="jvms-5.html#jvms-5.4.3.2" class="xref"
title="5.4.3.2. Field Resolution">§5.4.3.2</a>) can be thrown.

Otherwise, if the resolved field is not a `static` (class) field or an
interface field, <span class="emphasis">*putstatic*</span> throws an
`IncompatibleClassChangeError`.

Otherwise, if the resolved field is `final`, it must be declared in the
current class or interface, and the instruction must occur in the class
or interface initialization method of the current class or interface.
Otherwise, an `IllegalAccessError` is thrown.

</div>

<div id="jvms-6.5.putstatic.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exception

</div>

</div>

</div>

Otherwise, if execution of this
<span class="emphasis">*putstatic*</span> instruction causes
initialization of the referenced class or interface,
<span class="emphasis">*putstatic*</span> may throw an `Error` as
detailed in <a href="jvms-5.html#jvms-5.5" class="xref"
title="5.5. Initialization">§5.5</a>.

</div>

<div id="jvms-6.5.putstatic.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

A <span class="emphasis">*putstatic*</span> instruction may be used only
to set the value of an interface field on the initialization of that
field. Interface fields may be assigned to only once, on execution of an
interface variable initialization expression when the interface is
initialized (<a href="jvms-5.html#jvms-5.5" class="xref"
title="5.5. Initialization">§5.5</a>, JLS §9.3.1).

</div>

</div>

<div id="jvms-6.5.ret" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*ret*</span>

</div>

</div>

</div>

<div id="d5e24464" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Return from subroutine

</div>

<div id="d5e24467" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*ret*</span>  
<span class="emphasis">*index*</span>  

</div>

</div>

<div id="d5e24472" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*ret*</span> = 169 (0xa9)

</div>

<div id="d5e24476" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

No change

</div>

<div id="jvms-6.5.ret.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*index*</span> is an unsigned byte between 0
and 255, inclusive. The local variable at
<span class="emphasis">*index*</span> in the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>)
must contain a value of type `returnAddress`. The contents of the local
variable are written into the Java Virtual Machine's `pc` register, and
execution continues there.

</div>

<div id="jvms-6.5.ret.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

Note that <span class="emphasis">*jsr*</span>
(<a href="jvms-6.html#jvms-6.5.jsr" class="xref" title="jsr">§<span
class="emphasis"><em>jsr</em></span></a>) pushes the address onto the
operand stack and <span class="emphasis">*ret*</span> gets it out of a
local variable. This asymmetry is intentional.

In Oracle's implementation of a compiler for the Java programming
language prior to Java SE 6, the <span class="emphasis">*ret*</span>
instruction was used with the <span class="emphasis">*jsr*</span> and
<span class="emphasis">*jsr_w*</span> instructions
(<a href="jvms-6.html#jvms-6.5.jsr" class="xref" title="jsr">§<span
class="emphasis"><em>jsr</em></span></a>,
<a href="jvms-6.html#jvms-6.5.jsr_w" class="xref" title="jsr_w">§<span
class="emphasis"><em>jsr_w</em></span></a>) in the implementation of the
`finally` clause (<a href="jvms-3.html#jvms-3.13" class="xref"
title="3.13. Compiling finally">§3.13</a>,
<a href="jvms-4.html#jvms-4.10.2.5" class="xref"
title="4.10.2.5. Exceptions and finally">§4.10.2.5</a>).

The <span class="emphasis">*ret*</span> instruction should not be
confused with the <span class="emphasis">*return*</span> instruction
(<a href="jvms-6.html#jvms-6.5.return" class="xref" title="return">§<span
class="emphasis"><em>return</em></span></a>). A
<span class="emphasis">*return*</span> instruction returns control from
a method to its invoker, without passing any value back to the invoker.

The <span class="emphasis">*ret*</span> opcode can be used in
conjunction with the <span class="emphasis">*wide*</span> instruction
(<a href="jvms-6.html#jvms-6.5.wide" class="xref" title="wide">§<span
class="emphasis"><em>wide</em></span></a>) to access a local variable
using a two-byte unsigned index.

</div>

</div>

<div id="jvms-6.5.return" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*return*</span>

</div>

</div>

</div>

<div id="d5e24514" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Return `void` from method

</div>

<div id="d5e24518" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*return*</span>  

</div>

</div>

<div id="d5e24522" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*return*</span> = 177 (0xb1)

</div>

<div id="d5e24526" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

... <span class="symbol">→</span>

\[empty\]

</div>

<div id="jvms-6.5.return.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The current method must have return type `void`. If the current method
is a `synchronized` method, the monitor entered or reentered on
invocation of the method is updated and possibly exited as if by
execution of a <span class="emphasis">*monitorexit*</span> instruction
(<a href="jvms-6.html#jvms-6.5.monitorexit" class="xref"
title="monitorexit">§<span
class="emphasis"><em>monitorexit</em></span></a>) in the current thread.
If no exception is thrown, any values on the operand stack of the
current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>)
are discarded.

The interpreter then returns control to the invoker of the method,
reinstating the frame of the invoker.

</div>

<div id="jvms-6.5.return.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

If the Java Virtual Machine implementation does not enforce the rules on
structured locking described in
<a href="jvms-2.html#jvms-2.11.10" class="xref"
title="2.11.10. Synchronization">§2.11.10</a>, then if the current
method is a `synchronized` method and the current thread is not the
owner of the monitor entered or reentered on invocation of the method,
<span class="emphasis">*return*</span> throws an
`IllegalMonitorStateException`. This can happen, for example, if a
`synchronized` method contains a
<span class="emphasis">*monitorexit*</span> instruction, but no
<span class="emphasis">*monitorenter*</span> instruction, on the object
on which the method is `synchronized`.

Otherwise, if the Java Virtual Machine implementation enforces the rules
on structured locking described in
<a href="jvms-2.html#jvms-2.11.10" class="xref"
title="2.11.10. Synchronization">§2.11.10</a> and if the first of those
rules is violated during invocation of the current method, then
<span class="emphasis">*return*</span> throws an
`IllegalMonitorStateException`.

</div>

</div>

<div id="jvms-6.5.saload" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*saload*</span>

</div>

</div>

</div>

<div id="d5e24558" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Load `short` from array

</div>

<div id="d5e24562" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*saload*</span>  

</div>

</div>

<div id="d5e24566" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*saload*</span> = 53 (0x35)

</div>

<div id="d5e24570" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*arrayref*</span>,
<span class="emphasis">*index*</span> <span class="symbol">→</span>

..., <span class="emphasis">*value*</span>

</div>

<div id="jvms-6.5.saload.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*arrayref*</span> must be of type `reference`
and must refer to an array whose components are of type `short`. The
<span class="emphasis">*index*</span> must be of type `int`. Both
<span class="emphasis">*arrayref*</span> and
<span class="emphasis">*index*</span> are popped from the operand stack.
The component of the array at <span class="emphasis">*index*</span> is
retrieved and sign-extended to an `int`
<span class="emphasis">*value*</span>. That
<span class="emphasis">*value*</span> is pushed onto the operand stack.

</div>

<div id="jvms-6.5.saload.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

If <span class="emphasis">*arrayref*</span> is `null`,
<span class="emphasis">*saload*</span> throws a `NullPointerException`.

Otherwise, if <span class="emphasis">*index*</span> is not within the
bounds of the array referenced by
<span class="emphasis">*arrayref*</span>, the
<span class="emphasis">*saload*</span> instruction throws an
`ArrayIndexOutOfBoundsException`.

</div>

</div>

<div id="jvms-6.5.sastore" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*sastore*</span>

</div>

</div>

</div>

<div id="d5e24607" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Store into `short` array

</div>

<div id="d5e24611" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*sastore*</span>  

</div>

</div>

<div id="d5e24615" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*sastore*</span> = 86 (0x56)

</div>

<div id="d5e24619" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*arrayref*</span>,
<span class="emphasis">*index*</span>,
<span class="emphasis">*value*</span> <span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.sastore.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*arrayref*</span> must be of type `reference`
and must refer to an array whose components are of type `short`. Both
<span class="emphasis">*index*</span> and
<span class="emphasis">*value*</span> must be of type `int`. The
<span class="emphasis">*arrayref*</span>,
<span class="emphasis">*index*</span>, and
<span class="emphasis">*value*</span> are popped from the operand stack.
The `int` <span class="emphasis">*value*</span> is truncated to a
`short` and stored as the component of the array indexed by
<span class="emphasis">*index*</span>.

</div>

<div id="jvms-6.5.sastore.runtime" class="section">

<div class="titlepage">

<div>

<div>

#### Run-time Exceptions

</div>

</div>

</div>

If <span class="emphasis">*arrayref*</span> is `null`,
<span class="emphasis">*sastore*</span> throws a `NullPointerException`.

Otherwise, if <span class="emphasis">*index*</span> is not within the
bounds of the array referenced by
<span class="emphasis">*arrayref*</span>, the
<span class="emphasis">*sastore*</span> instruction throws an
`ArrayIndexOutOfBoundsException`.

</div>

</div>

<div id="jvms-6.5.sipush" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*sipush*</span>

</div>

</div>

</div>

<div id="d5e24658" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Push `short`

</div>

<div id="d5e24662" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*sipush*</span>  
<span class="emphasis">*byte1*</span>  
<span class="emphasis">*byte2*</span>  

</div>

</div>

<div id="d5e24668" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*sipush*</span> = 17 (0x11)

</div>

<div id="d5e24672" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

... <span class="symbol">→</span>

..., <span class="emphasis">*value*</span>

</div>

<div id="jvms-6.5.sipush.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The immediate unsigned <span class="emphasis">*byte1*</span> and
<span class="emphasis">*byte2*</span> values are assembled into an
intermediate `short`, where the value of the `short` is
(<span class="emphasis">*byte1*</span> `<<` 8) \|
<span class="emphasis">*byte2*</span>. The intermediate value is then
sign-extended to an `int` <span class="emphasis">*value*</span>. That
<span class="emphasis">*value*</span> is pushed onto the operand stack.

</div>

</div>

<div id="jvms-6.5.swap" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*swap*</span>

</div>

</div>

</div>

<div id="d5e24694" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Swap the top two operand stack values

</div>

<div id="d5e24697" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*swap*</span>  

</div>

</div>

<div id="d5e24701" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*swap*</span> = 95 (0x5f)

</div>

<div id="d5e24705" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*value2*</span>,
<span class="emphasis">*value1*</span> <span class="symbol">→</span>

..., <span class="emphasis">*value1*</span>,
<span class="emphasis">*value2*</span>

</div>

<div id="jvms-6.5.swap.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

Swap the top two values on the operand stack.

The <span class="emphasis">*swap*</span> instruction must not be used
unless <span class="emphasis">*value1*</span> and
<span class="emphasis">*value2*</span> are both values of a category 1
computational type (<a href="jvms-2.html#jvms-2.11.1" class="xref"
title="2.11.1. Types and the Java Virtual Machine">§2.11.1</a>).

</div>

<div id="jvms-6.5.swap.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The Java Virtual Machine does not provide an instruction implementing a
swap on operands of category 2 computational types.

</div>

</div>

<div id="jvms-6.5.tableswitch" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*tableswitch*</span>

</div>

</div>

</div>

<div id="d5e24728" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Access jump table by index and jump

</div>

<div id="d5e24731" class="section">

<div class="titlepage">

<div>

<div>

#### Format

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*tableswitch*</span>  
<span class="emphasis">*\<0-3 byte pad\>*</span>  
<span class="emphasis">*defaultbyte1*</span>  
<span class="emphasis">*defaultbyte2*</span>  
<span class="emphasis">*defaultbyte3*</span>  
<span class="emphasis">*defaultbyte4*</span>  
<span class="emphasis">*lowbyte1*</span>  
<span class="emphasis">*lowbyte2*</span>  
<span class="emphasis">*lowbyte3*</span>  
<span class="emphasis">*lowbyte4*</span>  
<span class="emphasis">*highbyte1*</span>  
<span class="emphasis">*highbyte2*</span>  
<span class="emphasis">*highbyte3*</span>  
<span class="emphasis">*highbyte4*</span>  
<span class="emphasis">*jump offsets...*</span>  

</div>

</div>

<div id="d5e24749" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*tableswitch*</span> = 170 (0xaa)

</div>

<div id="d5e24753" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

..., <span class="emphasis">*index*</span> <span class="symbol">→</span>

...

</div>

<div id="jvms-6.5.tableswitch.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

A <span class="emphasis">*tableswitch*</span> is a variable-length
instruction. Immediately after the
<span class="emphasis">*tableswitch*</span> opcode, between zero and
three bytes must act as padding, such that
<span class="emphasis">*defaultbyte1*</span> begins at an address that
is a multiple of four bytes from the start of the current method (the
opcode of its first instruction). Immediately after the padding are
bytes constituting three signed 32-bit values:
<span class="emphasis">*default*</span>,
<span class="emphasis">*low*</span>, and
<span class="emphasis">*high*</span>. Immediately following are bytes
constituting a series of <span class="emphasis">*high*</span> -
<span class="emphasis">*low*</span> + 1 signed 32-bit offsets. The value
<span class="emphasis">*low*</span> must be less than or equal to
<span class="emphasis">*high*</span>. The
<span class="emphasis">*high*</span> -
<span class="emphasis">*low*</span> + 1 signed 32-bit offsets are
treated as a 0-based jump table. Each of these signed 32-bit values is
constructed as (<span class="emphasis">*byte1*</span> `<<` 24) \|
(<span class="emphasis">*byte2*</span> `<<` 16) \|
(<span class="emphasis">*byte3*</span> `<<` 8) \|
<span class="emphasis">*byte4*</span>.

The <span class="emphasis">*index*</span> must be of type `int` and is
popped from the operand stack. If <span class="emphasis">*index*</span>
is less than <span class="emphasis">*low*</span> or
<span class="emphasis">*index*</span> is greater than
<span class="emphasis">*high*</span>, then a target address is
calculated by adding <span class="emphasis">*default*</span> to the
address of the opcode of this
<span class="emphasis">*tableswitch*</span> instruction. Otherwise, the
offset at position <span class="emphasis">*index*</span> -
<span class="emphasis">*low*</span> of the jump table is extracted. The
target address is calculated by adding that offset to the address of the
opcode of this <span class="emphasis">*tableswitch*</span> instruction.
Execution then continues at the target address.

The target address that can be calculated from each jump table offset,
as well as the one that can be calculated from
<span class="emphasis">*default*</span>, must be the address of an
opcode of an instruction within the method that contains this
<span class="emphasis">*tableswitch*</span> instruction.

</div>

<div id="jvms-6.5.tableswitch.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

The alignment required of the 4-byte operands of the
<span class="emphasis">*tableswitch*</span> instruction guarantees
4-byte alignment of those operands if and only if the method that
contains the <span class="emphasis">*tableswitch*</span> starts on a
4-byte boundary.

</div>

</div>

<div id="jvms-6.5.wide" class="section-execution">

<div class="titlepage">

<div>

<div>

### <span class="emphasis">*wide*</span>

</div>

</div>

</div>

<div id="d5e24804" class="section">

<div class="titlepage">

<div>

<div>

#### Operation

</div>

</div>

</div>

Extend local variable index by additional bytes

</div>

<div id="d5e24807" class="section">

<div class="titlepage">

<div>

<div>

#### Format 1

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*wide*</span>  
<span class="emphasis">*\<opcode\>*</span>  
<span class="emphasis">*indexbyte1*</span>  
<span class="emphasis">*indexbyte2*</span>  

</div>

where <span class="emphasis">*\<opcode\>*</span> is one of
<span class="emphasis">*iload*</span>,
<span class="emphasis">*fload*</span>,
<span class="emphasis">*aload*</span>,
<span class="emphasis">*lload*</span>,
<span class="emphasis">*dload*</span>,
<span class="emphasis">*istore*</span>,
<span class="emphasis">*fstore*</span>,
<span class="emphasis">*astore*</span>,
<span class="emphasis">*lstore*</span>,
<span class="emphasis">*dstore*</span>, or
<span class="emphasis">*ret*</span>

</div>

<div id="d5e24827" class="section">

<div class="titlepage">

<div>

<div>

#### Format 2

</div>

</div>

</div>

<div class="literallayout">

  
<span class="emphasis">*wide*</span>  
<span class="emphasis">*iinc*</span>  
<span class="emphasis">*indexbyte1*</span>  
<span class="emphasis">*indexbyte2*</span>  
<span class="emphasis">*constbyte1*</span>  
<span class="emphasis">*constbyte2*</span>  

</div>

</div>

<div id="d5e24836" class="section">

<div class="titlepage">

<div>

<div>

#### Forms

</div>

</div>

</div>

<span class="emphasis">*wide*</span> = 196 (0xc4)

</div>

<div id="d5e24840" class="section">

<div class="titlepage">

<div>

<div>

#### Operand Stack

</div>

</div>

</div>

Same as modified instruction

</div>

<div id="jvms-6.5.wide.desc" class="section">

<div class="titlepage">

<div>

<div>

#### Description

</div>

</div>

</div>

The <span class="emphasis">*wide*</span> instruction modifies the
behavior of another instruction. It takes one of two formats, depending
on the instruction being modified. The first form of the
<span class="emphasis">*wide*</span> instruction modifies one of the
instructions <span class="emphasis">*iload*</span>,
<span class="emphasis">*fload*</span>,
<span class="emphasis">*aload*</span>,
<span class="emphasis">*lload*</span>,
<span class="emphasis">*dload*</span>,
<span class="emphasis">*istore*</span>,
<span class="emphasis">*fstore*</span>,
<span class="emphasis">*astore*</span>,
<span class="emphasis">*lstore*</span>,
<span class="emphasis">*dstore*</span>, or
<span class="emphasis">*ret*</span>
(<a href="jvms-6.html#jvms-6.5.iload" class="xref" title="iload">§<span
class="emphasis"><em>iload</em></span></a>,
<a href="jvms-6.html#jvms-6.5.fload" class="xref" title="fload">§<span
class="emphasis"><em>fload</em></span></a>,
<a href="jvms-6.html#jvms-6.5.aload" class="xref" title="aload">§<span
class="emphasis"><em>aload</em></span></a>,
<a href="jvms-6.html#jvms-6.5.lload" class="xref" title="lload">§<span
class="emphasis"><em>lload</em></span></a>,
<a href="jvms-6.html#jvms-6.5.dload" class="xref" title="dload">§<span
class="emphasis"><em>dload</em></span></a>,
<a href="jvms-6.html#jvms-6.5.istore" class="xref" title="istore">§<span
class="emphasis"><em>istore</em></span></a>,
<a href="jvms-6.html#jvms-6.5.fstore" class="xref" title="fstore">§<span
class="emphasis"><em>fstore</em></span></a>,
<a href="jvms-6.html#jvms-6.5.astore" class="xref" title="astore">§<span
class="emphasis"><em>astore</em></span></a>,
<a href="jvms-6.html#jvms-6.5.lstore" class="xref" title="lstore">§<span
class="emphasis"><em>lstore</em></span></a>,
<a href="jvms-6.html#jvms-6.5.dstore" class="xref" title="dstore">§<span
class="emphasis"><em>dstore</em></span></a>,
<a href="jvms-6.html#jvms-6.5.ret" class="xref" title="ret">§<span
class="emphasis"><em>ret</em></span></a>). The second form applies only
to the <span class="emphasis">*iinc*</span> instruction
(<a href="jvms-6.html#jvms-6.5.iinc" class="xref" title="iinc">§<span
class="emphasis"><em>iinc</em></span></a>).

In either case, the <span class="emphasis">*wide*</span> opcode itself
is followed in the compiled code by the opcode of the instruction
<span class="emphasis">*wide*</span> modifies. In either form, two
unsigned bytes <span class="emphasis">*indexbyte1*</span> and
<span class="emphasis">*indexbyte2*</span> follow the modified opcode
and are assembled into a 16-bit unsigned index to a local variable in
the current frame
(<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>),
where the value of the index is
(<span class="emphasis">*indexbyte1*</span> `<<` 8) \|
<span class="emphasis">*indexbyte2*</span>. The calculated index must be
an index into the local variable array of the current frame. Where the
<span class="emphasis">*wide*</span> instruction modifies an
<span class="emphasis">*lload*</span>,
<span class="emphasis">*dload*</span>,
<span class="emphasis">*lstore*</span>, or
<span class="emphasis">*dstore*</span> instruction, the index following
the calculated index (index + 1) must also be an index into the local
variable array. In the second form, two immediate unsigned bytes
<span class="emphasis">*constbyte1*</span> and
<span class="emphasis">*constbyte2*</span> follow
<span class="emphasis">*indexbyte1*</span> and
<span class="emphasis">*indexbyte2*</span> in the code stream. Those
bytes are also assembled into a signed 16-bit constant, where the
constant is (<span class="emphasis">*constbyte1*</span> `<<` 8) \|
<span class="emphasis">*constbyte2*</span>.

The widened bytecode operates as normal, except for the use of the wider
index and, in the case of the second form, the larger increment range.

</div>

<div id="jvms-6.5.wide.notes" class="section">

<div class="titlepage">

<div>

<div>

#### Notes

</div>

</div>

</div>

Although we say that <span class="emphasis">*wide*</span> "modifies the
behavior of another instruction," the
<span class="emphasis">*wide*</span> instruction effectively treats the
bytes constituting the modified instruction as operands, denaturing the
embedded instruction in the process. In the case of a modified
<span class="emphasis">*iinc*</span> instruction, one of the logical
operands of the <span class="emphasis">*iinc*</span> is not even at the
normal offset from the opcode. The embedded instruction must never be
executed directly; its opcode must never be the target of any control
transfer instruction.

</div>

</div>

</div>

</div>

<div class="navfooter">

------------------------------------------------------------------------

|  |  |  |
|:---|:--:|---:|
| <a href="jvms-5.html" accesskey="p">Prev</a>  |   |  <a href="jvms-7.html" accesskey="n">Next</a> |
| Chapter 5. Loading, Linking, and Initializing  | <a href="index.html" accesskey="h">Home</a> |  Chapter 7. Opcode Mnemonics by Opcode |

</div>

<div class="navfooter">

------------------------------------------------------------------------

[Legal Notice](spec-frontmatter.html)

</div>
