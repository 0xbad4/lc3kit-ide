.ORIG x3000

        LEA R1, ARRAY      ; start
        LEA R2, ARRAY
        ADD R2, R2, #4     ; end

LOOP    LDR R3, R1, #0
        LDR R4, R2, #0

        STR R4, R1, #0
        STR R3, R2, #0

        ADD R1, R1, #1
        ADD R2, R2, #-1

        ; Stop when pointers meet
        NOT R5, R2
        ADD R5, R5, #1
        ADD R5, R1, R5
        BRn LOOP

        HALT

ARRAY   .FILL #10
        .FILL #20
        .FILL #30
        .FILL #40
        .FILL #50

.END