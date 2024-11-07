.globl isPrimeAssembly

isPrimeAssembly:
    MOV     x4, x0
    MOV     x5, x1
    MOV     x6, x2
    MOV     x7, x3
    MOV     x8, #0
    MOV     x9, #0
    MOV     x10, #0
    MOV     x15, x30
    BL      processArray

processArray:
    CMP     x8, x7
    BGE     endLoop
    LDR     x0, [x4, x8, LSL #3]
    BL      isPrime
    CBZ     x0, nonPrime

Prime:
    LDR     x0, [x4, x8, LSL #3]
    STR     x0, [x5, x9, LSL #3]
    ADD     x9, x9, #1
    B       incrementCount

nonPrime:
    LDR     x0, [x4, x8, LSL #3]
    STR     x0, [x6, x10, LSL #3]
    ADD     x10, x10, #1

incrementCount:
    ADD     x8, x8, #1
    B       processArray

endLoop:
    MOV     x30, x15
    BR      x30

isPrime:
    MOV     x11, x0
    MOV     x12, #2

conditional:
    LSR     x13, x11, #1
    CMP     x12, x13
    BGT     return1

divide:
    UDIV    x14, x11, x12
    MUL     x14, x14, x12
    CMP     x11, x14
    BEQ     return0

increment:
    ADD     x12, x12, #1
    B       conditional

return0:
    MOVZ    x0, #0
    B       exit

return1:
    MOVZ    x0, #1
    B       exit

exit:
    RET
