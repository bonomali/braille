#pragma once
#include <windows.h>
#include <chrono>
#include <cstdint>
#include <iostream>
#include "Utils.h"

namespace braille {
    /// <summary>
    /// �t���[�����[�g�̊Ǘ��N���X
    /// </summary>
    class FrameRate {
    private:
        /// <summary>
        /// �e�t���[���̊J�n���̎���
        /// </summary>
        std::chrono::system_clock::time_point start;

        /// <summary>
        /// �e�t���[���̏I�����̎���
        /// </summary>
        std::chrono::system_clock::time_point end;

        /// <summary>
        /// �t���[�����[�g�̏��
        /// </summary>
        uint32_t maxFrameRate;

        /// <summary>
        /// 1�t���[��������̎��Ԃ̏��
        /// </summary>
        double maxElapsed;

        /// <summary>
        /// ���݂̃t���[�����[�g
        /// </summary>
        uint32_t frameRate;

    public:
        /// <summary>
        /// �t���[�����[�g�̏�����
        /// </summary>
        /// <param name="_maxFrameRate">�t���[�����[�g�̏��</param>
        FrameRate(uint32_t _maxFrameRate = 60)
            : maxFrameRate(_maxFrameRate)
            , maxElapsed(1.0 / maxFrameRate)
            , frameRate(_maxFrameRate) {}

        /// <summary>
        /// �e�t���[���̊J�n���ɌĂяo��
        /// </summary>
        void startFrame();

        /// <summary>
        /// �e�t���[���̏I�����ɌĂяo��
        /// </summary>
        void endFrame();

        /// <summary>
        /// FPS��W���o�͂���
        /// </summary>
        /// <param name="x">�J�[�\���ʒu��x���W</param>
        /// <param name="y">�J�[�\���ʒu��y���W</param>
        void print(int32_t x = 0, int32_t y = 0) const;
    };
}