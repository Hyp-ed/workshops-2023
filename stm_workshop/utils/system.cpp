#include "system.hpp"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include <csignal>
#include <cstring>
#include <fstream>
#include <random>

namespace hyped::utils {


System::System()
    : running_(true)
{
}

std::uint64_t System::newRunId()
{
  static std::default_random_engine random_engine;
  static std::uniform_int_distribution<uint64_t> distribution(
    std::numeric_limits<std::uint64_t>::min(), std::numeric_limits<std::uint64_t>::max());
  return distribution(random_engine);
}

System &System::getSystem()
{
  if (system_) { return *system_; }
  /* Would love to log someone trying to access the system before initialization*/ 
  exit(1);
}

void System::interruptHandler(int)
{
  if (system_) { system_->stop(); }
  /* Would love to log this 'peaceful' interrupt signal */ 
  exit(0);
}

void System::segfaultHandler(int)
{
  if (system_) { system_->stop(); }
  /* Would love to log this seg fault */ 
  exit(1);
}

bool System::setExitFunction()
{
  static bool signal_set = false;
  if (signal_set) { return true; }

  // nominal termination
  std::signal(SIGINT, &interruptHandler);

  // forced termination
  std::signal(SIGSEGV, &segfaultHandler);
  std::signal(SIGABRT, &segfaultHandler);
  std::signal(SIGFPE, &segfaultHandler);
  std::signal(SIGILL, &segfaultHandler);
  std::signal(SIGTERM, &segfaultHandler);

  signal_set = true;
  return true;
}

bool System::isRunning()
{
  utils::concurrent::ScopedLock scoped_lock(&lock_);
  return running_;
}

void System::stop()
{
  utils::concurrent::ScopedLock scoped_lock(&lock_);
  running_ = false;
}

}  // namespace hyped::utils