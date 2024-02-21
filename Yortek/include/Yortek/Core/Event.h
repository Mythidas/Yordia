#pragma once

#include "Yortek/Core/Defines.h"

#include <functional>

namespace Yortek
{
	template <typename... Args>
	class Event
	{
	private:
		typedef void(*Func)(Args...);

	public:
		void dispatch(Args... args)
		{
			for (auto callback : m_callbacks)
			{
				callback(args...);
			}
			
			for (auto it = m_listeners.begin(); it != m_listeners.end(); ++it)
			{
				if ((*it))
					(*it)->dispatch(args...);
				else
					it = m_listeners.erase(it);
			}
		}

		void listen(Func func)
		{
			m_callbacks.push_back(func);
		}

		void listen(Event<Args...>& e)
		{
			m_listeners.push_back(&e);
		}

		void deafen(Func func)
		{
			for (auto it = m_callbacks.begin(); it != m_callbacks.end(); ++it)
			{
				if ((*it) == func)
				{
					m_callbacks.erase(it);
					break;
				}
			}
		}

		void deafen(Event<Args...>& e)
		{
			for (auto it = m_listeners.begin(); it != m_listeners.end(); ++it)
			{
				if ((*it) == &e)
				{
					m_listeners.erase(it);
					break;
				}
			}
		}

		void operator +=(Func callback)
		{
			listen(callback);
		}

		void operator +=(Event<Args...>& e)
		{
			listen(e);
		}

		void operator -=(Func callback)
		{
			deafen(callback);
		}

		void operator -=(Event<Args...>& e)
		{
			deafen(e);
		}

	private:
		std::vector<Func> m_callbacks;
		std::vector<Event<Args...>*> m_listeners;
	};
}