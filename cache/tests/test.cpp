// Copyright 2021 Masterluch <atim2203@gmail.com>

#include <gtest/gtest.h>
#include <header.hpp>

TEST(Example, EmptyTest)
{
    EXPECT_TRUE(true);
}

TEST(start_experiment, data_is_missing)
{
    ASSERT_THROW(Experiment(std::vector<size_t>{}), std::invalid_argument);
}

TEST(start_experimrnt, size_of_buffer_is_zero)
{
    ASSERT_THROW(Experiment(std::vector<size_t>{0}), std::invalid_argument);
}