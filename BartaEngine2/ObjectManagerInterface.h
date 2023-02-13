#pragma once
#include"BartaObject.h"
#include<list>

namespace Barta{
	class ObjectManagerInterface{
	public:
		using ObjectList = std::list<BartaObjectInterface*>;

		virtual ~ObjectManagerInterface() = default;

		virtual void addNewObject( BartaObjectInterface* const newObject ) = 0;

		virtual ObjectList getList() const = 0;

		virtual void reduceDeleted() = 0;
	};
}

