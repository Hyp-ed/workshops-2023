#pragma once

#include <atomic>
#include <cstdint>
#include <thread>

namespace hyped {
namespace utils {
namespace concurrent {

class Thread {
 public:
  explicit Thread();
  virtual ~Thread() {}

  /**
   * @brief      Spawn new thread and call Run() method
   */
  void start();

  /**
   * @brief      Wait until the thread terminates
   */
  void join();
  void stop();

  /**
   * @brief      Thread entry point
   */
  virtual void run();

  static void yield();

  uint8_t getId() { return id_; }

  static void sleep(uint32_t ms);

 private:
  inline static uint8_t next_id_;
  uint8_t id_;
  std::thread *thread_;

 protected:
  std::atomic_bool is_running_ = true;
};

}  // namespace concurrent
}  // namespace utils
}  // namespace hyped
