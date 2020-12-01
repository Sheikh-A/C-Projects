/********************************************************
 * file name   : program1.c                             *
 * author      : Thomas Farmer                          *
 * description : Hello World Program                    *
 *                                                      *
 ********************************************************
*
*/

#include <stdio.h>

int main () {

	char name [50]; //hold the data from input form the user
    float hw1, hw2, hw3, hw4, midterm, final;
    
    printf ("Welcome to CIT 593 \n") ;
    printf("Hello Earthling, please enter your name, hw1, hw2, hw3, hw4 scores (out of 100) your midterm exam grade and expected final exam grade (space inbetween each input like this: Ali 100 100 100 100 100 100)\n");
    
    scanf ("%s %f %f %f %f %f %f", &name, &hw1, &hw2, &hw3, &hw4, &midterm, &final);
    
    double hw_average = ((hw1 + hw2 + hw3 + hw4) / 4);
    double hw_weighted = hw_average * 0.6;
    double final_average = hw_weighted + (final * 0.2) + (midterm * 0.2);
    
    //We know print the information from above formatted    
    printf("Name %s\n", name);
    printf("\t\tHW Average\t\t: %.2lf%%\n",hw_average);
    printf("\t\tMidterm Grade\t\t: %.2lf%%\n",midterm);
    printf("\t\tFinal Exam Grade\t: %.2lf%%\n",final);
    printf("\t\tFinal Average\t\t: %.2lf%%\n",final_average);
    
	return (0) ;
}
