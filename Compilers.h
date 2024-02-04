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
* File name: Compilers.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A12, A22, A32.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file defines the functions called by main function.
* Function list: mainReader(), mainScanner(), mainParser().
*************************************************************/

#ifndef COMPILERS_H_
#define COMPILERS_H_

#define DEBUG 0

/*
 * ............................................................................
 * ADVICE 1:
 * Please check the "TODO" labels to develop your activity.
 *
 * ADVICE 2: This file must be updated according to each assignment
 * (see the progression: reader > scanner > parser).
 * ............................................................................
 */

/* TO_DO: Adjust your language (cannot be "Sofia") */

/* Language name */
#define STR_LANGNAME	"Eazy"

/* Logical constants - adapt for your language */
#define True  1
#define False 0

/*
------------------------------------------------------------
Data types definitions
NOTE: Some types may not be directly used by your language,
		but they can be necessary for conversions.
------------------------------------------------------------
*/


/* TO_DO: Define your typedefs */
typedef char			ez_char;
typedef char* ez_string;
typedef int				ez_int;
typedef float			ez_real;
typedef void			ez_void;

typedef unsigned char	ez_boln;
typedef unsigned char	ez_byte;

typedef long			ez_long;
typedef double			ez_doub;

/*
------------------------------------------------------------
Programs:
1: Reader - invokes MainReader code
2: Scanner - invokes MainScanner code
3: Parser - invokes MainParser code
------------------------------------------------------------
*/
enum PROGRAMS {
	PGM_READER	= 'r',
	PGM_SCANNER = 's',
	PGM_PARSER	= 'p'
};

/*
------------------------------------------------------------
Main functions signatures
(Code will be updated during next assignments)
------------------------------------------------------------
*/
ez_int mainReader(ez_int argc, ez_string* argv);

/* 
TO_DO: Include later mainScaner (A22) and mainParser (A32)
*/
ez_void printLogo();

#endif
