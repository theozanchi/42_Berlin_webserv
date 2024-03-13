#include "Request.hpp"

int main (int ac, char **av)
{
//	if (ac < 2)
//	{
//		std::cout << "No request." << std::endl;
//		return (0);
//	}
	(void) ac;
	std::string httpRequest = av[1];
	try {
		Request newRequest(httpRequest);

		std::cout << "OK" << std::endl;
	}

	catch (std::exception &e)
	{
		std::cout << "KO " << e.what() << std::endl;
	}

	return (0);
}