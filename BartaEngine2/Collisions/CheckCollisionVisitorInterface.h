#pragma once

namespace Barta{
	class CheckCollisionVisitorInterface{
	public:
		CheckCollisionVisitorInterface() = default;
		virtual ~CheckCollisionVisitorInterface() = default;

		virtual bool checkStaticCollision() const = 0;

		virtual bool checkDynamicCollision() const = 0;
	};
}
