#pragma once

#include "Yortek/Core/Defines.h"
#include "Yortek/Math/include.h"
#include "Yortek/Rendering/Image.h"
#include "Yortek/Rendering/Framebuffer.h"
#include "Yortek/Rendering/RenderData.h"
#include "Yortek/Rendering/CameraInfo.h"
#include "Yortek/Rendering/Color.h"
#include "Yortek/Rendering/RenderCommands.h"
#include "Yortek/Components/Transform.h"

namespace Yortek::Rendering
{
	using namespace Math;

	class Renderer2D
	{
	public:
		static void begin_frame(CameraInfo& camera, const Components::Transform& transform);
		static void end_frame();

		static void draw_quad(const Vector3& position, const Vector3& rotation, const Vector3& scale, const Color& color);
		static void draw_quad(const Vector3& position, const Vector3& rotation, const Vector3& scale, const Color& color, Shared<Image> texture);
		static void draw_quad(const Matrix4& transform, const Color& color, float textureID);
		static void draw_quad(const Matrix4& transform, const Color& color, Vector2 texCoords[4], float textureID);

	private:
		friend class Application;

		static void _construct();
		static void _destruct();
		static void _check_batch();
		static void _begin_batch();
		static void _end_batch();
		static float _get_texture_index(Shared<Image> texture);
		static bool _validate_api();


	private:
		static RenderData s_quad_data;
		static Unique<RenderCommands> s_render_commands;
	};
}