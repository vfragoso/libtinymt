// Copyright (c) 2020, Victor Fragoso
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.

// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
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

namespace mt {

template <typename ResultType>
class TinyMT {
 public:
  explicit TinyMT(ResultType seed);
  TinyMT();

  void Reset();
  ResultType Generate();
  bool IsPeriodReached() const;
  ResultType MinValue() const;
  ResultType MaxValue() const;

  // Getters.
  ResultType initial_seed() const;

 private:
  // Initial seed.
  ResultType initial_seed_;
  ResultType state_[4];
  // Multipliers and tempering factors.
  ResultType multiplier1_;
  ResultType multiplier2_;
  ResultType tempering_;

  // Helper functions.
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
