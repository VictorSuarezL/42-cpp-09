#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(const RPN &other) : _numbers(other._numbers)
{
}

RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
		_numbers = other._numbers;
	return (*this);
}

RPN::~RPN()
{
}

bool RPN::isOperator(const std::string &token)
{
	return (token.size() == 1
		&& (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/'));
}

void RPN::applyOperator(char op)
{
	int	right;
	int	left;

	if (_numbers.size() < 2)
		throw std::runtime_error("Error");
	right = _numbers.top();
	_numbers.pop();
	left = _numbers.top();
	_numbers.pop();
	if (op == '+')
		_numbers.push(left + right);
	else if (op == '-')
		_numbers.push(left - right);
	else if (op == '*')
		_numbers.push(left * right);
	else
	{
		if (right == 0)
			throw std::runtime_error("Error");
		_numbers.push(left / right);
	}
}

int RPN::calculate(const std::string &expression)
{
	std::istringstream	stream(expression);
	std::string			token;

	while (!_numbers.empty())
		_numbers.pop();
	while (stream >> token)
	{
		if (token.size() == 1 && token[0] >= '0' && token[0] <= '9')
			_numbers.push(std::atoi(token.c_str()));
		else if (isOperator(token))
			applyOperator(token[0]);
		else
			throw std::runtime_error("Error");
	}
	if (_numbers.size() != 1)
		throw std::runtime_error("Error");
	return (_numbers.top());
}
