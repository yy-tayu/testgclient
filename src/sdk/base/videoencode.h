#pragma once
#include <functional>
#include <queue>
#include <mutex>
#include <vector>
#include "owt/base/videoencoderinterface.h"
#include<atomic>

struct AVCodec;
struct AVCodecContext;
struct SwsContext;
struct AVPacket;
using namespace owt::base;
class VideoEncode :public VideoEncoderInterface
{
	friend class OtterObserver;
public:
	VideoEncode();
	~VideoEncode() = default;
	virtual bool InitEncoderContext(Resolution& resolution, uint32_t fps, uint32_t bitrate_kbps, VideoCodec video_codec)override;
	virtual bool EncodeOneFrame(std::vector<uint8_t>& buffer, bool key_frame) override;
	virtual bool Release() override;
	virtual VideoEncoderInterface* Copy() override;
private:
	owt::base::Resolution resolution_;
	int fps_;
	int bitrate_;
	owt::base::VideoCodec video_codec_;
	void InsertAVPacket(uint8_t* buffer, size_t length, void* reserve);
	std::mutex m_;
	std::queue<std::vector<uint8_t>> packet_queue_;
	std::atomic<std::queue<std::vector<uint8_t>>> packets_atomic_;
};

