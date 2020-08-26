#include "Game.h"

namespace braille {
    namespace Scene {
        Game::Game()
            : scorePos(GameObject{ 121, 5 }) {
            // �v���C���[�̏�����
            player.x = 20;
            player.y = 102;
            player.w = sprite["player1"].getWidth();
            player.h = sprite["player1"].getHeight();
            player.maxY = canvas->getHeight() - sprite["player1"].getHeight() - 4;
            player.jumpForce = 8;
            player.dy = -player.jumpForce;
            player.fallForce = 0.8;

            // �~�T�C���̏�����
            Missile msl;
            msl.x = player.x + player.w;
            msl.y = player.y;
            msl.w = sprite["missile"].getWidth();
            msl.h = sprite["missile"].getHeight();
            msl.dx = 5;
            msl.maxX = canvas->getWidth() - sprite["missile"].getWidth() - 4;
            missiles.push_back(msl);

            // �X�R�A�̊e���̈ʒu��������
            for (size_t i = 0; i < 4; i++) {
                digitPos.push_back(GameObject{ scorePos.x + 66 + 12 * i, scorePos.y,sprite["0"].getWidth(), sprite["0"].getHeight() });
            }
            ss << std::setw(4) << std::setfill('0') << min(score, 9999);

            // �L�����o�X�̃N���A�Ƙg���̒ǉ�
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
            canvas->draw(scorePos.x, scorePos.y, sprite["score"]);
        }

        void Game::update() {
            // �v���C���[�̏���
            canvas->clear(player.x, min(max(4, player.y), player.maxY), player.w, player.h);
            player.dy += player.fallForce;
            player.y += player.dy;
            if (keyInput["space"].clicked()) {
                player.dy = -player.jumpForce;

                Missile msl;
                msl.x = player.x + player.w;
                msl.y = min(player.y, canvas->getHeight() - sprite["missile"].getHeight());
                msl.w = sprite["missile"].getWidth();
                msl.h = sprite["missile"].getHeight();
                msl.dx = 5;
                msl.maxX = canvas->getWidth() - sprite["missile"].getWidth() - 4;
                missiles.push_back(msl);
            }

            // �~�T�C���̏���
            for (auto& msl : missiles) {
                canvas->clear(msl.x, msl.y, msl.w, msl.h);
                msl.x += msl.dx;
            }
            missiles.erase(std::remove_if(missiles.begin(), missiles.end(),
                [](Missile msl) { return msl.maxX < msl.x; }
            ), missiles.end());

            // �X�R�A�̕`�揀��
            ss.str("");
            ss.clear(std::ostringstream::goodbit);
            ss << std::setw(4) << std::setfill('0') << min(score, 9999);
            score += 1;

            if (player.y < 0 || player.maxY < player.y) {
                Game::draw();
                for (size_t sy = 0; sy < player.h / 4; sy++) {
                    for (size_t sx = 0; sx < player.w / 2; sx++) {
                        canvas->setAttr(player.x / 2 + sx, min(max(4, player.y), player.maxY) / 4 + sy, FOREGROUND_RED);
                    }
                }
                SceneManager::changeScene<Scene::Result>();
            }
        }

        void Game::draw() const {
            // �v���C���[�̕`��
            canvas->draw(player.x, min(max(4, player.y), player.maxY), sprite[
                (player.dy > 0) ? "player1" : "player2"
            ]);

            // �~�T�C���̕`��
            for (const auto& msl : missiles) {
                canvas->draw(msl.x, msl.y, sprite["missile"]);
            }

            // �X�R�A�̕`��
            for (size_t i = 0; i < 4; i++) {
                canvas->clear(digitPos[i].x, digitPos[i].y, digitPos[i].w, digitPos[i].h);
                canvas->draw(digitPos[i].x, digitPos[i].y, sprite[std::string{ ss.str()[i] }]);
            }
        }
    }
}