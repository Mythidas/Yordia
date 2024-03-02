#pragma once

#include "Yortek/Core/Defines.h"
#include "Yortek/Scene/IJob.h"
#include "Yortek/Tools/Singleton.h"

#include <vector>

namespace Yortek::Scene
{
#define YOR_REGISTER_JOB(JobName) struct JobName##_register \
{ JobName##_register() { Scene::JobScheduler::instance().register_job<JobName>(); } }; \
JobName##_register JobName##_reg;

  class JobScheduler : public Tools::Singleton<JobScheduler, true>
  {
  public:
    template <typename T>
    void register_job();
    void dispatch_jobs(Registry& registry);

  private:
    std::vector<Shared<IJob>> m_jobs;
  };

  template<typename T>
  inline void JobScheduler::register_job()
  {
    m_jobs.push_back(CreateShared<T>());
    static_assert(!std::is_convertible_v<T, IJob>, "T must be a IJob!");
  }
}