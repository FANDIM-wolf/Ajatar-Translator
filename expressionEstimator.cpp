/******************************************************
 Copyright (c/c++) 2013-doomsday by Aleksey Slovesnov 
 homepage http://slovesnov.users.sourceforge.net/?parser
 email slovesnov@yandex.ru
 All rights reserved.
 ******************************************************/

#include <regex>
#include <algorithm>
#define _USE_MATH_DEFINES //for M_PI
#include <cmath>

#include "expressionEstimator.h"

const char *CONSTANT_NAME[] = { "PI", "E", "SQRT2", "SQRT1_2", "LN2", "LN10",
		"LOG2E", "LOG10E", NULL };
const double CONSTANT_VALUE[] = { M_PI, M_E, M_SQRT2, M_SQRT1_2, M_LN2, M_LN10,
		M_LOG2E, M_LOG10E };
//const double CONSTANT_VALUE[] = { M_PI, M_E, sqrt(2), sqrt(0.5), log(2), log(
//		10), 1 / log(2), 1 / log(10) };

const char *OPERATOR[] = { "PLUS", "MINUS", "MULTIPLY", "DIVIDE",
		"LEFT_BRACKET", "RIGHT_BRACKET", "LEFT_SQUARE_BRACKET",
		"RIGHT_SQUARE_BRACKET", "LEFT_CURLY_BRACKET", "RIGHT_CURLY_BRACKET",
		"COMMA", "SIN", "COS", "TAN", "COT", "SEC", "CSC", "ASIN", "ACOS",
		"ATAN", "ACOT", "ASEC", "ACSC", "SINH", "COSH", "TANH", "COTH", "SECH",
		"CSCH", "ASINH", "ACOSH", "ATANH", "ACOTH", "ASECH", "ACSCH", "RANDOM",
		"CEIL", "FLOOR", "ROUND", "ABS", "EXP", "LOG", "SQRT", "POW", "ATAN2",
		"MIN", "MAX", "X", "NUMBER", "UNARY_MINUS", "END", NULL };


const std::string reservedWords[] = { "exp", "log", "pow", "sqrt", "abs",
		"random", "min", "max", "pi", "e", "sqrt2", "sqrt1_2", "ln2", "ln10",
		"log2e", "log10e", "sin", "cos", "tan", "cot", "sec", "csc", "asin",
		"acos", "atan", "acot", "asec", "acsc", "sinh", "cosh", "tanh", "coth",
		"sech", "csch", "asinh", "acosh", "atanh", "acoth", "asech", "acsch",
		"ceil", "floor", "round", "atan2" };


static std::regex bregex(std::string const& s){
	return std::regex("\\b"+s+"\\b");
}

static std::vector<std::string> splitR(std::string const &s, std::string const &separator = "\\s+") {
	std::vector<std::string> v;
	std::regex rgx(separator);
	std::sregex_token_iterator iter(s.begin(),
			s.end(), rgx, -1);
	std::sregex_token_iterator end;
	for (; iter != end; ++iter){
		v.push_back( *iter);
	}
	return v;
}

#ifdef _DEBUG
	int	ExpressionEstimator::totalDestroyed=0;
	int	ExpressionEstimator::totalCreated=0;
#endif

int ExpressionEstimator::getIndex(const char *a[], const char *v) {
	const char *n;
	int i;
	for (i = 0; (n = a[i]) != NULL; i++) {
		if (strcmp(n, v) == 0) {
			return i;
		}
	}
	throw std::invalid_argument("invalid argument exception");
}

void ExpressionEstimator::getToken() {
	unsigned i;
	char *pEnd = nullptr;
	const char T[] = "+-*/()[]{},";
	const char *p,*p1;
	unsigned long long v;
	
	if (m_position == m_expression.length()) {
		m_operator = OPERATOR_ENUM::END;
	} else if ((p = strchr(T, m_expression[m_position])) != NULL) {
		m_position++;
		m_operator = (OPERATOR_ENUM) (p - T);
	} else if (isLetter()) {
		for (i = m_position++;
				m_position < m_expression.length() && isFunctionSymbol();
				m_position++)
			;
		std::string token = m_expression.substr(i, m_position - i);

		try {
			if (token[0] == 'X' && token.length() == 1) {
				throw std::runtime_error("unknown keyword");
			} else if (token[0] == 'X' && token.length() > 1
					&& isDigit(token[1])) {
				i = unsigned(atoi(token.c_str() + 1));
				if (m_arguments < i + 1) {
					m_arguments = i + 1;
				}
				m_operator = OPERATOR_ENUM::X;
				m_tokenValue = i;
			} else {
				m_operator = (OPERATOR_ENUM) getIndex(OPERATOR, token.c_str());
				i = unsigned(m_operator);
				if (i < unsigned(OPERATOR_ENUM::SIN) || i > unsigned(OPERATOR_ENUM::MAX)) {
					throw std::invalid_argument("invalid argument exception");
				}
			}
		} catch (std::invalid_argument &e1) {
			try {
				m_tokenValue = CONSTANT_VALUE[getIndex(CONSTANT_NAME,
						token.c_str())];
				m_operator = OPERATOR_ENUM::NUMBER;
			} catch (std::invalid_argument &e2) {
				throw std::runtime_error("unknown keyword");
			}
		}
	} else if (isDigit() || isPoint()) {
		m_operator = OPERATOR_ENUM::NUMBER;
		p = m_expression.c_str() + m_position;
		//binary numbers
		//strtoll("0b")=0 but it's error, so check symbol after 'B'
		if (*p == '0' && m_position + 2 < m_expression.length() && p[1] == 'B'
				&& strchr("01.", p[2])) {
			p1 = p + 2;
			bool f=*p1 == '.';
			if (f) {
				m_tokenValue = 0;
			} else {
				m_tokenValue = strtoull(p1, &pEnd, 2);
				p1=pEnd;
			}
			if (*p1 == '.') {
				p1++;
				//strchr("01",'\0')!=NULL
				if(*p1=='0' || *p1=='1'){//0xb1.-1, prevents strtoull("-1")
					//printl(int(*p1))
					v = strtoull(p1, &pEnd, 2);
					m_tokenValue += double(v) / (1ll << (pEnd - p1));
				}
				else{
					if(f){
						throw std::runtime_error("invalid binary constant");
					}
					p--;//for m_position += pEnd - p;
					//printf("[%s]\n",m_expression.c_str() + m_position+(pEnd-p));
				}
			}
		}
		else{
			m_tokenValue = strtod(p, &pEnd);//also parse hex, 0x.34 also parsed here
		}
		m_position += pEnd - p;
	} else {
		throw std::runtime_error("unknown symbol");
	}

}

void ExpressionEstimator::compile(const char *expression) {
	m_position = 0;
	m_arguments = 0;
	m_expression = "";
	m_root = NULL;
	clear();
	m_argument = NULL;

	//parse dot as decimal separator for strtod, so setup standard locale
	const char *lorig = _strdup(setlocale(LC_ALL, NULL));
	setlocale(LC_NUMERIC, "C");

	const char *pc = expression;
	for (; *pc != 0; pc++) { //make upper string without empty symbols
		if (*pc == ' ' || *pc == '\t') {
			continue;
		}
		m_expression += toupper(*pc);
	}

	getToken();
	if (m_operator == OPERATOR_ENUM::END) {
		throw std::runtime_error("unexpected end of expression");
	}
	m_root = parse();
	if (m_operator != OPERATOR_ENUM::END) {
		throw std::runtime_error("end of expression expected");
	}

	//return original locale
	setlocale(LC_ALL, lorig);
	free((void*) lorig);
}

Node* ExpressionEstimator::parse() {
	Node *node = parse1();
	while (m_operator == OPERATOR_ENUM::PLUS || m_operator == OPERATOR_ENUM::MINUS) {
		node = createNode(m_operator, node);
		getToken();
		if (m_operator == OPERATOR_ENUM::PLUS || m_operator == OPERATOR_ENUM::MINUS) {
			throw std::runtime_error("two operators in a row");
		}
		node->m_right = parse1();
	}
	return node;
}

Node* ExpressionEstimator::parse1() {
	Node *node = parse2();
	while (m_operator == OPERATOR_ENUM::MULTIPLY || m_operator == OPERATOR_ENUM::DIVIDE) {
		node = createNode(m_operator, node);
		getToken();
		if (m_operator == OPERATOR_ENUM::PLUS || m_operator == OPERATOR_ENUM::MINUS) {
			throw std::runtime_error("two operators in a row");
		}
		node->m_right = parse2();
	}
	return node;
}



Node* ExpressionEstimator::parse3() {
	Node *node;
	OPERATOR_ENUM open;

	if (m_operator >= OPERATOR_ENUM::SIN && m_operator <= OPERATOR_ENUM::MAX) {
		int arguments;
		if (m_operator >= OPERATOR_ENUM::POW && m_operator <= OPERATOR_ENUM::MAX) {
			arguments = 2;
		} else {
			arguments = m_operator == OPERATOR_ENUM::RANDOM ? 0 : 1;
		}

		node = createNode(m_operator);
		getToken();
		open = m_operator;
		if (m_operator != OPERATOR_ENUM::LEFT_BRACKET && m_operator != OPERATOR_ENUM::LEFT_SQUARE_BRACKET
				&& m_operator != OPERATOR_ENUM::LEFT_CURLY_BRACKET) {
			throw std::runtime_error("open bracket expected");
		}
		getToken();

		if (arguments > 0) {
			node->m_left = parse();

			if (arguments == 2) {
				if (m_operator != OPERATOR_ENUM::COMMA) {
					throw std::runtime_error("comma expected");
				}
				getToken();
				node->m_right = parse();
			}
		}
		checkBracketBalance(open);
	} else {
		switch (m_operator) {

		case OPERATOR_ENUM::X:
		case OPERATOR_ENUM::NUMBER:
			node = createNode(m_operator, m_tokenValue);
			break;

		case OPERATOR_ENUM::LEFT_BRACKET:
		case OPERATOR_ENUM::LEFT_SQUARE_BRACKET:
		case OPERATOR_ENUM::LEFT_CURLY_BRACKET:
			open = m_operator;
			getToken();
			node = parse();
			checkBracketBalance(open);
			break;

		default:
			throw std::runtime_error("unexpected operator");
		}

	}
	getToken();
	return node;
}

double ExpressionEstimator::calculate() {
	if (m_root == NULL) {
		throw std::runtime_error("using of calculate() without compile()");
	}

	unsigned length = m_argument == NULL ? 0 : m_argumentSize;

	if (length != m_arguments) {
		throw std::runtime_error("invalid number of expression arguments");
	}
	return m_root->calculate();
}

double ExpressionEstimator::calculate(const char *s) {
	ExpressionEstimator estimator;
	estimator.compile(s);
	estimator.m_argument = NULL; //clear all arguments
	return estimator.calculate();
}

void ExpressionEstimator::clear() {
	std::vector<Node*>::iterator it;
	for (it = m_vnode.begin(); it != m_vnode.end(); it++) {
		delete *it;
	}
#ifdef _DEBUG
	if(m_vnode.size()!=0){
		//printf("destroyed %d node(s)\n",m_vnode.size());
	}
	totalDestroyed+=m_vnode.size();
#endif
	m_vnode.clear();

}

ExpressionEstimator::~ExpressionEstimator() {
	clear();
}

void ExpressionEstimator::compile(const std::string &expression,std::vector<std::string> const &variables){
	int i;
	std::string s, q,e = expression;
	std::vector<std::string> v;
	std::smatch sm;
	//char r should be \w because use \b in regex replace. 0x10=16 is good, so use '1' 1x.. is invalid
	const char r = '1';

	v=variables;

	std::sort(v.begin(),v.end());
	i=0;
	for (auto &a : v) {
		s=a;
		std::transform(s.begin(), s.end(), s.begin(), ::tolower);
		if (std::find(begin(reservedWords), end(reservedWords), s)
				!= end(reservedWords)) {
			throw std::runtime_error(
					"reserved word \"" + a + "\" is used as variable");
		}
		//also check empty
		if (!std::regex_search(a, std::regex("^_*[A-Za-z]\\w*$") )) {
			throw std::runtime_error(
					std::string("invalid variable name \"") + a + "\"");
		}
		if (i > 0 && a == v[i-1]) {
			throw std::runtime_error(
					std::string("repeated variable \"") + a + "\" in list");
		}
		i++;
	}

	v=variables;
	for (auto &a : v) {
		q=r+a;
		//check 1x... before replace or compile("1x0","x0") will be ok
		if (std::regex_search(e, sm,std::regex( "\\w*"+q+"\\w*" ))) {
			throw std::runtime_error("invalid keyword \"" + sm.str()+"\"");
		}

		if(std::regex_search(a, std::regex("^[xX]\\d+$"))){
			e = std::regex_replace(e, bregex( a ), q);
			a=q;
		}
	}

	s=e;
	i=0;
	for (auto &a : v) {
		q = std::to_string(i);
		if (std::regex_search(e, sm,bregex( "[xX]"+q ))) {
			throw std::runtime_error("unknown variable \"" + sm.str()+"\"");
		}
		s = std::regex_replace(s, bregex( a ),"x"+q);
		i++;
	}

	compile(s);
	if (m_arguments > v.size()) { //compile("x0+x1","x0")
		for (auto &a : splitR(expression, "\\W+")) {
			if (::tolower(a[0]) == 'x'
					&& atoi(a.c_str() + 1) >= int(v.size())) {
				throw std::runtime_error("unknown variable \"" + a + "\"");
			}
		}
		//should not happen
		throw std::runtime_error(
				"unknown variable found ExpressionEstimator::compile at line"
						+ std::to_string(__LINE__));
	}
	m_arguments=v.size();
}

