#pragma once
#include "owt/base/framegeneratorinterface.h"
#include <vector>
#include <queue>
#include <mutex>
#include <functional>

using namespace std;
using namespace owt::base;
class FrameGenerator :public VideoFrameGeneratorInterface
{
public:
	// owt will encode
	FrameGenerator();
	~FrameGenerator() = default;
	virtual uint32_t GenerateNextFrame(uint8_t* buffer,
		const uint32_t capacity) override;
	/**
	 @brief This function gets the size of next video frame.
	 */
	virtual uint32_t GetNextFrameSize() override;
	/**
	 @brief This function gets the height of video frame.
	 */
	virtual int GetHeight() override;
	/**
	 @brief This function gets the width of video frame.
	 */
	virtual int GetWidth() override;
	/**
	 @brief This function gets the fps of video frame generator.
	 */
	virtual int GetFps() override;
	/**
	 @brief This function gets the video frame type of video frame generator.
	 */
	virtual VideoFrameCodec GetType()  override;
	void InsertYUVFrame(uint8_t* buffer, size_t length);
	std::mutex m_;
	std::queue<vector<uint8_t>> frame_queue_;
};

