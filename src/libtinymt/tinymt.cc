// TODO(vfragos): Implement me!

#include "tinymt.h"

namespace mt {

template <typename ResultType, typename WordType> 
TinyMT<ResultType, WordType>::TinyMT(WordType seed) : initial_seed_(seed) {}

template <typename ResultType, typename WordType> 
TinyMT<ResultType, WordType>::TinyMT() : initial_seed_(static_cast<WordType>(1)) {}

// Implementation for 32 bits.
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
