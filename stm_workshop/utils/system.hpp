#pragma once

#include "utils.hpp"

#include <cstdint>
#include <memory>

#include <utils/concurrent/barrier.hpp>

namespace hyped::utils {

class System {
 public:
  System();
  static std::uint64_t newRunId();
  static System &getSystem();

  /**
   * Register custom signal handler for CTRL+C to make system exit gracefully
   */
  static bool setExitFunction();

  bool isRunning();
  void stop();

 private:
  utils::concurrent::Lock lock_;
  bool running_;

  inline static std::unique_ptr<System> system_;

  static void interruptHandler(int);
  static void segfaultHandler(int);

  System() = delete;
  NO_COPY_ASSIGN(System)
};

}  // namespace hyped::utils