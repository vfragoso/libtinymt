// TODO(vifragos): Add license here.

#include <stdint.h>

namespace mt {

template <typename ResultType, typename WordType>
class TinyMT {
public:
  explicit TinyMT(WordType seed);
  TinyMT();

  void Reset();

  ResultType Generate();

  bool IsPeriodReached() const;
  ResultType min_value() const;
  ResultType max_value() const;

private:
  WordType initial_seed_;
  WordType state_[4];
  // Multipliers and tempering factors.
  WordType multiplier1_;
  WordType multiplier2_;
  WordType tempering_;

  // Helper functions.
  void NextState();
  // Extracts a uint32_t instance from state.
  WordType ExtractUnsignedIntegerFromState();
  // Extracts a float instance from state ranging from 0.0f <= number < 1.0f.
  float ExtractFloatFromState();
  // Extracts a float instance from state ranging from 0.0 <= number < 1.0.
  double ExtractDoubleFromState();
};

}  // namespace mt