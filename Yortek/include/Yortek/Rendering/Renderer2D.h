#pragma once

#include "Yortek/Core/Defines.h"
#include "Yortek/Math/include.h"
#include "Yortek/Rendering/Image.h"
#include "Yortek/Rendering/Framebuffer.h"
#include "Yortek/Rendering/RenderData.h"
#include "Yortek/Rendering/RenderData.h"
#include "Yortek/Rendering/Camera.h"

namespace Yortek::Rendering
{
	using namespace Math;

	class Renderer
	{
	public:
		static void begin_frame(const Camera& camera, const Transform& transform);
		static void end_frame();

		static void draw_quad(const Vector3& position, const Vector3& rotation, const Vector3& scale, const Vector3& color);
		static void draw_quad(const Vector3& position, const Vector3& rotation, const Vector3& scale, const Vector3& color, Shared<Image> texture);
		static void draw_quad(const Matrix4& transform, const Vector3& color, float textureID);
		static void draw_quad(const Matrix4& transform, const Vector3& color, Vector2 texCoords[4], float textureID);

	private:
		friend class Application;

		static void _construct();
		static void _destruct();
		static void _check_batch();
		static void _begin_batch();
		static void _end_batch();
		static float _get_texture_index(Shared<Image> texture);


	private:
		static RenderData s_quad_data;
	};
}