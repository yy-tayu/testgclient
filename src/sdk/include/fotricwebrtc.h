#ifndef FOTRIC_WEBRTC_H_
#define FOTRIC_WEBRTC_H_
#include <string>
#include <functional>
#include <vector>
#ifdef _WIN32
#ifdef IR_WEBRTC_EXPORTS
#ifdef __cplusplus
#define IR_WEBRTC_API extern "C" __declspec(dllexport)
#else
#define IR_WEBRTC_API __declspec(dllexport)
#endif
#else
#ifdef __cplusplus
#define IR_WEBRTC_API extern "C" __declspec(dllimport)
#else
#define IR_WEBRTC_API __declspec(dllexport)
#endif
#endif
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

IR_WEBRTC_API void ir_webrtc_init(ir_webrtcsdk_info* info);
IR_WEBRTC_API void ir_webrtc_run();
IR_WEBRTC_API void ir_webrtc_register_message(std::function<void(const std::string& remote_user_id, const std::string message)> message_callback);
IR_WEBRTC_API void ir_webrtc_send_message(std::string msg);
IR_WEBRTC_API void ir_webrtc_insert_avpacket(uint8_t* buffer, size_t length, void* reserve);
IR_WEBRTC_API void ir_webrtc_insert_yuvframe(uint8_t* buffer, size_t length, void* reserve);
IR_WEBRTC_API void ir_webrtc_stop();
IR_WEBRTC_API void ir_webrtc_cleanup();

#endif // !FOTRIC_WEBRTC_H_
