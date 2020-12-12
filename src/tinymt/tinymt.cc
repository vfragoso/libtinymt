// Copyright (c) 2020, Victor Fragoso
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// Since this implementation is inspired by TinyMT, we include its BSD license.
//
// Copyright (c) 2011, 2013 Mutsuo Saito, Makoto Matsumoto,
// Hiroshima University and The University of Tokyo.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above
//      copyright notice, this list of conditions and the following
//      disclaimer in the documentation and/or other materials provided
//      with the distribution.
//    * Neither the name of the Hiroshima University nor the names of
//      its contributors may be used to endorse or promote products
//      derived from this software without specific prior written
//      permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <tinymt/tinymt.h>
#include <algorithm>

namespace mt {
namespace {

// Useful constants.
const size_t kNumStateEntries32 = 4;
const size_t kNumStateEntries64 = 2;
const size_t kInitialLoopIterations = 8;
const size_t kUpdateStateIterations = 8;
const uint64_t kMultiplier164 = static_cast<uint64_t>(0xfa051f40);
const uint64_t kMultiplier264 = static_cast<uint64_t>(0xffd0fff4);
const uint64_t kTempering64 = 0x58d02ffeffbfffbc;
const uint32_t kInitialFactor32 = static_cast<uint32_t>(1812433253);
const uint64_t kInitialFactor64 = static_cast<uint64_t>(6364136223846793005);
const uint32_t kFirstTwoBitsMask = 3;
const uint32_t kTinyMT32Mask = static_cast<uint32_t>(0x7fffffff);
const uint32_t kTinyMT32SH0 = 1;
const uint32_t kTinyMT32SH1 = 10;
const uint32_t kTinyMT32SH8 = 8;
const uint64_t kTinyMT64SH0 = 12;
const uint64_t kTinyMT64SH1 = 11;
const uint64_t kTinyMT64SH8 = 8;
const uint64_t kTinyMT64Mask = static_cast<uint64_t>(0x7fffffffffffffff);
const uint32_t kDefaultSeed = 1;
// Minimum and maxium values.
// Minimum uint32_t value is 0.
const uint32_t kMinUint32Value = 0;
// Maximum uint32_t value is 2^32 - 1.
const uint32_t kMaxUint32Value = static_cast<uint32_t>(0xFFFFFFFF);
// Maximum uint64_t value is 2^64 - 1.
const uint64_t kMaxUint64Value = static_cast<uint64_t>(0xFFFFFFFFFFFFFFFF);
// Initial state for 32 bits.
const uint32_t kDefaultState32[kNumStateEntries32] = {
  /* initial seed = */ kDefaultSeed,
  /* mat1 = */ 0x8f7011ee,
  /* mat2 = */ 0xfc78ff1f,
  /* tmat = */ 0x3793fdff
};

}  // namespace

//////////////////////////////
// Implementation for 32 bits.
template<>
inline void TinyMT<uint32_t>::NextState() {
  uint32_t y = state_[3];
  uint32_t x = (state_[0] & kTinyMT32Mask) ^ state_[1] ^ state_[2];
  x ^= (x << kTinyMT32SH0);
  y ^= (y >> kTinyMT32SH0) ^ x;
  state_[0] = state_[1];
  state_[1] = state_[2];
  state_[2] = x ^ (y << kTinyMT32SH1);
  state_[3] = y;
  state_[1] ^= static_cast<uint32_t>(
      -(static_cast<int32_t>(y & 1)) & static_cast<int32_t>(multiplier1_));
  state_[2] ^= static_cast<uint32_t>(
      -(static_cast<int32_t>(y & 1)) & static_cast<int32_t>(multiplier2_));
}

template <>
void TinyMT<uint32_t>::Reset() {
  // Reset the state vector.
  std::copy(kDefaultState32, kDefaultState32 + kNumStateEntries32, state_);
  // Initialize multipliers and tempering params.
  multiplier1_ = kDefaultState32[1];
  multiplier2_ = kDefaultState32[2];
  tempering_ = kDefaultState32[3];
  // Initialize seed into the state.
  state_[0] = initial_seed_;
  // Initialize the state vector.
  for (uint32_t i = 1; i < kInitialLoopIterations; ++i) {
    state_[i & kFirstTwoBitsMask] ^=
        i + kInitialFactor32 *
        (state_[(i - 1) & kFirstTwoBitsMask] ^
         (state_[(i - 1) & kFirstTwoBitsMask] >> 30));
  }
  // Update state.
  for (size_t i = 0; i < kUpdateStateIterations; ++i) {
    NextState();
  }
}

template <>
inline uint32_t TinyMT<uint32_t>::ExtractUnsignedIntegerFromState() {
  uint32_t outputInteger = state_[3];
  uint32_t temp = state_[0] + (state_[2] >> kTinyMT32SH8);
  outputInteger ^= temp;
  if ((temp & 1) != 0) {
    outputInteger ^= tempering_;
  }
  return outputInteger;
}

template <>
uint32_t TinyMT<uint32_t>::Generate() {
  NextState();
  return ExtractUnsignedIntegerFromState();
}

template <>
uint32_t TinyMT<uint32_t>::MaxValue() const {
  return kMaxUint32Value;
}

template <>
uint32_t TinyMT<uint32_t>::MinValue() const {
  return kMinUint32Value;
}

//////////////////////////////
// Implementation for 64 bits.
template <>
inline void TinyMT<uint64_t>::NextState() {
  state_[0] &= kTinyMT64Mask;
  uint64_t x = state_[0] ^ state_[1];
  x ^= x << kTinyMT64SH0;
  x ^= x >> 32;
  x ^= x << 32;
  x ^= x << kTinyMT64SH1;
  state_[0] = state_[1];
  state_[1] = x;
  if ((x & 1) != 0) {
    state_[0] ^= multiplier1_;
    state_[1] ^= (multiplier2_ << 32);
  }
}

template <>
void TinyMT<uint64_t>::Reset() {
  // Initialize multipliers.
  multiplier1_ = kMultiplier164;
  multiplier2_ = kMultiplier264;
  tempering_ = kTempering64;
  // Reset the state vector; only two entries in the state array are necessary.
  state_[0] = initial_seed_ ^ (multiplier1_ << 32);
  state_[1] = multiplier2_ ^ tempering_;
  state_[2] = 0;
  state_[3] = 0;
  for (size_t i = 1; i < kInitialLoopIterations; ++i) {
    state_[i & 1] ^=
        i + kInitialFactor64 *
        (state_[(i - 1) & 1] ^ (state_[(i - 1) & 1] >> 62));
  }
}

template <>
inline uint64_t TinyMT<uint64_t>::ExtractUnsignedIntegerFromState() {
  uint64_t outputInteger = state_[0] + state_[1];
  outputInteger ^= state_[0] >> kTinyMT64SH8;
  if ((outputInteger & 1) != 0) {
    outputInteger ^= tempering_;
  }
  return outputInteger;
}

template <>
uint64_t TinyMT<uint64_t>::Generate() {
  NextState();
  return ExtractUnsignedIntegerFromState();
}

template <>
uint64_t TinyMT<uint64_t>::MaxValue() const {
  return kMaxUint64Value;
}

template <>
uint64_t TinyMT<uint64_t>::MinValue() const {
  return static_cast<uint64_t>(kMinUint32Value);
}

}  // namespace mt

