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

#include <stdint.h>
#include <gtest/gtest.h>
#include <tinymt/tinymt.h>

namespace mt {
namespace {
// Useful constants.
constexpr uint32_t kMaxValue32 = 0xFFFFFFFF;
constexpr uint64_t kMaxValue64 = 0xFFFFFFFFFFFFFFFF;

// Test the generated sequences from the authors.
// https://github.com/MersenneTwister-Lab/TinyMT/blob/master/tinymt/check32.out.txt.
const uint32_t kExpectedUint32SequenceWithDefaultSeed[] = {
  2545341989, 981918433, 3715302833, 2387538352, 3591001365,
  3820442102, 2114400566, 2196103051, 2783359912, 764534509,
  643179475, 1822416315, 881558334, 4207026366, 3690273640,
  3240535687, 2921447122, 3984931427, 4092394160, 44209675,
  2188315343, 2908663843, 1834519336, 3774670961, 3019990707,
  4065554902, 1239765502, 4035716197, 3412127188, 552822483,
  161364450, 353727785, 140085994, 149132008, 2547770827,
  4064042525, 4078297538, 2057335507, 622384752, 2041665899,
  2193913817, 1080849512, 33160901, 662956935, 642999063,
  3384709977, 1723175122, 3866752252, 521822317, 2292524454};
// https://github.com/MersenneTwister-Lab/TinyMT/blob/master/tinymt/check64.out.txt.
const uint64_t kExpectedUint64SequenceWithDefaultSeed[] = {
  15503804787016557143, 17280942441431881838, 2177846447079362065,
  10087979609567186558, 8925138365609588954, 13030236470185662861,
  4821755207395923002, 11414418928600017220, 18168456707151075513,
  1749899882787913913, 2383809859898491614, 4819668342796295952,
  11996915412652201592, 11312565842793520524, 995000466268691999,
  6363016470553061398, 7460106683467501926, 981478760989475592,
  11852898451934348777, 5976355772385089998, 16662491692959689977,
  4997134580858653476, 11142084553658001518, 12405136656253403414,
  10700258834832712655, 13440132573874649640, 15190104899818839732,
  14179849157427519166, 10328306841423370385, 9266343271776906817
};

TEST(TinyMTTest, UniformDistributionUsingUnsignedInts32) {
  TinyMT<uint32_t> prng;
  EXPECT_EQ(prng.MinValue(), 0);
  EXPECT_EQ(prng.MaxValue(), kMaxValue32);
  const size_t num_samples =
      sizeof(kExpectedUint32SequenceWithDefaultSeed) / sizeof(uint32_t);
  for (size_t i = 0; i < num_samples; ++i) {
    const uint32_t random_value = prng.Generate();
    EXPECT_LE(random_value, prng.MaxValue());
    EXPECT_GE(random_value, prng.MinValue());
    EXPECT_EQ(random_value, kExpectedUint32SequenceWithDefaultSeed[i]);
  }
}

TEST(TinyMTTest, UniformDistributionUsingUnsignedInts64) {
  TinyMT<uint64_t> prng;
  EXPECT_EQ(prng.MinValue(), 0);
  EXPECT_EQ(prng.MaxValue(), kMaxValue64);
  const size_t num_samples =
      sizeof(kExpectedUint64SequenceWithDefaultSeed) / sizeof(uint64_t);
  for (size_t i = 0; i < num_samples; ++i) {
    const uint32_t random_value = prng.Generate();
    EXPECT_LE(random_value, prng.MaxValue());
    EXPECT_GE(random_value, prng.MinValue());
    EXPECT_EQ(random_value, kExpectedUint64SequenceWithDefaultSeed[i]);    
  }
}

}  // namespace
}  // namespace mt
