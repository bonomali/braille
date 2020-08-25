#pragma once
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
        /// <summary>
        /// �L�����o�X�̏�����
        /// </summary>
        /// <param name="_consoleWidth">�L�����o�X�̕�(������)</param>
        /// <param name="_consoleHeight">�L�����o�X�̍���(������)</param>
        Canvas(size_t _consoleWidth, size_t _consoleHeight)
            : Grid<bool>(_consoleWidth * 2, _consoleHeight * 4, 0)
            , consoleWidth(_consoleWidth)
            , consoleHeight(_consoleHeight)
            , text(Grid<WCHAR>(consoleWidth, consoleHeight, ' ')) {}

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
    };
}