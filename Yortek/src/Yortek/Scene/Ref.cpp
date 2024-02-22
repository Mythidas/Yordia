#include "Yortek/Scene/Ref.h"

namespace Yortek::Scene
{
  bool RefHelper::is_ref_valid(const TypeID& id, const UUID& ent_id)
  {
    return false;
  }

  void* RefHelper::get_ref_data(const TypeID& id, const UUID& ent_id)
  {
    return nullptr;
  }
}