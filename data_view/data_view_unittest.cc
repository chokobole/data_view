// Copyright (c) 2019 The DataView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "data_view/data_view.h"

#include "gtest/gtest.h"

namespace data_view {

template <typename T>
void ReadEndianTestImpl(ConstDataView data_view, const T* answer_le,
                        const T* answer_be) {
  for (size_t i = 0; i < data_view.length(); i += sizeof(T)) {
    T v;
    EXPECT_TRUE(data_view.Read(i, &v, true));
    EXPECT_EQ(v, *answer_le++);
    EXPECT_TRUE(data_view.Read(i, &v, false));
    EXPECT_EQ(v, *answer_be++);
  }
}

uint16_t makeU16BE(uint8_t u0, uint8_t u1) { return (u0 << 8) | u1; }

uint16_t makeU16LE(uint8_t u0, uint8_t u1) { return (u1 << 8) | u0; }

uint32_t makeU32BE(uint8_t u0, uint8_t u1, uint8_t u2, uint8_t u3) {
  return (u0 << 24) | (u1 << 16) | (u2 << 8) | u3;
}

uint32_t makeU32LE(uint8_t u0, uint8_t u1, uint8_t u2, uint8_t u3) {
  return (u3 << 24) | (u2 << 16) | (u1 << 8) | u0;
}

float makeF32BE(uint8_t u0, uint8_t u1, uint8_t u2, uint8_t u3) {
  union {
    uint32_t u32;
    float f32;
  } v;
  v.u32 = makeU32BE(u0, u1, u2, u3);
  return v.f32;
}

float makeF32LE(uint8_t u0, uint8_t u1, uint8_t u2, uint8_t u3) {
  union {
    uint32_t u32;
    float f32;
  } v;
  v.u32 = makeU32LE(u0, u1, u2, u3);
  return v.f32;
}

TEST(DataViewTest, ReadEndianTest) {
  const char buf[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  size_t buf_len = sizeof(buf);
  ConstDataView data_view(buf, buf_len);
  EXPECT_EQ(buf_len, data_view.length());

  ReadEndianTestImpl(data_view, buf, buf);
  const uint16_t u16_le[] = {
      makeU16LE(0, 1), makeU16LE(2, 3), makeU16LE(4, 5),
      makeU16LE(6, 7), makeU16LE(8, 9), makeU16LE(10, 11),
  };
  const uint16_t u16_be[] = {
      makeU16BE(0, 1), makeU16BE(2, 3), makeU16BE(4, 5),
      makeU16BE(6, 7), makeU16BE(8, 9), makeU16BE(10, 11),
  };
  ReadEndianTestImpl(data_view, u16_le, u16_be);
  const uint32_t u32_le[] = {
      makeU32LE(0, 1, 2, 3),
      makeU32LE(4, 5, 6, 7),
      makeU32LE(8, 9, 10, 11),
  };
  const uint32_t u32_be[] = {
      makeU32BE(0, 1, 2, 3),
      makeU32BE(4, 5, 6, 7),
      makeU32BE(8, 9, 10, 11),
  };
  ReadEndianTestImpl(data_view, u32_le, u32_be);
  const float f32_le[] = {
      makeF32LE(0, 1, 2, 3),
      makeF32LE(4, 5, 6, 7),
      makeF32LE(8, 9, 10, 11),
  };
  const float f32_be[] = {
      makeF32BE(0, 1, 2, 3),
      makeF32BE(4, 5, 6, 7),
      makeF32BE(8, 9, 10, 11),
  };
  ReadEndianTestImpl(data_view, f32_le, f32_be);
}

template <typename T>
void WriteEndianTestImpl(DataView data_view) {
  for (size_t i = 0; i < data_view.length(); i += sizeof(T)) {
    EXPECT_TRUE(data_view.Write(i, static_cast<T>(i), true));
    T v;
    EXPECT_TRUE(data_view.Read(i, &v, true));
    EXPECT_EQ(v, i);

    EXPECT_TRUE(data_view.Write(i, static_cast<T>(i), false));
    EXPECT_TRUE(data_view.Read(i, &v, false));
    EXPECT_EQ(v, i);
  }
}

TEST(DataViewTest, WriteEndianTest) {
  char buf[16] = {
      0,
  };
  size_t buf_len = sizeof(buf);
  DataView data_view(buf, buf_len);
  EXPECT_EQ(buf_len, data_view.length());

  WriteEndianTestImpl<uint8_t>(data_view);
  WriteEndianTestImpl<uint16_t>(data_view);
  WriteEndianTestImpl<int16_t>(data_view);
  WriteEndianTestImpl<float>(data_view);
  WriteEndianTestImpl<double>(data_view);
}

}  // namespace data_view