//
// Created by barta on 28/12/2023.
//

#include "StringSpriteBuilder.h"
Barta::StringSprite Barta::StringSpriteBuilder::build() noexcept {
    return StringSprite(
        this->vertex1,
        this->string,
        this->fontSize
    );
}
