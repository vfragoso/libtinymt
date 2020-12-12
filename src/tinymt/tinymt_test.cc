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

#include <cmath>
#include <random>
#include <stdint.h>
#include <vector>
#include <gtest/gtest.h>
#include <tinymt/tinymt.h>

namespace mt {
namespace {
// Useful constants.
constexpr uint32_t kMaxValue32 = 0xFFFFFFFF;
constexpr uint64_t kMaxValue64 = 0xFFFFFFFFFFFFFFFF;
constexpr size_t kNumSamples = 10000;

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
  15503804787016557143U, 17280942441431881838U, 2177846447079362065U,
  10087979609567186558U, 8925138365609588954U, 13030236470185662861U,
  4821755207395923002U, 11414418928600017220U, 18168456707151075513U,
  1749899882787913913U, 2383809859898491614U, 4819668342796295952U,
  11996915412652201592U, 11312565842793520524U, 995000466268691999U,
  6363016470553061398U, 7460106683467501926U, 981478760989475592U,
  11852898451934348777U, 5976355772385089998U, 16662491692959689977U,
  4997134580858653476U, 11142084553658001518U, 12405136656253403414U,
  10700258834832712655U, 13440132573874649640U, 15190104899818839732U,
  14179849157427519166U, 10328306841423370385U, 9266343271776906817U
};

TEST(TinyMTTest, UniformDistributionUsingUnsignedInts32) {
  TinyMT<uint32_t> prng;
  EXPECT_EQ(TinyMT<uint32_t>::min(), 0);
  EXPECT_EQ(TinyMT<uint32_t>::max(), kMaxValue32);
  const size_t num_samples =
      sizeof(kExpectedUint32SequenceWithDefaultSeed) / sizeof(uint32_t);
  for (size_t i = 0; i < num_samples; ++i) {
    const uint32_t random_value = prng.Generate();
    EXPECT_GE(random_value, 0);
    EXPECT_LE(random_value, kMaxValue32);
    EXPECT_EQ(random_value, kExpectedUint32SequenceWithDefaultSeed[i]);
  }
}

TEST(TinyMTTest, UniformDistributionUsingUnsignedInts64) {
  TinyMT<uint64_t> prng;
  EXPECT_EQ(TinyMT<uint64_t>::min(), static_cast<uint64_t>(0));
  EXPECT_EQ(TinyMT<uint64_t>::max(), kMaxValue64);
  const size_t num_samples =
      sizeof(kExpectedUint64SequenceWithDefaultSeed) / sizeof(uint64_t);
  for (size_t i = 0; i < num_samples; ++i) {
    const uint64_t random_value = prng.Generate();
    EXPECT_GE(random_value, static_cast<uint64_t>(0));
    EXPECT_LE(random_value, kMaxValue64);
    EXPECT_EQ(random_value, kExpectedUint64SequenceWithDefaultSeed[i]);    
  }
}

TEST(TinyMTTest, StandardNormalDistribution) {
  TinyMT<uint32_t> prng(11);
  std::normal_distribution<float> dist;
  std::vector<float> samples;
  float mean = 0.0f;
  for (size_t i = 0; i < kNumSamples; ++i) {
    samples.push_back(dist(prng));
    mean += samples.back();
  }
  mean /= samples.size();
  EXPECT_NEAR(0.0f, mean, 0.1);
  float std_dev = 0.0f;
  for (const float sample : samples) {
    const float deviation = mean - sample;
    std_dev += deviation * deviation;
  }
  std_dev /= samples.size();
  std_dev = std::sqrtf(std_dev);
  EXPECT_NEAR(1.0f, std_dev, 0.1);
}

}  // namespace
}  // namespace mt
