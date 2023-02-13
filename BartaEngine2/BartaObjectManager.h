#pragma once
#include<list>
#include"ObjectManagerInterface.h"

namespace Barta{
	class BartaObjectManager : public ObjectManagerInterface{
	public:
		BartaObjectManager() = default;

		virtual ~BartaObjectManager();

		virtual void addNewObject( BartaObjectInterface* const newObject ) override;
		
		virtual ObjectList getList() const override;
		
		virtual void reduceDeleted() override;

	private:
		ObjectList objectList;
	};
}

