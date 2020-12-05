// TODO(vfragos): Implement me!

#include "tinymt.h"
#include <algorithm>

namespace mt {
namespace {
  // Useful constants.
  const uint8_t kNumStateEntries = 4;
  const uint32_t kDefaultSeed = 1;
  // Initial state.
  const uint32_t kDefaultState32[kNumStateEntries] = {
    /* initial seed = */ kDefaultSeed, 
    /* mat1 = */ 0x8f7011ee, 
    /* mat2 = */ 0xfc78ff1f, 
    /* tmat = */ 0x3793fdff};
            
}  // namespace

template <typename ResultType, typename WordType> 
TinyMT<ResultType, WordType>::TinyMT(WordType seed) : initial_seed_(seed) {
    Reset();
}

template <typename ResultType, typename WordType> 
TinyMT<ResultType, WordType>::TinyMT() : initial_seed_(static_cast<WordType>(kDefaultSeed)) { 
    Reset();
}

// Implementation for 32 bits.
template <typename ResultType> 
class TinyMT<ResultType, uint32_t> {
public:
  explicit TinyMT(uint32_t seed);
  TinyMT();
  void Reset();
  ResultType Generate();

private:
  uint32_t initial_seed_;
  uint32_t state_[4];
  // Multipliers and tempering factors.
  uint32_t multiplier1_;
  uint32_t multiplier2_;
  uint32_t tempering_;

  // Helper functions.
  void NextState();
  // Extracts a uint32_t instance from state.
  uint32_t ExtractUnsignedIntegerFromState();
  // Extracts a float instance from state ranging from 0.0f <= number < 1.0f.
  float ExtractFloatFromState();
  // Extracts a float instance from state ranging from 0.0 <= number < 1.0.
  double ExtractDoubleFromState();
};

template <typename ResultType> 
void TinyMT<ResultType, uint32_t>::Reset() {
  // Reset the state vector.
  std::copy(kDefaultState32, kDefaultState32 + kNumStateEntries, state_);
  // Initialize multipliers and tempering params.
  multiplier1_ = kDefaultState32[1];
  multiplier2_ = kDefaultState32[2];
  tempering_ = kDefaultState32[3];
  // Initialize seed into the state.
  state_[0] = initial_seed_;
  /*
  // Initialize the state vector.
  for (uint32_t i = 1; i < kInitialLoopIterations; ++i) {
    m_state[ComputeFirstTwoBits(i)] ^= 
    i + kInitialFactor * (m_state[ComputeFirstTwoBits(i - 1)] ^ (m_state[ComputeFirstTwoBits(i - 1)] >> 30));
  }
  // Update state.
  for (size_t i = 0; i < kUpdateStateIterations; ++i) {
    NextState();
  }
  */
}

template <> uint32_t TinyMT<uint32_t, uint32_t>::Generate() {
  return 0;
}

template <> float TinyMT<float, uint32_t>::Generate() {
  return 0.0f;
}

template <> double TinyMT<double, uint32_t>::Generate() {
  return 0.0;
}

// Implementation for 64 bits.
template <> uint64_t TinyMT<uint64_t, uint64_t>::Generate() {
  return 0;
}

template <> float TinyMT<float, uint64_t>::Generate() {
  return 0.0f;
}

template <> double TinyMT<double, uint64_t>::Generate() {
  return 0.0;
}

}  // namespace mt
