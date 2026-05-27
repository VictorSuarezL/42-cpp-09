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

bool BitcoinExchange::isValidDate(const std::string &date) const
{
	int	year;
	int	month;
	int	day;
	int	days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return (false);
	year = std::atoi(date.substr(0, 4).c_str());
	month = std::atoi(date.substr(5, 2).c_str());
	day = std::atoi(date.substr(8, 2).c_str());
	if (month < 1 || month > 12)
		return (false);
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
		days[2] = 29;
	if (day < 1 || day > days[month])
		return (false);
	return (true);
}

bool BitcoinExchange::isValidValue(const std::string &value, double &number) const
{
	std::istringstream	stream(value);
	char				rest;

	stream >> number;
	if (stream.fail() || (stream >> rest))
	{
		std::cerr << "Error: bad input => " << value << std::endl;
		return (false);
	}
	if (number < 0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return (false);
	}
	if (number > 1000)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return (false);
	}
	return (true);
}

bool BitcoinExchange::getRate(const std::string &date, double &rate) const
{
	std::map<std::string, double>::const_iterator	it;

	it = _rates.lower_bound(date);
	if (it != _rates.end() && it->first == date)
	{
		rate = it->second;
		return (true);
	}
	if (it == _rates.begin())
		return (false);
	--it;
	rate = it->second;
	return (true);
}

void BitcoinExchange::loadDatabase(const std::string &filename)
{
	std::ifstream	file(filename.c_str());
	std::string		line;
	std::string		date;
	std::string		value;
	std::size_t		comma;

	if (!file)
		throw std::runtime_error("Error: could not open file.");
	std::getline(file, line);
	while (std::getline(file, line))
	{
		comma = line.find(',');
		if (comma != std::string::npos)
		{
			date = line.substr(0, comma);
			value = line.substr(comma + 1);
			_rates[date] = std::atof(value.c_str());
		}
	}
}

void BitcoinExchange::processInput(const std::string &filename) const
{
	std::ifstream	file(filename.c_str());
	std::string		line;
	std::string		date;
	std::string		valueStr;
	std::size_t		pipe;
	double			value;
	double			rate;

	if (!file)
		throw std::runtime_error("Error: could not open file.");
	std::getline(file, line);
	while (std::getline(file, line))
	{
		pipe = line.find(" | ");
		if (pipe == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		date = line.substr(0, pipe);
		valueStr = line.substr(pipe + 3);
		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}
		if (!isValidValue(valueStr, value))
			continue;
		if (!getRate(date, rate))
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}
		std::cout << date << " => " << value << " = " << value * rate << std::endl;
	}
}
