//#define _CRT_SECURE_NO_WARNINGS

#include <string.h>

#include <ctype.h>

#include <stdio.h>

#include <stdlib.h>




#define LOAD 1
#define ADD 2
#define STORE 3
#define SUB 4
#define IN 5
#define OUT 6
#define END 7
#define JMP 8
#define SKIPZ 9

void printVaribles();


typedef struct //creation of basic structure

{

  int opCode; //Stores the opCode

  int deviceOrAddress; //This is the address of the operation

}
Instruction;

int CODESIZE = 13, pc = 10, ir = 0, mar = 0; //setting code size and variables

int dataMemory[9] = {
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0
};

int mdr = 0; //storing the data of memory

int ac = 0; //setting accumulator

void printVaribles() //print statement for variables

{

  int i;

  printf(" PC: %d | A: %d | MEM: [", pc, ac);

  for (i = 0; i < 9; i += 1)

  {

    printf("%d,", dataMemory[i]);

  }

  printf("] ");

}


int getNumberOfLineInFile(FILE * asmCodefile) //gets number of lines in the input file

{

  char asmCodeBuffer[10];

  int count = 0;

  if (asmCodefile == NULL)

  {

    printf("ASM code file txt not opening..."); 	

    exit(0);

  }

  while (fgets(asmCodeBuffer, 10, asmCodefile) != NULL)

    count++; //increament count

  fclose(asmCodefile);

  return count; //returns count

}

void tinyMachineSimulator(int opCode, int b) { //simulator

  if (opCode == LOAD) { //if statement for succesful op code loading

    printf(" /* Loading from address [%d]... */ ", b);

    ir = b;

    mar = ir;

    mdr = dataMemory[mar];

    ac = mdr;


    printVaribles();

    pc += 1;

    printf(" /* PC <- PC + 1 */ ");

    printf("/* PC <- PC + 1 */ ");

    printf("/* MAR <- IR.ADDR */ ");

    printf("/* MDR <- MEM[MAR] */ ");

    printf("/* A <- MDR */ ");
  } else if (opCode == ADD) {

    printf(" /Adding the accumulator value address value[%d]/ ", b);

    ir = b;

    mar = ir;

    mdr = dataMemory[mar];

    ac += mdr;


    printVaribles();

    pc += 1;
  } else if (opCode == STORE) { //else statement 

    printf(" /* storing accumulator to memory location 0 */ "); 

    mdr = ac;

    ir = b;

    mar = ir;

    dataMemory[mar] = mdr;


    printVaribles();

    pc += 1;
  } else if (opCode == SUB) {

    printf(" /* Subtracting memory address value [%d] from accumulator*/ ", b);

    ir = b;

    mar = ir;

    mdr = dataMemory[mar];

    ac -= mdr;


    printVaribles();

    pc += 1;
  } else if (opCode == IN) {

    printf(" /Please input value:/ ");

    scanf("%d", & ac);

    printVaribles();

    pc += 1;
  } else if (opCode == OUT) {

    printf(" /*Accumulators current value = %d */ ", ac);


    printVaribles();

    pc += 1;

  } else if (opCode == END) {

    printf(" Program complete ");

    exit(1);
  } else if (opCode == JMP) {


    printf(" /Setting program counter to %d/ ", b);

    pc = b;

    printVaribles();

  } else if (opCode == SKIPZ) {

    printf(" /Skipping the next instruction/ ");

    if (ac == 0) //if ac==0 skip next instruction

      pc += 2; //increament PC by 2

    else //otherwise

      pc += 1;

    printVaribles();
  } else {

    printf(" /There was an error parsing your opCode! Exiting./ ");

    exit(0);

  }

}

int main(int argc, char * argv[])

{
  CODESIZE = getNumberOfLineInFile(fopen(argv[1], "r"));
  


  Instruction programMemory[CODESIZE]; 

  FILE * asmCodefile = fopen(argv[1], "r");

  char asmCodefileBuffer[10];

  int i = 0;

  if (asmCodefile == NULL)

  {

    printf("ASM code file is not opening..."); //instruction for if the asm code file isnt opening properly, this was the bane of my existance

    exit(0);

  }

  while (fgets(asmCodefileBuffer, sizeof(CODESIZE), asmCodefile) != NULL)

  {

    if ((asmCodefileBuffer == " " || asmCodefileBuffer != " "))

    {


      if (isdigit(asmCodefileBuffer[0]) && (int) asmCodefileBuffer[2] != 0)

      {

        programMemory[i].opCode = atoi( & asmCodefileBuffer[0]);

        programMemory[i].deviceOrAddress = atoi( & asmCodefileBuffer[2]);

        i++; //increament

      }

    }

  }

  fclose(asmCodefile); //close input file

  printf(" Tiny Machine Simulator Assembling program... Program assembled Run. "); //code for the program assembly

  printVaribles();


  for (i = (pc / 10) - 1; i < sizeof(programMemory); i += 1)

  {

    tinyMachineSimulator(programMemory[i].opCode, programMemory[i].deviceOrAddress);

  }

  printf(" Program concluded... ");

  return 0;

}
