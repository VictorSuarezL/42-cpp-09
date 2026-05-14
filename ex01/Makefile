NAME = RPN

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = main.cpp RPN.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

main.o: main.cpp RPN.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

RPN.o: RPN.cpp RPN.hpp
	$(CXX) $(CXXFLAGS) -c RPN.cpp -o RPN.o

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
