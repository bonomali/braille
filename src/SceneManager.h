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
    /// シーンの管理クラス
    /// </summary>
    class SceneManager {
    private:
        SceneManager() {}

        /// <summary>
        /// 現在のシーンのスマートポインタ
        /// </summary>
        static std::unique_ptr<IScene> current;

    public:
        /// <summary>
        /// シーンの変更
        /// </summary>
        /// <typeparam name="Scene">シーンのクラス名</typeparam>
        template <class Scene>
        static void changeScene() {
            current.reset(new Scene());
        }

        /// <summary>
        /// 各フレームの更新
        /// </summary>
        static void update();

        /// <summary>
        /// 各フレームの描画
        /// </summary>
        static void draw();
    };
}