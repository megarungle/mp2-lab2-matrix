#include "utmatrix.h"

#include "gtest.h"

TEST(TVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, throws_when_create_vector_with_negative_startindex)
{
	ASSERT_ANY_THROW(TVector<int> v(5, -2));
}

TEST(TVector, can_create_copied_vector)
{
	TVector<int> v(10);

	ASSERT_NO_THROW(TVector<int> v1(v));
}

TEST(TVector, copied_vector_is_equal_to_source_one)
{
	int val = 10;
	TVector<int> v1(val);
	for (int i = 0; i < val; ++i)
	{
		v1[i] = i + 1;
	}
	TVector<int> v2(v1);

	EXPECT_EQ(v1, v2);
}

TEST(TVector, copied_vector_has_its_own_memory)
{
	int val = 10;
	TVector<int> v1(val);
	for (int i = 0; i < val; ++i)
	{
		v1[i] = i + 1;
	}
	TVector<int> v2(v1);
	v2[0] = val;

	EXPECT_NE(v1, v2);
}

TEST(TVector, can_get_size)
{
	TVector<int> v(4);

	EXPECT_EQ(4, v.GetSize());
}

TEST(TVector, can_get_start_index)
{
	TVector<int> v(4, 2);

	EXPECT_EQ(2, v.GetStartIndex());
}

TEST(TVector, can_set_and_get_element)
{
	TVector<int> v(4);
	v[0] = 4;

	EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index)
{
	TVector<int> v(5);

	ASSERT_ANY_THROW(v[-1] = -1);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
	int val = 10;
	TVector<int> v(val);

	ASSERT_ANY_THROW(v[val] = val);
}

TEST(TVector, can_assign_vector_to_itself)
{
	int val = 5;
	TVector<int> v(val);
	for (int i = 0; i < val; ++i)
	{
		v[i] = i + 1;
	}

	ASSERT_NO_THROW(v = v);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
	int val = 5;
	TVector<int> v1(val);
	TVector<int> v2(val);
	for (int i = 0; i < val; ++i)
	{
		v1[i] = i + 1;
	}
	v2 = v1;

	EXPECT_EQ(v1, v2);
}

TEST(TVector, assign_operator_change_vector_size)
{
	int val = 5;
	TVector<int> v1(val);
	TVector<int> v2(2 * val);
	for (int i = 0; i < v2.GetSize(); ++i)
	{
		v2[i] = i + 1;
	}
	v1 = v2;

	EXPECT_EQ(v2.GetSize(), v1.GetSize());
}

TEST(TVector, can_assign_vectors_of_different_size)
{
	int val = 5;
	TVector<int> v1(val);
	TVector<int> v2(2 * val);
	for (int i = 0; i < v2.GetSize(); ++i)
	{
		v2[i] = i + 1;
	}

	ASSERT_NO_THROW(v1 = v2);
}

TEST(TVector, compare_equal_vectors_return_true)
{
	int val = 5;
	TVector<int> v1(val);
	TVector<int> v2(val);
	for (int i = 0; i < val; ++i)
	{
		v1[i] = i + 1;
		v2[i] = i + 1;
	}

	EXPECT_TRUE(v1 == v2);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
	int val = 5;
	TVector<int> v1(val);
	for (int i = 0; i < val; ++i)
	{
		v1[i] = i + 1;
	}

	EXPECT_TRUE(v1 == v1);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
	int val = 5;
	TVector<int> v1(val);
	TVector<int> v2(2 * val);
	for (int i = 0; i < val; ++i)
	{
		v1[i] = i + 1;
	}
	for (int i = 0; i < 2 * val; ++i)
	{
		v2[i] = i + 1;
	}

	EXPECT_TRUE(v1 != v2);
}

TEST(TVector, can_add_scalar_to_vector)
{
	int val = 5;
	TVector<int> v(val);
	for (int i = 0; i < val; ++i)
	{
		v[i] = i + 1;
	}

	ASSERT_NO_THROW(v = v + val);
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	int val = 5;
	TVector<int> v(val);
	for (int i = 0; i < val; ++i)
	{
		v[i] = i + 1;
	}

	ASSERT_NO_THROW(v = v - val);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
	int val = 5;
	TVector<int> v(val);
	for (int i = 0; i < val; ++i)
	{
		v[i] = i + 1;
	}

	ASSERT_NO_THROW(v = v * val);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
	int val = 5;
	TVector<int> v1(val);
	TVector<int> v2(val);
	for (int i = 0; i < val; ++i)
	{
		v1[i] = i + 1;
		v2[i] = i + 2;
	}

	ASSERT_NO_THROW(v1 = v1 + v2);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	int val = 5;
	TVector<int> v1(val);
	TVector<int> v2(2 * val);
	for (int i = 0; i < val; ++i)
	{
		v1[i] = i + 1;
	}
	for (int i = 0; i < 2 * val; ++i)
	{
		v2[i] = i + 1;
	}

	ASSERT_ANY_THROW(v1 = v1 + v2);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
	int val = 5;
	TVector<int> v1(val);
	TVector<int> v2(val);
	for (int i = 0; i < val; ++i)
	{
		v1[i] = i + 1;
		v2[i] = i + 2;
	}

	ASSERT_NO_THROW(v1 = v1 - v2);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
	int val = 5;
	TVector<int> v1(val);
	TVector<int> v2(2 * val);
	for (int i = 0; i < val; ++i)
	{
		v1[i] = i + 1;
	}
	for (int i = 0; i < 2 * val; ++i)
	{
		v2[i] = i + 1;
	}

	ASSERT_ANY_THROW(v1 = v1 - v2);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
	int val = 5;
	TVector<int> v1(val);
	TVector<int> v2(val);
	for (int i = 0; i < val; ++i)
	{
		v1[i] = i + 1;
		v2[i] = i + 2;
	}

	ASSERT_NO_THROW(v1 = v1 * v2);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	int val = 5;
	TVector<int> v1(val);
	TVector<int> v2(2 * val);
	for (int i = 0; i < val; ++i)
	{
		v1[i] = i + 1;
	}
	for (int i = 0; i < 2 * val; ++i)
	{
		v2[i] = i + 1;
	}

	ASSERT_ANY_THROW(v1 = v1 * v2);
}

// my tests:

TEST(TVector, can_add_three_vectors_with_equal_size_MY_TEST)
{
	int val = 5;
	TVector<int> v1(val);
	TVector<int> v2(val);
	TVector<int> v3(val);
	TVector<int> v(val);
	for (int i = 0; i < val; ++i)
	{
		v1[i] = 1;
		v2[i] = 2;
		v3[i] = 3;
		v[i] = 6;
	}
	v1 = v1 + v2 + v3;

	EXPECT_EQ(v1, v);
}

TEST(TVector, can_subtract_three_vectors_with_equal_size_MY_TEST)
{
	int val = 5;
	TVector<int> v1(val);
	TVector<int> v2(val);
	TVector<int> v3(val);
	TVector<int> v(val);
	for (int i = 0; i < val; ++i)
	{
		v1[i] = 1;
		v2[i] = 2;
		v3[i] = 3;
		v[i] = -4;
	}
	v1 = v1 - v2 - v3;

	EXPECT_EQ(v1, v);
}

TEST(TVector, can_assign_three_vectors_of_equal_size_MY_TEST)
{
	int val = 5;
	TVector<int> v1(val);
	TVector<int> v2(val);
	TVector<int> v3(val);
	for (int i = 0; i < val; ++i)
	{
		v1[i] = 1;
		v2[i] = 2;
		v3[i] = 3;
	}
	v1 = v2 = v3;

	EXPECT_EQ(v1, v2);
	EXPECT_EQ(v2, v3);
}

TEST(TVector, compare_vectors_with_equal_size_and_different_startindex_return_false_MY_TEST)
{
	int val = 5;
	TVector<int> v1(val, 0);
	TVector<int> v2(val, 1);
	for (int i = 0; i < val; ++i)
	{
		v1[i] = i + 1;
		v2[i+1] = i + 1;
	}

	EXPECT_FALSE(v1 == v2);
}

TEST(TVector, cant_create_vector_with_too_large_startindex_MY_TEST)
{
	ASSERT_ANY_THROW(TVector<int> v(5, MAX_VECTOR_SIZE + 1));
}

TEST(TVector, cant_set_and_get_element_with_pos_less_startindex_MY_TEST)
{
	TVector<int> v(5, 2);

	ASSERT_ANY_THROW(v[0] = 0);
	ASSERT_ANY_THROW(int elem = v[1]);
}

TEST(TVector, can_create_null_vector_MY_TEST)
{
	ASSERT_NO_THROW(TVector<int> v(0));
}