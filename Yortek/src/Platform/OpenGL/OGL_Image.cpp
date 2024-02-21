#include "Platform/OpenGL/OGL_Image.h"
#include "Yortek/Debug/Log.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace Yortek::Rendering::OGL
{
	namespace Utils
	{
		static GLenum TypeToGL(ImageType type)
		{
			switch (type)
			{
			case ImageType::e1D: return GL_TEXTURE_1D;
			case ImageType::e2D: return GL_TEXTURE_2D;
			case ImageType::e3D: return GL_TEXTURE_3D;
			default: return GL_TEXTURE_2D;
			}
		}

		static GLenum WrapToGL(ImageWrap wrap)
		{
			switch (wrap)
			{
			case ImageWrap::Repeat: return GL_REPEAT;
			case ImageWrap::ClampToEdge: return GL_CLAMP_TO_EDGE;
			case ImageWrap::MirroredRepeat: return GL_MIRRORED_REPEAT;
			}
		}

		static GLenum TilingToGL(ImageTiling tiling)
		{
			switch (tiling)
			{
			case ImageTiling::Linear: return GL_LINEAR;
			case ImageTiling::Nearest: return GL_NEAREST;
			}
		}

		static GLenum FormatToGL(ImageFormat format)
		{
			switch (format)
			{
			case ImageFormat::R8: return GL_RED;
			case ImageFormat::RGBA8: return GL_RGBA;
			case ImageFormat::RGBA32F: return GL_RGBA;
			}
		}

		static GLenum FormatToGLInternal(ImageFormat format)
		{
			switch (format)
			{
			case ImageFormat::R8: return GL_R8;
			case ImageFormat::RGBA8: return GL_RGBA8;
			case ImageFormat::RGBA32F: return GL_RGBA32F;
			}
		}

		static uint32_t FormatSize(ImageFormat format)
		{
			switch (format)
			{
			case ImageFormat::R8: return 1;
			case ImageFormat::RGBA8: return 4;
			case ImageFormat::RGBA32F: return 4 * 4;
			}

			return 0;
		}

		static void SetGLImage(const Image::Builder& builder)
		{
			if (builder.type == ImageType::e1D)
			{
				glTexImage1D(GL_TEXTURE_1D, 0, FormatToGL(builder.format),
					builder.size.x, 0, FormatToGL(builder.format), GL_UNSIGNED_BYTE, nullptr);
			}
			else if (builder.type == ImageType::e2D)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, FormatToGL(builder.format),
					builder.size.x, builder.size.y, 0, FormatToGL(builder.format), GL_UNSIGNED_BYTE, nullptr);
			}
			else if (builder.type == ImageType::e3D)
			{
				glTexImage3D(GL_TEXTURE_3D, 0, FormatToGL(builder.format),
					builder.size.x, builder.size.y, builder.size.z, 0, FormatToGL(builder.format), GL_UNSIGNED_BYTE, nullptr);
			}

			glTexParameteri(Utils::TypeToGL(builder.type), GL_TEXTURE_WRAP_S, Utils::WrapToGL(builder.wrap));
			glTexParameteri(Utils::TypeToGL(builder.type), GL_TEXTURE_WRAP_T, Utils::WrapToGL(builder.wrap));
			glTexParameteri(Utils::TypeToGL(builder.type), GL_TEXTURE_WRAP_R, Utils::WrapToGL(builder.wrap));

			glTexParameteri(Utils::TypeToGL(builder.type), GL_TEXTURE_MIN_FILTER, Utils::TilingToGL(builder.tiling));
			glTexParameteri(Utils::TypeToGL(builder.type), GL_TEXTURE_MAG_FILTER, Utils::TilingToGL(builder.tiling));
		}

		static void SetGLImageData(const Image::Builder& builder, void* data)
		{
			if (builder.type == ImageType::e1D)
			{
				glTexSubImage1D(GL_TEXTURE_1D, 0, 0, builder.size.x, FormatToGL(builder.format), GL_UNSIGNED_BYTE, data);
			}
			else if (builder.type == ImageType::e2D)
			{
				glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, builder.size.x, builder.size.y, FormatToGL(builder.format), GL_UNSIGNED_BYTE, data);
			}
			else if (builder.type == ImageType::e3D)
			{
				glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0, builder.size.x, builder.size.y, builder.size.z, FormatToGL(builder.format), GL_UNSIGNED_BYTE, data);
			}
		}
	}

	OGL_Image::OGL_Image(const Builder& builder)
		: m_render_id(0)
	{
		glGenTextures(1, &m_render_id);
		glBindTexture(Utils::TypeToGL(builder.type), m_render_id);
		Utils::SetGLImage(builder);
	}

	void OGL_Image::bind(uint32_t slot) const
	{
		glBindTexture(Utils::TypeToGL(m_builder.type), m_render_id);
		glBindTextureUnit(slot, m_render_id);
	}

	void OGL_Image::set_data(void* data, size_t size)
	{
		uint32_t imageSize = (m_builder.size.x * m_builder.size.y * m_builder.size.z) * Utils::FormatSize(m_builder.format);
		if (size != static_cast<size_t>(imageSize))
		{
			Debug::Log::error("Size does not match Image Size!");
			return;
		}

		glBindTexture(Utils::TypeToGL(m_builder.type), m_render_id);
		Utils::SetGLImageData(m_builder, data);
	}

	// Only supports 2D or 1D texture data
	void OGL_Image::load_data(const Tools::Path& path)
	{
		int nrChannels, width, height;
		stbi_set_flip_vertically_on_load(m_builder.flipped);
		unsigned char* data = stbi_load(path.to_string().c_str(), &width, &height, &nrChannels, 0);
		
		glBindTexture(Utils::TypeToGL(m_builder.type), m_render_id);
		Utils::SetGLImage(m_builder.set_size({ width, height, 1 }));
		Utils::SetGLImageData(m_builder, data);

		stbi_image_free(data);
	}

	void* OGL_Image::get_render_id() const
	{
		return reinterpret_cast<void*>((uint32_t)m_render_id);
	}
}