#include "gmock/gmock.h"
#include <unordered_map>
#include "Bank.h"

using namespace testing;

std::string accountNumber;

class AnAccount : public Test
{
public:
	Account *a;
	void SetUp() override
	{
		a = new Account("90142020213002", UserInfo("Shobhit", 26), Account::CURRENT);
	}
	void TearDown() override
	{
		delete a;
		a = nullptr;
	}
};

class ABank : public Test
{
public:
	Bank b;
	void CreateAccount(const char* name, uint16_t ag, Account::AccountType type, std::string& accno)
	{
		b.CreateAccount(name, ag, type, accno);
	}
};

TEST_F(ABank, CannotCreateAccountWithEmptyName)
{
	ASSERT_FALSE(b.CreateAccount("", 24, Account::SAVINGS, accountNumber));
}

TEST_F(ABank, CannotCreateAccountForMinor)
{
	ASSERT_FALSE(b.CreateAccount("XYZ", 15, Account::CURRENT, accountNumber));
}

TEST_F(ABank, CannotCreateAccountIfAccTypeNone)
{
	ASSERT_FALSE(b.CreateAccount("XYZ", 26, Account::NONE, accountNumber));
}

TEST_F(ABank, GeneratesAccNoWith14Digits)
{
	b.CreateAccount("Mohit", 28, Account::SAVINGS, accountNumber);
	ASSERT_THAT(accountNumber.length(), Eq(14));
}

TEST_F(ABank, GeneratesAccNoBeginningWith9014)
{
	b.CreateAccount("Mohit", 28, Account::SAVINGS, accountNumber);
	ASSERT_THAT(accountNumber, StartsWith("9014"));
}

TEST_F(ABank, GeneratesAccNoWithSecondNibbleAsTheCurrentYear)
{
	b.CreateAccount("Mohit", 28, Account::SAVINGS, accountNumber);
	ASSERT_THAT(accountNumber.substr(4), StartsWith("2020"));
}

TEST_F(ABank, GeneratesAccNoWithLast6DigitsForNewCustomerCount)
{
	b.CreateAccount("Mohit", 28, Account::SAVINGS, accountNumber);
	ASSERT_THAT(std::stoi(accountNumber.substr(8)) , Eq(1));
}

TEST_F(ABank, AssignsIncrementingAccNoToNewCustomer)
{
	CreateAccount("Shobhit", 28, Account::SAVINGS, accountNumber);
	std::string accNo2;
	b.CreateAccount("Mohit", 28, Account::SAVINGS, accNo2);
	ASSERT_THAT(std::stoi(accountNumber.substr(8)), Eq(1));
	ASSERT_THAT(std::stoi(accNo2.substr(8)), Eq(2));
}

TEST_F(ABank, DoesNotAllowLoginWithIncorrectAccNo)
{
	CreateAccount("Mohit", 28, Account::SAVINGS, accountNumber);
	UserInfo u;
	ASSERT_FALSE(b.Login(accountNumber.substr(1), u));
}

TEST_F(ABank, AllowsLoginWithCorrectAccNoOnly)
{
	CreateAccount("Mohit", 28, Account::SAVINGS, accountNumber);
	UserInfo u;
	ASSERT_TRUE(b.Login(accountNumber, u));
}

TEST_F(ABank, RetrievesCorrectUserInfoOnLogin)
{	
	CreateAccount("Mohit", 28, Account::SAVINGS, accountNumber);
	UserInfo u;
	b.Login(accountNumber, u);
	EXPECT_THAT(u._name, Eq("Mohit"));
	EXPECT_THAT(u._age, Eq(28));
}

TEST_F(AnAccount, HasBalanceRaisedByAmountCredited)
{
	a->CreditAmount(100u);
	ASSERT_THAT(a->GetBalance(), Eq(100u));
}

TEST_F(AnAccount, HasBalanceDebitedByAmountWithdrawn)
{
	a->CreditAmount(100u);
	a->DebitAmount(50u);
	ASSERT_THAT(a->GetBalance(), Eq(50u));
}

TEST_F(AnAccount, DoesNotAllowWithdrawalofAmountGreaterThanBalance)
{
	a->CreditAmount(100u);
	ASSERT_FALSE(a->DebitAmount(200u) == true);
}