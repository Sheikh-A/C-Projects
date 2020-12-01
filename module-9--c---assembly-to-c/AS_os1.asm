;;;;;;;;;;;;;;;;;;
;;;;;;;;;;OS TRAP VECTOR TABLE
;;;;;;;;;;;;;;;;;


.OS
.CODE
.ADDR x8000
   ;TRAP vector Table
   ;;JMP TRAP_MY_FIRST_TRAP ;; x00 COMMENTED OUT
   JMP TRAP_GETC ;; x00
   
   
   OS_KBSR_ADDR .UCONST xFE00 ;Status Reg
   OS_KBDR_ADDR .UCONST xFE02 ;Data Reg


;;;;;;;;;;;;;;;;;;
;;;;;;;;OS Implementation
;;;;;;;;;;;;;;;;;;;;;;;;;

.CODE
.ADDR x8200
.FALIGN
   ;;by defualt usercode = PC = x0000
   CONST R7, #0
   RTI  ;;PC = R7, PSR [15]=0
   
   
.CODE
TRAP_GETC
  LC R0, OS_KBSR_ADDR ; RO ADDRESS OF KEYBOARD STATUS REG
  LDR R0, R0, #0      ; R0 VALUE OF KEYBOARD STATUS REG
  BRzp TRAP_GETC      ; IF R0[15] = 1 DATA IS WAITING
  
  ;REACHING HERE MEANS DATA IS WAITING IN KEYBOARD DATA REG
  
  LC R0, OS_KBDR_ADDR ;;R0 - ADDRSS OF KEYBOARD DATA REG
  LDR R0, R0, #0      ;; R0 = VALUE OF KEBOARD DATA REG
  RTI                 ;; PC = R7, PSR15 = 0


;TRAP_MY_FIRST_TRAP
;  ;;ADD 1 to register 0
;  ADD R0, R0, #1
;  RTI ;;PC = R7, PSR[15] = 0  

  