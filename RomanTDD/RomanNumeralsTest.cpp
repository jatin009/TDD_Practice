#include "gmock/gmock.h"
#include "DecimalToRomanConverter.h"

using namespace testing;

class ARomanConverter: public Test
{
public:
	DecimalToRomanConverter converter;

	void ASSERT_MULTIPLES_OF_1_UPTO_3()
	{
		ASSERT_THAT(converter.Convert(1), Eq("I"));
		ASSERT_THAT(converter.Convert(2), Eq("II"));
		ASSERT_THAT(converter.Convert(3), Eq("III"));
	}

	void ASSERT_SINGLE_LETTER_ROMAN()
	{
		ASSERT_THAT(converter.Convert(1), Eq("I"));
		ASSERT_THAT(converter.Convert(5), Eq("V"));
		ASSERT_THAT(converter.Convert(10), Eq("X"));
		ASSERT_THAT(converter.Convert(50), Eq("L"));
		ASSERT_THAT(converter.Convert(100), Eq("C"));
		ASSERT_THAT(converter.Convert(500), Eq("D"));
		ASSERT_THAT(converter.Convert(1000), Eq("M"));
	}
};

TEST_F(ARomanConverter, ReturnsSingleLetterRomanForReferenceNumbers)
{
	ASSERT_SINGLE_LETTER_ROMAN();
}

TEST_F(ARomanConverter, ReturnsAsMany_I_AsMultipleOfOneUpto3)
{
	ASSERT_MULTIPLES_OF_1_UPTO_3();
}

TEST_F(ARomanConverter, DoesNotReturnFour_I_ForValue4)
{
	ASSERT_THAT(converter.Convert(4), Ne("IIII"));
}

TEST_F(ARomanConverter, Returns_IV_ForValue4)
{
	ASSERT_THAT(converter.Convert(4), Eq("IV"));
}

TEST_F(ARomanConverter, Returns_I_AppendedTo_V_ForNumberUpto8)
{
	ASSERT_THAT(converter.Convert(6), Eq("VI"));
	ASSERT_THAT(converter.Convert(7), Eq("VII"));
	ASSERT_THAT(converter.Convert(8), Eq("VIII"));
}

TEST_F(ARomanConverter, DoesNotReturnFour_I_AppendedTo_V_ForValue9)
{
	ASSERT_THAT(converter.Convert(9), Ne("VIIII"));
}

TEST_F(ARomanConverter, Returns_IX_ForValue9)
{
	ASSERT_THAT(converter.Convert(9), Eq("IX"));
}

TEST_F(ARomanConverter, Returns_X_PrependedToUnitDigitsForGreaterThan10)
{
	ASSERT_THAT(converter.Convert(11), Eq("XI"));
	ASSERT_THAT(converter.Convert(17), Eq("XVII"));
	ASSERT_THAT(converter.Convert(39), Eq("XXXIX"));
}

TEST_F(ARomanConverter, DoesNotReturnFour_X_For40s)
{
	ASSERT_THAT(converter.Convert(42), Ne("XXXXII"));
}

TEST_F(ARomanConverter, Returns_X_PrependedTo_L_For40s)
{
	ASSERT_THAT(converter.Convert(47), Eq("XLVII"));
}

TEST_F(ARomanConverter, Returns_L_AppendedWith_X_Upto80s)
{
	ASSERT_THAT(converter.Convert(76), Eq("LXXVI"));
	ASSERT_THAT(converter.Convert(85), Eq("LXXXV"));
}

TEST_F(ARomanConverter, Returns_X_PrependedTo_C_For90s)
{
	ASSERT_THAT(converter.Convert(99), Eq("XCIX"));
}

TEST_F(ARomanConverter, Returns_C_PrependedToUnitDigitsFor100s)
{
	ASSERT_THAT(converter.Convert(105), Eq("CV"));
}

TEST_F(ARomanConverter, RandomTest)
{
	ASSERT_THAT(converter.Convert(146), Eq("CXLVI"));
	ASSERT_THAT(converter.Convert(260), Eq("CCLX"));
	ASSERT_THAT(converter.Convert(350), Eq("CCCL"));
	ASSERT_THAT(converter.Convert(380), Eq("CCCLXXX"));
	ASSERT_THAT(converter.Convert(420), Eq("CDXX"));
	ASSERT_THAT(converter.Convert(642), Eq("DCXLII"));
	ASSERT_THAT(converter.Convert(2459), Eq("MMCDLIX"));
	ASSERT_THAT(converter.Convert(2000), Eq("MM"));
	ASSERT_THAT(converter.Convert(3999), Eq("MMMCMXCIX"));
}