/******************************************************
 Copyright (c/c++) 2013-doomsday by Aleksey Slovesnov 
 homepage http://slovesnov.users.sourceforge.net/?parser
 email slovesnov@yandex.ru
 All rights reserved.
 ******************************************************/

#ifndef _node_h_
#define _node_h_

#include <mutex>

#include "operatorEnum.h"

class ExpressionEstimator;

class Node {
	friend class ExpressionEstimator;

	ExpressionEstimator *m_estimator;
	OPERATOR_ENUM m_operator;
	double m_value;
	Node *m_left, *m_right;
	static std::mutex m_mutex;

	void init(ExpressionEstimator *estimator, OPERATOR_ENUM _operator,
			double value, Node *left);

	double calculate();

	static double random();
};

#endif
