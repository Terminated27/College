.globl isPrimeAssembly

isPrimeAssembly:
    SUBI    SP, SP, #64         ; Allocate stack space
    STP     x29, x30, [SP, #48] ; Store frame pointer and return address
    ADDI    x29, SP, #48        ; New frame pointer
    
    STUR    X0, [X29, #-8]      ; Store array1 base address 
    STUR    X1, [X29, #-16]     ; Store array2 base address 
    STUR    X2, [X29, #-24]     ; Store array3 base address 
    STUR    X3, [X29, #-32]     ; Store length
    
    STUR    XZR, [SP, #40]      ; Initialize counter to 0 
    STUR    XZR, [SP, #32]      ; Initialize prime count 
    STUR    XZR, [SP, #24]      ; Initialize non-prime count

processArray:
    LDUR    x8, [SP, #40]       ; Load counter
    LDUR    x9, [x29, #-32]     ; Load length
    CMP     x8, x9              ; Compare counter with length
    BGE     endLoop             ; if counter >= length, end loop
    
    LDUR    x8, [x29, #-8]      ; load array1 base address
    LDUR    x9, [SP, #40]       ; load counter
    LDR     x0, [x8, x9, LSL #3]; load array1[counter] into x0
    
    BL      isPrime             ; call isPrime
    STUR    x0, [SP, #16]       ; store result
    
    LDUR    x8, [SP, #16]       ; load result
    CBNZ    x8, Prime           ; if result is 1 (prime), go to Prime
    B       nonPrime            ; otherwise, go to nonPrime

Prime:
    LDUR    x8, [x29, #-8]      ; load base address of array1
    LDUR    x9, [SP, #40]       ; load counter
    LDR     x8, [x8, x9, LSL #3]; load array1[counter] into x8
    LDUR    x9, [x29, #-16]     ; load base address of array2
    LDUR    x10, [SP, #32]      ; load prime count
    STR     x8, [x9, x10, LSL #3]; store into array2[prime count]
    ADDI    x10, x10, #1        ; increment prime count
    STUR    x10, [SP, #32]      ; store updated prime count
    B       incrementCount      ; go to next iteration

nonPrime:
    LDUR    x8, [x29, #-8]      ; load base address of array1
    LDUR    x9, [SP, #40]       ; load counter
    LDR     x8, [x8, x9, LSL #3]; load array1[counter] into x8
    LDUR    x9, [x29, #-24]     ; load base address of array3
    LDUR    x10, [SP, #24]      ; load non-prime count
    STR     x8, [x9, x10, LSL #3]; store into array3[non-prime count]
    ADDI    x10, x10, #1        ; increment non-prime count
    STUR    x10, [SP, #24]      ; store updated non-prime count
    B       incrementCount      ; go to next iteration

incrementCount:
    LDUR    x8, [SP, #40]       ; load counter
    ADDI    x8, x8, #1          ; increment counter
    STUR    x8, [SP, #40]       ; store updated counter
    B       processArray        ; repeat loop

endLoop:
    LDP     x29, x30, [SP, #48] ; restore frame pointer & ret address
    ADDI    SP, SP, #64         ; deallocate stack
    RET                         ; return

isPrime:
    SUBI    SP, SP, #32         ; Allocate stack space
    STUR    x0, [SP, #16]       ; Store input number
    MOVZ    x8, #2              ; Initialize i with 2
    STUR    x8, [SP, #8]        ; Store i

conditional:
    LDUR    x8, [SP, #8]        ; Load i
    LDUR    x9, [SP, #16]       ; Load input number
    LSR     x10, x9, #1         ; Set upper limit to input / 2
    CMP     x8, x10             ; Check if i > input / 2
    BGT     return1             ; If i > input / 2, it's prime
    B       divide

divide:
    LDUR    x8, [SP, #8]        ; Load i
    LDUR    x9, [SP, #16]       ; Load input number
    UDIV    x10, x9, x8         ; x10 = input / i
    MUL     x10, x10, x8        ; x10 = i * (input / i)
    CMP     x9, x10             ; Check if input == (i * (input / i))
    BEQ     return0             ; If equal, not prime

increment:
    LDUR    x8, [SP, #8]        ; Load i
    ADDI    x8, x8, #1          ; Increment i
    STUR    x8, [SP, #8]        ; Store updated i
    B       conditional

return0:
    MOVZ    x0, #0              ; Not prime
    B       exit

return1:
    MOVZ    x0, #1              ; Prime
    B       exit

exit:
    ADDI    SP, SP, #32         ; Deallocate stack space
    RET                         ; Return from function
