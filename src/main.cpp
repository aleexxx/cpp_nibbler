#include "Nibbler.hpp"
#include "Usage_error.hpp"
#include "Graphic_error.hpp"

int	main(int ac, char **av)
{
	int a;
	int b;
	std::string error;

	try
	{
		if (ac == 4)
		{
			if ((a = atoi(av[1])) == 0)
			{
				error = USAGE;
				error += "\nWidth : int()";
				throw Usage_error(error);
			}
			if ((b = atoi(av[2])) == 0)
			{
				error = USAGE;
				error += "\nHeight : int()";
				throw Usage_error(error);
			}
			if (a < MAX_SIZE_X && a > MIN_SIZE_X && b > MIN_SIZE_X && b < MAX_SIZE_Y)
			{
				nibbler nibb = nibbler(a, b, av[3]);
				nibb.gameloop();
			}
			else
			{
				error = USAGE;
				error += "\nMin-Max width : " + std::to_string(MIN_SIZE_X) + "-" + std::to_string(MAX_SIZE_X) +
										  "\nMin-Max height : " + std::to_string(MIN_SIZE_X) + "-" + std::to_string(MAX_SIZE_Y);
				throw Usage_error(error);
			}
		}
		else
			throw Usage_error("Usage: ./nibbler width height lib.so");
	}
	catch (Usage_error error)
	{
		std::cerr << error.what() << std::endl;
	}
	catch (Graphic_error error)
	{
		std::cerr << "Graphic error " << error.what() << std::endl;
	}
	return (0);
}
