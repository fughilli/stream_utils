#include "stream_utils/bit_pipe.h"

#include "googletest/include/gtest/gtest.h"

namespace util {
namespace {

TEST(BitPipeTest, EmptyBitPipeHasZeroSize) {
  BitPipe<uint16_t> pipe(ShiftDirection::kLeft);
  EXPECT_EQ(pipe.size(), 0);
}

TEST(BitPipeTest, EmptyBitPipePopReturnsFalse) {
  uint16_t value = 0xdead;
  BitPipe<uint16_t> pipe(ShiftDirection::kLeft);
  EXPECT_EQ(pipe.size(), 0);
  EXPECT_FALSE(pipe.Pop(1, &value));
  EXPECT_EQ(pipe.size(), 0);
  EXPECT_EQ(value, 0xdead);
}

TEST(BitPipeTest, BitPipePopReturnsPushedBits) {
  BitPipe<uint16_t> pipe(ShiftDirection::kLeft);
  EXPECT_EQ(pipe.size(), 0);
  EXPECT_TRUE(pipe.Push(0xab, 8));
  EXPECT_EQ(pipe.size(), 8);

  uint16_t value = 0;
  EXPECT_TRUE(pipe.Pop(8, &value));
  EXPECT_EQ(pipe.size(), 0);
  EXPECT_EQ(value, 0xab);
}

TEST(BitPipeTest, BitPipePopSplitsPushedBits) {
  BitPipe<uint16_t> pipe(ShiftDirection::kLeft);
  EXPECT_EQ(pipe.size(), 0);
  EXPECT_TRUE(pipe.Push(0xcd, 8));
  EXPECT_EQ(pipe.size(), 8);

  uint16_t value = 0;
  EXPECT_TRUE(pipe.Pop(3, &value));
  EXPECT_EQ(pipe.size(), 5);
  EXPECT_EQ(value, 0x6);
  EXPECT_TRUE(pipe.Pop(5, &value));
  EXPECT_EQ(pipe.size(), 0);
  EXPECT_EQ(value, 0xd);
}

TEST(BitPipeTest, BitPipePopMoreBitsThanSizeReturnsFalse) {
  BitPipe<uint16_t> pipe(ShiftDirection::kLeft);
  EXPECT_TRUE(pipe.Push(0, 5));
  EXPECT_FALSE(pipe.Pop(6, nullptr));
}

TEST(BitPipeTest, BitPipeLeftOrdering) {
  BitPipe<uint16_t> pipe(ShiftDirection::kLeft);
  EXPECT_TRUE(pipe.Push(0xa, 4));
  EXPECT_TRUE(pipe.Push(0xb, 4));
  EXPECT_TRUE(pipe.Push(0xc, 4));
  uint16_t value = 0;
  EXPECT_TRUE(pipe.Pop(12, &value));
  EXPECT_EQ(value, 0xabc);
}

TEST(BitPipeTest, BitPipeRightOrdering) {
  BitPipe<uint16_t> pipe(ShiftDirection::kRight);
  EXPECT_TRUE(pipe.Push(0xa, 4));
  EXPECT_TRUE(pipe.Push(0xb, 4));
  EXPECT_TRUE(pipe.Push(0xc, 4));
  uint16_t value = 0;
  EXPECT_TRUE(pipe.Pop(12, &value));
  EXPECT_EQ(value, 0xcba);
}

}  // namespace
}  // namespace util
