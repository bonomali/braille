#pragma once
#include <windows.h>
#include <cstdint>

namespace braille {
    class KeyInput {
    private:
        /// <summary>
        /// �o�[�`�����L�[�R�[�h
        /// </summary>
        uint8_t keyCode;

        /// <summary>
        /// 1�t���[���O�̃L�[�̓��͏��
        /// </summary>
        bool keyState;

    public:
        KeyInput() = default;

        /// <summary>
        /// �L�[���͂̏�����
        /// </summary>
        /// <param name="_keyCode">�m�F�������L�[�̃R�[�h</param>
        KeyInput(uint8_t _keyCode)
            : keyCode(_keyCode)
            , keyState(false) {}

        /// <summary>
        /// ���̃L�[�����݂̃t���[���œ��͂��ꂽ���ǂ����m�F����
        /// </summary>
        /// <returns>�L�[�����͂���Ă��邩�ǂ���</returns>
        bool clicked();
    };
}