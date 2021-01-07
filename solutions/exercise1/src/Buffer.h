#ifndef BUFFER_H
#define BUFFER_H

#include <array>
#include <optional>

class Buffer {
public:
  enum class Status { Ok, Full };

  Buffer()  = default;
  ~Buffer() = default;

  Status             add(int value);
  std::optional<int> get();
  bool               is_empty();
  unsigned           size();
  unsigned           capacity();
  void               flush();

private:
  static constexpr int sz = 8;
  unsigned             read{};
  unsigned             write{};
  unsigned             num_items{};

  std::array<int, sz> buffer{};
};

#endif // BUFFER_H