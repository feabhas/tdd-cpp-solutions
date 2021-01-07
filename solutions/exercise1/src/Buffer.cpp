#include "Buffer.h"

Buffer::Status Buffer::add(int value)
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

std::optional<int> Buffer::get()
{
  if (num_items == 0) {
    return std::nullopt;
  }
  else {
    int value = buffer[read];

    --num_items;
    ++read;
    if (read == sz) read = 0;

    return std::make_optional<int>(value);
  }
}

bool Buffer::is_empty()
{
  return (num_items == 0);
}

unsigned Buffer::size()
{
  return num_items;
}

unsigned Buffer::capacity()
{
  return sz;
}

void Buffer::flush()
{
  read      = 0;
  write     = 0;
  num_items = 0;
}
