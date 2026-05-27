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
		std::map<std::string, double> _rates;

		bool	isValidDate(const std::string &date) const;
		bool	isValidValue(const std::string &value, double &number) const;
		bool	getRate(const std::string &date, double &rate) const;

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();

		void	loadDatabase(const std::string &filename);
		void	processInput(const std::string &filename) const;
};

#endif
