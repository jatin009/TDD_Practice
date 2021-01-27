#ifndef Bank_H
#define Bank_H

#include <string>
#include <unordered_map>

struct UserInfo
{
	std::string _name;
	uint16_t _age;

	UserInfo() = default;
	UserInfo(const std::string n, const uint16_t age)
		: _name(n), _age(age) {}
};

class Account
{

public:
	enum AccountType
	{
		SAVINGS,
		CURRENT,
		NONE
	};

	Account(const std::string& accNo, const UserInfo& user, const AccountType type)
		: m_AccountNumber(accNo)
		, m_User(user)
		, m_Type(type)
		, m_Balance(0U) {}

	std::string GetAccountNumber() const { return m_AccountNumber; }
	UserInfo GetUserInfo() const { return m_User; }
	AccountType GetAccountType() const { return m_Type; }
	uint32_t GetBalance() const { return m_Balance; }
	void CreditAmount(const uint32_t & cr) { m_Balance += cr; }
	bool DebitAmount(const uint32_t & db)
	{
		bool validTransaction = m_Balance > db;
		if (validTransaction)
			m_Balance -= db;
		return validTransaction;
	}

private:

	std::string m_AccountNumber;
	UserInfo m_User;
	AccountType m_Type;
	uint32_t m_Balance;
};

class AccountCreationHelper
{
public:

	std::string GenerateAccountNumber(size_t accCount)
	{
		std::string acSerial = std::to_string(accCount);
		return BranchCode + CurrentYear + std::string(IdentifierLength - acSerial.length(), '0') + acSerial;
	}
	bool ValidateUserInfo(const char* name, uint16_t age, Account::AccountType type)
	{
		return strlen(name) > 0 && age > 18 && type != Account::NONE;
	}

private:
	const char* BranchCode = "9014";
	std::string CurrentYear = "2020";
	const size_t IdentifierLength = 6;

};

class Bank
{
public:

	bool CreateAccount(const char* name, uint16_t age, Account::AccountType type, std::string& accNo);
	bool Login(const std::string& accNo, UserInfo& userDetails);

private:

	size_t AccountsCount = 0;
	AccountCreationHelper m_AccCreatorValidator;
	std::vector<Account*> m_vAccountsInBank;

};

#endif //Bank_H