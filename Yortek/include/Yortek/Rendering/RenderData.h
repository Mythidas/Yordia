#pragma once

#include "Yortek/Rendering/Shader.h"
#include "Yortek/Rendering/RenderBuffer.h"
#include "Yortek/Rendering/Framebuffer.h"
#include "Yortek/Rendering/Image.h"
#include "Yortek/Rendering/Camera.h"
#include "Yortek/Math/include.h"

namespace Yortek::Rendering
{
	using namespace Math;

	struct Vertex
	{
		Vector3 position;
		Vector3 color;
		Vector2 texCoord;
		float texIndex;
	};

	struct RenderData
	{
		static const int MAX_QUADS = 100;
		static const int MAX_VERTICES = MAX_QUADS * 4;
		static const int MAX_INDICES = MAX_QUADS * 6;
		static const int MAX_TEXTURE_SLOTS = 32;

		Shared<Shader> pipeline;
		Shared<RenderBuffer> buffer;
		Vertex* staging_buffer{ nullptr };
		Vertex* staging_buffer_ptr{ nullptr };
		uint32_t index_count{ 0 };
		uint32_t texture_slot_index{ 1 };
		Shared<Image> texture_slots[MAX_TEXTURE_SLOTS];

		glm::vec4 vertex_positions[4]{};
		glm::vec2 texture_positions[4]{};

		Camera camera;
		struct CameraBuffer
		{
			glm::mat4 view{ 1.0f };
			glm::mat4 projection{ 1.0f };
		} camera_buffer;

		Shared<RenderBuffer> camera_uniform;
	};
}