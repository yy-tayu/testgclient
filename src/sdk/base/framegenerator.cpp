#include "framegenerator.h"

FrameGenerator::FrameGenerator()
{
}

uint32_t FrameGenerator::GenerateNextFrame(uint8_t* buffer, const uint32_t capacity)
{
    auto len = frame_queue_.size();
    if (len > 0)
    {
        std::lock_guard<mutex>lock(m_);
        auto source = frame_queue_.front();
        if (source.size() > capacity)
        {
            frame_queue_.pop();
            return  -1;
        }
        memcpy(buffer, source.data(), source.size());
        frame_queue_.pop(); 
        return source.size();
    }
    return 0;
}

uint32_t FrameGenerator::GetNextFrameSize()
{
    return 460800;
}

int FrameGenerator::GetHeight()
{
    return 480;
}

int FrameGenerator::GetWidth()
{
    return 640;
}

int FrameGenerator::GetFps()
{
    return 30;
}

VideoFrameGeneratorInterface::VideoFrameCodec FrameGenerator::GetType()
{
    return VideoFrameGeneratorInterface::VideoFrameCodec::I420;
}

void FrameGenerator::InsertYUVFrame(uint8_t* buffer, size_t length)
{
    vector<uint8_t> tmp(length, 0);
    memcpy(tmp.data(), buffer, length);
    auto len = frame_queue_.size();
    if (len < 3)
    {
        std::lock_guard<mutex>lock(m_);
        frame_queue_.push(std::move(tmp));
    }
    else
    {
        std::this_thread::sleep_for(std::chrono::microseconds(30));
        std::lock_guard<mutex>lock(m_);
        queue<vector<uint8_t>>empty;
        swap(empty, frame_queue_);
        frame_queue_.push(tmp);
    }
}
