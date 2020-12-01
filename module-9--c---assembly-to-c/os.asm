;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  file name   : os.asm                                 ;
;  author      : 
;  description : LC4 Assembly program to serve as an OS ;
;                TRAPS will be implemented in this file ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;

;; CIT 593 TO-DO:
;; 1) Open up your last codio assignment (in a separate browswer window)
;; 2) In that window, open up your working os.asm file:
;;    -select everything in the file, and "copy" this content (Conrol-C) 
;; 3) Return to the current codio assignment, paste the content into this os.asm 
;;    -now you can use the os.asm from your last HW in this HW
;; 4) Save the updated os.asm file

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; File:    OS.ASM
;;; Purpose: serves as an LC4 operating system w/multiple traps
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;   OS - TRAP VECTOR TABLE   ;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


.OS
.CODE
.ADDR x8000
  ; TRAP vector table
  JMP TRAP_GETC           ; x00
  JMP TRAP_PUTC           ; x01
  JMP TRAP_GETS           ; x02
  JMP TRAP_PUTS           ; x03
  JMP TRAP_TIMER          ; x04
  JMP TRAP_GETC_TIMER     ; x05
  JMP TRAP_RESET_VMEM	  ; x06
  JMP TRAP_BLT_VMEM	      ; x07
  JMP TRAP_DRAW_PIXEL     ; x08
  JMP TRAP_DRAW_RECT      ; x09
  JMP TRAP_DRAW_SPRITE    ; x0A



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;   OS - MEMORY ADDRESSES & CONSTANTS   ;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  ;; these handy alias' will be used in the TRAPs that follow
  USER_CODE_ADDR .UCONST x0000	; start of USER code
  OS_CODE_ADDR 	 .UCONST x8000	; start of OS code

  OS_GLOBALS_ADDR .UCONST xA000	; start of OS global mem
  OS_STACK_ADDR   .UCONST xBFFF	; start of OS stack mem

  OS_KBSR_ADDR .UCONST xFE00  	; alias for keyboard status reg
  OS_KBDR_ADDR .UCONST xFE02  	; alias for keyboard data reg

  OS_ADSR_ADDR .UCONST xFE04  	; alias for display status register
  OS_ADDR_ADDR .UCONST xFE06  	; alias for display data register

  OS_TSR_ADDR .UCONST xFE08 	; alias for timer status register
  OS_TIR_ADDR .UCONST xFE0A 	; alias for timer interval register

  OS_VDCR_ADDR	.UCONST xFE0C	; video display control register
  OS_MCR_ADDR	.UCONST xFFEE	; machine control register
  OS_VIDEO_NUM_COLS .UCONST #128
  OS_VIDEO_NUM_ROWS .UCONST #124


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;; OS DATA MEMORY RESERVATIONS ;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.DATA
.ADDR xA000
OS_GLOBALS_MEM	.BLKW x1000
;;;  LFSR value used by lfsr code
LFSR .FILL 0x0001

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;; OS VIDEO MEMORY RESERVATION ;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.DATA
.ADDR xC000
OS_VIDEO_MEM .BLKW x3E00

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;   OS & TRAP IMPLEMENTATIONS BEGIN HERE   ;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.CODE
.ADDR x8200
.FALIGN
  ;; first job of OS is to return PennSim to x0000 & downgrade privledge
  CONST R7, #0   ; R7 = 0
  RTI            ; PC = R7 ; PSR[15]=0


;;;;;;;;;;;;;;;;;;;;;;;;;;;   TRAP_GETC   ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Function: Get a single character from keyboard
;;; Inputs           - none
;;; Outputs          - R0 = ASCII character from ASCII keyboard

.CODE
TRAP_GETC
    LC R0, OS_KBSR_ADDR  ; R0 = address of keyboard status reg
    LDR R0, R0, #0       ; R0 = value of keyboard status reg
    BRzp TRAP_GETC       ; if R0[15]=1, data is waiting!
                             ; else, loop and check again...

    ; reaching here, means data is waiting in keyboard data reg

    LC R0, OS_KBDR_ADDR  ; R0 = address of keyboard data reg
    LDR R0, R0, #0       ; R0 = value of keyboard data reg
    RTI                  ; PC = R7 ; PSR[15]=0


;;;;;;;;;;;;;;;;;;;;;;;;;;;   TRAP_PUTC   ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Function: Put a single character out to ASCII display
;;; Inputs           - R0 = ASCII character to write to ASCII display
;;; Outputs          - none

.CODE
TRAP_PUTC
  LC R1, OS_ADSR_ADDR 	; R1 = address of display status reg
  LDR R1, R1, #0    	; R1 = value of display status reg
  BRzp TRAP_PUTC    	; if R1[15]=1, display is ready to write!
		    	    ; else, loop and check again...

  ; reaching here, means console is ready to display next char

  LC R1, OS_ADDR_ADDR 	; R1 = address of display data reg
  STR R0, R1, #0    	; R1 = value of keyboard data reg (R0)
  RTI			; PC = R7 ; PSR[15]=0


;;;;;;;;;;;;;;;;;;;;;;;;;;;   TRAP_PUTS   ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Function: Put a string of characters out to ASCII display
;;; Inputs           - R0 = Address for first character
;;; Outputs          - none

.CODE
TRAP_PUTS
  LDR R1, R0, #0    ; Load the next character into R1
  BRz END_TRAP_PUTS ; Check for the zero terminating character

  LC R2, OS_ADSR_ADDR
CHECK_ADSR
  LDR R3, R2, #0
  BRzp CHECK_ADSR   ; Loop while ADSR[15] == 0 ie output not ready
  LC R2, OS_ADDR_ADDR
  STR R1, R2, #0    ; Write out the character
  ADD R0, R0, #1    ; Increment the pointer R0
  BRnzp TRAP_PUTS   ; Go back to the top

END_TRAP_PUTS
  RTI


;;;;;;;;;;;;;;;;;;;;;;;;;;;   TRAP_GETS   ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Function: Get a string of characters from the ASCII keyboard
;;; Inputs           - R0 = Address to place characters from keyboard
;;; Outputs          - R1 = Length of the string without the NULL
;;;
;;; Register allocations :
;;; R0 == the memory address to place characters from keyboard, i.e. ASCII display
;;; R1 == length of string, I call this variable L
;;; R2 == the reg status for the keyboard, then data value
;;; R3 == holds 0, for nulling end of string
;;; R4 == holds lower end of memory locations
;;; R5 == holds upper end of memory locations

.CODE
TRAP_GETS

ADD R1, R1, #0            ; initialize string length counter, L, to 0

CONST R4 #0               ; this is the low
HICONST R4 x20            ; end of memory location

CONST R5 xFF              ; this is the high
HICONST R5 x7F            ; end of memory location

                          ; below we are checking if R0 contains a valid address in memory
  CMP R0, R4              ; first location in data memory is x2000, therefore, R0 must be greater than that
  BRn END_TG              ; if R0-x2000 < 0, then end trap subroutine
  CMP R0, R5              ; last location in data memory is x7FFF, therefore, R0 must be smaller
  BRp END_TG              ; if R0-x7FFF > 0, then end trap subroutine

LOOP
  LC R2, OS_KBSR_ADDR     ; load keyboard status reg address to R2
  LDR R2, R2, #0          ; load value in keyboard signal
  BRzp LOOP               ; polling for signal of RSP[15]==1

  LC R2, OS_KBDR_ADDR     ; we get the address of the keyboard data
  LDR R2, R2, #0          ; load keyboard data value into R2
  CMPI R2, #10            ; check if char is "return"
  BRz NULL                ; if char is enter, then exit loop, null last char, and R1 is current increment level

CHAR_TO_MEM               ; if char is not "return", then store it and increment L
  STR R2, R0, #0          ; store R2 into R0
  ADD R1, R1, #1          ; increment L
  ADD R0, R0, #1          ; increment data storage address
  BRnzp LOOP              ; start signal loop over

NULL
  CONST R3 #0             ; initialize R3 to 0
  HICONST R3 #0           ; initialize R3 to 0
  STR R3, R0, #0          ; store R3, a zero, into R0, our last location, ensuring string ends with NULL

END_TG
  RTI

;;;;;;;;;;;;;;;;;;;;;;;;;   TRAP_TIMER   ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Function:
;;; Inputs           - R0 = time to wait in milliseconds
;;; Outputs          - none

.CODE
TRAP_TIMER
  LC R1, OS_TIR_ADDR 	; R1 = address of timer interval reg
  STR R0, R1, #0    	; Store R0 in timer interval register

COUNT
  LC R1, OS_TSR_ADDR  	; Save timer status register in R1
  LDR R1, R1, #0    	; Load the contents of TSR in R1
  BRzp COUNT    	; If R1[15]=1, timer has gone off!

  ; reaching this line means we've finished counting R0

  RTI       		; PC = R7 ; PSR[15]=0



;;;;;;;;;;;;;;;;;;;;;;;   TRAP_GETC_TIMER   ;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Function: Get a single character from keyboard
;;; Inputs           - R0 = time to wait
;;; Outputs          - R0 = ASCII character from keyboard (or NULL)

.CODE
TRAP_GETC_TIMER
  LC R1, OS_TIR_ADDR  ; R1 = address of timer
  STR R0, R1, #0    ; Store time to wait in timer interval

GETC_COUNT
  LC R2, OS_KBSR_ADDR ; R2 = address of keyboard status
  LDR R2, R2, #0    ; R2 = value of keyboard status
  BRn KEYFOUND

  ; if no key found
  LC R1, OS_TSR_ADDR  ; R1 = address of timer status
  LDR R1, R1, #0    ; R1 = value of TSR
  BRzp GETC_COUNT      ; if the timer is still not completed

  CONST R0 #0     ; if timer expired and no key found, store 0
  BRnzp END_TRAP_GETC_TIMER

KEYFOUND
  LC R0 OS_KBDR_ADDR  ; R0 = address of keyboard data
  LDR R0, R0, #0    ; R0 = value of keyboard data
  BRnzp END_TRAP_GETC_TIMER

END_TRAP_GETC_TIMER
  RTI


;;;;;;;;;;;;;;;;;;;;;;;;;   TRAP_DRAW_PIXEL   ;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Function: Draw point on video display
;;; Inputs           - R0 = row to draw on (y)
;;;                  - R1 = column to draw on (x)
;;;                  - R2 = color to draw with
;;; Outputs          - none

.CODE
TRAP_DRAW_PIXEL
  LEA R3, OS_VIDEO_MEM       ; R3=start address of video memory
  LC  R4, OS_VIDEO_NUM_COLS  ; R4=number of columns

  CMPIU R1, #0    	     ; Checks if x coord from input is > 0
  BRn END_PIXEL
  CMPIU R1, #127    	     ; Checks if x coord from input is < 127
  BRp END_PIXEL
  CMPIU R0, #0    	     ; Checks if y coord from input is > 0
  BRn END_PIXEL
  CMPIU R0, #123    	     ; Checks if y coord from input is < 123
  BRp END_PIXEL

  MUL R4, R0, R4      	     ; R4= (row * NUM_COLS)
  ADD R4, R4, R1      	     ; R4= (row * NUM_COLS) + col
  ADD R4, R4, R3      	     ; Add the offset to the start of video memory
  STR R2, R4, #0      	     ; Fill in the pixel with color from user (R2)

END_PIXEL
  RTI       		     ; PC = R7 ; PSR[15]=0


;;;;;;;;;;;;;;;;;;;;;;;;;   TRAP_VIDEO_COLOR   ;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Function: Set all pixels of VIDEO display to a certain color
;;; Inputs           - R0 = color to set all pixels to
;;; Outputs          - none

.CODE
TRAP_VIDEO_COLOR

  ;;
  ;; CIS 240 TO DO: complete this trap
  ;;

  RTI       ; PC = R7 ; PSR[15]=0



;;;;;;;;;;;;;;;;;;;;;;;;;   TRAP_DRAW_RECT   ;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Function: Draws a solid rectangular block on the screen
;;; Inputs           - R0 = x coordinate of top left corner of rectangle
;;; Inputs           - R1 = y coordinate of top left corner of rectangle
;;; Inputs           - R2 = width of rectangle
;;; Inputs           - R3 = height of rectangle
;;; Inputs           - R4 = color of rectangle
;;; Outputs          - none

.CODE
TRAP_DRAW_RECT

  ;; Check if width or height is <= 0
  CMPI R2, #0
  BRnz TRAP_DRAW_RECT_END
  CMPI R3, #0
  BRnz TRAP_DRAW_RECT_END

  ;; Compute end row and store in R3
  ;; R3 = MIN(OS_VIDEO_NUM_COLS, R3 + R1)
  ADD R3, R3, R1
  LC R5 OS_VIDEO_NUM_ROWS
  CMP R3, R5
  BRnz TRAP_DRAW_RECT_L1
  LC R3 OS_VIDEO_NUM_ROWS
TRAP_DRAW_RECT_L1

  ;; Compute start row and store in R1
  ;; R1 = MAX(0, R1)
  CMPI R1, #0
  BRzp TRAP_DRAW_RECT_L2
  CONST R1, #0
TRAP_DRAW_RECT_L2

  ;; Compute end column and store in R2
  ;; R2 = MIN(OS_VIDEO_NUM_COLS, R0+R2)
  ADD R2, R2, R0
  LC R5 OS_VIDEO_NUM_COLS
  CMP R2, R5
  BRnz TRAP_DRAW_RECT_L3
  LC R2 OS_VIDEO_NUM_COLS
TRAP_DRAW_RECT_L3

  ;; Compute start col and store in R0
  ;; R0 = MAX(0, R0)
  CMPI R0, #0
  BRzp TRAP_DRAW_RECT_L4
  CONST R0, #0
TRAP_DRAW_RECT_L4

  ;; Register allocation
  ;; R1 - row
  ;; R5 - col
  ;; R6 - ptr to video memory

;;; for (row = start_row; row < end_row; ++row) {
;;;   ptr = VIDEO_MEM + row*num_cols + start_col
;;;   for (col = start_col; col < end_col; ++col, ++ptr)
;;;       *ptr = color;
;;; }

  JMP TRAP_DRAW_RECT_F12

TRAP_DRAW_RECT_F11

  ;; Set up ptr in R6 using R5
  SLL R6, R1, #7    ; R6 = R1 << 7 = R1*128
  LEA R5, OS_VIDEO_MEM
  ADD R6, R6, R5
  ADD R6, R6, R0

  ADD R5, R0, #0    ; col = start_col
  JMP TRAP_DRAW_RECT_F22
TRAP_DRAW_RECT_F21
  STR R4, R6, #0    ; *ptr = color
  ADD R6, R6, #1    ; increment ptr
  ADD R5, R5, #1    ; increment col
TRAP_DRAW_RECT_F22
  CMP R5, R2
  BRn TRAP_DRAW_RECT_F21

  ADD R1, R1, #1    ; increment row
TRAP_DRAW_RECT_F12
  CMP R1, R3
  BRn TRAP_DRAW_RECT_F11

TRAP_DRAW_RECT_END
  RTI


;;;;;;;;;;;;;;;;;;;;;;;   TRAP_DRAW_SPRITE   ;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Function: Draws a circle on the video screen at a specific loc.
;;; Inputs           - R0 = x coordinate of top left corner of sprite
;;; Inputs           - R1 = y coordinate of top left corner of box
;;; Inputs           - R2 = color of the sprite
;;; Inputs           - R3 = starting address in data memory of sprite pattern
;;; Outputs          - none

.CODE
TRAP_DRAW_SPRITE

;; STORE R0, R1 and R7
LEA R6, OS_GLOBALS_MEM
STR R0, R6, #0
STR R1, R6, #1
STR R7, R6, #2


;;; for (i=0; i < 8; ++i, ++ptr) {
;;; temp = i + start_row;
;;; if (temp < 0) continue;
;;; if (temp >= NUM_ROWS) end;
;;; byte = *ptr & 0xFF;
;;; col = start_col + 7;
;;; temp = VIDEO_MEM + (temp * 128) + col
;;; do {
;;; if (col >= 0 && col < NUM_COLS && byte & 0x1)
;;; *temp = color
;;; --col;
;;; --temp;
;;; byte >>= 1;
;;; } while (byte)
;;; }
;;;
;;; Register Allocation
;;; R0 - i
;;; R1 - temp
;;; R2 - color
;;; R3 - ptr
;;; R4 - byte
;;; R5 - col
;;; R6 - scratch
;;; R7 - scratch


  CONST R0, #0 ; i = 0
  JMP TRAP_DRAW_SPRITE_F12

TRAP_DRAW_SPRITE_F11

  LEA R6, OS_GLOBALS_MEM
  LDR R1, R6, #1 ; load start_row
  ADD R1, R1, R0 ; temp = i + start_row
  BRn TRAP_DRAW_SPRITE_F13 ; temp < 0 continue
  LC R7 OS_VIDEO_NUM_ROWS
  CMP R1, R7
  BRzp TRAP_DRAW_SPRITE_END ; (temp >= NUM_ROWS) end
  LDR R4, R3, #0 ; byte = *ptr
  CONST R7, 0xFF
  AND R4, R4, R7 ; byte = byte & xFF

  LEA R6, OS_GLOBALS_MEM
  LDR R5, R6, #0 ; load start_col
  ADD R5, R5, #7 ; col = start_col + 7

  SLL R1, R1, #7 ; temp = temp * 128
  ADD R1, R1, R5 ; temp = temp + col
  LEA R7, OS_VIDEO_MEM
  ADD R1, R1, R7 ; temp = temp + OS_VIDEO_MEM

  LC R7, OS_VIDEO_NUM_COLS

TRAP_DRAW_SPRITE_W1

  CMPI R5, #0
  BRn TRAP_DRAW_SPRITE_W2 ; col < 0 continue

  CMP R5, R7
  BRzp TRAP_DRAW_SPRITE_W2 ; col >= NUM_COLS continue

  AND R6, R4, 0x01
  BRz TRAP_DRAW_SPRITE_W2 ; byte & 0x1 == 0 continue

  STR R2, R1, 0 ; *temp = color

TRAP_DRAW_SPRITE_W2

  ADD R5, R5, #-1 ; --col
  ADD R1, R1, #-1 ; --temp
  SRL R4, R4, #1 ; byte >>= 1

  BRnp TRAP_DRAW_SPRITE_W1

TRAP_DRAW_SPRITE_F13
  ADD R0, R0, #1 ; ++i
  ADD R3, R3, #1 ; ++ptr
TRAP_DRAW_SPRITE_F12
  CMPI R0, #8
  BRn TRAP_DRAW_SPRITE_F11

TRAP_DRAW_SPRITE_END
  LEA R6, OS_GLOBALS_MEM
  LDR R7, R6, #2
RTI





;;;;;;;;;;;;;;;;;;;;;;;;;;;;; TRAP_RESET_VMEM ;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; In double-buffered video mode, resets the video display
;;; CIS 240 students do not need to modify this trap, it's for HW#8
;;; Inputs - none
;;; Outputs - none
.CODE
TRAP_RESET_VMEM
	LC R4, OS_VDCR_ADDR
	CONST R5, #1
	STR R5, R4, #0
	RTI

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; TRAP_BLT_VMEM ;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; TRAP_BLT_VMEM - In double-buffered video mode, copies the contents
;;; of video memory to the video display.
;;; CIS 240 students do not need to modify this trap, it's for HW#8
;;; Inputs - none
;;; Outputs - none
.CODE
TRAP_BLT_VMEM
	LC R4, OS_VDCR_ADDR
	CONST R5, #2
	STR R5, R4, #0
	RTI




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; TRAP_LRSR ;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; TRAP_BLT_VMEM - In double-buffered video mode, copies the contents
;;; of video memory to the video display.
;;; CIS 240 students do not need to modify this trap, it's for HW#8
;;; Inputs - none
;;; Outputs - none.CODE
TRAP_LFSR
	LEA R3, LFSR
	LDR R0, R3, 0

	SLL R1, R0, 2		; move bit 13 to MSB
	XOR R2, R0, R1		; xor with bit 15

	SLL R1, R0, 3		; move bit 12 to MSB
	XOR R2, R1, R2

	SLL R1, R0, 5		; move bit 10 to MSB
	XOR R2, R1, R2

	SRL R2, R2, 15		; Shift right logical move MSB to LSB and zeros elsewhere

	SLL R0, R0, 1		; shift left by one bit
	OR  R0, R0, R2		; add in the LSB - note upper bits of R2 are all 0

	STR R0, R3, 0		; update the LFSR in memory

	RTI


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; TRAP_LFSR_SET_SEED - sets the seed value used by TRAP_LFSR
;;; Inputs - R0: initial value
;;; Outputs - none

.CODE
TRAP_LFSR_SET_SEED
	LEA R3, LFSR

	STR R0, R3, #0

	RTI
