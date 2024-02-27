#pragma once

#include "Yortek/Tools/Hash.h"

#include <type_traits>
#include <string>

namespace Yortek
{
	using TypeID = uint64_t;
	static const TypeID INVALID_TYPE = UINT64_MAX;

	enum class TypeRef : int
	{
		Unknown = 0,
		Bool,
		String,
		Int32,
		Int64,
		UInt32,
		UInt64,
		Float,
		Double
	};
}

namespace Yortek::Reflection
{
	template<typename T>
	class Type
	{
	public:
		std::string name() const
		{
			std::string debug = typeid(T).name();
			size_t offset = debug.find_last_of(':') + 1;
			if (offset == 0)
				offset = debug.find_last_of(' ') + 1;
			return debug.substr(offset);
		}

		std::string debug_name() const
		{
			return typeid(T).name();
		}

		TypeID id() const
		{
			return Tools::Hash<const char*>()(typeid(T).name());
		}

		TypeRef ref() const
		{
			if constexpr (std::is_same_v<T, std::string>)
				return TypeRef::String;
			else if constexpr (std::is_same_v<T, bool>)
				return TypeRef::Bool;
			else if constexpr (std::is_same_v<T, int>)
				return TypeRef::Int32;
			else if constexpr (std::is_same_v<T, long long>)
				return TypeRef::Int64;
			else if constexpr (std::is_same_v<T, unsigned int>)
				return TypeRef::UInt32;
			else if constexpr (std::is_same_v<T, unsigned long long>)
				return TypeRef::UInt64;
			else if constexpr (std::is_same_v<T, float>)
				return TypeRef::Float;
			else if constexpr (std::is_same_v<T, double>)
				return TypeRef::Double;

			return TypeRef::Unknown;
		}
	};
}