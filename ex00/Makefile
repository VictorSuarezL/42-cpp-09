NAME = btc

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = main.cpp BitcoinExchange.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

main.o: main.cpp BitcoinExchange.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

BitcoinExchange.o: BitcoinExchange.cpp BitcoinExchange.hpp
	$(CXX) $(CXXFLAGS) -c BitcoinExchange.cpp -o BitcoinExchange.o

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
