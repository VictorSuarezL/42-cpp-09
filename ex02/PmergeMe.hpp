#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <climits>
# include <cstdlib>
# include <ctime>
# include <deque>
# include <iomanip>
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

class PmergeMe
{
	private:
		std::vector<int>	_vector;
		std::deque<int>		_deque;
		double				_vectorTime;
		double				_dequeTime;

		static int					parseNumber(const std::string &text);
		static std::vector<int>		sortVector(const std::vector<int> &values);
		static std::deque<int>		sortDeque(const std::deque<int> &values);
		static void					insertVector(std::vector<int> &values, int number);
		static void					insertDeque(std::deque<int> &values, int number);
		static std::vector<std::size_t>	jacobsthalOrder(std::size_t size);
		static void					printVector(const std::vector<int> &values);

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &other);
		PmergeMe &operator=(const PmergeMe &other);
		~PmergeMe();

		void	parse(int argc, char **argv);
		void	sort();
		void	print() const;
};

#endif
