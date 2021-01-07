#include "TemplateBuffer.h"
#include "gtest/gtest.h"

namespace
{
  class Template_BufferTest : public ::testing::Test {
  protected:
    using TestBuffer = Buffer<>;

    Template_BufferTest() = default;

    TestBuffer buffer{};
  };

  TEST_F(Template_BufferTest, defaultConfig)
  {
    ASSERT_EQ(8, buffer.capacity());
    ASSERT_EQ(0, buffer.size());
    ASSERT_TRUE(buffer.is_empty());

    // By enabling the macro ACCESS_CLASS_INTERNALS
    // (defined in testdefs.h) we can examine the
    // private members of our buffer class (by making
    // them public)
    //
    // ASSERT_EQ(0, buffer.read);
    // ASSERT_EQ(0, buffer.write);
  }

  TEST_F(Template_BufferTest, getFromEmpty)
  {
    auto[val, error] = buffer.get();
    ASSERT_EQ(TestBuffer::Status::Empty, error);
  }

  TEST_F(Template_BufferTest, addSingle)
  {
    auto error = buffer.add(100);
    ASSERT_EQ(1, buffer.size());
    ASSERT_FALSE(buffer.is_empty());
    ASSERT_EQ(TestBuffer::Status::Ok, error);
  }

  TEST_F(Template_BufferTest, getSingle)
  {
    buffer.add(100);
    auto[val, error] = buffer.get();

    ASSERT_EQ(100, val);
    ASSERT_EQ(0, buffer.size());
    ASSERT_TRUE(buffer.is_empty());
    ASSERT_EQ(TestBuffer::Status::Ok, error);
  }

  TEST_F(Template_BufferTest, fillBuffer)
  {
    for (unsigned i = 0; i < buffer.capacity(); ++i) {
      auto error = buffer.add(i);
      ASSERT_EQ(i + 1, buffer.size());
      ASSERT_FALSE(buffer.is_empty());
      ASSERT_EQ(TestBuffer::Status::Ok, error);
    }
  }

  TEST_F(Template_BufferTest, testFlush)
  {
    for (unsigned i = 0; i < buffer.capacity(); ++i) {
      buffer.add(i);
    }
    buffer.flush();
    ASSERT_EQ(0, buffer.size());
    ASSERT_TRUE(buffer.is_empty());
  }

  TEST_F(Template_BufferTest, addToFull)
  {
    for (unsigned i = 0; i < buffer.capacity(); ++i) {
      buffer.add(i);
    }

    auto error = buffer.add(100);
    ASSERT_EQ(8, buffer.size());
    ASSERT_FALSE(buffer.is_empty());
    ASSERT_EQ(TestBuffer::Status::Full, error);
  }

  TEST_F(Template_BufferTest, readFromFull)
  {
    for (unsigned i = 0; i < 16; ++i) {
      buffer.add(i);
    }

    for (unsigned i = 0; i < buffer.capacity(); ++i) {
      auto[val, error] = buffer.get();
      ASSERT_EQ(i, val);
      ASSERT_EQ(TestBuffer::Status::Ok, error);
    }
    ASSERT_EQ(0, buffer.size());
    ASSERT_TRUE(buffer.is_empty());
  }

  TEST_F(Template_BufferTest, readWriteAlternately)
  {
    for (unsigned i = 0; i < 32; ++i) {
      auto status = buffer.add(i);
      ASSERT_EQ(TestBuffer::Status::Ok, status);

      auto[val, error] = buffer.get();
      ASSERT_EQ(0, buffer.size());
      ASSERT_EQ(i, val);
      ASSERT_TRUE(buffer.is_empty());
      ASSERT_EQ(TestBuffer::Status::Ok, error);
    }
  }
}