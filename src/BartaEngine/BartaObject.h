#pragma once
#include "Geometrics/TransformableInterface.h"
#include "Graphics/Resource.h"

namespace Barta{

	class BartaObjectInterface{
	public:
        virtual ~BartaObjectInterface() noexcept = default;

		virtual bool isToBeDeleted() const = 0;

		virtual const TransformableInterface& getTransformable() const = 0;

		virtual Resource getResourceId() const noexcept = 0;
	};
}
