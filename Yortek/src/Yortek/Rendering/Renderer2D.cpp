#include "YTEngine/Graphics/Renderer.h"
#include "YTEngine/Core/Application.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Yor
{
	RenderData Renderer::s_quadData;
	Unique<RenderCommands> Renderer::s_renderCommands = nullptr;

	void Renderer::_construct()
	{
		s_quadData.buffer = RenderBuffer::Builder()
			.setSize(sizeof(Vertex) * RenderData::MAX_VERTICES)
			.setUsage(BufferUsage::Vertex)
			.setRate(BufferRate::Dynamic)
			.build();

		s_quadData.stagingBuffer = new Vertex[RenderData::MAX_VERTICES];

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
			.setSize(sizeof(indices))
			.setUsage(BufferUsage::Index)
			.setRate(BufferRate::Static)
			.build();

		indexBuffer->setData(indices, sizeof(indices), 0);

		s_quadData.vertexPositions[0] = { 0.5f, 0.5f, 0.0f, 1.0f };
		s_quadData.vertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_quadData.vertexPositions[2] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_quadData.vertexPositions[3] = { -0.5f, 0.5f, 0.0f, 1.0f };

		s_quadData.texturePositions[0] = { 1.0f, 1.0f };
		s_quadData.texturePositions[1] = { 1.0f, 0.0f };
		s_quadData.texturePositions[2] = { 0.0f, 0.0f };
		s_quadData.texturePositions[3] = { 0.0f, 1.0f };

		uint32_t whiteTextureData = 0xFFFFFFFF;
		Shared<Image> whiteTex = Image::Builder()
			.setFormat(ImageFormat::RGBA8)
			.setSize({ 1, 1, 1 })
			.setType(ImageType::e2D)
			.build();

		whiteTex->setData(&whiteTextureData, sizeof(uint32_t));
		s_quadData.textureSlots[0] = whiteTex;

		s_quadData.cameraUniform = RenderBuffer::Builder()
			.setBinding(0)
			.setRate(BufferRate::Dynamic)
			.setSize(sizeof(RenderData::CameraBuffer))
			.setUsage(BufferUsage::Uniform)
			.build();

		s_quadData.pipeline = GraphicsPipeline::Builder()
			.setVertPath("../Assets/Shaders/QuadShader.vert")
			.setFragPath("../Assets/Shaders/QuadShader.frag")
			.setVertexBuffer(s_quadData.buffer)
			.setIndexBuffer(indexBuffer)
			.setRenderBuffers({ s_quadData.cameraUniform })
			.setAttributes({ VertexAttribute::Float3, VertexAttribute::Float3, VertexAttribute::Float2, VertexAttribute::Float })
			.build();

		s_renderCommands = RenderCommands::Builder().build();
		RenderCommands::enableDepthTesting(true);
	}

	void Renderer::_destruct()
	{
		delete[] s_quadData.stagingBuffer;
	}

	void Renderer::beginFrame(Ref<Camera> camera, const Transform& transform)
	{
		s_quadData.camera = camera;
		Transform transformCopy(transform);
		transformCopy.position.y *= -1;
		transformCopy.position.z *= -1;

		s_quadData.cameraBuffer.view = transformCopy.getInverseMatrix();
		s_quadData.cameraBuffer.projection = camera->getProjection();
		s_quadData.cameraUniform->setData(&s_quadData.cameraBuffer, sizeof(RenderData::CameraBuffer), 0);

		RenderCommands::resize(camera->getSwapBuffer()->getSize().x, camera->getSwapBuffer()->getSize().y);
		camera->getSwapBuffer()->bind();
		RenderCommands::setClearColor(camera->clearColor.x, camera->clearColor.y, camera->clearColor.z);

		_beginBatch();
	}

	void Renderer::endFrame()
	{
		_endBatch();
		s_quadData.camera->getSwapBuffer()->Unbind();
	}

	void Renderer::drawQuad(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale, const glm::vec3& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position))
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(glm::vec3(1.0f, 0.0f, 0.0f)))
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(glm::vec3(0.0f, 1.0f, 0.0f)))
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(glm::vec3(0.0f, 0.0f, 1.0f)))
			* glm::scale(glm::mat4(1.0f), glm::vec3(scale));

		drawQuad(transform, color, 0.0f);
	}

	void Renderer::drawQuad(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale, const glm::vec3& color, Shared<Image> texture)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position))
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(glm::vec3(1.0f, 0.0f, 0.0f)))
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(glm::vec3(0.0f, 1.0f, 0.0f)))
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(glm::vec3(0.0f, 0.0f, 1.0f)))
			* glm::scale(glm::mat4(1.0f), glm::vec3(scale));

		float texIndex = _getTextureIndex(texture);
		drawQuad(transform, color, texIndex);
	}

	void Renderer::drawQuad(const glm::mat4& transform, const glm::vec3& color, float texIndex)
	{
		_checkBatch();

		for (size_t i = 0; i < 4; i++)
		{
			s_quadData.stagingBufferPtr->position = transform * s_quadData.vertexPositions[i];
			s_quadData.stagingBufferPtr->color = color;
			s_quadData.stagingBufferPtr->texCoord = s_quadData.texturePositions[i];
			s_quadData.stagingBufferPtr->texIndex = texIndex;
			s_quadData.stagingBufferPtr++;
		}

		s_quadData.indexCount += 6;
	}

	void Renderer::drawQuad(const glm::mat4& transform, const glm::vec3& color, glm::vec2 texCoords[4], float texIndex)
	{
		_checkBatch();

		for (size_t i = 0; i < 4; i++)
		{
			s_quadData.stagingBufferPtr->position = transform * s_quadData.vertexPositions[i];
			s_quadData.stagingBufferPtr->color = color;
			s_quadData.stagingBufferPtr->texCoord = texCoords[i];
			s_quadData.stagingBufferPtr->texIndex = texIndex;
			s_quadData.stagingBufferPtr++;
		}

		s_quadData.indexCount += 6;
	}

	void Renderer::_checkBatch()
	{
		if (s_quadData.indexCount >= RenderData::MAX_INDICES || s_quadData.textureSlotIndex == RenderData::MAX_TEXTURE_SLOTS)
		{
			_endBatch();
			_beginBatch();
		}
	}

	void Renderer::_beginBatch()
	{
		s_quadData.stagingBufferPtr = s_quadData.stagingBuffer;
		s_quadData.indexCount = 0;
		s_quadData.textureSlotIndex = 1;
	}

	void Renderer::_endBatch()
	{
		for (uint32_t i = 0; i < s_quadData.textureSlotIndex; i++)
		{
			s_quadData.textureSlots[i]->bind(i);
		}

		size_t size = (uint8_t*)s_quadData.stagingBufferPtr - (uint8_t*)s_quadData.stagingBuffer;
		s_quadData.buffer->setData(s_quadData.stagingBuffer, size, 0);

		s_quadData.pipeline->draw(s_quadData.indexCount);
	}

	float Renderer::_getTextureIndex(Shared<Image> texture)
	{
		float texIndex = 0.0f;
		for (uint32_t i = 1; i < s_quadData.textureSlotIndex; i++)
		{
			if (*(float*)s_quadData.textureSlots[i]->getRenderID() == *(float*)texture->getRenderID())
			{
				texIndex = (float)i;
				break;
			}
		}

		if (texIndex == 0.0f)
		{
			texIndex = (float)s_quadData.textureSlotIndex;
			s_quadData.textureSlots[(size_t)texIndex] = texture;
			s_quadData.textureSlotIndex++;
		}

		return texIndex;
	}
}