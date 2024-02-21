#pragma once

#include <glm/glm.hpp>

namespace Yortek::Math
{
	template <typename T>
	struct TVector4;

	using Vector4 = TVector4<float>;
	using IVector4 = TVector4<int>;
	using UVector4 = TVector4<unsigned int>;

	template <typename T>
	struct TVector4
	{
	public:
		TVector4() = default;
		TVector4(T value)
		{
			x = value;
			y = value;
			z = value;
			w = value;
		}
		TVector4(T _x, T _y, T _z, T _w)
		{
			x = _x;
			y = _y;
			z = _z;
			w = _w;
		}
		TVector4(const glm::vec4& gvec3)
		{
			x = static_cast<T>(gvec3.x);
			y = static_cast<T>(gvec3.y);
			z = static_cast<T>(gvec3.z);
			w = static_cast<T>(gvec3.w);
		}
		TVector4(const glm::ivec4& gvec3)
		{
			x = static_cast<T>(gvec3.x);
			y = static_cast<T>(gvec3.y);
			z = static_cast<T>(gvec3.z);
			w = static_cast<T>(gvec3.w);
		}
		TVector4(const glm::uvec4& gvec3)
		{
			x = static_cast<T>(gvec3.x);
			y = static_cast<T>(gvec3.y);
			z = static_cast<T>(gvec3.z);
			w = static_cast<T>(gvec3.w);
		}

		union { T x, r; };
		union { T y, g; };
		union { T z, b; };
		union { T w, a; };

	public:
		// Scalar Ops
		TVector4<T> operator+(const T& rhs) const;
		TVector4<T> operator-(const T& rhs) const;
		TVector4<T> operator*(const T& rhs) const;
		TVector4<T> operator/(const T& rhs) const;

		TVector4<T>& operator+=(const T& rhs);
		TVector4<T>& operator-=(const T& rhs);
		TVector4<T>& operator*=(const T& rhs);
		TVector4<T>& operator/=(const T& rhs);

		// TVector4<T> Ops
		TVector4<T> operator+(const TVector4<T>& rhs) const;
		TVector4<T> operator-(const TVector4<T>& rhs) const;
		TVector4<T> operator*(const TVector4<T>& rhs) const;
		TVector4<T> operator/(const TVector4<T>& rhs) const;

		TVector4<T>& operator+=(const TVector4<T>& rhs);
		TVector4<T>& operator-=(const TVector4<T>& rhs);
		TVector4<T>& operator*=(const TVector4<T>& rhs);
		TVector4<T>& operator/=(const TVector4<T>& rhs);

		T operator[](int index) const
		{
			static_assert(index > 3 || index < 0, "Index out of range!");

			if (index == 0)
				return x;
			if (index == 1)
				return y;
			if (index == 2)
				return z;
			if (index == 3)
				return w;
		}

		operator glm::vec4() const
		{
			return glm::vec4(x, y, z, w);
		}
		operator glm::ivec4() const
		{
			return glm::ivec4(x, y, z, w);
		}
		operator glm::uvec4() const
		{
			return glm::uvec4(x, y, z, w);
		}
	};

	// Scalar Ops

	template <typename T>
	inline TVector4<T> TVector4<T>::operator+(const T& rhs) const
	{
		return TVector4<T>(x + rhs, y + rhs, z + rhs, w + rhs);
	}
	template <typename T>
	inline TVector4<T> TVector4<T>::operator-(const T& rhs) const
	{
		return TVector4<T>(x - rhs, y - rhs, z - rhs, w - rhs);
	}
	template <typename T>
	inline TVector4<T> TVector4<T>::operator*(const T& rhs) const
	{
		return TVector4<T>(x * rhs, y * rhs, z * rhs, w * rhs);
	}
	template <typename T>
	inline TVector4<T> TVector4<T>::operator/(const T& rhs) const
	{
		return TVector4<T>(x / rhs, y / rhs, z / rhs, w / rhs);
	}
	template <typename T>
	inline TVector4<T>& TVector4<T>::operator+=(const T& rhs)
	{
		x += rhs; y += rhs; z += rhs; w += rhs;
		return *this;
	}
	template <typename T>
	inline TVector4<T>& TVector4<T>::operator-=(const T& rhs)
	{
		x -= rhs; y -= rhs; z -= rhs; w -= rhs;
		return *this;
	}
	template <typename T>
	inline TVector4<T>& TVector4<T>::operator*=(const T& rhs)
	{
		x *= rhs; y *= rhs; z *= rhs; w *= rhs;
		return *this;
	}
	template <typename T>
	inline TVector4<T>& TVector4<T>::operator/=(const T& rhs)
	{
		x /= rhs; y /= rhs; z /= rhs; w /= rhs;
		return *this;
	}

	// TVector4<T> Ops

	template <typename T>
	inline TVector4<T> TVector4<T>::operator+(const TVector4<T>& rhs) const
	{
		return TVector4<T>(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
	}
	template <typename T>
	inline TVector4<T> TVector4<T>::operator-(const TVector4<T>& rhs) const
	{
		return TVector4<T>(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
	}
	template <typename T>
	inline TVector4<T> TVector4<T>::operator*(const TVector4<T>& rhs) const
	{
		return TVector4<T>(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
	}
	template <typename T>
	inline TVector4<T> TVector4<T>::operator/(const TVector4<T>& rhs) const
	{
		return TVector4<T>(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
	}
	template <typename T>
	inline TVector4<T>& TVector4<T>::operator+=(const TVector4<T>& rhs)
	{
		x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w;
		return *this;
	}
	template <typename T>
	inline TVector4<T>& TVector4<T>::operator-=(const TVector4<T>& rhs)
	{
		x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w;
		return *this;
	}
	template <typename T>
	inline TVector4<T>& TVector4<T>::operator*=(const TVector4<T>& rhs)
	{
		x *= rhs.x; y *= rhs.y; z *= rhs.z; w *= rhs.w;
		return *this;
	}
	template <typename T>
	inline TVector4<T>& TVector4<T>::operator/=(const TVector4<T>& rhs)
	{
		x /= rhs.x; y /= rhs.y; z /= rhs.z; w /= rhs.w;
		return *this;
	}
}