#include "stream_utils/bits.h"

#include <iostream>

#include "googletest/include/gtest/gtest.h"

namespace util {
namespace {

TEST(BitsTest, AllOnesReturnsExpectedMask) {
  EXPECT_EQ(AllOnes<uint8_t>(), 0xff);
  EXPECT_EQ(AllOnes<uint16_t>(), 0xffff);
  EXPECT_EQ(AllOnes<uint32_t>(), 0xffffffff);
  EXPECT_EQ(AllOnes<uint64_t>(), 0xffffffffffffffff);
}

TEST(BitsTest, LargestSingleBitReturnsExpectedMask) {
  EXPECT_EQ(LargestSingleBit<uint8_t>(), 0x80);
  EXPECT_EQ(LargestSingleBit<uint16_t>(), 0x8000);
  EXPECT_EQ(LargestSingleBit<uint32_t>(), 0x80000000);
  EXPECT_EQ(LargestSingleBit<uint64_t>(), 0x8000000000000000);
}

TEST(BitsTest, BitRunGivesExpectedMask) {
  EXPECT_EQ(BitRun<uint8_t>(0), 0u);
  EXPECT_EQ(BitRun<uint16_t>(0), 0u);
  EXPECT_EQ(BitRun<uint32_t>(0), 0u);
  EXPECT_EQ(BitRun<uint64_t>(0), 0u);
  EXPECT_EQ(BitRun<uint8_t>(1), 0x1u);
  EXPECT_EQ(BitRun<uint8_t>(2), 0x3u);
  EXPECT_EQ(BitRun<uint8_t>(3), 0x7u);
  EXPECT_EQ(BitRun<uint8_t>(7), 0x7fu);
  EXPECT_EQ(BitRun<uint16_t>(12), 0x0fffu);
  EXPECT_EQ(BitRun<uint32_t>(17), 0x0001fffful);
  EXPECT_EQ(BitRun<uint32_t>(32), 0xfffffffful);
  EXPECT_EQ(BitRun<uint64_t>(64), 0xffffffffffffffffull);
}

TEST(BitsTest, MakeFieldGivesExpectedMask) {
  EXPECT_EQ(BitRun<uint32_t>(0) & 0xff, 0x0ul);
  EXPECT_EQ(BitRun<uint32_t>(1) & 0xff, 0x1ul);
  EXPECT_EQ(MakeField<uint32_t>(0xff, 0, 0), 0x00000000ul);
  EXPECT_EQ(MakeField<uint32_t>(0xbbaa, 12, 16), 0x0baa0000ul);
  EXPECT_EQ(MakeField<uint32_t>(0xff, 8, 21), 0x1fe00000ul);
  EXPECT_EQ(MakeField<uint32_t>(0xff, 5, 7), 0x00000f80ul);
}

TEST(BitsTest, OverwriteFieldGivesExpectedMask) {
  EXPECT_EQ(OverwriteField<uint16_t>(0xffff, 0x55, 7, 5), 0xfabfu);
  EXPECT_EQ(OverwriteField<uint16_t>(0xffff, 0x12, 8, 4), 0xf12fu);
}

TEST(BitsTest, GetFieldReturnsExpectedMask) {
  EXPECT_EQ(GetField<uint32_t>(0, 0, 0), 0x0u);
  EXPECT_EQ(GetField<uint32_t>(0xffffffff, 0, 0), 0x0u);
  EXPECT_EQ(GetField<uint32_t>(0xffffffff, 0, 8), 0x0u);
  EXPECT_EQ(GetField<uint32_t>(0x1234abcd, 12, 16), 0x234u);
  EXPECT_EQ(GetField<uint32_t>(0x1234abcd, 12, 16), 0x234u);
}

TEST(BitsTest, CountLeadingZeroesReturnsExpectedValue) {
  EXPECT_EQ(CountLeadingZeros<uint8_t>(0x00), 8);
  EXPECT_EQ(CountLeadingZeros<uint8_t>(0x80), 0);
  EXPECT_EQ(CountLeadingZeros<uint8_t>(0x0f), 4);
  EXPECT_EQ(CountLeadingZeros<uint8_t>(0x10), 3);

  EXPECT_EQ(CountLeadingZeros<uint64_t>(0x0000100000000000ull), 19);
  EXPECT_EQ(CountLeadingZeros<uint64_t>(0x0003ffffff000000ull), 14);
}

TEST(BitsTest, CountLeadingZeroesFieldReturnsExpectedValue) {
  EXPECT_EQ(CountLeadingZerosField<uint8_t>(0x00, 8, 0), 8);
  EXPECT_EQ(CountLeadingZerosField<uint8_t>(0x80, 4, 0), 4);
  EXPECT_EQ(CountLeadingZerosField<uint8_t>(0x0f, 5, 1), 2);
  EXPECT_EQ(CountLeadingZerosField<uint8_t>(0x10, 4, 4), 3);

  EXPECT_EQ(CountLeadingZerosField<uint64_t>(0x0000100000000000ull, 64, 0), 19);
  EXPECT_EQ(CountLeadingZerosField<uint64_t>(0x0003ffffff000000ull, 64, 0), 14);
}

TEST(BitsTest, CountTrailingOnesFieldReturnsExpectedValue) {
  EXPECT_EQ(CountTrailingOnesField<uint16_t>(0x0000, 16, 0), 0);
  EXPECT_EQ(CountTrailingOnesField<uint16_t>(0x00FF, 16, 0), 8);
  EXPECT_EQ(CountTrailingOnesField<uint16_t>(0xFC3F, 8, 2), 4);
}

}  // namespace
}  // namespace util
