/******************************************************
 Copyright (c/c++) 2013-doomsday by Aleksey Slovesnov 
 homepage http://slovesnov.users.sourceforge.net/?parser
 email slovesnov@yandex.ru
 All rights reserved.
 ******************************************************/

#ifndef _expressionEstimator_h_
#define _expressionEstimator_h_

#include <vector>
#include <cstring> //strchr
#include <string>
#include <stdexcept>

#include "node.h"

class ExpressionEstimator {
	friend class Node;

	std::string m_expression;
	double m_tokenValue;
	OPERATOR_ENUM m_operator;
	unsigned m_position;
	const double *m_argument;
	int m_argumentSize;
	unsigned m_arguments;
	Node *m_root;
	std::vector<Node*> m_vnode;

	inline bool isLetter() {
		return isalpha(m_expression[m_position]) != 0;
	}

	inline bool isDigit() {
		return isdigit(m_expression[m_position]) != 0;
	}

	inline static bool isDigit(char c) {
		return isdigit(c) != 0;
	}

	inline bool isPoint() {
		return m_expression[m_position] == '.';
	}

	inline bool isFunctionSymbol() {
		char c = m_expression[m_position];
		return isalnum(c) != 0 || c == '_';
	}

	void getToken();

	Node* parse();
	Node* parse1();
	Node* parse2();
	Node* parse3();

	inline Node* createNode(OPERATOR_ENUM _operator, Node *left) {
		Node *node = new Node();
		node->init(this, _operator, 0, left);
		return node;
	}

	inline Node* createNode(OPERATOR_ENUM _operator) {
		Node *node = new Node();
		node->init(this, _operator, 0, NULL);
		return node;

	}

	inline Node* createNode(OPERATOR_ENUM _operator, double value) {
		Node *node = new Node();
		node->init(this, _operator, value, NULL);
		return node;
	}

	inline void checkBracketBalance(OPERATOR_ENUM open) {
		if ((open == OPERATOR_ENUM::LEFT_BRACKET && m_operator != OPERATOR_ENUM::RIGHT_BRACKET)
				|| (open == OPERATOR_ENUM::LEFT_SQUARE_BRACKET
						&& m_operator != OPERATOR_ENUM::RIGHT_SQUARE_BRACKET)
				|| (open == OPERATOR_ENUM::LEFT_CURLY_BRACKET
						&& m_operator != OPERATOR_ENUM::RIGHT_CURLY_BRACKET)) {
			throw std::runtime_error(
					"close bracket expected or another type of close bracket");
		}
	}

	static int getIndex(const char *a[], const char *v);

	void clear();

public:

#ifdef _DEBUG
	static int totalCreated;
	static int totalDestroyed;
#endif

	ExpressionEstimator() {
		m_root = NULL; //don't remove
	}

	//forbid copy
	ExpressionEstimator(ExpressionEstimator const&) = delete;
	ExpressionEstimator& operator=(ExpressionEstimator const&) = delete;

	template<typename ...A>
	ExpressionEstimator(const std::string &expression, A ...a) {
		std::vector<std::string> v = { std::forward<std::string>(a)... };
		try{
			compile(expression,v);
		}
		catch(std::exception& e){
			clear();
			throw;
		}
	}

	ExpressionEstimator(const std::string &expression,
			std::vector<std::string> const &v):ExpressionEstimator(){
		try{
			compile(expression,v);
		}
		catch(std::exception& e){
			clear();
			throw;
		}
	}

	ExpressionEstimator(const std::string &expression,
			std::initializer_list<std::string> const &v):ExpressionEstimator() {
		try{
			compile(expression,std::vector<std::string>( v));
		}
		catch(std::exception& e){
			clear();
			throw;
		}
	}
	ExpressionEstimator(const std::string &expression, const std::string *x,
			const int size):ExpressionEstimator() {
		try{
			compile(expression,std::vector<std::string>(x, x + size));
		}
		catch(std::exception& e){
			clear();
			throw;
		}
	}
	ExpressionEstimator(const std::string &expression, std::string *x,
			const int size):ExpressionEstimator() {
		try{
			compile(expression,std::vector<std::string>(x, x + size));
		}
		catch(std::exception& e){
			clear();
			throw;
		}
	}

	ExpressionEstimator(const char *expression):ExpressionEstimator(){
		try{
			compile(expression);
		}
		catch(std::exception& e){
			clear();
			throw;
		}
	}

	ExpressionEstimator(std::string const & expression) : ExpressionEstimator(expression.c_str()){
	}

	void compile(const char *expression);
	void compile(const std::string &expression) {
		compile(expression.c_str());
	}

	/*compile with variable list*/
	template<typename ...A>
	void compile(const std::string &expression, A ...a) {
		std::vector<std::string> v = { std::forward<std::string>(a)... };
		compile(expression, v);
	}
	void compile(const std::string &expression,
			std::vector<std::string> const &v);

	void compile(const std::string &expression,
			std::initializer_list<std::string> const &v) {
		compile(expression, std::vector<std::string> { v });
	}
	void compile(const char* expression,
			std::initializer_list<std::string> const &v) {
		compile(expression, std::vector<std::string> { v });
	}
	void compile(const std::string &expression, const std::string *x,
			const int size) {
		compile(expression, std::vector<std::string>(x, x + size) );
	}
	void compile(const std::string &expression, std::string *x,
			const int size) {
		compile(expression, std::vector<std::string>(x, x + size) );
	}


	template <typename...A>
	double calculate(A...a){
		std::vector<double> v={std::forward<double>(a)...};
		return calculate(v);
	}

	double calculate(std::vector<double> const &v) {
		return calculate( (const double *)v.data(), int(v.size()));
	}

	double calculate(std::initializer_list<double> const &v) {
		return calculate(std::vector<double>{v});
	}

	double calculate(const double *x, const int size) {
		m_argument = x;
		m_argumentSize = size;
		return calculate();
	}

	double calculate(double *x, const int size) {
		m_argument = x;
		m_argumentSize = size;
		return calculate();
	}

	double calculate();

	/**
	 * 
	 * @return number of expression arguments
	 */
	inline int getArguments() {
		return m_arguments;
	}

	static double calculate(const char *s);
	static double calculate(std::string const & s){
		return calculate(s.c_str());
	}

	~ExpressionEstimator();
};

#endif
