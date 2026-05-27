#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <climits>
# include <cstdlib>
# include <ctime>
# include <deque>
# include <iomanip>
# include <iostream>
# include <algorithm>
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
		static void					mergeInsertSort(std::vector<int> &values);
		static void					mergeInsertSort(std::deque<int> &values);
		static void					printNumbers(const std::vector<int> &values);

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
