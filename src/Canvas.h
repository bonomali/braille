#pragma once
#include <fstream>
#include <iostream>
#include "Grid.h"

namespace braille {
    class Canvas : public Grid<bool> {
    private:
        /// <summary>
        /// �R���\�[���̕�(������)
        /// </summary>
        size_t consoleWidth;

        /// <summary>
        /// �R���\�[���̍���(������)
        /// </summary>
        size_t consoleHeight;

        /// <summary>
        /// �_����Unicode�v�Z�p
        /// </summary>
        uint8_t pixelMap[8] = { 0x01, 0x02, 0x04, 0x40, 0x08, 0x10, 0x20, 0x80 };

        /// <summary>
        /// ���ۂɏo�͂��镶��
        /// </summary>
        Grid<WCHAR> text;

    public:
        Canvas() = default;

        /// <summary>
        /// �L�����o�X�̏�����
        /// </summary>
        /// <param name="_consoleWidth">�L�����o�X�̕�(������)</param>
        /// <param name="_consoleHeight">�L�����o�X�̍���(������)</param>
        Canvas(size_t _width, size_t _height)
            : Grid<bool>(_width, _height, 0)
            , consoleWidth(_width / 2)
            , consoleHeight(_height / 4)
            , text(Grid<WCHAR>(consoleWidth, consoleHeight, ' ')) {
            if (width % 2 != 0 || height % 4 != 0) {
                std::cout << width << ", " << height << std::endl;
                throwError();
            }
        }

        /// <summary>
        /// �L�����o�X�̃h�b�g���R���\�[���p�̃O���b�h�ɃR�s�[����
        /// </summary>
        void updateText();

        /// <summary>
        /// �������R���\�[���p�̃O���b�h�ɃR�s�[����
        /// </summary>
        /// <param name="consoleX">x���W</param>
        /// <param name="consoleY">y���W</param>
        /// <param name="c">�R�s�[���镶��</param>
        void setText(size_t consoleX, size_t consoleY, WCHAR c);

        /// <summary>
        /// ��������R���\�[���p�̃O���b�h�ɃR�s�[����
        /// </summary>
        /// <param name="consoleX">x���W</param>
        /// <param name="consoleY">y���W</param>
        /// <param name="s">�R�s�[���镶����</param>
        void setText(size_t consoleX, size_t consoleY, std::string s);

        /// <summary>
        /// �R���\�[���p�̃O���b�h���當�����擾
        /// </summary>
        /// <param name="consoleX">x���W</param>
        /// <param name="consoleY">y���W</param>
        /// <returns>�擾��������</returns>
        WCHAR getText(size_t consoleX, size_t consoleY) const {
            return text.get(consoleX, consoleY);
        }

        /// <summary>
        /// �ʂ̃L�����o�X�������ɕ`�悷��
        /// </summary>
        /// <param name="x">�`��̊�ɂ���x���W</param>
        /// <param name="y">�`��̊�ɂ���y���W</param>
        /// <param name="sprite">�`�悷��L�����o�X</param>
        void draw(size_t x, size_t y, Canvas& spr);

        /// <summary>
        /// �����񂩂�L�����o�X��ǂݍ���
        /// </summary>
        /// <param name="str">0��1����Ȃ镶����(�����̓L�����o�X�̃T�C�Y�Ɠ���)</param>
        void load(std::string str);

        /// <summary>
        /// �t�@�C������L�����o�X��ǂݍ���
        /// </summary>
        /// <param name="filename">�t�@�C����(�t�@�C������0��1�������ǂݍ��܂��)</param>
        void loadFromFile(std::string filename);

        /// <summary>
        /// ��ʂ��N���A����
        /// </summary>
        void clear();

        /// <summary>
        /// �̈���w�肵�ĉ�ʂ��N���A����
        /// </summary>
        /// <param name="x">�N���A�����ƂȂ�x���W</param>
        /// <param name="y">�N���A�����ƂȂ�y���W</param>
        /// <param name="w">�N���A���镝</param>
        /// <param name="h">�N���A���鍂��</param>
        void clear(size_t x, size_t y, size_t w, size_t h) {
            for (size_t sy = 0; sy < h; sy++) {
                for (size_t sx = 0; sx < w; sx++) {
                    set(x + sx, y + sy, 0);
                    text.set((x + sx) / 2, (y + sy) / 4, ' ');
                }
            }
        }
    };
}