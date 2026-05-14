#include "PmergeMe.hpp"

static void	printBefore(int argc, char **argv)
{
	std::cout << "Before: ";
	for (int i = 1; i < argc; ++i)
	{
		if (i != 1)
			std::cout << " ";
		std::cout << argv[i];
	}
	std::cout << std::endl;
}

int	main(int argc, char **argv)
{
	PmergeMe	sorter;

	try
	{
		sorter.parse(argc, argv);
		printBefore(argc, argv);
		sorter.sort();
		sorter.print();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}
