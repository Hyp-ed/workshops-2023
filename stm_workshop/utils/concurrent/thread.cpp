#include "thread.hpp"

#include <chrono>

namespace hyped::utils::concurrent {

namespace {

void threadEntryPoint(Thread *this_)
{
  this_->run();
}

}  // namespace

Thread::Thread() : id_(next_id_++), thread_(0)
{
}

void Thread::start()
{
  thread_ = new std::thread(threadEntryPoint, this);
}

void Thread::join()
{
  thread_->join();
}

void Thread::stop()
{
  is_running_ = false;
}

void Thread::run()
{

}

void Thread::yield()
{
  std::this_thread::yield();
}

void Thread::sleep(uint32_t ms)
{
  std::this_thread::sleep_for(std::chrono::microseconds(ms * 1000));
}

}  // namespace hyped::utils::concurrent