#pragma once
#pragma once
#include <windows.h>
#include <iostream>

/// <summary>
/// �G���[���N�����ăv���O�������I��������
/// </summary>
#define throwError() braille::_throwError(__FILE__, __LINE__, __func__)

namespace braille {
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
    /// �J�[�\���ʒu�̐ݒ�
    /// </summary>
    /// <param name="x">�J�[�\���ʒu��x���W</param>
    /// <param name="y">�J�[�\���ʒu��y���W</param>
    void setCursorPosition(size_t x, size_t y);

    /// <summary>
    /// �E�B���h�E�̏�����
    /// </summary>
    /// <param name="title">�E�B���h�E�^�C�g��</param>
    /// <param name="fontSize">�t�H���g�T�C�Y</param>
    /// <param name="width">�E�B���h�E�̕�(������)</param>
    /// <param name="height">�E�B���h�E�̍���(������)</param>
    void initWindow(LPCWSTR title = L"", size_t fontSize = 16, size_t width = 120, size_t height = 30);
}