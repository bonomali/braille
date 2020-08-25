#include "FrameRate.h"

extern std::unique_ptr<braille::Canvas> canvas;

namespace braille {
    std::chrono::system_clock::time_point FrameRate::start;
    std::chrono::system_clock::time_point FrameRate::end;
    uint32_t FrameRate::maxFrameRate = 60;
    double FrameRate::maxElapsed = 1.0 / 60;
    uint32_t FrameRate::frameRate = 60;

    void FrameRate::setMaxFrameRate(uint32_t fps) {
        maxFrameRate = fps;
        maxElapsed = 1.0 / maxFrameRate;
    }

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

    void FrameRate::print(size_t x, size_t y) {
        canvas->setText(110, 2, "fps: " + std::to_string(min(frameRate, maxFrameRate)));
    }
}