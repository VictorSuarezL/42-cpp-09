#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : _vectorTime(0), _dequeTime(0)
{
}

PmergeMe::PmergeMe(const PmergeMe &other)
	: _vector(other._vector), _deque(other._deque),
	_vectorTime(other._vectorTime), _dequeTime(other._dequeTime)
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		_vector = other._vector;
		_deque = other._deque;
		_vectorTime = other._vectorTime;
		_dequeTime = other._dequeTime;
	}
	return (*this);
}

PmergeMe::~PmergeMe()
{
}

int PmergeMe::parseNumber(const std::string &text)
{
	long	number;
	char	*end;

	if (text.empty())
		throw std::runtime_error("Error");
	for (std::size_t i = 0; i < text.size(); ++i)
	{
		if (text[i] < '0' || text[i] > '9')
			throw std::runtime_error("Error");
	}
	number = std::strtol(text.c_str(), &end, 10);
	if (*end != '\0' || number <= 0 || number > INT_MAX)
		throw std::runtime_error("Error");
	return (static_cast<int>(number));
}

void PmergeMe::parse(int argc, char **argv)
{
	int	number;

	if (argc < 2)
		throw std::runtime_error("Error");
	for (int i = 1; i < argc; ++i)
	{
		number = parseNumber(argv[i]);
		_vector.push_back(number);
		_deque.push_back(number);
	}
}

void PmergeMe::mergeInsertSort(std::vector<int> &values)
{
	std::vector<int>			big;
	std::vector<int>			small;

	if (values.size() <= 1)
		return ;
	for (std::size_t i = 0; i < values.size(); i += 2)
	{
		if (i + 1 == values.size())
			small.push_back(values[i]);
		else if (values[i] < values[i + 1])
		{
			small.push_back(values[i]);
			big.push_back(values[i + 1]);
		}
		else
		{
			small.push_back(values[i + 1]);
			big.push_back(values[i]);
		}
	}
	mergeInsertSort(big);
	values = big;
	for (std::size_t i = 0; i < small.size(); ++i)
		values.insert(std::lower_bound(values.begin(), values.end(), small[i]), small[i]);
}

void PmergeMe::mergeInsertSort(std::deque<int> &values)
{
	std::deque<int>				big;
	std::deque<int>				small;

	if (values.size() <= 1)
		return ;
	for (std::size_t i = 0; i < values.size(); i += 2)
	{
		if (i + 1 == values.size())
			small.push_back(values[i]);
		else if (values[i] < values[i + 1])
		{
			small.push_back(values[i]);
			big.push_back(values[i + 1]);
		}
		else
		{
			small.push_back(values[i + 1]);
			big.push_back(values[i]);
		}
	}
	mergeInsertSort(big);
	values = big;
	for (std::size_t i = 0; i < small.size(); ++i)
		values.insert(std::lower_bound(values.begin(), values.end(), small[i]), small[i]);
}

void PmergeMe::sort()
{
	clock_t	start;

	start = std::clock();
	mergeInsertSort(_vector);
	_vectorTime = static_cast<double>(std::clock() - start) * 1000000.0 / CLOCKS_PER_SEC;
	start = std::clock();
	mergeInsertSort(_deque);
	_dequeTime = static_cast<double>(std::clock() - start) * 1000000.0 / CLOCKS_PER_SEC;
}

void PmergeMe::printNumbers(const std::vector<int> &values)
{
	for (std::size_t i = 0; i < values.size(); ++i)
	{
		if (i != 0)
			std::cout << " ";
		std::cout << values[i];
	}
	std::cout << std::endl;
}

void PmergeMe::print() const
{
	std::cout << "After: ";
	printNumbers(_vector);
	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << _vector.size()
		<< " elements with std::vector : " << _vectorTime << " us" << std::endl;
	std::cout << "Time to process a range of " << _deque.size()
		<< " elements with std::deque : " << _dequeTime << " us" << std::endl;
}
