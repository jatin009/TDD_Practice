#include "gmock/gmock.h"

class Stack 
{
private:
	size_t m_Size = 0;
	int m_Arr[100];
public:
	size_t Size()
	{
		return m_Size;
	}
	void Push(int elem)
	{
		m_Arr[m_Size] = elem;
		m_Size += 1;
	}
	void Pop()
	{
		if (m_Size > 0)
			m_Size -= 1;
	}
	int Top()
	{
		return m_Arr[m_Size-1];
	}
};

using namespace testing;

class StackImpl : public Test
{
public:
	Stack st;
};

class TwoElementStack: public Test
{
public:
	Stack st;
	void SetUp() override
	{
		st.Push(45);
		st.Push(3);
	}
};

TEST_F(StackImpl, InitializesEmptyStack)
{
	ASSERT_THAT(st.Size(), Eq(0));
}

TEST_F(StackImpl, HasSizeOneOnSinglePush)
{
	st.Push(4);
	ASSERT_THAT(st.Size(), Eq(1));
}

TEST_F(StackImpl, HasSizeZeroOnSinglePushSinglePop)
{
	st.Push(4);
	st.Pop();
	ASSERT_THAT(st.Size(), Eq(0));
}

TEST_F(StackImpl, HasStillZeroSizeOnPoppingEmptyStack)
{
	st.Pop();
	ASSERT_THAT(st.Size(), Eq(0));
}

TEST_F(TwoElementStack, HasSecondElementOnTop)
{
	ASSERT_THAT(st.Top(), Eq(3));
}

TEST_F(TwoElementStack, RemovesTheSecondElementFromTopOnPop)
{
	st.Pop();
	ASSERT_THAT(st.Top(), Ne(3));
}

TEST_F(TwoElementStack, HasFirstElementOnTopOnSinglePop)
{
	st.Pop();
	ASSERT_THAT(st.Top(), Eq(45));
}

TEST_F(TwoElementStack, HasSizeOneAfterOnePop)
{
	st.Pop();
	ASSERT_THAT(st.Size(), Eq(1));
}