#include "Yortek/Core/UUID.h"

#include <random>

namespace Yortek
{
  UUID::UUID()
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint64_t> dist(0, INVALID - 1);
    m_uuid = dist(gen);
  }

  UUID::UUID(uint64_t uuid)
    : m_uuid(uuid)
  {
  }

  bool UUID::valid() const
  {
    return m_uuid != INVALID;
  }
}