#ifndef FOTRIC_TEST_H_
#define FOTRIC_TEST_H_
#include <string>
#include <functional>
#include <vector>

#ifdef X11
#ifdef IR_TEST_EXPORTS
#define IR_TEST_EXPORTS __attribute__ ((visibility("default")))
#else 
#define IR_TEST_EXPORTS
#endif
#endif

enum class STREAM_TYPE : int
{
    kScreenCast = 1,
    kYUV,
    kH264,
};

struct ir_test_info
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

IR_TEST_EXPORTS void ir_test_init();

#endif // !FOTRIC_TEST_H_