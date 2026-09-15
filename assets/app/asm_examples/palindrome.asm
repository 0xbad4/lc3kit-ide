.ORIG x3000

        LEA R1, STRING     ; left
        LEA R2, STRING     ; find end

FIND_END
        LDR R3, R2, #0
        BRz END_FOUND
        ADD R2, R2, #1
        BR FIND_END

END_FOUND
        ADD R2, R2, #-1    ; last character

CHECK
        ; if left >= right, palindrome
        NOT R3, R2
        ADD R3, R3, #1
        ADD R3, R1, R3
        BRzp PALINDROME

        LDR R4, R1, #0
        LDR R5, R2, #0

        NOT R6, R5
        ADD R6, R6, #1
        ADD R6, R4, R6
        BRnp NOT_PALINDROME

        ADD R1, R1, #1
        ADD R2, R2, #-1
        BR CHECK

PALINDROME
        ; R0 = 1
        AND R0, R0, #0
        ADD R0, R0, #1
        BR DONE

NOT_PALINDROME
        ; R0 = 0
        AND R0, R0, #0

DONE    HALT

STRING  .STRINGZ "LEVEL"  ; if palindrome R0 = 1 (true) otherwise R0 = 0 (false)

.END