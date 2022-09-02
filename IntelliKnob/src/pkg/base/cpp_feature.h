// Copyright (c) winking324
// Base cpp features
//

#pragma once  // NOLINT(build/header_guard)

namespace intelli_knob {
inline namespace pkg {
namespace base {

class NonCopyOrMovable {
 protected:
  NonCopyOrMovable() {}
  ~NonCopyOrMovable() {}

 private:
  NonCopyOrMovable(const NonCopyOrMovable &) = delete;
  NonCopyOrMovable(NonCopyOrMovable &&) = delete;
  NonCopyOrMovable &operator=(const NonCopyOrMovable &) = delete;
  NonCopyOrMovable &operator=(NonCopyOrMovable &&) = delete;
};

template <typename T>
class Singleton : private NonCopyOrMovable {
 public:
  static T *Instance() {
    static T inst;
    return &inst;
  }

  Singleton() = delete;
  ~Singleton() = delete;
};

}  // namespace base
}  // namespace pkg
}  // namespace intelli_knob
