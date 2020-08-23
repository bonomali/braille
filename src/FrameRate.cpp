#include "FrameRate.h"

namespace braille {
    void FrameRate::startFrame() {
        start = std::chrono::system_clock::now();
    }

    void FrameRate::endFrame() {
        end = std::chrono::system_clock::now();
        double elapsed = std::chrono::duration<double>(end - start).count();
        frameRate = (uint32_t)(1 / elapsed);
        if (frameRate > maxFrameRate) {
            Sleep((maxElapsed - elapsed) * 1000);
        }
    }

    void FrameRate::print(int32_t x, int32_t y) const {
        setCursorPosition(x, y);
        std::cout << "fps: " << min(frameRate, maxFrameRate);
    }
}