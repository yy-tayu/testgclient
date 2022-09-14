#ifndef FOTRIC_WEBRTC_H_
#define FOTRIC_WEBRTC_H_
#include <string>
#include <functional>
#include <vector>

#if defined(WIN32)
#if defined(AONYX_SHARED_IMPLEMENTATION)
#define IR_AONYX_EXPORTS __declspec(dllexport)
#define IR_AONYX_EXPORTS_PRIVATE __declspec(dllexport)
#else
#define IR_AONYX_EXPORTS __declspec(dllimport)
#define IR_AONYX_EXPORTS_PRIVATE __declspec(dllimport)
#endif  // defined(HELLO_SHARED_IMPLEMENTATION)
#else
#if defined(AONYX_SHARED_IMPLEMENTATION)
#define IR_AONYX_EXPORTS __attribute__((visibility("default")))
#define IR_AONYX_EXPORTS_PRIVATE __attribute__((visibility("default")))
#else
#define IR_AONYX_EXPORTS
#define IR_AONYX_EXPORTS_PRIVATE
#endif  // defined(HELLO_SHARED_IMPLEMENTATION)
#endif

enum class STREAM_TYPE : int
{
    kScreenCast = 1,
    kYUV,
    kH264,
};

struct ir_webrtcsdk_info
{
    std::string local_id_;
    std::string remote_id_;
    std::string signaling_address_;
    std::string stun_address_;
    std::string trun_address_;
    uint16_t video_width_;
    uint16_t video_height_;
    STREAM_TYPE stream_type_;
};

IR_AONYX_EXPORTS void ir_webrtc_init(ir_webrtcsdk_info* info);
IR_AONYX_EXPORTS void ir_webrtc_run();
IR_AONYX_EXPORTS void ir_webrtc_register_message(std::function<void(const std::string& remote_user_id, const std::string message)> message_callback);
IR_AONYX_EXPORTS void ir_webrtc_send_message(std::string msg);
IR_AONYX_EXPORTS void ir_webrtc_insert_avpacket(uint8_t* buffer, size_t length, void* reserve);
IR_AONYX_EXPORTS void ir_webrtc_insert_yuvframe(uint8_t* buffer, size_t length, void* reserve);
IR_AONYX_EXPORTS void ir_webrtc_stop();
IR_AONYX_EXPORTS void ir_webrtc_cleanup();

#endif // !FOTRIC_WEBRTC_H_
