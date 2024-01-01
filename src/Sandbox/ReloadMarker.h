#pragma once
#include "BartaObject.h"
#include "DeletableObject.h"
#include "Gun.h"

class ReloadMarker: 
    public Barta::BartaObjectInterface,
    public Barta::DeletableObject {
	public:

	ReloadMarker(Gun* gun) noexcept;
    ~ReloadMarker() noexcept = default;
    ReloadMarker(const ReloadMarker&) = delete;
    ReloadMarker(ReloadMarker&&) = default;
    ReloadMarker& operator=(const ReloadMarker&) = delete;
    ReloadMarker& operator=(ReloadMarker&&) = default;

    bool isToBeDeleted() const override { return Barta::DeletableObject::isToBeDeleted(); };

	const Barta::TransformableInterface& getTransformable() const override;

	const Barta::BartaSprite* getResource() noexcept override;
    int getZIndex() const override;

private:
    void loadResource();
	std::unique_ptr<Barta::TransformableInterface> transformable;

    Barta::BartaSprite resource;

    Gun* gun;
};

