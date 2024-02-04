/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2023
* Author: TO_DO
* Professors: Paulo Sousa
************************************************************
					   .,,.ez.ez.ez,.
			  ..,.ez.ez.ez.ez.ez.ez.ez.ez?l!i:.
		 ,=.ez.ez.ez.ez.ez.ez.ez?!||||||||||||||
		 !...:!.ez.ez.ez||||||||||!!^^""'   ||||
		 !.......:!?|||||!!^^""'            ||||
		 !.........||||                     ||||
		 !.........||||  |||||              ||||
		 !.........||||  |                  ||||
		 !.........||||  |	        ||||    ||||
		 !.........||||  |||||        |     ||||
		 !.........||||  |           |      ||||
		 `.........||||  |          ||||  ,||||
		  .;.......||||  |||||        _.-!!|||||
   .,uodWBBBBb.....||||       _.-!!|||||||||!:'
!YBBBBBBBBBBBBBBb..!|||:..-!!|||||||!iof68BBBBBb....
!..YBBBBBBBBBBBBBBb!!||||||||!iof68BBBBBBRPFT?!::   `.
!....YBBBBBBBBBBBBBBbaaitf68BBBBBBRPFT?!:::::::::     `.
!......YBBBBBBBBBBBBBBBBBBBRPFT?!::::::;:!^"`;:::       `.
!........YBBBBBBBBBBRPFT?!::::::::::^''...::::::;         .ez.ez
`..........YBRPFT?!::::::::::::::::::::::::;.ez.ez.e      .ez.ez.e
  `..........:::::::::::::::::::::::;.ez.ez.ez.ez.ez.e     `.ez.ez'
	`........::::::::::::::::;.ez.ez.ez.ez.ez.ez.ez.ez.e    `
	  `......:::::::::;.ez.ez.ez.ez.ez.ez.ez.ez.ez.ez.ez.e
		`....:::;:.ez.ez.ez.ez.ez.ez.ez.ez.ez.ez.ez.ez.ez.e!
		  `..::!.ez.ez.ez.ez.ez.ez.ez.ez.ez.ez.ez.ez|!^"'
			`' !!.ez.ez.ez.ez.ez.ez.ez.ez.ez.e|!^"'
				`!!.ez.ez.ez.ez.ez.ez.ez|!^"'
				  `!.ez.ez.ez.ez.e|!^"'
					`!.ez.ez|!^"'
					  `!^"'
*/

/*
************************************************************
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A12.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_

/* TIP: Do not change pragmas, unless necessary .......................................*/
/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'f', /* Fixed mode (constant size) */
	MODE_ADDIT = 'a', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'm'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR		(-1)						/* General error message */
#define READER_TERMINATOR	'\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (Eazy) .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

/* Add your bit-masks constant definitions here - Defined for BOA */
/* BITS                                (7654.3210) */
#define READER_DEFAULT_FLAG 0x00 	/* (0000.0000)_2 = (000)_10 */
/* TO_DO: BIT 3: END = End of buffer flag */
/* TO_DO: BIT 2: REL = Rellocation memory flag */
/* TO_DO: BIT 1: EMP = Buffer empty flag */
/* TO_DO: BIT 0: FUL = Buffer full flag */

#define NCHAR				128			/* Chars from 0 to 127 */

#define CHARSEOF			(-1)		/* EOF Code for Reader */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (Eazy) .................................. */

/* TODO: Adjust datatypes */

/* Offset declaration */
typedef struct position {
	ez_int mark;			/* the offset to the mark position (in chars) */
	ez_int read;			/* the offset to the get a char position (in chars) */
	ez_int wrte;			/* the offset to the add chars (in chars) */
} Position;

/* Buffer structure */
typedef struct bufferReader {
	ez_string	content;			/* pointer to the beginning of character array (character buffer) */
	ez_int		size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	ez_int		increment;			/* character array increment factor */
	ez_int		mode;				/* operational mode indicator */
	ez_byte		flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Position		position;				/* Offset / position field */
	ez_int		histogram[NCHAR];	/* Statistics of chars */
	ez_int		numReaderErrors;	/* Number of errors from Reader */
} Buffer, *BufferPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
BufferPointer	readerCreate		(ez_int, ez_int, ez_int);
BufferPointer	readerAddChar		(BufferPointer const, ez_char);
ez_boln		readerClear		    (BufferPointer const);
ez_boln		readerFree		    (BufferPointer const);
ez_boln		readerIsFull		(BufferPointer const);
ez_boln		readerIsEmpty		(BufferPointer const);
ez_boln		readerSetMark		(BufferPointer const, ez_int);
ez_int		readerPrint		    (BufferPointer const);
ez_int		readerLoad			(BufferPointer const, FILE* const);
ez_boln		readerRecover		(BufferPointer const);
ez_boln		readerRetract		(BufferPointer const);
ez_boln		readerRestore		(BufferPointer const);
/* Getters */
ez_char		readerGetChar		(BufferPointer const);
ez_string	readerGetContent	(BufferPointer const, ez_int);
ez_int		readerGetPosRead	(BufferPointer const);
ez_int		readerGetPosWrte	(BufferPointer const);
ez_int		readerGetPosMark	(BufferPointer const);
ez_int		readerGetSize		(BufferPointer const);
ez_int		readerGetInc		(BufferPointer const);
ez_int		readerGetMode		(BufferPointer const);
ez_byte		readerGetFlags		(BufferPointer const);
ez_void		readerPrintStat		(BufferPointer const);
ez_int		readerNumErrors		(BufferPointer const);

#endif
