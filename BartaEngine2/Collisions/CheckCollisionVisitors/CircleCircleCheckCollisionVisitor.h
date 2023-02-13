#pragma once
#include"../CheckCollisionVisitorInterface.h"
#include"../../BartaShapes/Circle.h"

namespace Barta{
	class CircleCircleCheckCollisionVisitor : public CheckCollisionVisitorInterface{
	public:
		CircleCircleCheckCollisionVisitor(
			const Circle& circle1,
			const Circle& circle2
		);
		virtual ~CircleCircleCheckCollisionVisitor();

		virtual bool checkStaticCollision() const override;
		
		virtual bool checkDynamicCollision() const override;

	private:
		const Circle circle1;
		const Circle circle2;
	};
}

