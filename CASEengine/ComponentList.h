#pragma once

#include "Types.h"

namespace ECS {
	
	class ICompList {

	public:
		ICompList() = default;
		virtual ~ICompList() = default;
		virtual void Erase(const EntityID entity) {}
	};


	template<typename T>
	class CompList : public ICompList {
	public:
		CompList() = default;
		~CompList() = default;

		void Insert(const T& component)	{
			auto component = std::find_if(data.begin(), data.end(), [&](const T& c) == component.GetID());
		}
	};

}