.ORIG x3000

        LEA R1, STRING
        AND R2, R2, #0     ; length = 0

LOOP    LDR R3, R1, #0
        BRz DONE

        ADD R2, R2, #1
        ADD R1, R1, #1
        BR LOOP

DONE    HALT

STRING  .STRINGZ "Hello, LC3!"  ; LEN in R2

.END