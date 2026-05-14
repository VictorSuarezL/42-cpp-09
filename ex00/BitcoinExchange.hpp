#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <cstdlib>
# include <fstream>
# include <iomanip>
# include <iostream>
# include <map>
# include <sstream>
# include <stdexcept>
# include <string>

class BitcoinExchange
{
	private:
		std::map<int, double> _rates;

		static bool		isLeapYear(int year);
		static int		dateToInt(const std::string &date);
		static double	valueToDouble(const std::string &value, bool checkLimit);
		static void		printResult(int date, double value, double rate);

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();

		void	loadDatabase(const std::string &filename);
		void	processInput(const std::string &filename) const;
};

#endif
