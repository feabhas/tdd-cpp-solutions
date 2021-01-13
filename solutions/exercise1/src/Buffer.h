#ifndef BUFFER_H
#define BUFFER_H

#include <array>
#include <optional>
#include <cstdint>

class Buffer
{
public:
  using buffer_t = std::uint8_t;
  enum class Status
  {
    Ok,
    Full
  };

  Buffer() = default;
  ~Buffer() = default;

  Status add(buffer_t value);
  std::optional<buffer_t> get();
  bool is_empty() const;
  unsigned size() const;
  unsigned capacity() const;
  void flush();

private:
  static constexpr unsigned sz = 16;
  unsigned read{};
  unsigned write{};
  unsigned num_items{};

  std::array<buffer_t, sz> buffer{};
};

#endif // BUFFER_H