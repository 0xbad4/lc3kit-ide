.ORIG x3000

        LD  R6, STACK      ; SP

        ; push 10
        ADD R6, R6, #-1
        AND R0, R0, #0
        ADD R0, R0, #10
        STR R0, R6, #0

        ; push 20
        ADD R6, R6, #-1
        AND R0, R0, #0
        ADD R0, R0, #20
        STR R0, R6, #0

        ; pop -> R1
        LDR R1, R6, #0
        ADD R6, R6, #1

        ; pop -> R2
        LDR R2, R6, #0
        ADD R6, R6, #1

        HALT

STACK   .FILL x4000

.END