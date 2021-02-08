#include "stream_utils/base64_stream.h"

#include <iostream>

#include "googletest/include/gtest/gtest.h"

namespace util {
namespace {

class StringStream : public Stream<uint8_t> {
 public:
  bool Write(const uint8_t& token) final {
    buffer_ += token;
    return true;
  }

  void Clear() { buffer_.clear(); }
  const std::string& buffer() const { return buffer_; }

 private:
  std::string buffer_;
};

TEST(Base64StreamTest, NoWrites) {
  StringStream ss;
  Base64EncodeStream b64s;
  b64s.RegisterDownstream(&ss);

  EXPECT_TRUE(ss.buffer().empty());
  EXPECT_TRUE(b64s.Flush());
  EXPECT_TRUE(ss.buffer().empty());
}

TEST(Base64StreamTest, EvenBytesWrite) {
  StringStream ss;
  Base64EncodeStream b64s;
  b64s.RegisterDownstream(&ss);

  const uint8_t message[] = "abc";
  EXPECT_TRUE(b64s.WriteBuffer(message, 3));
  EXPECT_EQ(ss.buffer(), "YWJj");
}

TEST(Base64StreamTest, OddBytesWrite) {
  StringStream ss;
  Base64EncodeStream b64s;
  b64s.RegisterDownstream(&ss);

  const uint8_t message[] = "ab";
  EXPECT_TRUE(b64s.WriteBuffer(message, 2));
  EXPECT_EQ(ss.buffer(), "YW");
  EXPECT_TRUE(b64s.Flush());
  EXPECT_EQ(ss.buffer(), "YWI=");

  ss.Clear();
  const uint8_t message_longer[] = {0x01, 0x02, 0x03, 0xff};
  EXPECT_TRUE(b64s.WriteBuffer(message_longer, 4));
  EXPECT_TRUE(b64s.Flush());
  EXPECT_EQ(ss.buffer(), "AQID/w==");
}

}  // namespace
}  // namespace util
