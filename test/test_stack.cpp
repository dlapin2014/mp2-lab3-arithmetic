// тесты для стека

#include "stack.h"
#include <gtest.h>



TEST(TStack, empty_stack_has_null_size)
{
	const int size = 0;
	TStack<int> a;

	EXPECT_EQ(size, a.GetSize());
}


TEST(TStack, stack_GetSize_is_true)
{
	const int size = 2;
	TStack<int> a;
	a.push(size);
	a.push(size);

	EXPECT_EQ(size, a.GetSize());
}





TEST(TStack, stack_create_works)
{
	ASSERT_NO_THROW(TStack<int> a);
}

TEST(TStack, stack_push_works)
{
	TStack<int> a;

	ASSERT_NO_THROW(a.push(2));
}


TEST(TStack, stack_push_works_correctly)
{
	TStack<int> a;
	a.push(2);

	EXPECT_EQ(2,a.top());
}

TEST(TStack, stack_empty_method_works_correctly)
{
	TStack<int> a;
	

	EXPECT_EQ(1, (a.empty()==true));
}

TEST(TStack, stack_copy_constructor_works_correctly)
{
	TStack<int> a;
	a.push(2);
	a.push(3);
	TStack<int> b(a);
	bool t = true;
	while (!a.empty()) {
		t = (a.top() == b.top());
		a.pop(); b.pop();
	}


	EXPECT_EQ(1, (a.empty() == true));
}


TEST(TStack, clear_works_correctly)
{
	TStack<int> a;
	a.push(2);
	a.push(3);
	a.clear();
	EXPECT_EQ(0, a.GetSize());
}

TEST(TStack, pop_works_correctly)
{
	TStack<int> a;
	a.push(2);
	a.push(3);
	a.pop();
	EXPECT_EQ(a.top(), 2);
}


TEST(TStack, pop_empty_array_throws_exception)
{
	TStack<int> a;
	ASSERT_ANY_THROW(a.pop());
}





