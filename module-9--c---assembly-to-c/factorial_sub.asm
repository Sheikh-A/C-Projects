;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  file name   : factorial_sub.asm                      ;
;  author      : 
;  description : LC4 Assembly subroutine to compute the ;
;                factorial of a number                  ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;

;; CIT 593 TO-DO:
;; 1) Open up the codio assignment where you created the factorial subroutine (in a separate browswer window)
;; 2) In that window, open up your working factorial_sub.asm file:
;;    -select everything in the file, and "copy" this content (Conrol-C) 
;; 3) Return to the current codio assignment, paste the content into this factorial_sub.asm 
;;    -now you can use the factorial_sub.asm from your last HW in this HW
;; 4) Save the updated factorial_sub.asm file

; MAIN
; A = 6 ;
; B = sub_factorial (A) ;
; // your sub_factorial subroutine goes here
; END


.FALIGN  ; move SR to multiple of 16
SUB_FACTORIAL

;; prologue
	STR R7, R6, #-2	;; save return address
	STR R5, R6, #-3	;; save base pointer
	ADD R6, R6, #-3
	ADD R5, R6, #0
	ADD R6, R6, #-1	;; allocate stack space for local variables
    
    LDR R0, R5, #3 ;; load the value of R0 into R5 offset by 3
    STR R0, R5, #-1 ;; store the value of R0 at location R5 -1
    
  CMPI R0, #9  ; IF STATEMENT test 9, causes error
  BRzp ELSE ; number is greater than 9, exit i.e. 10 - 9 = +1 9-9 = 0 JUMP TO ELSE
  CMPI R0, #0  ; IF STATEMENT set A - 0 to see if number is negative
  BRn ELSE; if negative go to END
  
  ;;Set B's value
  ADD R1, R0, #0 ; set the value of B = A
  JMP WHILE_LOOP
  JMP LOOP_END
  
WHILE_LOOP
  CMPI R0, 1 ;compare to see if A > 1
  BRnz RET_LABEL ; we want to end when A is equal to 1 or less than 1
  ADD R0, R0, #-1 ;add negative 1 = A - 1
  MUL R1, R1, R0 ; multiply B * A
  JMP WHILE_LOOP  ; we can also use BRnzp here
  
ELSE
  CONST R1, #-1 ; if user inputs 9 or above set B to -1 --indicating an error
RET_LABEL
LOOP_END

;;EPILOGUE -copied from prb1

    LDR R7, R5, #-1 ; we need to load C into R7
    
	ADD R6, R5, #0	;; pop locals off stack
	ADD R6, R6, #3	;; free space for return address, base pointer, and return value
	STR R7, R6, #-1	;; store return value
	LDR R5, R6, #-3	;; restore base pointer
	LDR R7, R6, #-2	;; restore return address


RET ;



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  CHECKS & BALANCES         
;  Negative should give -1
;  9 & above should give -1   
;  Others will give correct answer                               
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Checks: 5 = 0078 = 120
;; Checks: 6 = 02D0 = 720
;; Checks: 7 = 13B0 = 5040
;; Checks: 8 = 9D80   = 40320
;; Checks: 9 = FFFF = -1
;; Checks: 10= FFFF = -1
;; Checks: -5= FFFF = -1