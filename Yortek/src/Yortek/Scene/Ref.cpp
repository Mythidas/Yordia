#include "Yortek/Scene/Ref.h"
#include "Yortek/Scene/Registry.h"

namespace Yortek::Scene
{
  bool RefHelper::is_ref_valid(const TypeID& id, const UUID& ent_id, bool is_behavior, Registry* reg)
  {
    if (is_behavior)
      return reg->has_behavior(id, reg->find_ent(ent_id));
    else
      return reg->has_component(id, reg->find_ent(ent_id));
  }

  void* RefHelper::get_ref_data(const TypeID& id, const UUID& ent_id, bool is_behavior, Registry* reg)
  {
    if (is_behavior)
      return reg->get_behavior(id, reg->find_ent(ent_id));
    else
      return reg->get_component(id, reg->find_ent(ent_id));
  }
}