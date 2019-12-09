#include <atomic>
#include <chrono>
#include <thread>
#include <utility>

#include <fmt/printf.h>
#include <gsl/gsl_assert>

template <typename Agent> concept IsAgent = requires(Agent agent) {
  {agent.doWork()};
};

template <typename Agent> requires IsAgent<Agent> class Runner {
public:
  Runner(Agent &&agent) : m_agent(std::forward<Agent>(agent)) {}

  constexpr void start() {
    m_running = true;
    m_thread = std::thread([&]() { run(); });
  }

  constexpr void run() {
    while (m_running) {
      m_agent.doWork();
    }
  }

  constexpr void stop() {
    m_running = false;
    m_thread.join();
  }

  ~Runner() { Expects(m_running == false); }

private:
  Agent m_agent;
  std::thread m_thread;
  std::atomic<bool> m_running{false};
};

template <typename Agent> Runner(Agent &&)->Runner<Agent>;

class HelloWorldAgent {
public:
  void doWork() noexcept { fmt::print("Hello, {}!\n", "Nanosecond"); }
};

int main() {
  using namespace std::chrono_literals;

  auto runner = Runner{HelloWorldAgent{}};
  runner.start();

  std::this_thread::sleep_for(2s);

  runner.stop();

  return 0;
}
