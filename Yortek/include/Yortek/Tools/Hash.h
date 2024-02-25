#pragma once

namespace Yortek::Tools
{
  template <typename T>
  class Hash
  {
  public:
    unsigned long long get_hash(const T& input)
    {
      return 0;
    }

    unsigned long long operator()(const T& input)
    {
      return get_hash(input);
    }
  };

  template <>
  class Hash<const char*>
  {
  public:
    // Murmur 64bit
    unsigned long long get_hash(const char* input)
    {
      unsigned long long hash(525201411107845655ull);
      for (; *input; ++input)
      {
        hash ^= *input;
        hash *= 0x5bd1e9955bd1e995;
        hash ^= hash >> 47;
      }
      return hash;
    }

    unsigned long long operator()(const char* input)
    {
      return get_hash(input);
    }
  };
}