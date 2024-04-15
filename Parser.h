/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: winter, 2023
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
* File name: Parser.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A32.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main header for Parser (.h)
************************************************************
*/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef READER_H_
#include "Reader.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token			lookahead;
extern BufferPointer	stringLiteralTable;
extern ez_int			line;
extern Token			tokenizer(ez_void);
extern ez_string		keywordTable[KWT_SIZE];
static ez_int			syntaxErrorNumber = 0;

#define LANG_WRTE		"pout("
#define LANG_READ		"pin("
#define LANG_MAIN		"main("

/* TO_DO: Create ALL constants for keywords (sequence given in table.h) */

/* Constants */
enum KEYWORDS {
	NO_ATTR = -1,
	KW_def,
	KW_data,
	KW_code,
	KW_int,
	KW_real,
	KW_string,
	KW_if,
	KW_then,
	KW_else,
	KW_while,
	KW_do,
	KW_return,
	KW_break,
	KW_continue,
	KW_try,
	KW_catch
};

/* TO_DO: Define the number of BNF rules */
#define NUM_BNF_RULES 16

/* Parser */
typedef struct parserData {
	ez_int parsHistogram[NUM_BNF_RULES];	/* Number of BNF Statements */
} ParserData, * pParsData;

/* Number of errors */
ez_int numParserErrors;

/* Scanner data */
ParserData psData;

/* Function definitions */
ez_void startParser();
ez_void matchToken(ez_int, ez_int);
ez_void syncErrorHandler(ez_int);
ez_void printError();
ez_void printBNFData(ParserData psData);

/* List of BNF statements */
enum BNF_RULES {
	BNF_error,										/*  0: Error token */
	BNF_codeSession,								/*  1 */
	BNF_comment,									/*  2 */
	BNF_dataSession,								/*  3 */
	BNF_optVarListDeclarations,						/*  4 */
	BNF_optionalStatements,							/*  5 */
	BNF_outputStatement,							/*  6 */
	BNF_outputVariableList,							/*  7 */
	BNF_program,									/*  8 */
	BNF_statement,									/*  9 */
	BNF_statements,									/* 10 */
	BNF_statementsPrime								/* 11 */
};


/* TO_DO: Define the list of keywords */
static ez_string BNFStrTable[NUM_BNF_RULES] = {
	"BNF_error",					//00
	"BNF_codeSession",
	"BNF_comment",
	"BNF_dataSession",
	"BNF_optVarListDeclarations",
	"BNF_optionalStatements",
	"BNF_outputStatement",
	"BNF_outputVariableList",
	"BNF_program",
	"BNF_statement",
	"BNF_statements",
	"BNF_statementsPrime"			//11
};

/* TO_DO: Place ALL non-terminal function declarations */
ez_void codeSession();
ez_void comment();
ez_void dataSession();
ez_void optVarListDeclarations();
ez_void optionalStatements();
ez_void outputStatement();
ez_void outputVariableList();
ez_void program();
ez_void statement();
ez_void statements();
ez_void statementsPrime();

#endif
