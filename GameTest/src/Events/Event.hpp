#pragma once
#ifndef _EVENT_HPP
#define _EVENT_HPP
#include <string>

//*******************************************************************************************
//  Event
//*******************************************************************************************
/* This class is the base class for the Events

 */

namespace Engine
{
	template <typename T>
	class Event
	{
	public:
		Event() {};
		Event(T type, const std::string& name = "") : m_type(type), m_name(name) {}
		~Event() {};

		inline const T GetType() const { return m_type; }

		inline const std::string GetName() const { return m_name; }

		virtual bool IsHandled() const { return m_handled; }

	protected:
		T m_type;
		std::string m_name;
		bool m_handled = false;
	};
}
#endif