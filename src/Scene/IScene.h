#pragma once
#include "../SceneManager.h"

namespace braille {
    /// <summary>
    /// シーンのインタフェース
    /// </summary>
    class IScene {
    public:
        virtual void update() = 0;
        virtual void draw() const = 0;
    };
}