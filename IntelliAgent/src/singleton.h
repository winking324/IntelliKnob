// Copyright (c) winking324
//

#pragma once

namespace intelli_agent {

class NonCopyOrMovable {
 protected:
  NonCopyOrMovable() = default;
  ~NonCopyOrMovable() = default;

 private:
  NonCopyOrMovable(const NonCopyOrMovable &) = delete;
  NonCopyOrMovable(NonCopyOrMovable &&) = delete;
  NonCopyOrMovable &operator=(const NonCopyOrMovable &) = delete;
  NonCopyOrMovable &operator=(NonCopyOrMovable &&) = delete;
};

template <class T>
class Singleton : private NonCopyOrMovable {
 public:
  static T *Instance() {
    static T inst;
    return &inst;
  }

  Singleton() = delete;
  ~Singleton() = delete;
};

}  // namespace intelli_agent
