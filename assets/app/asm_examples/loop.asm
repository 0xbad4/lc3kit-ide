.ORIG x3000

        LD  R1, N          ; counter
        AND R2, R2, #0     ; sum = 0

LOOP    ADD R2, R2, R1
        ADD R1, R1, #-1
        BRp LOOP

        HALT

N       .FILL #10

.END