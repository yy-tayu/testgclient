#ifndef OTTER_OBSERVER_H_
#define OTTER_OBSERVER_H_
#include "owt/p2p/p2pclient.h"
#include "videoencode.h"
#include "framegenerator.h"
#include "p2psocketsignalingchannel.h"
using namespace owt::base;
using namespace owt::p2p;
using namespace std;

class OtterObserver : P2PClientObserver, enable_shared_from_this<OtterObserver>
{
public:
    enum class StreamType : int
    {
        kSendScreenCast = 1,
        kSendYUV,
        kSendH264,
    };
    struct WebrtcsdkInfo
    {
        std::string local_id_;
        std::string remote_id_;
        std::string signaling_address_;
        std::string stun_address_;
        std::string trun_address_;
        uint16_t video_width_;
        uint16_t video_height_;
        StreamType stream_type_;
    };
    static OtterObserver* Create(WebrtcsdkInfo* info);



    void Connect(function<void(const string&)>on_success, function<void(unique_ptr<Exception>)> on_failed);
    void SetReceiveMessageCallback(function<void(const string& remote_user_id, const string message)> callback);
    void SendMesg(std::string message);

    void InsertAVPacket(uint8_t* buffer, size_t length, void* reserve);
    void InsertYUVFrame(uint8_t* buffer, size_t length, void* reserve);
    void SetRemoteID();
private:
    explicit OtterObserver(WebrtcsdkInfo* server_info);
    void PublishStream();
    virtual void OnMessageReceived(const std::string& remote_user_id,
        const std::string message)override;
    P2PClientConfiguration configuration_;
    shared_ptr<P2PClient> pc_;
    shared_ptr<P2PSocketSignalingChannel> signaling_channel_;
    shared_ptr<LocalDesktopStreamParameters> desktop_sp_; 
    shared_ptr<LocalCustomizedStreamParameters> customized_sp_; 
    shared_ptr<LocalStream> local_stream_;
    shared_ptr<RemoteStream> remote_stream_;
    shared_ptr<P2PPublication> publication_;
    shared_ptr<VideoEncode> encoder_;
    unique_ptr<FrameGenerator> frame_generator_;
    string local_id_;
    string remote_id_;
    string signaling_address_;
    string stun_address_;
    string trun_address_;
    owt::base::Resolution resolution_;
    uint8_t fps_;
    string video_codec_;
    StreamType stream_type_;
    std::function<void(const string& remote_user_id, const string message)> mssage_callback_;
};
#endif