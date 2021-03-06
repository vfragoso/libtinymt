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

#ifndef TINYMT_TINYMT_H_
#define TINYMT_TINYMT_H_

#include <stdint.h>
#include <limits>

namespace mt {

// This class implements TinyMT,  an efficient MersenneTwister pseudo random
// number generator proposed by Mutsuo Saito (Hiroshima University) and Makoto
// Matsumoto (The University of Tokyo).
//
// This class only implements TinyMT for 32 and 64 bits using C++ classes.
//
// Examples:
//
//   TinyMT<uint32_t> prng32;
//   const uint32_t random_number_32 = prng32.Generate();
//
//   TinyMT<uint64_t> prng64(/* initial_seed = */ 11);
//   const uint64_t random_number_32 = prng64.Generate();
//
//   TinyMT<uint32_t> prng;
//   std::normal_distribution<float> dist;
//   const float sample = dist(prng);
template <typename ResultType>
class TinyMT {
 public:
  // Parameters:
  //   seed:  Initial seed.
  explicit TinyMT(ResultType seed);

  // The default constructor uses static_cast<ResultType>(1) as an initial seed.
  TinyMT();

  // Resets the internal state variables.
  void Reset();

  // Generates a number in the range [min(), max()]. The minimum and
  // maximum values depend on the ResultType and can be obtained by calling
  // min() and max() functions; see below.
  ResultType Generate();

  // Gets the initial seed.
  ResultType initial_seed() const;

  // Defining 'result_type' so that TinyMT can be used w/ many of the
  // distributions in the standard library of C++11 and above standards.
  typedef ResultType result_type;

  // The maximum value this PRNG can generate. The maximum value this PRNG can
  // generate depends on the ResultType either uint32_t and uint64_t.
  static constexpr result_type max() {
    return std::numeric_limits<result_type>::max();
  }

  // The minimum value this PRNG can generate. The minimum value this PRNG can
  // generate depends on the ResultType either uint32_t and uint64_t.
  static constexpr result_type min() {
    return std::numeric_limits<result_type>::min();
  }

  // Generates a random number by calling Generate(); see above.
  result_type operator()() {
    return Generate();
  }

 private:
  // Initial seed.
  const ResultType initial_seed_;
  ResultType state_[4];

  // Multipliers and tempering factors.
  ResultType multiplier1_;
  ResultType multiplier2_;
  ResultType tempering_;

  // Helper functions.

  // Advances the state.
  void NextState();

  // Extracts an unsigned integer from state.
  ResultType ExtractUnsignedIntegerFromState();
};

// Implementation.
template <typename ResultType>
TinyMT<ResultType>::TinyMT(ResultType seed) : initial_seed_(seed) {
  Reset();
}

template <typename ResultType>
TinyMT<ResultType>::TinyMT() : initial_seed_(static_cast<ResultType>(1)) {
  Reset();
}

template <typename ResultType>
ResultType TinyMT<ResultType>::initial_seed() const {
  return initial_seed_;
}

}  // namespace mt

#endif  // TINYMT_TINYMT_H_

