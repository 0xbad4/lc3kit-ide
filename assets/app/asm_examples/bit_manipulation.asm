.ORIG x3000

        LD  R1, VALUE
        AND R2, R2, #0     ; count = 0
        LD  R3, MASK

LOOP    AND R4, R1, R3
        BRz SKIP

        ADD R2, R2, #1

SKIP    ADD R1, R1, R1     ; shift left
        ADD R3, R3, R3

        BRnp LOOP

        HALT

VALUE   .FILL x00F3
MASK    .FILL x0001

.END