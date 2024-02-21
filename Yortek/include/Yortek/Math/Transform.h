#pragma once

#include "Yortek/Math/Vector3.h"
#include "Yortek/Math/Matrix4.h"

namespace Yortek::Math
{
  struct Transform
  {
    Vector3 position{ 0.0f };
    Vector3 rotation{ 0.0f };
    Vector3 scale{ 1.0f };

    Matrix4 get_matrix() const;
    Matrix4 get_inverse_matrix() const;

    Vector3 forward() const;
    Vector3 back() const;
    Vector3 right() const;
    Vector3 left() const;
    Vector3 up() const;
    Vector3 down() const;
  };
}