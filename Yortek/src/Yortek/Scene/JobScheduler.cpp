#include "Yortek/Scene/JobScheduler.h"
#include "Yortek/Scene/Registry.h"

namespace Yortek::Scene
{
  void JobScheduler::dispatch_jobs(Registry& registry)
  {
    for (auto& job : m_jobs)
    {
      job.second->on_update(registry);
    }
  }
}