#include "Bank.h"

bool Bank::CreateAccount(const char* name, uint16_t age, Account::AccountType type, std::string& accNo)
{
	if (m_AccCreatorValidator.ValidateUserInfo(name, age, type))
	{
		accNo = m_AccCreatorValidator.GenerateAccountNumber(++AccountsCount);
		m_vAccountsInBank.push_back(new Account(accNo, UserInfo(name, age), type));
		return true;
	}
	return false;
}

bool Bank::Login(const std::string& accNo, UserInfo& userDetails)
{
	for (auto acc : m_vAccountsInBank)
	{
		if (acc->GetAccountNumber() == accNo)
		{
			userDetails = acc->GetUserInfo();
			return true;
		}
	}
	return false;
}