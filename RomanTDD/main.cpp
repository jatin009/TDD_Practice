#include "gmock/gmock.h"
#include "DecimalToRomanConverter.h"

using namespace testing;

int main(int argc, char** argv)
{
	InitGoogleMock(&argc, argv);
	RUN_ALL_TESTS();

	char ch;
	uint32_t number;
	DecimalToRomanConverter converter;
	do
	{
		std::cout << "\nEnter a decimal number from 1-3999 for roman conversion: ";
		std::cin >> number;

		std::cout << converter.Convert(number);
		std::cout << "\n\nContinue ? ";
		std::cin >> ch;
	} while (ch != 'n');
}