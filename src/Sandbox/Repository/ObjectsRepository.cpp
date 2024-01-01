//
// Created by barta on 28/12/2023.
//

#include "ObjectsRepository.h"
#include "Graphics/SpriteBuilder/RectangleWithColorsSpriteBuilder.h"
ObjectsRepository::ObjectsRepository(
    ListManager &listManager,
    Barta::ObjectManagerInterface &objectManager
) noexcept
    : listManager(listManager),
      objectManager(objectManager)
{}
void ObjectsRepository::addWalls() {

    auto merger = Barta::SpriteMerger();
    auto builder = Barta::RectangleWithColorsSpriteBuilder();

    auto horizontalAABB = Barta::AABB({0.f, 0.f}, {700.f, 100.f});
    builder.setVertex1({0.f, 0.f});
    builder.setSize(horizontalAABB.getWidthHeight());
    builder.setAllColors(Wall::WALL_COLOR);
    merger.addRectanglewithColors(builder.build());
    auto horizontalWallResource = merger.merge(false);

    auto verticalAABB = Barta::AABB({0.f, 0.f}, {100.f, 500.f});
    builder.setVertex1({0.f, 0.f});
    builder.setSize(verticalAABB.getWidthHeight());
    builder.setAllColors(Wall::WALL_COLOR);
    merger.addRectanglewithColors(builder.build());
    auto verticalWallResource = merger.merge(false);

    auto upperBound = new Wall(
        {0.f, 0.f},
        horizontalAABB,
        horizontalWallResource
    );
    this->listManager.addObject(upperBound);
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(upperBound));
    this->objectManager.addNewObject(upperBound);

    auto rightBound = new Wall(
        {600.f, 100.f},
        verticalAABB,
        verticalWallResource
    );
    this->listManager.addObject(rightBound);
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(rightBound));
    this->objectManager.addNewObject(rightBound);

    auto bottomBound = new Wall(
        {0.f, 600.f},
        horizontalAABB,
        horizontalWallResource
    );
    this->listManager.addObject(bottomBound);
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(bottomBound));
    this->objectManager.addNewObject(bottomBound);

    auto leftBound = new Wall(
        {0.f, 100.f},
        verticalAABB,
        verticalWallResource
    );
    this->listManager.addObject(leftBound);
    this->objectManager.addDynamicsObject(static_cast<Barta::DynamicsAwareInterface*>(leftBound));
    this->objectManager.addNewObject(leftBound);
}
