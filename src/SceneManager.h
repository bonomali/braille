#pragma once
#include <memory>
#include <map>
#include "Scene/IScene.h"
#include "Scene/Title.h"
#include "Scene/Game.h"
#include "Scene/Result.h"
#include "Canvas.h"
#include "KeyInput.h"

extern std::unique_ptr<braille::Canvas> canvas;
extern std::map<std::string, braille::Canvas> sprite;
extern std::map<std::string, braille::KeyInput> keyInput;

namespace braille {
    /// <summary>
    /// �V�[���̊Ǘ��N���X
    /// </summary>
    class SceneManager {
    private:
        SceneManager() {}

        /// <summary>
        /// ���݂̃V�[���̃X�}�[�g�|�C���^
        /// </summary>
        static std::unique_ptr<IScene> current;

    public:
        /// <summary>
        /// �V�[���̕ύX
        /// </summary>
        /// <typeparam name="Scene">�V�[���̃N���X��</typeparam>
        template <class Scene>
        static void changeScene() {
            current.reset(new Scene());
        }

        /// <summary>
        /// �e�t���[���̍X�V
        /// </summary>
        static void update();

        /// <summary>
        /// �e�t���[���̕`��
        /// </summary>
        static void draw();
    };
}