#include "Buffer.h"

Buffer::Status Buffer::add(Buffer::buffer_t value)
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

std::optional<Buffer::buffer_t> Buffer::get()
{
  if (num_items == 0) {
    return std::nullopt;
  }
  else {
    buffer_t value = buffer[read];

    --num_items;
    ++read;
    if (read == sz) read = 0;

    return std::make_optional<buffer_t>(value);
  }
}

bool Buffer::is_empty() const
{
  return (num_items == 0);
}

unsigned Buffer::size() const
{
  return num_items;
}

unsigned Buffer::capacity() const
{
  return sz;
}

void Buffer::flush()
{
  read      = 0;
  write     = 0;
  num_items = 0;
}
