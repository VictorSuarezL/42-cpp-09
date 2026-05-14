#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _rates(other._rates)
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		_rates = other._rates;
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

bool BitcoinExchange::isLeapYear(int year)
{
	return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

int BitcoinExchange::dateToInt(const std::string &date)
{
	int			year;
	int			month;
	int			day;
	std::string	part;
	int			days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		throw std::runtime_error("Error: bad input => " + date);
	for (std::size_t i = 0; i < date.size(); ++i)
	{
		if (i != 4 && i != 7 && (date[i] < '0' || date[i] > '9'))
			throw std::runtime_error("Error: bad input => " + date);
	}
	year = std::atoi(date.substr(0, 4).c_str());
	month = std::atoi(date.substr(5, 2).c_str());
	day = std::atoi(date.substr(8, 2).c_str());
	if (year < 1)
		throw std::runtime_error("Error: bad input => " + date);
	if (month < 1 || month > 12)
		throw std::runtime_error("Error: bad input => " + date);
	if (month == 2 && isLeapYear(year))
		days[2] = 29;
	if (day < 1 || day > days[month])
		throw std::runtime_error("Error: bad input => " + date);
	return (year * 10000 + month * 100 + day);
}

double BitcoinExchange::valueToDouble(const std::string &value, bool checkLimit)
{
	std::istringstream	stream(value);
	double				number;
	char				rest;

	if (value.empty())
		throw std::runtime_error("Error: bad input => " + value);
	if (value[0] == '-')
		throw std::runtime_error("Error: not a positive number.");
	stream >> number;
	if (stream.fail() || (stream >> rest))
		throw std::runtime_error("Error: bad input => " + value);
	if (number < 0)
		throw std::runtime_error("Error: not a positive number.");
	if (checkLimit && number > 1000)
		throw std::runtime_error("Error: too large a number.");
	return (number);
}

void BitcoinExchange::printResult(int date, double value, double rate)
{
	int	year = date / 10000;
	int	month = date / 100 % 100;
	int	day = date % 100;

	std::cout << std::setfill('0') << std::setw(4) << year << "-"
		<< std::setw(2) << month << "-"
		<< std::setw(2) << day << std::setfill(' ')
		<< " => " << value << " = " << value * rate << std::endl;
}

void BitcoinExchange::loadDatabase(const std::string &filename)
{
	std::ifstream	file(filename.c_str());
	std::string		line;
	std::size_t		comma;

	if (!file)
		throw std::runtime_error("Error: could not open file.");
	std::getline(file, line);
	while (std::getline(file, line))
	{
		if (line.empty())
			continue;
		comma = line.find(',');
		if (comma == std::string::npos)
			continue;
		_rates[dateToInt(line.substr(0, comma))] = valueToDouble(line.substr(comma + 1), false);
	}
}

void BitcoinExchange::processInput(const std::string &filename) const
{
	std::ifstream					file(filename.c_str());
	std::string						line;
	std::size_t						pipe;
	int								date;
	double							value;
	std::map<int, double>::const_iterator	it;

	if (!file)
		throw std::runtime_error("Error: could not open file.");
	std::getline(file, line);
	while (std::getline(file, line))
	{
		try
		{
			pipe = line.find(" | ");
			if (pipe == std::string::npos)
				throw std::runtime_error("Error: bad input => " + line);
			date = dateToInt(line.substr(0, pipe));
			value = valueToDouble(line.substr(pipe + 3), true);
			it = _rates.lower_bound(date);
			if (it == _rates.end() || it->first > date)
			{
				if (it == _rates.begin())
					throw std::runtime_error("Error: bad input => " + line);
				--it;
			}
			printResult(date, value, it->second);
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}
