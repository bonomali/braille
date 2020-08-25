#pragma once
#include <windows.h>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <string>
#include "Utils.h"
#include "Canvas.h"

namespace braille {
    /// <summary>
    /// �t���[�����[�g�̊Ǘ��N���X
    /// </summary>
    class FrameRate {
    private:
        FrameRate() {}

        /// <summary>
        /// �e�t���[���̊J�n���̎���
        /// </summary>
        static std::chrono::system_clock::time_point start;

        /// <summary>
        /// �e�t���[���̏I�����̎���
        /// </summary>
        static std::chrono::system_clock::time_point end;

        /// <summary>
        /// �t���[�����[�g�̏��
        /// </summary>
        static uint32_t maxFrameRate;

        /// <summary>
        /// 1�t���[��������̎��Ԃ̏��
        /// </summary>
        static double maxElapsed;

        /// <summary>
        /// ���݂̃t���[�����[�g
        /// </summary>
        static uint32_t frameRate;

    public:
        /// <summary>
        /// �t���[�����[�g����̐ݒ�
        /// </summary>
        /// <param name="fps">�t���[�����[�g�̏��</param>
        static void setMaxFrameRate(uint32_t fps = 60);

        /// <summary>
        /// �e�t���[���̊J�n���ɌĂяo��
        /// </summary>
        static void startFrame();

        /// <summary>
        /// �e�t���[���̏I�����ɌĂяo��
        /// </summary>
        static void endFrame();

        /// <summary>
        /// FPS��W���o�͂���
        /// </summary>
        /// <param name="x">�J�[�\���ʒu��x���W</param>
        /// <param name="y">�J�[�\���ʒu��y���W</param>
        static void print(size_t x = 0, size_t y = 0);
    };
}