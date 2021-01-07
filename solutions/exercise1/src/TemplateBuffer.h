#ifndef TEMPLATEBUFFER_H
#define TEMPLATEBUFFER_H

#include <array>
#include <tuple>

template<typename T = int, unsigned sz = 8>
class Buffer {
public:
  enum class Status { Ok, Full, Empty };

  Buffer()  = default;
  ~Buffer() = default;

  Status                  add(int value);
  std::tuple<int, Status> get();
  bool                    is_empty();
  unsigned                size();
  unsigned                capacity();
  void                    flush();

private:
  unsigned read{};
  unsigned write{};
  unsigned num_items{};

  std::array<T, sz> buffer{};
};

template<typename T, unsigned sz>
typename Buffer<T, sz>::Status Buffer<T, sz>::add(int value)
{
  if (num_items == sz) {
    return Status::Full;
  }
  else {
    buffer[write] = value;

    ++num_items;
    ++write;
    if (write == sz) write = 0;

    return Status::Ok;
  }
}

template<typename T, unsigned sz>
std::tuple<int, typename Buffer<T, sz>::Status> Buffer<T, sz>::get()
{
  if (num_items == 0) {
    return std::make_tuple(0, Status::Empty);
  }
  else {
    int value = buffer[read];

    --num_items;
    ++read;
    if (read == sz) read = 0;

    return std::make_tuple(value, Status::Ok);
  }
}

template<typename T, unsigned sz>
bool Buffer<T, sz>::is_empty()
{
  return (num_items == 0);
}

template<typename T, unsigned sz>
unsigned Buffer<T, sz>::size()
{
  return num_items;
}

template<typename T, unsigned sz>
unsigned Buffer<T, sz>::capacity()
{
  return sz;
}

template<typename T, unsigned sz>
void Buffer<T, sz>::flush()
{
  read      = 0;
  write     = 0;
  num_items = 0;
}

#endif // TEMPLATEBUFFER_H