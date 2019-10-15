#include <gtest/gtest.h>
#include "deque.h"

TEST(Deque, Empty) {
  Deque<int> dq;

  EXPECT_EQ(dq.Empty(), true);
  EXPECT_EQ(dq.Size(), 0);
  EXPECT_THROW(dq.PopFront(), std::exception);
}

TEST(Deque, DoubleInsertionBack) {
  Deque<int> dq;

  dq.PushBack(23);
  dq.PushBack(42);
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 2);
  EXPECT_EQ(dq[0], 23);
  EXPECT_EQ(dq[1], 42);
  EXPECT_EQ(dq.Back(), 42);
}

TEST(Deque, DoubleInsertionBackFront) {
  Deque<int> dq;

  dq.PushBack(23);
  dq.PushFront(42);
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 2);
  EXPECT_EQ(dq[0], 42);
  EXPECT_EQ(dq[1], 23);
  EXPECT_EQ(dq.Back(), 23);
}

TEST(Deque, DoublePushBackPushFrontPopBack) {
  Deque<int> dq;

  dq.PushBack(100);
  dq.PushBack(20);
  dq.PushFront(30);
  dq.PopBack();
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 2);
  EXPECT_EQ(dq[0], 30);
  EXPECT_EQ(dq[1], 100);
  EXPECT_EQ(dq.Back(), 100);
}

TEST(Deque, WrapTailAround) {
  Deque<int> dq;

  dq.PushBack(23);
  dq.PushBack(42);
  dq.PopFront();
  dq.PushBack(1);
  dq.PushBack(2);
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 3);
  EXPECT_EQ(dq[0], 42);
  EXPECT_EQ(dq[1], 1);
  EXPECT_EQ(dq.Back(), 2);
}

TEST(Deque, Shrink) {
  Deque<int> dq;

  dq.PushBack(23);
  dq.PushBack(42);
  dq.PushBack(1);
  EXPECT_EQ(dq.Size(), 3);
  dq.PopBack();
  dq.ShrinkToFit();
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 2);
}

TEST(Deque, Errors) {
  Deque<int> dq;

  EXPECT_THROW(dq.Front(), std::out_of_range);
  EXPECT_THROW(dq.Back(), std::out_of_range);
  EXPECT_THROW(dq.PopFront(), std::out_of_range);
  EXPECT_THROW(dq.PopBack(), std::out_of_range);
  EXPECT_THROW(dq[1], std::out_of_range);
  EXPECT_THROW(dq[-2], std::out_of_range);
}

TEST(Deque, Clear) {
  Deque<int> dq;

  dq.PushBack(23);
  dq.PushBack(42);
  dq.Clear();
  EXPECT_EQ(dq.Size(), 0);
  EXPECT_THROW(dq[0], std::out_of_range);
}

TEST(Deque, WrapHeadAround) {
  Deque<int> dq;

  dq.PushBack(23);
  dq.PushFront(18);
  dq.PushFront(32);
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 3);
  EXPECT_EQ(dq[0], 32);
  EXPECT_EQ(dq[1], 18);
  EXPECT_EQ(dq.Back(), 23);
}

TEST(Deque, Push4AndFront) {
  Deque<int> dq;

  dq.PushBack(23);
  dq.PushBack(18);
  dq.PushBack(32);
  dq.PushBack(10);
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 4);
  EXPECT_EQ(dq[0], 23);
  EXPECT_EQ(dq[1], 18);
  EXPECT_EQ(dq[2], 32);
  EXPECT_EQ(dq[3], 10);
  EXPECT_EQ(dq.Front(), 23);
  EXPECT_EQ(dq.Back(), 10);
}

TEST(Deque, AltFrontAndBackPushesTestFrontAndBack) {
  Deque<int> dq;

  dq.PushFront(23);
  dq.PushBack(18);
  dq.PushFront(32);
  dq.PushBack(10);
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 4);
  EXPECT_EQ(dq[0], 32);
  EXPECT_EQ(dq[1], 23);
  EXPECT_EQ(dq[2], 18);
  EXPECT_EQ(dq[3], 10);
  EXPECT_EQ(dq.Front(), 32);
  EXPECT_EQ(dq.Back(), 10);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

