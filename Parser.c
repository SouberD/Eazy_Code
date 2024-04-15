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
* File name: Parser.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A32.
* Date: May 01 2023
* Purpose: This file contains all functionalities from Parser.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/* Parser data */
extern ParserData psData; /* BNF statistics */

/*
************************************************************
 * Process Parser
 ***********************************************************
 */
 /* TO_DO: This is the function to start the parser - check your program definition */

ez_void startParser() {
	/* TO_DO: Initialize Parser data */
	ez_int i = 0;
	for (i = 0; i < NUM_BNF_RULES; i++) {
		psData.parsHistogram[i] = 0;
	}
	/* Proceed parser */
	lookahead = tokenizer();
	if (lookahead.code != SEOF_T) {
		program();
	}
	matchToken(SEOF_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}


/*
 ************************************************************
 * Match Token
 ***********************************************************
 */
 /* TO_DO: This is the main code for match - check your definition */
ez_void matchToken(ez_int tokenCode, ez_int tokenAttribute) {
	ez_int matchFlag = 1;
	switch (lookahead.code) {
	
	case KyWo_T:
		if (lookahead.attribute.codeType != tokenAttribute)
			matchFlag = 0;
	default:
		if (lookahead.code != tokenCode)
			matchFlag = 0;
	}
	if (matchFlag && lookahead.code == SEOF_T)
		return;
	if (matchFlag) {
		lookahead = tokenizer();
		if (lookahead.code == Err_T) {
			printError();
			lookahead = tokenizer();
			syntaxErrorNumber++;
		}
	}
	else
		syncErrorHandler(tokenCode);
}

/*
 ************************************************************
 * Syncronize Error Handler
 ***********************************************************
 */
 /* TO_DO: This is the function to handler error - adjust basically datatypes */
ez_void syncErrorHandler(ez_int syncTokenCode) {
	printError();
	syntaxErrorNumber++;
	while (lookahead.code != syncTokenCode) {
		if (lookahead.code == SEOF_T)
			exit(syntaxErrorNumber);
		lookahead = tokenizer();
	}
	if (lookahead.code != SEOF_T)
		lookahead = tokenizer();
}

/*
 ************************************************************
 * Print Error
 ***********************************************************
 */
 /* TO_DO: This is the function to error printing - adjust basically datatypes */
ez_void printError() {
	extern numParserErrors;			/* link to number of errors (defined in Parser.h) */
	Token t = lookahead;
	printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
	printf("*****  Token code:%3d Attribute: ", t.code);
	switch (t.code) {
	case Err_T:
		printf("*ERROR*: %s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case Func_T:
		printf("Func_T:\t\t%s\t\n", t.attribute.idLexeme);
		break;
	case Str_T:
		printf("Str_T: %s\n", readerGetContent(stringLiteralTable, t.attribute.contentString));
		break;
	case KyWo_T:
		printf("KyWo_T: %s\n", keywordTable[t.attribute.codeType]);
		break;
	case LP_T:
		printf("LP_T\n");
		break;
	case RP_T:
		printf("RP_T\n");
		break;
	case LB_T:
		printf("LB_T\n");
		break;
	case RB_T:
		printf("RB_T\n");
		break;
	case EndS_T:
		printf("NA\n");
		break;
	default:
		printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
		numParserErrors++; // Updated parser error
	}
}

/*
 ************************************************************
 * Program statement
 * BNF: <program> -> main& { <opt_statements> }
 * FIRST(<program>)= {CMT_T, MNID_T (main ()), SEOF_T}.
 ***********************************************************
 */
ez_void program() {
	/* Update program statistics */
	psData.parsHistogram[BNF_program]++;
	/* Program code */
	switch (lookahead.code) {
	case Cmt_T:
		comment();
	case Func_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_MAIN, 5) == 0) {
			matchToken(Func_T, NO_ATTR);
			matchToken(LB_T, NO_ATTR);
			dataSession();
			codeSession();
			matchToken(RB_T, NO_ATTR);
			break;
		}
		else {
			printError();
		}
	case SEOF_T:
		; // Empty
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Program parsed");
}

/*
 ************************************************************
 * comment
 * BNF: comment
 * FIRST(<comment>)= {Cmt_T}.
 ***********************************************************
 */
ez_void comment() {
	psData.parsHistogram[BNF_comment]++;
	matchToken(Cmt_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Comment parsed");
}

/*
 ************************************************************
 * dataSession
 * BNF: <dataSession> -> data { <opt_varlist_declarations> }
 * FIRST(<program>)= {KW_T (KW_data)}.
 ***********************************************************
 */
ez_void dataSession() {
	psData.parsHistogram[BNF_dataSession]++;
	switch (lookahead.code) {
	case Cmt_T:
		comment();
	default:
	
		// in my language there is no need for the data session keyword or the praceses

		//matchToken(KyWo_T, KW_data);
		matchToken(LB_T, NO_ATTR);
		optVarListDeclarations();
		matchToken(RB_T, NO_ATTR);
		//printf("%s%s\n", STR_LANGNAME, ": Data Session parsed");
	}
}

/*
 ************************************************************
 * Optional Var List Declarations
 * BNF: <opt_varlist_declarations> -> <varlist_declarations> | e
 * FIRST(<opt_varlist_declarations>) = { e, KW_T (KW_int), KW_T (KW_real), KW_T (KW_string)}.
 ***********************************************************
 */
ez_void optVarListDeclarations() {
	psData.parsHistogram[BNF_optVarListDeclarations]++;
	switch (lookahead.code) {
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional Variable List Declarations parsed");
}

/*
 ************************************************************
 * codeSession statement
 * BNF: <codeSession> -> code { <opt_statements> }
 * FIRST(<codeSession>)= {KW_T (KW_code)}.
 ***********************************************************
 */
ez_void codeSession() {
	psData.parsHistogram[BNF_codeSession]++;
	switch (lookahead.code) {
	case Cmt_T:
		comment();
	default:
		// in my language there is no need for the code session keyword

		//matchToken(KyWo_T, KW_code);
		matchToken(LB_T, NO_ATTR);
		optionalStatements();
		matchToken(RB_T, NO_ATTR);
		printf("%s%s\n", STR_LANGNAME, ": Code Session parsed");
	}
}

/* TO_DO: Continue the development (all non-terminal functions) */

/*
 ************************************************************
 * Optional statement
 * BNF: <opt_statements> -> <statements> | ϵ
 * FIRST(<opt_statements>) = { ϵ , IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *				KW_T(KW_while), MNID_T(print&), MNID_T(input&) }
 ***********************************************************
 */
ez_void optionalStatements() {
	psData.parsHistogram[BNF_optionalStatements]++;
	switch (lookahead.code) {
	case Cmt_T:
		comment();
	case Func_T:
		if ((strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) ||
			(strncmp(lookahead.attribute.idLexeme, LANG_READ, 6) == 0)) {
			statements();
			break;
		}
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
}

/*
 ************************************************************
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 * FIRST(<statements>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *		KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
ez_void statements() {
	psData.parsHistogram[BNF_statements]++;

	statement();
	statementsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
}

/*
 ************************************************************
 * Statements Prime
 * BNF: <statementsPrime> -> <statement><statementsPrime> | ϵ
 * FIRST(<statementsPrime>) = { ϵ , IVID_T, FVID_T, SVID_T,
 *		KW_T(KW_if), KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
ez_void statementsPrime() {
	psData.parsHistogram[BNF_statementsPrime]++;
	switch (lookahead.code) {
	case Func_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			statements();
			break;
		}
	default:
		; //empty string
	}
}

/*
 ************************************************************
 * Single statement
 * BNF: <statement> -> <assignment statement> | <selection statement> |
 *	<iteration statement> | <input statement> | <output statement>
 * FIRST(<statement>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if), KW_T(KW_while),
 *			MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
ez_void statement() {
	psData.parsHistogram[BNF_statement]++;
	switch (lookahead.code) {
	case KyWo_T:
		switch (lookahead.attribute.codeType) {
		default:
			printError();
		}
		break;
	case Func_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			outputStatement();
		}
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}

/*
 ************************************************************
 * Output Statement
 * BNF: <output statement> -> print& (<output statementPrime>);
 * FIRST(<output statement>) = { MNID_T(print&) }
 ***********************************************************
 */
ez_void outputStatement() {
	psData.parsHistogram[BNF_outputStatement]++;
	matchToken(Func_T, NO_ATTR);
	matchToken(LP_T, NO_ATTR);
	outputVariableList();
	matchToken(RP_T, NO_ATTR);
	matchToken(EndS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
}

/*
 ************************************************************
 * Output Variable List
 * BNF: <opt_variable list> -> <variable list> | ϵ
 * FIRST(<opt_variable_list>) = { IVID_T, FVID_T, SVID_T, ϵ }
 ***********************************************************
 */
ez_void outputVariableList() {
	psData.parsHistogram[BNF_outputVariableList]++;
	switch (lookahead.code) {
	case Str_T:
		matchToken(Str_T, NO_ATTR);
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Output variable list parsed");
}

/*
 ************************************************************
 * The function prints statistics of BNF rules
 * Param:
 *	- Parser data
 * Return:
 *	- Void (procedure)
 ***********************************************************
 */
 /*
 ez_void printBNFData(ParserData psData) {
 }
 */
ez_void printBNFData(ParserData psData) {
	/* Print Parser statistics */
	printf("Statistics:\n");
	printf("----------------------------------\n");
	int cont = 0;
	for (cont = 0; cont < NUM_BNF_RULES; cont++) {
		if (psData.parsHistogram[cont] > 0)
			printf("%s%s%s%d%s", "Token[", BNFStrTable[cont], "]=", psData.parsHistogram[cont], "\n");
	}
	printf("----------------------------------\n");
}
