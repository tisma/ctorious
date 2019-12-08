#include <atomic>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <thread>

class CLooper {
public:
  using Runnable = std::function<void()>;

  class CDispatcher {
    friend class CLooper;

  public:
    bool post(CLooper::Runnable &&aOther) {
      return mAssignedLooper.post(std::move(aOther));
    }

  private:
    CDispatcher(CLooper &aLooper) : mAssignedLooper(aLooper) {}
    CLooper &mAssignedLooper;
  };

  CLooper()
      : mDispatcher(std::shared_ptr<CDispatcher>(new CDispatcher(*this))) {}
  ~CLooper() { abortAndJoin(); }

  void stop() { abortAndJoin(); }

  bool run() {
    try {
      mThread = std::thread(&CLooper::runFunc, this);
    } catch (...) {
      return false;
    }

    return true;
  }

  bool running() { return mRunning.load(); }

  Runnable next() {
    std::lock_guard guard(mRunnablesMutex);

    if (mRunnables.empty()) {
      return nullptr;
    }

    Runnable runnable = mRunnables.front();
    mRunnables.pop();

    return runnable;
  }

  std::shared_ptr<CDispatcher> getDispatcher() { return mDispatcher; }

private:
  void runFunc() {
    mRunning.store(true);
    while (false == mAbortRequested.load()) {
      try {
        using namespace std::chrono_literals;
        Runnable r = next();
        if (nullptr != r) {
          r();
        } else {
          std::this_thread::sleep_for(1ms);
        }
      } catch (std::runtime_error &e) {

      } catch (...) {
      }
    }
    mRunning.store(false);
  }

  void abortAndJoin() {
    mAbortRequested.store(true);
    if (mThread.joinable()) {
      mThread.join();
    }
  }

  bool post(Runnable &&aRunnable) {
    if (not running()) {
      return false;
    }

    try {
      std::lock_guard guard(mRunnablesMutex);
      mRunnables.push(std::move(aRunnable));
    } catch (...) {
      return false;
    }

    return true;
  }

  std::thread mThread;
  std::atomic_bool mRunning;
  std::atomic_bool mAbortRequested;
  std::recursive_mutex mRunnablesMutex;
  std::queue<Runnable> mRunnables;
  std::shared_ptr<CDispatcher> mDispatcher;
};

int main() {
  auto looper = std::make_unique<CLooper>();
  std::cout << "Starting looper" << std::endl;
  looper->run();

  auto dispatcher = looper->getDispatcher();

  std::cout << "Adding tasks" << std::endl;
  for (uint32_t k = 0; k < 500; ++k) {
    auto const task = [k]() {
      std::cout
          << "Invocation " << k
          << ": Hello, I have been executed asynchronously on the looper for "
          << (k + 1) << " times." << std::endl;
    };

    dispatcher->post(std::move(task));
  }

  std::cout << "Waiting 5 seconds for completion" << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(5));

  std::cout << "Stopping looper" << std::endl;

  dispatcher = nullptr;
  looper->stop();
  looper = nullptr;

  return 0;
}
