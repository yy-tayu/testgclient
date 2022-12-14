#ifndef P2P_SOCKET_SIGNALING_CHANNEL_H_
#define P2P_SOCKET_SIGNALING_CHANNEL_H_

#include <vector>
#include "socketio/sio_client.h"
#include "owt/p2p/p2psignalingchannelinterface.h"

using namespace owt::p2p;

class ConnectionListener
{
    sio::client& handler;
public:
    ConnectionListener(sio::client& hdl) : handler(hdl) {}

    void on_connected() {}
};

class P2PSocketSignalingChannel : public P2PSignalingChannelInterface {
public:
    explicit P2PSocketSignalingChannel();
    virtual void AddObserver(
        P2PSignalingChannelObserver& observer) override;
    virtual void RemoveObserver(
        P2PSignalingChannelObserver& observer) override;
    virtual void Connect(const std::string& host,
        const std::string& token,
        std::function<void(const std::string&)> on_success,
        std::function<void(std::unique_ptr<Exception>)> on_failure) override;
    virtual void Disconnect(std::function<void()> on_success,
        std::function<void(std::unique_ptr<Exception>)> on_failure) override;
    virtual void SendMessage(const std::string& message,
        const std::string& target_id,
        std::function<void()> on_success,
        std::function<void(std::unique_ptr<Exception>)> on_failure) override;
private:
    std::vector<P2PSignalingChannelObserver*> observers_;
    std::unique_ptr<sio::client> io_;
    std::function<void(const std::string&)> connect_success_callback_;
    std::unique_ptr<ConnectionListener> connection_listener_;
};
#endif // !P2P_SOCKET_SIGNALING_CHANNEL_H_