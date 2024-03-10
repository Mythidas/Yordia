#pragma once

#include "Yortek/Core/Defines.h"
#include "Yortek/Scene/IJob.h"
#include "Yortek/Tools/Singleton.h"
#include "Yortek/Reflection/Type.h"

#include <unordered_map>

// Jobs need to be #include in a source file to be compiled and registered
// This creates a simple module system where only jobs included are registered
// Could be used to let users choose what jobs are registered and run

namespace
{
#define YOR_REGISTER_JOB(JobName) static inline bool JobName##_reg_ = Yortek::Scene::JobScheduler::instance().register_job<JobName>();
}

namespace Yortek::Scene
{
  class JobScheduler : public Tools::Singleton<JobScheduler, true>
  {
  public:
    template <typename T>
    bool register_job();
    void dispatch_jobs(Registry& registry);

  private:
    std::unordered_map<TypeID, Shared<IJob>> m_jobs;
  };

  template<typename T>
  inline bool JobScheduler::register_job()
  {
    static_assert(!std::is_convertible_v<T, IJob>, "T must be a IJob!");
    if (!m_jobs.contains(Reflection::Type<T>().id()))
      m_jobs[Reflection::Type<T>().id()] = CreateShared<T>();
    return true;
  }
}