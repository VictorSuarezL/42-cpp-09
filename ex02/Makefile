NAME = PmergeMe

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = main.cpp PmergeMe.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

main.o: main.cpp PmergeMe.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

PmergeMe.o: PmergeMe.cpp PmergeMe.hpp
	$(CXX) $(CXXFLAGS) -c PmergeMe.cpp -o PmergeMe.o

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
