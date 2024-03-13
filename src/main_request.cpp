#include "Request.hpp"

int main (int ac, char **av)
{
	(void)ac;
	std::string httpRequest = av[1];
	Request newRequest(httpRequest);

	std::cout << "Ok" << std::endl;

	return (0);
}