;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  file name   : user_start.asm                         ;
;  author      : 
;  description : LC4 Assembly subroutine: USER_START    ;
;                This subroutine "calls" main()         ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;


.DATA
.ADDR x2000
USER_STACK_ADDR .UCONST x7FFF	; address where stack should start for users
    
;;LC refers to x7FFF, LEA refers to x2000, LDR loads the value of the DMEM so x7FFF

.CODE                           ; adddress where USER_START should be loaded
.ADDR x0000

.FALIGN
USER_START
    LC R6, USER_STACK_ADDR	    ; initialize the stack pointer (R6)
    ADD R5, R6, #0		        ; initialize the frame pointer (R5)
    LEA R7, main
    JSRR R7			            ; invoke the main routine
END