/**
 * @file mem_pool_tests.cpp
 */

#include <gtest/gtest.h>
extern "C" {
#include "../../../utilities/mem_manager.h"
}

TEST(MemPoolTests, Initialization)
{
	// Expect two strings not to be equal.
	// EXPECT_STRNE("hello", "world");
	// Expect equality.
	EXPECT_EQ(mmgr_pool_init(), 8);
}
