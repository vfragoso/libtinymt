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
  ResultType MinValue() const;
  ResultType MaxValue() const;

  // Getters.
  WordType initial_seed() const {
    return initial_seed_;
  }

private:
  // Initial seed.
  WordType initial_seed_;
};

}  // namespace mt