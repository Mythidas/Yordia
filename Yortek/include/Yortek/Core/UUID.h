#pragma once

#include <xhash>

namespace Yortek
{
  class UUID
  {
  public:
    inline static const uint64_t INVALID = UINT64_MAX;

  public:
    UUID();
    UUID(uint64_t uuid);

    bool valid() const;

  public:
    bool operator==(const UUID& rhs) const
    {
      return m_uuid == rhs.m_uuid;
    }

    bool operator!=(const UUID& rhs) const
    {
      return m_uuid != rhs.m_uuid;
    }

    operator uint64_t() const
    {
      return m_uuid;
    }

  private:
    uint64_t m_uuid;
  };
}

namespace std
{
  template<>
  struct hash<Yortek::UUID>
  {
    size_t operator()(const Yortek::UUID& rhs) const
    {
      return hash<uint64_t>()(uint64_t(rhs));
    }
  };
}