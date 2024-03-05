#pragma once

#include "Yortek/Scene/JobScheduler.h"

namespace Yortek::Jobs
{
  class Scene2DRenderJob : public Scene::IJob
  {
  public:
    virtual void on_update(Scene::Registry& registry) override;
  };
  YOR_REGISTER_JOB(Scene2DRenderJob)
}