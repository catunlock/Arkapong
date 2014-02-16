#include "angles.h"

void testRadians()
{
	print_sinus_cosinus(M_PI_2);
	print_sinus_cosinus(M_PI);
	print_sinus_cosinus(3 * M_PI / 2);
	print_sinus_cosinus(2 * M_PI);
}


void print_sinus_cosinus(double rads)
{
	std::cout << "Radians: " << rads << "\t\t cos: " << cos(rads) << "\t\t sin: " << sin(rads) << std::endl;
}
