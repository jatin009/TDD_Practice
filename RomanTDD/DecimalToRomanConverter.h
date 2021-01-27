#include <unordered_map>

enum DecimalPlace
{
	UNIT = 1,
	TENS = 10,
	HUNDRED = 100,
	THOUSAND = 1000
};

struct DigitsInNumber
{
	uint32_t un_Digit;
	uint32_t te_Digit;
	uint32_t hn_Digit;
	uint32_t th_Digit;

	DigitsInNumber(uint32_t number)
	{
		un_Digit = number % 10;
		te_Digit = (number / TENS) % 10;
		hn_Digit = (number / HUNDRED) % 10;
		th_Digit = (number / THOUSAND) % 10;
	}
};

class DecimalToRomanConverter
{
public:
	typedef std::unordered_map<uint32_t, const char> StandardRomansMap;

	DecimalToRomanConverter() :
		standardRomanNumeralsMap{
			{ 1, 'I' },{ 5, 'V' },{ 10, 'X' },{ 50, 'L' },{ 100, 'C' },{ 500, 'D' },{ 1000, 'M' }
	} {}

	std::string Convert(uint32_t decimalNumber)
	{
		if (IsConvertibleToSingleRomanLetter(decimalNumber))
			return GetRomanFromMap(decimalNumber);
		return FormRomanRepresentation(decimalNumber);
	}
private:
	std::string GetPlaceWiseRomanFor(const uint32_t decimalNumber, DecimalPlace place)
	{
		if (decimalNumber <= 3)
			return GetRomanFromMap(place, decimalNumber);
		else if (decimalNumber == 4)
			return GetRomanFromMap(place) + GetRomanFromMap(5 * place);
		else if (decimalNumber <= 8)
			return GetRomanFromMap(5 * place) + GetRomanFromMap(place, decimalNumber - 5);
		else
			return GetRomanFromMap(place) + GetRomanFromMap(10 * place);
	}
	std::string GetRomanFromMap(uint32_t decimalNumber, uint32_t times = 1)
	{
		return std::string(times, standardRomanNumeralsMap.at(decimalNumber));
	}
	std::string FormRomanRepresentation(const uint32_t decimalNumber)
	{
		DigitsInNumber num(decimalNumber);
		return GetPlaceWiseRomanFor(num.th_Digit, THOUSAND) + GetPlaceWiseRomanFor(num.hn_Digit, HUNDRED) + GetPlaceWiseRomanFor(num.te_Digit, TENS) + GetPlaceWiseRomanFor(num.un_Digit, UNIT);
	}
	bool IsConvertibleToSingleRomanLetter(const uint32_t decimalNumber)
	{
		return (standardRomanNumeralsMap.find(decimalNumber) != standardRomanNumeralsMap.end());
	}
	const StandardRomansMap standardRomanNumeralsMap;
};