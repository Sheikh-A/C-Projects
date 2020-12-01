.CODE
.ADDR x0000

  CONST R0, #2
  CONST R1, #3
  CONST R2, #0


LOOP
  CMPI R1, #0
  BRnz END
  ADD R2, R2, R0
  ADD R1, R1, #-1
  BRnzp LOOP

END

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;THE OS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


.OS
.CODE
.ADDR x8200
.FALIGN

  CONST R7, #0
  RTI