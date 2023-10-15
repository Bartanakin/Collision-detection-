#pragma once
#include "Geometrics/TransformableInterface.h"

namespace Barta{

	class BartaObjectInterface{
	public:
        virtual ~BartaObjectInterface() noexcept = default;

		virtual bool isToBeDeleted() const = 0;

		virtual const TransformableInterface& getTransformable() const = 0;

		virtual int getResourceId() const noexcept = 0;
	};
}
