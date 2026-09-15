.ORIG x3000

	LD  R1, A
        LD  R2, B

        ; R3 = A - B
        NOT R3, R2
        ADD R3, R3, #1
        ADD R3, R1, R3

        BRzp A_GREATER

        ADD R3, R2, #0
        BR DONE

A_GREATER
        ADD R3, R1, #0

DONE    HALT

A       .FILL #42
B       .FILL #17

.END