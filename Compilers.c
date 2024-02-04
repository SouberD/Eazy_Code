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
* File name: compilers.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A12, A22, A32.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main program of Compilers Project
* Function list: main().
************************************************************
*/


#include <stdio.h>
#include <stdlib.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

/*
 * ............................................................................
 * ADVICE 1:
 * Please check the "TODO" labels to develop your activity.
 *
 * ADVICE 2: This file must be updated according to each assignment
 * (see the progression: reader > scanner > parser).
 * ............................................................................
 */

/*
***********************************************************
* Function name: main
* Purpose: Main function
* Author: Paulo Sousa
* History/Versions: Ver F22
* Called functions: mainReader(), mainScanner(), mainParser()
* Parameters: Command line arguments - argc, argv
* Return value: Status
* Algorithm: -
*************************************************************
*/

ez_int main(int argc, char** argv) {
	ez_int i;
	printLogo();
	if (DEBUG) {
		for (i = 0; i < argc; ++i)
			printf("argv[%d] = %s\n", i, argv[i]);
	}
	if (argc < 2) {
		printf("%s%c%s%c%s%c%s", "OPTIONS:\n* [",
			PGM_READER, "] - Reader\n* [",
			PGM_SCANNER, "] - Scanner\n* [",
			PGM_PARSER, "] - Parser\n");
		return EXIT_FAILURE;
	}
	ez_char option = argv[1][0];
	switch (option) {
	case PGM_READER:
		printf("%s%c%s", "\n[Option '", PGM_READER, "': Starting READER .....]\n\n");
		mainReader(argc, argv);
		break;
	/* TO_DO: Include later SCANNER (A22) and PARSER (A32) */
	default:
		printf("%s%c%s%c%s%c%s", "* OPTIONS:\n- [",
			PGM_READER, "] - Reader\n- [",
			PGM_SCANNER, "] - Scanner\n- [",
			PGM_PARSER, "] - Parser\n");
		break;
	}
	return EXIT_SUCCESS;
}

/*
***********************************************************
* Function name: printLogo
* Purpose: Print Logo
* Author: Paulo Sousa
* History/Versions: Ver S23
* Called functions: -
* Parameters: -
* Return value: (Null)
* Algorithm: -
*************************************************************
*/

/* TO_DO: Update your logo with your own language message */

ez_void printLogo() {
	printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
		 "\t=---------------------------------------=\n",
		 "\t            .,,.ez.ez.ez,.\n",
		 "\t   ..,.ez.ez.ez.ez.ez.ez.ez.ez?l!i:.\n",
		 "\t,=.ez.ez.ez.ez.ez.ez.ez?!||||||||||||||\n",
		 "\t!...:!.ez.ez.ez||||||||||!!^^""'   ||||\n",
		 "\t!.......:!?|||||!!^^""'            ||||\n",
		 "\t!.........||||                     ||||\n",
		 "\t!.........||||  |||||              ||||\n",
		 "\t!.........||||  |                  ||||\n",
		 "\t!.........||||  |	      ||||    ||||\n",
		 "\t!.........||||  |||||        |     ||||\n",
		 "\t!.........||||  |           |      ||||\n",
	   	 "\t`.........||||  |          ||||  ,||||\n",
		  "\t.;.......||||  |||||        _.-!!|||||\n",
   "\t.,uodWBBBBb.....||||       _.-!!|||||||||!:'\n",
"\t!YBBBBBBBBBBBBBBb..!|||:..-!!|||||||!iof68BBBBBb....\n",
"\t!..YBBBBBBBBBBBBBBb!!||||||||!iof68BBBBBBRPFT?!::`.\n",
"\t!....YBBBBBBBBBBBBBBbaaitf68BBBBBBRPFT?!:::::::::     `.\n",
"\t!......YBBBBBBBBBBBBBBBBBBBRPFT?!::::::;:!^`;:::       . \n",
"\t!........YBBBBBBBBBBRPFT?!::::::::::^''...::::::;.ez.     ez\n",
"\t`..........YBRPFT?!::::::::::::::::::::::::;.ez.ez.e.ez.  ez.e\n",
"\t`..........:::::::::::::::::::::::;.ez.ez.ez.ez.ez.ez.ez.   ez'\n",
    "\t`........::::::::::::::::;.ez.ez.ez.ez.ez.ez.ez.ez.ez.   `\n",
      "\t`......:::::::::;.ez.ez.ez.ez.ez.ez.ez.ez.ez.ez.ez.ez    \n",
        "\t`....:::;:.ez.ez.ez.ez.ez.ez.ez.ez.ez.ez.ez.ez.ez.e!   \n",
          "\t`..::!.ez.ez.ez.ez.ez.ez.ez.ez.ez.ez.ez.ez|!^'\n",
            "\t`' !!.ez.ez.ez.ez.ez.ez.ez.ez.ez.e|!^''\n",
                "\t`!!.ez.ez.ez.ez.ez.ez.ez|!^''\n",
                  "\t`!.ez.ez.ez.ez.e|!^'''\n",
                    "\t`!.ez.ez|!^''\n",
                      "\t`!^''\n"


	);
}
