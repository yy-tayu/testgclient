#include "videoencode.h"
using namespace std;

VideoEncode::VideoEncode()
{
}

bool VideoEncode::InitEncoderContext(Resolution& resolution, uint32_t fps, uint32_t bitrate_kbps, VideoCodec video_codec)
{
    resolution_ = resolution;
    fps_ = fps;
    bitrate_ = bitrate_kbps;
    video_codec_ = video_codec;
    return true;
}

bool VideoEncode::EncodeOneFrame(std::vector<uint8_t>& buffer, bool key_frame)
{
    auto len = packet_queue_.size();
    if (len > 0)
    {
        std::lock_guard<mutex>lock(m_);
        auto source = packet_queue_.front();
        buffer.swap(source);
        packet_queue_.pop();
        key_frame = true;
        return true;
    }
    return false;
}

bool VideoEncode::Release()
{
    return false;
}

VideoEncoderInterface* VideoEncode::Copy()
{
    VideoEncoderInterface* ptr = this;
    return ptr;
}

void VideoEncode::InsertAVPacket(uint8_t* buffer, size_t length, void* reserve)
{
    vector<uint8_t> tmp_buffer;
    tmp_buffer.resize(length);
    memcpy(tmp_buffer.data(), buffer, tmp_buffer.size());
    auto size = packet_queue_.size();
    std::lock_guard<mutex>lock(m_);
    packet_queue_.push(std::move(tmp_buffer));
}