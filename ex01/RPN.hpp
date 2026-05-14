#ifndef RPN_HPP
# define RPN_HPP

# include <cstdlib>
# include <iostream>
# include <sstream>
# include <stack>
# include <stdexcept>
# include <string>

class RPN
{
	private:
		std::stack<int>	_numbers;

		static bool	isOperator(const std::string &token);
		void		applyOperator(char op);

	public:
		RPN();
		RPN(const RPN &other);
		RPN &operator=(const RPN &other);
		~RPN();

		int	calculate(const std::string &expression);
};

#endif
