#pragma once
#pragma once
#include <windows.h>
#include <iostream>

/// <summary>
/// �G���[���N�����ăv���O�������I��������
/// </summary>
#define throwError() braille::_throwError(__FILE__, __LINE__, __func__)

namespace braille {
    struct GameObject {
        double x;
        double y;
        size_t w;
        size_t h;
    };

    /// <summary>
    /// �W�����͂̃n���h��
    /// </summary>
    extern HANDLE hStdin;

    /// <summary>
    /// �W���o�͂̃n���h��
    /// </summary>
    extern HANDLE hStdout;

    /// <summary>
    /// �G���[���N�����ăv���O�������I��������
    /// </summary>
    /// <param name="filename">�G���[���N�����t�@�C��</param>
    /// <param name="line">�G���[���N�����s��</param>
    /// <param name="funcname">�G���[���N�����֐�</param>
    void _throwError(const char* filename, int line, const char* funcname);

    /// <summary>
    /// �E�B���h�E�̏�����
    /// </summary>
    /// <param name="title">�E�B���h�E�^�C�g��</param>
    /// <param name="fontSize">�t�H���g�T�C�Y</param>
    /// <param name="width">�E�B���h�E�̕�(������)</param>
    /// <param name="height">�E�B���h�E�̍���(������)</param>
    void initWindow(LPCWSTR title, size_t fontSize, SMALL_RECT& windowSize, HANDLE(&screenBuffer)[2]);

    /// <summary>
    /// �Փ˂̔���
    /// </summary>
    /// <param name="x0">1�ڂ̕��̂�x���W</param>
    /// <param name="y0">1�ڂ̕��̂�y���W</param>
    /// <param name="w0">1�ڂ̕��̂̕�</param>
    /// <param name="h0">1�ڂ̕��̂̍���</param>
    /// <param name="x1">2�ڂ̕��̂�x���W</param>
    /// <param name="y1">2�ڂ̕��̂�y���W</param>
    /// <param name="w1">2�ڂ̕��̂̕�</param>
    /// <param name="h1">2�ڂ̕��̂̍���</param>
    /// <returns></returns>
    bool isCollision(size_t x0, size_t y0, size_t w0, size_t h0
        , size_t x1, size_t y1, size_t w1, size_t h1);
}