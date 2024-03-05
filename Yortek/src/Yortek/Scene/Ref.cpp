#include "Yortek/Scene/Ref.h"
#include "Yortek/Scene/Registry.h"

namespace Yortek::Scene
{
  bool RefHelper::is_ref_valid(const TypeID& id, const UUID& ent_id, Registry* reg)
  {

    return reg->has_component(id, reg->find_ent(ent_id));
  }

  void* RefHelper::get_ref_data(const TypeID& id, const UUID& ent_id, Registry* reg)
  {
    return reg->get_component(id, reg->find_ent(ent_id));
  }
}