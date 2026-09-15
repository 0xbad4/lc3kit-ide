.ORIG x3000

        LEA R1, ARRAY
        LD  R2, LENGTH
        LD  R3, TARGET

LOOP    LDR R4, R1, #0

        ; R5 = element - target
        NOT R5, R3
        ADD R5, R5, #1
        ADD R5, R4, R5

        BRz FOUND

        ADD R1, R1, #1
        ADD R2, R2, #-1
        BRp LOOP

        ; Not found
        AND R0, R0, #0
        BR DONE

FOUND   ADD R0, R1, #0     ; return address of element

DONE    HALT

TARGET  .FILL #30  ; after search: address stored in R0, NOT FOUND R0 = 0 (null)
LENGTH  .FILL #5

ARRAY   .FILL #10
        .FILL #20
        .FILL #30
        .FILL #40
        .FILL #50

.END