#include <array>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <optional>
#include <sstream>
#include <string_view>
#include <type_traits>

template<typename payload>
concept event_payload = requires(payload a, std::ostream& os) {
  { a.to_osstream(os) } -> std::same_as<void>;
};

struct signal
{
  enum class transmission_type : std::uint8_t { SENT, RECEIVED };
  enum class signal_type : std::uint8_t { SIGNAL1, SIGNAL2, SIGNAL3, SIGNAL4, SIGNAL5 };

  [[nodiscard]] inline static constexpr auto
  enum_to_cstr(const transmission_type& status) noexcept -> const char*
  {
      switch(status) {
          case transmission_type::SENT: return "SENT";
          case transmission_type::RECEIVED: return "RECD";
      }
      return "Unknown";
  }

  [[nodiscard]] static constexpr auto
  enum_to_cstr(const signal_type& s) noexcept -> const char*
  {
    switch (s)
    {
      case signal_type::SIGNAL1: return "Signal 1";
      case signal_type::SIGNAL2: return "Signal 2";
      case signal_type::SIGNAL3: return "Signal 3";
      case signal_type::SIGNAL4: return "Signal 4";
      case signal_type::SIGNAL5: return "Signal 5";
    }
    return "Unknown Signal";
  }

  inline friend std::ostream& operator<<(std::ostream& os, const signal& sig) noexcept
  {
      sig.to_osstream(os);
      return os;
  }

  inline void
  to_osstream(std::ostream& os) const noexcept
  {
    os << ' ' << enum_to_cstr(_status)
       << ' ' << enum_to_cstr(_signal)
       << _debug_string
       << '.';
  }

  transmission_type _status;
  signal_type _signal;
  std::string _debug_string;
};


template<event_payload Event, std::size_t N>
class circular_buffer
{
public:
  inline auto
  log(const Event& message) noexcept
  {
    buffer[write_index] = {std::chrono::system_clock::now(), message};
    write_index = (write_index + 1) % N;
    active_entries = std::min(active_entries + 1, N);
  }

  inline auto
  to_osstream(std::ostream& os) const noexcept
  {
    for(std::size_t i = 0; i < active_entries; ++i)
    {
      const auto index = (write_index + N - active_entries + i) % N;
      const auto& [timestamp, message] = buffer[index];
      const auto time = std::chrono::system_clock::to_time_t(timestamp);
      os << std::put_time(std::localtime(&time), "%Y-%m-%d %X") << ' ' << message << '\n';
    }
  }

  [[nodiscard]] inline auto
  to_string() const noexcept -> std::string
  {
    std::ostringstream oss;
    to_osstream(oss);
    return oss.str();
  }

private:
  std::array<std::pair<std::chrono::system_clock::time_point, Event>, N> buffer = {};
  std::size_t write_index = 0;
  std::size_t active_entries = 0;
};

int main()
{
  circular_buffer<signal, 5> logger;

  logger.log(signal{
    ._status = signal::transmission_type::SENT,
    ._signal = signal::signal_type::SIGNAL1,
    ._debug_string = "This will be removed..."
  });
  logger.log(signal{
    ._status = signal::transmission_type::SENT,
    ._signal = signal::signal_type::SIGNAL1
  });
  logger.log(signal{
    ._status = signal::transmission_type::RECEIVED,
    ._signal = signal::signal_type::SIGNAL2
  });
  logger.log(signal{
    ._status = signal::transmission_type::SENT,
    ._signal = signal::signal_type::SIGNAL3
  });
  logger.log(signal{
    ._status = signal::transmission_type::RECEIVED,
    ._signal = signal::signal_type::SIGNAL5,
    ._debug_string = " This is a weird signal..."
  });
  logger.log(signal{
    ._status = signal::transmission_type::SENT,
    ._signal = signal::signal_type::SIGNAL1
  });

  logger.to_osstream(std::cout);
}
