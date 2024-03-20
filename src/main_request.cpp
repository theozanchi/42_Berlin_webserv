#include "Request.hpp"

int main (int ac, char **av)
{
//	if (ac < 2)
//	{
//		std::cout << "No request." << std::endl;
//		return (0);
//	}
	(void) ac;
	if (av[1])
	{
		std::string httpRequest = av[1];
		try {
			Request newRequest(httpRequest);
			std::cout << newRequest;
		}

		catch (std::exception &e)
		{
			std::cout<< RED << e.what() << RES << std::endl;
		}
	}

	return (0);
}