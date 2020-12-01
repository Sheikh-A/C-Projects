/********************************************************
 * file name   : problem2.c                             *
 * author      : Thomas Farmer
 * description : C program to call LC4-Assembly TRAP_PUTC
 *               the TRAP is called through the wrapper 
 *               lc4putc() (located in lc4_stdio.asm)   *
 ********************************************************
*
*/

// while ( “enter key” is not pressed ) {
            
//         get a character from the keyboard
//         put that character out to the asci display
// }
//    while (c != 0x0A) this throws errors ASK IN OFFICE HOURS

int main() {

	char c = ''; //set c equal to null so user can input letters
    
    char return_key = 0x0A; //From ASCII Table
        
    while (c != return_key) {  
        c = lc4_getc(); //user input from keyboard
        lc4_putc(c);    //display user input from keyboard until Enter is presssed 
    }
    
    //remember to return 0 at end of function!
    
    return(0);


}
