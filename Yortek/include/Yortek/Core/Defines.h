#pragma once

#include <memory>
#include <functional>

#define YOR_BIND_FNC(fn)  [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Yortek
{
	// Smart Pointers
	template <typename T>
	using Unique = std::unique_ptr<T>;

	template <typename T, typename... Args>
	Unique<T> CreateUnique(Args ...args)
	{
		return std::make_unique<T>(args...);
	}

	template <typename T>
	using Shared = std::shared_ptr<T>;

	template <typename T, typename ...Args>
	Shared<T> CreateShared(Args... args)
	{
		return std::make_shared<T>(args...);
	}

	template <typename T>
	using WeakShared = std::weak_ptr<T>;
}