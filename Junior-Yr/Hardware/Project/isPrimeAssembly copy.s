.globl isPrimeAssembly

isPrimeAssembly:
    MOV     x4, x0              ; Save original array base address in x4
    MOV     x5, x1              ; Save prime array base address in x5
    MOV     x6, x2              ; Save composite array base address in x6
    MOV     x7, x3              ; Save length in x7
    MOV     x15, x30            ; Store link register
    
    MOV     x8, #0              ; Initialize counter
    MOV     x9, #0              ; Initialize prime count
    MOV     x10, #0             ; Initialize non-prime count

processArray:
    CMP     x8, x7              ; Compare counter with length
    BGE     endLoop             ; if counter >= length, end loop
    
    LDR     x0, [x4, x8, LSL #3] ; Load original_array[counter] into x0
    BL      isPrime             ; Call isPrime
    CBZ     x0, nonPrime        ; If result is 0 (non-prime), go to nonPrime
    
Prime:
    LDR     x0, [x4, x8, LSL #3] ; Load original_array[counter] into x0
    STR     x0, [x5, x9, LSL #3] ; Store in prime_array[prime count]
    ADDI    x9, x9, #1           ; Increment prime count
    B       incrementCount       ; Go to next iteration

nonPrime:
    LDR     x0, [x4, x8, LSL #3] ; Load original_array[counter] into x0
    STR     x0, [x6, x10, LSL #3]; Store in composite_array[non-prime count]
    ADD    x10, x10, #1         ; Increment non-prime count
    B       incrementCount       ; Go to next iteration

incrementCount:
    ADDI    x8, x8, #1           ; Increment counter
    B       processArray         ; Repeat loop

endLoop:
    MOV     x30, x15             ; Return the link address
    BR      X30                  ; Return to caller by branching to X30

isPrime:
    MOV     x11, x0              ; Store input number in x11
    MOV     x12, #2              ; Initialize divisor with 2

conditional:
    LSR     x13, x11, #1         ; Set upper limit to input / 2
    CMP     x12, x13             ; Check if divisor > input / 2
    BGT     return1              ; If divisor > input / 2, number is prime
    B       divide

divide:
    UDIV    x14, x11, x12        ; x14 = input / divisor
    MUL     x14, x14, x12        ; x14 = divisor * (input / divisor)
    CMP     x11, x14             ; Check if input == (divisor * (input / divisor))
    BEQ     return0              ; If equal, not prime

increment:
    ADDI    x12, x12, #1         ; Increment divisor
    B       conditional

return0:
    MOVZ    x0, #0               ; Not prime
    B       exit

return1:
    MOVZ    x0, #1               ; Prime
    B       exit

exit:
    RET                          ; Return to caller
