.ORIG x3000

        LD  R1, A
        LD  R2, B
        AND R3, R3, #0     ; result = 0

LOOP    ADD R3, R3, R1
        ADD R2, R2, #-1
        BRp LOOP

        HALT

A       .FILL #6
B       .FILL #7

.END