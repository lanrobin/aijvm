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
<th colspan="3" style="text-align: center;">Chapter 4. The <code
class="literal">class</code> File Format</th>
</tr>
</thead>
<tbody>
<tr>
<td style="text-align: left; width: 20%;"><a href="jvms-3.html"
accesskey="p">Prev</a> </td>
<td style="text-align: center; width: 60%;"> </td>
<td style="text-align: right; width: 20%;"> <a href="jvms-5.html"
accesskey="n">Next</a></td>
</tr>
</tbody>
</table>

------------------------------------------------------------------------

</div>

<div id="jvms-4" class="chapter" lang="en">

<div class="titlepage">

<div>

<div>

# Chapter 4. The `class` File Format

</div>

</div>

</div>

<div class="toc">

**Table of Contents**

<span class="section">[4.1. The `ClassFile`
Structure](jvms-4.html#jvms-4.1)</span>

<span class="section">[4.2. Names](jvms-4.html#jvms-4.2)</span>

<span class="section">[4.2.1. Binary Class and Interface
Names](jvms-4.html#jvms-4.2.1)</span>

<span class="section">[4.2.2. Unqualified
Names](jvms-4.html#jvms-4.2.2)</span>

<span class="section">[4.2.3. Module and Package
Names](jvms-4.html#jvms-4.2.3)</span>

<span class="section">[4.3. Descriptors](jvms-4.html#jvms-4.3)</span>

<span class="section">[4.3.1. Grammar
Notation](jvms-4.html#jvms-4.3.1)</span>

<span class="section">[4.3.2. Field
Descriptors](jvms-4.html#jvms-4.3.2)</span>

<span class="section">[4.3.3. Method
Descriptors](jvms-4.html#jvms-4.3.3)</span>

<span class="section">[4.4. The Constant
Pool](jvms-4.html#jvms-4.4)</span>

<span class="section">[4.4.1. The `CONSTANT_Class_info`
Structure](jvms-4.html#jvms-4.4.1)</span>

<span class="section">[4.4.2. The `CONSTANT_Fieldref_info`,
`CONSTANT_Methodref_info`, and `CONSTANT_InterfaceMethodref_info`
Structures](jvms-4.html#jvms-4.4.2)</span>

<span class="section">[4.4.3. The `CONSTANT_String_info`
Structure](jvms-4.html#jvms-4.4.3)</span>

<span class="section">[4.4.4. The `CONSTANT_Integer_info` and
`CONSTANT_Float_info` Structures](jvms-4.html#jvms-4.4.4) </span>

<span class="section">[4.4.5. The `CONSTANT_Long_info` and
`CONSTANT_Double_info` Structures](jvms-4.html#jvms-4.4.5)</span>

<span class="section">[4.4.6. The `CONSTANT_NameAndType_info`
Structure](jvms-4.html#jvms-4.4.6)</span>

<span class="section">[4.4.7. The `CONSTANT_Utf8_info`
Structure](jvms-4.html#jvms-4.4.7)</span>

<span class="section">[4.4.8. The `CONSTANT_MethodHandle_info`
Structure](jvms-4.html#jvms-4.4.8)</span>

<span class="section">[4.4.9. The `CONSTANT_MethodType_info`
Structure](jvms-4.html#jvms-4.4.9)</span>

<span class="section">[4.4.10. The `CONSTANT_Dynamic_info` and
`CONSTANT_InvokeDynamic_info`
Structures](jvms-4.html#jvms-4.4.10)</span>

<span class="section">[4.4.11. The `CONSTANT_Module_info`
Structure](jvms-4.html#jvms-4.4.11)</span>

<span class="section">[4.4.12. The `CONSTANT_Package_info`
Structure](jvms-4.html#jvms-4.4.12)</span>

<span class="section">[4.5. Fields](jvms-4.html#jvms-4.5)</span>

<span class="section">[4.6. Methods](jvms-4.html#jvms-4.6)</span>

<span class="section">[4.7. Attributes](jvms-4.html#jvms-4.7)</span>

<span class="section">[4.7.1. Defining and Naming New
Attributes](jvms-4.html#jvms-4.7.1)</span>

<span class="section">[4.7.2. The `ConstantValue`
Attribute](jvms-4.html#jvms-4.7.2)</span>

<span class="section">[4.7.3. The `Code`
Attribute](jvms-4.html#jvms-4.7.3)</span>

<span class="section">[4.7.4. The `StackMapTable`
Attribute](jvms-4.html#jvms-4.7.4)</span>

<span class="section">[4.7.5. The `Exceptions`
Attribute](jvms-4.html#jvms-4.7.5)</span>

<span class="section">[4.7.6. The `InnerClasses`
Attribute](jvms-4.html#jvms-4.7.6)</span>

<span class="section">[4.7.7. The `EnclosingMethod`
Attribute](jvms-4.html#jvms-4.7.7)</span>

<span class="section">[4.7.8. The `Synthetic`
Attribute](jvms-4.html#jvms-4.7.8)</span>

<span class="section">[4.7.9. The `Signature`
Attribute](jvms-4.html#jvms-4.7.9)</span>

<span class="section">[4.7.9.1.
Signatures](jvms-4.html#jvms-4.7.9.1)</span>

<span class="section">[4.7.10. The `SourceFile`
Attribute](jvms-4.html#jvms-4.7.10)</span>

<span class="section">[4.7.11. The `SourceDebugExtension`
Attribute](jvms-4.html#jvms-4.7.11)</span>

<span class="section">[4.7.12. The `LineNumberTable`
Attribute](jvms-4.html#jvms-4.7.12)</span>

<span class="section">[4.7.13. The `LocalVariableTable`
Attribute](jvms-4.html#jvms-4.7.13)</span>

<span class="section">[4.7.14. The `LocalVariableTypeTable`
Attribute](jvms-4.html#jvms-4.7.14)</span>

<span class="section">[4.7.15. The `Deprecated`
Attribute](jvms-4.html#jvms-4.7.15)</span>

<span class="section">[4.7.16. The `RuntimeVisibleAnnotations`
Attribute](jvms-4.html#jvms-4.7.16)</span>

<span class="section">[4.7.16.1. The `element_value`
structure](jvms-4.html#jvms-4.7.16.1)</span>

<span class="section">[4.7.17. The `RuntimeInvisibleAnnotations`
Attribute](jvms-4.html#jvms-4.7.17)</span>

<span class="section">[4.7.18. The `RuntimeVisibleParameterAnnotations`
Attribute](jvms-4.html#jvms-4.7.18)</span>

<span class="section">[4.7.19. The
`RuntimeInvisibleParameterAnnotations`
Attribute](jvms-4.html#jvms-4.7.19)</span>

<span class="section">[4.7.20. The `RuntimeVisibleTypeAnnotations`
Attribute](jvms-4.html#jvms-4.7.20)</span>

<span class="section">[4.7.20.1. The `target_info`
union](jvms-4.html#jvms-4.7.20.1)</span>

<span class="section">[4.7.20.2. The `type_path`
structure](jvms-4.html#jvms-4.7.20.2)</span>

<span class="section">[4.7.21. The `RuntimeInvisibleTypeAnnotations`
Attribute](jvms-4.html#jvms-4.7.21)</span>

<span class="section">[4.7.22. The `AnnotationDefault`
Attribute](jvms-4.html#jvms-4.7.22)</span>

<span class="section">[4.7.23. The `BootstrapMethods`
Attribute](jvms-4.html#jvms-4.7.23)</span>

<span class="section">[4.7.24. The `MethodParameters`
Attribute](jvms-4.html#jvms-4.7.24)</span>

<span class="section">[4.7.25. The `Module`
Attribute](jvms-4.html#jvms-4.7.25)</span>

<span class="section">[4.7.26. The `ModulePackages`
Attribute](jvms-4.html#jvms-4.7.26)</span>

<span class="section">[4.7.27. The `ModuleMainClass`
Attribute](jvms-4.html#jvms-4.7.27)</span>

<span class="section">[4.7.28. The `NestHost`
Attribute](jvms-4.html#jvms-4.7.28)</span>

<span class="section">[4.7.29. The `NestMembers`
Attribute](jvms-4.html#jvms-4.7.29)</span>

<span class="section">[4.7.30. The `Record`
Attribute](jvms-4.html#jvms-4.7.30)</span>

<span class="section">[4.7.31. The `PermittedSubclasses`
Attribute](jvms-4.html#jvms-4.7.31)</span>

<span class="section">[4.8. Format
Checking](jvms-4.html#jvms-4.8)</span>

<span class="section">[4.9. Constraints on Java Virtual Machine
Code](jvms-4.html#jvms-4.9)</span>

<span class="section">[4.9.1. Static
Constraints](jvms-4.html#jvms-4.9.1)</span>

<span class="section">[4.9.2. Structural
Constraints](jvms-4.html#jvms-4.9.2)</span>

<span class="section">[4.10. Verification of `class`
Files](jvms-4.html#jvms-4.10)</span>

<span class="section">[4.10.1. Verification by Type
Checking](jvms-4.html#jvms-4.10.1)</span>

<span class="section">[4.10.1.1. Accessors for Java Virtual Machine
Artifacts](jvms-4.html#jvms-4.10.1.1)</span>

<span class="section">[4.10.1.2. Verification Type
System](jvms-4.html#jvms-4.10.1.2)</span>

<span class="section">[4.10.1.3. Instruction
Representation](jvms-4.html#jvms-4.10.1.3)</span>

<span class="section">[4.10.1.4. Stack Map Frames and Type
Transitions](jvms-4.html#jvms-4.10.1.4)</span>

<span class="section">[4.10.1.5. Type Checking
Methods](jvms-4.html#jvms-4.10.1.5)</span>

<span class="section">[4.10.1.6. Type Checking Code
Streams](jvms-4.html#jvms-4.10.1.6)</span>

<span class="section">[4.10.1.7. Type Checking Load and Store
Instructions](jvms-4.html#jvms-4.10.1.7)</span>

<span class="section">[4.10.1.8. Type Checking for `protected`
Members](jvms-4.html#jvms-4.10.1.8)</span>

<span class="section">[4.10.1.9. Type Checking
Instructions](jvms-4.html#jvms-4.10.1.9)</span>

<span class="section">[<span class="emphasis">*aaload*</span>](jvms-4.html#jvms-4.10.1.9.aaload)</span>

<span class="section">[<span class="emphasis">*aastore*</span>](jvms-4.html#jvms-4.10.1.9.aastore)</span>

<span class="section">[<span class="emphasis">*aconst_null*</span>](jvms-4.html#jvms-4.10.1.9.aconst_null)</span>

<span class="section">[<span class="emphasis">*aload*</span>,
<span class="emphasis">*aload\_\<n\>*</span>](jvms-4.html#jvms-4.10.1.9.aload)</span>

<span class="section">[<span class="emphasis">*anewarray*</span>](jvms-4.html#jvms-4.10.1.9.anewarray)</span>

<span class="section">[<span class="emphasis">*areturn*</span>](jvms-4.html#jvms-4.10.1.9.areturn)</span>

<span class="section">[<span class="emphasis">*arraylength*</span>](jvms-4.html#jvms-4.10.1.9.arraylength)</span>

<span class="section">[<span class="emphasis">*astore*</span>,
<span class="emphasis">*astore\_\<n\>*</span>](jvms-4.html#jvms-4.10.1.9.astore)</span>

<span class="section">[<span class="emphasis">*athrow*</span>](jvms-4.html#jvms-4.10.1.9.athrow)</span>

<span class="section">[<span class="emphasis">*baload*</span>](jvms-4.html#jvms-4.10.1.9.baload)</span>

<span class="section">[<span class="emphasis">*bastore*</span>](jvms-4.html#jvms-4.10.1.9.bastore)</span>

<span class="section">[<span class="emphasis">*bipush*</span>](jvms-4.html#jvms-4.10.1.9.bipush)</span>

<span class="section">[<span class="emphasis">*caload*</span>](jvms-4.html#jvms-4.10.1.9.caload)</span>

<span class="section">[<span class="emphasis">*castore*</span>](jvms-4.html#jvms-4.10.1.9.castore)</span>

<span class="section">[<span class="emphasis">*checkcast*</span>](jvms-4.html#jvms-4.10.1.9.checkcast)</span>

<span class="section">[<span class="emphasis">*d2f*</span>,
<span class="emphasis">*d2i*</span>,
<span class="emphasis">*d2l*</span>](jvms-4.html#jvms-4.10.1.9.d2f)</span>

<span class="section">[<span class="emphasis">*dadd*</span>](jvms-4.html#jvms-4.10.1.9.dadd)</span>

<span class="section">[<span class="emphasis">*daload*</span>](jvms-4.html#jvms-4.10.1.9.daload)</span>

<span class="section">[<span class="emphasis">*dastore*</span>](jvms-4.html#jvms-4.10.1.9.dastore)</span>

<span class="section">[<span class="emphasis">*dcmp\<op\>*</span>](jvms-4.html#jvms-4.10.1.9.dcmp_op)</span>

<span class="section">[<span class="emphasis">*dconst\_\<d\>*</span>](jvms-4.html#jvms-4.10.1.9.dconst_d)</span>

<span class="section">[<span class="emphasis">*ddiv*</span>](jvms-4.html#jvms-4.10.1.9.ddiv)</span>

<span class="section">[<span class="emphasis">*dload*</span>,
<span class="emphasis">*dload\_\<n\>*</span>](jvms-4.html#jvms-4.10.1.9.dload)</span>

<span class="section">[<span class="emphasis">*dmul*</span>](jvms-4.html#jvms-4.10.1.9.dmul)</span>

<span class="section">[<span class="emphasis">*dneg*</span>](jvms-4.html#jvms-4.10.1.9.dneg)</span>

<span class="section">[<span class="emphasis">*drem*</span>](jvms-4.html#jvms-4.10.1.9.drem)</span>

<span class="section">[<span class="emphasis">*dreturn*</span>](jvms-4.html#jvms-4.10.1.9.dreturn)</span>

<span class="section">[<span class="emphasis">*dstore*</span>,
<span class="emphasis">*dstore\_\<n\>*</span>](jvms-4.html#jvms-4.10.1.9.dstore)</span>

<span class="section">[<span class="emphasis">*dsub*</span>](jvms-4.html#jvms-4.10.1.9.dsub)</span>

<span class="section">[<span class="emphasis">*dup*</span>](jvms-4.html#jvms-4.10.1.9.dup)</span>

<span class="section">[<span class="emphasis">*dup_x1*</span>](jvms-4.html#jvms-4.10.1.9.dup_x1)</span>

<span class="section">[<span class="emphasis">*dup_x2*</span>](jvms-4.html#jvms-4.10.1.9.dup_x2)</span>

<span class="section">[<span class="emphasis">*dup2*</span>](jvms-4.html#jvms-4.10.1.9.dup2)</span>

<span class="section">[<span class="emphasis">*dup2_x1*</span>](jvms-4.html#jvms-4.10.1.9.dup2_x1)</span>

<span class="section">[<span class="emphasis">*dup2_x2*</span>](jvms-4.html#jvms-4.10.1.9.dup2_x2)</span>

<span class="section">[<span class="emphasis">*f2d*</span>,
<span class="emphasis">*f2i*</span>,
<span class="emphasis">*f2l*</span>](jvms-4.html#jvms-4.10.1.9.f2d)</span>

<span class="section">[<span class="emphasis">*fadd*</span>](jvms-4.html#jvms-4.10.1.9.fadd)</span>

<span class="section">[<span class="emphasis">*faload*</span>](jvms-4.html#jvms-4.10.1.9.faload)</span>

<span class="section">[<span class="emphasis">*fastore*</span>](jvms-4.html#jvms-4.10.1.9.fastore)</span>

<span class="section">[<span class="emphasis">*fcmp\<op\>*</span>](jvms-4.html#jvms-4.10.1.9.fcmp_op)</span>

<span class="section">[<span class="emphasis">*fconst\_\<f\>*</span>](jvms-4.html#jvms-4.10.1.9.fconst_f)</span>

<span class="section">[<span class="emphasis">*fdiv*</span>](jvms-4.html#jvms-4.10.1.9.fdiv)</span>

<span class="section">[<span class="emphasis">*fload*</span>,
<span class="emphasis">*fload\_\<n\>*</span>](jvms-4.html#jvms-4.10.1.9.fload)</span>

<span class="section">[<span class="emphasis">*fmul*</span>](jvms-4.html#jvms-4.10.1.9.fmul)</span>

<span class="section">[<span class="emphasis">*fneg*</span>](jvms-4.html#jvms-4.10.1.9.fneg)</span>

<span class="section">[<span class="emphasis">*frem*</span>](jvms-4.html#jvms-4.10.1.9.frem)</span>

<span class="section">[<span class="emphasis">*freturn*</span>](jvms-4.html#jvms-4.10.1.9.freturn)</span>

<span class="section">[<span class="emphasis">*fstore*</span>,
<span class="emphasis">*fstore\_\<n\>*</span>](jvms-4.html#jvms-4.10.1.9.fstore)</span>

<span class="section">[<span class="emphasis">*fsub*</span>](jvms-4.html#jvms-4.10.1.9.fsub)</span>

<span class="section">[<span class="emphasis">*getfield*</span>](jvms-4.html#jvms-4.10.1.9.getfield)</span>

<span class="section">[<span class="emphasis">*getstatic*</span>](jvms-4.html#jvms-4.10.1.9.getstatic)</span>

<span class="section">[<span class="emphasis">*goto*</span>,
<span class="emphasis">*goto_w*</span>](jvms-4.html#jvms-4.10.1.9.goto)</span>

<span class="section">[<span class="emphasis">*i2b*</span>,
<span class="emphasis">*i2c*</span>,
<span class="emphasis">*i2d*</span>,
<span class="emphasis">*i2f*</span>,
<span class="emphasis">*i2l*</span>,
<span class="emphasis">*i2s*</span>](jvms-4.html#jvms-4.10.1.9.i2b)</span>

<span class="section">[<span class="emphasis">*iadd*</span>](jvms-4.html#jvms-4.10.1.9.iadd)</span>

<span class="section">[<span class="emphasis">*iaload*</span>](jvms-4.html#jvms-4.10.1.9.iaload)</span>

<span class="section">[<span class="emphasis">*iand*</span>](jvms-4.html#jvms-4.10.1.9.iand)</span>

<span class="section">[<span class="emphasis">*iastore*</span>](jvms-4.html#jvms-4.10.1.9.iastore)</span>

<span class="section">[<span class="emphasis">*iconst\_\<i\>*</span>](jvms-4.html#jvms-4.10.1.9.iconst_i)</span>

<span class="section">[<span class="emphasis">*idiv*</span>](jvms-4.html#jvms-4.10.1.9.idiv)</span>

<span class="section">[<span class="emphasis">*if_acmp\<cond\>*</span>](jvms-4.html#jvms-4.10.1.9.if_acmp_cond)</span>

<span class="section">[<span class="emphasis">*if_icmp\<cond\>*</span>](jvms-4.html#jvms-4.10.1.9.if_icmp_cond)</span>

<span class="section">[<span class="emphasis">*if\<cond\>*</span>](jvms-4.html#jvms-4.10.1.9.if_cond)</span>

<span class="section">[<span class="emphasis">*ifnonnull*</span>,
<span class="emphasis">*ifnull*</span>](jvms-4.html#jvms-4.10.1.9.ifnonnull)</span>

<span class="section">[<span class="emphasis">*iinc*</span>](jvms-4.html#jvms-4.10.1.9.iinc)</span>

<span class="section">[<span class="emphasis">*iload*</span>,
<span class="emphasis">*iload\_\<n\>*</span>](jvms-4.html#jvms-4.10.1.9.iload)</span>

<span class="section">[<span class="emphasis">*imul*</span>](jvms-4.html#jvms-4.10.1.9.imul)</span>

<span class="section">[<span class="emphasis">*ineg*</span>](jvms-4.html#jvms-4.10.1.9.ineg)</span>

<span class="section">[<span class="emphasis">*instanceof*</span>](jvms-4.html#jvms-4.10.1.9.instanceof)</span>

<span class="section">[<span class="emphasis">*invokedynamic*</span>](jvms-4.html#jvms-4.10.1.9.invokedynamic)</span>

<span class="section">[<span class="emphasis">*invokeinterface*</span>](jvms-4.html#jvms-4.10.1.9.invokeinterface)</span>

<span class="section">[<span class="emphasis">*invokespecial*</span>](jvms-4.html#jvms-4.10.1.9.invokespecial)</span>

<span class="section">[<span class="emphasis">*invokestatic*</span>](jvms-4.html#jvms-4.10.1.9.invokestatic)</span>

<span class="section">[<span class="emphasis">*invokevirtual*</span>](jvms-4.html#jvms-4.10.1.9.invokevirtual)</span>

<span class="section">[<span class="emphasis">*ior*</span>,
<span class="emphasis">*irem*</span>](jvms-4.html#jvms-4.10.1.9.ior)</span>

<span class="section">[<span class="emphasis">*ireturn*</span>](jvms-4.html#jvms-4.10.1.9.ireturn)</span>

<span class="section">[<span class="emphasis">*ishl*</span>,
<span class="emphasis">*ishr*</span>,
<span class="emphasis">*iushr*</span>](jvms-4.html#jvms-4.10.1.9.ishl)</span>

<span class="section">[<span class="emphasis">*istore*</span>,
<span class="emphasis">*istore\_\<n\>*</span>](jvms-4.html#jvms-4.10.1.9.istore)</span>

<span class="section">[<span class="emphasis">*isub*</span>,
<span class="emphasis">*ixor*</span>](jvms-4.html#jvms-4.10.1.9.isub)</span>

<span class="section">[<span class="emphasis">*l2d*</span>,
<span class="emphasis">*l2f*</span>,
<span class="emphasis">*l2i*</span>](jvms-4.html#jvms-4.10.1.9.l2d)</span>

<span class="section">[<span class="emphasis">*ladd*</span>](jvms-4.html#jvms-4.10.1.9.ladd)</span>

<span class="section">[<span class="emphasis">*laload*</span>](jvms-4.html#jvms-4.10.1.9.laload)</span>

<span class="section">[<span class="emphasis">*land*</span>](jvms-4.html#jvms-4.10.1.9.land)</span>

<span class="section">[<span class="emphasis">*lastore*</span>](jvms-4.html#jvms-4.10.1.9.lastore)</span>

<span class="section">[<span class="emphasis">*lcmp*</span>](jvms-4.html#jvms-4.10.1.9.lcmp)</span>

<span class="section">[<span class="emphasis">*lconst\_\<l\>*</span>](jvms-4.html#jvms-4.10.1.9.lconst_l)</span>

<span class="section">[<span class="emphasis">*ldc*</span>,
<span class="emphasis">*ldc_w*</span>,
<span class="emphasis">*ldc2_w*</span>](jvms-4.html#jvms-4.10.1.9.ldc)</span>

<span class="section">[<span class="emphasis">*ldiv*</span>](jvms-4.html#jvms-4.10.1.9.ldiv)</span>

<span class="section">[<span class="emphasis">*lload*</span>,
<span class="emphasis">*lload\_\<n\>*</span>](jvms-4.html#jvms-4.10.1.9.lload)</span>

<span class="section">[<span class="emphasis">*lmul*</span>](jvms-4.html#jvms-4.10.1.9.lmul)</span>

<span class="section">[<span class="emphasis">*lneg*</span>](jvms-4.html#jvms-4.10.1.9.lneg)</span>

<span class="section">[<span class="emphasis">*lookupswitch*</span>](jvms-4.html#jvms-4.10.1.9.lookupswitch)</span>

<span class="section">[<span class="emphasis">*lor*</span>,
<span class="emphasis">*lrem*</span>](jvms-4.html#jvms-4.10.1.9.lor)</span>

<span class="section">[<span class="emphasis">*lreturn*</span>](jvms-4.html#jvms-4.10.1.9.lreturn)</span>

<span class="section">[<span class="emphasis">*lshl*</span>,
<span class="emphasis">*lshr*</span>,
<span class="emphasis">*lushr*</span>](jvms-4.html#jvms-4.10.1.9.lshl)</span>

<span class="section">[<span class="emphasis">*lstore*</span>,
<span class="emphasis">*lstore\_\<n\>*</span>](jvms-4.html#jvms-4.10.1.9.lstore)</span>

<span class="section">[<span class="emphasis">*lsub*</span>,
<span class="emphasis">*lxor*</span>](jvms-4.html#jvms-4.10.1.9.lsub)</span>

<span class="section">[<span class="emphasis">*monitorenter*</span>,
<span class="emphasis">*monitorexit*</span>](jvms-4.html#jvms-4.10.1.9.monitorenter)</span>

<span class="section">[<span class="emphasis">*multianewarray*</span>](jvms-4.html#jvms-4.10.1.9.multianewarray)</span>

<span class="section">[<span class="emphasis">*new*</span>](jvms-4.html#jvms-4.10.1.9.new)</span>

<span class="section">[<span class="emphasis">*newarray*</span>](jvms-4.html#jvms-4.10.1.9.newarray)</span>

<span class="section">[<span class="emphasis">*nop*</span>](jvms-4.html#jvms-4.10.1.9.nop)</span>

<span class="section">[<span class="emphasis">*pop*</span>,
<span class="emphasis">*pop2*</span>](jvms-4.html#jvms-4.10.1.9.pop)</span>

<span class="section">[<span class="emphasis">*putfield*</span>](jvms-4.html#jvms-4.10.1.9.putfield)</span>

<span class="section">[<span class="emphasis">*putstatic*</span>](jvms-4.html#jvms-4.10.1.9.putstatic)</span>

<span class="section">[<span class="emphasis">*return*</span>](jvms-4.html#jvms-4.10.1.9.return)</span>

<span class="section">[<span class="emphasis">*saload*</span>](jvms-4.html#jvms-4.10.1.9.saload)</span>

<span class="section">[<span class="emphasis">*sastore*</span>](jvms-4.html#jvms-4.10.1.9.sastore)</span>

<span class="section">[<span class="emphasis">*sipush*</span>](jvms-4.html#jvms-4.10.1.9.sipush)</span>

<span class="section">[<span class="emphasis">*swap*</span>](jvms-4.html#jvms-4.10.1.9.swap)</span>

<span class="section">[<span class="emphasis">*tableswitch*</span>](jvms-4.html#jvms-4.10.1.9.tableswitch)</span>

<span class="section">[<span class="emphasis">*wide*</span>](jvms-4.html#jvms-4.10.1.9.wide)</span>

<span class="section">[4.10.2. Verification by Type
Inference](jvms-4.html#jvms-4.10.2)</span>

<span class="section">[4.10.2.1. The Process of Verification by Type
Inference](jvms-4.html#jvms-4.10.2.1)</span>

<span class="section">[4.10.2.2. The Bytecode
Verifier](jvms-4.html#jvms-4.10.2.2)</span>

<span class="section">[4.10.2.3. Values of Types `long` and
`double`](jvms-4.html#jvms-4.10.2.3)</span>

<span class="section">[4.10.2.4. Instance Initialization Methods and
Newly Created Objects](jvms-4.html#jvms-4.10.2.4)</span>

<span class="section">[4.10.2.5. Exceptions and
`finally`](jvms-4.html#jvms-4.10.2.5)</span>

<span class="section">[4.11. Limitations of the Java Virtual
Machine](jvms-4.html#jvms-4.11)</span>

</div>

This chapter describes the `class` file format of the Java Virtual
Machine. Each `class` file contains the definition of a single class,
interface, or module. Although a class, interface, or module need not
have an external representation literally contained in a file (for
instance, because the class is generated by a class loader), we will
colloquially refer to any valid representation of a class, interface, or
module as being in the `class` file format.

A `class` file consists of a stream of 8-bit bytes. 16-bit and 32-bit
quantities are constructed by reading in two and four consecutive 8-bit
bytes, respectively. Multibyte data items are always stored in
big-endian order, where the high bytes come first. This chapter defines
the data types `u1`, `u2`, and `u4` to represent an unsigned one-, two-,
or four-byte quantity, respectively.

In the Java SE Platform API, the `class` file format is supported by
interfaces `java.io.DataInput` and `java.io.DataOutput` and classes such
as `java.io.DataInputStream` and `java.io.DataOutputStream`. For
example, values of the types `u1`, `u2`, and `u4` may be read by methods
such as `readUnsignedByte`, `readUnsignedShort`, and `readInt` of the
interface `java.io.DataInput`.

This chapter presents the `class` file format using pseudostructures
written in a C-like structure notation. To avoid confusion with the
fields of classes and class instances, etc., the contents of the
structures describing the `class` file format are referred to as
<span class="emphasis">*items*</span>. Successive items are stored in
the `class` file sequentially, without padding or alignment.

<span class="emphasis">*Tables*</span>, consisting of zero or more
variable-sized items, are used in several `class` file structures.
Although we use C-like array syntax to refer to table items, the fact
that tables are streams of varying-sized structures means that it is not
possible to translate a table index directly to a byte offset into the
table.

Where we refer to a data structure as an
<span class="emphasis">*array*</span>, it consists of zero or more
contiguous fixed-sized items and can be indexed like an array.

Reference to an ASCII character in this chapter should be interpreted to
mean the Unicode code point corresponding to the ASCII character.

<div id="jvms-4.1" class="section">

<div class="titlepage">

<div>

<div>

## 4.1. The `ClassFile` Structure

</div>

</div>

</div>

A `class` file consists of a single `ClassFile` structure:

``` screen
ClassFile {
    u4             magic;
    u2             minor_version;
    u2             major_version;
    u2             constant_pool_count;
    cp_info        constant_pool[constant_pool_count-1];
    u2             access_flags;
    u2             this_class;
    u2             super_class;
    u2             interfaces_count;
    u2             interfaces[interfaces_count];
    u2             fields_count;
    field_info     fields[fields_count];
    u2             methods_count;
    method_info    methods[methods_count];
    u2             attributes_count;
    attribute_info attributes[attributes_count];
}
```

The items in the `ClassFile` structure are as follows:

<div class="variablelist">

<span class="term">magic</span>  
The `magic` item supplies the magic number identifying the `class` file
format; it has the value `0xCAFEBABE`.

<span class="term">minor_version, major_version</span>  
The values of the `minor_version` and `major_version` items are the
minor and major version numbers of this `class` file. Together, a major
and a minor version number determine the version of the `class` file
format. If a `class` file has major version number `M` and minor version
number `m`, we denote the version of its `class` file format as `M`.`m`.

The `major_version` item must be a value in the range 45 through 70,
inclusive. A Java Virtual Machine implementation which conforms to Java
SE 26 supports precisely these major version numbers.

For a `class` file whose `major_version` is 56 or above, the
`minor_version` must be 0 or 65535.

For a `class` file whose `major_version` is between 45 and 55 inclusive,
the `minor_version` may be any value.

A `class` file with version number 70.65535 depends on the preview
features of Java SE 26 (<a href="jvms-1.html#jvms-1.5.1" class="xref"
title="1.5.1. Restrictions on the Use of Preview Features">§1.5.1</a>).
Such a `class` file may be loaded only when the user has indicated via
the host system that preview features are enabled.

A `class` file with version number `M`.65535, where 56
<span class="symbol">≤</span> `M` \< 70, depends on the preview features
of an older release of the Java SE Platform. Such a `class` file may not
be loaded, regardless of whether preview features are enabled. Instead,
the `class` file may be loaded only by a Java Virtual Machine
implementation that conforms to the older release.

A `class` file with any other version number does not depend on preview
features, and may be loaded regardless of whether preview features are
enabled.

A historical perspective is warranted on JDK use of the `class` file
`minor_version`. JDK 1.0.2 supported versions 45.0 through 45.3
inclusive. JDK 1.1 supported versions 45.0 through 45.65535 inclusive.
When JDK 1.2 introduced support for major version 46, the only minor
version supported under that major version was 0. Later JDKs continued
the practice of introducing support for a new major version (47, 48,
etc.) but supporting only a minor version of 0 under the new major
version. Finally, the introduction of preview features
(<a href="jvms-1.html#jvms-1.5" class="xref"
title="1.5. Preview Features">§1.5</a>) in Java SE 12 motivated a
standard role for the minor version of the `class` file format, so JDK
12 supported minor versions of 0 <span class="emphasis">*and*</span>
65535 under major version 56. Subsequent JDKs introduce support for
`N`.0 and `N`.65535 where `N` is the corresponding major version of the
implemented Java SE Platform. For example, JDK 13 supports 57.0 and
57.65535.

<span class="term">constant_pool_count</span>  
The value of the `constant_pool_count` item is equal to the number of
entries in the `constant_pool` table plus one. A `constant_pool` index
is considered valid if it is greater than zero and less than
`constant_pool_count`, with the exception for constants of type `long`
and `double` noted in <a href="jvms-4.html#jvms-4.4.5" class="xref"
title="4.4.5. The CONSTANT_Long_info and CONSTANT_Double_info Structures">§4.4.5</a>.

<span class="term">constant_pool\[\]</span>  
The `constant_pool` is a table of structures
(<a href="jvms-4.html#jvms-4.4" class="xref"
title="4.4. The Constant Pool">§4.4</a>) representing various string
constants, class and interface names, field names, and other constants
that are referred to within the `ClassFile` structure and its
substructures. The format of each `constant_pool` table entry is
indicated by its first "tag" byte.

The `constant_pool` table is indexed from 1 to `constant_pool_count` -
1.

<span class="term">access_flags</span>  
The value of the `access_flags` item is a mask of flags used to denote
access permissions to and properties of this class or interface. The
interpretation of each flag, when set, is specified in
<a href="jvms-4.html#jvms-4.1-200-E.1" class="xref"
title="Table 4.1-B. Class access and property modifiers">Table 4.1-B</a>.

<div id="jvms-4.1-200-E.1" class="table">

**Table 4.1-B. Class access and property modifiers**

<div class="table-contents">

| Flag Name | Value | Interpretation |
|----|----|----|
| `ACC_PUBLIC` | 0x0001 | Declared `public`; may be accessed from outside its package. |
| `ACC_FINAL` | 0x0010 | Declared `final`; no subclasses allowed. |
| `ACC_SUPER` | 0x0020 | Treat superclass methods specially when invoked by the <span class="emphasis">*invokespecial*</span> instruction. |
| `ACC_INTERFACE` | 0x0200 | Is an interface, not a class. |
| `ACC_ABSTRACT` | 0x0400 | Declared `abstract`; must not be instantiated. |
| `ACC_SYNTHETIC` | 0x1000 | Declared synthetic; not present in the source code. |
| `ACC_ANNOTATION` | 0x2000 | Declared as an annotation interface. |
| `ACC_ENUM` | 0x4000 | Declared as an `enum` class. |
| `ACC_MODULE` | 0x8000 | Is a module, not a class or interface. |

</div>

</div>

  

The `ACC_MODULE` flag indicates that this `class` file defines a module,
not a class or interface. If the `ACC_MODULE` flag is set, then special
rules apply to the `class` file which are given at the end of this
section. If the `ACC_MODULE` flag is not set, then the rules immediately
below the current paragraph apply to the `class` file.

An interface is distinguished by the `ACC_INTERFACE` flag being set. If
the `ACC_INTERFACE` flag is not set, this `class` file defines a class,
not an interface or module.

If the `ACC_INTERFACE` flag is set, the `ACC_ABSTRACT` flag must also be
set, and the `ACC_FINAL`, `ACC_SUPER`, `ACC_ENUM`, and `ACC_MODULE`
flags set must not be set.

If the `ACC_INTERFACE` flag is not set, any of the other flags in
<a href="jvms-4.html#jvms-4.1-200-E.1" class="xref"
title="Table 4.1-B. Class access and property modifiers">Table 4.1-B</a>
may be set except `ACC_ANNOTATION` and `ACC_MODULE`. However, such a
`class` file must not have both its `ACC_FINAL` and `ACC_ABSTRACT` flags
set (JLS §8.1.1.2).

The `ACC_SUPER` flag indicates which of two alternative semantics is to
be expressed by the <span class="emphasis">*invokespecial*</span>
instruction (<a href="jvms-6.html#jvms-6.5.invokespecial" class="xref"
title="invokespecial">§<span
class="emphasis"><em>invokespecial</em></span></a>) if it appears in
this class or interface. Compilers to the instruction set of the Java
Virtual Machine should set the `ACC_SUPER` flag. In Java SE 8 and above,
the Java Virtual Machine considers the `ACC_SUPER` flag to be set in
every `class` file, regardless of the actual value of the flag in the
`class` file and the version of the `class` file.

The `ACC_SUPER` flag exists for backward compatibility with code
compiled by older compilers for the Java programming language. Prior to
JDK 1.0.2, the compiler generated `access_flags` in which the flag now
representing `ACC_SUPER` had no assigned meaning, and Oracle's Java
Virtual Machine implementation ignored the flag if it was set.

The `ACC_SYNTHETIC` flag indicates that this class or interface was
generated by a compiler and does not appear in source code.

An annotation interface (JLS §9.6) must have its `ACC_ANNOTATION` flag
set. If the `ACC_ANNOTATION` flag is set, the `ACC_INTERFACE` flag must
also be set.

The `ACC_ENUM` flag indicates that this class or its superclass is
declared as an enum class (JLS §8.9).

All bits of the `access_flags` item not assigned in
<a href="jvms-4.html#jvms-4.1-200-E.1" class="xref"
title="Table 4.1-B. Class access and property modifiers">Table 4.1-B</a>
are reserved for future use. They should be set to zero in generated
`class` files and should be ignored by Java Virtual Machine
implementations.

<span class="term">this_class</span>  
The value of the `this_class` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Class_info` structure
(<a href="jvms-4.html#jvms-4.4.1" class="xref"
title="4.4.1. The CONSTANT_Class_info Structure">§4.4.1</a>)
representing the class or interface defined by this `class` file.

<span class="term">super_class</span>  
For a class, the value of the `super_class` item either must be zero or
must be a valid index into the `constant_pool` table. If the value of
the `super_class` item is nonzero, the `constant_pool` entry at that
index must be a `CONSTANT_Class_info` structure representing the direct
superclass of the class defined by this `class` file. Neither the direct
superclass nor any of its superclasses may have the `ACC_FINAL` flag set
in the `access_flags` item of its `ClassFile` structure.

If the value of the `super_class` item is zero, then this `class` file
must represent the class `Object`, the only class or interface without a
direct superclass.

For an interface, the value of the `super_class` item must always be a
valid index into the `constant_pool` table. The `constant_pool` entry at
that index must be a `CONSTANT_Class_info` structure representing the
class `Object`.

<span class="term">interfaces_count</span>  
The value of the `interfaces_count` item gives the number of direct
superinterfaces of this class or interface type.

<span class="term">interfaces\[\]</span>  
Each value in the `interfaces` array must be a valid index into the
`constant_pool` table. The `constant_pool` entry at each value of
`interfaces[`<span class="emphasis">*`i`*</span>`]`, where 0
<span class="symbol">≤</span> <span class="emphasis">*i*</span> \<
`interfaces_count`, must be a `CONSTANT_Class_info` structure
representing an interface that is a direct superinterface of this class
or interface type, in the left-to-right order given in the source for
the type.

<span class="term">fields_count</span>  
The value of the `fields_count` item gives the number of `field_info`
structures in the `fields` table. The `field_info` structures represent
all fields, both class variables and instance variables, declared by
this class or interface type.

<span class="term">fields\[\]</span>  
Each value in the `fields` table must be a `field_info` structure
(<a href="jvms-4.html#jvms-4.5" class="xref" title="4.5. Fields">§4.5</a>)
giving a complete description of a field in this class or interface. The
`fields` table includes only those fields that are declared by this
class or interface. It does not include items representing fields that
are inherited from superclasses or superinterfaces.

<span class="term">methods_count</span>  
The value of the `methods_count` item gives the number of `method_info`
structures in the `methods` table.

<span class="term">methods\[\]</span>  
Each value in the `methods` table must be a `method_info` structure
(<a href="jvms-4.html#jvms-4.6" class="xref"
title="4.6. Methods">§4.6</a>) giving a complete description of a method
in this class or interface. If neither of the `ACC_NATIVE` and
`ACC_ABSTRACT` flags are set in the `access_flags` item of a
`method_info` structure, the Java Virtual Machine instructions
implementing the method are also supplied.

The `method_info` structures represent all methods declared by this
class or interface type, including instance methods, class methods,
instance initialization methods
(<a href="jvms-2.html#jvms-2.9.1" class="xref"
title="2.9.1. Instance Initialization Methods">§2.9.1</a>), and any
class or interface initialization method
(<a href="jvms-2.html#jvms-2.9.2" class="xref"
title="2.9.2. Class Initialization Methods">§2.9.2</a>). The `methods`
table does not include items representing methods that are inherited
from superclasses or superinterfaces.

<span class="term">attributes_count</span>  
The value of the `attributes_count` item gives the number of attributes
in the `attributes` table of this class.

<span class="term">attributes\[\]</span>  
Each value of the `attributes` table must be an `attribute_info`
structure (<a href="jvms-4.html#jvms-4.7" class="xref"
title="4.7. Attributes">§4.7</a>).

The attributes defined by this specification as appearing in the
`attributes` table of a `ClassFile` structure are listed in
<a href="jvms-4.html#jvms-4.7-320" class="xref"
title="Table 4.7-C. Predefined class file attributes (by location)">Table 4.7-C</a>.

The rules concerning attributes defined to appear in the `attributes`
table of a `ClassFile` structure are given in
<a href="jvms-4.html#jvms-4.7" class="xref"
title="4.7. Attributes">§4.7</a>.

The rules concerning non-predefined attributes in the `attributes` table
of a `ClassFile` structure are given in
<a href="jvms-4.html#jvms-4.7.1" class="xref"
title="4.7.1. Defining and Naming New Attributes">§4.7.1</a>.

</div>

If the `ACC_MODULE` flag is set in the `access_flags` item, then no
other flag in the `access_flags` item may be set, and the following
rules apply to the rest of the `ClassFile` structure:

<div>

- `major_version`, `minor_version`: <span class="symbol">≥</span> 53.0
  (i.e., Java SE 9 and above)

- `this_class`: `module-info`

- `super_class`, `interfaces_count`, `fields_count`, `methods_count`:
  zero

- `attributes`: One `Module` attribute must be present. Except for
  `Module`, `ModulePackages`, `ModuleMainClass`, `InnerClasses`,
  `SourceFile`, `SourceDebugExtension`, `RuntimeVisibleAnnotations`, and
  `RuntimeInvisibleAnnotations`, none of the pre-defined attributes
  (<a href="jvms-4.html#jvms-4.7" class="xref"
  title="4.7. Attributes">§4.7</a>) may appear.

</div>

</div>

<div id="jvms-4.2" class="section">

<div class="titlepage">

<div>

<div>

## 4.2. Names

</div>

</div>

</div>

<div id="jvms-4.2.1" class="section">

<div class="titlepage">

<div>

<div>

### 4.2.1. Binary Class and Interface Names

</div>

</div>

</div>

Class and interface names that appear in `class` file structures are
always represented in a fully qualified form known as
<span class="emphasis">*binary names*</span> (JLS §13.1). Such names are
always represented as `CONSTANT_Utf8_info` structures
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) and thus may
be drawn, where not further constrained, from the entire Unicode
codespace. Class and interface names are referenced from those
`CONSTANT_NameAndType_info` structures
(<a href="jvms-4.html#jvms-4.4.6" class="xref"
title="4.4.6. The CONSTANT_NameAndType_info Structure">§4.4.6</a>) which
have such names as part of their descriptor
(<a href="jvms-4.html#jvms-4.3" class="xref"
title="4.3. Descriptors">§4.3</a>), and from all `CONSTANT_Class_info`
structures (<a href="jvms-4.html#jvms-4.4.1" class="xref"
title="4.4.1. The CONSTANT_Class_info Structure">§4.4.1</a>).

For historical reasons, the syntax of binary names that appear in
`class` file structures differs from the syntax of binary names
documented in JLS §13.1. In this internal form, the ASCII periods (`.`)
that normally separate the identifiers which make up the binary name are
replaced by ASCII forward slashes (`/`). The identifiers themselves must
be unqualified names (<a href="jvms-4.html#jvms-4.2.2" class="xref"
title="4.2.2. Unqualified Names">§4.2.2</a>).

For example, the normal binary name of class `Thread` is
`java.lang.Thread`. In the internal form used in descriptors in the
`class` file format, a reference to the name of class `Thread` is
implemented using a `CONSTANT_Utf8_info` structure representing the
string `java/lang/Thread`.

</div>

<div id="jvms-4.2.2" class="section">

<div class="titlepage">

<div>

<div>

### 4.2.2. Unqualified Names

</div>

</div>

</div>

Names of methods, fields, local variables, and formal parameters are
stored as <span class="emphasis">*unqualified names*</span>. An
unqualified name must contain at least one Unicode code point and must
not contain any of the ASCII characters `.` `;` `[` `/` (that is, period
or semicolon or left square bracket or forward slash).

Method names are further constrained so that, with the exception of the
special method names `<init>` and `<clinit>`
(<a href="jvms-2.html#jvms-2.9" class="xref"
title="2.9. Special Methods">§2.9</a>), they must not contain the ASCII
characters `<` or `>` (that is, left angle bracket or right angle
bracket).

Note that no method invocation instruction may reference `<clinit>`, and
only the <span class="emphasis">*invokespecial*</span> instruction
(<a href="jvms-6.html#jvms-6.5.invokespecial" class="xref"
title="invokespecial">§<span
class="emphasis"><em>invokespecial</em></span></a>) may reference
`<init>`.

</div>

<div id="jvms-4.2.3" class="section">

<div class="titlepage">

<div>

<div>

### 4.2.3. Module and Package Names

</div>

</div>

</div>

Module names referenced from the `Module` attribute are stored in
`CONSTANT_Module_info` structures in the constant pool
(<a href="jvms-4.html#jvms-4.4.11" class="xref"
title="4.4.11. The CONSTANT_Module_info Structure">§4.4.11</a>). A
`CONSTANT_Module_info` structure wraps a `CONSTANT_Utf8_info` structure
that denotes the module name. Module names are not encoded in "internal
form" like class and interface names, that is, the ASCII periods (`.`)
that separate the identifiers in a module name are not replaced by ASCII
forward slashes (`/`).

Module names may be drawn from the entire Unicode codespace, subject to
the following constraints:

<div class="norm">

- A module name must not contain any code point in the range '`\u0000`'
  to '`\u001F`' inclusive.

- The ASCII backslash (`\`) is reserved for use as an escape character
  in module names. It must not appear in a module name unless it is
  followed by an ASCII backslash, an ASCII colon (`:`), or an ASCII
  at-sign (`@`). The ASCII character sequence `\``\` may be used to
  encode a backslash in a module name.

- The ASCII colon (`:`) and at-sign (`@`) are reserved for future use in
  module names. They must not appear in module names unless they are
  escaped. The ASCII character sequences `\``:` and `\``@` may be used
  to encode a colon and an at-sign in a module name.

</div>

Package names referenced from the `Module` attribute are stored in
`CONSTANT_Package_info` structures in the constant pool
(<a href="jvms-4.html#jvms-4.4.12" class="xref"
title="4.4.12. The CONSTANT_Package_info Structure">§4.4.12</a>). A
`CONSTANT_Package_info` structure wraps a `CONSTANT_Utf8_info` structure
that represents a package name encoded in internal form.

</div>

</div>

<div id="jvms-4.3" class="section">

<div class="titlepage">

<div>

<div>

## 4.3. Descriptors

</div>

</div>

</div>

A <span class="emphasis">*descriptor*</span> is a string representing
the type of a field or method. Descriptors are represented in the
`class` file format using modified UTF-8 strings
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) and thus may
be drawn, where not further constrained, from the entire Unicode
codespace.

<div id="jvms-4.3.1" class="section">

<div class="titlepage">

<div>

<div>

### 4.3.1. Grammar Notation

</div>

</div>

</div>

Descriptors are specified using a grammar. The grammar is a set of
productions that describe how sequences of characters can form
syntactically correct descriptors of various kinds. Terminal symbols of
the grammar are shown in `fixed width` font, and should be interpreted
as ASCII characters. Nonterminal symbols are shown in
<span class="emphasis">*italic*</span> type. The definition of a
nonterminal is introduced by the name of the nonterminal being defined,
followed by a colon. One or more alternative definitions for the
nonterminal then follow on succeeding lines.

The syntax <span class="emphasis">*{x}*</span> on the right-hand side of
a production denotes zero or more occurrences of
<span class="emphasis">*x*</span>.

The phrase <span class="emphasis">*(one of)*</span> on the right-hand
side of a production signifies that each of the terminal symbols on the
following line or lines is an alternative definition.

</div>

<div id="jvms-4.3.2" class="section">

<div class="titlepage">

<div>

<div>

### 4.3.2. Field Descriptors

</div>

</div>

</div>

A <span class="emphasis">*field descriptor*</span> represents the type
of a field, parameter, local variable, or value.

<div id="jvms-4.3.2-110" class="productionset">

<div id="jvms-FieldDescriptor" class="production">

<div class="lhs">

FieldDescriptor:

</div>

<div class="rhs">

[FieldType](jvms-4.html#jvms-FieldType "FieldType")

</div>

</div>

<div id="jvms-FieldType" class="production">

<div class="lhs">

FieldType:

</div>

<div class="rhs">

[BaseType](jvms-4.html#jvms-BaseType "BaseType")  
[ClassType](jvms-4.html#jvms-ClassType "ClassType")  
[ArrayType](jvms-4.html#jvms-ArrayType "ArrayType")

</div>

</div>

<div id="jvms-BaseType" class="production">

<div class="lhs">

BaseType:

</div>

<div class="rhs">

(one of)  
`B` `C` `D` `F` `I` `J` `S` `Z`

</div>

</div>

<div id="jvms-ClassType" class="production">

<div class="lhs">

ClassType:

</div>

<div class="rhs">

`L` ClassName `;`

</div>

</div>

<div id="jvms-ArrayType" class="production">

<div class="lhs">

ArrayType:

</div>

<div class="rhs">

`[` [ComponentType](jvms-4.html#jvms-ComponentType "ComponentType")

</div>

</div>

<div id="jvms-ComponentType" class="production">

<div class="lhs">

ComponentType:

</div>

<div class="rhs">

[FieldType](jvms-4.html#jvms-FieldType "FieldType")

</div>

</div>

</div>

<span class="emphasis">*ClassName*</span> represents a binary class or
interface name encoded in internal form
(<a href="jvms-4.html#jvms-4.2.1" class="xref"
title="4.2.1. Binary Class and Interface Names">§4.2.1</a>).

A field descriptor <span class="emphasis">*mentions*</span> a class or
interface name if the name appears as a
<span class="emphasis">*ClassName*</span> in the descriptor. This
includes a <span class="emphasis">*ClassName*</span> nested in the
<span class="emphasis">*ComponentType*</span> of an
<span class="emphasis">*ArrayType*</span>.

The interpretation of field descriptors as types is shown in
<a href="jvms-4.html#jvms-4.3.2-200" class="xref"
title="Table 4.3-A. Interpretation of field descriptors">Table 4.3-A</a>.
See <a href="jvms-2.html#jvms-2.2" class="xref"
title="2.2. Data Types">§2.2</a>,
<a href="jvms-2.html#jvms-2.3" class="xref"
title="2.3. Primitive Types and Values">§2.3</a>, and
<a href="jvms-2.html#jvms-2.4" class="xref"
title="2.4. Reference Types and Values">§2.4</a> for the meaning of
these types.

A field descriptor representing an array type is valid only if it
represents a type with 255 or fewer dimensions.

<div id="jvms-4.3.2-200" class="table">

**Table 4.3-A. Interpretation of field descriptors**

<div class="table-contents">

| <span class="emphasis">*FieldType*</span> term | Type |
|----|----|
| `B` | `byte` |
| `C` | `char` |
| `D` | `double` |
| `F` | `float` |
| `I` | `int` |
| `J` | `long` |
| `L` <span class="emphasis">*ClassName*</span> `;` | Named class or interface type |
| `S` | `short` |
| `Z` | `boolean` |
| `[` <span class="emphasis">*ComponentType*</span> | Array of given component type |

</div>

</div>

  

<div class="informalexample">

The field descriptor of an instance variable of type `int` is simply
`I`.

The field descriptor of an instance variable of type `Object` is
`Ljava/lang/Object;`. Note that the internal form of the binary name for
class `Object` is used.

The field descriptor of an instance variable of the multidimensional
array type `double[][][]` is `[[[D`.

</div>

</div>

<div id="jvms-4.3.3" class="section">

<div class="titlepage">

<div>

<div>

### 4.3.3. Method Descriptors

</div>

</div>

</div>

A <span class="emphasis">*method descriptor*</span> contains zero or
more <span class="emphasis">*parameter descriptors*</span>, representing
the types of parameters that the method takes, and a
<span class="emphasis">*return descriptor*</span>, representing the type
of the value (if any) that the method returns.

<div id="jvms-4.3.3-110" class="productionset">

<div id="jvms-MethodDescriptor" class="production">

<div class="lhs">

MethodDescriptor:

</div>

<div class="rhs">

`(`
{[ParameterDescriptor](jvms-4.html#jvms-ParameterDescriptor "ParameterDescriptor")}
`)`
[ReturnDescriptor](jvms-4.html#jvms-ReturnDescriptor "ReturnDescriptor")

</div>

</div>

<div id="jvms-ParameterDescriptor" class="production">

<div class="lhs">

ParameterDescriptor:

</div>

<div class="rhs">

[FieldType](jvms-4.html#jvms-FieldType "FieldType")

</div>

</div>

<div id="jvms-ReturnDescriptor" class="production">

<div class="lhs">

ReturnDescriptor:

</div>

<div class="rhs">

[FieldType](jvms-4.html#jvms-FieldType "FieldType")  
[VoidDescriptor](jvms-4.html#jvms-VoidDescriptor "VoidDescriptor")

</div>

</div>

<div id="jvms-VoidDescriptor" class="production">

<div class="lhs">

VoidDescriptor:

</div>

<div class="rhs">

`V`

</div>

</div>

</div>

The character `V` indicates that the method returns no value (its result
is `void`).

A method descriptor <span class="emphasis">*mentions*</span> a class or
interface name if the name appears as a
<span class="emphasis">*ClassName*</span> in the
<span class="emphasis">*FieldType*</span> of a parameter descriptor or
return descriptor.

<div class="informalexample">

The method descriptor for the method:

``` screen
Object m(int i, double d, Thread t) {...}
```

is:

``` screen
(IDLjava/lang/Thread;)Ljava/lang/Object;
```

Note that the internal forms of the binary names of `Thread` and
`Object` are used.

</div>

A method descriptor is valid only if it represents method parameters
with a total length of 255 or less, where that length includes the
contribution for `this` in the case of instance or interface method
invocations. The total length is calculated by summing the contributions
of the individual parameters, where a parameter of type `long` or
`double` contributes two units to the length and a parameter of any
other type contributes one unit.

A method descriptor is the same whether the method it describes is a
class method or an instance method. Although an instance method is
passed `this`, a reference to the object on which the method is being
invoked, in addition to its intended arguments, that fact is not
reflected in the method descriptor. The reference to `this` is passed
implicitly by the Java Virtual Machine instructions which invoke
instance methods (<a href="jvms-2.html#jvms-2.6.1" class="xref"
title="2.6.1. Local Variables">§2.6.1</a>,
<a href="jvms-4.html#jvms-4.11" class="xref"
title="4.11. Limitations of the Java Virtual Machine">§4.11</a>).

</div>

</div>

<div id="jvms-4.4" class="section">

<div class="titlepage">

<div>

<div>

## 4.4. The Constant Pool

</div>

</div>

</div>

Java Virtual Machine instructions do not rely on the run-time layout of
classes, interfaces, class instances, or arrays. Instead, instructions
refer to symbolic information in the `constant_pool` table.

All `constant_pool` table entries have the following general format:

``` screen
cp_info {
    u1 tag;
    u1 info[];
}
```

Each entry in the `constant_pool` table must begin with a 1-byte tag
indicating the kind of constant denoted by the entry. There are 17 kinds
of constant, listed in <a href="jvms-4.html#jvms-4.4-140" class="xref"
title="Table 4.4-A. Constant pool tags (by section)">Table 4.4-A</a>
with their corresponding tags, and ordered by their section number in
this chapter. Each tag byte must be followed by two or more bytes giving
information about the specific constant. The format of the additional
information depends on the tag byte, that is, the content of the `info`
array varies with the value of `tag`.

<div id="jvms-4.4-140" class="table">

**Table 4.4-A. Constant pool tags (by section)**

<div class="table-contents">

| Constant Kind | Tag | Section |
|----|----|----|
| `CONSTANT_Class` | 7 | <a href="jvms-4.html#jvms-4.4.1" class="xref"
title="4.4.1. The CONSTANT_Class_info Structure">§4.4.1</a> |
| `CONSTANT_Fieldref` | 9 | <a href="jvms-4.html#jvms-4.4.2" class="xref"
title="4.4.2. The CONSTANT_Fieldref_info, CONSTANT_Methodref_info, and CONSTANT_InterfaceMethodref_info Structures">§4.4.2</a> |
| `CONSTANT_Methodref` | 10 | <a href="jvms-4.html#jvms-4.4.2" class="xref"
title="4.4.2. The CONSTANT_Fieldref_info, CONSTANT_Methodref_info, and CONSTANT_InterfaceMethodref_info Structures">§4.4.2</a> |
| `CONSTANT_InterfaceMethodref` | 11 | <a href="jvms-4.html#jvms-4.4.2" class="xref"
title="4.4.2. The CONSTANT_Fieldref_info, CONSTANT_Methodref_info, and CONSTANT_InterfaceMethodref_info Structures">§4.4.2</a> |
| `CONSTANT_String` | 8 | <a href="jvms-4.html#jvms-4.4.3" class="xref"
title="4.4.3. The CONSTANT_String_info Structure">§4.4.3</a> |
| `CONSTANT_Integer` | 3 | <a href="jvms-4.html#jvms-4.4.4" class="xref"
title="4.4.4. The CONSTANT_Integer_info and CONSTANT_Float_info Structures">§4.4.4</a> |
| `CONSTANT_Float` | 4 | <a href="jvms-4.html#jvms-4.4.4" class="xref"
title="4.4.4. The CONSTANT_Integer_info and CONSTANT_Float_info Structures">§4.4.4</a> |
| `CONSTANT_Long` | 5 | <a href="jvms-4.html#jvms-4.4.5" class="xref"
title="4.4.5. The CONSTANT_Long_info and CONSTANT_Double_info Structures">§4.4.5</a> |
| `CONSTANT_Double` | 6 | <a href="jvms-4.html#jvms-4.4.5" class="xref"
title="4.4.5. The CONSTANT_Long_info and CONSTANT_Double_info Structures">§4.4.5</a> |
| `CONSTANT_NameAndType` | 12 | <a href="jvms-4.html#jvms-4.4.6" class="xref"
title="4.4.6. The CONSTANT_NameAndType_info Structure">§4.4.6</a> |
| `CONSTANT_Utf8` | 1 | <a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a> |
| `CONSTANT_MethodHandle` | 15 | <a href="jvms-4.html#jvms-4.4.8" class="xref"
title="4.4.8. The CONSTANT_MethodHandle_info Structure">§4.4.8</a> |
| `CONSTANT_MethodType` | 16 | <a href="jvms-4.html#jvms-4.4.9" class="xref"
title="4.4.9. The CONSTANT_MethodType_info Structure">§4.4.9</a> |
| `CONSTANT_Dynamic` | 17 | <a href="jvms-4.html#jvms-4.4.10" class="xref"
title="4.4.10. The CONSTANT_Dynamic_info and CONSTANT_InvokeDynamic_info Structures">§4.4.10</a> |
| `CONSTANT_InvokeDynamic` | 18 | <a href="jvms-4.html#jvms-4.4.10" class="xref"
title="4.4.10. The CONSTANT_Dynamic_info and CONSTANT_InvokeDynamic_info Structures">§4.4.10</a> |
| `CONSTANT_Module` | 19 | <a href="jvms-4.html#jvms-4.4.11" class="xref"
title="4.4.11. The CONSTANT_Module_info Structure">§4.4.11</a> |
| `CONSTANT_Package` | 20 | <a href="jvms-4.html#jvms-4.4.12" class="xref"
title="4.4.12. The CONSTANT_Package_info Structure">§4.4.12</a> |

</div>

</div>

  

In a `class` file whose version number is
<span class="emphasis">*v*</span>, each entry in the `constant_pool`
table must have a tag that was first defined in version
<span class="emphasis">*v*</span> or earlier of the `class` file format
(<a href="jvms-4.html#jvms-4.1" class="xref"
title="4.1. The ClassFile Structure">§4.1</a>). That is, each entry must
denote a kind of constant that is approved for use in the `class` file.
<a href="jvms-4.html#jvms-4.4-210" class="xref"
title="Table 4.4-B. Constant pool tags (by tag)">Table 4.4-B</a> lists
each tag with the first version of the `class` file format in which it
was defined. Also shown is the version of the Java SE Platform which
introduced that version of the `class` file format.

<div id="jvms-4.4-210" class="table">

**Table 4.4-B. Constant pool tags (by tag)**

<div class="table-contents">

| Constant Kind                 | Tag | `class` file format | Java SE |
|-------------------------------|-----|---------------------|---------|
| `CONSTANT_Utf8`               | 1   | 45.3                | 1.0.2   |
| `CONSTANT_Integer`            | 3   | 45.3                | 1.0.2   |
| `CONSTANT_Float`              | 4   | 45.3                | 1.0.2   |
| `CONSTANT_Long`               | 5   | 45.3                | 1.0.2   |
| `CONSTANT_Double`             | 6   | 45.3                | 1.0.2   |
| `CONSTANT_Class`              | 7   | 45.3                | 1.0.2   |
| `CONSTANT_String`             | 8   | 45.3                | 1.0.2   |
| `CONSTANT_Fieldref`           | 9   | 45.3                | 1.0.2   |
| `CONSTANT_Methodref`          | 10  | 45.3                | 1.0.2   |
| `CONSTANT_InterfaceMethodref` | 11  | 45.3                | 1.0.2   |
| `CONSTANT_NameAndType`        | 12  | 45.3                | 1.0.2   |
| `CONSTANT_MethodHandle`       | 15  | 51.0                | 7       |
| `CONSTANT_MethodType`         | 16  | 51.0                | 7       |
| `CONSTANT_Dynamic`            | 17  | 55.0                | 11      |
| `CONSTANT_InvokeDynamic`      | 18  | 51.0                | 7       |
| `CONSTANT_Module`             | 19  | 53.0                | 9       |
| `CONSTANT_Package`            | 20  | 53.0                | 9       |

</div>

</div>

  

Some entries in the `constant_pool` table are
<span class="emphasis">*loadable*</span> because they represent entities
that can be pushed onto the stack at run time to enable further
computation. In a `class` file whose version number is
<span class="emphasis">*v*</span>, an entry in the `constant_pool` table
is loadable if it has a tag that was first deemed to be loadable in
version <span class="emphasis">*v*</span> or earlier of the `class` file
format. <a href="jvms-4.html#jvms-4.4-310" class="xref"
title="Table 4.4-C. Loadable constant pool tags">Table 4.4-C</a> lists
each tag with the first version of the `class` file format in which it
was deemed to be loadable. Also shown is the version of the Java SE
Platform which introduced that version of the `class` file format.

In every case except `CONSTANT_Class`, a tag was first deemed to be
loadable in the same version of the `class` file format that first
defined the tag.

<div id="jvms-4.4-310" class="table">

**Table 4.4-C. Loadable constant pool tags**

<div class="table-contents">

| Constant Kind           | Tag | `class` file format | Java SE |
|-------------------------|-----|---------------------|---------|
| `CONSTANT_Integer`      | 3   | 45.3                | 1.0.2   |
| `CONSTANT_Float`        | 4   | 45.3                | 1.0.2   |
| `CONSTANT_Long`         | 5   | 45.3                | 1.0.2   |
| `CONSTANT_Double`       | 6   | 45.3                | 1.0.2   |
| `CONSTANT_Class`        | 7   | 49.0                | 5.0     |
| `CONSTANT_String`       | 8   | 45.3                | 1.0.2   |
| `CONSTANT_MethodHandle` | 15  | 51.0                | 7       |
| `CONSTANT_MethodType`   | 16  | 51.0                | 7       |
| `CONSTANT_Dynamic`      | 17  | 55.0                | 11      |

</div>

</div>

  

<div id="jvms-4.4.1" class="section">

<div class="titlepage">

<div>

<div>

### 4.4.1. The `CONSTANT_Class_info` Structure

</div>

</div>

</div>

The `CONSTANT_Class_info` structure is used to represent a class or an
interface:

``` screen
CONSTANT_Class_info {
    u1 tag;
    u2 name_index;
}
```

The items of the `CONSTANT_Class_info` structure are as follows:

<div class="variablelist">

<span class="term">tag</span>  
The `tag` item has the value `CONSTANT_Class` (7).

<span class="term">name_index</span>  
The value of the `name_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
a valid binary class or interface name encoded in internal form
(<a href="jvms-4.html#jvms-4.2.1" class="xref"
title="4.2.1. Binary Class and Interface Names">§4.2.1</a>).

</div>

Because arrays are objects, the opcodes
<span class="emphasis">*anewarray*</span> and
<span class="emphasis">*multianewarray*</span> - but not the opcode
<span class="emphasis">*new*</span> - can reference array "classes" via
`CONSTANT_Class_info` structures in the `constant_pool` table. For such
array classes, the name of the class is the descriptor of the array type
(<a href="jvms-4.html#jvms-4.3.2" class="xref"
title="4.3.2. Field Descriptors">§4.3.2</a>).

<div class="informalexample">

For example, the class name representing the two-dimensional array type
`int[][]` is `[[I`, while the class name representing the type
`Thread[]` is `[Ljava/lang/Thread;`.

</div>

An array type descriptor is valid only if it represents 255 or fewer
dimensions.

</div>

<div id="jvms-4.4.2" class="section">

<div class="titlepage">

<div>

<div>

### 4.4.2. The `CONSTANT_Fieldref_info`, `CONSTANT_Methodref_info`, and `CONSTANT_InterfaceMethodref_info` Structures

</div>

</div>

</div>

Fields, methods, and interface methods are represented by similar
structures:

``` screen
CONSTANT_Fieldref_info {
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
}

CONSTANT_Methodref_info {
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
}

CONSTANT_InterfaceMethodref_info {
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
}
```

The items of these structures are as follows:

<div class="variablelist">

<span class="term">tag</span>  
The `tag` item of a `CONSTANT_Fieldref_info` structure has the value
`CONSTANT_Fieldref` (9).

The `tag` item of a `CONSTANT_Methodref_info` structure has the value
`CONSTANT_Methodref` (10).

The `tag` item of a `CONSTANT_InterfaceMethodref_info` structure has the
value `CONSTANT_InterfaceMethodref` (11).

<span class="term">class_index</span>  
The value of the `class_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Class_info` structure
(<a href="jvms-4.html#jvms-4.4.1" class="xref"
title="4.4.1. The CONSTANT_Class_info Structure">§4.4.1</a>)
representing a class or interface type that has the field or method as a
member.

In a `CONSTANT_Fieldref_info` structure, the `class_index` item may be
either a class type or an interface type.

In a `CONSTANT_Methodref_info` structure, the `class_index` item should
be a class type, not an interface type.

In a `CONSTANT_InterfaceMethodref_info` structure, the `class_index`
item should be an interface type, not a class type.

<span class="term">name_and_type_index</span>  
The value of the `name_and_type_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_NameAndType_info` structure
(<a href="jvms-4.html#jvms-4.4.6" class="xref"
title="4.4.6. The CONSTANT_NameAndType_info Structure">§4.4.6</a>). This
`constant_pool` entry indicates the name and descriptor of the field or
method.

In a `CONSTANT_Fieldref_info` structure, the indicated descriptor must
be a field descriptor (<a href="jvms-4.html#jvms-4.3.2" class="xref"
title="4.3.2. Field Descriptors">§4.3.2</a>). Otherwise, the indicated
descriptor must be a method descriptor
(<a href="jvms-4.html#jvms-4.3.3" class="xref"
title="4.3.3. Method Descriptors">§4.3.3</a>).

If the name of the method in a `CONSTANT_Methodref_info` structure
begins with a '`<`' ('`\u003c`'), then the name must be the special name
`<init>`, representing an instance initialization method
(<a href="jvms-2.html#jvms-2.9.1" class="xref"
title="2.9.1. Instance Initialization Methods">§2.9.1</a>). The return
type of such a method must be `void`.

</div>

</div>

<div id="jvms-4.4.3" class="section">

<div class="titlepage">

<div>

<div>

### 4.4.3. The `CONSTANT_String_info` Structure

</div>

</div>

</div>

The `CONSTANT_String_info` structure is used to represent constant
objects of the type `String`:

``` screen
CONSTANT_String_info {
    u1 tag;
    u2 string_index;
}
```

The items of the `CONSTANT_String_info` structure are as follows:

<div class="variablelist">

<span class="term">tag</span>  
The `tag` item has the value `CONSTANT_String` (8).

<span class="term">string_index</span>  
The value of the `string_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the sequence of Unicode code points to which the `String` object is to
be initialized.

</div>

</div>

<div id="jvms-4.4.4" class="section">

<div class="titlepage">

<div>

<div>

### 4.4.4. The `CONSTANT_Integer_info` and `CONSTANT_Float_info` Structures

</div>

</div>

</div>

The `CONSTANT_Integer_info` and `CONSTANT_Float_info` structures
represent 4-byte numeric (`int` and `float`) constants:

``` screen
CONSTANT_Integer_info {
    u1 tag;
    u4 bytes;
}

CONSTANT_Float_info {
    u1 tag;
    u4 bytes;
}
```

The items of these structures are as follows:

<div class="variablelist">

<span class="term">tag</span>  
The `tag` item of the `CONSTANT_Integer_info` structure has the value
`CONSTANT_Integer` (3).

The `tag` item of the `CONSTANT_Float_info` structure has the value
`CONSTANT_Float` (4).

<span class="term">bytes</span>  
The `bytes` item of the `CONSTANT_Integer_info` structure represents the
value of the `int` constant. The bytes of the value are stored in
big-endian (high byte first) order.

The `bytes` item of the `CONSTANT_Float_info` structure represents the
value of the `float` constant in IEEE 754 binary32 floating-point format
(<a href="jvms-2.html#jvms-2.3.2" class="xref"
title="2.3.2. Floating-Point Types and Values">§2.3.2</a>). The bytes of
the item are stored in big-endian (high byte first) order.

The value represented by the `CONSTANT_Float_info` structure is
determined as follows. The bytes of the value are first converted into
an `int` constant <span class="emphasis">*bits*</span>. Then:

<div class="norm">

- If <span class="emphasis">*bits*</span> is `0x7f800000`, the `float`
  value will be positive infinity.

- If <span class="emphasis">*bits*</span> is `0xff800000`, the `float`
  value will be negative infinity.

- If <span class="emphasis">*bits*</span> is in the range `0x7f800001`
  through `0x7fffffff` or in the range `0xff800001` through
  `0xffffffff`, the `float` value will be NaN.

- In all other cases, let `s`, `e`, and `m` be three values that might
  be computed from <span class="emphasis">*bits*</span>:

  ``` screen
  int s = ((bits >> 31) == 0) ? 1 : -1;
  int e = ((bits >> 23) & 0xff);
  int m = (e == 0) ?
            (bits & 0x7fffff) << 1 :
            (bits & 0x7fffff) | 0x800000;
            
  ```

</div>

Then the `float` value equals the result of the mathematical expression
`s · m · 2`<sup>`e-150`</sup>.

</div>

</div>

<div id="jvms-4.4.5" class="section">

<div class="titlepage">

<div>

<div>

### 4.4.5. The `CONSTANT_Long_info` and `CONSTANT_Double_info` Structures

</div>

</div>

</div>

The `CONSTANT_Long_info` and `CONSTANT_Double_info` represent 8-byte
numeric (`long` and `double`) constants:

``` screen
CONSTANT_Long_info {
    u1 tag;
    u4 high_bytes;
    u4 low_bytes;
}

CONSTANT_Double_info {
    u1 tag;
    u4 high_bytes;
    u4 low_bytes;
}
```

All 8-byte constants take up two entries in the `constant_pool` table of
the `class` file. If a `CONSTANT_Long_info` or `CONSTANT_Double_info`
structure is the entry at index <span class="emphasis">*n*</span> in the
`constant_pool` table, then the next usable entry in the table is
located at index <span class="emphasis">*n*</span>+2. The
`constant_pool` index <span class="emphasis">*n*</span>+1 must be valid
but is considered unusable.

In retrospect, making 8-byte constants take two constant pool entries
was a poor choice.

The items of these structures are as follows:

<div class="variablelist">

<span class="term">tag</span>  
The `tag` item of the `CONSTANT_Long_info` structure has the value
`CONSTANT_Long` (5).

The `tag` item of the `CONSTANT_Double_info` structure has the value
`CONSTANT_Double` (6).

<span class="term">high_bytes, low_bytes</span>  
The unsigned `high_bytes` and `low_bytes` items of the
`CONSTANT_Long_info` structure together represent the value of the
`long` constant

``` screen
((long) high_bytes << 32) + low_bytes
      
```

where the bytes of each of `high_bytes` and `low_bytes` are stored in
big-endian (high byte first) order.

The `high_bytes` and `low_bytes` items of the `CONSTANT_Double_info`
structure together represent the `double` value in IEEE 754 binary64
floating-point format (<a href="jvms-2.html#jvms-2.3.2" class="xref"
title="2.3.2. Floating-Point Types and Values">§2.3.2</a>). The bytes of
each item are stored in big-endian (high byte first) order.

The value represented by the `CONSTANT_Double_info` structure is
determined as follows. The `high_bytes` and `low_bytes` items are
converted into the `long` constant <span class="emphasis">*bits*</span>,
which is equal to

``` screen
((long) high_bytes << 32) + low_bytes
      
```

Then:

<div class="norm">

- If <span class="emphasis">*bits*</span> is `0x7ff0000000000000L`, the
  `double` value will be positive infinity.

- If <span class="emphasis">*bits*</span> is `0xfff0000000000000L`, the
  `double` value will be negative infinity.

- If <span class="emphasis">*bits*</span> is in the range
  `0x7ff0000000000001L` through `0x7fffffffffffffffL` or in the range
  `0xfff0000000000001L` through `0xffffffffffffffffL`, the double value
  will be NaN.

- In all other cases, let `s`, `e`, and `m` be three values that might
  be computed from <span class="emphasis">*bits*</span>:

  ``` screen
  int s = ((bits >> 63) == 0) ? 1 : -1;
  int e = (int)((bits >> 52) & 0x7ffL);
  long m = (e == 0) ?
             (bits & 0xfffffffffffffL) << 1 :
             (bits & 0xfffffffffffffL) | 0x10000000000000L;
            
  ```

</div>

Then the floating-point value equals the `double` value of the
mathematical expression `s · m · 2`<sup>`e-1075`</sup>.

</div>

</div>

<div id="jvms-4.4.6" class="section">

<div class="titlepage">

<div>

<div>

### 4.4.6. The `CONSTANT_NameAndType_info` Structure

</div>

</div>

</div>

The `CONSTANT_NameAndType_info` structure is used to represent a field
or method, without indicating which class or interface type it belongs
to:

``` screen
CONSTANT_NameAndType_info {
    u1 tag;
    u2 name_index;
    u2 descriptor_index;
}
```

The items of the `CONSTANT_NameAndType_info` structure are as follows:

<div class="variablelist">

<span class="term">tag</span>  
The `tag` item has the value `CONSTANT_NameAndType` (12).

<span class="term">name_index</span>  
The value of the `name_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
either a valid unqualified name denoting a field or method
(<a href="jvms-4.html#jvms-4.2.2" class="xref"
title="4.2.2. Unqualified Names">§4.2.2</a>), or the special method name
`<init>` (<a href="jvms-2.html#jvms-2.9.1" class="xref"
title="2.9.1. Instance Initialization Methods">§2.9.1</a>).

<span class="term">descriptor_index</span>  
The value of the `descriptor_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
a valid field descriptor or method descriptor
(<a href="jvms-4.html#jvms-4.3.2" class="xref"
title="4.3.2. Field Descriptors">§4.3.2</a>,
<a href="jvms-4.html#jvms-4.3.3" class="xref"
title="4.3.3. Method Descriptors">§4.3.3</a>).

</div>

</div>

<div id="jvms-4.4.7" class="section">

<div class="titlepage">

<div>

<div>

### 4.4.7. The `CONSTANT_Utf8_info` Structure

</div>

</div>

</div>

The `CONSTANT_Utf8_info` structure is used to represent constant string
values:

``` screen
CONSTANT_Utf8_info {
    u1 tag;
    u2 length;
    u1 bytes[length];
}
```

The items of the `CONSTANT_Utf8_info` structure are as follows:

<div class="variablelist">

<span class="term">tag</span>  
The `tag` item has the value `CONSTANT_Utf8` (1).

<span class="term">length</span>  
The value of the `length` item gives the number of bytes in the `bytes`
array (not the length of the resulting string).

<span class="term">bytes\[\]</span>  
The `bytes` array contains the bytes of the string.

No byte may have the value `(byte)0`.

No byte may lie in the range `(byte)0xf0` to `(byte)0xff`.

</div>

String content is encoded in modified UTF-8. Modified UTF-8 strings are
encoded so that code point sequences that contain only non-null ASCII
characters can be represented using only 1 byte per code point, but all
code points in the Unicode codespace can be represented. Modified UTF-8
strings are not null-terminated. The encoding is as follows:

<div class="norm">

- Code points in the range '`\u0001`' to '`\u007F`' are represented by a
  single byte:

  <div id="jvms-4.4.7-300-A.1" class="table">

  **Table 4.6. **

  <div class="table-contents">

  <table class="table" data-border="1">
  <tbody>
  <tr>
  <td style="text-align: center;"><span
  class="emphasis"><em>0</em></span></td>
  <td colspan="7" style="text-align: center;"><span
  class="emphasis"><em>bits 6-0</em></span></td>
  </tr>
  </tbody>
  </table>

  </div>

  </div>

    

  The 7 bits of data in the byte give the value of the code point
  represented.

- The null code point ('`\u0000`') and code points in the range
  '`\u0080`' to '`\u07FF`' are represented by a pair of bytes `x` and
  `y` :

  <div id="jvms-4.4.7-300-B.1" class="table">

  **Table 4.7. **

  <div class="table-contents">

  <table class="table" data-border="0">
  <tbody>
  <tr>
  <td><code class="literal">x</code>:</td>
  <td><div id="d5e4876" class="table">
  <p><strong>Table 4.8. </strong></p>
  <div class="table-contents">
  <table class="table" data-border="1">
  <tbody>
  <tr>
  <td style="text-align: center;"><span
  class="emphasis"><em>1</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>1</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>0</em></span></td>
  <td colspan="5" style="text-align: center;"><span
  class="emphasis"><em>bits 10-6</em></span></td>
  </tr>
  </tbody>
  </table>
  </div>
  </div>
  <br />
  </td>
  </tr>
  <tr>
  <td><code class="literal">y</code>:</td>
  <td><div id="d5e4900" class="table">
  <p><strong>Table 4.9. </strong></p>
  <div class="table-contents">
  <table class="table" data-border="1">
  <tbody>
  <tr>
  <td style="text-align: center;"><span
  class="emphasis"><em>1</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>0</em></span></td>
  <td colspan="6" style="text-align: center;"><span
  class="emphasis"><em>bits 5-0</em></span></td>
  </tr>
  </tbody>
  </table>
  </div>
  </div>
  <br />
  </td>
  </tr>
  </tbody>
  </table>

  </div>

  </div>

    

  The two bytes represent the code point with the value:

  ``` screen
  ((x & 0x1f) << 6) + (y & 0x3f)
      
  ```

- Code points in the range '`\u0800`' to '`\uFFFF`' are represented by 3
  bytes `x`, `y`, and `z` :

  <div id="jvms-4.4.7-300-C.1" class="table">

  **Table 4.10. **

  <div class="table-contents">

  <table class="table" data-border="0">
  <tbody>
  <tr>
  <td><code class="literal">x</code>:</td>
  <td><div id="d5e4936" class="table">
  <p><strong>Table 4.11. </strong></p>
  <div class="table-contents">
  <table class="table" data-border="1">
  <tbody>
  <tr>
  <td style="text-align: center;"><span
  class="emphasis"><em>1</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>1</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>1</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>0</em></span></td>
  <td colspan="4" style="text-align: center;"><span
  class="emphasis"><em>bits 15-12</em></span></td>
  </tr>
  </tbody>
  </table>
  </div>
  </div>
  <br />
  </td>
  </tr>
  <tr>
  <td><code class="literal">y</code>:</td>
  <td><div id="d5e4962" class="table">
  <p><strong>Table 4.12. </strong></p>
  <div class="table-contents">
  <table class="table" data-border="1">
  <tbody>
  <tr>
  <td style="text-align: center;"><span
  class="emphasis"><em>1</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>0</em></span></td>
  <td colspan="6" style="text-align: center;"><span
  class="emphasis"><em>bits 11-6</em></span></td>
  </tr>
  </tbody>
  </table>
  </div>
  </div>
  <br />
  </td>
  </tr>
  <tr>
  <td><code class="literal">z</code>:</td>
  <td><div id="d5e4984" class="table">
  <p><strong>Table 4.13. </strong></p>
  <div class="table-contents">
  <table class="table" data-border="1">
  <tbody>
  <tr>
  <td style="text-align: center;"><span
  class="emphasis"><em>1</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>0</em></span></td>
  <td colspan="6" style="text-align: center;"><span
  class="emphasis"><em>bits 5-0</em></span></td>
  </tr>
  </tbody>
  </table>
  </div>
  </div>
  <br />
  </td>
  </tr>
  </tbody>
  </table>

  </div>

  </div>

    

  The three bytes represent the code point with the value:

  ``` screen
  ((x & 0xf) << 12) + ((y & 0x3f) << 6) + (z & 0x3f)
      
  ```

- Characters with code points above U+FFFF (so-called
  <span class="emphasis">*supplementary characters*</span>) are
  represented by separately encoding the two surrogate code units of
  their UTF-16 representation. Each of the surrogate code units is
  represented by three bytes. This means supplementary characters are
  represented by six bytes, `u`, `v`, `w`, `x`, `y`, and `z` :

  <div id="jvms-4.4.7-300-D.1" class="table">

  **Table 4.14. **

  <div class="table-contents">

  <table class="table" data-border="0">
  <tbody>
  <tr>
  <td><code class="literal">u</code>:</td>
  <td><div id="d5e5022" class="table">
  <p><strong>Table 4.15. </strong></p>
  <div class="table-contents">
  <table class="table" data-border="1">
  <tbody>
  <tr>
  <td style="text-align: center;"><span
  class="emphasis"><em>1</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>1</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>1</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>0</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>1</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>1</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>0</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>1</em></span></td>
  </tr>
  </tbody>
  </table>
  </div>
  </div>
  <br />
  </td>
  </tr>
  <tr>
  <td><code class="literal">v</code>:</td>
  <td><div id="d5e5054" class="table">
  <p><strong>Table 4.16. </strong></p>
  <div class="table-contents">
  <table class="table" data-border="1">
  <tbody>
  <tr>
  <td style="text-align: center;"><span
  class="emphasis"><em>1</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>0</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>1</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>0</em></span></td>
  <td colspan="4" style="text-align: center;"><span
  class="emphasis"><em>(bits 20-16)-1</em></span></td>
  </tr>
  </tbody>
  </table>
  </div>
  </div>
  <br />
  </td>
  </tr>
  <tr>
  <td><code class="literal">w</code>:</td>
  <td><div id="d5e5080" class="table">
  <p><strong>Table 4.17. </strong></p>
  <div class="table-contents">
  <table class="table" data-border="1">
  <tbody>
  <tr>
  <td style="text-align: center;"><span
  class="emphasis"><em>1</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>0</em></span></td>
  <td colspan="6" style="text-align: center;"><span
  class="emphasis"><em>bits 15-10</em></span></td>
  </tr>
  </tbody>
  </table>
  </div>
  </div>
  <br />
  </td>
  </tr>
  <tr>
  <td><code class="literal">x</code>:</td>
  <td><div id="d5e5102" class="table">
  <p><strong>Table 4.18. </strong></p>
  <div class="table-contents">
  <table class="table" data-border="1">
  <tbody>
  <tr>
  <td style="text-align: center;"><span
  class="emphasis"><em>1</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>1</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>1</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>0</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>1</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>1</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>0</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>1</em></span></td>
  </tr>
  </tbody>
  </table>
  </div>
  </div>
  <br />
  </td>
  </tr>
  <tr>
  <td><code class="literal">y</code>:</td>
  <td><div id="d5e5134" class="table">
  <p><strong>Table 4.19. </strong></p>
  <div class="table-contents">
  <table class="table" data-border="1">
  <tbody>
  <tr>
  <td style="text-align: center;"><span
  class="emphasis"><em>1</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>0</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>1</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>1</em></span></td>
  <td colspan="4" style="text-align: center;"><span
  class="emphasis"><em>bits 9-6</em></span></td>
  </tr>
  </tbody>
  </table>
  </div>
  </div>
  <br />
  </td>
  </tr>
  <tr>
  <td><code class="literal">z</code>:</td>
  <td><div id="d5e5160" class="table">
  <p><strong>Table 4.20. </strong></p>
  <div class="table-contents">
  <table class="table" data-border="1">
  <tbody>
  <tr>
  <td style="text-align: center;"><span
  class="emphasis"><em>1</em></span></td>
  <td style="text-align: center;"><span
  class="emphasis"><em>0</em></span></td>
  <td colspan="6" style="text-align: center;"><span
  class="emphasis"><em>bits 5-0</em></span></td>
  </tr>
  </tbody>
  </table>
  </div>
  </div>
  <br />
  </td>
  </tr>
  </tbody>
  </table>

  </div>

  </div>

    

  The six bytes represent the code point with the value:

  ``` screen
  0x10000 + ((v & 0x0f) << 16) + ((w & 0x3f) << 10) +
  ((y & 0x0f) << 6) + (z & 0x3f)
      
  ```

</div>

The bytes of multibyte characters are stored in the `class` file in
big-endian (high byte first) order.

There are two differences between this format and the "standard" UTF-8
format. First, the null character `(char)0` is encoded using the 2-byte
format rather than the 1-byte format, so that modified UTF-8 strings
never have embedded nulls. Second, only the 1-byte, 2-byte, and 3-byte
formats of standard UTF-8 are used. The Java Virtual Machine does not
recognize the four-byte format of standard UTF-8; it uses its own
two-times-three-byte format instead.

For more information regarding the standard UTF-8 format, see Section
3.9 *Unicode Encoding Forms* of *The Unicode Standard, Version 17.0.0*.

</div>

<div id="jvms-4.4.8" class="section">

<div class="titlepage">

<div>

<div>

### 4.4.8. The `CONSTANT_MethodHandle_info` Structure

</div>

</div>

</div>

The `CONSTANT_MethodHandle_info` structure is used to represent a method
handle:

``` screen
CONSTANT_MethodHandle_info {
    u1 tag;
    u1 reference_kind;
    u2 reference_index;
}
```

The items of the `CONSTANT_MethodHandle_info` structure are the
following:

<div class="variablelist">

<span class="term">tag</span>  
The `tag` item has the value `CONSTANT_MethodHandle` (15).

<span class="term">reference_kind</span>  
The value of the `reference_kind` item must be in the range 1 to 9. The
value denotes the <span class="emphasis">*kind*</span> of this method
handle, which characterizes its bytecode behavior
(<a href="jvms-5.html#jvms-5.4.3.5" class="xref"
title="5.4.3.5. Method Type and Method Handle Resolution">§5.4.3.5</a>).

<span class="term">reference_index</span>  
The value of the `reference_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be
as follows:

<div class="norm">

- If the value of the `reference_kind` item is 1 (`REF_getField`), 2
  (`REF_getStatic`), 3 (`REF_putField`), or 4 (`REF_putStatic`), then
  the `constant_pool` entry at that index must be a
  `CONSTANT_Fieldref_info` structure
  (<a href="jvms-4.html#jvms-4.4.2" class="xref"
  title="4.4.2. The CONSTANT_Fieldref_info, CONSTANT_Methodref_info, and CONSTANT_InterfaceMethodref_info Structures">§4.4.2</a>)
  representing a field for which a method handle is to be created.

- If the value of the `reference_kind` item is 5 (`REF_invokeVirtual`)
  or 8 (`REF_newInvokeSpecial`), then the `constant_pool` entry at that
  index must be a `CONSTANT_Methodref_info` structure
  (<a href="jvms-4.html#jvms-4.4.2" class="xref"
  title="4.4.2. The CONSTANT_Fieldref_info, CONSTANT_Methodref_info, and CONSTANT_InterfaceMethodref_info Structures">§4.4.2</a>)
  representing a class's method or constructor
  (<a href="jvms-2.html#jvms-2.9.1" class="xref"
  title="2.9.1. Instance Initialization Methods">§2.9.1</a>) for which a
  method handle is to be created.

- If the value of the `reference_kind` item is 6 (`REF_invokeStatic`) or
  7 (`REF_invokeSpecial`), then if the `class` file version number is
  less than 52.0, the `constant_pool` entry at that index must be a
  `CONSTANT_Methodref_info` structure representing a class's method for
  which a method handle is to be created; if the `class` file version
  number is 52.0 or above, the `constant_pool` entry at that index must
  be either a `CONSTANT_Methodref_info` structure or a
  `CONSTANT_InterfaceMethodref_info` structure
  (<a href="jvms-4.html#jvms-4.4.2" class="xref"
  title="4.4.2. The CONSTANT_Fieldref_info, CONSTANT_Methodref_info, and CONSTANT_InterfaceMethodref_info Structures">§4.4.2</a>)
  representing a class's or interface's method for which a method handle
  is to be created.

- If the value of the `reference_kind` item is 9
  (`REF_invokeInterface`), then the `constant_pool` entry at that index
  must be a `CONSTANT_InterfaceMethodref_info` structure representing an
  interface's method for which a method handle is to be created.

</div>

If the value of the `reference_kind` item is 5 (`REF_invokeVirtual`), 6
(`REF_invokeStatic`), 7 (`REF_invokeSpecial`), or 9
(`REF_invokeInterface`), the name of the method represented by a
`CONSTANT_Methodref_info` structure or a
`CONSTANT_InterfaceMethodref_info` structure must not be `<init>` or
`<clinit>`.

If the value is 8 (`REF_newInvokeSpecial`), the name of the method
represented by a `CONSTANT_Methodref_info` structure must be `<init>`.

</div>

</div>

<div id="jvms-4.4.9" class="section">

<div class="titlepage">

<div>

<div>

### 4.4.9. The `CONSTANT_MethodType_info` Structure

</div>

</div>

</div>

The `CONSTANT_MethodType_info` structure is used to represent a method
type:

``` screen
CONSTANT_MethodType_info {
    u1 tag;
    u2 descriptor_index;
}
```

The items of the `CONSTANT_MethodType_info` structure are as follows:

<div class="variablelist">

<span class="term">tag</span>  
The `tag` item has the value `CONSTANT_MethodType` (16).

<span class="term">descriptor_index</span>  
The value of the `descriptor_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
a method descriptor (<a href="jvms-4.html#jvms-4.3.3" class="xref"
title="4.3.3. Method Descriptors">§4.3.3</a>).

</div>

</div>

<div id="jvms-4.4.10" class="section">

<div class="titlepage">

<div>

<div>

### 4.4.10. The `CONSTANT_Dynamic_info` and `CONSTANT_InvokeDynamic_info` Structures

</div>

</div>

</div>

Most structures in the `constant_pool` table represent entities
directly, by combining names, descriptors, and values recorded
statically in the table. In contrast, the `CONSTANT_Dynamic_info` and
`CONSTANT_InvokeDynamic_info` structures represent entities indirectly,
by pointing to code which computes an entity dynamically. The code,
called a <span class="emphasis">*bootstrap method*</span>, is invoked by
the Java Virtual Machine during resolution of symbolic references
derived from these structures
(<a href="jvms-5.html#jvms-5.1" class="xref"
title="5.1. The Run-Time Constant Pool">§5.1</a>,
<a href="jvms-5.html#jvms-5.4.3.6" class="xref"
title="5.4.3.6. Dynamically-Computed Constant and Call Site Resolution">§5.4.3.6</a>).
Each structure specifies a bootstrap method as well as an auxiliary name
and type that characterize the entity to be computed. In more detail:

<div class="norm">

- The `CONSTANT_Dynamic_info` structure is used to represent a
  <span class="emphasis">*dynamically-computed constant*</span>, an
  arbitrary value that is produced by invocation of a bootstrap method
  in the course of an <span class="emphasis">*ldc*</span> instruction
  (<a href="jvms-6.html#jvms-6.5.ldc" class="xref" title="ldc">§<span
  class="emphasis"><em>ldc</em></span></a>), among others. The auxiliary
  type specified by the structure constrains the type of the
  dynamically-computed constant.

- The `CONSTANT_InvokeDynamic_info` structure is used to represent a
  <span class="emphasis">*dynamically-computed call site*</span>, an
  instance of `java.lang.invoke.CallSite` that is produced by invocation
  of a bootstrap method in the course of an
  <span class="emphasis">*invokedynamic*</span> instruction
  (<a href="jvms-6.html#jvms-6.5.invokedynamic" class="xref"
  title="invokedynamic">§<span
  class="emphasis"><em>invokedynamic</em></span></a>). The auxiliary
  type specified by the structure constrains the method type of the
  dynamically-computed call site.

</div>

``` screen
CONSTANT_Dynamic_info {
    u1 tag;
    u2 bootstrap_method_attr_index;
    u2 name_and_type_index;
}

CONSTANT_InvokeDynamic_info {
    u1 tag;
    u2 bootstrap_method_attr_index;
    u2 name_and_type_index;
}
```

The items of these structures are as follows:

<div class="variablelist">

<span class="term">tag</span>  
The `tag` item of a `CONSTANT_Dynamic_info` structure has the value
`CONSTANT_Dynamic` (17).

The `tag` item of a `CONSTANT_InvokeDynamic_info` structure has the
value `CONSTANT_InvokeDynamic` (18).

<span class="term">bootstrap_method_attr_index</span>  
The value of the `bootstrap_method_attr_index` item must be a valid
index into the `bootstrap_methods` array of the bootstrap method table
of this `class` file (<a href="jvms-4.html#jvms-4.7.23" class="xref"
title="4.7.23. The BootstrapMethods Attribute">§4.7.23</a>).

`CONSTANT_Dynamic_info` structures are unique in that they are
syntactically allowed to refer to themselves via the bootstrap method
table. Rather than mandating that such cycles are detected when classes
are loaded (a potentially expensive check), we permit cycles initially
but mandate a failure at resolution
(<a href="jvms-5.html#jvms-5.4.3.6" class="xref"
title="5.4.3.6. Dynamically-Computed Constant and Call Site Resolution">§5.4.3.6</a>).

<span class="term">name_and_type_index</span>  
The value of the `name_and_type_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_NameAndType_info` structure
(<a href="jvms-4.html#jvms-4.4.6" class="xref"
title="4.4.6. The CONSTANT_NameAndType_info Structure">§4.4.6</a>). This
`constant_pool` entry indicates a name and descriptor.

In a `CONSTANT_Dynamic_info` structure, the indicated descriptor must be
a field descriptor (<a href="jvms-4.html#jvms-4.3.2" class="xref"
title="4.3.2. Field Descriptors">§4.3.2</a>).

In a `CONSTANT_InvokeDynamic_info` structure, the indicated descriptor
must be a method descriptor
(<a href="jvms-4.html#jvms-4.3.3" class="xref"
title="4.3.3. Method Descriptors">§4.3.3</a>).

</div>

</div>

<div id="jvms-4.4.11" class="section">

<div class="titlepage">

<div>

<div>

### 4.4.11. The `CONSTANT_Module_info` Structure

</div>

</div>

</div>

The `CONSTANT_Module_info` structure is used to represent a module:

``` screen
CONSTANT_Module_info {
    u1 tag;
    u2 name_index;
}
```

The items of the `CONSTANT_Module_info` structure are as follows:

<div class="variablelist">

<span class="term">tag</span>  
The `tag` item has the value `CONSTANT_Module` (19).

<span class="term">name_index</span>  
The value of the `name_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
a valid module name (<a href="jvms-4.html#jvms-4.2.3" class="xref"
title="4.2.3. Module and Package Names">§4.2.3</a>).

</div>

A `CONSTANT_Module_info` structure is permitted only in the constant
pool of a `class` file that declares a module, that is, a `ClassFile`
structure where the `access_flags` item has the `ACC_MODULE` flag set.
In all other `class` files, a `CONSTANT_Module_info` structure is
illegal.

</div>

<div id="jvms-4.4.12" class="section">

<div class="titlepage">

<div>

<div>

### 4.4.12. The `CONSTANT_Package_info` Structure

</div>

</div>

</div>

The `CONSTANT_Package_info` structure is used to represent a package
exported or opened by a module:

``` screen
CONSTANT_Package_info {
    u1 tag;
    u2 name_index;
}
```

The items of the `CONSTANT_Package_info` structure are as follows:

<div class="variablelist">

<span class="term">tag</span>  
The `tag` item has the value `CONSTANT_Package` (20).

<span class="term">name_index</span>  
The value of the `name_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
a valid package name encoded in internal form
(<a href="jvms-4.html#jvms-4.2.3" class="xref"
title="4.2.3. Module and Package Names">§4.2.3</a>).

</div>

A `CONSTANT_Package_info` structure is permitted only in the constant
pool of a `class` file that declares a module, that is, a `ClassFile`
structure where the `access_flags` item has the `ACC_MODULE` flag set.
In all other `class` files, a `CONSTANT_Package_info` structure is
illegal.

</div>

</div>

<div id="jvms-4.5" class="section">

<div class="titlepage">

<div>

<div>

## 4.5. Fields

</div>

</div>

</div>

Each field is described by a `field_info` structure.

No two fields in one `class` file may have the same name and descriptor
(<a href="jvms-4.html#jvms-4.3.2" class="xref"
title="4.3.2. Field Descriptors">§4.3.2</a>).

The structure has the following format:

``` screen
field_info {
    u2             access_flags;
    u2             name_index;
    u2             descriptor_index;
    u2             attributes_count;
    attribute_info attributes[attributes_count];
}
```

The items of the `field_info` structure are as follows:

<div class="variablelist">

<span class="term">access_flags</span>  
The value of the `access_flags` item is a mask of flags used to denote
access permission to and properties of this field. The interpretation of
each flag, when set, is specified in
<a href="jvms-4.html#jvms-4.5-200-A.1" class="xref"
title="Table 4.5-A. Field access and property flags">Table 4.5-A</a>.

<div id="jvms-4.5-200-A.1" class="table">

**Table 4.5-A. Field access and property flags**

<div class="table-contents">

| Flag Name | Value | Interpretation |
|----|----|----|
| `ACC_PUBLIC` | 0x0001 | Declared `public`; may be accessed from outside its package. |
| `ACC_PRIVATE` | 0x0002 | Declared `private`; accessible only within the defining class and other classes belonging to the same nest (<a href="jvms-5.html#jvms-5.4.4" class="xref"
title="5.4.4. Access Control">§5.4.4</a>). |
| `ACC_PROTECTED` | 0x0004 | Declared `protected`; may be accessed within subclasses. |
| `ACC_STATIC` | 0x0008 | Declared `static`. |
| `ACC_FINAL` | 0x0010 | Declared `final`; never directly assigned to after object construction (JLS §17.5). |
| `ACC_VOLATILE` | 0x0040 | Declared `volatile`; cannot be cached. |
| `ACC_TRANSIENT` | 0x0080 | Declared `transient`; not written or read by a persistent object manager. |
| `ACC_SYNTHETIC` | 0x1000 | Declared synthetic; not present in the source code. |
| `ACC_ENUM` | 0x4000 | Declared as an element of an `enum` class. |

</div>

</div>

  

Fields of classes may set any of the flags in
<a href="jvms-4.html#jvms-4.5-200-A.1" class="xref"
title="Table 4.5-A. Field access and property flags">Table 4.5-A</a>.
However, each field of a class may have at most one of its `ACC_PUBLIC`,
`ACC_PRIVATE`, and `ACC_PROTECTED` flags set (JLS §8.3.1), and must not
have both its `ACC_FINAL` and `ACC_VOLATILE` flags set (JLS §8.3.1.4).

Fields of interfaces must have their `ACC_PUBLIC`, `ACC_STATIC`, and
`ACC_FINAL` flags set; they may have their `ACC_SYNTHETIC` flag set and
must not have any of the other flags in
<a href="jvms-4.html#jvms-4.5-200-A.1" class="xref"
title="Table 4.5-A. Field access and property flags">Table 4.5-A</a> set
(JLS §9.3).

The `ACC_SYNTHETIC` flag indicates that this field was generated by a
compiler and does not appear in source code.

The `ACC_ENUM` flag indicates that this field is used to hold an element
of an enum class (JLS §8.9).

All bits of the `access_flags` item not assigned in
<a href="jvms-4.html#jvms-4.5-200-A.1" class="xref"
title="Table 4.5-A. Field access and property flags">Table 4.5-A</a> are
reserved for future use. They should be set to zero in generated `class`
files and should be ignored by Java Virtual Machine implementations.

<span class="term">name_index</span>  
The value of the `name_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) which
represents a valid unqualified name denoting a field
(<a href="jvms-4.html#jvms-4.2.2" class="xref"
title="4.2.2. Unqualified Names">§4.2.2</a>).

<span class="term">descriptor_index</span>  
The value of the `descriptor_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) which
represents a valid field descriptor
(<a href="jvms-4.html#jvms-4.3.2" class="xref"
title="4.3.2. Field Descriptors">§4.3.2</a>).

<span class="term">attributes_count</span>  
The value of the `attributes_count` item indicates the number of
additional attributes of this field.

<span class="term">attributes\[\]</span>  
Each value of the `attributes` table must be an `attribute_info`
structure (<a href="jvms-4.html#jvms-4.7" class="xref"
title="4.7. Attributes">§4.7</a>).

A field can have any number of optional attributes associated with it.

The attributes defined by this specification as appearing in the
`attributes` table of a `field_info` structure are listed in
<a href="jvms-4.html#jvms-4.7-320" class="xref"
title="Table 4.7-C. Predefined class file attributes (by location)">Table 4.7-C</a>.

The rules concerning attributes defined to appear in the `attributes`
table of a `field_info` structure are given in
<a href="jvms-4.html#jvms-4.7" class="xref"
title="4.7. Attributes">§4.7</a>.

The rules concerning non-predefined attributes in the `attributes` table
of a `field_info` structure are given in
<a href="jvms-4.html#jvms-4.7.1" class="xref"
title="4.7.1. Defining and Naming New Attributes">§4.7.1</a>.

</div>

</div>

<div id="jvms-4.6" class="section">

<div class="titlepage">

<div>

<div>

## 4.6. Methods

</div>

</div>

</div>

Each method, including each instance initialization method
(<a href="jvms-2.html#jvms-2.9.1" class="xref"
title="2.9.1. Instance Initialization Methods">§2.9.1</a>) and the class
or interface initialization method
(<a href="jvms-2.html#jvms-2.9.2" class="xref"
title="2.9.2. Class Initialization Methods">§2.9.2</a>), is described by
a `method_info` structure.

No two methods in one `class` file may have the same name and descriptor
(<a href="jvms-4.html#jvms-4.3.3" class="xref"
title="4.3.3. Method Descriptors">§4.3.3</a>).

The structure has the following format:

``` screen
method_info {
    u2             access_flags;
    u2             name_index;
    u2             descriptor_index;
    u2             attributes_count;
    attribute_info attributes[attributes_count];
}
```

The items of the `method_info` structure are as follows:

<div class="variablelist">

<span class="term">access_flags</span>  
The value of the `access_flags` item is a mask of flags used to denote
access permission to and properties of this method. The interpretation
of each flag, when set, is specified in
<a href="jvms-4.html#jvms-4.6-200-A.1" class="xref"
title="Table 4.6-A. Method access and property flags">Table 4.6-A</a>.

<div id="jvms-4.6-200-A.1" class="table">

**Table 4.6-A. Method access and property flags**

<div class="table-contents">

| Flag Name | Value | Interpretation |
|----|----|----|
| `ACC_PUBLIC` | 0x0001 | Declared `public`; may be accessed from outside its package. |
| `ACC_PRIVATE` | 0x0002 | Declared `private`; accessible only within the defining class and other classes belonging to the same nest (<a href="jvms-5.html#jvms-5.4.4" class="xref"
title="5.4.4. Access Control">§5.4.4</a>). |
| `ACC_PROTECTED` | 0x0004 | Declared `protected`; may be accessed within subclasses. |
| `ACC_STATIC` | 0x0008 | Declared `static`. |
| `ACC_FINAL` | 0x0010 | Declared `final`; must not be overridden (<a href="jvms-5.html#jvms-5.4.5" class="xref"
title="5.4.5. Method Overriding">§5.4.5</a>). |
| `ACC_SYNCHRONIZED` | 0x0020 | Declared `synchronized`; invocation is wrapped by a monitor use. |
| `ACC_BRIDGE` | 0x0040 | A bridge method, generated by the compiler. |
| `ACC_VARARGS` | 0x0080 | Declared with variable number of arguments. |
| `ACC_NATIVE` | 0x0100 | Declared `native`; implemented in a language other than the Java programming language. |
| `ACC_ABSTRACT` | 0x0400 | Declared `abstract`; no implementation is provided. |
| `ACC_STRICT` | 0x0800 | In a `class` file whose major version number is at least 46 and at most 60: Declared `strictfp`. |
| `ACC_SYNTHETIC` | 0x1000 | Declared synthetic; not present in the source code. |

</div>

</div>

  

The value 0x0800 is interpreted as the `ACC_STRICT` flag only in a
`class` file whose major version number is at least 46 and at most 60.
For methods in such a `class` file, the rules below determine whether
the `ACC_STRICT` flag may be set in combination with other flags.
(Setting the `ACC_STRICT` flag constrained a method's floating-point
instructions in Java SE 1.2 through 16
(<a href="jvms-2.html#jvms-2.8" class="xref"
title="2.8. Floating-Point Arithmetic">§2.8</a>).) For methods in a
`class` file whose major version number is less than 46 or greater than
60, the value 0x0800 is not interpreted as the `ACC_STRICT` flag, but
rather is unassigned; it is not meaningful to "set the `ACC_STRICT`
flag" in such a `class` file.

Methods of classes may have any of the flags in
<a href="jvms-4.html#jvms-4.6-200-A.1" class="xref"
title="Table 4.6-A. Method access and property flags">Table 4.6-A</a>
set. However, each method of a class may have at most one of its
`ACC_PUBLIC`, `ACC_PRIVATE`, and `ACC_PROTECTED` flags set (JLS §8.4.3).

Methods of interfaces may have any of the flags in
<a href="jvms-4.html#jvms-4.6-200-A.1" class="xref"
title="Table 4.6-A. Method access and property flags">Table 4.6-A</a>
set except `ACC_PROTECTED`, `ACC_FINAL`, `ACC_SYNCHRONIZED`, and
`ACC_NATIVE` (JLS §9.4). In a `class` file whose version number is less
than 52.0, each method of an interface must have its `ACC_PUBLIC` and
`ACC_ABSTRACT` flags set; in a `class` file whose version number is 52.0
or above, each method of an interface must have exactly one of its
`ACC_PUBLIC` and `ACC_PRIVATE` flags set.

If a method of a class or interface has its `ACC_ABSTRACT` flag set, it
must not have any of its `ACC_PRIVATE`, `ACC_STATIC`, `ACC_FINAL`,
`ACC_SYNCHRONIZED`, or `ACC_NATIVE` flags set, nor (in a `class` file
whose major version number is at least 46 and at most 60) have its
`ACC_STRICT` flag set.

An instance initialization method
(<a href="jvms-2.html#jvms-2.9.1" class="xref"
title="2.9.1. Instance Initialization Methods">§2.9.1</a>) may have at
most one of its `ACC_PUBLIC`, `ACC_PRIVATE`, and `ACC_PROTECTED` flags
set, and may also have its `ACC_VARARGS` and `ACC_SYNTHETIC` flags set,
and may also (in a `class` file whose major version number is at least
46 and at most 60) have its `ACC_STRICT` flag set, but must not have any
of the other flags in
<a href="jvms-4.html#jvms-4.6-200-A.1" class="xref"
title="Table 4.6-A. Method access and property flags">Table 4.6-A</a>
set.

In a `class` file whose version number is 51.0 or above, a method whose
name is `<clinit>` must have its `ACC_STATIC` flag set.

A class or interface initialization method
(<a href="jvms-2.html#jvms-2.9.2" class="xref"
title="2.9.2. Class Initialization Methods">§2.9.2</a>) is called
implicitly by the Java Virtual Machine. The value of its `access_flags`
item is ignored except for the setting of the `ACC_STATIC` flag and (in
a `class` file whose major version number is at least 46 and at most 60)
the `ACC_STRICT` flag, and the method is exempt from the preceding rules
about legal combinations of flags.

The `ACC_BRIDGE` flag is used to indicate a bridge method generated by a
compiler for the Java programming language.

The `ACC_VARARGS` flag indicates that this method takes a variable
number of arguments at the source code level. A method declared to take
a variable number of arguments must be compiled with the `ACC_VARARGS`
flag set to 1. All other methods must be compiled with the `ACC_VARARGS`
flag set to 0.

The `ACC_SYNTHETIC` flag indicates that this method was generated by a
compiler and does not appear in source code, unless it is one of the
methods named in <a href="jvms-4.html#jvms-4.7.8" class="xref"
title="4.7.8. The Synthetic Attribute">§4.7.8</a>.

All bits of the `access_flags` item not assigned in
<a href="jvms-4.html#jvms-4.6-200-A.1" class="xref"
title="Table 4.6-A. Method access and property flags">Table 4.6-A</a>
are reserved for future use. (This includes the bit corresponding to
0x0800 in a `class` file whose major version number is less than 46 or
greater than 60.) They should be set to zero in generated `class` files
and should be ignored by Java Virtual Machine implementations.

<span class="term">name_index</span>  
The value of the `name_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
either a valid unqualified name denoting a method
(<a href="jvms-4.html#jvms-4.2.2" class="xref"
title="4.2.2. Unqualified Names">§4.2.2</a>), or (if this method is in a
class rather than an interface) the special method name `<init>`, or the
special method name `<clinit>`.

<span class="term">descriptor_index</span>  
The value of the `descriptor_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Utf8_info` structure representing a valid method descriptor
(<a href="jvms-4.html#jvms-4.3.3" class="xref"
title="4.3.3. Method Descriptors">§4.3.3</a>). Furthermore:

<div class="norm">

- If this method is in a class rather than an interface, and the name of
  the method is `<init>`, then the descriptor must denote a `void`
  method.

- If the name of the method is `<clinit>`, then the descriptor must
  denote a `void` method, and, in a `class` file whose version number is
  51.0 or above, a method that takes no arguments.

</div>

A future edition of this specification may require that the last
parameter descriptor of the method descriptor is an array type if the
`ACC_VARARGS` flag is set in the `access_flags` item.

<span class="term">attributes_count</span>  
The value of the `attributes_count` item indicates the number of
additional attributes of this method.

<span class="term">attributes\[\]</span>  
Each value of the `attributes` table must be an `attribute_info`
structure (<a href="jvms-4.html#jvms-4.7" class="xref"
title="4.7. Attributes">§4.7</a>).

A method can have any number of optional attributes associated with it.

The attributes defined by this specification as appearing in the
`attributes` table of a `method_info` structure are listed in
<a href="jvms-4.html#jvms-4.7-320" class="xref"
title="Table 4.7-C. Predefined class file attributes (by location)">Table 4.7-C</a>.

The rules concerning attributes defined to appear in the `attributes`
table of a `method_info` structure are given in
<a href="jvms-4.html#jvms-4.7" class="xref"
title="4.7. Attributes">§4.7</a>.

The rules concerning non-predefined attributes in the `attributes` table
of a `method_info` structure are given in
<a href="jvms-4.html#jvms-4.7.1" class="xref"
title="4.7.1. Defining and Naming New Attributes">§4.7.1</a>.

</div>

</div>

<div id="jvms-4.7" class="section">

<div class="titlepage">

<div>

<div>

## 4.7. Attributes

</div>

</div>

</div>

<span class="emphasis">*Attributes*</span> are used in the `ClassFile`,
`field_info`, `method_info`, `Code_attribute`, and
`record_component_info` structures of the `class` file format
(<a href="jvms-4.html#jvms-4.1" class="xref"
title="4.1. The ClassFile Structure">§4.1</a>,
<a href="jvms-4.html#jvms-4.5" class="xref" title="4.5. Fields">§4.5</a>,
<a href="jvms-4.html#jvms-4.6" class="xref"
title="4.6. Methods">§4.6</a>,
<a href="jvms-4.html#jvms-4.7.3" class="xref"
title="4.7.3. The Code Attribute">§4.7.3</a>,
<a href="jvms-4.html#jvms-4.7.30" class="xref"
title="4.7.30. The Record Attribute">§4.7.30</a>).

All attributes have the following general format:

``` screen
attribute_info {
    u2 attribute_name_index;
    u4 attribute_length;
    u1 info[attribute_length];
}
```

For all attributes, the `attribute_name_index` item must be a valid
unsigned 16-bit index into the constant pool of the class. The
`constant_pool` entry at `attribute_name_index` must be a
`CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the name of the attribute. The value of the `attribute_length` item
indicates the length of the subsequent information in bytes. The length
does not include the initial six bytes that contain the
`attribute_name_index` and `attribute_length` items.

30 attributes are predefined by this specification. They are listed
three times, for ease of navigation:

<div class="norm">

- <a href="jvms-4.html#jvms-4.7-300" class="xref"
  title="Table 4.7-A. Predefined class file attributes (by section)">Table 4.7-A</a>
  is ordered by the attributes' section numbers in this chapter. Each
  attribute is shown with the first version of the `class` file format
  in which it was defined. Also shown is the version of the Java SE
  Platform which introduced that version of the `class` file format
  (<a href="jvms-4.html#jvms-4.1" class="xref"
  title="4.1. The ClassFile Structure">§4.1</a>).

- <a href="jvms-4.html#jvms-4.7-310" class="xref"
  title="Table 4.7-B. Predefined class file attributes (by class file format)">Table 4.7-B</a>
  is ordered by the first version of the `class` file format in which
  each attribute was defined.

- <a href="jvms-4.html#jvms-4.7-320" class="xref"
  title="Table 4.7-C. Predefined class file attributes (by location)">Table 4.7-C</a>
  is ordered by the location in a `class` file where each attribute is
  defined to appear.

</div>

Within the context of their use in this specification, that is, in the
`attributes` tables of the `class` file structures in which they appear,
the names of these predefined attributes are reserved.

Any conditions on the presence of a predefined attribute in an
`attributes` table are specified explicitly in the section which
describes the attribute. If no conditions are specified, then the
attribute may appear any number of times in an `attributes` table.

The predefined attributes are categorized into three groups according to
their purpose:

<div class="orderedlist">

1.  Seven attributes are critical to correct interpretation of the
    `class` file by the Java Virtual Machine:

    <div class="norm">

    - `ConstantValue`

    - `Code`

    - `StackMapTable`

    - `BootstrapMethods`

    - `NestHost`

    - `NestMembers`

    - `PermittedSubclasses`

    </div>

    In a `class` file whose version number is
    <span class="emphasis">*v*</span>, each of these attributes must be
    recognized and correctly read by an implementation of the Java
    Virtual Machine if the implementation supports version
    <span class="emphasis">*v*</span> of the `class` file format, and
    the attribute was first defined in version
    <span class="emphasis">*v*</span> or earlier of the `class` file
    format, and the attribute appears in a location where it is defined
    to appear.

2.  Ten attributes are not critical to correct interpretation of the
    `class` file by the Java Virtual Machine, but are either critical to
    correct interpretation of the `class` file by the class libraries of
    the Java SE Platform, or are useful for tools (in which case the
    section that specifies an attribute describes it as "optional"):

    <div class="norm">

    - `Exceptions`

    - `InnerClasses`

    - `EnclosingMethod`

    - `Synthetic`

    - `Signature`

    - `Record`

    - `SourceFile`

    - `LineNumberTable`

    - `LocalVariableTable`

    - `LocalVariableTypeTable`

    </div>

    In a `class` file whose version number is
    <span class="emphasis">*v*</span>, each of these attributes must be
    recognized and correctly read by an implementation of the Java
    Virtual Machine if the implementation supports version
    <span class="emphasis">*v*</span> of the `class` file format, and
    the attribute was first defined in version
    <span class="emphasis">*v*</span> or earlier of the `class` file
    format, and the attribute appears in a location where it is defined
    to appear.

3.  Thirteen attributes are not critical to correct interpretation of
    the `class` file by the Java Virtual Machine, but contain metadata
    about the `class` file that is either exposed by the class libraries
    of the Java SE Platform, or made available by tools (in which case
    the section that specifies an attribute describes it as "optional"):

    <div class="norm">

    - `SourceDebugExtension`

    - `Deprecated`

    - `RuntimeVisibleAnnotations`

    - `RuntimeInvisibleAnnotations`

    - `RuntimeVisibleParameterAnnotations`

    - `RuntimeInvisibleParameterAnnotations`

    - `RuntimeVisibleTypeAnnotations`

    - `RuntimeInvisibleTypeAnnotations`

    - `AnnotationDefault`

    - `MethodParameters`

    - `Module`

    - `ModulePackages`

    - `ModuleMainClass`

    </div>

    An implementation of the Java Virtual Machine may use the
    information that these attributes contain, or otherwise must
    silently ignore these attributes.

</div>

<div id="jvms-4.7-300" class="table">

**Table 4.7-A. Predefined `class` file attributes (by section)**

<div class="table-contents">

| Attribute | Section | `class` file | Java SE |
|----|----|----|----|
| `ConstantValue` | <a href="jvms-4.html#jvms-4.7.2" class="xref"
title="4.7.2. The ConstantValue Attribute">§4.7.2</a> | 45.3 | 1.0.2 |
| `Code` | <a href="jvms-4.html#jvms-4.7.3" class="xref"
title="4.7.3. The Code Attribute">§4.7.3</a> | 45.3 | 1.0.2 |
| `StackMapTable` | <a href="jvms-4.html#jvms-4.7.4" class="xref"
title="4.7.4. The StackMapTable Attribute">§4.7.4</a> | 50.0 | 6 |
| `Exceptions` | <a href="jvms-4.html#jvms-4.7.5" class="xref"
title="4.7.5. The Exceptions Attribute">§4.7.5</a> | 45.3 | 1.0.2 |
| `InnerClasses` | <a href="jvms-4.html#jvms-4.7.6" class="xref"
title="4.7.6. The InnerClasses Attribute">§4.7.6</a> | 45.3 | 1.1 |
| `EnclosingMethod` | <a href="jvms-4.html#jvms-4.7.7" class="xref"
title="4.7.7. The EnclosingMethod Attribute">§4.7.7</a> | 49.0 | 5.0 |
| `Synthetic` | <a href="jvms-4.html#jvms-4.7.8" class="xref"
title="4.7.8. The Synthetic Attribute">§4.7.8</a> | 45.3 | 1.1 |
| `Signature` | <a href="jvms-4.html#jvms-4.7.9" class="xref"
title="4.7.9. The Signature Attribute">§4.7.9</a> | 49.0 | 5.0 |
| `SourceFile` | <a href="jvms-4.html#jvms-4.7.10" class="xref"
title="4.7.10. The SourceFile Attribute">§4.7.10</a> | 45.3 | 1.0.2 |
| `SourceDebugExtension` | <a href="jvms-4.html#jvms-4.7.11" class="xref"
title="4.7.11. The SourceDebugExtension Attribute">§4.7.11</a> | 49.0 | 5.0 |
| `LineNumberTable` | <a href="jvms-4.html#jvms-4.7.12" class="xref"
title="4.7.12. The LineNumberTable Attribute">§4.7.12</a> | 45.3 | 1.0.2 |
| `LocalVariableTable` | <a href="jvms-4.html#jvms-4.7.13" class="xref"
title="4.7.13. The LocalVariableTable Attribute">§4.7.13</a> | 45.3 | 1.0.2 |
| `LocalVariableTypeTable` | <a href="jvms-4.html#jvms-4.7.14" class="xref"
title="4.7.14. The LocalVariableTypeTable Attribute">§4.7.14</a> | 49.0 | 5.0 |
| `Deprecated` | <a href="jvms-4.html#jvms-4.7.15" class="xref"
title="4.7.15. The Deprecated Attribute">§4.7.15</a> | 45.3 | 1.1 |
| `RuntimeVisibleAnnotations` | <a href="jvms-4.html#jvms-4.7.16" class="xref"
title="4.7.16. The RuntimeVisibleAnnotations Attribute">§4.7.16</a> | 49.0 | 5.0 |
| `RuntimeInvisibleAnnotations` | <a href="jvms-4.html#jvms-4.7.17" class="xref"
title="4.7.17. The RuntimeInvisibleAnnotations Attribute">§4.7.17</a> | 49.0 | 5.0 |
| `RuntimeVisibleParameterAnnotations` | <a href="jvms-4.html#jvms-4.7.18" class="xref"
title="4.7.18. The RuntimeVisibleParameterAnnotations Attribute">§4.7.18</a> | 49.0 | 5.0 |
| `RuntimeInvisibleParameterAnnotations` | <a href="jvms-4.html#jvms-4.7.19" class="xref"
title="4.7.19. The RuntimeInvisibleParameterAnnotations Attribute">§4.7.19</a> | 49.0 | 5.0 |
| `RuntimeVisibleTypeAnnotations` | <a href="jvms-4.html#jvms-4.7.20" class="xref"
title="4.7.20. The RuntimeVisibleTypeAnnotations Attribute">§4.7.20</a> | 52.0 | 8 |
| `RuntimeInvisibleTypeAnnotations` | <a href="jvms-4.html#jvms-4.7.21" class="xref"
title="4.7.21. The RuntimeInvisibleTypeAnnotations Attribute">§4.7.21</a> | 52.0 | 8 |
| `AnnotationDefault` | <a href="jvms-4.html#jvms-4.7.22" class="xref"
title="4.7.22. The AnnotationDefault Attribute">§4.7.22</a> | 49.0 | 5.0 |
| `BootstrapMethods` | <a href="jvms-4.html#jvms-4.7.23" class="xref"
title="4.7.23. The BootstrapMethods Attribute">§4.7.23</a> | 51.0 | 7 |
| `MethodParameters` | <a href="jvms-4.html#jvms-4.7.24" class="xref"
title="4.7.24. The MethodParameters Attribute">§4.7.24</a> | 52.0 | 8 |
| `Module` | <a href="jvms-4.html#jvms-4.7.25" class="xref"
title="4.7.25. The Module Attribute">§4.7.25</a> | 53.0 | 9 |
| `ModulePackages` | <a href="jvms-4.html#jvms-4.7.26" class="xref"
title="4.7.26. The ModulePackages Attribute">§4.7.26</a> | 53.0 | 9 |
| `ModuleMainClass` | <a href="jvms-4.html#jvms-4.7.27" class="xref"
title="4.7.27. The ModuleMainClass Attribute">§4.7.27</a> | 53.0 | 9 |
| `NestHost` | <a href="jvms-4.html#jvms-4.7.28" class="xref"
title="4.7.28. The NestHost Attribute">§4.7.28</a> | 55.0 | 11 |
| `NestMembers` | <a href="jvms-4.html#jvms-4.7.29" class="xref"
title="4.7.29. The NestMembers Attribute">§4.7.29</a> | 55.0 | 11 |
| `Record` | <a href="jvms-4.html#jvms-4.7.30" class="xref"
title="4.7.30. The Record Attribute">§4.7.30</a> | 60.0 | 16 |
| `PermittedSubclasses` | <a href="jvms-4.html#jvms-4.7.31" class="xref"
title="4.7.31. The PermittedSubclasses Attribute">§4.7.31</a> | 61.0 | 17 |

</div>

</div>

  

<div id="jvms-4.7-310" class="table">

**Table 4.7-B. Predefined `class` file attributes (by `class` file
format)**

<div class="table-contents">

| Attribute | `class` file | Java SE | Section |
|----|----|----|----|
| `ConstantValue` | 45.3 | 1.0.2 | <a href="jvms-4.html#jvms-4.7.2" class="xref"
title="4.7.2. The ConstantValue Attribute">§4.7.2</a> |
| `Code` | 45.3 | 1.0.2 | <a href="jvms-4.html#jvms-4.7.3" class="xref"
title="4.7.3. The Code Attribute">§4.7.3</a> |
| `Exceptions` | 45.3 | 1.0.2 | <a href="jvms-4.html#jvms-4.7.5" class="xref"
title="4.7.5. The Exceptions Attribute">§4.7.5</a> |
| `SourceFile` | 45.3 | 1.0.2 | <a href="jvms-4.html#jvms-4.7.10" class="xref"
title="4.7.10. The SourceFile Attribute">§4.7.10</a> |
| `LineNumberTable` | 45.3 | 1.0.2 | <a href="jvms-4.html#jvms-4.7.12" class="xref"
title="4.7.12. The LineNumberTable Attribute">§4.7.12</a> |
| `LocalVariableTable` | 45.3 | 1.0.2 | <a href="jvms-4.html#jvms-4.7.13" class="xref"
title="4.7.13. The LocalVariableTable Attribute">§4.7.13</a> |
| `InnerClasses` | 45.3 | 1.1 | <a href="jvms-4.html#jvms-4.7.6" class="xref"
title="4.7.6. The InnerClasses Attribute">§4.7.6</a> |
| `Synthetic` | 45.3 | 1.1 | <a href="jvms-4.html#jvms-4.7.8" class="xref"
title="4.7.8. The Synthetic Attribute">§4.7.8</a> |
| `Deprecated` | 45.3 | 1.1 | <a href="jvms-4.html#jvms-4.7.15" class="xref"
title="4.7.15. The Deprecated Attribute">§4.7.15</a> |
| `EnclosingMethod` | 49.0 | 5.0 | <a href="jvms-4.html#jvms-4.7.7" class="xref"
title="4.7.7. The EnclosingMethod Attribute">§4.7.7</a> |
| `Signature` | 49.0 | 5.0 | <a href="jvms-4.html#jvms-4.7.9" class="xref"
title="4.7.9. The Signature Attribute">§4.7.9</a> |
| `SourceDebugExtension` | 49.0 | 5.0 | <a href="jvms-4.html#jvms-4.7.11" class="xref"
title="4.7.11. The SourceDebugExtension Attribute">§4.7.11</a> |
| `LocalVariableTypeTable` | 49.0 | 5.0 | <a href="jvms-4.html#jvms-4.7.14" class="xref"
title="4.7.14. The LocalVariableTypeTable Attribute">§4.7.14</a> |
| `RuntimeVisibleAnnotations` | 49.0 | 5.0 | <a href="jvms-4.html#jvms-4.7.16" class="xref"
title="4.7.16. The RuntimeVisibleAnnotations Attribute">§4.7.16</a> |
| `RuntimeInvisibleAnnotations` | 49.0 | 5.0 | <a href="jvms-4.html#jvms-4.7.17" class="xref"
title="4.7.17. The RuntimeInvisibleAnnotations Attribute">§4.7.17</a> |
| `RuntimeVisibleParameterAnnotations` | 49.0 | 5.0 | <a href="jvms-4.html#jvms-4.7.18" class="xref"
title="4.7.18. The RuntimeVisibleParameterAnnotations Attribute">§4.7.18</a> |
| `RuntimeInvisibleParameterAnnotations` | 49.0 | 5.0 | <a href="jvms-4.html#jvms-4.7.19" class="xref"
title="4.7.19. The RuntimeInvisibleParameterAnnotations Attribute">§4.7.19</a> |
| `AnnotationDefault` | 49.0 | 5.0 | <a href="jvms-4.html#jvms-4.7.22" class="xref"
title="4.7.22. The AnnotationDefault Attribute">§4.7.22</a> |
| `StackMapTable` | 50.0 | 6 | <a href="jvms-4.html#jvms-4.7.4" class="xref"
title="4.7.4. The StackMapTable Attribute">§4.7.4</a> |
| `BootstrapMethods` | 51.0 | 7 | <a href="jvms-4.html#jvms-4.7.23" class="xref"
title="4.7.23. The BootstrapMethods Attribute">§4.7.23</a> |
| `RuntimeVisibleTypeAnnotations` | 52.0 | 8 | <a href="jvms-4.html#jvms-4.7.20" class="xref"
title="4.7.20. The RuntimeVisibleTypeAnnotations Attribute">§4.7.20</a> |
| `RuntimeInvisibleTypeAnnotations` | 52.0 | 8 | <a href="jvms-4.html#jvms-4.7.21" class="xref"
title="4.7.21. The RuntimeInvisibleTypeAnnotations Attribute">§4.7.21</a> |
| `MethodParameters` | 52.0 | 8 | <a href="jvms-4.html#jvms-4.7.24" class="xref"
title="4.7.24. The MethodParameters Attribute">§4.7.24</a> |
| `Module` | 53.0 | 9 | <a href="jvms-4.html#jvms-4.7.25" class="xref"
title="4.7.25. The Module Attribute">§4.7.25</a> |
| `ModulePackages` | 53.0 | 9 | <a href="jvms-4.html#jvms-4.7.26" class="xref"
title="4.7.26. The ModulePackages Attribute">§4.7.26</a> |
| `ModuleMainClass` | 53.0 | 9 | <a href="jvms-4.html#jvms-4.7.27" class="xref"
title="4.7.27. The ModuleMainClass Attribute">§4.7.27</a> |
| `NestHost` | 55.0 | 11 | <a href="jvms-4.html#jvms-4.7.28" class="xref"
title="4.7.28. The NestHost Attribute">§4.7.28</a> |
| `NestMembers` | 55.0 | 11 | <a href="jvms-4.html#jvms-4.7.29" class="xref"
title="4.7.29. The NestMembers Attribute">§4.7.29</a> |
| `Record` | 60.0 | 16 | <a href="jvms-4.html#jvms-4.7.30" class="xref"
title="4.7.30. The Record Attribute">§4.7.30</a> |
| `PermittedSubclasses` | 61.0 | 17 | <a href="jvms-4.html#jvms-4.7.31" class="xref"
title="4.7.31. The PermittedSubclasses Attribute">§4.7.31</a> |

</div>

</div>

  

<div id="jvms-4.7-320" class="table">

**Table 4.7-C. Predefined `class` file attributes (by location)**

<div class="table-contents">

| Attribute | Location | `class` file |
|----|----|----|
| `SourceFile` | `ClassFile` | 45.3 |
| `InnerClasses` | `ClassFile` | 45.3 |
| `EnclosingMethod` | `ClassFile` | 49.0 |
| `SourceDebugExtension` | `ClassFile` | 49.0 |
| `BootstrapMethods` | `ClassFile` | 51.0 |
| `Module`, `ModulePackages`, `ModuleMainClass` | `ClassFile` | 53.0 |
| `NestHost`, `NestMembers` | `ClassFile` | 55.0 |
| `Record` | `ClassFile` | 60.0 |
| `PermittedSubclasses` | `ClassFile` | 61.0 |
| `ConstantValue` | `field_info` | 45.3 |
| `Code` | `method_info` | 45.3 |
| `Exceptions` | `method_info` | 45.3 |
| `RuntimeVisibleParameterAnnotations`, `RuntimeInvisibleParameterAnnotations` | `method_info` | 49.0 |
| `AnnotationDefault` | `method_info` | 49.0 |
| `MethodParameters` | `method_info` | 52.0 |

</div>

</div>

  

<div id="jvms-4.7-320.1" class="table">

**Table 4.7-C (cont.). Predefined `class` file attributes (by
location)**

<div class="table-contents">

| Attribute | Location | `class` file |
|----|----|----|
| `Synthetic` | `ClassFile`, `field_info`, `method_info` | 45.3 |
| `Deprecated` | `ClassFile`, `field_info`, `method_info` | 45.3 |
| `Signature` | `ClassFile`, `field_info`, `method_info`, `record_component_info` | 49.0 |
| `RuntimeVisibleAnnotations`, `RuntimeInvisibleAnnotations` | `ClassFile`, `field_info`, `method_info`, `record_component_info` | 49.0 |
| `LineNumberTable` | `Code` | 45.3 |
| `LocalVariableTable` | `Code` | 45.3 |
| `LocalVariableTypeTable` | `Code` | 49.0 |
| `StackMapTable` | `Code` | 50.0 |
| `RuntimeVisibleTypeAnnotations`, `RuntimeInvisibleTypeAnnotations` | `ClassFile`, `field_info`, `method_info`, `Code`, `record_component_info` | 52.0 |

</div>

</div>

  

<div id="jvms-4.7.1" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.1. Defining and Naming New Attributes

</div>

</div>

</div>

Compilers are permitted to define and emit `class` files containing new
attributes in the `attributes` tables of `class` file structures,
`field_info` structures, `method_info` structures, and `Code` attributes
(<a href="jvms-4.html#jvms-4.7.3" class="xref"
title="4.7.3. The Code Attribute">§4.7.3</a>). Java Virtual Machine
implementations are permitted to recognize and use new attributes found
in these `attributes` tables. However, any attribute not defined as part
of this specification must not affect the semantics of the `class` file.
Java Virtual Machine implementations are required to silently ignore
attributes they do not recognize.

For instance, defining a new attribute to support vendor-specific
debugging is permitted. Because Java Virtual Machine implementations are
required to ignore attributes they do not recognize, `class` files
intended for that particular Java Virtual Machine implementation will be
usable by other implementations even if those implementations cannot
make use of the additional debugging information that the `class` files
contain.

Java Virtual Machine implementations are specifically prohibited from
throwing an exception or otherwise refusing to use `class` files simply
because of the presence of some new attribute. Of course, tools
operating on `class` files may not run correctly if given `class` files
that do not contain all the attributes they require.

Two attributes that are intended to be distinct, but that happen to use
the same attribute name and are of the same length, will conflict on
implementations that recognize either attribute. Attributes defined
other than in this specification should have names chosen according to
the package naming convention described in *The Java Language
Specification, Java SE 26 Edition* (JLS §6.1).

Future versions of this specification may define additional attributes.

</div>

<div id="jvms-4.7.2" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.2. The `ConstantValue` Attribute

</div>

</div>

</div>

The `ConstantValue` attribute is a fixed-length attribute in the
`attributes` table of a `field_info` structure
(<a href="jvms-4.html#jvms-4.5" class="xref" title="4.5. Fields">§4.5</a>).
A `ConstantValue` attribute represents the value of a constant
expression (JLS §15.28), and is used as follows:

<div class="norm">

- If the `ACC_STATIC` flag in the `access_flags` item of the
  `field_info` structure is set, then the field represented by the
  `field_info` structure is assigned the value represented by its
  `ConstantValue` attribute as part of the initialization of the class
  or interface declaring the field
  (<a href="jvms-5.html#jvms-5.5" class="xref"
  title="5.5. Initialization">§5.5</a>). This occurs prior to the
  invocation of the class or interface initialization method of that
  class or interface (<a href="jvms-2.html#jvms-2.9.2" class="xref"
  title="2.9.2. Class Initialization Methods">§2.9.2</a>).

- Otherwise, the Java Virtual Machine must silently ignore the
  attribute.

</div>

There may be at most one `ConstantValue` attribute in the `attributes`
table of a `field_info` structure.

The `ConstantValue` attribute has the following format:

``` screen
ConstantValue_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 constantvalue_index;
}
```

The items of the `ConstantValue_attribute` structure are as follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the string "`ConstantValue`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item must be two.

<span class="term">constantvalue_index</span>  
The value of the `constantvalue_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index gives
the value represented by this attribute. The `constant_pool` entry must
be of a type appropriate to the field, as specified in
<a href="jvms-4.html#jvms-4.7.2-300-C.1" class="xref"
title="Table 4.7.2-A. Constant value attribute types">Table 4.7.2-A</a>.

<div id="jvms-4.7.2-300-C.1" class="table">

**Table 4.7.2-A. Constant value attribute types**

<div class="table-contents">

| Field Type                                | Entry Type         |
|-------------------------------------------|--------------------|
| `int`, `short`, `char`, `byte`, `boolean` | `CONSTANT_Integer` |
| `float`                                   | `CONSTANT_Float`   |
| `long`                                    | `CONSTANT_Long`    |
| `double`                                  | `CONSTANT_Double`  |
| `String`                                  | `CONSTANT_String`  |

</div>

</div>

  

</div>

</div>

<div id="jvms-4.7.3" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.3. The `Code` Attribute

</div>

</div>

</div>

The `Code` attribute is a variable-length attribute in the `attributes`
table of a `method_info` structure
(<a href="jvms-4.html#jvms-4.6" class="xref"
title="4.6. Methods">§4.6</a>). A `Code` attribute contains the Java
Virtual Machine instructions and auxiliary information for a method,
including an instance initialization method and a class or interface
initialization method (<a href="jvms-2.html#jvms-2.9.1" class="xref"
title="2.9.1. Instance Initialization Methods">§2.9.1</a>,
<a href="jvms-2.html#jvms-2.9.2" class="xref"
title="2.9.2. Class Initialization Methods">§2.9.2</a>).

If the method is either `native` or `abstract`, and is not a class or
interface initialization method, then its `method_info` structure must
not have a `Code` attribute in its `attributes` table. Otherwise, its
`method_info` structure must have exactly one `Code` attribute in its
`attributes` table.

The `Code` attribute has the following format:

``` screen
Code_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1 code[code_length];
    u2 exception_table_length;
    {   u2 start_pc;
        u2 end_pc;
        u2 handler_pc;
        u2 catch_type;
    } exception_table[exception_table_length];
    u2 attributes_count;
    attribute_info attributes[attributes_count];
}
```

The items of the `Code_attribute` structure are as follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the string "`Code`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item indicates the length of the
attribute, excluding the initial six bytes.

<span class="term">max_stack</span>  
The value of the `max_stack` item gives the maximum depth of the operand
stack of this method (<a href="jvms-2.html#jvms-2.6.2" class="xref"
title="2.6.2. Operand Stacks">§2.6.2</a>) at any point during execution
of the method.

<span class="term">max_locals</span>  
The value of the `max_locals` item gives the number of local variables
in the local variable array allocated upon invocation of this method
(<a href="jvms-2.html#jvms-2.6.1" class="xref"
title="2.6.1. Local Variables">§2.6.1</a>), including the local
variables used to pass parameters to the method on its invocation.

The greatest local variable index for a value of type `long` or `double`
is `max_locals - 2`. The greatest local variable index for a value of
any other type is `max_locals - 1`.

<span class="term">code_length</span>  
The value of the `code_length` item gives the number of bytes in the
`code` array for this method.

The value of `code_length` must be greater than zero (as the `code`
array must not be empty) and less than 65536.

<span class="term">code\[\]</span>  
The `code` array gives the actual bytes of Java Virtual Machine code
that implement the method.

When the `code` array is read into memory on a byte-addressable machine,
if the first byte of the array is aligned on a 4-byte boundary, the
<span class="emphasis">*tableswitch*</span> and
<span class="emphasis">*lookupswitch*</span> 32-bit offsets will be
4-byte aligned. (Refer to the descriptions of those instructions for
more information on the consequences of `code` array alignment.)

The detailed constraints on the contents of the `code` array are
extensive and are given in a separate section
(<a href="jvms-4.html#jvms-4.9" class="xref"
title="4.9. Constraints on Java Virtual Machine Code">§4.9</a>).

<span class="term">exception_table_length</span>  
The value of the `exception_table_length` item gives the number of
entries in the `exception_table` array.

<span class="term">exception_table\[\]</span>  
Each entry in the `exception_table` array describes one exception
handler in the `code` array. The order of the handlers in the
`exception_table` array is significant
(<a href="jvms-2.html#jvms-2.10" class="xref"
title="2.10. Exceptions">§2.10</a>).

Each `exception_table` entry contains the following four items:

<div class="variablelist">

<span class="term">start_pc, end_pc</span>  
The values of the two items `start_pc` and `end_pc` indicate the ranges
in the `code` array at which the exception handler is active. The value
of `start_pc` must be a valid index into the `code` array of the opcode
of an instruction. The value of `end_pc` either must be a valid index
into the `code` array of the opcode of an instruction or must be equal
to `code_length`, the length of the `code` array. The value of
`start_pc` must be less than the value of `end_pc`.

The `start_pc` is inclusive and `end_pc` is exclusive; that is, the
exception handler must be active while the program counter is within the
interval \[`start_pc`, `end_pc`).

The fact that `end_pc` is exclusive is a historical mistake in the
design of the Java Virtual Machine: if the Java Virtual Machine code for
a method is exactly 65535 bytes long and ends with an instruction that
is 1 byte long, then that instruction cannot be protected by an
exception handler. A compiler writer can work around this bug by
limiting the maximum size of the generated Java Virtual Machine code for
any method, instance initialization method, or static initializer (the
size of any code array) to 65534 bytes.

<span class="term">handler_pc</span>  
The value of the `handler_pc` item indicates the start of the exception
handler. The value of the item must be a valid index into the `code`
array and must be the index of the opcode of an instruction.

<span class="term">catch_type</span>  
If the value of the `catch_type` item is nonzero, it must be a valid
index into the `constant_pool` table. The `constant_pool` entry at that
index must be a `CONSTANT_Class_info` structure
(<a href="jvms-4.html#jvms-4.4.1" class="xref"
title="4.4.1. The CONSTANT_Class_info Structure">§4.4.1</a>)
representing a class of exceptions that this exception handler is
designated to catch. The exception handler will be called only if the
thrown exception is an instance of the given class or one of its
subclasses.

The verifier checks that the class is `Throwable` or a subclass of
`Throwable` (<a href="jvms-4.html#jvms-4.9.2" class="xref"
title="4.9.2. Structural Constraints">§4.9.2</a>).

If the value of the `catch_type` item is zero, this exception handler is
called for all exceptions.

This is used to implement `finally`
(<a href="jvms-3.html#jvms-3.13" class="xref"
title="3.13. Compiling finally">§3.13</a>).

</div>

<span class="term">attributes_count</span>  
The value of the `attributes_count` item indicates the number of
attributes of the `Code` attribute.

<span class="term">attributes\[\]</span>  
Each value of the `attributes` table must be an `attribute_info`
structure (<a href="jvms-4.html#jvms-4.7" class="xref"
title="4.7. Attributes">§4.7</a>).

A `Code` attribute can have any number of optional attributes associated
with it.

The attributes defined by this specification as appearing in the
`attributes` table of a `Code` attribute are listed in
<a href="jvms-4.html#jvms-4.7-320" class="xref"
title="Table 4.7-C. Predefined class file attributes (by location)">Table 4.7-C</a>.

The rules concerning attributes defined to appear in the `attributes`
table of a `Code` attribute are given in
<a href="jvms-4.html#jvms-4.7" class="xref"
title="4.7. Attributes">§4.7</a>.

The rules concerning non-predefined attributes in the `attributes` table
of a `Code` attribute are given in
<a href="jvms-4.html#jvms-4.7.1" class="xref"
title="4.7.1. Defining and Naming New Attributes">§4.7.1</a>.

</div>

</div>

<div id="jvms-4.7.4" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.4. The `StackMapTable` Attribute

</div>

</div>

</div>

The `StackMapTable` attribute is a variable-length attribute in the
`attributes` table of a `Code` attribute
(<a href="jvms-4.html#jvms-4.7.3" class="xref"
title="4.7.3. The Code Attribute">§4.7.3</a>). A `StackMapTable`
attribute is used during the process of verification by type checking
(<a href="jvms-4.html#jvms-4.10.1" class="xref"
title="4.10.1. Verification by Type Checking">§4.10.1</a>).

There may be at most one `StackMapTable` attribute in the `attributes`
table of a `Code` attribute.

In a `class` file whose version number is 50.0 or above, if a method's
`Code` attribute does not have a `StackMapTable` attribute, it has an
<span class="emphasis">*implicit stack map attribute*</span>
(<a href="jvms-4.html#jvms-4.10.1" class="xref"
title="4.10.1. Verification by Type Checking">§4.10.1</a>). This
implicit stack map attribute is equivalent to a `StackMapTable`
attribute with `number_of_entries` equal to zero.

The `StackMapTable` attribute has the following format:

``` screen
StackMapTable_attribute {
    u2              attribute_name_index;
    u4              attribute_length;
    u2              number_of_entries;
    stack_map_frame entries[number_of_entries];
}
```

The items of the `StackMapTable_attribute` structure are as follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the string "`StackMapTable`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item indicates the length of the
attribute, excluding the initial six bytes.

<span class="term">number_of_entries</span>  
The value of the `number_of_entries` item gives the number of
`stack_map_frame` entries in the `entries` table.

<span class="term">entries\[\]</span>  
Each entry in the `entries` table describes one stack map frame of the
method. The order of the stack map frames in the `entries` table is
significant.

</div>

A <span class="emphasis">*stack map frame*</span> specifies (either
explicitly or implicitly) the bytecode offset at which it applies, and
the verification types of local variables and operand stack entries for
that offset.

Each stack map frame described in the `entries` table relies on the
previous frame for some of its semantics. The first stack map frame of a
method is implicit, and computed from the method descriptor by the type
checker (<a href="jvms-4.html#jvms-4.10.1.5" class="xref"
title="4.10.1.5. Type Checking Methods">§4.10.1.5</a>). The
`stack_map_frame` structure at `entries[0]` therefore describes the
second stack map frame of the method.

The <span class="emphasis">*bytecode offset*</span> at which a stack map
frame applies is calculated by taking the value `offset_delta` specified
in the frame (either explicitly or implicitly), and adding
`offset_delta + 1` to the bytecode offset of the previous frame, unless
the previous frame is the initial frame of the method. In that case, the
bytecode offset at which the stack map frame applies is the value
`offset_delta` specified in the frame.

By using an offset delta rather than storing the actual bytecode offset,
we ensure, by definition, that stack map frames are in the correctly
sorted order. Furthermore, by consistently using the formula
`offset_delta + 1` for all explicit frames (as opposed to the implicit
first frame), we guarantee the absence of duplicates.

We say that an instruction in the bytecode has a
<span class="emphasis">*corresponding stack map frame*</span> if the
instruction starts at offset <span class="emphasis">*i*</span> in the
`code` array of a `Code` attribute, and the `Code` attribute has a
`StackMapTable` attribute whose `entries` array contains a stack map
frame that applies at bytecode offset <span class="emphasis">*i*</span>.

A <span class="emphasis">*verification type*</span> specifies the type
of either one or two locations, where a
<span class="emphasis">*location*</span> is either a single local
variable or a single operand stack entry. A verification type is
represented by a discriminated union, `verification_type_info`, that
consists of a one-byte tag, indicating which item of the union is in
use, followed by zero or more bytes, giving more information about the
tag.

``` screen
union verification_type_info {
    Top_variable_info;
    Integer_variable_info;
    Float_variable_info;
    Long_variable_info;
    Double_variable_info;
    Null_variable_info;
    UninitializedThis_variable_info;
    Object_variable_info;
    Uninitialized_variable_info;
}
```

A verification type that specifies one location in the local variable
array or in the operand stack is represented by the following items of
the `verification_type_info` union:

<div class="norm">

- The `Top_variable_info` item indicates that the local variable has the
  verification type `top`.

  ``` screen
  Top_variable_info {
      u1 tag = ITEM_Top; /* 0 */
  }
      
  ```

- The `Integer_variable_info` item indicates that the location has the
  verification type `int`.

  ``` screen
  Integer_variable_info {
      u1 tag = ITEM_Integer; /* 1 */
  }
      
  ```

- The `Float_variable_info` item indicates that the location has the
  verification type `float`.

  ``` screen
  Float_variable_info {
      u1 tag = ITEM_Float; /* 2 */
  }
      
  ```

- The `Null_variable_info` type indicates that the location has the
  verification type `null`.

  ``` screen
  Null_variable_info {
      u1 tag = ITEM_Null; /* 5 */
  }
      
  ```

- The `UninitializedThis_variable_info` item indicates that the location
  has the verification type `uninitializedThis`.

  ``` screen
  UninitializedThis_variable_info {
      u1 tag = ITEM_UninitializedThis; /* 6 */
  }
      
  ```

- The `Object_variable_info` item indicates that the location has the
  verification type which is the class represented by the
  `CONSTANT_Class_info` structure
  (<a href="jvms-4.html#jvms-4.4.1" class="xref"
  title="4.4.1. The CONSTANT_Class_info Structure">§4.4.1</a>) found in
  the `constant_pool` table at the index given by `cpool_index`.

  ``` screen
  Object_variable_info {
      u1 tag = ITEM_Object; /* 7 */
      u2 cpool_index;
  }
      
  ```

- The `Uninitialized_variable_info` item indicates that the location has
  the verification type `uninitialized(Offset)`. The `Offset` item
  indicates the offset, in the `code` array of the `Code` attribute that
  contains this `StackMapTable` attribute, of the
  <span class="emphasis">*new*</span> instruction
  (<a href="jvms-6.html#jvms-6.5.new" class="xref" title="new">§<span
  class="emphasis"><em>new</em></span></a>) that created the object
  being stored in the location.

  ``` screen
  Uninitialized_variable_info {
      u1 tag = ITEM_Uninitialized; /* 8 */
      u2 offset;
  }
      
  ```

</div>

A verification type that specifies two locations in the local variable
array or in the operand stack is represented by the following items of
the `verification_type_info` union:

<div class="norm">

- The `Long_variable_info` item indicates that the first of two
  locations has the verification type `long`.

  ``` screen
  Long_variable_info {
      u1 tag = ITEM_Long; /* 4 */
  }
      
  ```

- The `Double_variable_info` item indicates that the first of two
  locations has the verification type `double`.

  ``` screen
  Double_variable_info {
      u1 tag = ITEM_Double; /* 3 */
  }
      
  ```

- The `Long_variable_info` and `Double_variable_info` items indicate the
  verification type of the second of two locations as follows:

  <div class="norm">

  - If the first of the two locations is a local variable, then:

    <div class="norm">

    - It must not be the local variable with the highest index.

    - The next higher numbered local variable has the verification type
      `top`.

    </div>

  - If the first of the two locations is an operand stack entry, then:

    <div class="norm">

    - It must not be the topmost location of the operand stack.

    - The next location closer to the top of the operand stack has the
      verification type `top`.

    </div>

  </div>

</div>

A stack map frame is represented by a discriminated union,
`stack_map_frame`, which consists of a one-byte tag, indicating which
item of the union is in use, followed by zero or more bytes, giving more
information about the tag.

``` screen
union stack_map_frame {
    same_frame;
    same_locals_1_stack_item_frame;
    same_locals_1_stack_item_frame_extended;
    chop_frame;
    same_frame_extended;
    append_frame;
    full_frame;
}
```

The tag indicates the <span class="emphasis">*frame type*</span> of the
stack map frame:

<div class="norm">

- The frame type `same_frame` is represented by tags in the range
  \[0-63\]. This frame type indicates that the frame has exactly the
  same local variables as the previous frame and that the operand stack
  is empty. The `offset_delta` value for the frame is the value of the
  tag item, `frame_type`.

  ``` screen
  same_frame {
      u1 frame_type = SAME; /* 0-63 */
  }
      
  ```

- The frame type `same_locals_1_stack_item_frame` is represented by tags
  in the range \[64, 127\]. This frame type indicates that the frame has
  exactly the same local variables as the previous frame and that the
  operand stack has one entry. The `offset_delta` value for the frame is
  given by the formula `frame_type - 64`. The verification type of the
  one stack entry appears after the frame type.

  ``` screen
  same_locals_1_stack_item_frame {
      u1 frame_type = SAME_LOCALS_1_STACK_ITEM; /* 64-127 */
      verification_type_info stack[1];
  }
  ```

- Tags in the range \[128-246\] are reserved for future use.

- The frame type `same_locals_1_stack_item_frame_extended` is
  represented by the tag 247. This frame type indicates that the frame
  has exactly the same local variables as the previous frame and that
  the operand stack has one entry. The `offset_delta` value for the
  frame is given explicitly, unlike in the frame type
  `same_locals_1_stack_item_frame`. The verification type of the one
  stack entry appears after `offset_delta`.

  ``` screen
  same_locals_1_stack_item_frame_extended {
      u1 frame_type = SAME_LOCALS_1_STACK_ITEM_EXTENDED; /* 247 */
      u2 offset_delta;
      verification_type_info stack[1];
  }
      
  ```

- The frame type `chop_frame` is represented by tags in the range
  \[248-250\]. This frame type indicates that the frame has the same
  local variables as the previous frame except that the last
  <span class="emphasis">*k*</span> local variables are absent, and that
  the operand stack is empty. The value of
  <span class="emphasis">*k*</span> is given by the formula
  `251 - frame_type`. The `offset_delta` value for the frame is given
  explicitly.

  ``` screen
  chop_frame {
      u1 frame_type = CHOP; /* 248-250 */
      u2 offset_delta;
  }
      
  ```

  Assume the verification types of local variables in the previous frame
  are given by `locals`, an array structured as in the `full_frame`
  frame type. If `locals[M-1]` in the previous frame represented local
  variable <span class="type">X</span> and `locals[M]` represented local
  variable <span class="type">Y</span>, then the effect of removing one
  local variable is that `locals[M-1]` in the new frame represents local
  variable <span class="type">X</span> and `locals[M]` is undefined.

  It is an error if <span class="emphasis">*k*</span> is larger than the
  number of local variables in `locals` for the previous frame, that is,
  if the number of local variables in the new frame would be less than
  zero.

- The frame type `same_frame_extended` is represented by the tag 251.
  This frame type indicates that the frame has exactly the same local
  variables as the previous frame and that the operand stack is empty.
  The `offset_delta` value for the frame is given explicitly, unlike in
  the frame type `same_frame`.

  ``` screen
  same_frame_extended {
      u1 frame_type = SAME_FRAME_EXTENDED; /* 251 */
      u2 offset_delta;
  }
      
  ```

- The frame type `append_frame` is represented by tags in the range
  \[252-254\]. This frame type indicates that the frame has the same
  locals as the previous frame except that
  <span class="emphasis">*k*</span> additional locals are defined, and
  that the operand stack is empty. The value of
  <span class="emphasis">*k*</span> is given by the formula
  `frame_type - 251`. The `offset_delta` value for the frame is given
  explicitly.

  ``` screen
  append_frame {
      u1 frame_type = APPEND; /* 252-254 */
      u2 offset_delta;
      verification_type_info locals[frame_type - 251];
  }
      
  ```

  The 0th entry in `locals` represents the verification type of the
  first additional local variable. If `locals[M]` represents local
  variable `N`, then:

  <div class="norm">

  - `locals[M+1]` represents local variable `N+1` if `locals[M]` is one
    of `Top_variable_info`, `Integer_variable_info`,
    `Float_variable_info`, `Null_variable_info`,
    `UninitializedThis_variable_info`, `Object_variable_info`, or
    `Uninitialized_variable_info`; and

  - `locals[M+1]` represents local variable `N+2` if `locals[M]` is
    either `Long_variable_info` or `Double_variable_info`.

  </div>

  It is an error if, for any index <span class="emphasis">*i*</span>,
  `locals[`<span class="emphasis">*`i`*</span>`]` represents a local
  variable whose index is greater than the maximum number of local
  variables for the method.

- The frame type `full_frame` is represented by the tag 255. The
  `offset_delta` value for the frame is given explicitly.

  ``` screen
  full_frame {
      u1 frame_type = FULL_FRAME; /* 255 */
      u2 offset_delta;
      u2 number_of_locals;
      verification_type_info locals[number_of_locals];
      u2 number_of_stack_items;
      verification_type_info stack[number_of_stack_items];
  }
      
  ```

  The 0th entry in `locals` represents the verification type of local
  variable 0. If `locals[M]` represents local variable `N`, then:

  <div class="norm">

  - `locals[M+1]` represents local variable `N+1` if `locals[M]` is one
    of `Top_variable_info`, `Integer_variable_info`,
    `Float_variable_info`, `Null_variable_info`,
    `UninitializedThis_variable_info`, `Object_variable_info`, or
    `Uninitialized_variable_info`; and

  - `locals[M+1]` represents local variable `N+2` if `locals[M]` is
    either `Long_variable_info` or `Double_variable_info`.

  </div>

  It is an error if, for any index <span class="emphasis">*i*</span>,
  `locals[`<span class="emphasis">*`i`*</span>`]` represents a local
  variable whose index is greater than the maximum number of local
  variables for the method.

  The 0th entry in `stack` represents the verification type of the
  bottom of the operand stack, and subsequent entries in `stack`
  represent the verification types of stack entries closer to the top of
  the operand stack. We refer to the bottom of the operand stack as
  stack entry 0, and to subsequent entries of the operand stack as stack
  entry 1, 2, etc. If `stack[M]` represents stack entry `N`, then:

  <div class="norm">

  - `stack[M+1]` represents stack entry `N+1` if `stack[M]` is one of
    `Top_variable_info`, `Integer_variable_info`, `Float_variable_info`,
    `Null_variable_info`, `UninitializedThis_variable_info`,
    `Object_variable_info`, or `Uninitialized_variable_info`; and

  - `stack[M+1]` represents stack entry `N+2` if `stack[M]` is either
    `Long_variable_info` or `Double_variable_info`.

  </div>

  It is an error if, for any index <span class="emphasis">*i*</span>,
  `stack[`<span class="emphasis">*`i`*</span>`]` represents a stack
  entry whose index is greater than the maximum operand stack size for
  the method.

</div>

</div>

<div id="jvms-4.7.5" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.5. The `Exceptions` Attribute

</div>

</div>

</div>

The `Exceptions` attribute is a variable-length attribute in the
`attributes` table of a `method_info` structure
(<a href="jvms-4.html#jvms-4.6" class="xref"
title="4.6. Methods">§4.6</a>). The `Exceptions` attribute indicates
which checked exceptions a method may throw.

There may be at most one `Exceptions` attribute in the `attributes`
table of a `method_info` structure.

The `Exceptions` attribute has the following format:

``` screen
Exceptions_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 number_of_exceptions;
    u2 exception_index_table[number_of_exceptions];
}
```

The items of the `Exceptions_attribute` structure are as follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be the `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the string "`Exceptions`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item indicates the length of the
attribute, excluding the initial six bytes.

<span class="term">number_of_exceptions</span>  
The value of the `number_of_exceptions` item indicates the number of
entries in the `exception_index_table`.

<span class="term">exception_index_table\[\]</span>  
Each value in the `exception_index_table` array must be a valid index
into the `constant_pool` table. The `constant_pool` entry at that index
must be a `CONSTANT_Class_info` structure
(<a href="jvms-4.html#jvms-4.4.1" class="xref"
title="4.4.1. The CONSTANT_Class_info Structure">§4.4.1</a>)
representing a class type that this method is declared to throw.

</div>

A method should throw an exception only if at least one of the following
three criteria is met:

<div class="note">

- The exception is an instance of `RuntimeException` or one of its
  subclasses.

- The exception is an instance of `Error` or one of its subclasses.

- The exception is an instance of one of the exception classes specified
  in the `exception_index_table` just described, or one of their
  subclasses.

</div>

These requirements are not enforced in the Java Virtual Machine; they
are enforced only at compile time.

</div>

<div id="jvms-4.7.6" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.6. The `InnerClasses` Attribute

</div>

</div>

</div>

The `InnerClasses` attribute is a variable-length attribute in the
`attributes` table of a `ClassFile` structure
(<a href="jvms-4.html#jvms-4.1" class="xref"
title="4.1. The ClassFile Structure">§4.1</a>).

If the constant pool of a class or interface <span class="type">C</span>
contains at least one `CONSTANT_Class_info` entry
(<a href="jvms-4.html#jvms-4.4.1" class="xref"
title="4.4.1. The CONSTANT_Class_info Structure">§4.4.1</a>) which
represents a class or interface that is not a member of a package, then
there must be exactly one `InnerClasses` attribute in the `attributes`
table of the `ClassFile` structure for <span class="type">C</span>.

The `InnerClasses` attribute has the following format:

``` screen
InnerClasses_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 number_of_classes;
    {   u2 inner_class_info_index;
        u2 outer_class_info_index;
        u2 inner_name_index;
        u2 inner_class_access_flags;
    } classes[number_of_classes];
}
```

The items of the `InnerClasses_attribute` structure are as follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the string "`InnerClasses`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item indicates the length of the
attribute, excluding the initial six bytes.

<span class="term">number_of_classes</span>  
The value of the `number_of_classes` item indicates the number of
entries in the `classes` array.

<span class="term">classes\[\]</span>  
Every `CONSTANT_Class_info` entry in the `constant_pool` table which
represents a class or interface <span class="type">C</span> that is not
a package member must have exactly one corresponding entry in the
`classes` array.

If a class or interface has members that are classes or interfaces, its
`constant_pool` table (and hence its `InnerClasses` attribute) must
refer to each such member (JLS §13.1), even if that member is not
otherwise mentioned by the class.

In addition, the `constant_pool` table of every nested class and nested
interface must refer to its enclosing class, so altogether, every nested
class and nested interface will have `InnerClasses` information for each
enclosing class and for each of its own nested classes and interfaces.

Each entry in the `classes` array contains the following four items:

<div class="variablelist">

<span class="term">inner_class_info_index</span>  
The value of the `inner_class_info_index` item must be a valid index
into the `constant_pool` table. The `constant_pool` entry at that index
must be a `CONSTANT_Class_info` structure representing
<span class="type">C</span>.

<span class="term">outer_class_info_index</span>  
If <span class="type">C</span> is not a member of a class or an
interface - that is, if <span class="type">C</span> is a top-level class
or interface (JLS §7.6) or a local class (JLS §14.3) or an anonymous
class (JLS §15.9.5) - then the value of the `outer_class_info_index`
item must be zero.

Otherwise, the value of the `outer_class_info_index` item must be a
valid index into the `constant_pool` table, and the entry at that index
must be a `CONSTANT_Class_info` structure representing the class or
interface of which <span class="type">C</span> is a member. The value of
the `outer_class_info_index` item must not equal the the value of the
`inner_class_info_index` item.

<span class="term">inner_name_index</span>  
If <span class="type">C</span> is anonymous (JLS §15.9.5), the value of
the `inner_name_index` item must be zero.

Otherwise, the value of the `inner_name_index` item must be a valid
index into the `constant_pool` table, and the entry at that index must
be a `CONSTANT_Utf8_info` structure that represents the original simple
name of <span class="type">C</span>, as given in the source code from
which this `class` file was compiled.

<span class="term">inner_class_access_flags</span>  
The value of the `inner_class_access_flags` item is a mask of flags used
to denote access permissions to and properties of class or interface
<span class="type">C</span> as declared in the source code from which
this `class` file was compiled. It is used by a compiler to recover the
original information when source code is not available. The flags are
specified in <a href="jvms-4.html#jvms-4.7.6-300-D.1-D.1" class="xref"
title="Table 4.7.6-A. Nested class access and property flags">Table 4.7.6-A</a>.

<div id="jvms-4.7.6-300-D.1-D.1" class="table">

**Table 4.7.6-A. Nested class access and property flags**

<div class="table-contents">

| Flag Name | Value | Interpretation |
|----|----|----|
| `ACC_PUBLIC` | 0x0001 | Marked or implicitly `public` in source. |
| `ACC_PRIVATE` | 0x0002 | Marked `private` in source. |
| `ACC_PROTECTED` | 0x0004 | Marked `protected` in source. |
| `ACC_STATIC` | 0x0008 | Marked or implicitly `static` in source. |
| `ACC_FINAL` | 0x0010 | Marked or implicitly `final` in source. |
| `ACC_INTERFACE` | 0x0200 | Was an `interface` in source. |
| `ACC_ABSTRACT` | 0x0400 | Marked or implicitly `abstract` in source. |
| `ACC_SYNTHETIC` | 0x1000 | Declared synthetic; not present in the source code. |
| `ACC_ANNOTATION` | 0x2000 | Declared as an annotation interface. |
| `ACC_ENUM` | 0x4000 | Declared as an `enum` class. |

</div>

</div>

  

All bits of the `inner_class_access_flags` item not assigned in
<a href="jvms-4.html#jvms-4.7.6-300-D.1-D.1" class="xref"
title="Table 4.7.6-A. Nested class access and property flags">Table 4.7.6-A</a>
are reserved for future use. They should be set to zero in generated
`class` files and should be ignored by Java Virtual Machine
implementations.

</div>

If a `class` file has a version number that is 51.0 or above, and has an
`InnerClasses` attribute in its `attributes` table, then for all entries
in the `classes` array of the `InnerClasses` attribute, the value of the
`outer_class_info_index` item must be zero if the value of the
`inner_name_index` item is zero.

</div>

Oracle's Java Virtual Machine implementation does not check the
consistency of an `InnerClasses` attribute against a `class` file
representing a class or interface referenced by the attribute.

</div>

<div id="jvms-4.7.7" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.7. The `EnclosingMethod` Attribute

</div>

</div>

</div>

The `EnclosingMethod` attribute is a fixed-length attribute in the
`attributes` table of a `ClassFile` structure
(<a href="jvms-4.html#jvms-4.1" class="xref"
title="4.1. The ClassFile Structure">§4.1</a>). A class must have an
`EnclosingMethod` attribute if and only if it represents a local class
or an anonymous class (JLS §14.3, JLS §15.9.5).

There may be at most one `EnclosingMethod` attribute in the `attributes`
table of a `ClassFile` structure.

The `EnclosingMethod` attribute has the following format:

``` screen
EnclosingMethod_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 class_index;
    u2 method_index;
}
```

The items of the `EnclosingMethod_attribute` structure are as follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the string "`EnclosingMethod`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item must be four.

<span class="term">class_index</span>  
The value of the `class_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Class_info` structure
(<a href="jvms-4.html#jvms-4.4.1" class="xref"
title="4.4.1. The CONSTANT_Class_info Structure">§4.4.1</a>)
representing the innermost class that encloses the declaration of the
current class.

<span class="term">method_index</span>  
If the current class is not immediately enclosed by a method or
constructor, then the value of the `method_index` item must be zero.

In particular, `method_index` must be zero if the current class was
immediately enclosed in source code by an instance initializer, static
initializer, instance variable initializer, or class variable
initializer. (The first two concern both local classes and anonymous
classes, while the last two concern anonymous classes declared on the
right hand side of a field assignment.)

Otherwise, the value of the `method_index` item must be a valid index
into the `constant_pool` table. The `constant_pool` entry at that index
must be a `CONSTANT_NameAndType_info` structure
(<a href="jvms-4.html#jvms-4.4.6" class="xref"
title="4.4.6. The CONSTANT_NameAndType_info Structure">§4.4.6</a>)
representing the name and type of a method in the class referenced by
the `class_index` attribute above.

It is the responsibility of a Java compiler to ensure that the method
identified via the `method_index` is indeed the closest lexically
enclosing method of the class that contains this `EnclosingMethod`
attribute.

</div>

</div>

<div id="jvms-4.7.8" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.8. The `Synthetic` Attribute

</div>

</div>

</div>

The `Synthetic` attribute is a fixed-length attribute in the
`attributes` table of a `ClassFile`, `field_info`, or `method_info`
structure (<a href="jvms-4.html#jvms-4.1" class="xref"
title="4.1. The ClassFile Structure">§4.1</a>,
<a href="jvms-4.html#jvms-4.5" class="xref" title="4.5. Fields">§4.5</a>,
<a href="jvms-4.html#jvms-4.6" class="xref"
title="4.6. Methods">§4.6</a>). A class member that does not appear in
the source code must be marked using a `Synthetic` attribute, or else it
must have its `ACC_SYNTHETIC` flag set. The only exceptions to this
requirement are compiler-generated members which are not considered
implementation artifacts, namely:

<div class="norm">

- an instance initialization method representing a default constructor
  of the Java programming language
  (<a href="jvms-2.html#jvms-2.9.1" class="xref"
  title="2.9.1. Instance Initialization Methods">§2.9.1</a>)

- a class or interface initialization method
  (<a href="jvms-2.html#jvms-2.9.2" class="xref"
  title="2.9.2. Class Initialization Methods">§2.9.2</a>)

- the implicitly declared members of enum and record classes (JLS
  §8.9.3, JLS §8.10.3)

</div>

The `Synthetic` attribute was introduced in JDK 1.1 to support nested
classes and interfaces.

It is a limitation of the `class` file format that only formal
parameters and modules can be flagged as `ACC_MANDATED`
(<a href="jvms-4.html#jvms-4.7.24" class="xref"
title="4.7.24. The MethodParameters Attribute">§4.7.24</a>,
<a href="jvms-4.html#jvms-4.7.25" class="xref"
title="4.7.25. The Module Attribute">§4.7.25</a>) to indicate that,
despite being compiler-generated, they are not considered implementation
artifacts. There is no way to flag other compiler-generated constructs
so that they too are not considered implementation artifacts (JLS
§13.1). This limitation means that reflective APIs of the Java SE
Platform may not accurately indicate the "mandated" status of such
constructs.

The `Synthetic` attribute has the following format:

``` screen
Synthetic_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
}
```

The items of the `Synthetic_attribute` structure are as follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the string "`Synthetic`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item must be zero.

</div>

</div>

<div id="jvms-4.7.9" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.9. The `Signature` Attribute

</div>

</div>

</div>

The `Signature` attribute is a fixed-length attribute in the
`attributes` table of a `ClassFile`, `field_info`, `method_info`, or
`record_component_info` structure
(<a href="jvms-4.html#jvms-4.1" class="xref"
title="4.1. The ClassFile Structure">§4.1</a>,
<a href="jvms-4.html#jvms-4.5" class="xref" title="4.5. Fields">§4.5</a>,
<a href="jvms-4.html#jvms-4.6" class="xref"
title="4.6. Methods">§4.6</a>,
<a href="jvms-4.html#jvms-4.7.30" class="xref"
title="4.7.30. The Record Attribute">§4.7.30</a>). A `Signature`
attribute stores a signature
(<a href="jvms-4.html#jvms-4.7.9.1" class="xref"
title="4.7.9.1. Signatures">§4.7.9.1</a>) for a class, interface,
constructor, method, field, or record component whose declaration in the
Java programming language uses type variables or parameterized types.
See *The Java Language Specification, Java SE 26 Edition* for details
about these constructs.

There may be at most one `Signature` attribute in the `attributes` table
of a `ClassFile`, `field_info`, `method_info`, or
`record_component_info` structure.

The `Signature` attribute has the following format:

``` screen
Signature_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 signature_index;
}
```

The items of the `Signature_attribute` structure are as follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the string "`Signature`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item must be two.

<span class="term">signature_index</span>  
The value of the `signature_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
a class signature if this `Signature` attribute is an attribute of a
`ClassFile` structure; a method signature if this `Signature` attribute
is an attribute of a `method_info` structure; or a field signature
otherwise.

</div>

Oracle's Java Virtual Machine implementation does not check the
well-formedness of `Signature` attributes during class loading or
linking. Instead, `Signature` attributes are checked by methods of the
Java SE Platform class libraries which expose generic signatures of
classes, interfaces, constructors, methods, and fields. Examples include
`getGenericSuperclass` in `Class` and `toGenericString` in
`java.lang.reflect.Executable`.

<div id="jvms-4.7.9.1" class="section">

<div class="titlepage">

<div>

<div>

#### 4.7.9.1. Signatures

</div>

</div>

</div>

<span class="emphasis">*Signatures*</span> encode declarations written
in the Java programming language that use types outside the type system
of the Java Virtual Machine. They support reflection and debugging, as
well as compilation when only `class` files are available.

A Java compiler must emit a signature for any class, interface,
constructor, method, field, or record component whose declaration uses
type variables or parameterized types. Specifically, a Java compiler
must emit:

<div class="norm">

- A class signature for any class or interface declaration which is
  either generic, or has a parameterized type as a superclass or
  superinterface, or both.

- A method signature for any method or constructor declaration which is
  either generic, or has a type variable or parameterized type as the
  return type or a formal parameter type, or has a type variable in a
  `throws` clause, or any combination thereof.

  If the `throws` clause of a method or constructor declaration does not
  involve type variables, then a compiler may treat the declaration as
  having no `throws` clause for the purpose of emitting a method
  signature.

- A field signature for any field, formal parameter, local variable, or
  record component declaration whose type uses a type variable or a
  parameterized type.

</div>

Signatures are specified using a grammar which follows the notation of
<a href="jvms-4.html#jvms-4.3.1" class="xref"
title="4.3.1. Grammar Notation">§4.3.1</a>. In addition to that
notation:

<div class="norm">

- The syntax <span class="emphasis">*\[x\]*</span> on the right-hand
  side of a production denotes zero or one occurrences of
  <span class="emphasis">*x*</span>. That is,
  <span class="emphasis">*x*</span> is an
  <span class="emphasis">*optional symbol*</span>. The alternative which
  contains the optional symbol actually defines two alternatives: one
  that omits the optional symbol and one that includes it.

- A very long right-hand side may be continued on a second line by
  clearly indenting the second line.

</div>

The grammar includes the terminal symbol
<span class="emphasis">*Identifier*</span> to denote the name of a type,
field, method, formal parameter, local variable, or type variable, as
generated by a Java compiler. Such a name must not contain any of the
ASCII characters `.` `;` `[` `/` `<` `>` `:` (that is, the characters
forbidden in method names (<a href="jvms-4.html#jvms-4.2.2" class="xref"
title="4.2.2. Unqualified Names">§4.2.2</a>) and also colon) but may
contain characters that must not appear in an identifier in the Java
programming language (JLS §3.8).

Signatures rely on a hierarchy of nonterminals known as
<span class="emphasis">*type signatures*</span>:

<div class="norm">

- A <span class="emphasis">*Java type signature*</span> represents
  either a reference type or a primitive type of the Java programming
  language.

  <div id="jvms-4.7.9.1-300-A.1" class="productionset">

  <div id="jvms-JavaTypeSignature" class="production">

  <div class="lhs">

  JavaTypeSignature:

  </div>

  <div class="rhs">

  [ReferenceTypeSignature](jvms-4.html#jvms-ReferenceTypeSignature "ReferenceTypeSignature")  
  [BaseType](jvms-4.html#jvms-BaseType "BaseType")

  </div>

  </div>

  </div>

  The following production from
  <a href="jvms-4.html#jvms-4.3.2" class="xref"
  title="4.3.2. Field Descriptors">§4.3.2</a> is repeated here for
  convenience:

  <div id="d5e7743" class="productionset">

  <div class="productionrecap-note">

  <div class="production">

  <div class="lhs">

  BaseType:

  </div>

  <div class="rhs">

  (one of)  
  `B` `C` `D` `F` `I` `J` `S` `Z`

  </div>

  </div>

  </div>

  </div>

- A <span class="emphasis">*reference type signature*</span> represents
  a reference type of the Java programming language, that is, a class or
  interface type, a type variable, or an array type.

  A <span class="emphasis">*class type signature*</span> represents a
  (possibly parameterized) class or interface type. A class type
  signature must be formulated such that it can be reliably mapped to
  the binary name of the class it denotes, in internal form
  (<a href="jvms-4.html#jvms-4.2.1" class="xref"
  title="4.2.1. Binary Class and Interface Names">§4.2.1</a>), by
  erasing any type arguments and converting each `.` character to a `$`
  character.

  A <span class="emphasis">*type variable signature*</span> represents a
  type variable.

  An <span class="emphasis">*array type signature*</span> represents one
  dimension of an array type.

  <div id="jvms-4.7.9.1-300-B.4" class="productionset">

  <div id="jvms-ReferenceTypeSignature" class="production">

  <div class="lhs">

  ReferenceTypeSignature:

  </div>

  <div class="rhs">

  [ClassTypeSignature](jvms-4.html#jvms-ClassTypeSignature "ClassTypeSignature")  
  [TypeVariableSignature](jvms-4.html#jvms-TypeVariableSignature "TypeVariableSignature")  
  [ArrayTypeSignature](jvms-4.html#jvms-ArrayTypeSignature "ArrayTypeSignature")

  </div>

  </div>

  <div id="jvms-ClassTypeSignature" class="production">

  <div class="lhs">

  ClassTypeSignature:

  </div>

  <div class="rhs">

  `L`
  \[[PackageSpecifier](jvms-4.html#jvms-PackageSpecifier "PackageSpecifier")\]
  [SimpleClassTypeSignature](jvms-4.html#jvms-SimpleClassTypeSignature "SimpleClassTypeSignature")
  {[ClassTypeSignatureSuffix](jvms-4.html#jvms-ClassTypeSignatureSuffix "ClassTypeSignatureSuffix")}
  `;`

  </div>

  </div>

  <div id="jvms-PackageSpecifier" class="production">

  <div class="lhs">

  PackageSpecifier:

  </div>

  <div class="rhs">

  Identifier `/`
  {[PackageSpecifier](jvms-4.html#jvms-PackageSpecifier "PackageSpecifier")}

  </div>

  </div>

  <div id="jvms-SimpleClassTypeSignature" class="production">

  <div class="lhs">

  SimpleClassTypeSignature:

  </div>

  <div class="rhs">

  Identifier
  \[[TypeArguments](jvms-4.html#jvms-TypeArguments "TypeArguments")\]

  </div>

  </div>

  <div id="jvms-TypeArguments" class="production">

  <div class="lhs">

  TypeArguments:

  </div>

  <div class="rhs">

  `<` [TypeArgument](jvms-4.html#jvms-TypeArgument "TypeArgument")
  {[TypeArgument](jvms-4.html#jvms-TypeArgument "TypeArgument")} `>`

  </div>

  </div>

  <div id="jvms-TypeArgument" class="production">

  <div class="lhs">

  TypeArgument:

  </div>

  <div class="rhs">

  \[[WildcardIndicator](jvms-4.html#jvms-WildcardIndicator "WildcardIndicator")\]
  [ReferenceTypeSignature](jvms-4.html#jvms-ReferenceTypeSignature "ReferenceTypeSignature")  
  `*`

  </div>

  </div>

  <div id="jvms-WildcardIndicator" class="production">

  <div class="lhs">

  WildcardIndicator:

  </div>

  <div class="rhs">

  `+`  
  `-`

  </div>

  </div>

  <div id="jvms-ClassTypeSignatureSuffix" class="production">

  <div class="lhs">

  ClassTypeSignatureSuffix:

  </div>

  <div class="rhs">

  `.`
  [SimpleClassTypeSignature](jvms-4.html#jvms-SimpleClassTypeSignature "SimpleClassTypeSignature")

  </div>

  </div>

  <div id="jvms-TypeVariableSignature" class="production">

  <div class="lhs">

  TypeVariableSignature:

  </div>

  <div class="rhs">

  `T` Identifier `;`

  </div>

  </div>

  <div id="jvms-ArrayTypeSignature" class="production">

  <div class="lhs">

  ArrayTypeSignature:

  </div>

  <div class="rhs">

  `[`
  [JavaTypeSignature](jvms-4.html#jvms-JavaTypeSignature "JavaTypeSignature")

  </div>

  </div>

  </div>

</div>

A <span class="emphasis">*class signature*</span> encodes type
information about a (possibly generic) class or interface declaration.
It describes any type parameters of the class or interface, and lists
its (possibly parameterized) direct superclass and direct
superinterfaces, if any. A type parameter is described by its name,
followed by any class bound and interface bounds.

<div id="jvms-4.7.9.1-410" class="productionset">

<div id="jvms-ClassSignature" class="production">

<div class="lhs">

ClassSignature:

</div>

<div class="rhs">

\[[TypeParameters](jvms-4.html#jvms-TypeParameters "TypeParameters")\]
[SuperclassSignature](jvms-4.html#jvms-SuperclassSignature "SuperclassSignature")
{[SuperinterfaceSignature](jvms-4.html#jvms-SuperinterfaceSignature "SuperinterfaceSignature")}

</div>

</div>

<div id="jvms-TypeParameters" class="production">

<div class="lhs">

TypeParameters:

</div>

<div class="rhs">

`<` [TypeParameter](jvms-4.html#jvms-TypeParameter "TypeParameter")
{[TypeParameter](jvms-4.html#jvms-TypeParameter "TypeParameter")} `>`

</div>

</div>

<div id="jvms-TypeParameter" class="production">

<div class="lhs">

TypeParameter:

</div>

<div class="rhs">

Identifier [ClassBound](jvms-4.html#jvms-ClassBound "ClassBound")
{[InterfaceBound](jvms-4.html#jvms-InterfaceBound "InterfaceBound")}

</div>

</div>

<div id="jvms-ClassBound" class="production">

<div class="lhs">

ClassBound:

</div>

<div class="rhs">

`:`
\[[ReferenceTypeSignature](jvms-4.html#jvms-ReferenceTypeSignature "ReferenceTypeSignature")\]

</div>

</div>

<div id="jvms-InterfaceBound" class="production">

<div class="lhs">

InterfaceBound:

</div>

<div class="rhs">

`:`
[ReferenceTypeSignature](jvms-4.html#jvms-ReferenceTypeSignature "ReferenceTypeSignature")

</div>

</div>

<div id="jvms-SuperclassSignature" class="production">

<div class="lhs">

SuperclassSignature:

</div>

<div class="rhs">

[ClassTypeSignature](jvms-4.html#jvms-ClassTypeSignature "ClassTypeSignature")

</div>

</div>

<div id="jvms-SuperinterfaceSignature" class="production">

<div class="lhs">

SuperinterfaceSignature:

</div>

<div class="rhs">

[ClassTypeSignature](jvms-4.html#jvms-ClassTypeSignature "ClassTypeSignature")

</div>

</div>

</div>

A <span class="emphasis">*method signature*</span> encodes type
information about a (possibly generic) method declaration. It describes
any type parameters of the method; the (possibly parameterized) types of
any formal parameters; the (possibly parameterized) return type, if any;
and the types of any exceptions declared in the method's `throws`
clause.

<div id="jvms-4.7.9.1-510" class="productionset">

<div id="jvms-MethodSignature" class="production">

<div class="lhs">

MethodSignature:

</div>

<div class="rhs">

\[[TypeParameters](jvms-4.html#jvms-TypeParameters "TypeParameters")\]
`(`
{[JavaTypeSignature](jvms-4.html#jvms-JavaTypeSignature "JavaTypeSignature")}
`)` [Result](jvms-4.html#jvms-Result "Result")
{[ThrowsSignature](jvms-4.html#jvms-ThrowsSignature "ThrowsSignature")}

</div>

</div>

<div id="jvms-Result" class="production">

<div class="lhs">

Result:

</div>

<div class="rhs">

[JavaTypeSignature](jvms-4.html#jvms-JavaTypeSignature "JavaTypeSignature")  
[VoidDescriptor](jvms-4.html#jvms-VoidDescriptor "VoidDescriptor")

</div>

</div>

<div id="jvms-ThrowsSignature" class="production">

<div class="lhs">

ThrowsSignature:

</div>

<div class="rhs">

`^`
[ClassTypeSignature](jvms-4.html#jvms-ClassTypeSignature "ClassTypeSignature")  
`^`
[TypeVariableSignature](jvms-4.html#jvms-TypeVariableSignature "TypeVariableSignature")

</div>

</div>

</div>

The following production from
<a href="jvms-4.html#jvms-4.3.3" class="xref"
title="4.3.3. Method Descriptors">§4.3.3</a> is repeated here for
convenience:

<div id="d5e7881" class="productionset">

<div class="productionrecap-note">

<div class="production">

<div class="lhs">

VoidDescriptor:

</div>

<div class="rhs">

`V`

</div>

</div>

</div>

</div>

A method signature encoded by the `Signature` attribute may not
correspond exactly to the method descriptor in the `method_info`
structure (<a href="jvms-4.html#jvms-4.3.3" class="xref"
title="4.3.3. Method Descriptors">§4.3.3</a>). In particular, there is
no assurance that the number of formal parameter types in the method
signature is the same as the number of parameter descriptors in the
method descriptor. The numbers are the same for most methods, but
certain constructors in the Java programming language have an implicitly
declared parameter which a compiler represents with a parameter
descriptor but may omit from the method signature. See the note in
<a href="jvms-4.html#jvms-4.7.18" class="xref"
title="4.7.18. The RuntimeVisibleParameterAnnotations Attribute">§4.7.18</a>
for a similar situation involving parameter annotations.

A <span class="emphasis">*field signature*</span> encodes the (possibly
parameterized) type of a field, formal parameter, local variable, or
record component declaration.

<div id="jvms-4.7.9.1-610" class="productionset">

<div id="jvms-FieldSignature" class="production">

<div class="lhs">

FieldSignature:

</div>

<div class="rhs">

[ReferenceTypeSignature](jvms-4.html#jvms-ReferenceTypeSignature "ReferenceTypeSignature")

</div>

</div>

</div>

</div>

</div>

<div id="jvms-4.7.10" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.10. The `SourceFile` Attribute

</div>

</div>

</div>

The `SourceFile` attribute is an optional fixed-length attribute in the
`attributes` table of a `ClassFile` structure
(<a href="jvms-4.html#jvms-4.1" class="xref"
title="4.1. The ClassFile Structure">§4.1</a>).

There may be at most one `SourceFile` attribute in the `attributes`
table of a `ClassFile` structure.

The `SourceFile` attribute has the following format:

``` screen
SourceFile_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 sourcefile_index;
}
```

The items of the `SourceFile_attribute` structure are as follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the string "`SourceFile`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item must be two.

<span class="term">sourcefile_index</span>  
The value of the `sourcefile_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Utf8_info` structure representing a string.

The string referenced by the `sourcefile_index` item will be interpreted
as indicating the name of the source file from which this `class` file
was compiled. It will not be interpreted as indicating the name of a
directory containing the file or an absolute path name for the file;
such platform-specific additional information must be supplied by the
run-time interpreter or development tool at the time the file name is
actually used.

</div>

</div>

<div id="jvms-4.7.11" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.11. The `SourceDebugExtension` Attribute

</div>

</div>

</div>

The `SourceDebugExtension` attribute is an optional attribute in the
`attributes` table of a `ClassFile` structure
(<a href="jvms-4.html#jvms-4.1" class="xref"
title="4.1. The ClassFile Structure">§4.1</a>).

There may be at most one `SourceDebugExtension` attribute in the
`attributes` table of a `ClassFile` structure.

The `SourceDebugExtension` attribute has the following format:

``` screen
SourceDebugExtension_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u1 debug_extension[attribute_length];
}
```

The items of the `SourceDebugExtension_attribute` structure are as
follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the string "`SourceDebugExtension`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item indicates the length of the
attribute, excluding the initial six bytes.

<span class="term">debug_extension\[\]</span>  
The `debug_extension` array holds extended debugging information which
has no semantic effect on the Java Virtual Machine. The information is
represented using a modified UTF-8 string
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) with no
terminating zero byte.

Note that the `debug_extension` array may denote a string longer than
that which can be represented with an instance of class `String`.

</div>

</div>

<div id="jvms-4.7.12" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.12. The `LineNumberTable` Attribute

</div>

</div>

</div>

The `LineNumberTable` attribute is an optional variable-length attribute
in the `attributes` table of a `Code` attribute
(<a href="jvms-4.html#jvms-4.7.3" class="xref"
title="4.7.3. The Code Attribute">§4.7.3</a>). It may be used by
debuggers to determine which part of the `code` array corresponds to a
given line number in the original source file.

If multiple `LineNumberTable` attributes are present in the `attributes`
table of a `Code` attribute, then they may appear in any order.

There may be more than one `LineNumberTable` attribute
<span class="emphasis">*per line of a source file*</span> in the
`attributes` table of a `Code` attribute. That is, `LineNumberTable`
attributes may together represent a given line of a source file, and
need not be one-to-one with source lines.

The `LineNumberTable` attribute has the following format:

``` screen
LineNumberTable_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 line_number_table_length;
    {   u2 start_pc;
        u2 line_number;
    } line_number_table[line_number_table_length];
}
```

The items of the `LineNumberTable_attribute` structure are as follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the string "`LineNumberTable`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item indicates the length of the
attribute, excluding the initial six bytes.

<span class="term">line_number_table_length</span>  
The value of the `line_number_table_length` item indicates the number of
entries in the `line_number_table` array.

<span class="term">line_number_table\[\]</span>  
Each entry in the `line_number_table` array indicates that the line
number in the original source file changes at a given point in the
`code` array. Each `line_number_table` entry must contain the following
two items:

<div class="variablelist">

<span class="term">start_pc</span>  
The value of the `start_pc` item must be a valid index into the `code`
array of this `Code` attribute. The item indicates the index into the
`code` array at which the code for a new line in the original source
file begins.

<span class="term">line_number</span>  
The value of the `line_number` item gives the corresponding line number
in the original source file.

</div>

</div>

</div>

<div id="jvms-4.7.13" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.13. The `LocalVariableTable` Attribute

</div>

</div>

</div>

The `LocalVariableTable` attribute is an optional variable-length
attribute in the `attributes` table of a `Code` attribute
(<a href="jvms-4.html#jvms-4.7.3" class="xref"
title="4.7.3. The Code Attribute">§4.7.3</a>). It may be used by
debuggers to determine the value of a given local variable during the
execution of a method.

If multiple `LocalVariableTable` attributes are present in the
`attributes` table of a `Code` attribute, then they may appear in any
order.

There may be no more than one `LocalVariableTable` attribute
<span class="emphasis">*per local variable*</span> in the `attributes`
table of a `Code` attribute.

The `LocalVariableTable` attribute has the following format:

``` screen
LocalVariableTable_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 local_variable_table_length;
    {   u2 start_pc;
        u2 length;
        u2 name_index;
        u2 descriptor_index;
        u2 index;
    } local_variable_table[local_variable_table_length];
}
```

The items of the `LocalVariableTable_attribute` structure are as
follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the string "`LocalVariableTable`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item indicates the length of the
attribute, excluding the initial six bytes.

<span class="term">local_variable_table_length</span>  
The value of the `local_variable_table_length` item indicates the number
of entries in the `local_variable_table` array.

<span class="term">local_variable_table\[\]</span>  
Each entry in the `local_variable_table` array indicates a range of
`code` array offsets within which a local variable has a value, and
indicates the index into the local variable array of the current frame
at which that local variable can be found. Each entry must contain the
following five items:

<div class="variablelist">

<span class="term">start_pc, length</span>  
The value of the `start_pc` item must be a valid index into the `code`
array of this `Code` attribute and must be the index of the opcode of an
instruction.

The value of `start_pc + length` must either be a valid index into the
`code` array of this `Code` attribute and be the index of the opcode of
an instruction, or it must be the first index beyond the end of that
`code` array.

The `start_pc` and `length` items indicate that the given local variable
has a value at indices into the `code` array in the interval
\[`start_pc`, `start_pc + length`), that is, between `start_pc`
inclusive and `start_pc + length` exclusive.

<span class="term">name_index</span>  
The value of the `name_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must
contain a `CONSTANT_Utf8_info` structure representing a valid
unqualified name denoting a local variable
(<a href="jvms-4.html#jvms-4.2.2" class="xref"
title="4.2.2. Unqualified Names">§4.2.2</a>).

<span class="term">descriptor_index</span>  
The value of the `descriptor_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must
contain a `CONSTANT_Utf8_info` structure representing a field descriptor
which encodes the type of a local variable in the source program
(<a href="jvms-4.html#jvms-4.3.2" class="xref"
title="4.3.2. Field Descriptors">§4.3.2</a>).

<span class="term">index</span>  
The value of the `index` item must be a valid index into the local
variable array of the current frame. The given local variable is at
`index` in the local variable array of the current frame.

If the given local variable is of type `double` or `long`, it occupies
both `index` and `index + 1`.

</div>

</div>

</div>

<div id="jvms-4.7.14" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.14. The `LocalVariableTypeTable` Attribute

</div>

</div>

</div>

The `LocalVariableTypeTable` attribute is an optional variable-length
attribute in the `attributes` table of a `Code` attribute
(<a href="jvms-4.html#jvms-4.7.3" class="xref"
title="4.7.3. The Code Attribute">§4.7.3</a>). It may be used by
debuggers to determine the value of a given local variable during the
execution of a method.

If multiple `LocalVariableTypeTable` attributes are present in the
`attributes` table of a given `Code` attribute, then they may appear in
any order.

There may be no more than one `LocalVariableTypeTable` attribute
<span class="emphasis">*per local variable*</span> in the `attributes`
table of a `Code` attribute.

The `LocalVariableTypeTable` attribute differs from the
`LocalVariableTable` attribute
(<a href="jvms-4.html#jvms-4.7.13" class="xref"
title="4.7.13. The LocalVariableTable Attribute">§4.7.13</a>) in that it
provides signature information rather than descriptor information. This
difference is only significant for variables whose type uses a type
variable or parameterized type. Such variables will appear in both
tables, while variables of other types will appear only in
`LocalVariableTable`.

The `LocalVariableTypeTable` attribute has the following format:

``` screen
LocalVariableTypeTable_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 local_variable_type_table_length;
    {   u2 start_pc;
        u2 length;
        u2 name_index;
        u2 signature_index;
        u2 index;
    } local_variable_type_table[local_variable_type_table_length];
}
```

The items of the `LocalVariableTypeTable_attribute` structure are as
follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the string "`LocalVariableTypeTable`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item indicates the length of the
attribute, excluding the initial six bytes.

<span class="term">local_variable_type_table_length</span>  
The value of the `local_variable_type_table_length` item indicates the
number of entries in the `local_variable_type_table` array.

<span class="term">local_variable_type_table\[\]</span>  
Each entry in the `local_variable_type_table` array indicates a range of
`code` array offsets within which a local variable has a value, and
indicates the index into the local variable array of the current frame
at which that local variable can be found. Each entry must contain the
following five items:

<div class="variablelist">

<span class="term">start_pc, length</span>  
The value of the `start_pc` item must be a valid index into the `code`
array of this `Code` attribute and must be the index of the opcode of an
instruction.

The value of `start_pc + length` must either be a valid index into the
`code` array of this `Code` attribute and be the index of the opcode of
an instruction, or it must be the first index beyond the end of that
`code` array.

The `start_pc` and `length` items indicate that the given local variable
has a value at indices into the `code` array in the interval
\[`start_pc`, `start_pc + length`), that is, between `start_pc`
inclusive and `start_pc + length` exclusive.

<span class="term">name_index</span>  
The value of the `name_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must
contain a `CONSTANT_Utf8_info` structure representing a valid
unqualified name denoting a local variable
(<a href="jvms-4.html#jvms-4.2.2" class="xref"
title="4.2.2. Unqualified Names">§4.2.2</a>).

<span class="term">signature_index</span>  
The value of the `signature_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must
contain a `CONSTANT_Utf8_info` structure representing a field signature
which encodes the type of a local variable in the source program
(<a href="jvms-4.html#jvms-4.7.9.1" class="xref"
title="4.7.9.1. Signatures">§4.7.9.1</a>).

<span class="term">index</span>  
The value of the `index` item must be a valid index into the local
variable array of the current frame. The given local variable is at
`index` in the local variable array of the current frame.

If the given local variable is of type `double` or `long`, it occupies
both `index` and `index + 1`.

</div>

</div>

</div>

<div id="jvms-4.7.15" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.15. The `Deprecated` Attribute

</div>

</div>

</div>

The `Deprecated` attribute is an optional fixed-length attribute in the
`attributes` table of a `ClassFile`, `field_info`, or `method_info`
structure (<a href="jvms-4.html#jvms-4.1" class="xref"
title="4.1. The ClassFile Structure">§4.1</a>,
<a href="jvms-4.html#jvms-4.5" class="xref" title="4.5. Fields">§4.5</a>,
<a href="jvms-4.html#jvms-4.6" class="xref"
title="4.6. Methods">§4.6</a>). A class, interface, method, or field may
be marked using a `Deprecated` attribute to indicate that the class,
interface, method, or field has been superseded.

A run-time interpreter or tool that reads the `class` file format, such
as a compiler, can use this marking to advise the user that a superseded
class, interface, method, or field is being referred to. The presence of
a `Deprecated` attribute does not alter the semantics of a class or
interface.

The `Deprecated` attribute has the following format:

``` screen
Deprecated_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
}
```

The items of the `Deprecated_attribute` structure are as follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the string "`Deprecated`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item must be zero.

</div>

</div>

<div id="jvms-4.7.16" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.16. The `RuntimeVisibleAnnotations` Attribute

</div>

</div>

</div>

The `RuntimeVisibleAnnotations` attribute is a variable-length attribute
in the `attributes` table of a `ClassFile`, `field_info`, `method_info`,
or `record_component_info` structure
(<a href="jvms-4.html#jvms-4.1" class="xref"
title="4.1. The ClassFile Structure">§4.1</a>,
<a href="jvms-4.html#jvms-4.5" class="xref" title="4.5. Fields">§4.5</a>,
<a href="jvms-4.html#jvms-4.6" class="xref"
title="4.6. Methods">§4.6</a>,
<a href="jvms-4.html#jvms-4.7.30" class="xref"
title="4.7.30. The Record Attribute">§4.7.30</a>). The
`RuntimeVisibleAnnotations` attribute stores run-time visible
annotations on the declaration of the corresponding class, field,
method, or record component.

There may be at most one `RuntimeVisibleAnnotations` attribute in the
`attributes` table of a `ClassFile`, `field_info`, `method_info`, or
`record_component_info` structure.

The `RuntimeVisibleAnnotations` attribute has the following format:

``` screen
RuntimeVisibleAnnotations_attribute {
    u2         attribute_name_index;
    u4         attribute_length;
    u2         num_annotations;
    annotation annotations[num_annotations];
}
```

The items of the `RuntimeVisibleAnnotations_attribute` structure are as
follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the string "`RuntimeVisibleAnnotations`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item indicates the length of the
attribute, excluding the initial six bytes.

<span class="term">num_annotations</span>  
The value of the `num_annotations` item gives the number of run-time
visible annotations represented by the structure.

<span class="term">annotations\[\]</span>  
Each entry in the `annotations` table represents a single run-time
visible annotation on a declaration. The `annotation` structure has the
following format:

``` screen
annotation {
    u2 type_index;
    u2 num_element_value_pairs;
    {   u2            element_name_index;
        element_value value;
    } element_value_pairs[num_element_value_pairs];
}
      
```

The items of the `annotation` structure are as follows:

<div class="variablelist">

<span class="term">type_index</span>  
The value of the `type_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
a field descriptor (<a href="jvms-4.html#jvms-4.3.2" class="xref"
title="4.3.2. Field Descriptors">§4.3.2</a>). The field descriptor
denotes the type of the annotation represented by this `annotation`
structure.

<span class="term">num_element_value_pairs</span>  
The value of the `num_element_value_pairs` item gives the number of
element-value pairs of the annotation represented by this `annotation`
structure.

<span class="term">element_value_pairs\[\]</span>  
Each value of the `element_value_pairs` table represents a single
element-value pair in the annotation represented by this `annotation`
structure. Each `element_value_pairs` entry contains the following two
items:

<div class="variablelist">

<span class="term">element_name_index</span>  
The value of the `element_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>). The
`constant_pool` entry denotes the name of the element of the
element-value pair represented by this `element_value_pairs` entry.

In other words, the entry denotes an element of the annotation interface
specified by `type_index`.

<span class="term">value</span>  
The value of the `value` item represents the value of the element-value
pair represented by this `element_value_pairs` entry.

</div>

</div>

</div>

<div id="jvms-4.7.16.1" class="section">

<div class="titlepage">

<div>

<div>

#### 4.7.16.1. The `element_value` structure

</div>

</div>

</div>

The `element_value` structure is a discriminated union representing the
value of an element-value pair. It has the following format:

``` screen
element_value {
    u1 tag;
    union {
        u2 const_value_index;

        {   u2 type_name_index;
            u2 const_name_index;
        } enum_const_value;

        u2 class_info_index;

        annotation annotation_value;

        {   u2            num_values;
            element_value values[num_values];
        } array_value;
    } value;
}
```

The `tag` item uses a single ASCII character to indicate the type of the
value of the element-value pair. This determines which item of the
`value` union is in use.
<a href="jvms-4.html#jvms-4.7.16.1-130" class="xref"
title="Table 4.7.16.1-A. Interpretation of tag values as types">Table 4.7.16.1-A</a>
shows the valid characters for the `tag` item, the type indicated by
each character, and the item used in the `value` union for each
character. The table's fourth column is used in the description below of
one item of the `value` union.

<div id="jvms-4.7.16.1-130" class="table">

**Table 4.7.16.1-A. Interpretation of `tag` values as types**

<div class="table-contents">

| `tag` Item | Type | `value` Item | Constant Type |
|----|----|----|----|
| `B` | `byte` | `const_value_index` | `CONSTANT_Integer` |
| `C` | `char` | `const_value_index` | `CONSTANT_Integer` |
| `D` | `double` | `const_value_index` | `CONSTANT_Double` |
| `F` | `float` | `const_value_index` | `CONSTANT_Float` |
| `I` | `int` | `const_value_index` | `CONSTANT_Integer` |
| `J` | `long` | `const_value_index` | `CONSTANT_Long` |
| `S` | `short` | `const_value_index` | `CONSTANT_Integer` |
| `Z` | `boolean` | `const_value_index` | `CONSTANT_Integer` |
| `s` | `String` | `const_value_index` | `CONSTANT_Utf8` |
| `e` | Enum class | `enum_const_value` | <span class="emphasis">*Not applicable*</span> |
| `c` | `Class` | `class_info_index` | <span class="emphasis">*Not applicable*</span> |
| `@` | Annotation interface | `annotation_value` | <span class="emphasis">*Not applicable*</span> |
| `[` | Array type | `array_value` | <span class="emphasis">*Not applicable*</span> |

</div>

</div>

  

The <span class="emphasis">*value*</span> item represents the value of
an element-value pair. The item is a union, whose own items are as
follows:

<div class="variablelist">

<span class="term">const_value_index</span>  
The `const_value_index` item denotes a constant of either a primitive
type or the type `String` as the value of this element-value pair.

The value of the `const_value_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be
of a type appropriate to the `tag` item, as specified in the fourth
column of <a href="jvms-4.html#jvms-4.7.16.1-130" class="xref"
title="Table 4.7.16.1-A. Interpretation of tag values as types">Table 4.7.16.1-A</a>.

<span class="term">enum_const_value</span>  
The `enum_const_value` item denotes an enum constant as the value of
this element-value pair.

The `enum_const_value` item consists of the following two items:

<div class="variablelist">

<span class="term">type_name_index</span>  
The value of the `type_name_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
a field descriptor (<a href="jvms-4.html#jvms-4.3.2" class="xref"
title="4.3.2. Field Descriptors">§4.3.2</a>). The `constant_pool` entry
gives the internal form of the binary name of the type of the enum
constant represented by this `element_value` structure
(<a href="jvms-4.html#jvms-4.2.1" class="xref"
title="4.2.1. Binary Class and Interface Names">§4.2.1</a>).

<span class="term">const_name_index</span>  
The value of the `const_name_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>). The
`constant_pool` entry gives the simple name of the enum constant
represented by this `element_value` structure.

</div>

<span class="term">class_info_index</span>  
The `class_info_index` item denotes a class literal as the value of this
element-value pair.

The `class_info_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
a return descriptor (<a href="jvms-4.html#jvms-4.3.3" class="xref"
title="4.3.3. Method Descriptors">§4.3.3</a>). The return descriptor
gives the type corresponding to the class literal represented by this
`element_value` structure. Types correspond to class literals as
follows:

<div class="norm">

- For a class literal <span class="type">C</span>`.``class`, where
  <span class="type">C</span> is the name of a class, interface, or
  array type, the corresponding type is <span class="type">C</span>. The
  return descriptor in the `constant_pool` will be a
  <span class="emphasis">*ClassType*</span> or an
  <span class="emphasis">*ArrayType*</span>.

- For a class literal <span class="type">p</span>`.``class`, where
  <span class="type">p</span> is the name of a primitive type, the
  corresponding type is <span class="type">p</span>. The return
  descriptor in the `constant_pool` will be a
  <span class="emphasis">*BaseType*</span> character.

- For a class literal `void``.``class`, the corresponding type is
  `void`. The return descriptor in the `constant_pool` will be
  <span class="emphasis">*V*</span>.

</div>

For example, the class literal `Object.class` corresponds to the type
`Object`, so the `constant_pool` entry is `Ljava/lang/Object;`, whereas
the class literal `int.class` corresponds to the type `int`, so the
`constant_pool` entry is `I`.

The class literal `void.class` corresponds to `void`, so the
`constant_pool` entry is <span class="emphasis">*V*</span>, whereas the
class literal `Void.class` corresponds to the type `Void`, so the
`constant_pool` entry is `Ljava/lang/Void;`.

<span class="term">annotation_value</span>  
The `annotation_value` item denotes a "nested" annotation as the value
of this element-value pair.

The value of the `annotation_value` item is an `annotation` structure
(<a href="jvms-4.html#jvms-4.7.16" class="xref"
title="4.7.16. The RuntimeVisibleAnnotations Attribute">§4.7.16</a>)
that gives the annotation represented by this `element_value` structure.

<span class="term">array_value</span>  
The `array_value` item denotes an array as the value of this
element-value pair.

The `array_value` item consists of the following two items:

<div class="variablelist">

<span class="term">num_values</span>  
The value of the `num_values` item gives the number of elements in the
array represented by this `element_value` structure.

<span class="term">values\[\]</span>  
Each value in the `values` table gives the corresponding element of the
array represented by this `element_value` structure.

</div>

</div>

</div>

</div>

<div id="jvms-4.7.17" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.17. The `RuntimeInvisibleAnnotations` Attribute

</div>

</div>

</div>

The `RuntimeInvisibleAnnotations` attribute is a variable-length
attribute in the `attributes` table of a `ClassFile`, `field_info`,
`method_info`, or `record_component_info` structure
(<a href="jvms-4.html#jvms-4.1" class="xref"
title="4.1. The ClassFile Structure">§4.1</a>,
<a href="jvms-4.html#jvms-4.5" class="xref" title="4.5. Fields">§4.5</a>,
<a href="jvms-4.html#jvms-4.6" class="xref"
title="4.6. Methods">§4.6</a>,
<a href="jvms-4.html#jvms-4.7.30" class="xref"
title="4.7.30. The Record Attribute">§4.7.30</a>). The
`RuntimeInvisibleAnnotations` attribute stores run-time invisible
annotations on the declaration of the corresponding class, method,
field, or record component.

There may be at most one `RuntimeInvisibleAnnotations` attribute in the
`attributes` table of a `ClassFile`, `field_info`, `method_info`, or
`record_component_info` structure.

The `RuntimeInvisibleAnnotations` attribute is similar to the
`RuntimeVisibleAnnotations` attribute
(<a href="jvms-4.html#jvms-4.7.16" class="xref"
title="4.7.16. The RuntimeVisibleAnnotations Attribute">§4.7.16</a>),
except that the annotations represented by a
`RuntimeInvisibleAnnotations` attribute must not be made available for
return by reflective APIs, unless the Java Virtual Machine has been
instructed to retain these annotations via some implementation-specific
mechanism such as a command line flag. In the absence of such
instructions, the Java Virtual Machine ignores this attribute.

The `RuntimeInvisibleAnnotations` attribute has the following format:

``` screen
RuntimeInvisibleAnnotations_attribute {
    u2         attribute_name_index;
    u4         attribute_length;
    u2         num_annotations;
    annotation annotations[num_annotations];
}
```

The items of the `RuntimeInvisibleAnnotations_attribute` structure are
as follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the string "`RuntimeInvisibleAnnotations`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item indicates the length of the
attribute, excluding the initial six bytes.

<span class="term">num_annotations</span>  
The value of the `num_annotations` item gives the number of run-time
invisible annotations represented by the structure.

<span class="term">annotations\[\]</span>  
Each entry in the `annotations` table represents a single run-time
invisible annotation on a declaration. The `annotation` structure is
specified in <a href="jvms-4.html#jvms-4.7.16" class="xref"
title="4.7.16. The RuntimeVisibleAnnotations Attribute">§4.7.16</a>.

</div>

</div>

<div id="jvms-4.7.18" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.18. The `RuntimeVisibleParameterAnnotations` Attribute

</div>

</div>

</div>

The `RuntimeVisibleParameterAnnotations` attribute is a variable-length
attribute in the `attributes` table of the `method_info` structure
(<a href="jvms-4.html#jvms-4.6" class="xref"
title="4.6. Methods">§4.6</a>). The `RuntimeVisibleParameterAnnotations`
attribute stores run-time visible annotations on the declarations of
formal parameters of the corresponding method.

There may be at most one `RuntimeVisibleParameterAnnotations` attribute
in the `attributes` table of a `method_info` structure.

The `RuntimeVisibleParameterAnnotations` attribute has the following
format:

``` screen
RuntimeVisibleParameterAnnotations_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u1 num_parameters;
    {   u2         num_annotations;
        annotation annotations[num_annotations];
    } parameter_annotations[num_parameters];
}
```

The items of the `RuntimeVisibleParameterAnnotations_attribute`
structure are as follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the string "`RuntimeVisibleParameterAnnotations`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item indicates the length of the
attribute, excluding the initial six bytes.

<span class="term">num_parameters</span>  
The value of the `num_parameters` item gives the number of run-time
visible parameter annotations represented by this structure.

There is no assurance that this number is the same as the number of
parameter descriptors in the method descriptor.

<span class="term">parameter_annotations\[\]</span>  
Each entry in the `parameter_annotations` table represents all of the
run-time visible annotations on the declaration of a single formal
parameter. Each `parameter_annotations` entry contains the following two
items:

<div class="variablelist">

<span class="term">num_annotations</span>  
The value of the `num_annotations` item indicates the number of run-time
visible annotations on the declaration of the formal parameter
corresponding to the `parameter_annotations` entry.

<span class="term">annotations\[\]</span>  
Each entry in the `annotations` table represents a single run-time
visible annotation on the declaration of the formal parameter
corresponding to the `parameter_annotations` entry. The `annotation`
structure is specified in <a href="jvms-4.html#jvms-4.7.16" class="xref"
title="4.7.16. The RuntimeVisibleAnnotations Attribute">§4.7.16</a>.

</div>

The <span class="emphasis">*i*</span>'th entry in the
`parameter_annotations` table may, but is not required to, correspond to
the <span class="emphasis">*i*</span>'th parameter descriptor in the
method descriptor (<a href="jvms-4.html#jvms-4.3.3" class="xref"
title="4.3.3. Method Descriptors">§4.3.3</a>).

For example, a compiler may choose to create entries in the table
corresponding only to those parameter descriptors which represent
explicitly declared parameters in source code. In the Java programming
language, a constructor of an inner class is specified to have an
implicitly declared parameter before its explicitly declared parameters
(JLS §8.8.1), so the corresponding `<init>` method in a `class` file has
a parameter descriptor representing the implicitly declared parameter
before any parameter descriptors representing explicitly declared
parameters. If the first explicitly declared parameter is annotated in
source code, then a compiler may create `parameter_annotations[0]` to
store annotations corresponding to the
<span class="emphasis">*second*</span> parameter descriptor.

</div>

</div>

<div id="jvms-4.7.19" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.19. The `RuntimeInvisibleParameterAnnotations` Attribute

</div>

</div>

</div>

The `RuntimeInvisibleParameterAnnotations` attribute is a
variable-length attribute in the `attributes` table of a `method_info`
structure (<a href="jvms-4.html#jvms-4.6" class="xref"
title="4.6. Methods">§4.6</a>). The
`RuntimeInvisibleParameterAnnotations` attribute stores run-time
invisible annotations on the declarations of formal parameters of the
corresponding method.

There may be at most one `RuntimeInvisibleParameterAnnotations`
attribute in the `attributes` table of a `method_info` structure.

The `RuntimeInvisibleParameterAnnotations` attribute is similar to the
`RuntimeVisibleParameterAnnotations` attribute
(<a href="jvms-4.html#jvms-4.7.18" class="xref"
title="4.7.18. The RuntimeVisibleParameterAnnotations Attribute">§4.7.18</a>),
except that the annotations represented by a
`RuntimeInvisibleParameterAnnotations` attribute must not be made
available for return by reflective APIs, unless the Java Virtual Machine
has specifically been instructed to retain these annotations via some
implementation-specific mechanism such as a command line flag. In the
absence of such instructions, the Java Virtual Machine ignores this
attribute.

The `RuntimeInvisibleParameterAnnotations` attribute has the following
format:

``` screen
RuntimeInvisibleParameterAnnotations_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u1 num_parameters;
    {   u2         num_annotations;
        annotation annotations[num_annotations];
    } parameter_annotations[num_parameters];
}
```

The items of the `RuntimeInvisibleParameterAnnotations_attribute`
structure are as follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the string "`RuntimeInvisibleParameterAnnotations`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item indicates the length of the
attribute, excluding the initial six bytes.

<span class="term">num_parameters</span>  
The value of the `num_parameters` item gives the number of run-time
invisible parameter annotations represented by this structure.

There is no assurance that this number is the same as the number of
parameter descriptors in the method descriptor.

<span class="term">parameter_annotations\[\]</span>  
Each entry in the `parameter_annotations` table represents all of the
run-time invisible annotations on the declaration of a single formal
parameter. Each `parameter_annotations` entry contains the following two
items:

<div class="variablelist">

<span class="term">num_annotations</span>  
The value of the `num_annotations` item indicates the number of run-time
invisible annotations on the declaration of the formal parameter
corresponding to the `parameter_annotations` entry.

<span class="term">annotations\[\]</span>  
Each entry in the `annotations` table represents a single run-time
invisible annotation on the declaration of the formal parameter
corresponding to the `parameter_annotations` entry. The `annotation`
structure is specified in <a href="jvms-4.html#jvms-4.7.16" class="xref"
title="4.7.16. The RuntimeVisibleAnnotations Attribute">§4.7.16</a>.

</div>

The <span class="emphasis">*i*</span>'th entry in the
`parameter_annotations` table may, but is not required to, correspond to
the <span class="emphasis">*i*</span>'th parameter descriptor in the
method descriptor (<a href="jvms-4.html#jvms-4.3.3" class="xref"
title="4.3.3. Method Descriptors">§4.3.3</a>).

See the note in <a href="jvms-4.html#jvms-4.7.18" class="xref"
title="4.7.18. The RuntimeVisibleParameterAnnotations Attribute">§4.7.18</a>
for an example of when `parameter_annotations[0]` does not correspond to
the first parameter descriptor in the method descriptor.

</div>

</div>

<div id="jvms-4.7.20" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.20. The `RuntimeVisibleTypeAnnotations` Attribute

</div>

</div>

</div>

The `RuntimeVisibleTypeAnnotations` attribute is an variable-length
attribute in the `attributes` table of a `ClassFile`, `field_info`,
`method_info`, or `record_component_info` structure, or `Code` attribute
(<a href="jvms-4.html#jvms-4.1" class="xref"
title="4.1. The ClassFile Structure">§4.1</a>,
<a href="jvms-4.html#jvms-4.5" class="xref" title="4.5. Fields">§4.5</a>,
<a href="jvms-4.html#jvms-4.6" class="xref"
title="4.6. Methods">§4.6</a>,
<a href="jvms-4.html#jvms-4.7.30" class="xref"
title="4.7.30. The Record Attribute">§4.7.30</a>,
<a href="jvms-4.html#jvms-4.7.3" class="xref"
title="4.7.3. The Code Attribute">§4.7.3</a>). The
`RuntimeVisibleTypeAnnotations` attribute stores run-time visible
annotations on types used in the declaration of the corresponding class,
field, method, or record component, or in an expression in the
corresponding method body. The `RuntimeVisibleTypeAnnotations` attribute
also stores run-time visible annotations on type parameter declarations
of generic classes, interfaces, methods, and constructors.

There may be at most one `RuntimeVisibleTypeAnnotations` attribute in
the `attributes` table of a `ClassFile`, `field_info`, `method_info`, or
`record_component_info` structure, or `Code` attribute.

An `attributes` table contains a `RuntimeVisibleTypeAnnotations`
attribute only if types are annotated in kinds of declaration or
expression that correspond to the parent structure or attribute of the
`attributes` table.

For example, all annotations on types in the `implements` clause of a
class declaration are recorded in the `RuntimeVisibleTypeAnnotations`
attribute of the class's `ClassFile` structure. Meanwhile, all
annotations on the type in a field declaration are recorded in the
`RuntimeVisibleTypeAnnotations` attribute of the field's `field_info`
structure.

The `RuntimeVisibleTypeAnnotations` attribute has the following format:

``` screen
RuntimeVisibleTypeAnnotations_attribute {
    u2              attribute_name_index;
    u4              attribute_length;
    u2              num_annotations;
    type_annotation annotations[num_annotations];
}
```

The items of the `RuntimeVisibleTypeAnnotations_attribute` structure are
as follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure representing the string
"`RuntimeVisibleTypeAnnotations`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item indicates the length of the
attribute, excluding the initial six bytes.

<span class="term">num_annotations</span>  
The value of the `num_annotations` item gives the number of run-time
visible type annotations represented by the structure.

<span class="term">annotations\[\]</span>  
Each entry in the `annotations` table represents a single run-time
visible annotation on a type used in a declaration or expression. The
`type_annotation` structure has the following format:

``` screen
type_annotation {
    u1 target_type;
    union {
        type_parameter_target;
        supertype_target;
        type_parameter_bound_target;
        empty_target;
        formal_parameter_target;
        throws_target;
        localvar_target;
        catch_target;
        offset_target;
        type_argument_target;
    } target_info;
    type_path target_path;
    u2        type_index;
    u2        num_element_value_pairs;
    {   u2            element_name_index;
        element_value value;
    } element_value_pairs[num_element_value_pairs];
}
      
```

The first three items - `target_type`, `target_info`, and
`target_path` - specify the precise location of the annotated type. The
last three items - `type_index`, `num_element_value_pairs`, and
`element_value_pairs[]` - specify the annotation's own type and
element-value pairs.

The items of the `type_annotation` structure are as follows:

<div class="variablelist">

<span class="term">target_type</span>  
The value of the `target_type` item denotes the kind of target on which
the annotation appears. The various kinds of target correspond to the
<span class="emphasis">*type contexts*</span> of the Java programming
language where types are used in declarations and expressions (JLS
§4.11).

The legal values of `target_type` are specified in
<a href="jvms-4.html#jvms-4.7.20-400" class="xref"
title="Table 4.7.20-A. Interpretation of target_type values (Part 1)">Table 4.7.20-A</a>
and <a href="jvms-4.html#jvms-4.7.20-410" class="xref"
title="Table 4.7.20-B. Interpretation of target_type values (Part 2)">Table 4.7.20-B</a>.
Each value is a one-byte tag indicating which item of the `target_info`
union follows the `target_type` item to give more information about the
target.

The kinds of target in
<a href="jvms-4.html#jvms-4.7.20-400" class="xref"
title="Table 4.7.20-A. Interpretation of target_type values (Part 1)">Table 4.7.20-A</a>
and <a href="jvms-4.html#jvms-4.7.20-410" class="xref"
title="Table 4.7.20-B. Interpretation of target_type values (Part 2)">Table 4.7.20-B</a>
correspond to the type contexts in JLS §4.11. Namely, `target_type`
values 0x10-0x17 and 0x40-0x42 correspond to type contexts 1-11, while
`target_type` values 0x43-0x4B correspond to type contexts 12-17.

The value of the `target_type` item determines whether the
`type_annotation` structure appears in a `RuntimeVisibleTypeAnnotations`
attribute in a `ClassFile` structure, a `field_info` structure, a
`method_info` structure, or a `Code` attribute.
<a href="jvms-4.html#jvms-4.7.20-420" class="xref"
title="Table 4.7.20-C. Location of enclosing attribute for target_type values">Table 4.7.20-C</a>
gives the location of the `RuntimeVisibleTypeAnnotations` attribute for
a `type_annotation` structure with each legal `target_type` value.

<span class="term">target_info</span>  
The value of the `target_info` item denotes precisely which type in a
declaration or expression is annotated.

The items of the `target_info` union are specified in
<a href="jvms-4.html#jvms-4.7.20.1" class="xref"
title="4.7.20.1. The target_info union">§4.7.20.1</a>.

<span class="term">target_path</span>  
The value of the `target_path` item denotes precisely which part of the
type indicated by `target_info` is annotated.

The format of the `type_path` structure is specified in
<a href="jvms-4.html#jvms-4.7.20.2" class="xref"
title="4.7.20.2. The type_path structure">§4.7.20.2</a>.

<span class="term">type_index, num_element_value_pairs, element_value_pairs\[\]</span>  
The meaning of these items in the `type_annotation` structure is the
same as their meaning in the `annotation` structure
(<a href="jvms-4.html#jvms-4.7.16" class="xref"
title="4.7.16. The RuntimeVisibleAnnotations Attribute">§4.7.16</a>).

</div>

</div>

<div id="jvms-4.7.20-400" class="table">

**Table 4.7.20-A. Interpretation of `target_type` values (Part 1)**

<div class="table-contents">

| Value | Kind of target | `target_info` item |
|----|----|----|
| 0x00 | type parameter declaration of generic class or interface | `type_parameter_target` |
| 0x01 | type parameter declaration of generic method or constructor | `type_parameter_target` |
| 0x10 | type in `extends` or `implements` clause of class declaration (including the direct superclass or direct superinterface of an anonymous class declaration), or in `extends` clause of interface declaration | `supertype_target` |
| 0x11 | type in bound of type parameter declaration of generic class or interface | `type_parameter_bound_target` |
| 0x12 | type in bound of type parameter declaration of generic method or constructor | `type_parameter_bound_target` |
| 0x13 | type in field or record component declaration | `empty_target` |
| 0x14 | return type of method, or type of newly constructed object | `empty_target` |
| 0x15 | receiver type of method or constructor | `empty_target` |
| 0x16 | type in formal parameter declaration of method, constructor, or lambda expression | `formal_parameter_target` |
| 0x17 | type in `throws` clause of method or constructor | `throws_target` |

</div>

</div>

  

<div id="jvms-4.7.20-410" class="table">

**Table 4.7.20-B. Interpretation of `target_type` values (Part 2)**

<div class="table-contents">

| Value | Kind of target | `target_info` item |
|----|----|----|
| 0x40 | type in local variable declaration | `localvar_target` |
| 0x41 | type in resource variable declaration | `localvar_target` |
| 0x42 | type in exception parameter declaration | `catch_target` |
| 0x43 | type in <span class="emphasis">*instanceof*</span> expression | `offset_target` |
| 0x44 | type in <span class="emphasis">*new*</span> expression | `offset_target` |
| 0x45 | type in method reference expression using `::`<span class="emphasis">*new*</span> | `offset_target` |
| 0x46 | type in method reference expression using `::`<span class="emphasis">*Identifier*</span> | `offset_target` |
| 0x47 | type in cast expression | `type_argument_target` |
| 0x48 | type argument for generic constructor in <span class="emphasis">*new*</span> expression or explicit constructor invocation statement | `type_argument_target` |
| 0x49 | type argument for generic method in method invocation expression | `type_argument_target` |
| 0x4A | type argument for generic constructor in method reference expression using `::`<span class="emphasis">*new*</span> | `type_argument_target` |
| 0x4B | type argument for generic method in method reference expression using `::`<span class="emphasis">*Identifier*</span> | `type_argument_target` |

</div>

</div>

  

<div id="jvms-4.7.20-420" class="table">

**Table 4.7.20-C. Location of enclosing attribute for `target_type`
values**

<div class="table-contents">

| Value | Kind of target | Location |
|----|----|----|
| 0x00 | type parameter declaration of generic class or interface | `ClassFile` |
| 0x01 | type parameter declaration of generic method or constructor | `method_info` |
| 0x10 | type in `extends` clause of class or interface declaration, or in `implements` clause of interface declaration | `ClassFile` |
| 0x11 | type in bound of type parameter declaration of generic class or interface | `ClassFile` |
| 0x12 | type in bound of type parameter declaration of generic method or constructor | `method_info` |
| 0x13 | type in field or record component declaration | `field_info`, `record_component_info` |
| 0x14 | return type of method or constructor | `method_info` |
| 0x15 | receiver type of method or constructor | `method_info` |
| 0x16 | type in formal parameter declaration of method, constructor, or lambda expression | `method_info` |
| 0x17 | type in `throws` clause of method or constructor | `method_info` |
| 0x40-0x4B | types in local variable declarations, resource variable declarations, exception parameter declarations, expressions | `Code` |

</div>

</div>

  

<div id="jvms-4.7.20.1" class="section">

<div class="titlepage">

<div>

<div>

#### 4.7.20.1. The `target_info` union

</div>

</div>

</div>

The items of the `target_info` union (except for the first) specify
precisely which type in a declaration or expression is annotated. The
first item specifies not which type, but rather which declaration of a
type parameter is annotated. The items are as follows:

<div class="norm">

- The `type_parameter_target` item indicates that an annotation appears
  on the declaration of the <span class="emphasis">*i*</span>'th type
  parameter of a generic class, generic interface, generic method, or
  generic constructor.

  ``` screen
  type_parameter_target {
      u1 type_parameter_index;
  }
      
  ```

  The value of the `type_parameter_index` item specifies which type
  parameter declaration is annotated. A `type_parameter_index` value of
  `0` specifies the first type parameter declaration.

- The `supertype_target` item indicates that an annotation appears on a
  type in the `extends` or `implements` clause of a class or interface
  declaration.

  ``` screen
  supertype_target {
      u2 supertype_index;
  }
      
  ```

  A `supertype_index` value of 65535 specifies that the annotation
  appears on the superclass in an `extends` clause of a class
  declaration.

  Any other `supertype_index` value is an index into the `interfaces`
  array of the enclosing `ClassFile` structure, and specifies that the
  annotation appears on that superinterface in either the `implements`
  clause of a class declaration or the `extends` clause of an interface
  declaration.

- The `type_parameter_bound_target` item indicates that an annotation
  appears on the <span class="emphasis">*i*</span>'th bound of the
  <span class="emphasis">*j*</span>'th type parameter declaration of a
  generic class, interface, method, or constructor.

  ``` screen
  type_parameter_bound_target {
      u1 type_parameter_index;
      u1 bound_index;
  }
      
  ```

  The value of the of `type_parameter_index` item specifies which type
  parameter declaration has an annotated bound. A `type_parameter_index`
  value of `0` specifies the first type parameter declaration.

  The value of the `bound_index` item specifies which bound of the type
  parameter declaration indicated by `type_parameter_index` is
  annotated. A `bound_index` value of `0` specifies the first bound of a
  type parameter declaration.

  The `type_parameter_bound_target` item records that a bound is
  annotated, but does not record the type which constitutes the bound.
  The type may be found by inspecting the class signature or method
  signature stored in the appropriate `Signature` attribute.

- The `empty_target` item indicates that an annotation appears on either
  the type in a field declaration, the type in a record component
  declaration, the return type of a method, the type of a newly
  constructed object, or the receiver type of a method or constructor.

  ``` screen
  empty_target {
  }
      
  ```

  Only one type appears in each of these locations, so there is no
  per-type information to represent in the `target_info` union.

- The `formal_parameter_target` item indicates that an annotation
  appears on the type in a formal parameter declaration of a method,
  constructor, or lambda expression.

  ``` screen
  formal_parameter_target {
      u1 formal_parameter_index;
  }
      
  ```

  The value of the `formal_parameter_index` item specifies which formal
  parameter declaration has an annotated type. A
  `formal_parameter_index` value of <span class="emphasis">*i*</span>
  may, but is not required to, correspond to the
  <span class="emphasis">*i*</span>'th parameter descriptor in the
  method descriptor (<a href="jvms-4.html#jvms-4.3.3" class="xref"
  title="4.3.3. Method Descriptors">§4.3.3</a>).

  The `formal_parameter_target` item records that a formal parameter's
  type is annotated, but does not record the type itself. The type may
  be found by inspecting the method descriptor, although a
  `formal_parameter_index` value of `0` does not always indicate the
  first parameter descriptor in the method descriptor; see the note in
  <a href="jvms-4.html#jvms-4.7.18" class="xref"
  title="4.7.18. The RuntimeVisibleParameterAnnotations Attribute">§4.7.18</a>
  for a similar situation involving the `parameter_annotations` table.

- The `throws_target` item indicates that an annotation appears on the
  <span class="emphasis">*i*</span>'th type in the `throws` clause of a
  method or constructor declaration.

  ``` screen
  throws_target {
      u2 throws_type_index;
  }
      
  ```

  The value of the `throws_type_index` item is an index into the
  `exception_index_table` array of the `Exceptions` attribute of the
  `method_info` structure enclosing the `RuntimeVisibleTypeAnnotations`
  attribute.

- The `localvar_target` item indicates that an annotation appears on the
  type in a local variable declaration, including a variable declared as
  a resource in a `try`-with-resources statement.

  ``` screen
  localvar_target {
      u2 table_length;
      {   u2 start_pc;
          u2 length;
          u2 index;
      } table[table_length];
  }
      
  ```

  The value of the `table_length` item gives the number of entries in
  the `table` array. Each entry indicates a range of `code` array
  offsets within which a local variable has a value. It also indicates
  the index into the local variable array of the current frame at which
  that local variable can be found. Each entry contains the following
  three items:

  <div class="variablelist">

  <span class="term">start_pc, length</span>  
  The given local variable has a value at indices into the `code` array
  in the interval \[`start_pc`, `start_pc + length`), that is, between
  `start_pc` inclusive and `start_pc + length` exclusive.

  <span class="term">index</span>  
  The given local variable must be at `index` in the local variable
  array of the current frame.

  If the local variable at `index` is of type `double` or `long`, it
  occupies both `index` and `index + 1`.

  </div>

  A table is needed to fully specify the local variable whose type is
  annotated, because a single local variable may be represented with
  different local variable indices over multiple live ranges. The
  `start_pc`, `length`, and `index` items in each table entry specify
  the same information as a `LocalVariableTable` attribute.

  The `localvar_target` item records that a local variable's type is
  annotated, but does not record the type itself. The type may be found
  by inspecting the appropriate `LocalVariableTable` attribute.

- The `catch_target` item indicates that an annotation appears on the
  <span class="emphasis">*i*</span>'th type in an exception parameter
  declaration.

  ``` screen
  catch_target {
      u2 exception_table_index;
  }
      
  ```

  The value of the `exception_table_index` item is an index into the
  `exception_table` array of the `Code` attribute enclosing the
  `RuntimeVisibleTypeAnnotations` attribute.

  The possibility of more than one type in an exception parameter
  declaration arises from the multi-`catch` clause of the `try`
  statement, where the type of the exception parameter is a union of
  types (JLS §14.20). A compiler usually creates one `exception_table`
  entry for each type in the union, which allows the `catch_target` item
  to distinguish them. This preserves the correspondence between a type
  and its annotations.

- The `offset_target` item indicates that an annotation appears on
  either the type in an <span class="emphasis">*instanceof*</span>
  expression or a <span class="emphasis">*new*</span> expression, or the
  type before the `::` in a method reference expression.

  ``` screen
  offset_target {
      u2 offset;
  }
      
  ```

  The value of the `offset` item specifies the `code` array offset of
  either the bytecode instruction corresponding to the
  <span class="emphasis">*instanceof*</span> expression, the
  <span class="emphasis">*new*</span> bytecode instruction corresponding
  to the <span class="emphasis">*new*</span> expression, or the bytecode
  instruction corresponding to the method reference expression.

- The `type_argument_target` item indicates that an annotation appears
  either on the <span class="emphasis">*i*</span>'th type in a cast
  expression, or on the <span class="emphasis">*i*</span>'th type
  argument in the explicit type argument list for any of the following:
  a <span class="emphasis">*new*</span> expression, an explicit
  constructor invocation statement, a method invocation expression, or a
  method reference expression.

  ``` screen
  type_argument_target {
      u2 offset;
      u1 type_argument_index;
  }
      
  ```

  The value of the `offset` item specifies the `code` array offset of
  either the bytecode instruction corresponding to the cast expression,
  the <span class="emphasis">*new*</span> bytecode instruction
  corresponding to the <span class="emphasis">*new*</span> expression,
  the bytecode instruction corresponding to the explicit constructor
  invocation statement, the bytecode instruction corresponding to the
  method invocation expression, or the bytecode instruction
  corresponding to the method reference expression.

  For a cast expression, the value of the `type_argument_index` item
  specifies which type in the cast operator is annotated. A
  `type_argument_index` value of `0` specifies the first (or only) type
  in the cast operator.

  The possibility of more than one type in a cast expression arises from
  a cast to an intersection type.

  For an explicit type argument list, the value of the
  `type_argument_index` item specifies which type argument is annotated.
  A `type_argument_index` value of `0` specifies the first type
  argument.

</div>

</div>

<div id="jvms-4.7.20.2" class="section">

<div class="titlepage">

<div>

<div>

#### 4.7.20.2. The `type_path` structure

</div>

</div>

</div>

Wherever a type is used in a declaration or expression, the `type_path`
structure identifies which part of the type is annotated. An annotation
may appear on the type itself, but if the type is a reference type, then
there are additional locations where an annotation may appear:

<div class="norm">

- If an array type <span class="type">T`[]`</span> is used in a
  declaration or expression, then an annotation may appear on any
  component type of the array type, including the element type.

- If a nested type <span class="type">T1`.`T2</span> is used in a
  declaration or expression, then an annotation may appear on the name
  of the innermost member type and any enclosing type for which a type
  annotation is admissible (JLS §9.7.4).

- If a parameterized type <span class="type">T`<`A`>`</span> or
  <span class="type">T`<`? extends A`>`</span> or
  <span class="type">T`<`? super A`>`</span> is used in a declaration or
  expression, then an annotation may appear on any type argument or on
  the bound of any wildcard type argument.

</div>

<div class="informalexample">

For example, consider the different parts of `String``[]``[]` that are
annotated in:

``` screen
@Foo String[][]   // Annotates the class type String
String @Foo [][]  // Annotates the array type String[][]
String[] @Foo []  // Annotates the array type String[]
```

or the different parts of the nested type `Outer.Middle.Inner` that are
annotated in:

``` screen
@Foo Outer.Middle.Inner
Outer.@Foo Middle.Inner
Outer.Middle.@Foo Inner
```

or the different parts of the parameterized types `Map<String,Object>`
and `List<...>` that are annotated in:

``` screen
@Foo Map<String,Object>
Map<@Foo String,Object>
Map<String,@Foo Object>

List<@Foo ? extends String>
List<? extends @Foo String>
```

</div>

The `type_path` structure has the following format:

``` screen
type_path {
    u1 path_length;
    {   u1 type_path_kind;
        u1 type_argument_index;
    } path[path_length];
}
```

The value of the `path_length` item gives the number of entries in the
`path` array:

<div class="norm">

- If the value of `path_length` is `0`, and the type being annotated is
  a nested type, then the annotation applies to the outermost part of
  the type for which a type annotation is admissible.

- If the value of `path_length` is `0`, and the type being annotated is
  not a nested type, then the annotation appears directly on the type
  itself.

- If the value of `path_length` is non-zero, then each entry in the
  `path` array represents an iterative, left-to-right step towards the
  precise location of the annotation in an array type, nested type, or
  parameterized type. (In an array type, the iteration visits the array
  type itself, then its component type, then the component type of that
  component type, and so on, until the element type is reached.) Each
  entry contains the following two items:

  <div class="variablelist">

  <span class="term">type_path_kind</span>  
  The legal values for the `type_path_kind` item are listed in
  <a href="jvms-4.html#jvms-4.7.20.2-220-B-A.1" class="xref"
  title="Table 4.7.20.2-A. Interpretation of type_path_kind values">Table 4.7.20.2-A</a>.

  <div id="jvms-4.7.20.2-220-B-A.1" class="table">

  **Table 4.7.20.2-A. Interpretation of `type_path_kind` values**

  <div class="table-contents">

  | Value | Interpretation |
  |----|----|
  | `0` | Annotation is deeper in an array type |
  | `1` | Annotation is deeper in a nested type |
  | `2` | Annotation is on the bound of a wildcard type argument of a parameterized type |
  | `3` | Annotation is on a type argument of a parameterized type |

  </div>

  </div>

    

  <span class="term">type_argument_index</span>  
  If the value of the `type_path_kind` item is `0`, `1`, or `2`, then
  the value of the `type_argument_index` item is `0`.

  If the value of the `type_path_kind` item is `3`, then the value of
  the `type_argument_index` item specifies which type argument of a
  parameterized type is annotated, where `0` indicates the first type
  argument of a parameterized type.

  </div>

</div>

<div class="informalexample">

<div id="d5e9514" class="table">

**Table 4.7.20.2-B. `type_path` structures for
`@A Map<@B ? extends @C String, @D List<@E Object>>`**

<div class="table-contents">

| Annotation | `path_length` | `path` |
|----|----|----|
| `@A` | `0` | `[]` |
| `@B` | `1` | `[{type_path_kind: 3; type_argument_index: 0}]` |
| `@C` | `2` | `[{type_path_kind: 3; type_argument_index: 0}, {type_path_kind: 2; type_argument_index: 0}]` |
| `@D` | `1` | `[{type_path_kind: 3; type_argument_index: 1}]` |
| `@E` | `2` | `[{type_path_kind: 3; type_argument_index: 1}, {type_path_kind: 3; type_argument_index: 0}]` |

</div>

</div>

  

<div id="d5e9565" class="table">

**Table 4.7.20.2-C. `type_path` structures for
`@I String @F [] @G [] @H []`**

<div class="table-contents">

| Annotation | `path_length` | `path` |
|----|----|----|
| `@F` | `0` | `[]` |
| `@G` | `1` | `[{type_path_kind: 0; type_argument_index: 0}]` |
| `@H` | `2` | `[{type_path_kind: 0; type_argument_index: 0}, {type_path_kind: 0; type_argument_index: 0}]` |
| `@I` | `3` | `[{type_path_kind: 0; type_argument_index: 0}, {type_path_kind: 0; type_argument_index: 0}, {type_path_kind: 0; type_argument_index: 0}]` |

</div>

</div>

  

<div id="d5e9609" class="table">

**Table 4.7.20.2-D. `type_path` structures for
`@A List<@B Comparable<@F Object @C [] @D [] @E []>>`**

<div class="table-contents">

| Annotation | `path_length` | `path` |
|----|----|----|
| `@A` | `0` | `[]` |
| `@B` | `1` | `[{type_path_kind: 3; type_argument_index: 0}]` |
| `@C` | `2` | `[{type_path_kind: 3; type_argument_index: 0}, {type_path_kind: 3; type_argument_index: 0}]` |
| `@D` | `3` | `[{type_path_kind: 3; type_argument_index: 0}, {type_path_kind: 3; type_argument_index: 0}, {type_path_kind: 0; type_argument_index: 0}]` |
| `@E` | `4` | `[{type_path_kind: 3; type_argument_index: 0}, {type_path_kind: 3; type_argument_index: 0}, {type_path_kind: 0; type_argument_index: 0}, {type_path_kind: 0; type_argument_index: 0}]` |
| `@F` | `5` | `[{type_path_kind: 3; type_argument_index: 0}, {type_path_kind: 3; type_argument_index: 0}, {type_path_kind: 0; type_argument_index: 0}, {type_path_kind: 0; type_argument_index: 0}, {type_path_kind: 0; type_argument_index: 0}]` |

</div>

</div>

  

<div id="d5e9667" class="table">

**Table 4.7.20.2-E. `type_path` structures for
`@A Outer . @B Middle . @C Inner`**

<div class="table-contents">

<table class="table" data-border="1">
<thead>
<tr>
<th>Assuming:</th>
<th> </th>
<th style="text-align: left;"><pre class="programlisting"><code>class Outer {
  class Middle {
    class Inner {}
  }
}</code></pre></th>
</tr>
<tr>
<th>Annotation</th>
<th><code class="literal">path_length</code></th>
<th><code class="literal">path</code></th>
</tr>
</thead>
<tbody>
<tr>
<td><code class="literal">@A</code></td>
<td><code class="literal">0</code></td>
<td><code class="literal">[]</code></td>
</tr>
<tr>
<td><code class="literal">@B</code></td>
<td><code class="literal">1</code></td>
<td><code
class="literal">[{type_path_kind: 1; type_argument_index: 0}]</code></td>
</tr>
<tr>
<td><code class="literal">@C</code></td>
<td><code class="literal">2</code></td>
<td><code
class="literal">[{type_path_kind: 1; type_argument_index: 0}, {type_path_kind: 1; type_argument_index: 0}]</code></td>
</tr>
</tbody>
</table>

</div>

</div>

  

<div id="d5e9709" class="table">

**Table 4.7.20.2-F. `type_path` structures for
`Outer . @A MiddleStatic . @B Inner`**

<div class="table-contents">

<table class="table" data-border="1">
<thead>
<tr>
<th>Assuming:</th>
<th> </th>
<th style="text-align: left;"><pre class="programlisting"><code>class Outer {
  static class MiddleStatic {
    class Inner {}
  }
}</code></pre></th>
</tr>
<tr>
<th>Annotation</th>
<th><code class="literal">path_length</code></th>
<th><code class="literal">path</code></th>
</tr>
</thead>
<tbody>
<tr>
<td><code class="literal">@A</code></td>
<td><code class="literal">0</code></td>
<td><code class="literal">[]</code></td>
</tr>
<tr>
<td><code class="literal">@B</code></td>
<td><code class="literal">1</code></td>
<td><code
class="literal">[{type_path_kind: 1; type_argument_index: 0}]</code></td>
</tr>
<tr>
<td> </td>
<td> </td>
<td style="text-align: left;">In the type <code
class="literal">Outer . MiddleStatic . Inner</code>, type annotations on
the simple name <code class="literal">Outer</code> are not admissible
because the type name to its right, <code
class="literal">MiddleStatic</code>, does not refer to an inner class of
<code class="literal">Outer</code>.</td>
</tr>
</tbody>
</table>

</div>

</div>

  

<div id="d5e9752" class="table">

**Table 4.7.20.2-G. `type_path` structures for
`Outer . MiddleStatic . @A InnerStatic`**

<div class="table-contents">

<table class="table" data-border="1">
<thead>
<tr>
<th>Assuming:</th>
<th> </th>
<th style="text-align: left;"><pre class="programlisting"><code>class Outer {
  static class MiddleStatic {
    static class InnerStatic {}
  }
}</code></pre></th>
</tr>
<tr>
<th>Annotation</th>
<th><code class="literal">path_length</code></th>
<th><code class="literal">path</code></th>
</tr>
</thead>
<tbody>
<tr>
<td><code class="literal">@A</code></td>
<td><code class="literal">0</code></td>
<td><code class="literal">[]</code></td>
</tr>
<tr>
<td> </td>
<td> </td>
<td style="text-align: left;">In the type <code
class="literal">Outer . MiddleStatic . InnerStatic</code>, type
annotations on the simple name <code class="literal">Outer</code> are
not admissible because the type name to its right, <code
class="literal">MiddleStatic</code>, does not refer to an inner class of
<code class="literal">Outer</code>. Similarly, type annotations on the
simple name <code class="literal">MiddleStatic</code> are not admissible
because the type name to its right, <code
class="literal">InnerStatic</code>, does not refer to an inner class of
<code class="literal">MiddleStatic</code>.</td>
</tr>
</tbody>
</table>

</div>

</div>

  

<div id="d5e9791" class="table">

**Table 4.7.20.2-H. `type_path` structures for
`Outer . Middle<@A Foo . @B Bar> . Inner<@D String @C []>`**

<div class="table-contents">

<table class="table" data-border="1">
<thead>
<tr>
<th>Assuming:</th>
<th> </th>
<th style="text-align: left;"><pre class="programlisting"><code>class Outer {
  class Middle&lt;T&gt; {
    class Inner&lt;U&gt; {}
  }
}</code></pre></th>
</tr>
<tr>
<th>Annotation</th>
<th><code class="literal">path_length</code></th>
<th><code class="literal">path</code></th>
</tr>
</thead>
<tbody>
<tr>
<td><code class="literal">@A</code></td>
<td><code class="literal">2</code></td>
<td><code
class="literal">[{type_path_kind: 1; type_argument_index: 0}, {type_path_kind: 3; type_argument_index: 0}]</code></td>
</tr>
<tr>
<td><code class="literal">@B</code></td>
<td><code class="literal">3</code></td>
<td><code
class="literal">[{type_path_kind: 1; type_argument_index: 0}, {type_path_kind: 3; type_argument_index: 0}, {type_path_kind: 1; type_argument_index: 0}]</code></td>
</tr>
<tr>
<td><code class="literal">@C</code></td>
<td><code class="literal">3</code></td>
<td><code
class="literal">[{type_path_kind: 1; type_argument_index: 0}, {type_path_kind: 1; type_argument_index: 0}, {type_path_kind: 3; type_argument_index: 0}]</code></td>
</tr>
<tr>
<td><code class="literal">@D</code></td>
<td><code class="literal">4</code></td>
<td><code
class="literal">[{type_path_kind: 1; type_argument_index: 0}, {type_path_kind: 1; type_argument_index: 0}, {type_path_kind: 3; type_argument_index: 0}, {type_path_kind: 0; type_argument_index: 0}]</code></td>
</tr>
</tbody>
</table>

</div>

</div>

  

</div>

</div>

</div>

<div id="jvms-4.7.21" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.21. The `RuntimeInvisibleTypeAnnotations` Attribute

</div>

</div>

</div>

The `RuntimeInvisibleTypeAnnotations` attribute is an variable-length
attribute in the `attributes` table of a `ClassFile`, `field_info`,
`method_info`, or `record_component_info` structure, or `Code` attribute
(<a href="jvms-4.html#jvms-4.1" class="xref"
title="4.1. The ClassFile Structure">§4.1</a>,
<a href="jvms-4.html#jvms-4.5" class="xref" title="4.5. Fields">§4.5</a>,
<a href="jvms-4.html#jvms-4.6" class="xref"
title="4.6. Methods">§4.6</a>,
<a href="jvms-4.html#jvms-4.7.30" class="xref"
title="4.7.30. The Record Attribute">§4.7.30</a>,
<a href="jvms-4.html#jvms-4.7.3" class="xref"
title="4.7.3. The Code Attribute">§4.7.3</a>). The
`RuntimeInvisibleTypeAnnotations` attribute stores run-time invisible
annotations on types used in the corresponding declaration of a class,
field, method, or record component, or in an expression in the
corresponding method body. The `RuntimeInvisibleTypeAnnotations`
attribute also stores annotations on type parameter declarations of
generic classes, interfaces, methods, and constructors.

There may be at most one `RuntimeInvisibleTypeAnnotations` attribute in
the `attributes` table of a `ClassFile`, `field_info`, `method_info`, or
`record_component_info` structure, or `Code` attribute.

An `attributes` table contains a `RuntimeInvisibleTypeAnnotations`
attribute only if types are annotated in kinds of declaration or
expression that correspond to the parent structure or attribute of the
`attributes` table.

The `RuntimeInvisibleTypeAnnotations` attribute has the following
format:

``` screen
RuntimeInvisibleTypeAnnotations_attribute {
    u2              attribute_name_index;
    u4              attribute_length;
    u2              num_annotations;
    type_annotation annotations[num_annotations];
}
```

The items of the `RuntimeInvisibleTypeAnnotations_attribute` structure
are as follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure representing the string
"`RuntimeInvisibleTypeAnnotations`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item indicates the length of the
attribute, excluding the initial six bytes.

<span class="term">num_annotations</span>  
The value of the `num_annotations` item gives the number of run-time
invisible type annotations represented by the structure.

<span class="term">annotations\[\]</span>  
Each entry in the `annotations` table represents a single run-time
invisible annotation on a type used in a declaration or expression. The
`type_annotation` structure is specified in
<a href="jvms-4.html#jvms-4.7.20" class="xref"
title="4.7.20. The RuntimeVisibleTypeAnnotations Attribute">§4.7.20</a>.

</div>

</div>

<div id="jvms-4.7.22" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.22. The `AnnotationDefault` Attribute

</div>

</div>

</div>

The `AnnotationDefault` attribute is a variable-length attribute in the
`attributes` table of certain `method_info` structures
(<a href="jvms-4.html#jvms-4.6" class="xref"
title="4.6. Methods">§4.6</a>), namely those representing elements of
annotation interfaces (JLS §9.6.1). The `AnnotationDefault` attribute
records the default value (JLS §9.6.2) for the element represented by
the `method_info` structure.

There may be at most one `AnnotationDefault` attribute in the
`attributes` table of a `method_info` structure which represents an
element of an annotation interface.

The `AnnotationDefault` attribute has the following format:

``` screen
AnnotationDefault_attribute {
    u2            attribute_name_index;
    u4            attribute_length;
    element_value default_value;
}
```

The items of the `AnnotationDefault_attribute` structure are as follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the string "`AnnotationDefault`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item indicates the length of the
attribute, excluding the initial six bytes.

<span class="term">default_value</span>  
The `default_value` item represents the default value of the annotation
interface element represented by the `method_info` structure enclosing
this `AnnotationDefault` attribute.

</div>

</div>

<div id="jvms-4.7.23" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.23. The `BootstrapMethods` Attribute

</div>

</div>

</div>

The `BootstrapMethods` attribute is a variable-length attribute in the
`attributes` table of a `ClassFile` structure
(<a href="jvms-4.html#jvms-4.1" class="xref"
title="4.1. The ClassFile Structure">§4.1</a>). The `BootstrapMethods`
attribute records bootstrap methods used to produce dynamically-computed
constants and dynamically-computed call sites
(<a href="jvms-4.html#jvms-4.4.10" class="xref"
title="4.4.10. The CONSTANT_Dynamic_info and CONSTANT_InvokeDynamic_info Structures">§4.4.10</a>).

There must be exactly one `BootstrapMethods` attribute in the
`attributes` table of a `ClassFile` structure if the `constant_pool`
table of the `ClassFile` structure has at least one
`CONSTANT_Dynamic_info` or `CONSTANT_InvokeDynamic_info` entry.

There may be at most one `BootstrapMethods` attribute in the
`attributes` table of a `ClassFile` structure.

The `BootstrapMethods` attribute has the following format:

``` screen
BootstrapMethods_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 num_bootstrap_methods;
    {   u2 bootstrap_method_ref;
        u2 num_bootstrap_arguments;
        u2 bootstrap_arguments[num_bootstrap_arguments];
    } bootstrap_methods[num_bootstrap_methods];
}
```

The items of the `BootstrapMethods_attribute` structure are as follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the string "`BootstrapMethods`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item indicates the length of the
attribute, excluding the initial six bytes.

<span class="term">num_bootstrap_methods</span>  
The value of the `num_bootstrap_methods` item determines the number of
bootstrap method specifiers in the `bootstrap_methods` array.

<span class="term">bootstrap_methods\[\]</span>  
Each entry in the `bootstrap_methods` table contains an index to a
`CONSTANT_MethodHandle_info` structure which specifies a bootstrap
method, and a sequence (perhaps empty) of indexes to
<span class="emphasis">*static arguments*</span> for the bootstrap
method.

Each `bootstrap_methods` entry must contain the following three items:

<div class="variablelist">

<span class="term">bootstrap_method_ref</span>  
The value of the `bootstrap_method_ref` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_MethodHandle_info` structure
(<a href="jvms-4.html#jvms-4.4.8" class="xref"
title="4.4.8. The CONSTANT_MethodHandle_info Structure">§4.4.8</a>).

The method handle will be resolved during resolution of a
dynamically-computed constant or call site
(<a href="jvms-5.html#jvms-5.4.3.6" class="xref"
title="5.4.3.6. Dynamically-Computed Constant and Call Site Resolution">§5.4.3.6</a>),
and then invoked as if by invocation of `invokeWithArguments` in
`java.lang.invoke.MethodHandle`. The method handle must be able to
accept the array of arguments described in
<a href="jvms-5.html#jvms-5.4.3.6" class="xref"
title="5.4.3.6. Dynamically-Computed Constant and Call Site Resolution">§5.4.3.6</a>,
or resolution will fail.

<span class="term">num_bootstrap_arguments</span>  
The value of the `num_bootstrap_arguments` item gives the number of
items in the `bootstrap_arguments` array.

<span class="term">bootstrap_arguments\[\]</span>  
Each entry in the `bootstrap_arguments` array must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be loadable (<a href="jvms-4.html#jvms-4.4" class="xref"
title="4.4. The Constant Pool">§4.4</a>).

</div>

</div>

</div>

<div id="jvms-4.7.24" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.24. The `MethodParameters` Attribute

</div>

</div>

</div>

The `MethodParameters` attribute is a variable-length attribute in the
`attributes` table of a `method_info` structure
(<a href="jvms-4.html#jvms-4.6" class="xref"
title="4.6. Methods">§4.6</a>). A `MethodParameters` attribute records
information about the formal parameters of a method, such as their
names.

There may be at most one `MethodParameters` attribute in the
`attributes` table of a `method_info` structure.

The `MethodParameters` attribute has the following format:

``` screen
MethodParameters_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u1 parameters_count;
    {   u2 name_index;
        u2 access_flags;
    } parameters[parameters_count];
}
```

The items of the `MethodParameters_attribute` structure are as follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the string "`MethodParameters`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item indicates the length of the
attribute, excluding the initial six bytes.

<span class="term">parameters_count</span>  
The value of the `parameters_count` item indicates the number of
parameter descriptors in the method descriptor
(<a href="jvms-4.html#jvms-4.3.3" class="xref"
title="4.3.3. Method Descriptors">§4.3.3</a>) referenced by the
`descriptor_index` of the attribute's enclosing `method_info` structure.

This is not a constraint which a Java Virtual Machine implementation
must enforce during format checking
(<a href="jvms-4.html#jvms-4.8" class="xref"
title="4.8. Format Checking">§4.8</a>). The task of matching parameter
descriptors in a method descriptor against the items in the `parameters`
array below is done by the reflection libraries of the Java SE Platform.

<span class="term">parameters\[\]</span>  
Each entry in the `parameters` array contains the following pair of
items:

<div class="variablelist">

<span class="term">name_index</span>  
The value of the `name_index` item must either be zero or a valid index
into the `constant_pool` table.

If the value of the `name_index` item is zero, then this `parameters`
element indicates a formal parameter with no name.

If the value of the `name_index` item is nonzero, the `constant_pool`
entry at that index must be a `CONSTANT_Utf8_info` structure
representing a valid unqualified name denoting a formal parameter
(<a href="jvms-4.html#jvms-4.2.2" class="xref"
title="4.2.2. Unqualified Names">§4.2.2</a>).

<span class="term">access_flags</span>  
The value of the `access_flags` item is as follows:

<div class="variablelist">

<span class="term">0x0010 (`ACC_FINAL`)</span>  
Indicates that the formal parameter was declared `final`.

<span class="term">0x1000 (`ACC_SYNTHETIC`)</span>  
Indicates that the formal parameter was not explicitly or implicitly
declared in source code, according to the specification of the language
in which the source code was written (JLS §13.1). (The formal parameter
is an implementation artifact of the compiler which produced this
`class` file.)

<span class="term">0x8000 (`ACC_MANDATED`)</span>  
Indicates that the formal parameter was implicitly declared in source
code, according to the specification of the language in which the source
code was written (JLS §13.1). (The formal parameter is mandated by a
language specification, so all compilers for the language must emit it.)

</div>

</div>

</div>

The <span class="emphasis">*i*</span>'th entry in the `parameters` array
corresponds to the <span class="emphasis">*i*</span>'th parameter
descriptor in the enclosing method's descriptor. (The `parameters_count`
item is one byte because a method descriptor is limited to 255
parameters.) Effectively, this means the `parameters` array stores
information for all the parameters of the method. One could imagine
other schemes, where entries in the `parameters` array specify their
corresponding parameter descriptors, but it would unduly complicate the
`MethodParameters` attribute.

The <span class="emphasis">*i*</span>'th entry in the `parameters` array
may or may not correspond to the <span class="emphasis">*i*</span>'th
type in the enclosing method's `Signature` attribute (if present), or to
the <span class="emphasis">*i*</span>'th annotation in the enclosing
method's parameter annotations.

</div>

<div id="jvms-4.7.25" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.25. The `Module` Attribute

</div>

</div>

</div>

The `Module` attribute is a variable-length attribute in the
`attributes` table of a `ClassFile` structure
(<a href="jvms-4.html#jvms-4.1" class="xref"
title="4.1. The ClassFile Structure">§4.1</a>). The `Module` attribute
indicates the modules required by a module; the packages exported and
opened by a module; and the services used and provided by a module.

There may be at most one `Module` attribute in the `attributes` table of
a `ClassFile` structure.

The `Module` attribute has the following format:

``` screen
Module_attribute {
    u2 attribute_name_index;
    u4 attribute_length;

    u2 module_name_index;
    u2 module_flags;
    u2 module_version_index;

    u2 requires_count;
    {   u2 requires_index;
        u2 requires_flags;
        u2 requires_version_index;
    } requires[requires_count];

    u2 exports_count;
    {   u2 exports_index;
        u2 exports_flags;
        u2 exports_to_count;
        u2 exports_to_index[exports_to_count];
    } exports[exports_count];

    u2 opens_count;
    {   u2 opens_index;
        u2 opens_flags;
        u2 opens_to_count;
        u2 opens_to_index[opens_to_count];
    } opens[opens_count];

    u2 uses_count;
    u2 uses_index[uses_count];

    u2 provides_count;
    {   u2 provides_index;
        u2 provides_with_count;
        u2 provides_with_index[provides_with_count];
    } provides[provides_count];
}
```

The items of the `Module_attribute` structure are as follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the string "`Module`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item indicates the length of the
attribute, excluding the initial six bytes.

<span class="term">module_name_index</span>  
The value of the `module_name_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Module_info` structure
(<a href="jvms-4.html#jvms-4.4.11" class="xref"
title="4.4.11. The CONSTANT_Module_info Structure">§4.4.11</a>) denoting
the current module.

<span class="term">module_flags</span>  
The value of the `module_flags` item is as follows:

<div class="variablelist">

<span class="term">0x0020 (`ACC_OPEN`)</span>  
Indicates that this module is open.

<span class="term">0x1000 (`ACC_SYNTHETIC`)</span>  
Indicates that this module was not explicitly or implicitly declared.

<span class="term">0x8000 (`ACC_MANDATED`)</span>  
Indicates that this module was implicitly declared.

</div>

<span class="term">module_version_index</span>  
The value of the `module_version_index` item must be either zero or a
valid index into the `constant_pool` table. If the value of the item is
zero, then no version information about the current module is present.
If the value of the item is nonzero, then the `constant_pool` entry at
that index must be a `CONSTANT_Utf8_info` structure representing the
version of the current module.

<span class="term">requires_count</span>  
The value of the `requires_count` item indicates the number of entries
in the `requires` table.

If the current module is `java.base`, then `requires_count` must be
zero.

If the current module is not `java.base`, then `requires_count` must be
at least one.

<span class="term">requires\[\]</span>  
Each entry in the `requires` table specifies a dependence of the current
module. The items in each entry are as follows:

<div class="variablelist">

<span class="term">requires_index</span>  
The value of the `requires_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Module_info` structure denoting a module on which the current
module depends.

At most one entry in the `requires` table may specify a module of a
given name with its `requires_index` item.

<span class="term">requires_flags</span>  
The value of the `requires_flags` item is as follows:

<div class="variablelist">

<span class="term">0x0020 (`ACC_TRANSITIVE`)</span>  
Indicates that any module which depends on the current module,
implicitly declares a dependence on the module indicated by this entry.

<span class="term">0x0040 (`ACC_STATIC_PHASE`)</span>  
Indicates that this dependence is mandatory in the static phase, i.e.,
at compile time, but is optional in the dynamic phase, i.e., at run
time.

<span class="term">0x1000 (`ACC_SYNTHETIC`)</span>  
Indicates that this dependence was not explicitly or implicitly declared
in the source of the module declaration.

<span class="term">0x8000 (`ACC_MANDATED`)</span>  
Indicates that this dependence was implicitly declared in the source of
the module declaration.

</div>

<span class="term">requires_version_index</span>  
The value of the `requires_version_index` item must be either zero or a
valid index into the `constant_pool` table. If the value of the item is
zero, then no version information about the dependence is present. If
the value of the item is nonzero, then the `constant_pool` entry at that
index must be a `CONSTANT_Utf8_info` structure representing the version
of the module specified by `requires_index`.

</div>

Unless the current module is `java.base`, exactly one entry in the
`requires` table must have all of the following:

<div class="norm">

- A `requires_index` item that indicates `java.base`.

- A `requires_flags` item that has the `ACC_SYNTHETIC` flag not set.
  (The `ACC_MANDATED` and `ACC_TRANSITIVE` flags may be set.)

- If the `class` file version number is 54.0 or above, a
  `requires_flags` item that has the `ACC_STATIC_PHASE` flag not set.

</div>

<span class="term">exports_count</span>  
The value of the `exports_count` item indicates the number of entries in
the `exports` table.

<span class="term">exports\[\]</span>  
Each entry in the `exports` table specifies a package exported by the
current module, such that `public` and `protected` types in the package,
and their `public` and `protected` members, may be accessed from outside
the current module, possibly from a limited set of "friend" modules.

The items in each entry are as follows:

<div class="variablelist">

<span class="term">exports_index</span>  
The value of the `exports_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Package_info` structure
(<a href="jvms-4.html#jvms-4.4.12" class="xref"
title="4.4.12. The CONSTANT_Package_info Structure">§4.4.12</a>)
representing a package exported by the current module.

At most one entry in the `exports` table may specify a package of a
given name with its `exports_index` item.

<span class="term">exports_flags</span>  
The value of the `exports_flags` item is as follows:

<div class="variablelist">

<span class="term">0x1000 (`ACC_SYNTHETIC`)</span>  
Indicates that this export was not explicitly or implicitly declared in
the source of the module declaration.

<span class="term">0x8000 (`ACC_MANDATED`)</span>  
Indicates that this export was implicitly declared in the source of the
module declaration.

</div>

<span class="term">exports_to_count</span>  
The value of the `exports_to_count` indicates the number of entries in
the `exports_to_index` table.

If `exports_to_count` is zero, then this package is exported by the
current module in an <span class="emphasis">*unqualified*</span>
fashion; code in any other module may access the types and members in
the package.

If `exports_to_count` is nonzero, then this package is exported by the
current module in a <span class="emphasis">*qualified*</span> fashion;
only code in the modules listed in the `exports_to_index` table may
access the types and members in the package.

<span class="term">exports_to_index\[\]</span>  
The value of each entry in the `exports_to_index` table must be a valid
index into the `constant_pool` table. The `constant_pool` entry at that
index must be a `CONSTANT_Module_info` structure denoting a module whose
code can access the types and members in this exported package.

For each entry in the `exports` table, at most one entry in its
`exports_to_index` table may specify a module of a given name.

</div>

<span class="term">opens_count</span>  
The value of the `opens_count` item indicates the number of entries in
the `opens` table.

`opens_count` must be zero if the current module is open.

<span class="term">opens\[\]</span>  
Each entry in the `opens` table specifies a package opened by the
current module, such that all types in the package, and all their
members, may be accessed from outside the current module via the
reflection libraries of the Java SE Platform, possibly from a limited
set of "friend" modules.

The items in each entry are as follows:

<div class="variablelist">

<span class="term">opens_index</span>  
The value of the `opens_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Package_info` structure representing a package opened by the
current module.

At most one entry in the `opens` table may specify a package of a given
name with its `opens_index` item.

<span class="term">opens_flags</span>  
The value of the `opens_flags` item is as follows:

<div class="variablelist">

<span class="term">0x1000 (`ACC_SYNTHETIC`)</span>  
Indicates that this opening was not explicitly or implicitly declared in
the source of the module declaration.

<span class="term">0x8000 (`ACC_MANDATED`)</span>  
Indicates that this opening was implicitly declared in the source of the
module declaration.

</div>

<span class="term">opens_to_count</span>  
The value of the `opens_to_count` indicates the number of entries in the
`opens_to_index` table.

If `opens_to_count` is zero, then this package is opened by the current
module in an <span class="emphasis">*unqualified*</span> fashion; code
in any other module may reflectively access the types and members in the
package.

If `opens_to_count` is nonzero, then this package is opened by the
current module in a <span class="emphasis">*qualified*</span> fashion;
only code in the modules listed in the `opens_to_index` table may
reflectively access the types and members in the package.

<span class="term">opens_to_index\[\]</span>  
The value of each entry in the `opens_to_index` table must be a valid
index into the `constant_pool` table. The `constant_pool` entry at that
index must be a `CONSTANT_Module_info` structure denoting a module whose
code can access the types and members in this opened package.

For each entry in the `opens` table, at most one entry in its
`opens_to_index` table may specify a module of a given name.

</div>

<span class="term">uses_count</span>  
The value of the `uses_count` item indicates the number of entries in
the `uses_index` table.

<span class="term">uses_index\[\]</span>  
The value of each entry in the `uses_index` table must be a valid index
into the `constant_pool` table. The `constant_pool` entry at that index
must be a `CONSTANT_Class_info` structure
(<a href="jvms-4.html#jvms-4.4.1" class="xref"
title="4.4.1. The CONSTANT_Class_info Structure">§4.4.1</a>)
representing a service interface which the current module may discover
via `java.util.ServiceLoader`.

At most one entry in the `uses_index` table may specify a service
interface of a given name.

<span class="term">provides_count</span>  
The value of the `provides_count` item indicates the number of entries
in the `provides` table.

<span class="term">provides\[\]</span>  
Each entry in the `provides` table represents a service implementation
for a given service interface.

The items in each entry are as follows:

<div class="variablelist">

<span class="term">provides_index</span>  
The value of the `provides_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Class_info` structure representing a service interface for
which the current module provides a service implementation.

At most one entry in the `provides` table may specify a service
interface of a given name with its `provides_index` item.

<span class="term">provides_with_count</span>  
The value of the `provides_with_count` indicates the number of entries
in the `provides_with_index` table.

`provides_with_count` must be nonzero.

<span class="term">provides_with_index\[\]</span>  
The value of each entry in the `provides_with_index` table must be a
valid index into the `constant_pool` table. The `constant_pool` entry at
that index must be a `CONSTANT_Class_info` structure representing a
service implementation for the service interface specified by
`provides_index`.

For each entry in the `provides` table, at most one entry in its
`provides_with_index` table may specify a service implementation of a
given name.

</div>

</div>

</div>

<div id="jvms-4.7.26" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.26. The `ModulePackages` Attribute

</div>

</div>

</div>

The `ModulePackages` attribute is a variable-length attribute in the
`attributes` table of a `ClassFile` structure
(<a href="jvms-4.html#jvms-4.1" class="xref"
title="4.1. The ClassFile Structure">§4.1</a>). The `ModulePackages`
attribute indicates all the packages of a module that are exported or
opened by the `Module` attribute, as well as all the packages of the
service implementations recorded in the `Module` attribute. The
`ModulePackages` attribute may also indicate packages in the module that
are neither exported nor opened nor contain service implementations.

There may be at most one `ModulePackages` attribute in the `attributes`
table of a `ClassFile` structure.

The `ModulePackages` attribute has the following format:

``` screen
ModulePackages_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 package_count;
    u2 package_index[package_count];
}
```

The items of the `ModulePackages_attribute` structure are as follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the string "`ModulePackages`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item indicates the length of the
attribute, excluding the initial six bytes.

<span class="term">package_count</span>  
The value of the `package_count` item indicates the number of entries in
the `package_index` table.

<span class="term">package_index\[\]</span>  
The value of each entry in the `package_index` table must be a valid
index into the `constant_pool` table. The `constant_pool` entry at that
index must be a `CONSTANT_Package_info` structure
(<a href="jvms-4.html#jvms-4.4.12" class="xref"
title="4.4.12. The CONSTANT_Package_info Structure">§4.4.12</a>)
representing a package in the current module.

At most one entry in the `package_index` table may specify a package of
a given name.

</div>

</div>

<div id="jvms-4.7.27" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.27. The `ModuleMainClass` Attribute

</div>

</div>

</div>

The `ModuleMainClass` attribute is a fixed-length attribute in the
`attributes` table of a `ClassFile` structure
(<a href="jvms-4.html#jvms-4.1" class="xref"
title="4.1. The ClassFile Structure">§4.1</a>). The `ModuleMainClass`
attribute indicates the main class of a module.

There may be at most one `ModuleMainClass` attribute in the `attributes`
table of a `ClassFile` structure.

The `ModuleMainClass` attribute has the following format:

``` screen
ModuleMainClass_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 main_class_index;
}
```

The items of the `ModuleMainClass_attribute` structure are as follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the string "`ModuleMainClass`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item must be two.

<span class="term">main_class_index</span>  
The value of the `main_class_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Class_info` structure
(<a href="jvms-4.html#jvms-4.4.1" class="xref"
title="4.4.1. The CONSTANT_Class_info Structure">§4.4.1</a>)
representing the main class of the current module.

</div>

</div>

<div id="jvms-4.7.28" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.28. The `NestHost` Attribute

</div>

</div>

</div>

The `NestHost` attribute is a fixed-length attribute in the `attributes`
table of a `ClassFile` structure. The `NestHost` attribute records the
nest host of the nest to which the current class or interface claims to
belong (<a href="jvms-5.html#jvms-5.4.4" class="xref"
title="5.4.4. Access Control">§5.4.4</a>).

There may be at most one `NestHost` attribute in the `attributes` table
of a `ClassFile` structure.

The `NestHost` attribute has the following format:

``` screen
NestHost_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 host_class_index;
}
```

The items of the `NestHost_attribute` structure are as follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the string "`NestHost`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item must be two.

<span class="term">host_class_index</span>  
The value of the `host_class_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Class_info` structure
(<a href="jvms-4.html#jvms-4.4.1" class="xref"
title="4.4.1. The CONSTANT_Class_info Structure">§4.4.1</a>)
representing a class or interface which is the nest host for the current
class or interface.

If the nest host cannot be loaded, or is not in the same run-time
package as the current class or interface, or does not authorize nest
membership for the current class or interface, then an error may occur
during access control (<a href="jvms-5.html#jvms-5.4.4" class="xref"
title="5.4.4. Access Control">§5.4.4</a>).

</div>

</div>

<div id="jvms-4.7.29" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.29. The `NestMembers` Attribute

</div>

</div>

</div>

The `NestMembers` attribute is a variable-length attribute in the
`attributes` table of a `ClassFile` structure
(<a href="jvms-4.html#jvms-4.1" class="xref"
title="4.1. The ClassFile Structure">§4.1</a>). The `NestMembers`
attribute records the classes and interfaces that are authorized to
claim membership in the nest hosted by the current class or interface
(<a href="jvms-5.html#jvms-5.4.4" class="xref"
title="5.4.4. Access Control">§5.4.4</a>).

There may be at most one `NestMembers` attribute in the `attributes`
table of a `ClassFile` structure.

The `attributes` table of a `ClassFile` structure must not contain both
a `NestMembers` attribute and a `NestHost` attribute.

This rule prevents a nest host from claiming membership in a different
nest. It is implicitly a member of the nest that it hosts.

The `NestMembers` attribute has the following format:

``` screen
NestMembers_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 number_of_classes;
    u2 classes[number_of_classes];
}
```

The items of the `NestMembers_attribute` structure are as follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the string "`NestMembers`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item indicates the length of the
attribute, excluding the initial six bytes.

<span class="term">number_of_classes</span>  
The value of the `number_of_classes` item indicates the number of
entries in the `classes` array.

<span class="term">classes\[\]</span>  
Each value in the `classes` array must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Class_info` structure
(<a href="jvms-4.html#jvms-4.4.1" class="xref"
title="4.4.1. The CONSTANT_Class_info Structure">§4.4.1</a>)
representing a class or interface which is a member of the nest hosted
by the current class or interface.

The `classes` array is consulted by access control
(<a href="jvms-5.html#jvms-5.4.4" class="xref"
title="5.4.4. Access Control">§5.4.4</a>). It should consist of
references to other classes and interfaces that are in the same run-time
package and have `NestHost` attributes which reference the current class
or interface. Array items that do not meet these criteria are ignored by
access control.

</div>

</div>

<div id="jvms-4.7.30" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.30. The `Record` Attribute

</div>

</div>

</div>

The `Record` attribute is a variable-length attribute in the
`attributes` table of a `ClassFile` structure
(<a href="jvms-4.html#jvms-4.1" class="xref"
title="4.1. The ClassFile Structure">§4.1</a>). The `Record` attribute
indicates that the current class is a record class (JLS §8.10), and
stores information about the record components of the record class (JLS
§8.10.1).

There may be at most one `Record` attribute in the `attributes` table of
a `ClassFile` structure.

The `Record` attribute has the following format:

``` screen
Record_attribute {
    u2                    attribute_name_index;
    u4                    attribute_length;
    u2                    components_count;
    record_component_info components[components_count];
}
```

The items of the `Record_attribute` structure are as follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the string "`Record`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item indicates the length of the
attribute, excluding the initial six bytes.

<span class="term">components_count</span>  
The value of the `components_count` item indicates the number of entries
in the `components` table.

<span class="term">components\[\]</span>  
Each entry in the `components` table specifies a record component of the
current class, in the order the record components were declared. The
`record_component_info` structure has the following format:

``` screen
record_component_info {
    u2             name_index;
    u2             descriptor_index;
    u2             attributes_count;
    attribute_info attributes[attributes_count];
}
      
```

The items of the `record_component_info` structure are as follows:

<div class="variablelist">

<span class="term">name_index</span>  
The value of the `name_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
a valid unqualified name denoting the record component
(<a href="jvms-4.html#jvms-4.2.2" class="xref"
title="4.2.2. Unqualified Names">§4.2.2</a>).

<span class="term">descriptor_index</span>  
The value of the `descriptor_index` item must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
a field descriptor which encodes the type of the record component
(<a href="jvms-4.html#jvms-4.3.2" class="xref"
title="4.3.2. Field Descriptors">§4.3.2</a>).

<span class="term">attributes_count</span>  
The value of the `attributes_count` item indicates the number of
additional attributes of this record component.

<span class="term">attributes\[\]</span>  
Each value of the `attributes` table must be an `attribute_info`
structure (<a href="jvms-4.html#jvms-4.7" class="xref"
title="4.7. Attributes">§4.7</a>).

A record component can have any number of optional attributes associated
with it.

The attributes defined by this specification as appearing in the
`attributes` table of a `record_component_info` structure are listed in
<a href="jvms-4.html#jvms-4.7-320" class="xref"
title="Table 4.7-C. Predefined class file attributes (by location)">Table 4.7-C</a>.

The rules concerning attributes defined to appear in the `attributes`
table of a `record_component_info` structure are given in
<a href="jvms-4.html#jvms-4.7" class="xref"
title="4.7. Attributes">§4.7</a>.

The rules concerning non-predefined attributes in the `attributes` table
of a `record_component_info` structure are given in
<a href="jvms-4.html#jvms-4.7.1" class="xref"
title="4.7.1. Defining and Naming New Attributes">§4.7.1</a>.

</div>

</div>

</div>

<div id="jvms-4.7.31" class="section">

<div class="titlepage">

<div>

<div>

### 4.7.31. The `PermittedSubclasses` Attribute

</div>

</div>

</div>

The `PermittedSubclasses` attribute is a variable-length attribute in
the `attributes` table of a `ClassFile` structure
(<a href="jvms-4.html#jvms-4.1" class="xref"
title="4.1. The ClassFile Structure">§4.1</a>). The
`PermittedSubclasses` attribute records the classes and interfaces that
are authorized to directly extend or implement the current class or
interface (<a href="jvms-5.html#jvms-5.3.5" class="xref"
title="5.3.5. Deriving a Class from a class File Representation">§5.3.5</a>).

The Java programming language uses the modifier `sealed` to indicate a
class or interface that limits its direct subclasses or direct
subinterfaces. One might suppose that this modifier would correspond to
an `ACC_SEALED` flag in a `class` file, since the related modifier
`final` corresponds to the `ACC_FINAL` flag. In fact, a `sealed` class
or interface is indicated in a `class` file by the presence of the
`PermittedSubclasses` attribute.

There may be at most one `PermittedSubclasses` attribute in the
`attributes` table of a `ClassFile` structure whose `access_flags` item
does not have the `ACC_FINAL` flag set.

There must be no `PermittedSubclasses` attribute in the `attributes`
table of a `ClassFile` structure whose `access_flags` item has the
`ACC_FINAL` flag set.

`sealed` is distinct from `final`: a `sealed` class has a list of
authorized subclasses, which a `final` class has no subclasses. Thus, a
`ClassFile` structure may have a `PermittedSubclasses` attribute, or
have its `ACC_FINAL` flag set, but not both.

The `PermittedSubclasses` attribute has the following format:

``` screen
PermittedSubclasses_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 number_of_classes;
    u2 classes[number_of_classes];
}
```

The items of the `PermittedSubclasses_attribute` structure are as
follows:

<div class="variablelist">

<span class="term">attribute_name_index</span>  
The value of the `attribute_name_index` item must be a valid index into
the `constant_pool` table. The `constant_pool` entry at that index must
be a `CONSTANT_Utf8_info` structure
(<a href="jvms-4.html#jvms-4.4.7" class="xref"
title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>) representing
the string "`PermittedSubclasses`".

<span class="term">attribute_length</span>  
The value of the `attribute_length` item indicates the length of the
attribute, excluding the initial six bytes.

<span class="term">number_of_classes</span>  
The value of the `number_of_classes` item indicates the number of
entries in the `classes` array.

<span class="term">classes\[\]</span>  
Each value in the `classes` array must be a valid index into the
`constant_pool` table. The `constant_pool` entry at that index must be a
`CONSTANT_Class_info` structure
(<a href="jvms-4.html#jvms-4.4.1" class="xref"
title="4.4.1. The CONSTANT_Class_info Structure">§4.4.1</a>)
representing a class or interface which is authorized to directly extend
or implement the current class or interface.

The `classes` array is consulted when a class or interface is created
that attempts to directly extend or implement the current class or
interface (<a href="jvms-5.html#jvms-5.3.5" class="xref"
title="5.3.5. Deriving a Class from a class File Representation">§5.3.5</a>).
Array items that represent classes or interfaces which do not attempt to
directly extend or implement the current class or interface are ignored.

</div>

</div>

</div>

<div id="jvms-4.8" class="section">

<div class="titlepage">

<div>

<div>

## 4.8. Format Checking

</div>

</div>

</div>

When a prospective `class` file is loaded by the Java Virtual Machine
(<a href="jvms-5.html#jvms-5.3" class="xref"
title="5.3. Creation and Loading">§5.3</a>), the Java Virtual Machine
first ensures that the file has the basic format of a `class` file
(<a href="jvms-4.html#jvms-4.1" class="xref"
title="4.1. The ClassFile Structure">§4.1</a>). This process is known as
<span class="emphasis">*format checking*</span>. The checks are as
follows:

<div class="norm">

- The first four bytes must contain the right magic number.

- All predefined attributes (<a href="jvms-4.html#jvms-4.7" class="xref"
  title="4.7. Attributes">§4.7</a>) must be of the proper length, except
  for `StackMapTable`, `RuntimeVisibleAnnotations`,
  `RuntimeInvisibleAnnotations`, `RuntimeVisibleParameterAnnotations`,
  `RuntimeInvisibleParameterAnnotations`,
  `RuntimeVisibleTypeAnnotations`, `RuntimeInvisibleTypeAnnotations`,
  and `AnnotationDefault`.

- The `class` file must not be truncated or have extra bytes at the end.

- The constant pool must satisfy the constraints documented throughout
  <a href="jvms-4.html#jvms-4.4" class="xref"
  title="4.4. The Constant Pool">§4.4</a>.

  For example, each `CONSTANT_Class_info` structure in the constant pool
  must contain in its `name_index` item a valid constant pool index for
  a `CONSTANT_Utf8_info` structure.

- All field references and method references in the constant pool must
  have valid names, valid classes, and valid descriptors
  (<a href="jvms-4.html#jvms-4.3" class="xref"
  title="4.3. Descriptors">§4.3</a>).

  Format checking does not ensure that the given field or method
  actually exists in the given class, nor that the descriptors given
  refer to real classes. Format checking ensures only that these items
  are well formed. More detailed checking is performed when the
  bytecodes themselves are verified, and during resolution.

</div>

These checks for basic `class` file integrity are necessary for any
interpretation of the `class` file contents. Format checking is distinct
from bytecode verification, although historically they have been
confused because both are a form of integrity check.

</div>

<div id="jvms-4.9" class="section">

<div class="titlepage">

<div>

<div>

## 4.9. Constraints on Java Virtual Machine Code

</div>

</div>

</div>

The code for a method, instance initialization method
(<a href="jvms-2.html#jvms-2.9.1" class="xref"
title="2.9.1. Instance Initialization Methods">§2.9.1</a>), or class or
interface initialization method
(<a href="jvms-2.html#jvms-2.9.2" class="xref"
title="2.9.2. Class Initialization Methods">§2.9.2</a>) is stored in the
`code` array of the `Code` attribute of a `method_info` structure of a
`class` file (<a href="jvms-4.html#jvms-4.7.3" class="xref"
title="4.7.3. The Code Attribute">§4.7.3</a>). This section describes
the constraints associated with the contents of the `Code_attribute`
structure.

<div id="jvms-4.9.1" class="section">

<div class="titlepage">

<div>

<div>

### 4.9.1. Static Constraints

</div>

</div>

</div>

The <span class="emphasis">*static constraints*</span> on a `class` file
are those defining the well-formedness of the file. These constraints
have been given in the previous sections, except for static constraints
on the code in the `class` file. The static constraints on the code in a
`class` file specify how Java Virtual Machine instructions must be laid
out in the `code` array and what the operands of individual instructions
must be.

The static constraints on the instructions in the `code` array are as
follows:

<div class="norm">

- Only instances of the instructions documented in
  <a href="jvms-6.html#jvms-6.5" class="xref"
  title="6.5. Instructions">§6.5</a> may appear in the `code` array.
  Instances of instructions using the reserved opcodes
  (<a href="jvms-6.html#jvms-6.2" class="xref"
  title="6.2. Reserved Opcodes">§6.2</a>) or any opcodes not documented
  in this specification must not appear in the `code` array.

  If the `class` file version number is 51.0 or above, then instances of
  instructions using the <span class="emphasis">*jsr*</span>,
  <span class="emphasis">*jsr_w*</span>, or
  <span class="emphasis">*ret*</span> opcodes must not appear in the
  `code` array.

- The opcode of the first instruction in the `code` array begins at
  index `0`.

- For each instruction in the `code` array except the last, the index of
  the opcode of the next instruction equals the index of the opcode of
  the current instruction plus the length of that instruction, including
  all its operands.

  The <span class="emphasis">*wide*</span> instruction is treated like
  any other instruction for these purposes; the opcode specifying the
  operation that a <span class="emphasis">*wide*</span> instruction is
  to modify is treated as one of the operands of that
  <span class="emphasis">*wide*</span> instruction. That opcode must
  never be directly reachable by the computation.

- The last byte of the last instruction in the `code` array must be the
  byte at index `code_length - 1`.

</div>

The static constraints on the operands of instructions in the `code`
array are as follows:

<div class="norm">

- The target of each jump and branch instruction
  (<span class="emphasis">*jsr*</span>,
  <span class="emphasis">*jsr_w*</span>,
  <span class="emphasis">*goto*</span>,
  <span class="emphasis">*goto_w*</span>,
  <span class="emphasis">*ifeq*</span>,
  <span class="emphasis">*ifne*</span>,
  <span class="emphasis">*ifle*</span>,
  <span class="emphasis">*iflt*</span>,
  <span class="emphasis">*ifge*</span>,
  <span class="emphasis">*ifgt*</span>,
  <span class="emphasis">*ifnull*</span>,
  <span class="emphasis">*ifnonnull*</span>,
  <span class="emphasis">*if_icmpeq*</span>,
  <span class="emphasis">*if_icmpne*</span>,
  <span class="emphasis">*if_icmple*</span>,
  <span class="emphasis">*if_icmplt*</span>,
  <span class="emphasis">*if_icmpge*</span>,
  <span class="emphasis">*if_icmpgt*</span>,
  <span class="emphasis">*if_acmpeq*</span>,
  <span class="emphasis">*if_acmpne*</span>) must be the opcode of an
  instruction within this method.

  The target of a jump or branch instruction must never be the opcode
  used to specify the operation to be modified by a
  <span class="emphasis">*wide*</span> instruction; a jump or branch
  target may be the <span class="emphasis">*wide*</span> instruction
  itself.

- Each target, including the default, of each
  <span class="emphasis">*tableswitch*</span> instruction must be the
  opcode of an instruction within this method.

  Each <span class="emphasis">*tableswitch*</span> instruction must have
  a number of entries in its jump table that is consistent with the
  value of its <span class="emphasis">*low*</span> and
  <span class="emphasis">*high*</span> jump table operands, and its
  <span class="emphasis">*low*</span> value must be less than or equal
  to its <span class="emphasis">*high*</span> value.

  No target of a <span class="emphasis">*tableswitch*</span> instruction
  may be the opcode used to specify the operation to be modified by a
  <span class="emphasis">*wide*</span> instruction; a
  <span class="emphasis">*tableswitch*</span> target may be a
  <span class="emphasis">*wide*</span> instruction itself.

- Each target, including the default, of each
  <span class="emphasis">*lookupswitch*</span> instruction must be the
  opcode of an instruction within this method.

  Each <span class="emphasis">*lookupswitch*</span> instruction must
  have a number of <span class="emphasis">*match-offset*</span> pairs
  that is consistent with the value of its
  <span class="emphasis">*npairs*</span> operand. The
  <span class="emphasis">*match-offset*</span> pairs must be sorted in
  increasing numerical order by signed match value.

  No target of a <span class="emphasis">*lookupswitch*</span>
  instruction may be the opcode used to specify the operation to be
  modified by a <span class="emphasis">*wide*</span> instruction; a
  <span class="emphasis">*lookupswitch*</span> target may be a
  <span class="emphasis">*wide*</span> instruction itself.

- The operands of each <span class="emphasis">*ldc*</span> instruction
  and each <span class="emphasis">*ldc_w*</span> instruction must
  represent a valid index into the `constant_pool` table. The constant
  pool entry referenced by that index must be loadable
  (<a href="jvms-4.html#jvms-4.4" class="xref"
  title="4.4. The Constant Pool">§4.4</a>), and not any of the
  following:

  <div class="norm">

  - An entry of kind `CONSTANT_Long` or `CONSTANT_Double`.

  - An entry of kind `CONSTANT_Dynamic` that references a
    `CONSTANT_NameAndType_info` structure which indicates a descriptor
    of `J` (denoting `long`) or `D` (denoting `double`).

  </div>

- The operands of each <span class="emphasis">*ldc2_w*</span>
  instruction must represent a valid index into the `constant_pool`
  table. The constant pool entry referenced by that index must be
  loadable, and in particular one of the following:

  <div class="norm">

  - An entry of kind `CONSTANT_Long` or `CONSTANT_Double`.

  - An entry of kind `CONSTANT_Dynamic` that references a
    `CONSTANT_NameAndType_info` structure which indicates a descriptor
    of `J` (denoting `long`) or `D` (denoting `double`).

  </div>

  The subsequent constant pool index must also be a valid index into the
  constant pool, and the constant pool entry at that index must not be
  used.

- The operands of each <span class="emphasis">*getfield*</span>,
  <span class="emphasis">*putfield*</span>,
  <span class="emphasis">*getstatic*</span>, and
  <span class="emphasis">*putstatic*</span> instruction must represent a
  valid index into the `constant_pool` table. The constant pool entry
  referenced by that index must be of kind `CONSTANT_Fieldref`.

- The <span class="emphasis">*indexbyte*</span> operands of each
  <span class="emphasis">*invokevirtual*</span> instruction must
  represent a valid index into the `constant_pool` table. The constant
  pool entry referenced by that index must be of kind
  `CONSTANT_Methodref`.

- The <span class="emphasis">*indexbyte*</span> operands of each
  <span class="emphasis">*invokespecial*</span> and
  <span class="emphasis">*invokestatic*</span> instruction must
  represent a valid index into the `constant_pool` table. If the `class`
  file version number is less than 52.0, the constant pool entry
  referenced by that index must be of kind `CONSTANT_Methodref`; if the
  `class` file version number is 52.0 or above, the constant pool entry
  referenced by that index must be of kind `CONSTANT_Methodref` or
  `CONSTANT_InterfaceMethodref`.

- The <span class="emphasis">*indexbyte*</span> operands of each
  <span class="emphasis">*invokeinterface*</span> instruction must
  represent a valid index into the `constant_pool` table. The constant
  pool entry referenced by that index must be of kind
  `CONSTANT_InterfaceMethodref`.

  The value of the <span class="emphasis">*count*</span> operand of each
  <span class="emphasis">*invokeinterface*</span> instruction must
  reflect the number of local variables necessary to store the arguments
  to be passed to the interface method, as implied by the descriptor of
  the `CONSTANT_NameAndType_info` structure referenced by the
  `CONSTANT_InterfaceMethodref` constant pool entry.

  The fourth operand byte of each
  <span class="emphasis">*invokeinterface*</span> instruction must have
  the value zero.

- The <span class="emphasis">*indexbyte*</span> operands of each
  <span class="emphasis">*invokedynamic*</span> instruction must
  represent a valid index into the `constant_pool` table. The constant
  pool entry referenced by that index must be of kind
  `CONSTANT_InvokeDynamic`.

  The third and fourth operand bytes of each
  <span class="emphasis">*invokedynamic*</span> instruction must have
  the value zero.

- Only the <span class="emphasis">*invokespecial*</span> instruction is
  allowed to invoke an instance initialization method
  (<a href="jvms-2.html#jvms-2.9.1" class="xref"
  title="2.9.1. Instance Initialization Methods">§2.9.1</a>).

  No other method whose name begins with the character '`<`'
  ('`\u003c`') may be called by the method invocation instructions. In
  particular, the class or interface initialization method specially
  named `<clinit>` is never called explicitly from Java Virtual Machine
  instructions, but only implicitly by the Java Virtual Machine itself.

- The operands of each <span class="emphasis">*instanceof*</span>,
  <span class="emphasis">*checkcast*</span>,
  <span class="emphasis">*new*</span>, and
  <span class="emphasis">*anewarray*</span> instruction, and the
  <span class="emphasis">*indexbyte*</span> operands of each
  <span class="emphasis">*multianewarray*</span> instruction, must
  represent a valid index into the `constant_pool` table. The constant
  pool entry referenced by that index must be of kind `CONSTANT_Class`.

- No <span class="emphasis">*new*</span> instruction may reference a
  constant pool entry of kind `CONSTANT_Class` that represents an array
  type (<a href="jvms-4.html#jvms-4.3.2" class="xref"
  title="4.3.2. Field Descriptors">§4.3.2</a>). The
  <span class="emphasis">*new*</span> instruction cannot be used to
  create an array.

- No <span class="emphasis">*anewarray*</span> instruction may be used
  to create an array of more than 255 dimensions.

- A <span class="emphasis">*multianewarray*</span> instruction must be
  used only to create an array of a type that has at least as many
  dimensions as the value of its
  <span class="emphasis">*dimensions*</span> operand. That is, while a
  <span class="emphasis">*multianewarray*</span> instruction is not
  required to create all of the dimensions of the array type referenced
  by its <span class="emphasis">*indexbyte*</span> operands, it must not
  attempt to create more dimensions than are in the array type.

  The <span class="emphasis">*dimensions*</span> operand of each
  <span class="emphasis">*multianewarray*</span> instruction must not be
  zero.

- The <span class="emphasis">*atype*</span> operand of each
  <span class="emphasis">*newarray*</span> instruction must take one of
  the values `T_BOOLEAN` (4), `T_CHAR` (5), `T_FLOAT` (6), `T_DOUBLE`
  (7), `T_BYTE` (8), `T_SHORT` (9), `T_INT` (10), or `T_LONG` (11).

- The <span class="emphasis">*index*</span> operand of each
  <span class="emphasis">*iload*</span>,
  <span class="emphasis">*fload*</span>,
  <span class="emphasis">*aload*</span>,
  <span class="emphasis">*istore*</span>,
  <span class="emphasis">*fstore*</span>,
  <span class="emphasis">*astore*</span>,
  <span class="emphasis">*iinc*</span>, and
  <span class="emphasis">*ret*</span> instruction must be a non-negative
  integer no greater than `max_locals - 1`.

  The implicit index of each
  <span class="emphasis">*iload\_\<n\>*</span>,
  <span class="emphasis">*fload\_\<n\>*</span>,
  <span class="emphasis">*aload\_\<n\>*</span>,
  <span class="emphasis">*istore\_\<n\>*</span>,
  <span class="emphasis">*fstore\_\<n\>*</span>, and
  <span class="emphasis">*astore\_\<n\>*</span> instruction must be no
  greater than `max_locals - 1`.

- The <span class="emphasis">*index*</span> operand of each
  <span class="emphasis">*lload*</span>,
  <span class="emphasis">*dload*</span>,
  <span class="emphasis">*lstore*</span>, and
  <span class="emphasis">*dstore*</span> instruction must be no greater
  than `max_locals - 2`.

  The implicit index of each
  <span class="emphasis">*lload\_\<n\>*</span>,
  <span class="emphasis">*dload\_\<n\>*</span>,
  <span class="emphasis">*lstore\_\<n\>*</span>, and
  <span class="emphasis">*dstore\_\<n\>*</span> instruction must be no
  greater than `max_locals - 2`.

- The <span class="emphasis">*indexbyte*</span> operands of each
  <span class="emphasis">*wide*</span> instruction modifying an
  <span class="emphasis">*iload*</span>,
  <span class="emphasis">*fload*</span>,
  <span class="emphasis">*aload*</span>,
  <span class="emphasis">*istore*</span>,
  <span class="emphasis">*fstore*</span>,
  <span class="emphasis">*astore*</span>,
  <span class="emphasis">*iinc*</span>, or
  <span class="emphasis">*ret*</span> instruction must represent a
  non-negative integer no greater than `max_locals - 1`.

  The <span class="emphasis">*indexbyte*</span> operands of each
  <span class="emphasis">*wide*</span> instruction modifying an
  <span class="emphasis">*lload*</span>,
  <span class="emphasis">*dload*</span>,
  <span class="emphasis">*lstore*</span>, or
  <span class="emphasis">*dstore*</span> instruction must represent a
  non-negative integer no greater than `max_locals - 2`.

</div>

</div>

<div id="jvms-4.9.2" class="section">

<div class="titlepage">

<div>

<div>

### 4.9.2. Structural Constraints

</div>

</div>

</div>

The structural constraints on the `code` array specify constraints on
relationships between Java Virtual Machine instructions. The structural
constraints are as follows:

<div class="norm">

- Each instruction must only be executed with the appropriate type and
  number of arguments in the operand stack and local variable array,
  regardless of the execution path that leads to its invocation.

  As noted in <a href="jvms-2.html#jvms-2.3.4" class="xref"
  title="2.3.4. The boolean Type">§2.3.4</a> and
  <a href="jvms-2.html#jvms-2.11.1" class="xref"
  title="2.11.1. Types and the Java Virtual Machine">§2.11.1</a>, the
  Java Virtual Machine implicitly converts values of types `boolean`,
  `byte`, `short`, and `char` to type `int`, allowing instructions
  expecting values of type `int` to operate on them.

- If an instruction can be executed along several different execution
  paths, the operand stack must have the same depth
  (<a href="jvms-2.html#jvms-2.6.2" class="xref"
  title="2.6.2. Operand Stacks">§2.6.2</a>) prior to the execution of
  the instruction, regardless of the path taken.

- At no point during execution can the operand stack grow to a depth
  greater than that implied by the `max_stack` item.

- At no point during execution can more values be popped from the
  operand stack than it contains.

- At no point during execution can the order of the local variable pair
  holding a value of type `long` or `double` be reversed or the pair
  split up. At no point can the local variables of such a pair be
  operated on individually.

- No local variable (or local variable pair, in the case of a value of
  type `long` or `double`) can be accessed before it is assigned a
  value.

- Each <span class="emphasis">*invokespecial*</span> instruction must
  name one of the following:

  <div class="norm">

  - an instance initialization method
    (<a href="jvms-2.html#jvms-2.9.1" class="xref"
    title="2.9.1. Instance Initialization Methods">§2.9.1</a>)

  - a method in the current class or interface

  - a method in a superclass of the current class

  - a method in a direct superinterface of the current class or
    interface

  - a method in `Object`

  </div>

  If an <span class="emphasis">*invokespecial*</span> instruction names
  an instance initialization method, then the target reference on the
  operand stack must be an uninitialized class instance. An instance
  initialization method must never be invoked on an initialized class
  instance. In addition:

  <div class="norm">

  - If the target reference on the operand stack is
    <span class="emphasis">*an uninitialized class instance for the
    current class*</span>, then
    <span class="emphasis">*invokespecial*</span> must name an instance
    initialization method from the current class or its direct
    superclass.

  - If the target reference on the operand stack is
    <span class="emphasis">*a class instance created by an earlier
    <span class="emphasis">*new*</span> instruction*</span>, then
    <span class="emphasis">*invokespecial*</span> must name an instance
    initialization method from the class of that class instance.

  - In either case, if the instruction is covered by an exception
    handler, then any copy of the target reference stored in a local
    variable must be treated as unusable by the exception handler code.

  </div>

  If an <span class="emphasis">*invokespecial*</span> instruction names
  a method which is not an instance initialization method, then the
  target reference on the operand stack must be a class instance whose
  type is assignment compatible with the current class (JLS §5.2).

  The general rule for <span class="emphasis">*invokespecial*</span> is
  that the class or interface named by
  <span class="emphasis">*invokespecial*</span> must be be "above" the
  caller class or interface, while the receiver object targeted by
  <span class="emphasis">*invokespecial*</span> must be "at" or "below"
  the caller class or interface. The latter clause is especially
  important: a class or interface can only perform invokespecial on its
  own objects. See
  <a href="jvms-4.html#jvms-4.10.1.9.invokespecial" class="xref"
  title="invokespecial">§<span
  class="emphasis"><em>invokespecial</em></span></a> for an explanation
  of how the latter clause is implemented in Prolog.

- Each instance initialization method, except for the instance
  initialization method derived from the constructor of class `Object`,
  must call either another instance initialization method of `this` or
  an instance initialization method of its direct superclass `super`
  before its instance members are
  <span class="emphasis">*accessed*</span>, and before the calling
  instance initialization method returns.

  However, instance fields of `this` that are declared in the current
  class may be <span class="emphasis">*assigned*</span> by
  <span class="emphasis">*putfield*</span> before calling any instance
  initialization method.

- When any instance method is invoked or when any instance variable is
  accessed, the class instance that contains the instance method or
  instance variable must already be initialized.

- There must never be an uninitialized class instance on the operand
  stack or in a local variable when a
  <span class="emphasis">*jsr*</span> or
  <span class="emphasis">*jsr_w*</span> instruction is executed.

- The type of every class instance that is the target of a method
  invocation instruction (that is, the type of the target reference on
  the operand stack) must be assignment compatible with the class or
  interface type specified in the instruction.

- The types of the arguments to each method invocation must be method
  invocation compatible with the method descriptor (JLS §5.3,
  <a href="jvms-4.html#jvms-4.3.3" class="xref"
  title="4.3.3. Method Descriptors">§4.3.3</a>).

- Each return instruction must match its method's return type:

  <div class="norm">

  - If the method returns a `boolean`, `byte`, `char`, `short`, or
    `int`, only the <span class="emphasis">*ireturn*</span> instruction
    may be used.

  - If the method returns a `float`, `long`, or `double`, only an
    <span class="emphasis">*freturn*</span>,
    <span class="emphasis">*lreturn*</span>, or
    <span class="emphasis">*dreturn*</span> instruction, respectively,
    may be used.

  - If the method returns a `reference` type, only an
    <span class="emphasis">*areturn*</span> instruction may be used, and
    the type of the returned value must be assignment compatible with
    the return descriptor of the method
    (<a href="jvms-4.html#jvms-4.3.3" class="xref"
    title="4.3.3. Method Descriptors">§4.3.3</a>).

  - All instance initialization methods, class or interface
    initialization methods, and methods declared to return `void` must
    use only the <span class="emphasis">*return*</span> instruction.

  </div>

- The type of every class instance accessed by a
  <span class="emphasis">*getfield*</span> instruction or modified by a
  <span class="emphasis">*putfield*</span> instruction (that is, the
  type of the target reference on the operand stack) must be assignment
  compatible with the class type specified in the instruction.

- The type of every value stored by a
  <span class="emphasis">*putfield*</span> or
  <span class="emphasis">*putstatic*</span> instruction must be
  compatible with the descriptor of the field
  (<a href="jvms-4.html#jvms-4.3.2" class="xref"
  title="4.3.2. Field Descriptors">§4.3.2</a>) of the class instance or
  class being stored into:

  <div class="norm">

  - If the descriptor type is `boolean`, `byte`, `char`, `short`, or
    `int`, then the value must be an `int`.

  - If the descriptor type is `float`, `long`, or `double`, then the
    value must be a `float`, `long`, or `double`, respectively.

  - If the descriptor type is a `reference` type, then the value must be
    of a type that is assignment compatible with the descriptor type.

  </div>

- The type of every value stored into an array by an
  <span class="emphasis">*aastore*</span> instruction must be a
  `reference` type.

  The component type of the array being stored into by the
  <span class="emphasis">*aastore*</span> instruction must also be a
  `reference` type.

- Each <span class="emphasis">*athrow*</span> instruction must throw
  only values that are instances of class `Throwable` or of subclasses
  of `Throwable`.

  Each class mentioned in a `catch_type` item of the `exception_table`
  array of the method's `Code_attribute` structure must be `Throwable`
  or a subclass of `Throwable`.

- If <span class="emphasis">*getfield*</span> or
  <span class="emphasis">*putfield*</span> is used to access a
  `protected` field declared in a superclass that is a member of a
  different run-time package than the current class, then the type of
  the class instance being accessed (that is, the type of the target
  reference on the operand stack) must be assignment compatible with the
  current class.

  If <span class="emphasis">*invokevirtual*</span> or
  <span class="emphasis">*invokespecial*</span> is used to access a
  `protected` method declared in a superclass that is a member of a
  different run-time package than the current class, then the type of
  the class instance being accessed (that is, the type of the target
  reference on the operand stack) must be assignment compatible with the
  current class.

- Execution never falls off the bottom of the `code` array.

- No return address (a value of type `returnAddress`) may be loaded from
  a local variable.

- The instruction following each <span class="emphasis">*jsr*</span> or
  <span class="emphasis">*jsr_w*</span> instruction may be returned to
  only by a single <span class="emphasis">*ret*</span> instruction.

- No <span class="emphasis">*jsr*</span> or
  <span class="emphasis">*jsr_w*</span> instruction that is returned to
  may be used to recursively call a subroutine if that subroutine is
  already present in the subroutine call chain. (Subroutines can be
  nested when using `try`-`finally` constructs from within a `finally`
  clause.)

- Each instance of type `returnAddress` can be returned to at most once.

  If a <span class="emphasis">*ret*</span> instruction returns to a
  point in the subroutine call chain above the
  <span class="emphasis">*ret*</span> instruction corresponding to a
  given instance of type `returnAddress`, then that instance can never
  be used as a return address.

</div>

</div>

</div>

<div id="jvms-4.10" class="section">

<div class="titlepage">

<div>

<div>

## 4.10. Verification of `class` Files

</div>

</div>

</div>

Even though a compiler for the Java programming language must only
produce `class` files that satisfy all the static and structural
constraints in the previous sections, the Java Virtual Machine has no
guarantee that any file it is asked to load was generated by that
compiler or is properly formed. Applications such as web browsers do not
download source code, which they then compile; these applications
download already-compiled `class` files. The browser needs to determine
whether the `class` file was produced by a trustworthy compiler or by an
adversary attempting to exploit the Java Virtual Machine.

An additional problem with compile-time checking is version skew. A user
may have successfully compiled a class, say `PurchaseStockOptions`, to
be a subclass of `TradingClass`. But the definition of `TradingClass`
might have changed since the time the class was compiled in a way that
is not compatible with pre-existing binaries. Methods might have been
deleted or had their return types or modifiers changed. Fields might
have changed types or changed from instance variables to class
variables. The access modifiers of a method or variable may have changed
from `public` to `private`. For a discussion of these issues, see
Chapter 13, "Binary Compatibility," in *The Java Language Specification,
Java SE 26 Edition*.

Because of these potential problems, the Java Virtual Machine needs to
verify for itself that the desired constraints are satisfied by the
`class` files it attempts to incorporate. A Java Virtual Machine
implementation verifies that each `class` file satisfies the necessary
constraints at linking time (<a href="jvms-5.html#jvms-5.4" class="xref"
title="5.4. Linking">§5.4</a>).

Link-time verification enhances the performance of the run-time
interpreter. Expensive checks that would otherwise have to be performed
to verify constraints at run time for each interpreted instruction can
be eliminated. The Java Virtual Machine can assume that these checks
have already been performed. For example, the Java Virtual Machine will
already know the following:

<div class="norm">

- There are no operand stack overflows or underflows.

- All local variable uses and stores are valid.

- The arguments to all the Java Virtual Machine instructions are of
  valid types.

</div>

There are two strategies that Java Virtual Machine implementations may
use for verification:

<div class="norm">

- Verification by type checking must be used to verify `class` files
  whose version number is greater than or equal to 50.0.

- Verification by type inference must be supported by all Java Virtual
  Machine implementations, except those conforming to the Java ME CLDC
  and Java Card profiles, in order to verify `class` files whose version
  number is less than 50.0.

  Verification on Java Virtual Machine implementations supporting the
  Java ME CLDC and Java Card profiles is governed by their respective
  specifications.

</div>

<div id="jvms-4.10.1" class="section">

<div class="titlepage">

<div>

<div>

### 4.10.1. Verification by Type Checking

</div>

</div>

</div>

A `class` file whose version number is 50.0 or above
(<a href="jvms-4.html#jvms-4.1" class="xref"
title="4.1. The ClassFile Structure">§4.1</a>) must be verified using
the type checking rules given in this section.

If, and only if, a `class` file's version number equals 50.0, then if
the type checking fails, a Java Virtual Machine implementation may
choose to attempt to perform verification by type inference
(<a href="jvms-4.html#jvms-4.10.2" class="xref"
title="4.10.2. Verification by Type Inference">§4.10.2</a>).

This is a pragmatic adjustment, designed to ease the transition to the
new verification discipline. Many tools that manipulate `class` files
may alter the bytecodes of a method in a manner that requires adjustment
of the method's stack map frames. If a tool does not make the necessary
adjustments to the stack map frames, type checking may fail even though
the bytecode is in principle valid (and would consequently verify under
the old type inference scheme). To allow implementors time to adapt
their tools, Java Virtual Machine implementations may fall back to the
older verification discipline, but only for a limited time.

In cases where type checking fails but type inference is invoked and
succeeds, a certain performance penalty is expected. Such a penalty is
unavoidable. It also should serve as a signal to tool vendors that their
output needs to be adjusted, and provides vendors with additional
incentive to make these adjustments.

In summary, failover to verification by type inference supports both the
gradual addition of stack map frames to the Java SE Platform (if they
are not present in a version 50.0 `class` file, failover is allowed) and
the gradual removal of the <span class="emphasis">*jsr*</span> and
<span class="emphasis">*jsr_w*</span> instructions from the Java SE
Platform (if they are present in a version 50.0 `class` file, failover
is allowed).

If a Java Virtual Machine implementation ever attempts to perform
verification by type inference on version 50.0 class files, it must do
so in all cases where verification by type checking fails.

This means that a Java Virtual Machine implementation cannot choose to
resort to type inference in one case and not in another. It must either
reject `class` files that do not verify via type checking, or else
consistently failover to the type inferencing verifier whenever type
checking fails.

The type checker enforces type rules that are specified by means of
Prolog clauses. English language text is used to describe the type rules
in an informal way, while the Prolog clauses provide a formal
specification.

The type checker requires a list of stack map frames for each method
with a `Code` attribute (<a href="jvms-4.html#jvms-4.7.3" class="xref"
title="4.7.3. The Code Attribute">§4.7.3</a>). A list of stack map
frames is given by the `StackMapTable` attribute
(<a href="jvms-4.html#jvms-4.7.4" class="xref"
title="4.7.4. The StackMapTable Attribute">§4.7.4</a>) of a `Code`
attribute. The intent is that a stack map frame must appear at the
beginning of each basic block in a method. The stack map frame specifies
the verification type of each operand stack entry and of each local
variable at the start of each basic block. The type checker reads the
stack map frames for each method with a `Code` attribute and uses these
maps to generate a proof of the type safety of the instructions in the
`Code` attribute.

The Prolog predicate `methodIsTypeSafe`
(<a href="jvms-4.html#jvms-4.10.1.5" class="xref"
title="4.10.1.5. Type Checking Methods">§4.10.1.5</a>) determines
whether a method with a `Code` attribute is type safe. If a method with
a `Code` attribute is not type safe, verification throws a `VerifyError`
to indicate that the class file is malformed.

If, for a given class, every method with a `Code` attribute passes the
`methodIsTypeSafe` check, the `class` file has type checked successfully
and bytecode verification has completed successfully.

The rest of this section explains the process of type checking in
detail:

<div class="norm">

- First, we give Prolog predicates for core Java Virtual Machine
  artifacts like classes and methods
  (<a href="jvms-4.html#jvms-4.10.1.1" class="xref"
  title="4.10.1.1. Accessors for Java Virtual Machine Artifacts">§4.10.1.1</a>).

- Second, we specify the type system known to the type checker
  (<a href="jvms-4.html#jvms-4.10.1.2" class="xref"
  title="4.10.1.2. Verification Type System">§4.10.1.2</a>).

- Third, we specify the Prolog representation of instructions and stack
  map frames (<a href="jvms-4.html#jvms-4.10.1.3" class="xref"
  title="4.10.1.3. Instruction Representation">§4.10.1.3</a>,
  <a href="jvms-4.html#jvms-4.10.1.4" class="xref"
  title="4.10.1.4. Stack Map Frames and Type Transitions">§4.10.1.4</a>).

- Fourth, we specify how a method is type checked
  (<a href="jvms-4.html#jvms-4.10.1.5" class="xref"
  title="4.10.1.5. Type Checking Methods">§4.10.1.5</a>,
  <a href="jvms-4.html#jvms-4.10.1.6" class="xref"
  title="4.10.1.6. Type Checking Code Streams">§4.10.1.6</a>).

- Fifth, we discuss type checking issues common to all load and store
  instructions (<a href="jvms-4.html#jvms-4.10.1.7" class="xref"
  title="4.10.1.7. Type Checking Load and Store Instructions">§4.10.1.7</a>),
  and also issues of access to `protected` members
  (<a href="jvms-4.html#jvms-4.10.1.8" class="xref"
  title="4.10.1.8. Type Checking for protected Members">§4.10.1.8</a>).

- Finally, we specify the rules to type check each instruction
  (<a href="jvms-4.html#jvms-4.10.1.9" class="xref"
  title="4.10.1.9. Type Checking Instructions">§4.10.1.9</a>).

</div>

<div id="jvms-4.10.1.1" class="section">

<div class="titlepage">

<div>

<div>

#### 4.10.1.1. Accessors for Java Virtual Machine Artifacts

</div>

</div>

</div>

We stipulate the existence of 17 Prolog predicates ("accessors") that
have certain expected behavior but whose formal definitions are not
given in this specification. The Prolog term `Class`, as used here,
represents a binary class or interface that has been successfully loaded
(<a href="jvms-5.html#jvms-5.3" class="xref"
title="5.3. Creation and Loading">§5.3</a>); the Prolog term `Method`
represents a method of a `Class`; and the Prolog term `Loader`
represents a class loader of a `Class`. This specification does not
mandate a precise structure for these entities.

<div class="variablelist">

<span class="term">classClassName(Class, ClassName)</span>  
Extracts the name, `ClassName`, of the class `Class`.

<span class="term">classIsInterface(Class)</span>  
True iff the class, `Class`, is an interface.

<span class="term">classSuperClassName(Class, SuperClassName)</span>  
Extracts the name, `SuperClassName`, of the superclass of class `Class`.

<span class="term">classInterfaceNames(Class, InterfaceNames)</span>  
Extracts a list, `InterfaceNames`, of the names of the direct
superinterfaces of the class `Class`.

<span class="term">classDeclaresMember(Class, MemberName, MemberDescriptor)</span>  
Asserts that a class, `Class`, declares a field or method with name
`MemberName` and descriptor `MemberDescriptor`. This assertion does not
consider members declared in the superclasses or superinterfaces of
`Class`.

<span class="term">classDefiningLoader(Class, Loader)</span>  
Extracts the defining class loader, `Loader`, of the class `Class`.

<span class="term">isBootstrapLoader(Loader)</span>  
True iff the class loader `Loader` is the bootstrap class loader.

<span class="term">loadedClass(Name, InitiatingLoader, ClassDefinition)</span>  
True iff there exists a class named `Name` whose representation (in
accordance with this specification) when loaded by the class loader
`InitiatingLoader` is `ClassDefinition`.

<span class="term">methodName(Method, Name)</span>  
Extracts the name, `Name`, of the method `Method`.

<span class="term">methodAccessFlags(Method, AccessFlags)</span>  
Extracts the access flags, `AccessFlags`, of the method `Method`.

<span class="term">methodDescriptor(Method, Descriptor)</span>  
Extracts the descriptor, `Descriptor`, of the method `Method`.

<span class="term">isProtected(MemberClass, MemberName, MemberDescriptor)</span>  
True iff there is a member named `MemberName` with descriptor
`MemberDescriptor` in the class `MemberClass` and it is `protected`.

<span class="term">isNotProtected(MemberClass, MemberName, MemberDescriptor)</span>  
True iff there is a member named `MemberName` with descriptor
`MemberDescriptor` in the class `MemberClass` and it is not `protected`.

<span class="term">parseFieldDescriptor(Descriptor, Type)</span>  
Converts a field descriptor, `Descriptor`, into the corresponding
verification type `Type`
(<a href="jvms-4.html#jvms-4.10.1.2" class="xref"
title="4.10.1.2. Verification Type System">§4.10.1.2</a>).

The verification type derived from descriptor types `byte`, `short`,
`boolean`, and `char`, when not used as array component types, is `int`.

<span class="term">parseMethodDescriptor(Descriptor, ArgTypeList, ReturnType)</span>  
Converts a method descriptor, `Descriptor`, into a list of verification
types, `ArgTypeList`, corresponding to the method argument types, and a
verification type, `ReturnType`, corresponding to the return type.

The verification type derived from descriptor types `byte`, `short`,
`boolean`, and `char`, when not used as array component types, is `int`.
A void return is represented with the special symbol `void`.

<span class="term">parseCodeAttribute(Class, Method, FrameSize, MaxStack, ParsedCode, Handlers, StackMap)</span>  
Extracts the instruction stream, `ParsedCode`, of the method `Method` in
`Class`, as well as the maximum operand stack size, `MaxStack`, the
maximal number of local variables, `FrameSize`, the exception handlers,
`Handlers`, and the stack map `StackMap`.

The representation of the instruction stream and stack map attribute
must be as specified in <a href="jvms-4.html#jvms-4.10.1.3" class="xref"
title="4.10.1.3. Instruction Representation">§4.10.1.3</a> and
<a href="jvms-4.html#jvms-4.10.1.4" class="xref"
title="4.10.1.4. Stack Map Frames and Type Transitions">§4.10.1.4</a>.

<span class="term">samePackageName(Class1, Class2)</span>  
True iff the package names of `Class1` and `Class2` are the same.

</div>

The above accessors are used to define `loadedSuperclasses`, which
produces a list of a class's superclasses by recurring on each class's
direct superclass until `Object`, which has no superclass, is reached.

``` programlisting
loadedSuperclasses(Class, [ Superclass | Rest ]) :-
    classSuperClassName(Class, SuperclassName),
    classDefiningLoader(Class, L),
    loadedClass(SuperclassName, L, Superclass),
    loadedSuperclasses(Superclass, Rest).

loadedSuperclasses(Class, []) :-
    \+ classSuperClassName(Class, _).
```

When type checking a method's body, it is convenient to access
information about the method. For this purpose, we define an
<span class="emphasis">*environment*</span>, a six-tuple consisting of:

<div class="norm">

- a class

- a method

- the declared return type of the method (or `void`)

- the instructions in a method

- the maximal size of the operand stack

- a list of exception handlers

</div>

We specify accessors to extract information from the environment.

``` programlisting
allInstructions(Environment, Instructions) :-
    Environment = environment(_Class, _Method, _ReturnType,
                              Instructions, _, _).

exceptionHandlers(Environment, Handlers) :-
    Environment = environment(_Class, _Method, _ReturnType,
                              _Instructions, _, Handlers).

maxOperandStackLength(Environment, MaxStack) :-
    Environment = environment(_Class, _Method, _ReturnType,
                              _Instructions, MaxStack, _Handlers).

currentClassLoader(Environment, Loader) :-
    Environment = environment(Class, _Method, _ReturnType,
                              _Instructions, _, _),
    classDefiningLoader(Class, Loader).

thisClass(Environment, Class) :-
    Environment = environment(Class, _Method, _ReturnType,
                              _Instructions, _, _).

thisType(Environment, class(ClassName, L)) :-
    Environment = environment(Class, _Method, _ReturnType,
                              _Instructions, _, _),
    classDefiningLoader(Class, L),
    classClassName(Class, ClassName).

thisMethodReturnType(Environment, ReturnType) :-
    Environment = environment(_Class, _Method, ReturnType,
                              _Instructions, _, _).

offsetStackFrame(Environment, Offset, StackFrame) :-
    allInstructions(Environment, Instructions),
    member(stackMap(Offset, StackFrame), Instructions).
```

Finally, we specify a general predicate used throughout the type rules:

``` programlisting
notMember(_, []).
notMember(X, [A | More]) :- X \= A, notMember(X, More).
```

The principle guiding the determination as to which accessors are
stipulated and which are fully specified is that we do not want to
over-specify the representation of the `class` file. Providing specific
accessors to the `Class` or `Method` term would force us to completely
specify the format for a Prolog term representing the `class` file.

</div>

<div id="jvms-4.10.1.2" class="section">

<div class="titlepage">

<div>

<div>

#### 4.10.1.2. Verification Type System

</div>

</div>

</div>

The type checker enforces a type system based upon a hierarchy of
<span class="emphasis">*verification types*</span>, illustrated below.

``` programlisting
Verification type hierarchy:

                             top
                 ____________/\____________
                /                          \
               /                            \
            oneWord                       twoWord
           /   |   \                     /       \
          /    |    \                   /         \
        int  float  reference        long        double
                     /     \
                    /       \_____________
                   /                      \
                  /                        \
           uninitialized                    +------------------+
            /         \                     |  reference type  |
           /           \                    |  hierarchy       |
uninitializedThis  uninitialized(Offset)    +------------------+
                                                     |
                                                     |
                                                    null
```

Most verification types have a direct correspondence with the primitive
and reference types described in
<a href="jvms-2.html#jvms-2.3" class="xref"
title="2.3. Primitive Types and Values">§2.3</a> and
<a href="jvms-2.html#jvms-2.4" class="xref"
title="2.4. Reference Types and Values">§2.4</a>, and represented by
field descriptors in <a href="jvms-4.html#jvms-4.3.2-200" class="xref"
title="Table 4.3-A. Interpretation of field descriptors">Table 4.3-A</a>:

<div class="norm">

- The primitive types `double`, `float`, `int`, and `long` (field
  descriptors `D`, `F`, `I`, `J`) each correspond to the verification
  type of the same name.

- The primitive types `byte`, `char`, `short`, and `boolean` (field
  descriptors `B`, `C`, `S`, `Z`) all correspond to the verification
  type `int`.

- Class and interface types (field descriptors beginning `L`) correspond
  to verification types that use the functor `class`. The verification
  type
  `class(`<span class="emphasis">*`N`*</span>`, `<span class="emphasis">*`L`*</span>`)`
  represents the type of the class or interface whose binary name is
  <span class="emphasis">*`N`*</span> as loaded by the loader
  <span class="emphasis">*`L`*</span>. Note that
  <span class="emphasis">*`L`*</span> is an initiating loader
  (<a href="jvms-5.html#jvms-5.3" class="xref"
  title="5.3. Creation and Loading">§5.3</a>) of the class represented
  by
  `class(`<span class="emphasis">*`N`*</span>`, `<span class="emphasis">*`L`*</span>`)`
  and may, or may not, be the class's defining loader.

  For example, the class type `Object` would be represented as
  `class('java/lang/Object', L)`, where the defining loader of class
  `java/lang/Object`, as loaded by `L`, is the bootstrap loader.

- Array types (field descriptors beginning `[`) correspond to
  verification types that use the functor `arrayOf`. Note that the
  primitive types `byte`, `char`, `short`, and `boolean` do not
  correspond to verification types, but an array type whose element type
  is `byte`, `char`, `short`, or `boolean`
  <span class="emphasis">*does*</span> correspond to a verification
  type; such verification types support the
  <span class="emphasis">*baload*</span>,
  <span class="emphasis">*bastore*</span>,
  <span class="emphasis">*caload*</span>,
  <span class="emphasis">*castore*</span>,
  <span class="emphasis">*saload*</span>,
  <span class="emphasis">*sastore*</span>, and
  <span class="emphasis">*newarray*</span> instructions.

  <div class="norm">

  - The verification type
    `arrayOf(`<span class="emphasis">*`T`*</span>`)` represents the
    array type whose component type is the verification type
    <span class="emphasis">*`T`*</span>.

  - The verification type `arrayOf(byte)` represents the array type
    whose component type is `byte`.

  - The verification type `arrayOf(char)` represents the array type
    whose component type is `char`.

  - The verification type `arrayOf(short)` represents the array type
    whose component type is `short`.

  - The verification type `arrayOf(boolean)` represents the array type
    whose component type is `boolean`.

  </div>

  For example, the array types `int[]` and `Object[]` would be
  represented by the verification types `arrayOf(int)` and
  `arrayOf(class('java/lang/Object', L))` respectively. The array types
  `byte``[]` and `boolean``[]``[]` would be represented by the
  verification types `arrayOf(byte)` and `arrayOf(arrayOf(boolean))`
  respectively.

</div>

The remaining verification types are described as follows:

<div class="norm">

- The verification types `top`, `oneWord`, `twoWord`, and `reference`
  denote abstract unions of other types, as illustrated above, and are
  represented in Prolog as atoms.

- The verification types `uninitialized`, `uninitializedThis`, and
  `uninitialized(Offset)` describe references to objects created with
  <span class="emphasis">*new*</span> that have not yet been initialized
  (<a href="jvms-2.html#jvms-2.9.1" class="xref"
  title="2.9.1. Instance Initialization Methods">§2.9.1</a>). The types
  `uninitialized` and `uninitializedThis` are represented as atoms. The
  type `uninitialized(Offset)` is represented by applying the functor
  `uninitialized` to an argument representing the numerical value of the
  `Offset`.

- The verification type `null` describes the result of the
  <span class="emphasis">*aconst_null*</span> instruction, and is
  represented in Prolog as an atom.

</div>

The subtyping rules for verification types are as follows.

Subtyping is reflexive.

``` programlisting
isAssignable(X, X).
```

The type `top` is a supertype of all other types.

``` programlisting
isAssignable(oneWord, top).
isAssignable(twoWord, top).
```

A type is a subtype of some other type, <span class="type">X</span>, if
it has a supertype that is a subtype of <span class="type">X</span>.

``` programlisting
isAssignable(int, X)    :- isAssignable(oneWord, X).
isAssignable(float, X)  :- isAssignable(oneWord, X).
isAssignable(long, X)   :- isAssignable(twoWord, X).
isAssignable(double, X) :- isAssignable(twoWord, X).

isAssignable(reference, X)   :- isAssignable(oneWord, X).
isAssignable(class(_, _), X) :- isAssignable(reference, X).
isAssignable(arrayOf(_), X)  :- isAssignable(reference, X).

isAssignable(null, X) :- isAssignable(reference, X).

isAssignable(uninitialized, X)     :- isAssignable(reference, X).
isAssignable(uninitializedThis, X) :- isAssignable(uninitialized, X).
isAssignable(uninitialized(_), X)  :- isAssignable(uninitialized, X).
```

The type `null` is a subtype of all reference types.

``` programlisting
isAssignable(null, class(_, _)).
isAssignable(null, arrayOf(_)).
```

These subtype rules are not necessarily the most obvious formulation of
subtyping. There is a clear split between subtyping rules among
reference types and rules for the remaining verification types. The
split allows us to state general subtyping relations between reference
types and other verification types. These relations hold independently
of a reference type's position in the type hierarchy, and help to
prevent excessive class loading by a Java Virtual Machine
implementation. For example, we do not want to start climbing the
superclass hierarchy in response to a query of the form
`class(foo, L) <: twoWord`.

We also have a rule that says subtyping is reflexive, so it is always
trivially possible to assign between two identical types—both in the
case of simple types, like from `int` to `int`, and more complex types,
like from `arrayOf(int)` to `arrayOf(int)` or from `class('C', Loader)`
to `class('C', Loader)`. Together, the above rules cover all subtyping
relationships except for between two distinct reference types.

The `isWideningReference` predicate is used to determine if an
assignment from one reference type to another, different, reference type
is allowed.

``` programlisting
isAssignable(From, To) :- isWideningReference(From, To).
```

The `isWideningReference` predicate is not reflexive: widening only
occurs when converting between distinct reference types.

The verifier allows any class or interface type to be widened to any
interface type.

``` programlisting
isWideningReference(class(_, _), class(To, L)) :-
    loadedClass(To, L, ToClass),
    classIsInterface(ToClass).
```

This approach is less strict than the Java programming language, which
will not allow an assignment to an interface unless the referenced
object is statically known to implement the interface. The Java Virtual
Machine instead uses a run-time check to ensure that invocations of
interface methods actually operate on objects that implement the
interface (<a href="jvms-6.html#jvms-6.5.invokeinterface" class="xref"
title="invokeinterface">§<span
class="emphasis"><em>invokeinterface</em></span></a>). There is no
requirement that a reference stored by a variable of an interface type
refers to an object that actually implements that interface.

A class type can be widened to another class type if the second type
refers to the loaded class of one of the first type's superclasses, or
if they both refer to the same class with different initiating loaders.

``` programlisting
isWideningReference(class(From, L1), class(To, L2)) :-
    From \= To,
    loadedClass(From, L1, FromClass),
    loadedClass(To, L2, ToClass),
    loadedSuperclasses(FromClass, Supers),
    member(ToClass, Supers).

isWideningReference(class(ClassName, L1), class(ClassName, L2)) :-
    L1 \= L2,
    loadedClass(ClassName, L1, Class),
    loadedClass(ClassName, L2, Class).
```

If two `class` types <span class="type">S</span> and
<span class="type">T</span> have the same name and the same loader,
there is no need to "widen" from one to the other, as `isAssignable` is
already true, according to the earlier rule.

Array types are subtypes of `Object`, `Cloneable`, and
`java.io.Serializable`. Subtyping between arrays of reference type is
covariant.

``` programlisting
isWideningReference(arrayOf(_), class(ClassName, L)) :-
    (ClassName = 'java/lang/Object' ;
     ClassName = 'java/lang/Cloneable' ;
     ClassName = 'java/io/Serializable')
    loadedClass(ClassName, L, LoadedClass),
    classDefiningLoader(LoadedClass, BL),
    isBootstrapLoader(BL).

isWideningReference(arrayOf(X), arrayOf(Y)) :-
    isWideningReference(X, Y).
```

</div>

<div id="jvms-4.10.1.3" class="section">

<div class="titlepage">

<div>

<div>

#### 4.10.1.3. Instruction Representation

</div>

</div>

</div>

Individual bytecode instructions are represented in Prolog as terms
whose functor is the name of the instruction and whose arguments are its
parsed operands.

For example, an <span class="emphasis">*aload*</span> instruction is
represented as the term `aload(N)`, which includes the index `N` that is
the operand of the instruction.

The instructions as a whole are represented as a list of terms of the
form:

``` screen
instruction(Offset, AnInstruction)
```

For example, `instruction(21, aload(1))`.

The order of instructions in this list must be the same as in the
`class` file.

Some instructions have operands that refer to entries in the
`constant_pool` table. Such entries are represented as functor
applications of the form:

<div class="norm">

- `class(Name, Loader)` or `arrayOf(ComponentType)` for a constant pool
  entry that is a `CONSTANT_Class_info` structure
  (<a href="jvms-4.html#jvms-4.4.1" class="xref"
  title="4.4.1. The CONSTANT_Class_info Structure">§4.4.1</a>).

  These are verification types, as described in
  <a href="jvms-4.html#jvms-4.10.1.2" class="xref"
  title="4.10.1.2. Verification Type System">§4.10.1.2</a>.

  If the `name_index` item of the structure gives the name of a class or
  interface, `Name` is that name, and `Loader` is the defining loader of
  the class or interface containing the constant pool.

  If the `name_index` item of the structure gives an array type,
  `ComponentType` is the array component type.

- `field(FieldClassType, FieldName, FieldDescriptor)` for a constant
  pool entry that is a `CONSTANT_Fieldref_info` structure
  (<a href="jvms-4.html#jvms-4.4.2" class="xref"
  title="4.4.2. The CONSTANT_Fieldref_info, CONSTANT_Methodref_info, and CONSTANT_InterfaceMethodref_info Structures">§4.4.2</a>).

  `FieldClassType` is the verification type of the class, interface, or
  array type referenced by the `class_index` item in the structure.
  `FieldName` and `FieldDescriptor` correspond to the name and field
  descriptor referenced by the `name_and_type_index` item of the
  structure.

- `method(MethodClassType, MethodName, MethodDescriptor)` for a constant
  pool entry that is a `CONSTANT_Methodref_info` structure
  (<a href="jvms-4.html#jvms-4.4.2" class="xref"
  title="4.4.2. The CONSTANT_Fieldref_info, CONSTANT_Methodref_info, and CONSTANT_InterfaceMethodref_info Structures">§4.4.2</a>).

  `MethodClassType` is the verification type of the class, interface, or
  array type referenced by the `class_index` item of the structure.
  `MethodName` and `MethodDescriptor` correspond to the name and method
  descriptor referenced by the `name_and_type_index` item of the
  structure.

- `imethod(MethodClassType, MethodName, MethodDescriptor)` for a
  constant pool entry that is a `CONSTANT_InterfaceMethodref_info`
  structure (<a href="jvms-4.html#jvms-4.4.2" class="xref"
  title="4.4.2. The CONSTANT_Fieldref_info, CONSTANT_Methodref_info, and CONSTANT_InterfaceMethodref_info Structures">§4.4.2</a>).

  `MethodClassType` is the verification type of the class, interface, or
  array type referenced by the `class_index` item of the structure.
  `MethodName` and `MethodDescriptor` correspond to the name and method
  descriptor referenced by the `name_and_type_index` item of the
  structure.

- `string(Value)` for a constant pool entry that is a
  `CONSTANT_String_info` structure
  (<a href="jvms-4.html#jvms-4.4.3" class="xref"
  title="4.4.3. The CONSTANT_String_info Structure">§4.4.3</a>).

  `Value` is the string referenced by the `string_index` item of the
  structure.

- `int(Value)` for a constant pool entry that is a
  `CONSTANT_Integer_info` structure
  (<a href="jvms-4.html#jvms-4.4.4" class="xref"
  title="4.4.4. The CONSTANT_Integer_info and CONSTANT_Float_info Structures">§4.4.4</a>).

  `Value` is the `int` constant represented by the `bytes` item of the
  structure.

- `float(Value)` for a constant pool entry that is a
  `CONSTANT_Float_info` structure
  (<a href="jvms-4.html#jvms-4.4.4" class="xref"
  title="4.4.4. The CONSTANT_Integer_info and CONSTANT_Float_info Structures">§4.4.4</a>).

  `Value` is the `float` constant represented by the `bytes` item of the
  structure.

- `long(Value)` for a constant pool entry that is a `CONSTANT_Long_info`
  structure (<a href="jvms-4.html#jvms-4.4.5" class="xref"
  title="4.4.5. The CONSTANT_Long_info and CONSTANT_Double_info Structures">§4.4.5</a>).

  `Value` is the `long` constant represented by the `high_bytes` and
  `low_bytes` items of the structure.

- `double(Value)` for a constant pool entry that is a
  `CONSTANT_Double_info` structure
  (<a href="jvms-4.html#jvms-4.4.5" class="xref"
  title="4.4.5. The CONSTANT_Long_info and CONSTANT_Double_info Structures">§4.4.5</a>).

  `Value` is the `double` constant represented by the `high_bytes` and
  `low_bytes` items of the structure.

- `methodHandle(Kind, Reference)` for a constant pool entry that is a
  `CONSTANT_MethodHandle_info` structure
  (<a href="jvms-4.html#jvms-4.4.8" class="xref"
  title="4.4.8. The CONSTANT_MethodHandle_info Structure">§4.4.8</a>).

  `Kind` is the value of the `reference_kind` item of the structure.
  `Reference` is the value of the `reference_index` item of the
  structure.

- `methodType(MethodDescriptor)` for a constant pool entry that is a
  `CONSTANT_MethodType_info` structure
  (<a href="jvms-4.html#jvms-4.4.9" class="xref"
  title="4.4.9. The CONSTANT_MethodType_info Structure">§4.4.9</a>).

  `MethodDescriptor` is the method descriptor referenced by the
  `descriptor_index` item of the structure.

- `dconstant(ConstantName, FieldDescriptor)` for a constant pool entry
  that is a `CONSTANT_Dynamic_info` structure
  (<a href="jvms-4.html#jvms-4.4.10" class="xref"
  title="4.4.10. The CONSTANT_Dynamic_info and CONSTANT_InvokeDynamic_info Structures">§4.4.10</a>).

  `ConstantName` and `FieldDescriptor` correspond to the name and field
  descriptor referenced by the `name_and_type_index` item of the
  structure. (The `bootstrap_method_attr_index` item is irrelevant to
  verification.)

- `dmethod(CallSiteName, MethodDescriptor)` for a constant pool entry
  that is a `CONSTANT_InvokeDynamic_info` structure
  (<a href="jvms-4.html#jvms-4.4.10" class="xref"
  title="4.4.10. The CONSTANT_Dynamic_info and CONSTANT_InvokeDynamic_info Structures">§4.4.10</a>).

  `CallSiteName` and `MethodDescriptor` correspond to the name and
  method descriptor referenced by the `name_and_type_index` item of the
  structure. (The `bootstrap_method_attr_index` item is irrelevant to
  verification.)

</div>

For example, a <span class="emphasis">*getfield*</span> instruction
whose operand refers to a constant pool entry representing a field `foo`
of type `F` in class `Bar` would be represented as as
`getfield(field(class('Bar', L), 'foo', 'F'))`, where `L` is the class
loader of the class containing the instruction. An
<span class="emphasis">*ldc*</span> instruction for loading the `int`
constant `91` would be represented as `ldc(int(91))`.

</div>

<div id="jvms-4.10.1.4" class="section">

<div class="titlepage">

<div>

<div>

#### 4.10.1.4. Stack Map Frames and Type Transitions

</div>

</div>

</div>

Stack map frames are represented in Prolog as a list of terms of the
form:

``` screen
stackMap(Offset, TypeState)
```

where:

<div class="norm">

- `Offset` is an integer indicating the bytecode offset at which the
  stack map frame applies (<a href="jvms-4.html#jvms-4.7.4" class="xref"
  title="4.7.4. The StackMapTable Attribute">§4.7.4</a>).

  The order of bytecode offsets in this list must be the same as in the
  `class` file.

- `TypeState` is the expected incoming type state for the instruction at
  `Offset`.

</div>

A <span class="emphasis">*type state*</span> is a mapping from locations
in the operand stack and local variables of a method to verification
types. It has the form:

``` screen
frame(Locals, OperandStack, Flags)
```

where:

<div class="norm">

- `Locals` is a list of verification types, such that the
  <span class="emphasis">*i*</span>'th element of the list (with 0-based
  indexing) represents the type of local variable
  <span class="emphasis">*i*</span>.

  Types of size 2 (`long` and `double`) are represented by two local
  variables (<a href="jvms-2.html#jvms-2.6.1" class="xref"
  title="2.6.1. Local Variables">§2.6.1</a>), with the first local
  variable being the type itself and the second local variable being
  `top` (<a href="jvms-4.html#jvms-4.10.1.7" class="xref"
  title="4.10.1.7. Type Checking Load and Store Instructions">§4.10.1.7</a>).

- `OperandStack` is a list of verification types, such that the first
  element of the list represents the type of the top of the operand
  stack, and the types of stack entries below the top follow in the list
  in the appropriate order.

  Types of size 2 (`long` and `double`) are represented by two stack
  entries, with the first entry being `top` and the second entry being
  the type itself.

  For example, a stack with a `double` value, an `int` value, and a
  `long` value is represented in a type state as a stack with five
  entries: `top` and `double` entries for the `double` value, an `int`
  entry for the `int` value, and `top` and `long` entries for the `long`
  value. Accordingly, `OperandStack` is the list
  `[top, double, int, top, long]`.

- `Flags` is a list which may either be empty or have the single element
  `flagThisUninit`.

  If any local variable in `Locals` has the type `uninitializedThis`,
  then `Flags` has the single element `flagThisUninit`, otherwise
  `Flags` is an empty list.

  `flagThisUninit` is used in constructors to mark type states where
  initialization of `this` has not yet been completed. In such type
  states, it is illegal to return from the method.

</div>

Subtyping of verification types is extended pointwise to type states.
The local variable array of a method has a fixed length by construction
(see `methodInitialStackFrame` in
<a href="jvms-4.html#jvms-4.10.1.5" class="xref"
title="4.10.1.5. Type Checking Methods">§4.10.1.5</a>), but the operand
stack grows and shrinks, so we require an explicit check on the length
of the operand stacks whose assignability is desired for subtyping.

``` programlisting
frameIsAssignable(frame(Locals1, StackMap1, Flags1),
                  frame(Locals2, StackMap2, Flags2)) :-
    length(StackMap1, StackMapLength),
    length(StackMap2, StackMapLength),
    maplist(isAssignable, Locals1, Locals2),
    maplist(isAssignable, StackMap1, StackMap2),
    subset(Flags1, Flags2).
```

Most of the type rules for individual instructions
(<a href="jvms-4.html#jvms-4.10.1.9" class="xref"
title="4.10.1.9. Type Checking Instructions">§4.10.1.9</a>) depend on
the notion of a valid <span class="emphasis">*type transition*</span>. A
type transition is <span class="emphasis">*valid*</span> if one can pop
a list of expected types off the incoming type state's operand stack and
replace them with an expected result type, resulting in a new type state
where the length of the operand stack does not exceed its declared
maximum size.

``` programlisting
validTypeTransition(Environment, ExpectedTypesOnStack, ResultType,
                    frame(Locals, InputOperandStack, Flags),
                    frame(Locals, NextOperandStack, Flags)) :-
    popMatchingList(InputOperandStack, ExpectedTypesOnStack,
                    InterimOperandStack),
    pushOperandStack(InterimOperandStack, ResultType, NextOperandStack),
    operandStackHasLegalLength(Environment, NextOperandStack).
```

Pop a list of types off the stack.

``` programlisting
popMatchingList(OperandStack, [], OperandStack).
popMatchingList(OperandStack, [P | Rest], NewOperandStack) :-
    popMatchingType(OperandStack, P, TempOperandStack, _ActualType),
    popMatchingList(TempOperandStack, Rest, NewOperandStack).
```

Pop an individual type off the stack. The exact behavior depends on the
stack contents. If the logical top of the stack is some subtype of the
specified type, `Type`, then pop it. If a type occupies two stack
entries, then the logical top of the stack is really the type just below
the top, and the top of the stack is the unusable type `top`.

``` programlisting
popMatchingType([ActualType | OperandStack],
                Type, OperandStack, ActualType) :-
    sizeOf(Type, 1),
    isAssignable(ActualType, Type).

popMatchingType([top, ActualType | OperandStack],
                Type, OperandStack, ActualType) :-
    sizeOf(Type, 2),
    isAssignable(ActualType, Type).

sizeOf(X, 2) :- isAssignable(X, twoWord).
sizeOf(X, 1) :- isAssignable(X, oneWord).
sizeOf(top, 1).
```

Push a logical type onto the stack. The exact behavior varies with the
size of the type. If the pushed type is of size 1, we just push it onto
the stack. If the pushed type is of size 2, we push it, and then push
`top`.

``` programlisting
pushOperandStack(OperandStack, 'void', OperandStack).
pushOperandStack(OperandStack, Type, [Type | OperandStack]) :-
    sizeOf(Type, 1).
pushOperandStack(OperandStack, Type, [top, Type | OperandStack]) :-
    sizeOf(Type, 2).
```

The length of the operand stack must not exceed the declared maximum
size.

``` programlisting
operandStackHasLegalLength(Environment, OperandStack) :-
    length(OperandStack, Length),
    maxOperandStackLength(Environment, MaxStack),
    Length =< MaxStack.
```

The <span class="emphasis">*dup*</span> instructions pop expected types
off the incoming type state's operand stack and replace them with
predefined result types, resulting in a new type state. However, these
instructions are not defined in terms of type transitions because there
is no need to match types by means of the subtyping relation. Instead,
the <span class="emphasis">*dup*</span> instructions manipulate the
operand stack entirely in terms of the
<span class="emphasis">*category*</span> of types on the stack
(<a href="jvms-2.html#jvms-2.11.1" class="xref"
title="2.11.1. Types and the Java Virtual Machine">§2.11.1</a>).

Category 1 types occupy a single stack entry. Popping a logical type of
category 1, `Type`, off the stack is possible if the top of the stack is
`Type` and `Type` is not `top` (otherwise it could denote the upper half
of a category 2 type). The result is the incoming stack, with the top
entry popped off.

``` programlisting
popCategory1([Type | Rest], Type, Rest) :-
    Type \= top,
    sizeOf(Type, 1).
```

Category 2 types occupy two stack entries. Popping a logical type of
category 2, `Type`, off the stack is possible if the top of the stack is
type `top`, and the entry directly below it is `Type`. The result is the
incoming stack, with the top two entries popped off.

``` programlisting
popCategory2([top, Type | Rest], Type, Rest) :-
    sizeOf(Type, 2).
```

The <span class="emphasis">*dup*</span> instructions push a list of
types onto the stack in essentially the same way as when a type is
pushed for a valid type transition.

``` programlisting
canSafelyPush(Environment, InputOperandStack, Type, OutputOperandStack) :-
    pushOperandStack(InputOperandStack, Type, OutputOperandStack),
    operandStackHasLegalLength(Environment, OutputOperandStack).

canSafelyPushList(Environment, InputOperandStack, Types,
                  OutputOperandStack) :-
    canPushList(InputOperandStack, Types, OutputOperandStack),
    operandStackHasLegalLength(Environment, OutputOperandStack).

canPushList(InputOperandStack, [], InputOperandStack).
canPushList(InputOperandStack, [Type | Rest], OutputOperandStack) :-
    pushOperandStack(InputOperandStack, Type, InterimOperandStack),
    canPushList(InterimOperandStack, Rest, OutputOperandStack).
```

Many of the type rules for individual instructions use the following
clause to easily pop a list of types off the stack.

``` programlisting
canPop(frame(Locals, OperandStack, Flags), Types,
       frame(Locals, PoppedOperandStack, Flags)) :-
    popMatchingList(OperandStack, Types, PoppedOperandStack).
```

Finally, certain array instructions
(<a href="jvms-4.html#jvms-4.10.1.9.aaload" class="xref"
title="aaload">§<span class="emphasis"><em>aaload</em></span></a>,
<a href="jvms-4.html#jvms-4.10.1.9.arraylength" class="xref"
title="arraylength">§<span
class="emphasis"><em>arraylength</em></span></a>,
<a href="jvms-4.html#jvms-4.10.1.9.baload" class="xref"
title="baload">§<span class="emphasis"><em>baload</em></span></a>,
<a href="jvms-4.html#jvms-4.10.1.9.bastore" class="xref"
title="bastore">§<span class="emphasis"><em>bastore</em></span></a>)
peek at types on the operand stack in order to check they are array
types. The following clause accesses the
<span class="emphasis">*i*</span>'th element of the operand stack from a
type state.

``` programlisting
nth1OperandStackIs(i, frame(_Locals, OperandStack, _Flags), Element) :-
    nth1(i, OperandStack, Element).
```

</div>

<div id="jvms-4.10.1.5" class="section">

<div class="titlepage">

<div>

<div>

#### 4.10.1.5. Type Checking Methods

</div>

</div>

</div>

A method with a `Code` attribute is type safe if it is possible to merge
the code and the stack map frames into a single stream such that each
stack map frame precedes the instruction it corresponds to, and the
merged stream is type correct. The method's exception handlers, if any,
must also be legal.

``` programlisting
methodIsTypeSafe(Class, Method) :-
    parseCodeAttribute(Class, Method, FrameSize, MaxStack,
                       ParsedCode, Handlers, StackMap),
    mergeStackMapAndCode(StackMap, ParsedCode, MergedCode),
    methodInitialStackFrame(Class, Method, FrameSize, StackFrame, ReturnType),
    Environment = environment(Class, Method, ReturnType, MergedCode,
                              MaxStack, Handlers),
    handlersAreLegal(Environment),
    mergedCodeIsTypeSafe(Environment, MergedCode, StackFrame).
```

Let us consider exception handlers first.

An exception handler is represented by a functor application of the
form:

``` screen
handler(Start, End, Target, ClassName)
```

whose arguments are, respectively, the start and end of the range of
instructions covered by the handler, the first instruction of the
handler code, and the name of the exception class that this handler is
designed to handle.

An exception handler is <span class="emphasis">*legal*</span> if its
start (`Start`) is less than its end (`End`), there exists an
instruction whose offset is equal to `Start`, there exists an
instruction whose offset equals `End`, and the handler's exception class
is assignable to the class `Throwable`. The exception class of a handler
is `Throwable` if the handler's class entry is 0, otherwise it is the
class named in the handler.

``` programlisting
handlersAreLegal(Environment) :-
    exceptionHandlers(Environment, Handlers),
    checklist(handlerIsLegal(Environment), Handlers).

handlerIsLegal(Environment, Handler) :-
    Handler = handler(Start, End, Target, _),
    Start < End,
    allInstructions(Environment, Instructions),
    member(instruction(Start, _), Instructions),
    offsetStackFrame(Environment, Target, _),
    instructionsIncludeEnd(Instructions, End),
    currentClassLoader(Environment, CurrentLoader),
    handlerExceptionClass(Handler, ExceptionClass, CurrentLoader),
    isBootstrapLoader(BL),
    isAssignable(ExceptionClass, class('java/lang/Throwable', BL)).

instructionsIncludeEnd(Instructions, End) :-
    member(instruction(End, _), Instructions).
instructionsIncludeEnd(Instructions, End) :-
    member(endOfCode(End), Instructions).

handlerExceptionClass(handler(_, _, _, 0),
                      class('java/lang/Throwable', BL), _) :-
    isBootstrapLoader(BL).

handlerExceptionClass(handler(_, _, _, Name),
                      class(Name, L), L) :-
    Name \= 0.
```

Let us now turn to the stream of instructions and stack map frames.

Merging instructions and stack map frames into a single stream involves
four cases:

<div>

- Merging an empty `StackMap` and a list of instructions yields the
  original list of instructions.

  ``` programlisting
  mergeStackMapAndCode([], CodeList, CodeList).
  ```

- Given a list of stack map frames beginning with the type state for the
  instruction at `Offset`, and a list of instructions beginning at
  `Offset`, the merged list is the head of the stack map frame list,
  followed by the head of the instruction list, followed by the merge of
  the tails of the two lists.

  ``` programlisting
  mergeStackMapAndCode([stackMap(Offset, Map) | RestMap],
                       [instruction(Offset, Parse) | RestCode],
                       [stackMap(Offset, Map),
                         instruction(Offset, Parse) | RestMerge]) :-
      mergeStackMapAndCode(RestMap, RestCode, RestMerge).
  ```

- Otherwise, given a list of stack map frames beginning with the type
  state for the instruction at `OffsetM`, and a list of instructions
  beginning at `OffsetP`, then, if `OffsetP < OffsetM`, the merged list
  consists of the head of the instruction list, followed by the merge of
  the stack map frame list and the tail of the instruction list.

  ``` programlisting
  mergeStackMapAndCode([stackMap(OffsetM, Map) | RestMap],
                       [instruction(OffsetP, Parse) | RestCode],
                       [instruction(OffsetP, Parse) | RestMerge]) :-
      OffsetP < OffsetM,
      mergeStackMapAndCode([stackMap(OffsetM, Map) | RestMap],
                           RestCode, RestMerge).
  ```

- Otherwise, the merge of the two lists is undefined. Since the
  instruction list has monotonically increasing offsets, the merge of
  the two lists is not defined unless every stack map frame offset has a
  corresponding instruction offset and the stack map frames are in
  monotonically increasing order.

</div>

To determine if the merged stream for a method is type correct, we first
infer the method's initial type state.

The initial type state of a method consists of an empty operand stack
and local variable types derived from the type of `this` and the
arguments, as well as the appropriate flag, depending on whether this is
an `<init>` method.

``` programlisting
methodInitialStackFrame(Class, Method, FrameSize, frame(Locals, [], Flags),
                        ReturnType):-
    methodDescriptor(Method, Descriptor),
    parseMethodDescriptor(Descriptor, RawArgs, ReturnType),
    expandTypeList(RawArgs, Args),
    methodInitialThisType(Class, Method, ThisList),
    flags(ThisList, Flags),
    append(ThisList, Args, ThisArgs),
    expandToLength(ThisArgs, FrameSize, top, Locals).
```

Given a list of types, the following clause produces a list where every
type of size 2 has been substituted by two entries: one for itself, and
one `top` entry. The result then corresponds to the representation of
the list as 32-bit words in the Java Virtual Machine.

``` programlisting
expandTypeList([], []).
expandTypeList([Item | List], [Item | Result]) :-
    sizeOf(Item, 1),
    expandTypeList(List, Result).
expandTypeList([Item | List], [Item, top | Result]) :-
    sizeOf(Item, 2),
    expandTypeList(List, Result).
```

``` programlisting
flags([uninitializedThis], [flagThisUninit]).
flags(X, []) :- X \= [uninitializedThis].

expandToLength(List, Size, _Filler, List) :-
    length(List, Size).
expandToLength(List, Size, Filler, Result) :-
    length(List, ListLength),
    ListLength < Size,
    Delta is Size - ListLength,
    length(Extra, Delta),
    checklist(=(Filler), Extra),
    append(List, Extra, Result).
```

For the initial type state of an instance method, we compute the type of
`this` and put it in a list. The type of `this` in an `<init>` method of
a class with a superclass (that is, of any class except `Object`) is
`uninitializedThis`; the type of `this` in any other instance method,
including an `<init>` method of `Object`, is `class(N, L)` where `N` is
the name of the class containing the method and `L` is its defining
class loader.

For the initial type state of a static method, `this` is irrelevant, so
the list is empty.

``` programlisting
methodInitialThisType(_Class, Method, []) :-
    methodAccessFlags(Method, AccessFlags),
    member(static, AccessFlags),
    methodName(Method, MethodName),
    MethodName \= '<init>'.

methodInitialThisType(Class, Method, [This]) :-
    methodAccessFlags(Method, AccessFlags),
    notMember(static, AccessFlags),
    instanceMethodInitialThisType(Class, Method, This).

instanceMethodInitialThisType(Class, Method, uninitializedThis) :-
    isSubclassInstanceInit(Class, Method).

instanceMethodInitialThisType(Class, Method, class(ClassName, L)) :-
    \+ isSubclassInstanceInit(Class, Method),
    classClassName(Class, ClassName),
    classDefiningLoader(Class, L).

isSubclassInstanceInit(Class, Method) :-
    methodName(Method, '<init>'),
    classSuperClassName(Class, _).
```

</div>

<div id="jvms-4.10.1.6" class="section">

<div class="titlepage">

<div>

<div>

#### 4.10.1.6. Type Checking Code Streams

</div>

</div>

</div>

Given an incoming type state, the `mergedCodeIsTypeSafe` predicate
checks that a merged stream of instructions and stack map frames is type
correct:

<div class="norm">

- If we have a stack map frame and an incoming type state, the type
  state must be assignable to the one in the stack map frame. We may
  then proceed to type check the rest of the stream with the type state
  given in the stack map frame.

  ``` programlisting
  mergedCodeIsTypeSafe(Environment, [stackMap(Offset, MapFrame) | MoreCode],
                       frame(Locals, OperandStack, Flags)) :-
      frameIsAssignable(frame(Locals, OperandStack, Flags), MapFrame),
      mergedCodeIsTypeSafe(Environment, MoreCode, MapFrame).
  ```

- A merged code stream is type safe relative to an incoming type state
  `T` if it begins with an instruction `I` that is type safe relative to
  `T`, and `I` <span class="emphasis">*satisfies*</span> its exception
  handlers (see below), and the tail of the stream is type safe given
  the type state following that execution of `I`.

  `NextStackFrame` indicates what falls through to the following
  instruction. For an unconditional branch instruction, it will have the
  special value `afterGoto`. `ExceptionStackFrame` indicates what is
  passed to exception handlers.

  ``` programlisting
  mergedCodeIsTypeSafe(Environment, [instruction(Offset, Parse) | MoreCode],
                       frame(Locals, OperandStack, Flags)) :-
      instructionIsTypeSafe(Parse, Environment, Offset,
                            frame(Locals, OperandStack, Flags),
                            NextStackFrame, ExceptionStackFrame),
      instructionSatisfiesHandlers(Environment, Offset, ExceptionStackFrame),
      mergedCodeIsTypeSafe(Environment, MoreCode, NextStackFrame).
  ```

- After an unconditional branch (indicated by an incoming type state of
  `afterGoto`), if we have a stack map frame giving the type state for
  the following instructions, we can proceed and type check them using
  the type state provided by the stack map frame.

  ``` programlisting
  mergedCodeIsTypeSafe(Environment, [stackMap(Offset, MapFrame) | MoreCode],
                       afterGoto) :-
      mergedCodeIsTypeSafe(Environment, MoreCode, MapFrame).
  ```

- It is illegal to have code after an unconditional branch without a
  stack map frame being provided for it.

  ``` programlisting
  mergedCodeIsTypeSafe(_Environment, [instruction(_, _) | _MoreCode],
                       afterGoto) :-
      write_ln('No stack frame after unconditional branch'),
      fail.
  ```

- If we have an unconditional branch at the end of the code, stop.

  ``` programlisting
  mergedCodeIsTypeSafe(_Environment, [endOfCode(Offset)],
                       afterGoto).
  ```

</div>

Branching to a target is type safe if the target has an associated stack
frame, `Frame`, and the current stack frame, `StackFrame`, is assignable
to `Frame`.

``` programlisting
targetIsTypeSafe(Environment, StackFrame, Target) :-
    offsetStackFrame(Environment, Target, Frame),
    frameIsAssignable(StackFrame, Frame).
```

An instruction <span class="emphasis">*satisfies its exception
handlers*</span> if it satisfies every exception handler that is
applicable to the instruction.

``` programlisting
instructionSatisfiesHandlers(Environment, Offset, ExceptionStackFrame) :-
    exceptionHandlers(Environment, Handlers),
    sublist(isApplicableHandler(Offset), Handlers, ApplicableHandlers),
    checklist(instructionSatisfiesHandler(Environment, ExceptionStackFrame),
              ApplicableHandlers).
```

An exception handler is <span class="emphasis">*applicable*</span> to an
instruction if the offset of the instruction is greater or equal to the
start of the handler's range and less than the end of the handler's
range.

``` programlisting
isApplicableHandler(Offset, handler(Start, End, _Target, _ClassName)) :-
    Offset >= Start,
    Offset < End.
```

An instruction <span class="emphasis">*satisfies*</span> an exception
handler if the instructions's outgoing type state is `ExcStackFrame`,
and the handler's target (the initial instruction of the handler code)
is type safe assuming an incoming type state `T`. The type state `T` is
derived from `ExcStackFrame` by replacing the operand stack with a stack
whose sole element is the handler's exception class.

``` programlisting
instructionSatisfiesHandler(Environment, ExcStackFrame, Handler) :-
    Handler = handler(_, _, Target, _),
    currentClassLoader(Environment, CurrentLoader),
    handlerExceptionClass(Handler, ExceptionClass, CurrentLoader),
    /* The stack consists of just the exception. */
    ExcStackFrame = frame(Locals, _, Flags),
    TrueExcStackFrame = frame(Locals, [ ExceptionClass ], Flags),
    operandStackHasLegalLength(Environment, TrueExcStackFrame),
    targetIsTypeSafe(Environment, TrueExcStackFrame, Target).
```

</div>

<div id="jvms-4.10.1.7" class="section">

<div class="titlepage">

<div>

<div>

#### 4.10.1.7. Type Checking Load and Store Instructions

</div>

</div>

</div>

All load instructions are variations on a common pattern, varying the
type of the value that the instruction loads.

Loading a value of type `Type` from local variable `Index` is type safe,
if the type of that local variable is `ActualType`, `ActualType` is
assignable to `Type`, and pushing `ActualType` onto the incoming operand
stack is a valid type transition
(<a href="jvms-4.html#jvms-4.10.1.4" class="xref"
title="4.10.1.4. Stack Map Frames and Type Transitions">§4.10.1.4</a>)
that yields a new type state `NextStackFrame`. After execution of the
load instruction, the type state will be `NextStackFrame`.

``` programlisting
loadIsTypeSafe(Environment, Index, Type, StackFrame, NextStackFrame) :-
    StackFrame = frame(Locals, _OperandStack, _Flags),
    nth0(Index, Locals, ActualType),
    isAssignable(ActualType, Type),
    validTypeTransition(Environment, [], ActualType, StackFrame,
                        NextStackFrame).
```

All store instructions are variations on a common pattern, varying the
type of the value that the instruction stores.

In general, a store instruction is type safe if the local variable it
references is of a type that is a supertype of `Type`, and the top of
the operand stack is of a subtype of `Type`, where `Type` is the type
the instruction is designed to store.

More precisely, the store is type safe if one can pop a type
`ActualType` that "matches" `Type` (that is, is a subtype of `Type`) off
the operand stack (<a href="jvms-4.html#jvms-4.10.1.4" class="xref"
title="4.10.1.4. Stack Map Frames and Type Transitions">§4.10.1.4</a>),
and then legally assign that type the local variable
`L`<sub>`Index`</sub>.

``` programlisting
storeIsTypeSafe(_Environment, Index, Type,
                frame(Locals, OperandStack, Flags),
                frame(NextLocals, NextOperandStack, Flags)) :-
    popMatchingType(OperandStack, Type, NextOperandStack, ActualType),
    modifyLocalVariable(Index, ActualType, Locals, NextLocals).
```

Given local variables `Locals`, modifying `Index` to have type `Type`
results in the local variable list `NewLocals`. The modifications are
somewhat involved, because some values (and their corresponding types)
occupy two local variables. Hence, modifying `L`<sub>`N`</sub> may
require modifying `L`<sub>`N+1`</sub> (because the type will occupy both
the `N` and `N+1` slots) or `L`<sub>`N-1`</sub> (because local `N` used
to be the upper half of the two word value/type starting at local `N-1`,
and so local `N-1` must be invalidated), or both. This is described
further below. We start at `L`<sub>`0`</sub> and count up.

``` programlisting
modifyLocalVariable(Index, Type, Locals, NewLocals) :-
    modifyLocalVariable(0, Index, Type, Locals, NewLocals).
```

Given `LocalsRest`, the suffix of the local variable list starting at
index `I`, modifying local variable `Index` to have type `Type` results
in the local variable list suffix `NextLocalsRest`.

If `I < Index-1`, just copy the input to the output and recurse forward.
If `I = Index-1`, the type of local `I` may change. This can occur if
`L`<sub>`I`</sub> has a type of size 2. Once we set `L`<sub>`I+1`</sub>
to the new type (and the corresponding value), the type/value of
`L`<sub>`I`</sub> will be invalidated, as its upper half will be
trashed. Then we recurse forward.

``` programlisting
modifyLocalVariable(I, Index, Type,
                    [Locals1 | LocalsRest],
                    [Locals1 | NextLocalsRest] ) :-
    I < Index - 1,
    I1 is I + 1,
    modifyLocalVariable(I1, Index, Type, LocalsRest, NextLocalsRest).

modifyLocalVariable(I, Index, Type,
                    [Locals1 | LocalsRest],
                    [NextLocals1 | NextLocalsRest] ) :-
    I =:= Index - 1,
    modifyPreIndexVariable(Locals1, NextLocals1),
    modifyLocalVariable(Index, Index, Type, LocalsRest, NextLocalsRest).
```

When we find the variable, and it only occupies one word, we change it
to `Type` and we're done. When we find the variable, and it occupies two
words, we change its type to `Type` and the next word to `top`.

``` programlisting
modifyLocalVariable(Index, Index, Type,
                    [_ | LocalsRest], [Type | LocalsRest]) :-
    sizeOf(Type, 1).

modifyLocalVariable(Index, Index, Type,
                    [_, _ | LocalsRest], [Type, top | LocalsRest]) :-
    sizeOf(Type, 2).
```

We refer to a local whose index immediately precedes a local whose type
will be modified as a <span class="emphasis">*pre-index
variable*</span>. The future type of a pre-index variable of type
`InputType` is `Result`. If the type, `Type`, of the pre-index local is
of size 1, it doesn't change. If the type of the pre-index local,
`Type`, is 2, we need to mark the lower half of its two word value as
unusable, by setting its type to `top`.

``` programlisting
modifyPreIndexVariable(Type, Type) :- sizeOf(Type, 1).
modifyPreIndexVariable(Type, top) :- sizeOf(Type, 2).
```

</div>

<div id="jvms-4.10.1.8" class="section">

<div class="titlepage">

<div>

<div>

#### 4.10.1.8. Type Checking for `protected` Members

</div>

</div>

</div>

All instructions that access members must contend with the rules
concerning `protected` members. This section describes the `protected`
check that corresponds to JLS §6.6.2.1.

The `protected` check applies only to `protected` members of
superclasses of the current class. `protected` members in other classes
will be caught by the access checking done at resolution
(<a href="jvms-5.html#jvms-5.4.4" class="xref"
title="5.4.4. Access Control">§5.4.4</a>). There are four cases:

<div class="norm">

- If the referenced type is not a class type with the same name as a
  superclass, it cannot be a superclass, and so it can safely be
  ignored.

  ``` programlisting
  passesProtectedCheck(Environment, class(MemberClassName, _), MemberName,
                       MemberDescriptor, StackFrame) :-
      thisClass(Environment, CurrentClass),
      \+ hasSuperclassWithName(CurrentClass, MemberClassName).

  passesProtectedCheck(Environment, arrayOf(_), MemberName,
                       MemberDescriptor, StackFrame).

  hasSuperclassWithName(Class, SuperclassName) :-
      loadedSuperclasses(Class, Supers),
      member(Super, Supers),
      classClassName(Super, SuperclassName).
  ```

- If the `MemberClassName` is the same as the name of a superclass, the
  class being resolved may indeed be a superclass. In this case, if no
  superclass named `MemberClassName` in a different run-time package has
  a `protected` member named `MemberName` with descriptor
  `MemberDescriptor`, the `protected` check does not apply.

  This is because the actual class being resolved will either be one of
  these superclasses, in which case we know that it is either in the
  same run-time package, and the access is legal; or the member in
  question is not `protected` and the check does not apply; or it will
  be a subclass, in which case the check would succeed anyway; or it
  will be some other class in the same run-time package, in which case
  the access is legal and the check need not take place; or the verifier
  need not flag this as a problem, since it will be caught anyway
  because resolution will per force fail.

  ``` programlisting
  passesProtectedCheck(Environment, class(MemberClassName, _), MemberName,
                       MemberDescriptor, StackFrame) :-
      thisClass(Environment, CurrentClass),
      hasSuperclassWithName(CurrentClass, MemberClassName),
      loadedSuperclasses(CurrentClass, Supers),
      classesInOtherPkgWithProtectedMember(
        CurrentClass, MemberName, MemberDescriptor, MemberClassName,
        Supers, []).
  ```

- If there does exist a `protected` superclass member in a different
  run-time package, then load `MemberClassName`; if the member in
  question is not `protected`, the check does not apply. (Using a
  superclass member that is not `protected` is trivially correct.)

  ``` programlisting
  passesProtectedCheck(Environment, class(MemberClassName, Loader),
                       MemberName, MemberDescriptor, StackFrame) :-
      thisClass(Environment, CurrentClass),
      hasSuperclassWithName(CurrentClass, MemberClassName),
      loadedSuperclasses(CurrentClass, Supers),
      classesInOtherPkgWithProtectedMember(
        CurrentClass, MemberName, MemberDescriptor, MemberClassName,
        Supers, List),
      List \= [],
      loadedClass(MemberClassName, Loader, ReferencedClass),
      isNotProtected(ReferencedClass, MemberName, MemberDescriptor).
  ```

- Otherwise, use of a member of an object of type `Target` requires that
  `Target` be assignable to the type of the current class.

  ``` programlisting
  passesProtectedCheck(Environment, class(MemberClassName, Loader),
                       MemberName, MemberDescriptor,
                       frame(_Locals, [Target | _Rest], _Flags)) :-
      thisClass(Environment, CurrentClass),
      hasSuperclassWithName(CurrentClass, MemberClassName),
      loadedSuperclasses(CurrentClass, Supers),
      classesInOtherPkgWithProtectedMember(
        CurrentClass, MemberName, MemberDescriptor, MemberClassName,
        Supers, List),
      List \= [],
      loadedClass(MemberClassName, Loader, ReferencedClass),
      isProtected(ReferencedClass, MemberName, MemberDescriptor),
      thisType(Environment, ThisType),
      isAssignable(Target, ThisType).
  ```

</div>

The predicate
`classesInOtherPkgWithProtectedMember(Class, MemberName, MemberDescriptor, MemberClassName, Supers, List)`
is true if `List` is the set of classes in `Supers` with name
`MemberClassName` that are in a different run-time package than `Class`
which declare a `protected` member named `MemberName` with descriptor
`MemberDescriptor`.

``` programlisting
classesInOtherPkgWithProtectedMember(_, _, _, _, [], []).

classesInOtherPkgWithProtectedMember(Class, MemberName,
                                     MemberDescriptor, MemberClassName,
                                     [Super | Tail], [Super | T]) :-
    classClassName(Super, MemberClassName),
    \+ sameRuntimePackage(Class, Super),
    isProtected(Super, MemberName, MemberDescriptor),
    classesInOtherPkgWithProtectedMember(
      Class, MemberName, MemberDescriptor, MemberClassName, Tail, T).

classesInOtherPkgWithProtectedMember(Class, MemberName,
                                     MemberDescriptor, MemberClassName,
                                     [Super | Tail], T) :-
    classClassName(Super, MemberClassName),
    \+ sameRuntimePackage(Class, Super),
    isNotProtected(Super, MemberName, MemberDescriptor),
    classesInOtherPkgWithProtectedMember(
      Class, MemberName, MemberDescriptor, MemberClassName, Tail, T).

classesInOtherPkgWithProtectedMember(Class, MemberName,
                                     MemberDescriptor, MemberClassName,
                                     [Super | Tail], T) :-
    classClassName(Super, MemberClassName),
    sameRuntimePackage(Class, Super),
    classesInOtherPkgWithProtectedMember(
      Class, MemberName, MemberDescriptor, MemberClassName, Tail, T).

classesInOtherPkgWithProtectedMember(Class, MemberName,
                                     MemberDescriptor, MemberClassName,
                                     [Super | Tail], T) :-
    classClassName(Super, SuperClassName),
    SuperClassName \= MemberClassName,
    classesInOtherPkgWithProtectedMember(
      Class, MemberName, MemberDescriptor, MemberClassName, Tail, T).

sameRuntimePackage(Class1, Class2) :-
    classDefiningLoader(Class1, L),
    classDefiningLoader(Class2, L),
    samePackageName(Class1, Class2).
```

</div>

<div id="jvms-4.10.1.9" class="section">

<div class="titlepage">

<div>

<div>

#### 4.10.1.9. Type Checking Instructions

</div>

</div>

</div>

In general, the type rule for an instruction is given relative to an
environment `Environment` that defines the class and method in which the
instruction occurs (<a href="jvms-4.html#jvms-4.10.1.1" class="xref"
title="4.10.1.1. Accessors for Java Virtual Machine Artifacts">§4.10.1.1</a>),
and the offset `Offset` within the method at which the instruction
occurs. The rule states that if the incoming type state `StackFrame`
fulfills certain requirements, then:

<div class="norm">

- The instruction is type safe.

- It is provable that the type state after the instruction completes
  normally has a particular form given by `NextStackFrame`, and that the
  type state after the instruction completes abruptly is given by
  `ExceptionStackFrame`.

  The type state after an instruction completes abruptly is the same as
  the incoming type state, except that the operand stack is empty.

  ``` programlisting
  exceptionStackFrame(StackFrame, ExceptionStackFrame) :-
      StackFrame = frame(Locals, _OperandStack, Flags),
      ExceptionStackFrame = frame(Locals, [], Flags).
      
  ```

</div>

Many instructions have type rules that are completely isomorphic to the
rules for other instructions. If an instruction `b1` is isomorphic to
another instruction `b2`, then the type rule for `b1` is the same as the
type rule for `b2`.

``` programlisting
instructionIsTypeSafe(Instruction, Environment, Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    instructionHasEquivalentTypeRule(Instruction, IsomorphicInstruction),
    instructionIsTypeSafe(IsomorphicInstruction, Environment, Offset,
                          StackFrame, NextStackFrame,
                          ExceptionStackFrame).
```

The English language description of each rule is intended to be
readable, intuitive, and concise. As such, the description avoids
repeating all the contextual assumptions given above. In particular:

<div class="norm">

- The description does not explicitly mention the environment.

- When the description speaks of the operand stack or local variables in
  the following, it is referring to the operand stack and local variable
  components of a type state: either the incoming type state or the
  outgoing one.

- The type state after the instruction completes abruptly is almost
  always identical to the incoming type state. The description only
  discusses the type state after the instruction completes abruptly when
  that is not the case.

- The description speaks of popping and pushing types onto the operand
  stack, and does not explicitly discuss issues of stack underflow or
  overflow. The description assumes these operations can be completed
  successfully, but the Prolog clauses for operand stack manipulation
  ensure that the necessary checks are made.

- The description discusses only the manipulation of logical types. In
  practice, some types take more than one word. The description
  abstracts from these representation details, but the Prolog clauses
  that manipulate data do not.

</div>

Any ambiguities can be resolved by referring to the formal Prolog
clauses.

<div id="jvms-4.10.1.9.aaload" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*aaload*</span>

</div>

</div>

</div>

An <span class="emphasis">*aaload*</span> instruction is type safe iff
one can validly replace types matching `int` and an array type with
component type `ComponentType` where `ComponentType` is a subtype of
`Object`, with `ComponentType` yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(aaload, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    nth1OperandStackIs(2, StackFrame, ArrayType),
    arrayComponentType(ArrayType, ComponentType),
    isBootstrapLoader(BL),
    validTypeTransition(Environment,
                        [int, arrayOf(class('java/lang/Object', BL))],
                        ComponentType, StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

The component type of an array of `X` is `X`. We define the component
type of `null` to be `null`.

``` programlisting
arrayComponentType(arrayOf(X), X).
arrayComponentType(null, null).
```

</div>

<div id="jvms-4.10.1.9.aastore" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*aastore*</span>

</div>

</div>

</div>

An <span class="emphasis">*aastore*</span> instruction is type safe iff
one can validly pop types matching `Object`, `int`, and an array of
`Object` off the incoming operand stack yielding the outgoing type
state.

``` programlisting
instructionIsTypeSafe(aastore, _Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    isBootstrapLoader(BL),
    canPop(StackFrame,
           [class('java/lang/Object', BL),
            int,
            arrayOf(class('java/lang/Object', BL))],
           NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.aconst_null" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*aconst_null*</span>

</div>

</div>

</div>

An <span class="emphasis">*aconst_null*</span> instruction is type safe
if one can validly push the type `null` onto the incoming operand stack
yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(aconst_null, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [], null, StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.aload" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*aload*</span>, <span class="emphasis">*aload\_\<n\>*</span>

</div>

</div>

</div>

An <span class="emphasis">*aload*</span> instruction with operand
`Index` is type safe and yields an outgoing type state `NextStackFrame`,
if a load instruction with operand `Index` and type `reference` is type
safe and yields an outgoing type state `NextStackFrame`.

``` programlisting
instructionIsTypeSafe(aload(Index), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    loadIsTypeSafe(Environment, Index, reference, StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

The instructions <span class="emphasis">*aload\_\<n\>*</span>, for 0
<span class="symbol">≤</span> <span class="emphasis">*n*</span>
<span class="symbol">≤</span> 3, are type safe iff the equivalent
<span class="emphasis">*aload*</span> instruction is type safe.

``` programlisting
instructionHasEquivalentTypeRule(aload_0, aload(0)).
instructionHasEquivalentTypeRule(aload_1, aload(1)).
instructionHasEquivalentTypeRule(aload_2, aload(2)).
instructionHasEquivalentTypeRule(aload_3, aload(3)).
```

</div>

<div id="jvms-4.10.1.9.anewarray" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*anewarray*</span>

</div>

</div>

</div>

An <span class="emphasis">*anewarray*</span> instruction with operand
`CP` is type safe iff `CP` refers to a constant pool entry denoting a
class, interface, or array type, and one can legally replace a type
matching `int` on the incoming operand stack with an array with
component type `CP` yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(anewarray(CP), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    (CP = class(_, _) ; CP = arrayOf(_)),
    validTypeTransition(Environment, [int], arrayOf(CP),
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.areturn" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*areturn*</span>

</div>

</div>

</div>

An <span class="emphasis">*areturn*</span> instruction is type safe iff
the enclosing method has a declared return type, `ReturnType`, that is a
`reference` type, and one can validly pop a type matching `ReturnType`
off the incoming operand stack.

``` programlisting
instructionIsTypeSafe(areturn, Environment, _Offset, StackFrame,
                      afterGoto, ExceptionStackFrame) :-
    thisMethodReturnType(Environment, ReturnType),
    isAssignable(ReturnType, reference),
    canPop(StackFrame, [ReturnType], _PoppedStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.arraylength" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*arraylength*</span>

</div>

</div>

</div>

An <span class="emphasis">*arraylength*</span> instruction is type safe
iff one can validly replace an array type on the incoming operand stack
with the type `int` yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(arraylength, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    nth1OperandStackIs(1, StackFrame, ArrayType),
    arrayComponentType(ArrayType, _),
    validTypeTransition(Environment, [top], int, StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.astore" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*astore*</span>, <span class="emphasis">*astore\_\<n\>*</span>

</div>

</div>

</div>

An <span class="emphasis">*astore*</span> instruction with operand
`Index` is type safe and yields an outgoing type state `NextStackFrame`,
if a store instruction with operand `Index` and type `reference` is type
safe and yields an outgoing type state `NextStackFrame`.

``` programlisting
instructionIsTypeSafe(astore(Index), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    storeIsTypeSafe(Environment, Index, reference, StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

The instructions <span class="emphasis">*astore\_\<n\>*</span>, for 0
<span class="symbol">≤</span> <span class="emphasis">*n*</span>
<span class="symbol">≤</span> 3, are type safe iff the equivalent
<span class="emphasis">*astore*</span> instruction is type safe.

``` programlisting
instructionHasEquivalentTypeRule(astore_0, astore(0)).
instructionHasEquivalentTypeRule(astore_1, astore(1)).
instructionHasEquivalentTypeRule(astore_2, astore(2)).
instructionHasEquivalentTypeRule(astore_3, astore(3)).
```

</div>

<div id="jvms-4.10.1.9.athrow" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*athrow*</span>

</div>

</div>

</div>

An <span class="emphasis">*athrow*</span> instruction is type safe iff
the top of the operand stack matches `Throwable`.

``` programlisting
instructionIsTypeSafe(athrow, _Environment, _Offset, StackFrame,
                      afterGoto, ExceptionStackFrame) :-
    isBootstrapLoader(BL),
    canPop(StackFrame, [class('java/lang/Throwable', BL)], _PoppedStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.baload" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*baload*</span>

</div>

</div>

</div>

A <span class="emphasis">*baload*</span> instruction is type safe iff
one can validly replace types matching `int` and a small array type on
the incoming operand stack with `int` yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(baload, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :
    nth1OperandStackIs(2, StackFrame, ArrayType),
    isSmallArray(ArrayType),
    validTypeTransition(Environment, [int, top], int,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

An array type is a <span class="emphasis">*small array type*</span> if
it is an array of `byte`, an array of `boolean`, or a subtype thereof
(`null`).

``` programlisting
isSmallArray(arrayOf(byte)).
isSmallArray(arrayOf(boolean)).
isSmallArray(null).
```

</div>

<div id="jvms-4.10.1.9.bastore" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*bastore*</span>

</div>

</div>

</div>

A <span class="emphasis">*bastore*</span> instruction is type safe iff
one can validly pop types matching `int`, `int` and a small array type
off the incoming operand stack yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(bastore, _Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    nth1OperandStackIs(3, StackFrame, ArrayType),
    isSmallArray(ArrayType),
    canPop(StackFrame, [int, int, top], NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.bipush" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*bipush*</span>

</div>

</div>

</div>

A <span class="emphasis">*bipush*</span> instruction is type safe iff
the equivalent <span class="emphasis">*sipush*</span> instruction is
type safe.

``` programlisting
instructionHasEquivalentTypeRule(bipush(Value), sipush(Value)).
```

</div>

<div id="jvms-4.10.1.9.caload" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*caload*</span>

</div>

</div>

</div>

A <span class="emphasis">*caload*</span> instruction is type safe iff
one can validly replace types matching `int` and array of `char` on the
incoming operand stack with `int` yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(caload, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [int, arrayOf(char)], int,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.castore" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*castore*</span>

</div>

</div>

</div>

A <span class="emphasis">*castore*</span> instruction is type safe iff
one can validly pop types matching `int`, `int` and array of `char` off
the incoming operand stack yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(castore, _Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    canPop(StackFrame, [int, int, arrayOf(char)], NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.checkcast" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*checkcast*</span>

</div>

</div>

</div>

A <span class="emphasis">*checkcast*</span> instruction with operand
`CP` is type safe iff `CP` refers to a constant pool entry denoting
either a class or an array, and one can validly replace the type
`Object` on top of the incoming operand stack with the type denoted by
`CP` yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(checkcast(CP), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    (CP = class(_, _) ; CP = arrayOf(_)),
    isBootstrapLoader(BL),
    validTypeTransition(Environment, [class('java/lang/Object', BL)], CP,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.d2f" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*d2f*</span>, <span class="emphasis">*d2i*</span>, <span class="emphasis">*d2l*</span>

</div>

</div>

</div>

A <span class="emphasis">*d2f*</span> instruction is type safe if one
can validly pop `double` off the incoming operand stack and replace it
with `float`, yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(d2f, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [double], float,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

A <span class="emphasis">*d2i*</span> instruction is type safe if one
can validly pop `double` off the incoming operand stack and replace it
with `int`, yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(d2i, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [double], int,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

A <span class="emphasis">*d2l*</span> instruction is type safe if one
can validly pop `double` off the incoming operand stack and replace it
with `long`, yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(d2l, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [double], long,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.dadd" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*dadd*</span>

</div>

</div>

</div>

A <span class="emphasis">*dadd*</span> instruction is type safe iff one
can validly replace types matching `double` and `double` on the incoming
operand stack with `double` yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(dadd, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [double, double], double,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.daload" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*daload*</span>

</div>

</div>

</div>

A <span class="emphasis">*daload*</span> instruction is type safe iff
one can validly replace types matching `int` and array of `double` on
the incoming operand stack with `double` yielding the outgoing type
state.

``` programlisting
instructionIsTypeSafe(daload, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [int, arrayOf(double)], double,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.dastore" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*dastore*</span>

</div>

</div>

</div>

A <span class="emphasis">*dastore*</span> instruction is type safe iff
one can validly pop types matching `double`, `int` and array of `double`
off the incoming operand stack yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(dastore, _Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    canPop(StackFrame, [double, int, arrayOf(double)], NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.dcmp_op" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*dcmp\<op\>*</span>

</div>

</div>

</div>

A <span class="emphasis">*dcmpg*</span> instruction is type safe iff one
can validly replace types matching `double` and `double` on the incoming
operand stack with `int` yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(dcmpg, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [double, double], int,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

A <span class="emphasis">*dcmpl*</span> instruction is type safe iff the
equivalent <span class="emphasis">*dcmpg*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(dcmpl, dcmpg).
```

</div>

<div id="jvms-4.10.1.9.dconst_d" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*dconst\_\<d\>*</span>

</div>

</div>

</div>

A <span class="emphasis">*dconst_0*</span> instruction is type safe if
one can validly push the type `double` onto the incoming operand stack
yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(dconst_0, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [], double, StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

A <span class="emphasis">*dconst_1*</span> instruction is type safe iff
the equivalent <span class="emphasis">*dconst_0*</span> instruction is
type safe.

``` programlisting
instructionHasEquivalentTypeRule(dconst_1, dconst_0).
```

</div>

<div id="jvms-4.10.1.9.ddiv" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*ddiv*</span>

</div>

</div>

</div>

A <span class="emphasis">*ddiv*</span> instruction is type safe iff the
equivalent <span class="emphasis">*dadd*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(ddiv, dadd).
```

</div>

<div id="jvms-4.10.1.9.dload" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*dload*</span>, <span class="emphasis">*dload\_\<n\>*</span>

</div>

</div>

</div>

A <span class="emphasis">*dload*</span> instruction with operand `Index`
is type safe and yields an outgoing type state `NextStackFrame`, if a
load instruction with operand `Index` and type `double` is type safe and
yields an outgoing type state `NextStackFrame`.

``` programlisting
instructionIsTypeSafe(dload(Index), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    loadIsTypeSafe(Environment, Index, double, StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

The instructions <span class="emphasis">*dload\_\<n\>*</span>, for 0
<span class="symbol">≤</span> <span class="emphasis">*n*</span>
<span class="symbol">≤</span> 3, are typesafe iff the equivalent
<span class="emphasis">*dload*</span> instruction is type safe.

``` programlisting
instructionHasEquivalentTypeRule(dload_0, dload(0)).
instructionHasEquivalentTypeRule(dload_1, dload(1)).
instructionHasEquivalentTypeRule(dload_2, dload(2)).
instructionHasEquivalentTypeRule(dload_3, dload(3)).
```

</div>

<div id="jvms-4.10.1.9.dmul" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*dmul*</span>

</div>

</div>

</div>

A <span class="emphasis">*dmul*</span> instruction is type safe iff the
equivalent <span class="emphasis">*dadd*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(dmul, dadd).
```

</div>

<div id="jvms-4.10.1.9.dneg" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*dneg*</span>

</div>

</div>

</div>

A <span class="emphasis">*dneg*</span> instruction is type safe iff
there is a type matching `double` on the incoming operand stack. The
<span class="emphasis">*dneg*</span> instruction does not alter the type
state.

``` programlisting
instructionIsTypeSafe(dneg, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [double], double,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.drem" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*drem*</span>

</div>

</div>

</div>

A <span class="emphasis">*drem*</span> instruction is type safe iff the
equivalent <span class="emphasis">*dadd*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(drem, dadd).
```

</div>

<div id="jvms-4.10.1.9.dreturn" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*dreturn*</span>

</div>

</div>

</div>

A <span class="emphasis">*dreturn*</span> instruction is type safe if
the enclosing method has a declared return type of `double`, and one can
validly pop a type matching `double` off the incoming operand stack.

``` programlisting
instructionIsTypeSafe(dreturn, Environment, _Offset, StackFrame,
                      afterGoto, ExceptionStackFrame) :-
    thisMethodReturnType(Environment, double),
    canPop(StackFrame, [double], _PoppedStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.dstore" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*dstore*</span>, <span class="emphasis">*dstore\_\<n\>*</span>

</div>

</div>

</div>

A <span class="emphasis">*dstore*</span> instruction with operand
`Index` is type safe and yields an outgoing type state `NextStackFrame`,
if a store instruction with operand `Index` and type `double` is type
safe and yields an outgoing type state `NextStackFrame`.

``` programlisting
instructionIsTypeSafe(dstore(Index), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    storeIsTypeSafe(Environment, Index, double, StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

The instructions <span class="emphasis">*dstore\_\<n\>*</span>, for 0
<span class="symbol">≤</span> <span class="emphasis">*n*</span>
<span class="symbol">≤</span> 3, are type safe iff the equivalent
<span class="emphasis">*dstore*</span> instruction is type safe.

``` programlisting
instructionHasEquivalentTypeRule(dstore_0, dstore(0)).
instructionHasEquivalentTypeRule(dstore_1, dstore(1)).
instructionHasEquivalentTypeRule(dstore_2, dstore(2)).
instructionHasEquivalentTypeRule(dstore_3, dstore(3)).
```

</div>

<div id="jvms-4.10.1.9.dsub" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*dsub*</span>

</div>

</div>

</div>

A <span class="emphasis">*dsub*</span> instruction is type safe iff the
equivalent <span class="emphasis">*dadd*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(dsub, dadd).
```

</div>

<div id="jvms-4.10.1.9.dup" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*dup*</span>

</div>

</div>

</div>

A <span class="emphasis">*dup*</span> instruction is type safe iff one
can validly replace a category 1 type, `Type`, with the types `Type`,
`Type`, yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(dup, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    StackFrame = frame(Locals, InputOperandStack, Flags),
    popCategory1(InputOperandStack, Type, _),
    canSafelyPush(Environment, InputOperandStack, Type, OutputOperandStack),
    NextStackFrame = frame(Locals, OutputOperandStack, Flags),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.dup_x1" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*dup_x1*</span>

</div>

</div>

</div>

A <span class="emphasis">*dup_x1*</span> instruction is type safe iff
one can validly replace two category 1 types, `Type1`, and `Type2`, on
the incoming operand stack with the types `Type1`, `Type2`, `Type1`,
yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(dup_x1, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    StackFrame = frame(Locals, InputOperandStack, Flags),
    popCategory1(InputOperandStack, Type1, Stack1),
    popCategory1(Stack1, Type2, Rest),
    canSafelyPushList(Environment, Rest, [Type1, Type2, Type1],
                      OutputOperandStack),
    NextStackFrame = frame(Locals, OutputOperandStack, Flags),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.dup_x2" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*dup_x2*</span>

</div>

</div>

</div>

A <span class="emphasis">*dup_x2*</span> instruction is type safe iff it
is a <span class="emphasis">*type safe form*</span> of the
<span class="emphasis">*dup_x2*</span> instruction.

``` programlisting
instructionIsTypeSafe(dup_x2, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    StackFrame = frame(Locals, InputOperandStack, Flags),
    dup_x2FormIsTypeSafe(Environment, InputOperandStack, OutputOperandStack),
    NextStackFrame = frame(Locals, OutputOperandStack, Flags),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

A <span class="emphasis">*dup_x2*</span> instruction is a
<span class="emphasis">*type safe form*</span> of the
<span class="emphasis">*dup_x2*</span> instruction iff it is a
<span class="emphasis">*type safe form 1*</span>
<span class="emphasis">*dup_x2*</span> instruction or a
<span class="emphasis">*type safe form 2*</span>
<span class="emphasis">*dup_x2*</span> instruction.

``` programlisting
dup_x2FormIsTypeSafe(Environment, InputOperandStack, OutputOperandStack) :-
    dup_x2Form1IsTypeSafe(Environment, InputOperandStack, OutputOperandStack).

dup_x2FormIsTypeSafe(Environment, InputOperandStack, OutputOperandStack) :-
    dup_x2Form2IsTypeSafe(Environment, InputOperandStack, OutputOperandStack).
```

A <span class="emphasis">*dup_x2*</span> instruction is a
<span class="emphasis">*type safe form 1*</span>
<span class="emphasis">*dup_x2*</span> instruction iff one can validly
replace three category 1 types, `Type1`, `Type2`, `Type3` on the
incoming operand stack with the types `Type1`, `Type2`, `Type3`,
`Type1`, yielding the outgoing type state.

``` programlisting
dup_x2Form1IsTypeSafe(Environment, InputOperandStack, OutputOperandStack) :-
    popCategory1(InputOperandStack, Type1, Stack1),
    popCategory1(Stack1, Type2, Stack2),
    popCategory1(Stack2, Type3, Rest),
    canSafelyPushList(Environment, Rest, [Type1, Type3, Type2, Type1],
                      OutputOperandStack).
```

A <span class="emphasis">*dup_x2*</span> instruction is a
<span class="emphasis">*type safe form 2*</span>
<span class="emphasis">*dup_x2*</span> instruction iff one can validly
replace a category 1 type, `Type1`, and a category 2 type, `Type2`, on
the incoming operand stack with the types `Type1`, `Type2`, `Type1`,
yielding the outgoing type state.

``` programlisting
dup_x2Form2IsTypeSafe(Environment, InputOperandStack, OutputOperandStack) :-
    popCategory1(InputOperandStack, Type1, Stack1),
    popCategory2(Stack1, Type2, Rest),
    canSafelyPushList(Environment, Rest, [Type1, Type2, Type1],
                      OutputOperandStack).
```

</div>

<div id="jvms-4.10.1.9.dup2" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*dup2*</span>

</div>

</div>

</div>

A <span class="emphasis">*dup2*</span> instruction is type safe iff it
is a <span class="emphasis">*type safe form*</span> of the
<span class="emphasis">*dup2*</span> instruction.

``` programlisting
instructionIsTypeSafe(dup2, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    StackFrame = frame(Locals, InputOperandStack, Flags),
    dup2FormIsTypeSafe(Environment,InputOperandStack, OutputOperandStack),
    NextStackFrame = frame(Locals, OutputOperandStack, Flags),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

A <span class="emphasis">*dup2*</span> instruction is a
<span class="emphasis">*type safe form*</span> of the
<span class="emphasis">*dup2*</span> instruction iff it is a
<span class="emphasis">*type safe form 1*</span>
<span class="emphasis">*dup2*</span> instruction or a
<span class="emphasis">*type safe form 2*</span>
<span class="emphasis">*dup2*</span> instruction.

``` programlisting
dup2FormIsTypeSafe(Environment, InputOperandStack, OutputOperandStack) :-
    dup2Form1IsTypeSafe(Environment,InputOperandStack, OutputOperandStack).

dup2FormIsTypeSafe(Environment, InputOperandStack, OutputOperandStack) :-
    dup2Form2IsTypeSafe(Environment,InputOperandStack, OutputOperandStack).
```

A <span class="emphasis">*dup2*</span> instruction is a
<span class="emphasis">*type safe form 1*</span>
<span class="emphasis">*dup2*</span> instruction iff one can validly
replace two category 1 types, `Type1` and `Type2` on the incoming
operand stack with the types `Type1`, `Type2`, `Type1`, `Type2`,
yielding the outgoing type state.

``` programlisting
dup2Form1IsTypeSafe(Environment, InputOperandStack, OutputOperandStack):-
    popCategory1(InputOperandStack, Type1, TempStack),
    popCategory1(TempStack, Type2, _),
    canSafelyPushList(Environment, InputOperandStack, [Type2, Type1],
                      OutputOperandStack).
```

A <span class="emphasis">*dup2*</span> instruction is a
<span class="emphasis">*type safe form 2*</span>
<span class="emphasis">*dup2*</span> instruction iff one can validly
replace a category 2 type, `Type` on the incoming operand stack with the
types `Type`, `Type`, yielding the outgoing type state.

``` programlisting
dup2Form2IsTypeSafe(Environment, InputOperandStack, OutputOperandStack):-
    popCategory2(InputOperandStack, Type, _),
    canSafelyPush(Environment, InputOperandStack, Type, OutputOperandStack).
```

</div>

<div id="jvms-4.10.1.9.dup2_x1" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*dup2_x1*</span>

</div>

</div>

</div>

A <span class="emphasis">*dup2_x1*</span> instruction is type safe iff
it is a <span class="emphasis">*type safe form*</span> of the
<span class="emphasis">*dup2_x1*</span> instruction.

``` programlisting
instructionIsTypeSafe(dup2_x1, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    StackFrame = frame(Locals, InputOperandStack, Flags),
    dup2_x1FormIsTypeSafe(Environment, InputOperandStack, OutputOperandStack),
    NextStackFrame = frame(Locals, OutputOperandStack, Flags),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

A <span class="emphasis">*dup2_x1*</span> instruction is a
<span class="emphasis">*type safe form*</span> of the
<span class="emphasis">*dup2_x1*</span> instruction iff it is a
<span class="emphasis">*type safe form 1*</span>
<span class="emphasis">*dup2_x1*</span> instruction or a
<span class="emphasis">*type safe form 2*</span>
<span class="emphasis">*dup_x2*</span> instruction.

``` programlisting
dup2_x1FormIsTypeSafe(Environment, InputOperandStack, OutputOperandStack) :-
    dup2_x1Form1IsTypeSafe(Environment, InputOperandStack, OutputOperandStack).

dup2_x1FormIsTypeSafe(Environment, InputOperandStack, OutputOperandStack) :-
    dup2_x1Form2IsTypeSafe(Environment, InputOperandStack, OutputOperandStack).
```

A <span class="emphasis">*dup2_x1*</span> instruction is a
<span class="emphasis">*type safe form 1*</span>
<span class="emphasis">*dup2_x1*</span> instruction iff one can validly
replace three category 1 types, `Type1`, `Type2`, `Type3`, on the
incoming operand stack with the types `Type1`, `Type2`, `Type3`,
`Type1`, `Type2`, yielding the outgoing type state.

``` programlisting
dup2_x1Form1IsTypeSafe(Environment, InputOperandStack, OutputOperandStack) :-
    popCategory1(InputOperandStack, Type1, Stack1),
    popCategory1(Stack1, Type2, Stack2),
    popCategory1(Stack2, Type3, Rest),
    canSafelyPushList(Environment, Rest, [Type2, Type1, Type3, Type2, Type1],
                      OutputOperandStack).
```

A <span class="emphasis">*dup2_x1*</span> instruction is a
<span class="emphasis">*type safe form 2*</span>
<span class="emphasis">*dup2_x1*</span> instruction iff one can validly
replace a category 2 type, `Type1`, and a category 1 type, `Type2`, on
the incoming operand stack with the types `Type1`, `Type2`, `Type1`,
yielding the outgoing type state.

``` programlisting
dup2_x1Form2IsTypeSafe(Environment, InputOperandStack, OutputOperandStack) :-
    popCategory2(InputOperandStack, Type1, Stack1),
    popCategory1(Stack1, Type2, Rest),
    canSafelyPushList(Environment, Rest, [Type1, Type2, Type1],
                      OutputOperandStack).
```

</div>

<div id="jvms-4.10.1.9.dup2_x2" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*dup2_x2*</span>

</div>

</div>

</div>

A <span class="emphasis">*dup2_x2*</span> instruction is type safe iff
it is a <span class="emphasis">*type safe form*</span> of the
<span class="emphasis">*dup2_x2*</span> instruction.

``` programlisting
instructionIsTypeSafe(dup2_x2, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    StackFrame = frame(Locals, InputOperandStack, Flags),
    dup2_x2FormIsTypeSafe(Environment, InputOperandStack, OutputOperandStack),
    NextStackFrame = frame(Locals, OutputOperandStack, Flags),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

A <span class="emphasis">*dup2_x2*</span> instruction is a
<span class="emphasis">*type safe form*</span> of the
<span class="emphasis">*dup2_x2*</span> instruction iff one of the
following holds:

<div class="norm">

- it is a <span class="emphasis">*type safe form 1*</span>
  <span class="emphasis">*dup2_x2*</span> instruction.

- it is a <span class="emphasis">*type safe form 2*</span>
  <span class="emphasis">*dup2_x2*</span> instruction.

- it is a <span class="emphasis">*type safe form 3*</span>
  <span class="emphasis">*dup2_x2*</span> instruction.

- it is a <span class="emphasis">*type safe form 4*</span>
  <span class="emphasis">*dup2_x2*</span> instruction.

</div>

``` programlisting
dup2_x2FormIsTypeSafe(Environment, InputOperandStack, OutputOperandStack) :-
    dup2_x2Form1IsTypeSafe(Environment, InputOperandStack, OutputOperandStack).

dup2_x2FormIsTypeSafe(Environment, InputOperandStack, OutputOperandStack) :-
    dup2_x2Form2IsTypeSafe(Environment, InputOperandStack, OutputOperandStack).

dup2_x2FormIsTypeSafe(Environment, InputOperandStack, OutputOperandStack) :-
    dup2_x2Form3IsTypeSafe(Environment, InputOperandStack, OutputOperandStack).

dup2_x2FormIsTypeSafe(Environment, InputOperandStack, OutputOperandStack) :-
    dup2_x2Form4IsTypeSafe(Environment, InputOperandStack, OutputOperandStack).
```

A <span class="emphasis">*dup2_x2*</span> instruction is a
<span class="emphasis">*type safe form 1*</span>
<span class="emphasis">*dup2_x2*</span> instruction iff one can validly
replace four category 1 types, `Type1`, `Type2`, `Type3`, `Type4`, on
the incoming operand stack with the types `Type1`, `Type2`, `Type3`,
`Type4`, `Type1`, `Type2`, yielding the outgoing type state.

``` programlisting
dup2_x2Form1IsTypeSafe(Environment, InputOperandStack, OutputOperandStack) :-
    popCategory1(InputOperandStack, Type1, Stack1),
    popCategory1(Stack1, Type2, Stack2),
    popCategory1(Stack2, Type3, Stack3),
    popCategory1(Stack3, Type4, Rest),
    canSafelyPushList(Environment, Rest,
                      [Type2, Type1, Type4, Type3, Type2, Type1],
                      OutputOperandStack).
```

A <span class="emphasis">*dup2_x2*</span> instruction is a
<span class="emphasis">*type safe form 2*</span>
<span class="emphasis">*dup2_x2*</span> instruction iff one can validly
replace a category 2 type, `Type1`, and two category 1 types, `Type2`,
`Type3`, on the incoming operand stack with the types `Type1`, `Type2`,
`Type3`, `Type1`, yielding the outgoing type state.

``` programlisting
dup2_x2Form2IsTypeSafe(Environment, InputOperandStack, OutputOperandStack) :-
    popCategory2(InputOperandStack, Type1, Stack1),
    popCategory1(Stack1, Type2, Stack2),
    popCategory1(Stack2, Type3, Rest),
    canSafelyPushList(Environment, Rest,
                      [Type1, Type3, Type2, Type1],
                      OutputOperandStack).
```

A <span class="emphasis">*dup2_x2*</span> instruction is a
<span class="emphasis">*type safe form 3*</span>
<span class="emphasis">*dup2_x2*</span> instruction iff one can validly
replace two category 1 types, `Type1`, `Type2`, and a category 2 type,
`Type3`, on the incoming operand stack with the types `Type1`, `Type2`,
`Type3`, `Type1`, `Type2`, yielding the outgoing type state.

``` programlisting
dup2_x2Form3IsTypeSafe(Environment, InputOperandStack, OutputOperandStack) :-
    popCategory1(InputOperandStack, Type1, Stack1),
    popCategory1(Stack1, Type2, Stack2),
    popCategory2(Stack2, Type3, Rest),
    canSafelyPushList(Environment, Rest,
                      [Type2, Type1, Type3, Type2, Type1],
                      OutputOperandStack).
```

A <span class="emphasis">*dup2_x2*</span> instruction is a
<span class="emphasis">*type safe form 4*</span>
<span class="emphasis">*dup2_x2*</span> instruction iff one can validly
replace two category 2 types, `Type1`, `Type2`, on the incoming operand
stack with the types `Type1`, `Type2`, `Type1`, yielding the outgoing
type state.

``` programlisting
dup2_x2Form4IsTypeSafe(Environment, InputOperandStack, OutputOperandStack) :-
    popCategory2(InputOperandStack, Type1, Stack1),
    popCategory2(Stack1, Type2, Rest),
    canSafelyPushList(Environment, Rest, [Type1, Type2, Type1],
                      OutputOperandStack).
```

</div>

<div id="jvms-4.10.1.9.f2d" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*f2d*</span>, <span class="emphasis">*f2i*</span>, <span class="emphasis">*f2l*</span>

</div>

</div>

</div>

An <span class="emphasis">*f2d*</span> instruction is type safe if one
can validly pop `float` off the incoming operand stack and replace it
with `double`, yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(f2d, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [float], double,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

An <span class="emphasis">*f2i*</span> instruction is type safe if one
can validly pop `float` off the incoming operand stack and replace it
with `int`, yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(f2i, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [float], int,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

An <span class="emphasis">*f2l*</span> instruction is type safe if one
can validly pop `float` off the incoming operand stack and replace it
with `long`, yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(f2l, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [float], long,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.fadd" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*fadd*</span>

</div>

</div>

</div>

An <span class="emphasis">*fadd*</span> instruction is type safe iff one
can validly replace types matching `float` and `float` on the incoming
operand stack with `float` yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(fadd, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [float, float], float,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.faload" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*faload*</span>

</div>

</div>

</div>

An <span class="emphasis">*faload*</span> instruction is type safe iff
one can validly replace types matching `int` and array of `float` on the
incoming operand stack with `float` yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(faload, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [int, arrayOf(float)], float,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.fastore" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*fastore*</span>

</div>

</div>

</div>

An <span class="emphasis">*fastore*</span> instruction is type safe iff
one can validly pop types matching `float`, `int` and array of `float`
off the incoming operand stack yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(fastore, _Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    canPop(StackFrame, [float, int, arrayOf(float)], NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.fcmp_op" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*fcmp\<op\>*</span>

</div>

</div>

</div>

An <span class="emphasis">*fcmpg*</span> instruction is type safe iff
one can validly replace types matching `float` and `float` on the
incoming operand stack with `int` yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(fcmpg, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [float, float], int,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

An <span class="emphasis">*fcmpl*</span> instruction is type safe iff
the equivalent <span class="emphasis">*fcmpg*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(fcmpl, fcmpg).
```

</div>

<div id="jvms-4.10.1.9.fconst_f" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*fconst\_\<f\>*</span>

</div>

</div>

</div>

An <span class="emphasis">*fconst_0*</span> instruction is type safe if
one can validly push the type `float` onto the incoming operand stack
yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(fconst_0, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [], float, StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

The rules for the other variants of
<span class="emphasis">*fconst*</span> are equivalent.

``` programlisting
instructionHasEquivalentTypeRule(fconst_1, fconst_0).
instructionHasEquivalentTypeRule(fconst_2, fconst_0).
```

</div>

<div id="jvms-4.10.1.9.fdiv" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*fdiv*</span>

</div>

</div>

</div>

An <span class="emphasis">*fdiv*</span> instruction is type safe iff the
equivalent <span class="emphasis">*fadd*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(fdiv, fadd).
```

</div>

<div id="jvms-4.10.1.9.fload" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*fload*</span>, <span class="emphasis">*fload\_\<n\>*</span>

</div>

</div>

</div>

An <span class="emphasis">*fload*</span> instruction with operand
`Index` is type safe and yields an outgoing type state `NextStackFrame`,
if a load instruction with operand `Index` and type `float` is type safe
and yields an outgoing type state `NextStackFrame`.

``` programlisting
instructionIsTypeSafe(fload(Index), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    loadIsTypeSafe(Environment, Index, float, StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

The instructions <span class="emphasis">*fload\_\<n\>*</span>, for 0
<span class="symbol">≤</span> <span class="emphasis">*n*</span>
<span class="symbol">≤</span> 3, are typesafe iff the equivalent
<span class="emphasis">*fload*</span> instruction is type safe.

``` programlisting
instructionHasEquivalentTypeRule(fload_0, fload(0)).
instructionHasEquivalentTypeRule(fload_1, fload(1)).
instructionHasEquivalentTypeRule(fload_2, fload(2)).
instructionHasEquivalentTypeRule(fload_3, fload(3)).
```

</div>

<div id="jvms-4.10.1.9.fmul" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*fmul*</span>

</div>

</div>

</div>

An <span class="emphasis">*fmul*</span> instruction is type safe iff the
equivalent <span class="emphasis">*fadd*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(fmul, fadd).
```

</div>

<div id="jvms-4.10.1.9.fneg" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*fneg*</span>

</div>

</div>

</div>

An <span class="emphasis">*fneg*</span> instruction is type safe iff
there is a type matching `float` on the incoming operand stack. The
<span class="emphasis">*fneg*</span> instruction does not alter the type
state.

``` programlisting
instructionIsTypeSafe(fneg, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [float], float,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.frem" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*frem*</span>

</div>

</div>

</div>

An <span class="emphasis">*frem*</span> instruction is type safe iff the
equivalent <span class="emphasis">*fadd*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(frem, fadd).
```

</div>

<div id="jvms-4.10.1.9.freturn" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*freturn*</span>

</div>

</div>

</div>

An <span class="emphasis">*freturn*</span> instruction is type safe if
the enclosing method has a declared return type of `float`, and one can
validly pop a type matching `float` off the incoming operand stack.

``` programlisting
instructionIsTypeSafe(freturn, Environment, _Offset, StackFrame,
                      afterGoto, ExceptionStackFrame) :-
    thisMethodReturnType(Environment, float),
    canPop(StackFrame, [float], _PoppedStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.fstore" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*fstore*</span>, <span class="emphasis">*fstore\_\<n\>*</span>

</div>

</div>

</div>

An <span class="emphasis">*fstore*</span> instruction with operand
`Index` is type safe and yields an outgoing type state `NextStackFrame`,
if a store instruction with operand `Index` and type `float` is type
safe and yields an outgoing type state `NextStackFrame`.

``` programlisting
instructionIsTypeSafe(fstore(Index), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    storeIsTypeSafe(Environment, Index, float, StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

The instructions <span class="emphasis">*fstore\_\<n\>*</span>, for 0
<span class="symbol">≤</span> <span class="emphasis">*n*</span>
<span class="symbol">≤</span> 3, are typesafe iff the equivalent
<span class="emphasis">*fstore*</span> instruction is type safe.

``` programlisting
instructionHasEquivalentTypeRule(fstore_0, fstore(0)).
instructionHasEquivalentTypeRule(fstore_1, fstore(1)).
instructionHasEquivalentTypeRule(fstore_2, fstore(2)).
instructionHasEquivalentTypeRule(fstore_3, fstore(3)).
```

</div>

<div id="jvms-4.10.1.9.fsub" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*fsub*</span>

</div>

</div>

</div>

An <span class="emphasis">*fsub*</span> instruction is type safe iff the
equivalent <span class="emphasis">*fadd*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(fsub, fadd).
```

</div>

<div id="jvms-4.10.1.9.getfield" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*getfield*</span>

</div>

</div>

</div>

A <span class="emphasis">*getfield*</span> instruction with operand `CP`
is type safe iff `CP` refers to a constant pool entry denoting a field
whose declared type is `FieldType` that is a member of a type
`FieldClassType`, and one can validly replace `FieldClassType` with
`FieldType` on the incoming operand stack yielding the outgoing type
state. `protected` fields are subject to additional checks
(<a href="jvms-4.html#jvms-4.10.1.8" class="xref"
title="4.10.1.8. Type Checking for protected Members">§4.10.1.8</a>).

``` programlisting
instructionIsTypeSafe(getfield(CP), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    CP = field(FieldClassType, FieldName, FieldDescriptor),
    parseFieldDescriptor(FieldDescriptor, FieldType),
    passesProtectedCheck(Environment, FieldClassType, FieldName,
                         FieldDescriptor, StackFrame),
    validTypeTransition(Environment, [FieldClassType], FieldType,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.getstatic" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*getstatic*</span>

</div>

</div>

</div>

A <span class="emphasis">*getstatic*</span> instruction with operand
`CP` is type safe iff `CP` refers to a constant pool entry denoting a
field whose declared type is `FieldType`, and one can validly push
`FieldType` on the incoming operand stack yielding the outgoing type
state.

``` programlisting
instructionIsTypeSafe(getstatic(CP), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    CP = field(_FieldClassType, _FieldName, FieldDescriptor),
    parseFieldDescriptor(FieldDescriptor, FieldType),
    validTypeTransition(Environment, [], FieldType,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.goto" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*goto*</span>, <span class="emphasis">*goto_w*</span>

</div>

</div>

</div>

A <span class="emphasis">*goto*</span> instruction is type safe iff its
target operand is a valid branch target.

``` programlisting
instructionIsTypeSafe(goto(Target), Environment, _Offset, StackFrame,
                      afterGoto, ExceptionStackFrame) :-
    targetIsTypeSafe(Environment, StackFrame, Target),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

A <span class="emphasis">*goto_w*</span> instruction is type safe iff
the equivalent <span class="emphasis">*goto*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(goto_w(Target), goto(Target)).
```

</div>

<div id="jvms-4.10.1.9.i2b" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*i2b*</span>, <span class="emphasis">*i2c*</span>, <span class="emphasis">*i2d*</span>, <span class="emphasis">*i2f*</span>, <span class="emphasis">*i2l*</span>, <span class="emphasis">*i2s*</span>

</div>

</div>

</div>

An <span class="emphasis">*i2b*</span> instruction is type safe iff the
equivalent <span class="emphasis">*ineg*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(i2b, ineg).
```

An <span class="emphasis">*i2c*</span> instruction is type safe iff the
equivalent <span class="emphasis">*ineg*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(i2c, ineg).
```

An <span class="emphasis">*i2d*</span> instruction is type safe if one
can validly pop `int` off the incoming operand stack and replace it with
`double`, yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(i2d, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [int], double,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

An <span class="emphasis">*i2f*</span> instruction is type safe if one
can validly pop `int` off the incoming operand stack and replace it with
`float`, yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(i2f, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [int], float,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

An <span class="emphasis">*i2l*</span> instruction is type safe if one
can validly pop `int` off the incoming operand stack and replace it with
`long`, yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(i2l, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [int], long,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

An <span class="emphasis">*i2s*</span> instruction is type safe iff the
equivalent <span class="emphasis">*ineg*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(i2s, ineg).
```

</div>

<div id="jvms-4.10.1.9.iadd" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*iadd*</span>

</div>

</div>

</div>

An <span class="emphasis">*iadd*</span> instruction is type safe iff one
can validly replace types matching `int` and `int` on the incoming
operand stack with `int` yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(iadd, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [int, int], int,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.iaload" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*iaload*</span>

</div>

</div>

</div>

An <span class="emphasis">*iaload*</span> instruction is type safe iff
one can validly replace types matching `int` and array of `int` on the
incoming operand stack with `int` yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(iaload, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [int, arrayOf(int)], int,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.iand" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*iand*</span>

</div>

</div>

</div>

An <span class="emphasis">*iand*</span> instruction is type safe iff the
equivalent <span class="emphasis">*iadd*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(iand, iadd).
```

</div>

<div id="jvms-4.10.1.9.iastore" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*iastore*</span>

</div>

</div>

</div>

An <span class="emphasis">*iastore*</span> instruction is type safe iff
one can validly pop types matching `int`, `int` and array of `int` off
the incoming operand stack yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(iastore, _Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    canPop(StackFrame, [int, int, arrayOf(int)], NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.iconst_i" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*iconst\_\<i\>*</span>

</div>

</div>

</div>

An <span class="emphasis">*iconst_m1*</span> instruction is type safe if
one can validly push the type `int` onto the incoming operand stack
yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(iconst_m1, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [], int, StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

The rules for the other variants of
<span class="emphasis">*iconst*</span> are equivalent.

``` programlisting
instructionHasEquivalentTypeRule(iconst_0, iconst_m1).
instructionHasEquivalentTypeRule(iconst_1, iconst_m1).
instructionHasEquivalentTypeRule(iconst_2, iconst_m1).
instructionHasEquivalentTypeRule(iconst_3, iconst_m1).
instructionHasEquivalentTypeRule(iconst_4, iconst_m1).
instructionHasEquivalentTypeRule(iconst_5, iconst_m1).
```

</div>

<div id="jvms-4.10.1.9.idiv" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*idiv*</span>

</div>

</div>

</div>

An <span class="emphasis">*idiv*</span> instruction is type safe iff the
equivalent <span class="emphasis">*iadd*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(idiv, iadd).
```

</div>

<div id="jvms-4.10.1.9.if_acmp_cond" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*if_acmp\<cond\>*</span>

</div>

</div>

</div>

An <span class="emphasis">*if_acmpeq*</span> instruction is type safe
iff one can validly pop types matching `reference` and `reference` on
the incoming operand stack yielding the outgoing type state
`NextStackFrame`, and the operand of the instruction, `Target`, is a
valid branch target assuming an incoming type state of `NextStackFrame`.

``` programlisting
instructionIsTypeSafe(if_acmpeq(Target), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    canPop(StackFrame, [reference, reference], NextStackFrame),
    targetIsTypeSafe(Environment, NextStackFrame, Target),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

The rule for <span class="emphasis">*if_acmpne*</span> is identical.

``` programlisting
instructionHasEquivalentTypeRule(if_acmpne(Target), if_acmpeq(Target)).
```

</div>

<div id="jvms-4.10.1.9.if_icmp_cond" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*if_icmp\<cond\>*</span>

</div>

</div>

</div>

An <span class="emphasis">*if_icmpeq*</span> instruction is type safe
iff one can validly pop types matching `int` and `int` on the incoming
operand stack yielding the outgoing type state `NextStackFrame`, and the
operand of the instruction, `Target`, is a valid branch target assuming
an incoming type state of `NextStackFrame`.

``` programlisting
instructionIsTypeSafe(if_icmpeq(Target), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    canPop(StackFrame, [int, int], NextStackFrame),
    targetIsTypeSafe(Environment, NextStackFrame, Target),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

The rules for all other variants of the
<span class="emphasis">*if_icmp\<cond\>*</span> instruction are
identical.

``` programlisting
instructionHasEquivalentTypeRule(if_icmpge(Target), if_icmpeq(Target)).
instructionHasEquivalentTypeRule(if_icmpgt(Target), if_icmpeq(Target)).
instructionHasEquivalentTypeRule(if_icmple(Target), if_icmpeq(Target)).
instructionHasEquivalentTypeRule(if_icmplt(Target), if_icmpeq(Target)).
instructionHasEquivalentTypeRule(if_icmpne(Target), if_icmpeq(Target)).
```

</div>

<div id="jvms-4.10.1.9.if_cond" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*if\<cond\>*</span>

</div>

</div>

</div>

An <span class="emphasis">*ifeq*</span> instruction is type safe iff one
can validly pop a type matching `int` off the incoming operand stack
yielding the outgoing type state `NextStackFrame`, and the operand of
the instruction, `Target`, is a valid branch target assuming an incoming
type state of `NextStackFrame`.

``` programlisting
instructionIsTypeSafe(ifeq(Target), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    canPop(StackFrame, [int], NextStackFrame),
    targetIsTypeSafe(Environment, NextStackFrame, Target),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

The rules for all other variations of the
<span class="emphasis">*if\<cond\>*</span> instruction are identical.

``` programlisting
instructionHasEquivalentTypeRule(ifge(Target), ifeq(Target)).
instructionHasEquivalentTypeRule(ifgt(Target), ifeq(Target)).
instructionHasEquivalentTypeRule(ifle(Target), ifeq(Target)).
instructionHasEquivalentTypeRule(iflt(Target), ifeq(Target)).
instructionHasEquivalentTypeRule(ifne(Target), ifeq(Target)).
```

</div>

<div id="jvms-4.10.1.9.ifnonnull" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*ifnonnull*</span>, <span class="emphasis">*ifnull*</span>

</div>

</div>

</div>

An <span class="emphasis">*ifnonnull*</span> instruction is type safe
iff one can validly pop a type matching `reference` off the incoming
operand stack yielding the outgoing type state `NextStackFrame`, and the
operand of the instruction, `Target`, is a valid branch target assuming
an incoming type state of `NextStackFrame`.

``` programlisting
instructionIsTypeSafe(ifnonnull(Target), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    canPop(StackFrame, [reference], NextStackFrame),
    targetIsTypeSafe(Environment, NextStackFrame, Target),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

An <span class="emphasis">*ifnull*</span> instruction is type safe iff
the equivalent <span class="emphasis">*ifnonnull*</span> instruction is
type safe.

``` programlisting
instructionHasEquivalentTypeRule(ifnull(Target), ifnonnull(Target)).
```

</div>

<div id="jvms-4.10.1.9.iinc" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*iinc*</span>

</div>

</div>

</div>

An <span class="emphasis">*iinc*</span> instruction with first operand
`Index` is type safe iff `L`<sub>`Index`</sub> has type `int`. The
<span class="emphasis">*iinc*</span> instruction does not change the
type state.

``` programlisting
instructionIsTypeSafe(iinc(Index, _Value), _Environment, _Offset,
                      StackFrame, StackFrame, ExceptionStackFrame) :-
    StackFrame = frame(Locals, _OperandStack, _Flags),
    nth0(Index, Locals, int),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.iload" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*iload*</span>, <span class="emphasis">*iload\_\<n\>*</span>

</div>

</div>

</div>

An <span class="emphasis">*iload*</span> instruction with operand
`Index` is type safe and yields an outgoing type state `NextStackFrame`,
if a load instruction with operand `Index` and type `int` is type safe
and yields an outgoing type state `NextStackFrame`.

``` programlisting
instructionIsTypeSafe(iload(Index), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    loadIsTypeSafe(Environment, Index, int, StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

The instructions <span class="emphasis">*iload\_\<n\>*</span>, for 0
<span class="symbol">≤</span> <span class="emphasis">*n*</span>
<span class="symbol">≤</span> 3, are typesafe iff the equivalent
<span class="emphasis">*iload*</span> instruction is type safe.

``` programlisting
instructionHasEquivalentTypeRule(iload_0, iload(0)).
instructionHasEquivalentTypeRule(iload_1, iload(1)).
instructionHasEquivalentTypeRule(iload_2, iload(2)).
instructionHasEquivalentTypeRule(iload_3, iload(3)).
```

</div>

<div id="jvms-4.10.1.9.imul" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*imul*</span>

</div>

</div>

</div>

An <span class="emphasis">*imul*</span> instruction is type safe iff the
equivalent <span class="emphasis">*iadd*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(imul, iadd).
```

</div>

<div id="jvms-4.10.1.9.ineg" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*ineg*</span>

</div>

</div>

</div>

An <span class="emphasis">*ineg*</span> instruction is type safe iff
there is a type matching `int` on the incoming operand stack. The
<span class="emphasis">*ineg*</span> instruction does not alter the type
state.

``` programlisting
instructionIsTypeSafe(ineg, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [int], int, StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.instanceof" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*instanceof*</span>

</div>

</div>

</div>

An <span class="emphasis">*instanceof*</span> instruction with operand
`CP` is type safe iff `CP` refers to a constant pool entry denoting
either a class or an array, and one can validly replace the type
`Object` on top of the incoming operand stack with type `int` yielding
the outgoing type state.

``` programlisting
instructionIsTypeSafe(instanceof(CP), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    (CP = class(_, _) ; CP = arrayOf(_)),
    isBootstrapLoader(BL),
    validTypeTransition(Environment, [class('java/lang/Object', BL)], int,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.invokedynamic" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*invokedynamic*</span>

</div>

</div>

</div>

An <span class="emphasis">*invokedynamic*</span> instruction is type
safe iff all of the following are true:

<div class="norm">

- Its first operand, `CP`, refers to a constant pool entry denoting an
  dynamic call site with name `CallSiteName` with descriptor
  `Descriptor`.

- `CallSiteName` is not `<init>`.

- `CallSiteName` is not `<clinit>`.

- One can validly replace types matching the argument types given in
  `Descriptor` on the incoming operand stack with the return type given
  in `Descriptor`, yielding the outgoing type state.

</div>

``` programlisting
instructionIsTypeSafe(invokedynamic(CP,0,0), Environment, _Offset,
                      StackFrame, NextStackFrame, ExceptionStackFrame) :-
    CP = dmethod(CallSiteName, Descriptor),
    CallSiteName \= '<init>',
    CallSiteName \= '<clinit>',
    parseMethodDescriptor(Descriptor, OperandArgList, ReturnType),
    reverse(OperandArgList, StackArgList),
    validTypeTransition(Environment, StackArgList, ReturnType,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.invokeinterface" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*invokeinterface*</span>

</div>

</div>

</div>

An <span class="emphasis">*invokeinterface*</span> instruction is type
safe iff all of the following are true:

<div class="norm">

- Its first operand, `CP`, refers to a constant pool entry denoting an
  interface method with descriptor `Descriptor` that is a member of a
  type `MethodClassType`.

- `MethodName` is not `<init>`.

- `MethodName` is not `<clinit>`.

- Its second operand, `Count`, is a valid count operand (see below).

- One can validly replace types matching `MethodClassType` and the
  argument types given in `Descriptor` on the incoming operand stack
  with the return type given in `Descriptor`, yielding the outgoing type
  state.

</div>

``` programlisting
instructionIsTypeSafe(invokeinterface(CP, Count, 0), Environment, _Offset,
                      StackFrame, NextStackFrame, ExceptionStackFrame) :-
    CP = imethod(MethodClassType, MethodName, Descriptor),
    MethodName \= '<init>',
    MethodName \= '<clinit>',
    parseMethodDescriptor(Descriptor, OperandArgList, ReturnType),
    reverse([MethodClassType | OperandArgList], StackArgList),
    canPop(StackFrame, StackArgList, TempFrame),
    validTypeTransition(Environment, [], ReturnType,
                        TempFrame, NextStackFrame),
    countIsValid(Count, StackFrame, TempFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

The `Count` operand of an
<span class="emphasis">*invokeinterface*</span> instruction is valid if
it equals the size of the arguments to the instruction. This is equal to
the difference between the size of `InputFrame` and `OutputFrame`.

``` programlisting
countIsValid(Count, InputFrame, OutputFrame) :-
    InputFrame = frame(_Locals1, OperandStack1, _Flags1),
    OutputFrame = frame(_Locals2, OperandStack2, _Flags2),
    length(OperandStack1, Length1),
    length(OperandStack2, Length2),
    Count =:= Length1 - Length2.
```

</div>

<div id="jvms-4.10.1.9.invokespecial" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*invokespecial*</span>

</div>

</div>

</div>

An <span class="emphasis">*invokespecial*</span> instruction is type
safe iff all of the following are true:

<div class="norm">

- Its first operand, `CP`, refers to a constant pool entry denoting a
  method named `MethodName` with descriptor `Descriptor` that is a
  member of a type `MethodClassType`.

- Either:

  <div class="norm">

  - `MethodName` is not `<init>`.

  - `MethodName` is not `<clinit>`.

  - `MethodClassType` is the current class, a superclass of the current
    class, or a direct superinterface of the current class.

  - One can validly replace types matching the current class and the
    argument types given in `Descriptor` on the incoming operand stack
    with the return type given in `Descriptor`, yielding the outgoing
    type state.

  </div>

</div>

``` programlisting
instructionIsTypeSafe(invokespecial(CP), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    (CP = method(MethodClassType, MethodName, Descriptor) ;
     CP = imethod(MethodClassType, MethodName, Descriptor)),
    MethodName \= '<init>',
    MethodName \= '<clinit>',
    validSpecialMethodClassType(Environment, MethodClassType),
    parseMethodDescriptor(Descriptor, OperandArgList, ReturnType),
    thisType(Environment, ThisType),
    reverse([ThisType | OperandArgList], StackArgList),
    validTypeTransition(Environment, StackArgList, ReturnType,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).

validSpecialMethodClassType(Environment, class(MethodClassName, _)) :-
    thisClass(Environment, ThisClass),
    classClassName(ThisClass, MethodClassName).

validSpecialMethodClassType(Environment, class(MethodClassName, L)) :-
    thisClass(Environment, ThisClass),
    loadedSuperclasses(ThisClass, Supers),
    member(Super, Supers),
    classClassName(Super, MethodClassName),
    loadedClass(MethodClassName, L, Super).

validSpecialMethodClassType(Environment, class(MethodClassName, _)) :-
    thisClass(Environment, ThisClass),
    classInterfaceNames(ThisClass, InterfaceNames),
    member(MethodClassName, InterfaceNames).
```

The `validSpecialMethodClassType` clause enforces the structural
constraint that <span class="emphasis">*invokespecial*</span>, for other
than an instance initialization method, must name a method in the
current class/interface or a superclass/superinterface.

The `validTypeTransition` clause enforces the structural constraint that
<span class="emphasis">*invokespecial*</span>, for other than an
instance initialization method, targets a receiver object of the current
class or deeper. To see why, consider that `StackArgList` simulates the
list of types on the operand stack expected by the method, starting with
the current class (the class performing
<span class="emphasis">*invokespecial*</span>). The actual types on the
operand stack are in `StackFrame`. The effect of `validTypeTransition`
is to pop the first type from the operand stack in `StackFrame` and
check it is a subtype of the first term of `StackArgList`, namely the
current class. Thus, the actual receiver type is compatible with the
current class.

A sharp-eyed reader might notice that enforcing this structural
constraint supercedes the structural constraint pertaining to
<span class="emphasis">*invokespecial*</span> of a `protected` method.
Thus, the Prolog code above makes no reference to `passesProtectedCheck`
(<a href="jvms-4.html#jvms-4.10.1.8" class="xref"
title="4.10.1.8. Type Checking for protected Members">§4.10.1.8</a>),
whereas the Prolog code for
<span class="emphasis">*invokespecial*</span> of an instance
initialization method uses `passesProtectedCheck` to ensure the actual
receiver type is compatible with the current class when certain
`protected` instance initialization methods are named.

<div class="norm">

- Or:

  <div class="norm">

  - MethodName is `<init>`.

  - `Descriptor` specifies a `void` return type.

  - One can validly pop types matching the argument types given in
    `Descriptor` and `uninitializedThis` off the incoming operand stack,
    yielding `OperandStack`.

  - `MethodClassType` is the current class or the direct superclass of
    the current class.

  - The outgoing type state is derived from the incoming type state by
    first replacing the incoming operand stack with `OperandStack` and
    then replacing all instances of `uninitializedThis` with the type of
    the current class.

  </div>

</div>

``` programlisting
instructionIsTypeSafe(invokespecial(CP), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    (CP = method(MethodClassType, '<init>', Descriptor) ;
     CP = imethod(MethodClassType, '<init>', Descriptor)),
    parseMethodDescriptor(Descriptor, OperandArgList, void),
    reverse([uninitializedThis | OperandArgList], StackArgList),
    canPop(StackFrame, StackArgList, frame(Locals, OperandStack, Flags)),
    validThisInitClassType(Environment, MethodClassType),
    thisType(Environment, This),
    substitute(uninitializedThis, This, OperandStack, NextOperandStack),
    substitute(uninitializedThis, This, Locals, NextLocals),
    substitute(uninitializedThis, top, Locals, ExceptionLocals),
    NextStackFrame = frame(NextLocals, NextOperandStack, []),
    ExceptionStackFrame = frame(ExceptionLocals, [], Flags).

validThisInitClassType(Environment, class(MethodClassName, _)) :-
    thisClass(Environment, ThisClass),
    classClassName(ThisClass, MethodClassName).

validThisInitClassType(Environment, class(MethodClassName, _)) :-
    thisClass(Environment, ThisClass),
    classSuperClassName(ThisClass, MethodClassName).

substitute(_Old, _New, [], []).
substitute(Old, New, [Old | FromRest], [New | ToRest]) :-
    substitute(Old, New, FromRest, ToRest).
substitute(Old, New, [From1 | FromRest], [From1 | ToRest]) :-
    From1 \= Old,
    substitute(Old, New, FromRest, ToRest).
```

<div class="norm">

- Or:

  <div class="norm">

  - MethodName is `<init>`.

  - `Descriptor` specifies a `void` return type.

  - One can validly pop types matching the argument types given in
    `Descriptor` and an uninitialized type, `uninitialized(Address)`,
    off the incoming operand stack, yielding `OperandStack`.

  - The instruction at `Address` created a new `MethodClassType`.

  - The outgoing type state is derived from the incoming type state by
    first replacing the incoming operand stack with `OperandStack` and
    then replacing all instances of `uninitialized(Address)` with
    `MethodClassType`.

  - If the method is `protected`, the usage conforms to the special
    rules governing access to `protected` members
    (<a href="jvms-4.html#jvms-4.10.1.8" class="xref"
    title="4.10.1.8. Type Checking for protected Members">§4.10.1.8</a>).

  </div>

</div>

``` programlisting
instructionIsTypeSafe(invokespecial(CP), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    (CP = method(MethodClassType, '<init>', Descriptor) ;
     CP = imethod(MethodClassType, '<init>', Descriptor)),
    parseMethodDescriptor(Descriptor, OperandArgList, void),
    reverse([uninitialized(Address) | OperandArgList], StackArgList),
    canPop(StackFrame, StackArgList, frame(Locals, OperandStack, Flags)),
    allInstructions(Environment, Instructions),
    member(instruction(Address, new(MethodClassType)), Instructions),
    substitute(uninitialized(Address), MethodClassType,
               OperandStack, NextOperandStack),
    substitute(uninitialized(Address), MethodClassType, Locals, NextLocals),
    substitute(uninitialized(Address), top, Locals, ExceptionLocals),
    NextStackFrame = frame(NextLocals, NextOperandStack, Flags),
    ExceptionStackFrame = frame(ExceptionLocals, [], Flags),
    passesProtectedCheck(Environment, MethodClassType, '<init>',
                         Descriptor, NextStackFrame).
```

The rule for <span class="emphasis">*invokespecial*</span> of an
`<init>` method is the sole motivation for passing back a distinct
exception stack frame. The concern is that when initializing an object,
the <span class="emphasis">*invokespecial*</span> invocation could fail,
leaving the object in a partially initialized, permanently unusable
state. To prevent repeated initialization attempts after an object fails
to initialize the first time, an exception handler must consider any
references to the object stored in local variables to have type `top`
rather than `uninitializedThis` or `uninitialized(Offset)`.

In the special case of initializing the current object (that is, when
invoking `<init>` for type `uninitializedThis`), the original frame
typically holds an uninitialized object in local variable 0 and has flag
`flagThisUninit`. Normal termination of
<span class="emphasis">*invokespecial*</span> initializes the
uninitialized object and turns off the `flagThisUninit` flag. But if the
<span class="emphasis">*invokespecial*</span> invocation throws an
exception, the exception frame contains the broken object (with type
`top`) and the `flagThisUninit` flag (the old flag). There is no way to
perform a return instruction given that type state, so the handler would
have to throw another exception (or loop forever). In fact, it's not
even possible to express a handler with that type state, because there
is no way for a stack frame, as expressed by the `StackMapTable`
attribute (<a href="jvms-4.html#jvms-4.7.4" class="xref"
title="4.7.4. The StackMapTable Attribute">§4.7.4</a>), to carry
`flagThisUninit` without any accompanying use of type
`uninitializedThis`.

If not for these special constraints on object initialization, the local
variable types and flags of the exception stack frame would always be
the same as the local variable types and flags of the input stack frame.

</div>

<div id="jvms-4.10.1.9.invokestatic" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*invokestatic*</span>

</div>

</div>

</div>

An <span class="emphasis">*invokestatic*</span> instruction is type safe
iff all of the following are true:

<div class="norm">

- Its first operand, `CP`, refers to a constant pool entry denoting a
  method named `MethodName` with descriptor `Descriptor`.

- `MethodName` is not `<init>`.

- `MethodName` is not `<clinit>`.

- One can validly replace types matching the argument types given in
  `Descriptor` on the incoming operand stack with the return type given
  in `Descriptor`, yielding the outgoing type state.

</div>

``` programlisting
instructionIsTypeSafe(invokestatic(CP), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    (CP = method(_MethodClassType, MethodName, Descriptor) ;
     CP = imethod(_MethodClassType, MethodName, Descriptor)),
    MethodName \= '<init>',
    MethodName \= '<clinit>',
    parseMethodDescriptor(Descriptor, OperandArgList, ReturnType),
    reverse(OperandArgList, StackArgList),
    validTypeTransition(Environment, StackArgList, ReturnType,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.invokevirtual" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*invokevirtual*</span>

</div>

</div>

</div>

An <span class="emphasis">*invokevirtual*</span> instruction is type
safe iff all of the following are true:

<div class="norm">

- Its first operand, `CP`, refers to a constant pool entry denoting a
  method named `MethodName` with descriptor `Descriptor` that is a
  member of a type `MethodClassType`.

- `MethodName` is not `<init>`.

- `MethodName` is not `<clinit>`.

- One can validly replace types matching `MethodClassType` and the
  argument types given in `Descriptor` on the incoming operand stack
  with the return type given in `Descriptor`, yielding the outgoing type
  state.

- If the method is `protected`, the usage conforms to the special rules
  governing access to `protected` members
  (<a href="jvms-4.html#jvms-4.10.1.8" class="xref"
  title="4.10.1.8. Type Checking for protected Members">§4.10.1.8</a>).

</div>

``` programlisting
instructionIsTypeSafe(invokevirtual(CP), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    CP = method(MethodClassType, MethodName, Descriptor),
    MethodName \= '<init>',
    MethodName \= '<clinit>',
    parseMethodDescriptor(Descriptor, OperandArgList, ReturnType),
    reverse(OperandArgList, ArgList),
    reverse([MethodClassType | OperandArgList], StackArgList),
    validTypeTransition(Environment, StackArgList, ReturnType,
                        StackFrame, NextStackFrame),
    canPop(StackFrame, ArgList, PoppedFrame),
    passesProtectedCheck(Environment, MethodClassType, MethodName,
                         Descriptor, PoppedFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.ior" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*ior*</span>, <span class="emphasis">*irem*</span>

</div>

</div>

</div>

An <span class="emphasis">*ior*</span> instruction is type safe iff the
equivalent <span class="emphasis">*iadd*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(ior, iadd).
```

An <span class="emphasis">*irem*</span> instruction is type safe iff the
equivalent <span class="emphasis">*iadd*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(irem, iadd).
```

</div>

<div id="jvms-4.10.1.9.ireturn" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*ireturn*</span>

</div>

</div>

</div>

An <span class="emphasis">*ireturn*</span> instruction is type safe if
the enclosing method has a declared return type of `int`, and one can
validly pop a type matching `int` off the incoming operand stack.

``` programlisting
instructionIsTypeSafe(ireturn, Environment, _Offset, StackFrame,
                      afterGoto, ExceptionStackFrame) :-
    thisMethodReturnType(Environment, int),
    canPop(StackFrame, [int], _PoppedStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.ishl" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*ishl*</span>, <span class="emphasis">*ishr*</span>, <span class="emphasis">*iushr*</span>

</div>

</div>

</div>

An <span class="emphasis">*ishl*</span> instruction is type safe iff the
equivalent <span class="emphasis">*iadd*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(ishl, iadd).
```

An <span class="emphasis">*ishr*</span> instruction is type safe iff the
equivalent <span class="emphasis">*iadd*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(ishr, iadd).
```

An <span class="emphasis">*iushr*</span> instruction is type safe iff
the equivalent <span class="emphasis">*iadd*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(iushr, iadd).
```

</div>

<div id="jvms-4.10.1.9.istore" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*istore*</span>, <span class="emphasis">*istore\_\<n\>*</span>

</div>

</div>

</div>

An <span class="emphasis">*istore*</span> instruction with operand
`Index` is type safe and yields an outgoing type state `NextStackFrame`,
if a store instruction with operand `Index` and type `int` is type safe
and yields an outgoing type state `NextStackFrame`.

``` programlisting
instructionIsTypeSafe(istore(Index), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    storeIsTypeSafe(Environment, Index, int, StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

The instructions <span class="emphasis">*istore\_\<n\>*</span>, for 0
<span class="symbol">≤</span> <span class="emphasis">*n*</span>
<span class="symbol">≤</span> 3, are type safe iff the equivalent
<span class="emphasis">*istore*</span> instruction is type safe.

``` programlisting
instructionHasEquivalentTypeRule(istore_0, istore(0)).
instructionHasEquivalentTypeRule(istore_1, istore(1)).
instructionHasEquivalentTypeRule(istore_2, istore(2)).
instructionHasEquivalentTypeRule(istore_3, istore(3)).
```

</div>

<div id="jvms-4.10.1.9.isub" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*isub*</span>, <span class="emphasis">*ixor*</span>

</div>

</div>

</div>

An <span class="emphasis">*isub*</span> instruction is type safe iff the
equivalent <span class="emphasis">*iadd*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(isub, iadd).
```

An <span class="emphasis">*ixor*</span> instruction is type safe iff the
equivalent <span class="emphasis">*iadd*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(ixor, iadd).
```

</div>

<div id="jvms-4.10.1.9.l2d" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*l2d*</span>, <span class="emphasis">*l2f*</span>, <span class="emphasis">*l2i*</span>

</div>

</div>

</div>

An <span class="emphasis">*l2d*</span> instruction is type safe if one
can validly pop `long` off the incoming operand stack and replace it
with `double`, yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(l2d, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [long], double,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

An <span class="emphasis">*l2f*</span> instruction is type safe if one
can validly pop `long` off the incoming operand stack and replace it
with `float`, yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(l2f, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [long], float,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

An <span class="emphasis">*l2i*</span> instruction is type safe if one
can validly pop `long` off the incoming operand stack and replace it
with `int`, yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(l2i, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [long], int,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.ladd" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*ladd*</span>

</div>

</div>

</div>

An <span class="emphasis">*ladd*</span> instruction is type safe iff one
can validly replace types matching `long` and `long` on the incoming
operand stack with `long` yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(ladd, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [long, long], long,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.laload" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*laload*</span>

</div>

</div>

</div>

An <span class="emphasis">*laload*</span> instruction is type safe iff
one can validly replace types matching `int` and array of `long` on the
incoming operand stack with `long` yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(laload, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [int, arrayOf(long)], long,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.land" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*land*</span>

</div>

</div>

</div>

An <span class="emphasis">*land*</span> instruction is type safe iff the
equivalent <span class="emphasis">*ladd*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(land, ladd).
```

</div>

<div id="jvms-4.10.1.9.lastore" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*lastore*</span>

</div>

</div>

</div>

An <span class="emphasis">*lastore*</span> instruction is type safe iff
one can validly pop types matching `long`, `int` and array of `long` off
the incoming operand stack yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(lastore, _Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    canPop(StackFrame, [long, int, arrayOf(long)], NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.lcmp" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*lcmp*</span>

</div>

</div>

</div>

A <span class="emphasis">*lcmp*</span> instruction is type safe iff one
can validly replace types matching `long` and `long` on the incoming
operand stack with `int` yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(lcmp, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [long, long], int,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.lconst_l" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*lconst\_\<l\>*</span>

</div>

</div>

</div>

An <span class="emphasis">*lconst_0*</span> instruction is type safe if
one can validly push the type `long` onto the incoming operand stack
yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(lconst_0, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [], long, StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

An <span class="emphasis">*lconst_1*</span> instruction is type safe iff
the equivalent <span class="emphasis">*lconst_0*</span> instruction is
type safe.

``` programlisting
instructionHasEquivalentTypeRule(lconst_1, lconst_0).
```

</div>

<div id="jvms-4.10.1.9.ldc" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*ldc*</span>, <span class="emphasis">*ldc_w*</span>, <span class="emphasis">*ldc2_w*</span>

</div>

</div>

</div>

An <span class="emphasis">*ldc*</span> instruction with operand `CP` is
type safe iff `CP` refers to a constant pool entry denoting an entity of
type `Type`, where `Type` is loadable
(<a href="jvms-4.html#jvms-4.4" class="xref"
title="4.4. The Constant Pool">§4.4</a>), but not `long` or `double`,
and one can validly push `Type` onto the incoming operand stack yielding
the outgoing type state.

``` programlisting
instructionIsTypeSafe(ldc(CP), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    loadableConstant(CP, Type),
    Type \= long,
    Type \= double,
    validTypeTransition(Environment, [], Type, StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).

loadableConstant(CP, Type) :-
    member([CP, Type], [
        [int(_),    int],
        [float(_),  float],
        [long(_),   long],
        [double(_), double]
    ]).

loadableConstant(CP, Type) :-
    isBootstrapLoader(BL),
    member([CP, Type], [
        [class(_,_),        class('java/lang/Class', BL)],
        [arrayOf(_),        class('java/lang/Class', BL)],
        [string(_),         class('java/lang/String', BL)],
        [methodHandle(_,_), class('java/lang/invoke/MethodHandle', BL)],
        [methodType(_,_),   class('java/lang/invoke/MethodType', BL)]
    ]).

loadableConstant(CP, Type) :-
    CP = dconstant(_, FieldDescriptor),
    parseFieldDescriptor(FieldDescriptor, Type).
```

An <span class="emphasis">*ldc_w*</span> instruction is type safe iff
the equivalent <span class="emphasis">*ldc*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(ldc_w(CP), ldc(CP))
```

An <span class="emphasis">*ldc2_w*</span> instruction with operand `CP`
is type safe iff `CP` refers to a constant pool entry denoting an entity
of type `Type`, where `Type` is either `long` or `double`, and one can
validly push `Type` onto the incoming operand stack yielding the
outgoing type state.

``` programlisting
instructionIsTypeSafe(ldc2_w(CP), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    loadableConstant(CP, Type),
    (Type = long ; Type = double),
    validTypeTransition(Environment, [], Type, StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.ldiv" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*ldiv*</span>

</div>

</div>

</div>

An <span class="emphasis">*ldiv*</span> instruction is type safe iff the
equivalent <span class="emphasis">*ladd*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(ldiv, ladd).
```

</div>

<div id="jvms-4.10.1.9.lload" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*lload*</span>, <span class="emphasis">*lload\_\<n\>*</span>

</div>

</div>

</div>

An <span class="emphasis">*lload*</span> instruction with operand
`Index` is type safe and yields an outgoing type state `NextStackFrame`,
if a load instruction with operand `Index` and type `long` is type safe
and yields an outgoing type state `NextStackFrame`.

``` programlisting
instructionIsTypeSafe(lload(Index), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    loadIsTypeSafe(Environment, Index, long, StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

The instructions <span class="emphasis">*lload\_\<n\>*</span>, for 0
<span class="symbol">≤</span> <span class="emphasis">*n*</span>
<span class="symbol">≤</span> 3, are type safe iff the equivalent
<span class="emphasis">*lload*</span> instruction is type safe.

``` programlisting
instructionHasEquivalentTypeRule(lload_0, lload(0)).
instructionHasEquivalentTypeRule(lload_1, lload(1)).
instructionHasEquivalentTypeRule(lload_2, lload(2)).
instructionHasEquivalentTypeRule(lload_3, lload(3)).
```

</div>

<div id="jvms-4.10.1.9.lmul" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*lmul*</span>

</div>

</div>

</div>

An <span class="emphasis">*lmul*</span> instruction is type safe iff the
equivalent <span class="emphasis">*ladd*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(lmul, ladd).
```

</div>

<div id="jvms-4.10.1.9.lneg" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*lneg*</span>

</div>

</div>

</div>

An <span class="emphasis">*lneg*</span> instruction is type safe iff
there is a type matching `long` on the incoming operand stack. The
<span class="emphasis">*lneg*</span> instruction does not alter the type
state.

``` programlisting
instructionIsTypeSafe(lneg, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [long], long,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.lookupswitch" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*lookupswitch*</span>

</div>

</div>

</div>

A <span class="emphasis">*lookupswitch*</span> instruction is type safe
if its keys are sorted, one can validly pop `int` off the incoming
operand stack yielding a new type state `BranchStackFrame`, and all of
the instruction's targets are valid branch targets assuming
`BranchStackFrame` as their incoming type state.

``` programlisting
instructionIsTypeSafe(lookupswitch(Targets, Keys), Environment, _, StackFrame,
                      afterGoto, ExceptionStackFrame) :-
    sort(Keys, Keys),
    canPop(StackFrame, [int], BranchStackFrame),
    checklist(targetIsTypeSafe(Environment, BranchStackFrame), Targets),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.lor" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*lor*</span>, <span class="emphasis">*lrem*</span>

</div>

</div>

</div>

A <span class="emphasis">*lor*</span> instruction is type safe iff the
equivalent <span class="emphasis">*ladd*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(lor, ladd).
```

An <span class="emphasis">*lrem*</span> instruction is type safe iff the
equivalent <span class="emphasis">*ladd*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(lrem, ladd).
```

</div>

<div id="jvms-4.10.1.9.lreturn" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*lreturn*</span>

</div>

</div>

</div>

An <span class="emphasis">*lreturn*</span> instruction is type safe if
the enclosing method has a declared return type of `long`, and one can
validly pop a type matching `long` off the incoming operand stack.

``` programlisting
instructionIsTypeSafe(lreturn, Environment, _Offset, StackFrame,
                      afterGoto, ExceptionStackFrame) :-
    thisMethodReturnType(Environment, long),
    canPop(StackFrame, [long], _PoppedStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.lshl" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*lshl*</span>, <span class="emphasis">*lshr*</span>, <span class="emphasis">*lushr*</span>

</div>

</div>

</div>

An <span class="emphasis">*lshl*</span> instruction is type safe if one
can validly replace the types `int` and `long` on the incoming operand
stack with the type `long` yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(lshl, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [int, long], long,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

An <span class="emphasis">*lshr*</span> instruction is type safe iff the
equivalent <span class="emphasis">*lshl*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(lshr, lshl).
```

An <span class="emphasis">*lushr*</span> instruction is type safe iff
the equivalent <span class="emphasis">*lshl*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(lushr, lshl).
```

</div>

<div id="jvms-4.10.1.9.lstore" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*lstore*</span>, <span class="emphasis">*lstore\_\<n\>*</span>

</div>

</div>

</div>

An <span class="emphasis">*lstore*</span> instruction with operand
`Index` is type safe and yields an outgoing type state `NextStackFrame`,
if a store instruction with operand `Index` and type `long` is type safe
and yields an outgoing type state `NextStackFrame`.

``` programlisting
instructionIsTypeSafe(lstore(Index), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    storeIsTypeSafe(Environment, Index, long, StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

The instructions <span class="emphasis">*lstore\_\<n\>*</span>, for 0
<span class="symbol">≤</span> <span class="emphasis">*n*</span>
<span class="symbol">≤</span> 3, are type safe iff the equivalent
<span class="emphasis">*lstore*</span> instruction is type safe.

``` programlisting
instructionHasEquivalentTypeRule(lstore_0, lstore(0)).
instructionHasEquivalentTypeRule(lstore_1, lstore(1)).
instructionHasEquivalentTypeRule(lstore_2, lstore(2)).
instructionHasEquivalentTypeRule(lstore_3, lstore(3)).
```

</div>

<div id="jvms-4.10.1.9.lsub" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*lsub*</span>, <span class="emphasis">*lxor*</span>

</div>

</div>

</div>

An <span class="emphasis">*lsub*</span> instruction is type safe iff the
equivalent <span class="emphasis">*ladd*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(lsub, ladd).
```

An <span class="emphasis">*lxor*</span> instruction is type safe iff the
equivalent <span class="emphasis">*ladd*</span> instruction is type
safe.

``` programlisting
instructionHasEquivalentTypeRule(lxor, ladd).
```

</div>

<div id="jvms-4.10.1.9.monitorenter" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*monitorenter*</span>, <span class="emphasis">*monitorexit*</span>

</div>

</div>

</div>

A <span class="emphasis">*monitorenter*</span> instruction is type safe
iff one can validly pop a type matching `reference` off the incoming
operand stack yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(monitorenter, _Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    canPop(StackFrame, [reference], NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

A <span class="emphasis">*monitorexit*</span> instruction is type safe
iff the equivalent <span class="emphasis">*monitorenter*</span>
instruction is type safe.

``` programlisting
instructionHasEquivalentTypeRule(monitorexit, monitorenter).
```

</div>

<div id="jvms-4.10.1.9.multianewarray" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*multianewarray*</span>

</div>

</div>

</div>

A <span class="emphasis">*multianewarray*</span> instruction with
operands `CP` and `Dim` is type safe iff `CP` refers to a constant pool
entry denoting an array type whose dimension is greater or equal to
`Dim`, `Dim` is strictly positive, and one can validly replace `Dim`
`int` types on the incoming operand stack with the type denoted by `CP`
yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(multianewarray(CP, Dim), Environment, _Offset,
                      StackFrame, NextStackFrame, ExceptionStackFrame) :-
    CP = arrayOf(_),
    arrayDimensions(CP, Dimensions),
    Dimensions >= Dim,
    Dim > 0,
    /* Make a list of Dim ints */
    findall(int, between(1, Dim, _), IntList),
    validTypeTransition(Environment, IntList, CP,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

The dimension of an array type whose component type is also an array
type is one more than the dimension of its component type.

``` programlisting
arrayDimensions(arrayOf(X), XDimensions + 1) :-
    arrayDimensions(X, XDimensions).

arrayDimensions(Type, 0) :-
    Type \= arrayOf(_).
```

</div>

<div id="jvms-4.10.1.9.new" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*new*</span>

</div>

</div>

</div>

A <span class="emphasis">*new*</span> instruction with operand `CP` at
offset `Offset` is type safe iff `CP` refers to a constant pool entry
denoting a class or interface type, the type `uninitialized(Offset)`
does not appear in the incoming operand stack, and one can validly push
`uninitialized(Offset)` onto the incoming operand stack and replace
`uninitialized(Offset)` with `top` in the incoming local variables
yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(new(CP), Environment, Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    StackFrame = frame(Locals, OperandStack, Flags),
    CP = class(_, _),
    NewItem = uninitialized(Offset),
    notMember(NewItem, OperandStack),
    substitute(NewItem, top, Locals, NewLocals),
    validTypeTransition(Environment, [], NewItem,
                        frame(NewLocals, OperandStack, Flags),
                        NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

The `substitute` predicate is defined in the rule for
<span class="emphasis">*invokespecial*</span>
(<a href="jvms-4.html#jvms-4.10.1.9.invokespecial" class="xref"
title="invokespecial">§<span
class="emphasis"><em>invokespecial</em></span></a>).

</div>

<div id="jvms-4.10.1.9.newarray" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*newarray*</span>

</div>

</div>

</div>

A <span class="emphasis">*newarray*</span> instruction with operand
`TypeCode` is type safe iff `TypeCode` corresponds to the primitive type
`ElementType`, and one can validly replace the type `int` on the
incoming operand stack with the type 'array of `ElementType`', yielding
the outgoing type state.

``` programlisting
instructionIsTypeSafe(newarray(TypeCode), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    primitiveArrayInfo(TypeCode, _TypeChar, ElementType, _VerifierType),
    validTypeTransition(Environment, [int], arrayOf(ElementType),
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

The correspondence between type codes and primitive types is specified
by the following predicate:

``` programlisting
primitiveArrayInfo(4,  0'Z, boolean, int).
primitiveArrayInfo(5,  0'C, char,    int).
primitiveArrayInfo(6,  0'F, float,   float).
primitiveArrayInfo(7,  0'D, double,  double).
primitiveArrayInfo(8,  0'B, byte,    int).
primitiveArrayInfo(9,  0'S, short,   int).
primitiveArrayInfo(10, 0'I, int,     int).
primitiveArrayInfo(11, 0'J, long,    long).
```

</div>

<div id="jvms-4.10.1.9.nop" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*nop*</span>

</div>

</div>

</div>

A <span class="emphasis">*nop*</span> instruction is always type safe.
The <span class="emphasis">*nop*</span> instruction does not affect the
type state.

``` programlisting
instructionIsTypeSafe(nop, _Environment, _Offset, StackFrame,
                      StackFrame, ExceptionStackFrame) :-
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.pop" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*pop*</span>, <span class="emphasis">*pop2*</span>

</div>

</div>

</div>

A <span class="emphasis">*pop*</span> instruction is type safe iff one
can validly pop a category 1 type off the incoming operand stack
yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(pop, _Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    StackFrame = frame(Locals, [Type | Rest], Flags),
    popCategory1([Type | Rest], Type, Rest),
    NextStackFrame = frame(Locals, Rest, Flags),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

A <span class="emphasis">*pop2*</span> instruction is type safe iff it
is a <span class="emphasis">*type safe form*</span> of the
<span class="emphasis">*pop2*</span> instruction.

``` programlisting
instructionIsTypeSafe(pop2, _Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    StackFrame = frame(Locals, InputOperandStack, Flags),
    pop2SomeFormIsTypeSafe(InputOperandStack, OutputOperandStack),
    NextStackFrame = frame(Locals, OutputOperandStack, Flags),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

A <span class="emphasis">*pop2*</span> instruction is a
<span class="emphasis">*type safe form*</span> of the
<span class="emphasis">*pop2*</span> instruction iff it is a
<span class="emphasis">*type safe form 1*</span>
<span class="emphasis">*pop2*</span> instruction or a
<span class="emphasis">*type safe form 2*</span>
<span class="emphasis">*pop2*</span> instruction.

``` programlisting
pop2SomeFormIsTypeSafe(InputOperandStack, OutputOperandStack) :-
    pop2Form1IsTypeSafe(InputOperandStack, OutputOperandStack).

pop2SomeFormIsTypeSafe(InputOperandStack, OutputOperandStack) :-
    pop2Form2IsTypeSafe(InputOperandStack, OutputOperandStack).
```

A <span class="emphasis">*pop2*</span> instruction is a
<span class="emphasis">*type safe form 1*</span>
<span class="emphasis">*pop2*</span> instruction iff one can validly pop
two types of size 1 off the incoming operand stack yielding the outgoing
type state.

``` programlisting
pop2Form1IsTypeSafe([Type1, Type2 | Rest], Rest) :-
    popCategory1([Type1 | Rest], Type1, Rest),
    popCategory1([Type2 | Rest], Type2, Rest).
```

A <span class="emphasis">*pop2*</span> instruction is a
<span class="emphasis">*type safe form 2*</span>
<span class="emphasis">*pop2*</span> instruction iff one can validly pop
a type of size 2 off the incoming operand stack yielding the outgoing
type state.

``` programlisting
pop2Form2IsTypeSafe([top, Type | Rest], Rest) :-
    popCategory2([top, Type | Rest], Type, Rest).
```

</div>

<div id="jvms-4.10.1.9.putfield" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*putfield*</span>

</div>

</div>

</div>

A <span class="emphasis">*putfield*</span> instruction with operand `CP`
is type safe iff all of the following are true:

<div class="norm">

- Its first operand, `CP`, refers to a constant pool entry denoting a
  field whose declared type is `FieldType` that is a member of a type
  `FieldClassType`.

- Either:

  <div class="norm">

  - One can validly pop types matching `FieldType` and `FieldClassType`
    off the incoming operand stack yielding the outgoing type state.

  - `protected` fields are subject to additional checks
    (<a href="jvms-4.html#jvms-4.10.1.8" class="xref"
    title="4.10.1.8. Type Checking for protected Members">§4.10.1.8</a>).

  </div>

</div>

``` programlisting
instructionIsTypeSafe(putfield(CP), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    CP = field(FieldClassType, FieldName, FieldDescriptor),
    parseFieldDescriptor(FieldDescriptor, FieldType),
    canPop(StackFrame, [FieldType], PoppedFrame),
    passesProtectedCheck(Environment, FieldClassType, FieldName,
                         FieldDescriptor, PoppedFrame),
    canPop(StackFrame, [FieldType, FieldClassType], NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

<div class="norm">

- Or:

  <div class="norm">

  - If the instruction occurs in an instance initialization method of
    the class named by `FieldClassType` and assigns to a field declared
    by the class, then one can validly pop types matching `FieldType`
    and `uninitializedThis` off the incoming operand stack yielding the
    outgoing type state. This allows instance fields of `this` that are
    declared in the current class to be assigned prior to complete
    initialization of `this`.

  </div>

</div>

``` programlisting
instructionIsTypeSafe(putfield(CP), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    CP = field(FieldClassType, FieldName, FieldDescriptor),
    thisType(Environment, FieldClassType),
    Environment = environment(CurrentClass, CurrentMethod, _, _, _, _),
    methodName(CurrentMethod, '<init>'),
    classDeclaresMember(CurrentClass, FieldName, FieldDescriptor),
    parseFieldDescriptor(FieldDescriptor, FieldType),
    canPop(StackFrame, [FieldType, uninitializedThis], NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.putstatic" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*putstatic*</span>

</div>

</div>

</div>

A <span class="emphasis">*putstatic*</span> instruction with operand
`CP` is type safe iff `CP` refers to a constant pool entry denoting a
field whose declared type is `FieldType`, and one can validly pop a type
matching `FieldType` off the incoming operand stack yielding the
outgoing type state.

``` programlisting
instructionIsTypeSafe(putstatic(CP), _Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    CP = field(_FieldClassType, _FieldName, FieldDescriptor),
    parseFieldDescriptor(FieldDescriptor, FieldType),
    canPop(StackFrame, [FieldType], NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.return" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*return*</span>

</div>

</div>

</div>

A <span class="emphasis">*return*</span> instruction is type safe if the
enclosing method declares a `void` return type, and either:

<div class="norm">

- The enclosing method is not an `<init>` method, or

- `this` has already been completely initialized at the point where the
  instruction occurs.

</div>

``` programlisting
instructionIsTypeSafe(return, Environment, _Offset, StackFrame,
                      afterGoto, ExceptionStackFrame) :-
    thisMethodReturnType(Environment, void),
    StackFrame = frame(_Locals, _OperandStack, Flags),
    notMember(flagThisUninit, Flags),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.saload" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*saload*</span>

</div>

</div>

</div>

An <span class="emphasis">*saload*</span> instruction is type safe iff
one can validly replace types matching `int` and array of `short` on the
incoming operand stack with `int` yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(saload, Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [int, arrayOf(short)], int,
                        StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.sastore" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*sastore*</span>

</div>

</div>

</div>

An <span class="emphasis">*sastore*</span> instruction is type safe iff
one can validly pop types matching `int`, `int`, and array of `short`
off the incoming operand stack yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(sastore, _Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    canPop(StackFrame, [int, int, arrayOf(short)], NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.sipush" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*sipush*</span>

</div>

</div>

</div>

An <span class="emphasis">*sipush*</span> instruction is type safe iff
one can validly push the type `int` onto the incoming operand stack
yielding the outgoing type state.

``` programlisting
instructionIsTypeSafe(sipush(_Value), Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    validTypeTransition(Environment, [], int, StackFrame, NextStackFrame),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.swap" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*swap*</span>

</div>

</div>

</div>

A <span class="emphasis">*swap*</span> instruction is type safe iff one
can validly replace two category 1 types, `Type1` and `Type2`, on the
incoming operand stack with the types `Type2` and `Type1` yielding the
outgoing type state.

``` programlisting
instructionIsTypeSafe(swap, _Environment, _Offset, StackFrame,
                      NextStackFrame, ExceptionStackFrame) :-
    StackFrame = frame(_Locals, [Type1, Type2 | Rest], _Flags),
    popCategory1([Type1 | Rest], Type1, Rest),
    popCategory1([Type2 | Rest], Type2, Rest),
    NextStackFrame = frame(_Locals, [Type2, Type1 | Rest], _Flags),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.tableswitch" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*tableswitch*</span>

</div>

</div>

</div>

A <span class="emphasis">*tableswitch*</span> instruction is type safe
if its keys are sorted, one can validly pop `int` off the incoming
operand stack yielding a new type state `BranchStackFrame`, and all of
the instruction's targets are valid branch targets assuming
`BranchStackFrame` as their incoming type state.

``` programlisting
instructionIsTypeSafe(tableswitch(Targets, Keys), Environment, _Offset,
                      StackFrame, afterGoto, ExceptionStackFrame) :-
    sort(Keys, Keys),
    canPop(StackFrame, [int], BranchStackFrame),
    checklist(targetIsTypeSafe(Environment, BranchStackFrame), Targets),
    exceptionStackFrame(StackFrame, ExceptionStackFrame).
```

</div>

<div id="jvms-4.10.1.9.wide" class="section-verification">

<div class="titlepage">

<div>

<div>

##### <span class="emphasis">*wide*</span>

</div>

</div>

</div>

The <span class="emphasis">*wide*</span> instructions follow the same
rules as the instructions they widen.

``` programlisting
instructionHasEquivalentTypeRule(wide(WidenedInstruction),
                                 WidenedInstruction).
```

</div>

</div>

</div>

<div id="jvms-4.10.2" class="section">

<div class="titlepage">

<div>

<div>

### 4.10.2. Verification by Type Inference

</div>

</div>

</div>

A `class` file that does not contain a `StackMapTable` attribute (which
necessarily has a version number of 49.0 or below) must be verified
using type inference.

<div id="jvms-4.10.2.1" class="section">

<div class="titlepage">

<div>

<div>

#### 4.10.2.1. The Process of Verification by Type Inference

</div>

</div>

</div>

During linking, the verifier checks the `code` array of the `Code`
attribute for each method of the `class` file by performing data-flow
analysis on each method. The verifier ensures that at any given point in
the program, no matter what code path is taken to reach that point, all
of the following are true:

<div class="norm">

- The operand stack is always the same size and contains the same types
  of values.

- No local variable is accessed unless it is known to contain a value of
  an appropriate type.

- Methods are invoked with the appropriate arguments.

- Fields are assigned only using values of appropriate types.

- All opcodes have appropriately typed arguments on the operand stack
  and in the local variable array.

</div>

For efficiency reasons, certain tests that could in principle be
performed by the verifier are delayed until the first time the code for
the method is actually invoked. In so doing, the verifier avoids loading
`class` files unless it has to.

For example, if a method invokes another method that returns an instance
of class <span class="type">A</span>, and that instance is assigned only
to a field of the same type, the verifier does not bother to check if
the class <span class="type">A</span> actually exists. However, if it is
assigned to a field of the type <span class="type">B</span>, the
definitions of both <span class="type">A</span> and
<span class="type">B</span> must be loaded in to ensure that
<span class="type">A</span> is a subclass of
<span class="type">B</span>.

</div>

<div id="jvms-4.10.2.2" class="section">

<div class="titlepage">

<div>

<div>

#### 4.10.2.2. The Bytecode Verifier

</div>

</div>

</div>

The code for each method is verified independently. First, the bytes
that make up the code are broken up into a sequence of instructions, and
the index into the `code` array of the start of each instruction is
placed in an array. The verifier then goes through the code a second
time and parses the instructions. During this pass a data structure is
built to hold information about each Java Virtual Machine instruction in
the method. The operands, if any, of each instruction are checked to
make sure they are valid. For instance:

<div class="norm">

- Branches must be within the bounds of the `code` array for the method.

- The targets of all control-flow instructions are each the start of an
  instruction. In the case of a <span class="emphasis">*wide*</span>
  instruction, the <span class="emphasis">*wide*</span> opcode is
  considered the start of the instruction, and the opcode giving the
  operation modified by that <span class="emphasis">*wide*</span>
  instruction is not considered to start an instruction. Branches into
  the middle of an instruction are disallowed.

- No instruction can access or modify a local variable at an index
  greater than or equal to the number of local variables that its method
  indicates it allocates.

- All references to the constant pool must be to an entry of the
  appropriate type. (For example, the instruction
  <span class="emphasis">*getfield*</span> must reference a field.)

- The code does not end in the middle of an instruction.

- Execution cannot fall off the end of the code.

- For each exception handler, the starting and ending point of code
  protected by the handler must be at the beginning of an instruction
  or, in the case of the ending point, immediately past the end of the
  code. The starting point must be before the ending point. The
  exception handler code must start at a valid instruction, and it must
  not start at an opcode being modified by the
  <span class="emphasis">*wide*</span> instruction.

</div>

For each instruction of the method, the verifier records the contents of
the operand stack and the contents of the local variable array prior to
the execution of that instruction. For the operand stack, it needs to
know the stack height and the type of each value on it. For each local
variable, it needs to know either the type of the contents of that local
variable or that the local variable contains an unusable or unknown
value (it might be uninitialized). The bytecode verifier does not need
to distinguish between the integral types (e.g., `byte`, `short`,
`char`) when determining the value types on the operand stack.

Next, a data-flow analyzer is initialized. For the first instruction of
the method, the local variables that represent parameters initially
contain values of the types indicated by the method's type descriptor;
the operand stack is empty. All other local variables contain an illegal
value. For the other instructions, which have not been examined yet, no
information is available regarding the operand stack or local variables.

Finally, the data-flow analyzer is run. For each instruction, a
"changed" bit indicates whether this instruction needs to be looked at.
Initially, the "changed" bit is set only for the first instruction. The
data-flow analyzer executes the following loop:

<div class="orderedlist">

1.  Select a Java Virtual Machine instruction whose "changed" bit is
    set. If no instruction remains whose "changed" bit is set, the
    method has successfully been verified. Otherwise, turn off the
    "changed" bit of the selected instruction.

2.  Model the effect of the instruction on the operand stack and local
    variable array by doing the following:

    <div class="norm">

    - If the instruction uses values from the operand stack, ensure that
      there are a sufficient number of values on the stack and that the
      top values on the stack are of an appropriate type. Otherwise,
      verification fails.

    - If the instruction uses a local variable, ensure that the
      specified local variable contains a value of the appropriate type.
      Otherwise, verification fails.

    - If the instruction pushes values onto the operand stack, ensure
      that there is sufficient room on the operand stack for the new
      values. Add the indicated types to the top of the modeled operand
      stack.

    - If the instruction modifies a local variable, record that the
      local variable now contains the new type.

    </div>

3.  Determine the instructions that can follow the current instruction.
    Successor instructions can be one of the following:

    <div class="norm">

    - The next instruction, if the current instruction is not an
      unconditional control transfer instruction (for instance,
      <span class="emphasis">*goto*</span>,
      <span class="emphasis">*return*</span>, or
      <span class="emphasis">*athrow*</span>). Verification fails if it
      is possible to "fall off" the last instruction of the method.

    - The target(s) of a conditional or unconditional branch or switch.

    - Any exception handlers for this instruction.

    </div>

4.  Merge the state of the operand stack and local variable array at the
    end of the execution of the current instruction into each of the
    successor instructions, as follows:

    <div class="norm">

    - If this is the first time the successor instruction has been
      visited, record that the operand stack and local variable values
      calculated in step 2 are the state of the operand stack and local
      variable array prior to executing the successor instruction. Set
      the "changed" bit for the successor instruction.

    - If the successor instruction has been seen before, merge the
      operand stack and local variable values calculated in step 2 into
      the values already there. Set the "changed" bit if there is any
      modification to the values.

    </div>

    In the special case of control transfer to an exception handler:

    <div class="norm">

    - Record that a single object, of the exception type indicated by
      the exception handler, is the state of the operand stack prior to
      executing the successor instruction. There must be sufficient room
      on the operand stack for this single value, as if an instruction
      had pushed it.

    - Record that the local variable values from immediately before step
      2 are the state of the local variable array prior to executing the
      successor instruction. The local variable values calculated in
      step 2 are irrelevant.

    </div>

5.  Continue at step 1.

</div>

To merge two operand stacks, the number of values on each stack must be
identical. The types of values on the stacks must also be identical,
except that differently typed `reference` values may appear at
corresponding places on the two stacks. In this case, the merged operand
stack contains a reference type representing the first common
superclass, superinterface, or array supertype of the two types. Such a
`reference` type always exists because the type `Object` is a superclass
of all class, interface, and array types. If the operand stacks cannot
be merged, verification of the method fails.

To merge two local variable array states, corresponding pairs of local
variables are compared. The value of the merged local variable is
computed using the rules above, except that the corresponding values are
permitted to be different primitive types. In that case, the verifier
records that the merged local variable contains an unusable value.

If the data-flow analyzer runs on a method without reporting a
verification failure, then the method has been successfully verified by
the `class` file verifier.

Certain instructions and data types complicate the data-flow analyzer.
We now examine each of these in more detail.

</div>

<div id="jvms-4.10.2.3" class="section">

<div class="titlepage">

<div>

<div>

#### 4.10.2.3. Values of Types `long` and `double`

</div>

</div>

</div>

Values of the `long` and `double` types are treated specially by the
verification process.

Whenever a value of type `long` or `double` is moved into a local
variable at index <span class="emphasis">*n*</span>, index
<span class="emphasis">*n*</span>+1 is specially marked to indicate that
it has been reserved by the value at index
<span class="emphasis">*n*</span> and must not be used as a local
variable index. Any value previously at index
<span class="emphasis">*n*</span>+1 becomes unusable.

Whenever a value is moved to a local variable at index
<span class="emphasis">*n*</span>, the index
<span class="emphasis">*n*</span>-1 is examined to see if it is the
index of a value of type `long` or `double`. If so, the local variable
at index <span class="emphasis">*n*</span>-1 is changed to indicate that
it now contains an unusable value. Since the local variable at index
<span class="emphasis">*n*</span> has been overwritten, the local
variable at index <span class="emphasis">*n*</span>-1 cannot represent a
value of type `long` or `double`.

Dealing with values of types `long` or `double` on the operand stack is
simpler; the verifier treats them as single values on the stack. For
example, the verification code for the
<span class="emphasis">*dadd*</span> opcode (add two `double` values)
checks that the top two items on the stack are both of type `double`.
When calculating operand stack length, values of type `long` and
`double` have length two.

Untyped instructions that manipulate the operand stack must treat values
of type `long` and `double` as atomic (indivisible). For example, the
verifier reports a failure if the top value on the stack is a `double`
and it encounters an instruction such as
<span class="emphasis">*pop*</span> or
<span class="emphasis">*dup*</span>. The instructions
<span class="emphasis">*pop2*</span> or
<span class="emphasis">*dup2*</span> must be used instead.

</div>

<div id="jvms-4.10.2.4" class="section">

<div class="titlepage">

<div>

<div>

#### 4.10.2.4. Instance Initialization Methods and Newly Created Objects

</div>

</div>

</div>

Creating a new class instance is a multistep process. The statement:

``` programlisting
...
new myClass(i, j, k);
...
```

can be implemented by the following:

``` programlisting
...
new #1            // Allocate uninitialized space for myClass
dup               // Duplicate object on the operand stack
iload_1           // Push i
iload_2           // Push j
iload_3           // Push k
invokespecial #5  // Invoke myClass.<init>
...
```

This instruction sequence leaves the newly created and initialized
object on top of the operand stack. (Additional examples of compilation
to the instruction set of the Java Virtual Machine are given in
<a href="jvms-3.html" class="xref"
title="Chapter 3. Compiling for the Java Virtual Machine">§3
(<em>Compiling for the Java Virtual Machine</em>)</a>.)

The instance initialization method
(<a href="jvms-2.html#jvms-2.9.1" class="xref"
title="2.9.1. Instance Initialization Methods">§2.9.1</a>) for class
`myClass` sees the new uninitialized object as its `this` argument in
local variable 0. Before that method invokes another instance
initialization method of `myClass` or its direct superclass on `this`,
the only operation the method can perform on `this` is assigning fields
declared within `myClass`.

When doing dataflow analysis on instance methods, the verifier
initializes local variable 0 to contain an object of the current class,
or, for instance initialization methods, local variable 0 contains a
special type indicating an uninitialized object. After an appropriate
instance initialization method is invoked (from the current class or its
direct superclass) on this object, all occurrences of this special type
on the verifier's model of the operand stack and in the local variable
array are replaced by the current class type. The verifier rejects code
that uses the new object before it has been initialized or that
initializes the object more than once. In addition, it ensures that
every normal return of the method has invoked an instance initialization
method either in the class of this method or in the direct superclass.

Similarly, a special type is created and pushed on the verifier's model
of the operand stack as the result of the Java Virtual Machine
instruction <span class="emphasis">*new*</span>. The special type
indicates the instruction by which the class instance was created and
the type of the uninitialized class instance created. When an instance
initialization method declared in the class of the uninitialized class
instance is invoked on that class instance, all occurrences of the
special type are replaced by the intended type of the class instance.
This change in type may propagate to subsequent instructions as the
dataflow analysis proceeds.

The instruction number needs to be stored as part of the special type,
as there may be multiple not-yet-initialized instances of a class in
existence on the operand stack at one time. For example, the Java
Virtual Machine instruction sequence that implements:

``` programlisting
new InputStream(new Foo(), new InputStream("foo"))
```

may have two uninitialized instances of `InputStream` on the operand
stack at once. When an instance initialization method is invoked on a
class instance, only those occurrences of the special type on the
operand stack or in the local variable array that are the same object as
the class instance are replaced.

</div>

<div id="jvms-4.10.2.5" class="section">

<div class="titlepage">

<div>

<div>

#### 4.10.2.5. Exceptions and `finally`

</div>

</div>

</div>

To implement the `try`-`finally` construct, a compiler for the Java
programming language that generates `class` files with version number
50.0 or below may use the exception-handling facilities together with
two special instructions: <span class="emphasis">*jsr*</span> ("jump to
subroutine") and <span class="emphasis">*ret*</span> ("return from
subroutine"). The `finally` clause is compiled as a subroutine within
the Java Virtual Machine code for its method, much like the code for an
exception handler. When a <span class="emphasis">*jsr*</span>
instruction that invokes the subroutine is executed, it pushes its
return address, the address of the instruction after the
<span class="emphasis">*jsr*</span> that is being executed, onto the
operand stack as a value of type `returnAddress`. The code for the
subroutine stores the return address in a local variable. At the end of
the subroutine, a <span class="emphasis">*ret*</span> instruction
fetches the return address from the local variable and transfers control
to the instruction at the return address.

Control can be transferred to the `finally` clause (the `finally`
subroutine can be invoked) in several different ways. If the `try`
clause completes normally, the `finally` subroutine is invoked via a
<span class="emphasis">*jsr*</span> instruction before evaluating the
next expression. A `break` or `continue` inside the `try` clause that
transfers control outside the `try` clause executes a
<span class="emphasis">*jsr*</span> to the code for the `finally` clause
first. If the `try` clause executes a
<span class="emphasis">*return*</span>, the compiled code does the
following:

<div class="orderedlist">

1.  Saves the return value (if any) in a local variable.

2.  Executes a <span class="emphasis">*jsr*</span> to the code for the
    `finally` clause.

3.  Upon return from the `finally` clause, returns the value saved in
    the local variable.

</div>

The compiler sets up a special exception handler, which catches any
exception thrown by the `try` clause. If an exception is thrown in the
`try` clause, this exception handler does the following:

<div class="orderedlist">

1.  Saves the exception in a local variable.

2.  Executes a <span class="emphasis">*jsr*</span> to the `finally`
    clause.

3.  Upon return from the `finally` clause, rethrows the exception.

</div>

For more information about the implementation of the `try`-`finally`
construct, see <a href="jvms-3.html#jvms-3.13" class="xref"
title="3.13. Compiling finally">§3.13</a>.

The code for the `finally` clause presents a special problem to the
verifier. Usually, if a particular instruction can be reached via
multiple paths and a particular local variable contains incompatible
values through those multiple paths, then the local variable becomes
unusable. However, a `finally` clause might be called from several
different places, yielding several different circumstances:

<div class="norm">

- The invocation from the exception handler may have a certain local
  variable that contains an exception.

- The invocation to implement <span class="emphasis">*return*</span> may
  have some local variable that contains the return value.

- The invocation from the bottom of the `try` clause may have an
  indeterminate value in that same local variable.

</div>

The code for the `finally` clause itself might pass verification, but
after completing the updating all the successors of the
<span class="emphasis">*ret*</span> instruction, the verifier would note
that the local variable that the exception handler expects to hold an
exception, or that the return code expects to hold a return value, now
contains an indeterminate value.

Verifying code that contains a `finally` clause is complicated. The
basic idea is the following:

<div class="norm">

- Each instruction keeps track of the list of
  <span class="emphasis">*jsr*</span> targets needed to reach that
  instruction. For most code, this list is empty. For instructions
  inside code for the `finally` clause, it is of length one. For
  multiply nested `finally` code (extremely rare!), it may be longer
  than one.

- For each instruction and each <span class="emphasis">*jsr*</span>
  needed to reach that instruction, a bit vector is maintained of all
  local variables accessed or modified since the execution of the
  <span class="emphasis">*jsr*</span> instruction.

- When executing the <span class="emphasis">*ret*</span> instruction,
  which implements a return from a subroutine, there must be only one
  possible subroutine from which the instruction can be returning. Two
  different subroutines cannot "merge" their execution to a single
  <span class="emphasis">*ret*</span> instruction.

- To perform the data-flow analysis on a
  <span class="emphasis">*ret*</span> instruction, a special procedure
  is used. Since the verifier knows the subroutine from which the
  instruction must be returning, it can find all the
  <span class="emphasis">*jsr*</span> instructions that call the
  subroutine and merge the state of the operand stack and local variable
  array at the time of the <span class="emphasis">*ret*</span>
  instruction into the operand stack and local variable array of the
  instructions following the <span class="emphasis">*jsr*</span>.
  Merging uses a special set of values for local variables:

  <div class="norm">

  - For any local variable that the bit vector (constructed above)
    indicates has been accessed or modified by the subroutine, use the
    type of the local variable at the time of the
    <span class="emphasis">*ret*</span>.

  - For other local variables, use the type of the local variable before
    the <span class="emphasis">*jsr*</span> instruction.

  </div>

</div>

</div>

</div>

</div>

<div id="jvms-4.11" class="section">

<div class="titlepage">

<div>

<div>

## 4.11. Limitations of the Java Virtual Machine

</div>

</div>

</div>

The following limitations of the Java Virtual Machine are implicit in
the `class` file format:

<div class="norm">

- The per-class or per-interface constant pool is limited to 65535
  entries by the 16-bit `constant_pool_count` field of the `ClassFile`
  structure (<a href="jvms-4.html#jvms-4.1" class="xref"
  title="4.1. The ClassFile Structure">§4.1</a>). This acts as an
  internal limit on the total complexity of a single class or interface.

- The number of fields that may be declared by a class or interface is
  limited to 65535 by the size of the `fields_count` item of the
  `ClassFile` structure (<a href="jvms-4.html#jvms-4.1" class="xref"
  title="4.1. The ClassFile Structure">§4.1</a>).

  Note that the value of the `fields_count` item of the `ClassFile`
  structure does not include fields that are inherited from superclasses
  or superinterfaces.

- The number of methods that may be declared by a class or interface is
  limited to 65535 by the size of the `methods_count` item of the
  `ClassFile` structure (<a href="jvms-4.html#jvms-4.1" class="xref"
  title="4.1. The ClassFile Structure">§4.1</a>).

  Note that the value of the `methods_count` item of the `ClassFile`
  structure does not include methods that are inherited from
  superclasses or superinterfaces.

- The number of direct superinterfaces of a class or interface is
  limited to 65535 by the size of the `interfaces_count` item of the
  `ClassFile` structure (<a href="jvms-4.html#jvms-4.1" class="xref"
  title="4.1. The ClassFile Structure">§4.1</a>).

- The greatest number of local variables in the local variables array of
  a frame created upon invocation of a method
  (<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>)
  is limited to 65535 by the size of the `max_locals` item of the `Code`
  attribute (<a href="jvms-4.html#jvms-4.7.3" class="xref"
  title="4.7.3. The Code Attribute">§4.7.3</a>) giving the code of the
  method, and by the 16-bit local variable indexing of the Java Virtual
  Machine instruction set.

  Note that values of type `long` and `double` are each considered to
  reserve two local variables and contribute two units toward the
  `max_locals` value, so use of local variables of those types further
  reduces this limit.

- The size of an operand stack in a frame
  (<a href="jvms-2.html#jvms-2.6" class="xref" title="2.6. Frames">§2.6</a>)
  is limited to 65535 values by the `max_stack` field of the `Code`
  attribute (<a href="jvms-4.html#jvms-4.7.3" class="xref"
  title="4.7.3. The Code Attribute">§4.7.3</a>).

  Note that values of type `long` and `double` are each considered to
  contribute two units toward the `max_stack` value, so use of values of
  these types on the operand stack further reduces this limit.

- The number of method parameters is limited to 255 by the definition of
  a method descriptor (<a href="jvms-4.html#jvms-4.3.3" class="xref"
  title="4.3.3. Method Descriptors">§4.3.3</a>), where the limit
  includes one unit for `this` in the case of instance or interface
  method invocations.

  Note that a method descriptor is defined in terms of a notion of
  method parameter length in which a parameter of type `long` or
  `double` contributes two units to the length, so parameters of these
  types further reduce the limit.

- The length of field and method names, field and method descriptors,
  and other constant string values (including those referenced by
  `ConstantValue` (<a href="jvms-4.html#jvms-4.7.2" class="xref"
  title="4.7.2. The ConstantValue Attribute">§4.7.2</a>) attributes) is
  limited to 65535 characters by the 16-bit unsigned `length` item of
  the `CONSTANT_Utf8_info` structure
  (<a href="jvms-4.html#jvms-4.4.7" class="xref"
  title="4.4.7. The CONSTANT_Utf8_info Structure">§4.4.7</a>).

  Note that the limit is on the number of bytes in the encoding and not
  on the number of encoded characters. UTF-8 encodes some characters
  using two or three bytes. Thus, strings incorporating multibyte
  characters are further constrained.

- The number of dimensions in an array is limited to 255 by the size of
  the <span class="emphasis">*dimensions*</span> opcode of the
  <span class="emphasis">*multianewarray*</span> instruction and by the
  constraints imposed on the
  <span class="emphasis">*multianewarray*</span>,
  <span class="emphasis">*anewarray*</span>, and
  <span class="emphasis">*newarray*</span> instructions
  (<a href="jvms-4.html#jvms-4.9.1" class="xref"
  title="4.9.1. Static Constraints">§4.9.1</a>,
  <a href="jvms-4.html#jvms-4.9.2" class="xref"
  title="4.9.2. Structural Constraints">§4.9.2</a>).

</div>

</div>

</div>

<div class="navfooter">

------------------------------------------------------------------------

|  |  |  |
|:---|:--:|---:|
| <a href="jvms-3.html" accesskey="p">Prev</a>  |   |  <a href="jvms-5.html" accesskey="n">Next</a> |
| Chapter 3. Compiling for the Java Virtual Machine  | <a href="index.html" accesskey="h">Home</a> |  Chapter 5. Loading, Linking, and Initializing |

</div>

<div class="navfooter">

------------------------------------------------------------------------

[Legal Notice](spec-frontmatter.html)

</div>
