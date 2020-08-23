#pragma once
#include "../SceneManager.h"

namespace braille {
    /// <summary>
    /// �V�[���̃C���^�t�F�[�X
    /// </summary>
    class IScene {
    public:
        virtual void update() = 0;
        virtual void draw() const = 0;
    };
}