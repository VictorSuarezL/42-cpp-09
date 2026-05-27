#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(const RPN &other)
{
	(void)other;
}

RPN &RPN::operator=(const RPN &other)
{
	(void)other;
	return (*this);
}

RPN::~RPN()
{
}

void RPN::calculate(const std::string &expression) const
{
	std::stack<int>		numbers;
	std::istringstream	stream(expression);
	std::string			token;
	int					a;
	int					b;

	while (stream >> token)
	{
		if (token.size() == 1 && token[0] >= '0' && token[0] <= '9')
			numbers.push(token[0] - '0');
		else if (token.size() == 1
			&& (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/'))
		{
			if (numbers.size() < 2)
				throw std::runtime_error("Error");
			b = numbers.top();
			numbers.pop();
			a = numbers.top();
			numbers.pop();
			if (token[0] == '+')
				numbers.push(a + b);
			else if (token[0] == '-')
				numbers.push(a - b);
			else if (token[0] == '*')
				numbers.push(a * b);
			else
			{
				if (b == 0)
					throw std::runtime_error("Error");
				numbers.push(a / b);
			}
		}
		else
			throw std::runtime_error("Error");
	}
	if (numbers.size() != 1)
		throw std::runtime_error("Error");
	std::cout << numbers.top() << std::endl;
}
