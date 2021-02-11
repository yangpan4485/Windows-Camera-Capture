#pragma once

#include <cstdint>

#include <unordered_map>

class FrameBuffer {
public:
    static FrameBuffer& Instance();

    uint8_t* GetBuffer(uint32_t width, uint32_t height, int& index);

    void ReleaseBuffer(int index);

private:
    FrameBuffer();
    ~FrameBuffer();
    FrameBuffer(const FrameBuffer&) = delete;
    FrameBuffer operator=(const FrameBuffer&) = delete;

    void FreeAllBuffer();

private:
    std::unordered_map<int, int> buffer_map_{};
    std::unordered_map<int, uint8_t*> buffer_vec_{};
    // std::vector<uint8_t*> buffer_vec_{};

    uint32_t width_{};
    uint32_t height_{};
    int index_{};
};