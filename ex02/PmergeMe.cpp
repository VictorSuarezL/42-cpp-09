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

std::vector<std::size_t> PmergeMe::jacobsthalOrder(std::size_t size)
{
	std::vector<std::size_t>	order;
	std::size_t				j0 = 0;
	std::size_t				j1 = 1;
	std::size_t				next;
	std::size_t				previous = 0;

	if (size == 0)
		return (order);
	while (true)
	{
		next = j1 + 2 * j0;
		j0 = j1;
		j1 = next;
		if (next <= 1)
			continue;
		if (next > size)
			break;
		while (next > previous)
		{
			order.push_back(next - 1);
			--next;
		}
		previous = j1;
	}
	for (std::size_t i = size; i > previous; --i)
		order.push_back(i - 1);
	for (std::size_t i = 0; i < previous; ++i)
	{
		bool	found = false;
		for (std::size_t j = 0; j < order.size(); ++j)
		{
			if (order[j] == i)
				found = true;
		}
		if (!found)
			order.push_back(i);
	}
	return (order);
}

void PmergeMe::insertVector(std::vector<int> &values, int number)
{
	std::size_t	left = 0;
	std::size_t	right = values.size();
	std::size_t	middle;

	while (left < right)
	{
		middle = left + (right - left) / 2;
		if (values[middle] < number)
			left = middle + 1;
		else
			right = middle;
	}
	values.insert(values.begin() + left, number);
}

void PmergeMe::insertDeque(std::deque<int> &values, int number)
{
	std::size_t	left = 0;
	std::size_t	right = values.size();
	std::size_t	middle;

	while (left < right)
	{
		middle = left + (right - left) / 2;
		if (values[middle] < number)
			left = middle + 1;
		else
			right = middle;
	}
	values.insert(values.begin() + left, number);
}

std::vector<int> PmergeMe::sortVector(const std::vector<int> &values)
{
	std::vector<int>			big;
	std::vector<int>			small;
	std::vector<int>			result;
	std::vector<std::size_t>	order;
	bool					hasLast = false;
	int						last = 0;

	if (values.size() <= 1)
		return (values);
	for (std::size_t i = 0; i < values.size(); i += 2)
	{
		if (i + 1 == values.size())
		{
			hasLast = true;
			last = values[i];
		}
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
	result = sortVector(big);
	order = jacobsthalOrder(small.size());
	for (std::size_t i = 0; i < order.size(); ++i)
		insertVector(result, small[order[i]]);
	if (hasLast)
		insertVector(result, last);
	return (result);
}

std::deque<int> PmergeMe::sortDeque(const std::deque<int> &values)
{
	std::deque<int>				big;
	std::deque<int>				small;
	std::deque<int>				result;
	std::vector<std::size_t>	order;
	bool						hasLast = false;
	int							last = 0;

	if (values.size() <= 1)
		return (values);
	for (std::size_t i = 0; i < values.size(); i += 2)
	{
		if (i + 1 == values.size())
		{
			hasLast = true;
			last = values[i];
		}
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
	result = sortDeque(big);
	order = jacobsthalOrder(small.size());
	for (std::size_t i = 0; i < order.size(); ++i)
		insertDeque(result, small[order[i]]);
	if (hasLast)
		insertDeque(result, last);
	return (result);
}

void PmergeMe::sort()
{
	clock_t	start;

	start = std::clock();
	_vector = sortVector(_vector);
	_vectorTime = static_cast<double>(std::clock() - start) * 1000000.0 / CLOCKS_PER_SEC;
	start = std::clock();
	_deque = sortDeque(_deque);
	_dequeTime = static_cast<double>(std::clock() - start) * 1000000.0 / CLOCKS_PER_SEC;
}

void PmergeMe::printVector(const std::vector<int> &values)
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
	printVector(_vector);
	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << _vector.size()
		<< " elements with std::vector : " << _vectorTime << " us" << std::endl;
	std::cout << "Time to process a range of " << _deque.size()
		<< " elements with std::deque : " << _dequeTime << " us" << std::endl;
}
