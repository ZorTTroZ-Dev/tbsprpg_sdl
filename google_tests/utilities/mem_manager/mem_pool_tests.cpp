/**
 * @file mem_pool_tests.cpp
 */

#include <gtest/gtest.h>
extern "C" {
#include "../../../utilities/mem_manager.h"
#include "../../../utilities/mem_manager/mem_pool.h"
}

TEST(MemPoolTestSuiteInit, Initialization)
{
	struct mmgr_pool_cfg pool_cfg {};
	uint32_t sizes[] = { 4 };
	uint32_t counts[] = { 3 };
	pool_cfg.num_pools = 1;
	pool_cfg.chunk_sizes = sizes;
	pool_cfg.chunk_counts = counts;
	EXPECT_EQ(mmgr_pool_open(&pool_cfg), 0);
	mmgr_pool_close();
}

TEST(MemPoolTestSuiteInit, InitializationNoPools)
{
	struct mmgr_pool_cfg pool_cfg {};
	uint32_t sizes[] = { 4 };
	uint32_t counts[] = { 3 };
	pool_cfg.num_pools = 0;
	pool_cfg.chunk_sizes = sizes;
	pool_cfg.chunk_counts = counts;
	EXPECT_EQ(mmgr_pool_open(&pool_cfg), 0);
	mmgr_pool_close();
}

TEST(MemPoolTestSuiteInit, InitializationNULLConfig)
{
	EXPECT_EQ(mmgr_pool_open(nullptr), 1);
	mmgr_pool_close();
}

class MemPoolTestSuite : public testing::Test {
    protected:
	void SetUp() override
	{
		this->pool_cfg = static_cast<struct mmgr_pool_cfg *>(
			malloc(sizeof(struct mmgr_pool_cfg)));
	}

	void TearDown() override
	{
		free(this->pool_cfg);
		this->pool_cfg = nullptr;
	}

	mmgr_pool_cfg *pool_cfg = nullptr;
};

TEST_F(MemPoolTestSuite, AllocateMemory)
{
	EXPECT_NE(pool_cfg, nullptr);
}
