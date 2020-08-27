#include "Game.h"

namespace braille {
    namespace Scene {
        Game::Game()
            : scorePos(GameObject{ 121, 7, sprite["score"].getWidth(), sprite["score"].getHeight() })
            , pipeInterval(0)
            , mt(std::mt19937{ _rnd() })
            , rnd(std::uniform_int_distribution<>{0, 56}) {
            // プレイヤーの初期化
            player.x = 32;
            player.y = 102;
            player.w = sprite["player1"].getWidth();
            player.h = sprite["player1"].getHeight();
            player.maxY = canvas->getHeight() - sprite["player1"].getHeight() - 4;
            player.jumpForce = 8;
            player.dy = -player.jumpForce;
            player.fallForce = 0.8;

            // 土管の初期化
            makePipe();

            // スコアの各桁の位置を初期化
            for (size_t i = 0; i < 4; i++) {
                digitPos.push_back(GameObject{ scorePos.x + 66 + 12 * i, scorePos.y,sprite["0"].getWidth(), sprite["0"].getHeight() });
            }
            ss << std::setw(4) << std::setfill('0') << min(score, 9999);

            // キャンバスのクリアと枠線の追加
            canvas->clear();
            for (size_t i = 0; i < canvas->getWidth(); i++) {
                canvas->set(i, 1, 1);
                canvas->set(i, 3, 1);
                canvas->set(i, canvas->getHeight() - 2, 1);
                canvas->set(i, canvas->getHeight() - 4, 1);
            }
            for (size_t i = 0; i < canvas->getHeight(); i++) {
                canvas->set(1, i, 1);
                canvas->set(3, i, 1);
                canvas->set(canvas->getWidth() - 2, i, 1);
                canvas->set(canvas->getWidth() - 4, i, 1);
            }
        }

        void Game::update() {
            // プレイヤーの処理
            canvas->clear(player.x, min(max(4, player.y), player.maxY), player.w, player.h);
            player.dy += player.fallForce;
            player.y += player.dy;
            if (keyInput["space"].clicked()) {
                player.dy = -player.jumpForce;
            }

            // 土管の処理
            pipeInterval++;
            if (pipeInterval > 40) {
                makePipe();
                pipeInterval = 0;
            }
            for (auto& pipe : pipes) {
                canvas->clear(pipe.x, pipe.y, pipe.w, pipe.h, 4);
                canvas->clear(pipe.x, pipe.y + pipe.h + pipe.gap, pipe.w, canvas->getHeight() - pipe.h - 8, 4);
                pipe.x += pipe.dx;
                if (!pipe.alreadyPass && pipe.x < player.x) {
                    score += 1;
                    pipe.alreadyPass = true;
                }
            }
            pipes.erase(std::remove_if(pipes.begin(), pipes.end(),
                [](Pipe pipe) { return pipe.x + pipe.w < 4; }
            ), pipes.end());

            // スコアの描画準備
            ss.str("");
            ss.clear(std::ostringstream::goodbit);
            ss << std::setw(4) << std::setfill('0') << min(score, 9999);

            // ゲームオーバー時の処理
            bool collidePipe = false;
            for (auto& pipe : pipes) {
                if (isCollision(player.x, player.y, player.w, player.h, pipe.x, pipe.y, pipe.w, pipe.h) ||
                    isCollision(player.x, player.y, player.w, player.h, pipe.x, pipe.y + pipe.h + pipe.gap, pipe.w, canvas->getHeight() - pipe.h - 8)) {
                    collidePipe = true;
                    break;
                }
            }

            if (player.y < 0 || player.maxY < player.y || collidePipe) {
                draw();
                for (size_t sy = 0; sy < player.h / 4; sy++) {
                    for (size_t sx = 0; sx < player.w / 2; sx++) {
                        canvas->setAttr(player.x / 2 + sx, min(max(4, player.y), player.maxY) / 4 + sy, FOREGROUND_RED);
                    }
                }
                SceneManager::changeScene<Scene::Result>();
            }
        }

        void Game::draw() const {
            // プレイヤーの描画
            canvas->draw(player.x, min(max(4, player.y), player.maxY), sprite[
                (player.dy > 0) ? "player1" : "player2"
            ]);

            // 土管の描画
            for (const auto& pipe : pipes) {
                canvas->rect(pipe.x, pipe.y, pipe.w, pipe.h, FOREGROUND_GREEN, 4);
                canvas->rect(pipe.x, pipe.y + pipe.h + pipe.gap, pipe.w, canvas->getHeight() - pipe.h - 8, FOREGROUND_GREEN, 4);
            }

            // スコアの描画
            canvas->clear(scorePos.x - 3, scorePos.y - 2, scorePos.w + (digitPos[0].w + 2) * 4 + 6, scorePos.h + 3);
            canvas->draw(scorePos.x, scorePos.y, sprite["score"]);
            for (size_t i = 0; i < 4; i++) {
                canvas->draw(digitPos[i].x, digitPos[i].y, sprite[std::string{ ss.str()[i] }]);
            }
        }

        void Game::makePipe() {
            Pipe pipe;
            pipe.x = canvas->getWidth() - 4;
            pipe.y = 4;
            pipe.w = 28;
            pipe.h = 32 + rnd(mt); //32-88
            pipe.dx = -3;
            pipe.gap = 52;
            pipe.alreadyPass = false;
            pipes.push_back(pipe);
        }
    }
}