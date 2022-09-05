#include <stdio.h> /* standard input/output library */
#include <stdlib.h> /* Standard C Library */
#include <string.h> /* String operations library */
#include <ctype.h> /* Library for useful character operations */
#include <limits.h> /* Library for definitions of common variable type characteristics */
// Part 1: Writing the assembler

// format:  labe opcode operands ; comments

// Define LC3b components

FILE* infile = NULL;
FILE* outfile = NULL;

#define MAX_LABEL_LEN 20
#define MAX_SYMBOLS 255
#define MAX_LINE_LENGTH 255
typedef struct {
	int address;
	char label[MAX_LABEL_LEN + 1];	/* Question for the reader: Why do we need to add 1? */
} TableEntry;
TableEntry symbolTable[MAX_SYMBOLS];
char *line[5];

char *opCodes[31] = {"add", "and", "br", "brp", "brz", "brzp", "brn", "brnp", "brnz",
"brnzp","halt", "jmp", "jsr", "jsrr", "ldb", "ldw",
"lea", "nop", "not", "ret", "lshf", "rshfl", "rshfa", "rti", "stb", "stw", "trap", "xor", ".FILL", ".ORIG", ".END" };
char *registers[8] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"};
int labels = 0;
int pcounter;

int translateLine(int counter){
printf("line\n");
for(int i = 0; i < counter; i++){
	printf("%s\n", line[i]);
}
 return 0;
}

toNum( char * pStr )
{
   char * t_ptr;
   char * orig_pStr;
   int t_length,k;
   int lNum, lNeg = 0;
   long int lNumLong;

   orig_pStr = pStr;
   if( *pStr == '#' )				/* decimal */
   { 
     pStr++;
     if( *pStr == '-' )				/* dec is negative */
     {
       lNeg = 1;
       pStr++;
     }
     t_ptr = pStr;
     t_length = strlen(t_ptr);
     for(k=0;k < t_length;k++)
     {
       if (!isdigit(*t_ptr))
       {
	 printf("Error: invalid decimal operand, %s\n",orig_pStr);
	 exit(4);
       }
       t_ptr++;
     }
     lNum = atoi(pStr);
     if (lNeg)
       lNum = -lNum;
 
     return lNum;
   }
   else if( *pStr == 'x' )	/* hex     */
   {
     pStr++;
     if( *pStr == '-' )				/* hex is negative */
     {
       lNeg = 1;
       pStr++;
     }
     t_ptr = pStr;
     t_length = strlen(t_ptr);
     for(k=0;k < t_length;k++)
     {
       if (!isxdigit(*t_ptr))
       {
	 printf("Error: invalid hex operand, %s\n",orig_pStr);
	 exit(4);
       }
       t_ptr++;
     }
     lNumLong = strtol(pStr, NULL, 16);    /* convert hex string into integer */
     lNum = (lNumLong > INT_MAX)? INT_MAX : lNumLong;
     if( lNeg )
       lNum = -lNum;
     return lNum;
   }
   else
   {
	printf( "Error: invalid operand, %s\n", orig_pStr);
	exit(4);  /* This has been changed from error code 3 to error code 4, see clarification 12 */
   }
}
int isOpcode(char *inst ){
   
    for(int pair = 0; pair < 31; pair++){
	//printf("%d\n", pair);
	//printf("%s\n", opCodes[pair]);
        if(strcmp(inst, opCodes[pair]) == 0){
            return 1;   // we have a pair (opcode)
        }
    }
            return -1; // not a pair, not an opcode
}enum
	{
	   DONE, OK, EMPTY_LINE
	};

func() 
	{
	   //printf("made it \n");
	   char lLine[MAX_LINE_LENGTH + 1], *lLabel, *lOpcode, *lArg1,
	        *lArg2, *lArg3, *lArg4;

	   int lRet;

	   FILE * lInfile;

	   lInfile = fopen( "Input.asm", "r" );	/* open the input file */

	   do
	   {
		lRet = readAndParse( lInfile, lLine, &lLabel,
			&lOpcode, &lArg1, &lArg2, &lArg3, &lArg4 );
		if( lRet != DONE && lRet != EMPTY_LINE )
		{
			
		}
	   } while( lRet != DONE );
	}
func2() 
	{
	   //printf("made it \n");
	   char lLine[MAX_LINE_LENGTH + 1], *lLabel, *lOpcode, *lArg1,
	        *lArg2, *lArg3, *lArg4;

	   int lRet;

	   FILE * lInfile;

	   lInfile = fopen( "Input.asm", "r" );	/* open the input file */

	   do
	   {
		lRet = readAndParse2( lInfile, lLine, &lLabel,
			&lOpcode, &lArg1, &lArg2, &lArg3, &lArg4 );
		if( lRet != DONE && lRet != EMPTY_LINE )
		{
			
		}
	   } while( lRet != DONE );
	}

readAndParse( FILE * pInfile, char * pLine, char ** pLabel, char
	** pOpcode, char ** pArg1, char ** pArg2, char ** pArg3, char ** pArg4
	)
	{

	   char * lRet, * lPtr;
	   int i;
	   pcounter++;
	   if( !fgets( pLine, MAX_LINE_LENGTH, pInfile ) )
		return( DONE );
	   for( i = 0; i < strlen( pLine ); i++ )
		pLine[i] = tolower( pLine[i] );
	   
           /* convert entire line to lowercase */
	   *pLabel = *pOpcode = *pArg1 = *pArg2 = *pArg3 = *pArg4 = pLine + strlen(pLine);

	   /* ignore the comments */
	   lPtr = pLine;

	   while( *lPtr != ';' && *lPtr != '\0' &&
	   *lPtr != '\n' ) 
		lPtr++;

	   *lPtr = '\0';
	   if( !(lPtr = strtok( pLine, "\t\n ," ) ) ) 
		return( EMPTY_LINE );
	   //printf("%s\n", lPtr);
	   if( isOpcode( lPtr ) == -1 && lPtr[0] != '.' ) /* found a label */
	   {
		//printf("found label\n");
		//printf("%s\n", lPtr);
		TableEntry newLabel;
		strcpy(newLabel.label, lPtr);
		newLabel.address = pcounter;
		//newLabel.address = "complete"
		symbolTable[labels] = newLabel;
		labels++;

		*pLabel = lPtr;
		if( !( lPtr = strtok( NULL, "\t\n ," ) ) )  return( OK );
		
		
	   }
	   
           *pOpcode = lPtr;
	   //printf("popcode is %s\n", *pOpcode);
	   if( !( lPtr = strtok( NULL, "\t\n ," ) ) )  return( OK );
	   
           *pArg1 = lPtr;
	   if(strcmp(".orig",*pOpcode) == 0){
	    pcounter = toNum(*pArg1) -1;
	   // printf("pcounter is %d\n", pcounter);
	   }
           if( !( lPtr = strtok( NULL, "\t\n ," ) ) )   return( OK );

	   *pArg2 = lPtr;
	   if( !( lPtr = strtok( NULL, "\t\n ," ) ) )    return( OK );

	   *pArg3 = lPtr;

	   if( !( lPtr = strtok( NULL, "\t\n ," ) ) )  return( OK );

	   *pArg4 = lPtr;
	   //translateLine( pOpcode, pArg1, pArg2, pArg3, pArg4);
	   
	   return( OK );
	}// Defining hash map

readAndParse2( FILE * pInfile, char * pLine, char ** pLabel, char
	** pOpcode, char ** pArg1, char ** pArg2, char ** pArg3, char ** pArg4
	)
	{

	   char * lRet, * lPtr;
	   int i;
	   pcounter++;
	   int argcounter = 0;
	   if( !fgets( pLine, MAX_LINE_LENGTH, pInfile ) )
		return( DONE );
	   for( i = 0; i < strlen( pLine ); i++ )
		pLine[i] = tolower( pLine[i] );
	   
           /* convert entire line to lowercase */
	   *pLabel = *pOpcode = *pArg1 = *pArg2 = *pArg3 = *pArg4 = pLine + strlen(pLine);

	   /* ignore the comments */
	   lPtr = pLine;

	   while( *lPtr != ';' && *lPtr != '\0' &&
	   *lPtr != '\n' ) 
		lPtr++;

	   *lPtr = '\0';
	   if( !(lPtr = strtok( pLine, "\t\n ," ) ) ) 
		return( EMPTY_LINE );
	   //printf("2nd pass word %s\n", lPtr);
	   if( isOpcode( lPtr ) == -1 && lPtr[0] != '.' ) /* found a label */
	   {
		
		*pLabel = lPtr;
		if( !( lPtr = strtok( NULL, "\t\n ," ) ) )  return( OK );
		
		
	   }
	   
           *pOpcode = lPtr;
	   //printf("popcode is %s\n", *pOpcode);
	   line[argcounter] = *pOpcode;
	   argcounter++;
	   if( !( lPtr = strtok( NULL, "\t\n ," ) ) ){  translateLine( argcounter);
 return( OK );
	   }
           *pArg1 = lPtr;
	   if(strcmp(".orig",*pOpcode) == 0){
	    pcounter = toNum(*pArg1) -1;
	   // printf("pcounter is %d\n", pcounter);
	   }
	   line[argcounter] = *pArg1;

	   argcounter++;
           if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) { translateLine( argcounter);
  return( OK );
}
	   *pArg2 = lPtr;
	   line[argcounter] = *pArg2;
	   argcounter++;
	   if( !( lPtr = strtok( NULL, "\t\n ," ) ) ){  translateLine(argcounter);
   return( OK );
}
	   *pArg3 = lPtr;
	   line[argcounter] = *pArg3;
	   argcounter++;
	   if( !( lPtr = strtok( NULL, "\t\n ," ) ) ){  translateLine(argcounter);
  return( OK );
}
	   *pArg4 = lPtr;
	   line[argcounter] = *pArg4;
	   argcounter++;
           
	   translateLine(argcounter);
	   
	   return( OK );
	}
int fileOpen(int argc, char* argv[]) {
	//printf("%s\n", argv[1]);
	//printf("%s\n", argv[2]);

     /* open the source file */
     infile = fopen(argv[1], "r");
     outfile = fopen(argv[2], "w");
		 
     if (!infile) {
       printf("Error: Cannot open file %s\n", argv[1]);
       exit(4);
		 }
     if (!outfile) {
       printf("Error: Cannot open file %s\n", argv[2]);
       exit(4);
     }

     func();

     fclose(infile);
     fclose(outfile);
}
int fileOpen2(int argc, char* argv[]) {
	//printf("%s\n", argv[1]);
	//printf("%s\n", argv[2]);

     /* open the source file */
     infile = fopen(argv[1], "r");
     outfile = fopen(argv[2], "w");
		 
     if (!infile) {
       printf("Error: Cannot open file %s\n", argv[1]);
       exit(4);
		 }
     if (!outfile) {
       printf("Error: Cannot open file %s\n", argv[2]);
       exit(4);
     }

     func2();

     fclose(infile);
     fclose(outfile);
}


// Parsing cmd line arguements
 int Arguements(int argc, char* argv[]) {

     char *prgName   = NULL;
     char *iFileName = NULL;
     char *oFileName = NULL;

     prgName   = argv[0];
     iFileName = argv[1];
     oFileName = argv[2];

     printf("program name = '%s'\n", prgName);
     printf("input file name = '%s'\n", iFileName);
     printf("output file name = '%s'\n", oFileName);
}

int main(){
char* argv[3];
int args = 2;
char* inputFile = "Input.asm";
char* outputFile = "Output.obj";
argv[1] = inputFile;
argv[2] = outputFile;
printf("first pass:\n");
fileOpen(args, argv);
//printf("%d\n", labels);
for(int i = 0; i < labels; i++){
	printf("label is %s: address is %d\n", symbolTable[i].label, symbolTable[i].address );
}
printf("second pass:\n");
fileOpen2(args, argv);


}

