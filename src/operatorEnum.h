/******************************************************
 Copyright (c/c++) 2013-doomsday by Aleksey Slovesnov 
 homepage http://slovesnov.users.sourceforge.net/?parser
 email slovesnov@yandex.ru
 All rights reserved.
 ******************************************************/

#ifndef _operatorEnum_h_
#define _operatorEnum_h_

/*
 notes for OPERATOR_ENUM 
 PLUS should be first in enum. Common operators should go in a row. Order is important. 
 Functions from SIN to MAX (should go in a row), first function should be SIN, last should be MAX
 POW,ATAN2,MIN,MAX should go in a row see parse3 function
 */
enum class OPERATOR_ENUM {
	PLUS,
	MINUS,
	MULTIPLY,
	DIVIDE,
	LEFT_BRACKET,
	RIGHT_BRACKET,
	LEFT_SQUARE_BRACKET,
	RIGHT_SQUARE_BRACKET,
	LEFT_CURLY_BRACKET,
	RIGHT_CURLY_BRACKET,
	COMMA,
	SIN,
	COS,
	TAN,
	COT,
	SEC,
	CSC,
	ASIN,
	ATAN,
	ACOT,
	ASEC,
	ACSC,
	SINH,
	COSH,
	TANH,
	COTH,
	SECH,
	CSCH,
	ASINH,
	ACOSH,
	ATANH,
	ACOTH,
	ASECH,
	ACSCH,
	RANDOM,
	CEIL,
	FLOOR,
	ROUND,
	ABS,
	EXP,
	LOG,
	SQRT,
	POW,
	ATAN2,
	MIN,
	MAX,
	X,
	NUMBER,
	
	END
};

#endif
