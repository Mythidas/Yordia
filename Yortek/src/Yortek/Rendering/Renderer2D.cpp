#include "Yortek/Rendering/Renderer2D.h"
#include "Yortek/Core/Environment.h"
#include "Yortek/Rendering/RenderCommands.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Yortek::Rendering
{
	RenderData Renderer2D::s_quad_data;
	Unique<RenderCommands> Renderer2D::s_render_commands;

	void Renderer2D::_construct()
	{
		if (!_validate_api()) return;

		s_quad_data.buffer = RenderBuffer::Builder()
			.set_size(sizeof(Vertex) * RenderData::MAX_VERTICES)
			.set_usage(BufferUsage::Vertex)
			.set_rate(BufferRate::Dynamic)
			.build();

		s_quad_data.staging_buffer = new Vertex[RenderData::MAX_VERTICES];

		uint32_t indices[RenderData::MAX_INDICES]{};
		uint32_t offset = 0;
		for (size_t i = 0; i < RenderData::MAX_INDICES; i += 6)
		{
			indices[i + 0] = 0 + offset;
			indices[i + 1] = 1 + offset;
			indices[i + 2] = 2 + offset;

			indices[i + 3] = 2 + offset;
			indices[i + 4] = 3 + offset;
			indices[i + 5] = 0 + offset;

			offset += 4;
		}

		Shared<RenderBuffer> indexBuffer = RenderBuffer::Builder()
			.set_size(sizeof(indices))
			.set_usage(BufferUsage::Index)
			.set_rate(BufferRate::Static)
			.build();

		indexBuffer->set_data(indices, sizeof(indices), 0);

		s_quad_data.vertex_positions[0] = { 0.5f, 0.5f, 0.0f, 1.0f };
		s_quad_data.vertex_positions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_quad_data.vertex_positions[2] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_quad_data.vertex_positions[3] = { -0.5f, 0.5f, 0.0f, 1.0f };

		s_quad_data.texture_positions[0] = { 1.0f, 1.0f };
		s_quad_data.texture_positions[1] = { 1.0f, 0.0f };
		s_quad_data.texture_positions[2] = { 0.0f, 0.0f };
		s_quad_data.texture_positions[3] = { 0.0f, 1.0f };

		uint32_t whiteTextureData = 0xFFFFFFFF;
		Shared<Image> whiteTex = Image::Builder()
			.set_format(ImageFormat::RGBA8)
			.set_size({ 1, 1, 1 })
			.set_type(ImageType::e2D)
			.build();

		whiteTex->set_data(&whiteTextureData, sizeof(uint32_t));
		s_quad_data.texture_slots[0] = whiteTex;

		s_quad_data.camera_uniform = RenderBuffer::Builder()
			.set_binding(0)
			.set_rate(BufferRate::Dynamic)
			.set_size(sizeof(RenderData::CameraBuffer))
			.set_usage(BufferUsage::Uniform)
			.build();

		s_quad_data.pipeline = Shader::Builder()
			.set_vert_path("../Assets/Shaders/QuadShader.vert")
			.set_frag_path("../Assets/Shaders/QuadShader.frag")
			.set_vertex_buffer(s_quad_data.buffer)
			.set_index_buffer(indexBuffer)
			.set_render_buffers({ s_quad_data.camera_uniform })
			.set_attributes({ VertexAttribute::Float3, VertexAttribute::Float3, VertexAttribute::Float2, VertexAttribute::Float })
			.build();

		s_render_commands = RenderCommands::Builder().build();
		RenderCommands::enable_depth_testing(true);
	}

	void Renderer2D::_destruct()
	{
		if (!_validate_api()) return;

		delete[] s_quad_data.staging_buffer;
	}

	void Renderer2D::begin_frame(Camera& camera, const Transform& transform)
	{
		if (!_validate_api()) return;

		s_quad_data.camera = &camera;
		Transform transformCopy(transform);
		transformCopy.position.y *= -1;
		transformCopy.position.z *= -1;

		s_quad_data.camera_buffer.view = transformCopy.get_inverse_matrix();
		s_quad_data.camera_buffer.projection = camera.get_projection();
		s_quad_data.camera_uniform->set_data(&s_quad_data.camera_buffer, sizeof(RenderData::CameraBuffer), 0);

		RenderCommands::resize(camera.get_framebuffer()->get_size());
		//camera.get_framebuffer()->bind();
		RenderCommands::clear_color(camera.clear_color);

		_begin_batch();
	}

	void Renderer2D::end_frame()
	{
		if (!_validate_api()) return;

		_end_batch();
		//s_quad_data.camera->get_framebuffer()->unbind();
	}

	void Renderer2D::draw_quad(const Vector3& position, const Vector3& rotation, const Vector3& scale, const Color& color)
	{
		Matrix4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position))
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f))
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f))
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f))
			* glm::scale(glm::mat4(1.0f), glm::vec3(scale));

		draw_quad(transform, color, 0.0f);
	}

	void Renderer2D::draw_quad(const Vector3& position, const Vector3& rotation, const Vector3& scale, const Color& color, Shared<Image> texture)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position))
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f))
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f))
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f))
			* glm::scale(glm::mat4(1.0f), glm::vec3(scale));

		float texIndex = _get_texture_index(texture);
		draw_quad(transform, color, texIndex);
	}

	void Renderer2D::draw_quad(const Matrix4& transform, const Color& color, float texIndex)
	{
		draw_quad(transform, color, s_quad_data.texture_positions, texIndex);
	}

	void Renderer2D::draw_quad(const Matrix4& transform, const Color& color, Vector2 texCoords[4], float texIndex)
	{
		if (!_validate_api()) return;

		_check_batch();

		for (size_t i = 0; i < 4; i++)
		{
			s_quad_data.staging_buffer_ptr->position = glm::vec3(transform * s_quad_data.vertex_positions[i]);
			s_quad_data.staging_buffer_ptr->color = Vector3(color.r, color.g, color.b);
			s_quad_data.staging_buffer_ptr->texCoord = texCoords[i];
			s_quad_data.staging_buffer_ptr->texIndex = texIndex;
			s_quad_data.staging_buffer_ptr++;
		}

		s_quad_data.index_count += 6;
	}

	void Renderer2D::_check_batch()
	{
		if (s_quad_data.index_count >= RenderData::MAX_INDICES || s_quad_data.texture_slot_index == RenderData::MAX_TEXTURE_SLOTS)
		{
			_end_batch();
			_begin_batch();
		}
	}

	void Renderer2D::_begin_batch()
	{
		s_quad_data.staging_buffer_ptr = s_quad_data.staging_buffer;
		s_quad_data.index_count = 0;
		s_quad_data.texture_slot_index = 1;
	}

	void Renderer2D::_end_batch()
	{
		for (uint32_t i = 0; i < s_quad_data.texture_slot_index; i++)
		{
			s_quad_data.texture_slots[i]->bind(i);
		}

		size_t size = (uint8_t*)s_quad_data.staging_buffer_ptr - (uint8_t*)s_quad_data.staging_buffer;
		s_quad_data.buffer->set_data(s_quad_data.staging_buffer, size, 0);

		s_quad_data.pipeline->draw(s_quad_data.index_count);
	}

	float Renderer2D::_get_texture_index(Shared<Image> texture)
	{
		float texIndex = 0.0f;
		for (uint32_t i = 1; i < s_quad_data.texture_slot_index; i++)
		{
			if (*(float*)s_quad_data.texture_slots[i]->get_render_id() == *(float*)texture->get_render_id())
			{
				texIndex = (float)i;
				break;
			}
		}

		if (texIndex == 0.0f)
		{
			texIndex = (float)s_quad_data.texture_slot_index;
			s_quad_data.texture_slots[(size_t)texIndex] = texture;
			s_quad_data.texture_slot_index++;
		}

		return texIndex;
	}

	bool Renderer2D::_validate_api()
	{
		return Yortek::Environment::get_graphics_api() != GraphicsAPI::None;
	}
}