// CORRIM COFFMAN CSC 362 002
// ASSIGNMENT 4     4/8/2022
//This program simulates a race between the tortoise and the hare with an array (the racetrack) and two array pointers (for the tortoise and the hare)
//Using a while loop until the one of them reaches the end of the array (loop will break), in which case the winner will be announced with a printf statement
//both pointers move through the array using their own separate functions and another function is used to print out the progress they are making (prints the array out and the pointers position in the array basically)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 60 //constant used for making sure hare is still in bounds of the array called path

char *moveTortoise(char *, char *, int *);
//this function moves the pointer t, pointer t traverses the array path
//the other char pointer (h) and the int pointer (collision) are used to check if pointers h and t are at the same spot in the array, in which case the collision pointer will change to = 1;
//(collision the int pointer acts as a flag)
//returns the pointer t

char *moveHare(char *, char *, int *, int *);
//does basically the same thing as moveTortoise except it moves pointer h instead of t
//has an extra int pointer called nap(it acts like a flag will = 1 or 0) which will keep track if the hare is napping which means he doesn't move
//if the current position in the array is the character 'C' then the pointer h will not move and replace 'C' with ' '
//if the h pointer is pointing to the characters 'R' or 'S' then there is a while loop which will decrease the value of pointer h until it is on a ' ' character
//returns the pointer h

void print (char [], char *, char *, int, int*, int*);
//prints out the path array character by character with a while loop, the loop uses a newly created pointer to traverse the array and once the pointer == 0\ then the loop will end.
// it will also print out the H or T if the positions of the pointers h or t match the character that is currently being read (it will replace what is there
//with 'H' or 'T'. If there is a collision or if the hare is napping then it will print out at the end there is a collision or napping is happening.
//it will reset nap and or collision to 0 if it equals to 1

int main() {//First in the main function it will set up the array and the array pointers as well as some int flags and an int counter used for the 3 functions.
    //then a while loop is run which will go until the hare h pointer has reached the end and print out the winner, the pointer who went the furthest
    //during the while loop the functions to move the t and h pointers are called, then after that the print function is called. the turn counter is incremented and the loop restarts
    char path[]=" R  R  R  SSSSS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R ";
    char *h; //will be an array pointer keeps track of the "hare" in the race
    h = path; //assign at the beginning of the race at the start of the array
    char *t; //will be an array pointer keeps track of the "tortoise" in the race
    t = path; //assign at the beginning of the race at the start of the array
    int turn = 1; //this is a counter variable it basically keeps track of how many times the while loop has looped, the print function will use the turn variable and print it out
    int collision = 0; //int flag can only be 0 or 1, 1 if there is a collision (both array pointers are in the same spot), or 0 in which case no collision.
    int nap = 0; //int flag also only 0 or 1, this variable will have a 1/4 chance decided in the moveHare function to equal 1 otherwise it equals 0 if the nap variable equals 1 then the hare or pointer h will not move

    srand(time(0)); //used to change the value of rand() otherwise rand() will produce the same value over and over (at least in my experience)

    while(h < path + MAX){//if the pointer h is still in bounds of the array path then the loop will keep going
        t = moveTortoise(t, h, &collision); // this function will move the pointer t and then return it and that value will be assigned to the pointer t (so it updates it)
        h = moveHare(h, t, &collision, &nap);//moves and returns pointer h and assigns that value to pointer h to update it the position where its at in the array
        print(path, h, t, turn, &collision, &nap);//prints the turn counter the array and the positions of both array pointers in the array
        turn++;
    }

    if(h > t){//who is further in the array / who won the race?
        printf("Hare wins!");
    }
    else{//that means t is > than h and therefore is the winner
        printf("Tortoise wins!");
    }

    return 0;
}

char *moveTortoise(char *t, char *h, int *collision) {//function moves pointer t by a random amount between 1 - 3 and then checks if its in the same place as the pointer h then it will return pointer t
    t = t + (rand() % 3 + 1); //rand() function called will give either 1,2, or 3 then add that to the position of the t pointer (advancing it in the array)


    if(t == h){//will check if both array pointers are at the same position in the path array, if so then set the collision flag to 1 and move the t pointer back by 1
        *collision = 1;
        t--;//move t pointer back by one
    }
    return t;
}

char *moveHare(char *h, char *t, int *collision, int *nap){//does the same thing as moveTortoise but with a few additions like the nap flag and depending on what character the h pointer is pointing to something will happen
    if(1 == (rand() % 4 + 1)){//will select a random value between 1,2,3,4 if the value == 1 then the nap flag is set to active and the hare or pointer h will not move
        *nap = 1;
    }
    else if (*h == 'C'){//if the pointer points to character 'C' then replace it with a space character (and since this condition is in the else if branch then it will skip the else branch and not move)
        *h = ' ';
    }
    else{//if neither condition above is true then a value between 1 - 8 is selected and the h pointer will advance by that amount in the array
        h = h + (rand() % 8 + 1);

    }
    if(h == t){//if in same position as the other array pointer it will decrease the position of h pointer until it is not
        *collision = 1;// collision flag is set
        h--;
    }
    while(*h == 'R' || *h == 'S' || h == t) {//this while loop checks if the character landed on is one of R or S or there is another collision in which case it will decrease the position of the h pointer until all of those conditions are false
        h--;
        if(h == t){// another check to see if both array pointers are in the same position
            *collision = 1;
        }
    }
    return h;
}

void print (char path[], char *h, char *t, int turn, int *collision, int *nap){// prints the current turn and the path array character by character and if that character matches the position of pointer t or h it will print a T or H instead
    printf("Turn  %2d: ", turn); //prints current turn
    char *ip; //pointer to traverse the whole array
    ip = path; //assigns the pointer to the first item in the array

    while(*ip != '\0'){//will keep going until the pointer reaches the end of the array and all the characters from the array are printed
        if(ip == h){//if it's the same position then print H instead of the current character
            printf("H");
        }
        else if(ip == t){//will print character T instead of the current character in the array if pointer t is in the same position as pointer ip
            printf("T");
        }
        else{
            printf("%c", *ip); //print the current character in the array
        }
        ip++; //increment pointer ip
    }
    if(*nap == 1){// if the nap flag is active set to 1 then print the text below and reset the flag to 0
        printf("    ---NAPPING---");
        *nap = 0;
    }
    else if(*collision == 1){// if collsion flag is active set it to 0 and print out the text below
        printf("    ---COLLISION---");
        *collision = 0;
    }
    printf("\n"); //to ensure each print statement is on its own line
}

/*
HARE WINS OUTPUT
Turn   1:  RHTR  R  SSSSS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R
Turn   2:  R  RTHR  SSSSS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R
Turn   3:  R  R  T HSSSSS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R
Turn   4:  R  R  RTHSSSSS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R     ---NAPPING---
Turn   5:  R  R  R HTSSSS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R     ---NAPPING---
Turn   6:  R  R  R  SSTSS  HR  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R     ---COLLISION---
Turn   7:  R  R  R  SSSST   RH R CCCC  R   R   CCCCCCCCCC  R  SSSS  R
Turn   8:  R  R  R  SSSSST  R  R CCCH  R   R   CCCCCCCCCC  R  SSSS  R
Turn   9:  R  R  R  SSSSS   T  R CCCH  R   R   CCCCCCCCCC  R  SSSS  R     ---NAPPING---
Turn  10:  R  R  R  SSSSS   R TR CCCH  R   R   CCCCCCCCCC  R  SSSS  R     ---NAPPING---
Turn  11:  R  R  R  SSSSS   R  R TCCH  R   R   CCCCCCCCCC  R  SSSS  R
Turn  12:  R  R  R  SSSSS   R  R CCT  HR   R   CCCCCCCCCC  R  SSSS  R     ---COLLISION---
Turn  13:  R  R  R  SSSSS   R  R CCC THR   R   CCCCCCCCCC  R  SSSS  R     ---NAPPING---
Turn  14:  R  R  R  SSSSS   R  R CCC T R H R   CCCCCCCCCC  R  SSSS  R     ---COLLISION---
Turn  15:  R  R  R  SSSSS   R  R CCC  TR   R H CCCCCCCCCC  R  SSSS  R
Turn  16:  R  R  R  SSSSS   R  R CCC   R T R  HCCCCCCCCCC  R  SSSS  R
Turn  17:  R  R  R  SSSSS   R  R CCC   R  TR   CCCCCCCHCC  R  SSSS  R
Turn  18:  R  R  R  SSSSS   R  R CCC   R   R T CCCCCCCHCC  R  SSSS  R
Turn  19:  R  R  R  SSSSS   R  R CCC   R   R   TCCCCCC CC  R HSSSS  R
Turn  20:  R  R  R  SSSSS   R  R CCC   R   R   CCTCCCC CC  R  SSSSH R
Turn  21:  R  R  R  SSSSS   R  R CCC   R   R   CCCTCCC CC  R  SSSS  R
Hare wins!
Process finished with exit code 0

TORTOISE WINS OUTPUT
Turn   1:  T  R HR  SSSSS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R
Turn   2:  R TR  R HSSSSS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R
Turn   3:  R  T  R HSSSSS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R     ---NAPPING---
Turn   4:  R  RT R HSSSSS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R     ---NAPPING---
Turn   5:  R  R TR HSSSSS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R     ---NAPPING---
Turn   6:  R  R  RTHSSSSS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R
Turn   7:  R  R  R HSTSSS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R     ---NAPPING---
Turn   8:  R  R  R HSSSTS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R     ---COLLISION---
Turn   9:  R  R  R HSSSSST  R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R     ---COLLISION---
Turn  10:  R  R  R HSSSSS T R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R     ---NAPPING---
Turn  11:  R  R  R HSSSSS   RT R CCCC  R   R   CCCCCCCCCC  R  SSSS  R
Turn  12:  R  R  R HSSSSS   R TR CCCC  R   R   CCCCCCCCCC  R  SSSS  R
Turn  13:  R  R  R HSSSSS   R  T CCCC  R   R   CCCCCCCCCC  R  SSSS  R
Turn  14:  R  R  R  SSSSS  HR  R TCCC  R   R   CCCCCCCCCC  R  SSSS  R
Turn  15:  R  R  R  SSSSS  HR  R CCCT  R   R   CCCCCCCCCC  R  SSSS  R     ---NAPPING---
Turn  16:  R  R  R  SSSSS  HR  R CCCC TR   R   CCCCCCCCCC  R  SSSS  R
Turn  17:  R  R  R  SSSSS   R  R CCHC  RT  R   CCCCCCCCCC  R  SSSS  R
Turn  18:  R  R  R  SSSSS   R  R CCHC  R   T   CCCCCCCCCC  R  SSSS  R
Turn  19:  R  R  R  SSSSS   R  R CCHC  R   RT  CCCCCCCCCC  R  SSSS  R     ---NAPPING---
Turn  20:  R  R  R  SSSSS   R  R CC CH R   R  TCCCCCCCCCC  R  SSSS  R
Turn  21:  R  R  R  SSSSS   R  R CC CH R   R   CTCCCCCCCC  R  SSSS  R     ---NAPPING---
Turn  22:  R  R  R  SSSSS   R  R CC C  R H R   CCCTCCCCCC  R  SSSS  R
Turn  23:  R  R  R  SSSSS   R  R CC C  R   R  HCCCCCTCCCC  R  SSSS  R
Turn  24:  R  R  R  SSSSS   R  R CC C  R   R   CCHCCCCTCC  R  SSSS  R
Turn  25:  R  R  R  SSSSS   R  R CC C  R   R   CCHCCCCCCCT R  SSSS  R
Turn  26:  R  R  R  SSSSS   R  R CC C  R   R   CC CCCCCHC TR  SSSS  R
Turn  27:  R  R  R  SSSSS   R  R CC C  R   R   CC CCCCCHC  T  SSSS  R
Turn  28:  R  R  R  SSSSS   R  R CC C  R   R   CC CCCCC C HR  TSSS  R
Turn  29:  R  R  R  SSSSS   R  R CC C  R   R   CC CCCCC C  RH SSST  R
Turn  30:  R  R  R  SSSSS   R  R CC C  R   R   CC CCCCC C  R HSSSS TR
Turn  31:  R  R  R  SSSSS   R  R CC C  R   R   CC CCCCC C  R HSSSS  R
Turn  32:  R  R  R  SSSSS   R  R CC C  R   R   CC CCCCC C  R  SSSSH R
Turn  33:  R  R  R  SSSSS   R  R CC C  R   R   CC CCCCC C  R  SSSS  R     ---COLLISION---
Tortoise wins!
 */