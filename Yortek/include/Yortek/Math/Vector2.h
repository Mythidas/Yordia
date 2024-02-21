#pragma once

#include <glm/glm.hpp>

namespace Yortek::Math
{
	template <typename T>
	struct TVector2;

	using Vector2 = TVector2<float>;
	using IVector2 = TVector2<int>;
	using UVector2 = TVector2<unsigned int>;

	template <typename T>
	struct TVector2
	{
	public:
		TVector2() = default;
		TVector2(T value)
		{
			x = value;
			y = value;
		}
		TVector2(T _x, T _y)
		{
			x = _x;
			y = _y;
		}
		TVector2(const glm::vec2& gvec2)
		{
			x = static_cast<T>(gvec2.x);
			y = static_cast<T>(gvec2.y);
		}
		TVector2(const glm::ivec2& gvec2)
		{
			x = static_cast<T>(gvec2.x);
			y = static_cast<T>(gvec2.y);
		}
		TVector2(const glm::uvec2& gvec2)
		{
			x = static_cast<T>(gvec2.x);
			y = static_cast<T>(gvec2.y);
		}

		union { T x, r; };
		union { T y, g; };

	public:
		// Scalar Ops
		TVector2<T> operator+(const T& rhs) const;
		TVector2<T> operator-(const T& rhs) const;
		TVector2<T> operator*(const T& rhs) const;
		TVector2<T> operator/(const T& rhs) const;

		TVector2<T>& operator+=(const T& rhs);
		TVector2<T>& operator-=(const T& rhs);
		TVector2<T>& operator*=(const T& rhs);
		TVector2<T>& operator/=(const T& rhs);

		// TVector2<T> Ops
		TVector2<T> operator+(const TVector2<T>& rhs) const;
		TVector2<T> operator-(const TVector2<T>& rhs) const;
		TVector2<T> operator*(const TVector2<T>& rhs) const;
		TVector2<T> operator/(const TVector2<T>& rhs) const;

		TVector2<T>& operator+=(const TVector2<T>& rhs);
		TVector2<T>& operator-=(const TVector2<T>& rhs);
		TVector2<T>& operator*=(const TVector2<T>& rhs);
		TVector2<T>& operator/=(const TVector2<T>& rhs);

		// Boolean Ops
		bool operator==(const TVector2<T>& rhs) const;
		bool operator!=(const TVector2<T>& rhs) const;

		T operator[](int index) const
		{
			if (index == 0)
				return x;
			if (index == 1)
				return y;
		}

		operator glm::vec2() const
		{
			return glm::vec2(x, y);
		}
		operator glm::ivec2() const
		{
			return glm::ivec2(x, y);
		}
		operator glm::uvec2() const
		{
			return glm::uvec2(x, y);
		}
	};

	// Scalar Ops

	template <typename T>
	inline TVector2<T> TVector2<T>::operator+(const T& rhs) const
	{
		return TVector2<T>(x + rhs, y + rhs);
	}
	template <typename T>
	inline TVector2<T> TVector2<T>::operator-(const T& rhs) const
	{
		return TVector2<T>(x - rhs, y - rhs);
	}
	template <typename T>
	inline TVector2<T> TVector2<T>::operator*(const T& rhs) const
	{
		return TVector2<T>(x * rhs, y * rhs);
	}
	template <typename T>
	inline TVector2<T> TVector2<T>::operator/(const T& rhs) const
	{
		return TVector2<T>(x / rhs, y / rhs);
	}
	template <typename T>
	inline TVector2<T>& TVector2<T>::operator+=(const T& rhs)
	{
		x += rhs; y += rhs;
		return *this;
	}
	template <typename T>
	inline TVector2<T>& TVector2<T>::operator-=(const T& rhs)
	{
		x -= rhs; y -= rhs;
		return *this;
	}
	template <typename T>
	inline TVector2<T>& TVector2<T>::operator*=(const T& rhs)
	{
		x *= rhs; y *= rhs;
		return *this;
	}
	template <typename T>
	inline TVector2<T>& TVector2<T>::operator/=(const T& rhs)
	{
		x /= rhs; y /= rhs;
		return *this;
	}

	// TVector2<T> Ops

	template <typename T>
	inline TVector2<T> TVector2<T>::operator+(const TVector2<T>& rhs) const
	{
		return TVector2<T>(x + rhs.x, y + rhs.y);
	}
	template <typename T>
	inline TVector2<T> TVector2<T>::operator-(const TVector2<T>& rhs) const
	{
		return TVector2<T>(x - rhs.x, y - rhs.y);
	}
	template <typename T>
	inline TVector2<T> TVector2<T>::operator*(const TVector2<T>& rhs) const
	{
		return TVector2<T>(x * rhs.x, y * rhs.y);
	}
	template <typename T>
	inline TVector2<T> TVector2<T>::operator/(const TVector2<T>& rhs) const
	{
		return TVector2<T>(x / rhs.x, y / rhs.y);
	}
	template <typename T>
	inline TVector2<T>& TVector2<T>::operator+=(const TVector2<T>& rhs)
	{
		x += rhs.x; y += rhs.y;
		return *this;
	}
	template <typename T>
	inline TVector2<T>& TVector2<T>::operator-=(const TVector2<T>& rhs)
	{
		x -= rhs.x; y -= rhs.y;
		return *this;
	}
	template <typename T>
	inline TVector2<T>& TVector2<T>::operator*=(const TVector2<T>& rhs)
	{
		x *= rhs.x; y *= rhs.y;
		return *this;
	}
	template <typename T>
	inline TVector2<T>& TVector2<T>::operator/=(const TVector2<T>& rhs)
	{
		x /= rhs.x; y /= rhs.y;
		return *this;
	}

	// Boolean Ops
	template<typename T>
	inline bool TVector2<T>::operator==(const TVector2<T>& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}
	template<typename T>
	inline bool TVector2<T>::operator!=(const TVector2<T>& rhs) const
	{
		return x != rhs.x && y != rhs.y;
	}
}