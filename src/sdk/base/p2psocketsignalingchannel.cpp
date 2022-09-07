#include <iostream>
#include <algorithm>
#include <thread>
#include "p2psocketsignalingchannel.h"

P2PSocketSignalingChannel::P2PSocketSignalingChannel()
    : io_(new sio::client()), connection_listener_(new ConnectionListener(*io_)) {}

void P2PSocketSignalingChannel::AddObserver(
    P2PSignalingChannelObserver& observer) {
    observers_.push_back(&observer);
}

void P2PSocketSignalingChannel::RemoveObserver(
    P2PSignalingChannelObserver& observer) {
    observers_.erase(remove(observers_.begin(), observers_.end(), &observer),
        observers_.end());
}

void P2PSocketSignalingChannel::Connect(
    const std::string& host,
    const std::string& token,
    std::function<void(const std::string&)> on_success,
    std::function<void(std::unique_ptr<Exception>)> on_failure) {
    connect_success_callback_ = on_success;

    std::map<std::string, std::string> query;
    sio::socket::ptr socket = io_->socket();
    io_->set_reconnect_attempts(1);
    io_->set_reconnect_delay(2000);
    std::string owt_chat = "owt-message";
    std::string auth_msg_type = "authentication";
    sio::message::ptr jsonObject = sio::object_message::create();
    jsonObject->get_map()["token"] = sio::string_message::create(token);

    io_->set_open_listener([=] {
        io_->socket()->emit(auth_msg_type, jsonObject, [=](const sio::message::list& msg) {
            if (msg.size() > 0 && msg[0]->get_flag() == sio::message::flag_integer) {
                int64_t error_code = msg[0]->get_int();
                if (on_failure) {
                    std::unique_ptr<Exception> exception(
                        new Exception(ExceptionType::kP2PConnectionAuthFailed,
                            "Authentication failed."));
                    on_failure(std::move(exception));
                }
                return;
            }
            std::string uid = msg[0]->get_map()["uid"]->get_string().data();
            if (connect_success_callback_) {
                connect_success_callback_(uid);
            }
            });
        });

    io_->set_fail_listener([=] {
        if (on_failure) {
            std::unique_ptr<Exception> exception(
                new Exception(ExceptionType::kP2PUnknown,
                    "Server connection failed."));
            on_failure(std::move(exception));
        }
        });

    socket->on(
        owt_chat,
        sio::socket::event_listener_aux(
            [&](std::string const& name, sio::message::ptr const& data,
                bool has_ack, sio::message::list& ack_resp) {
                    if (data->get_flag() == sio::message::flag_object) {
                        std::string msg = data->get_map()["data"]->get_string().data();
                        std::string from = data->get_map()["from"]->get_string().data();
                        for (auto it = observers_.begin(); it != observers_.end(); ++it)
                            (*it)->OnSignalingMessage(msg, from);
                    }
            }));
    io_->connect(host, query);
}

void P2PSocketSignalingChannel::Disconnect(
    std::function<void()> on_success,
    std::function<void(std::unique_ptr<Exception>)> on_failure) {
    if (!io_->opened()) {
        if (on_failure) {
            std::unique_ptr<Exception> exception(
                new Exception(ExceptionType::kP2PClientInvalidState,
                    "Socket IO service has not been opened yet."));
            on_failure(std::move(exception));
        }
        return;
    }

    if (on_success) {
        on_success();
    }
    io_->close();
}

void P2PSocketSignalingChannel::SendMessage(
    const std::string& message,
    const std::string& target_id,
    std::function<void()> on_success,
    std::function<void(std::unique_ptr<Exception>)> on_failure) {
    sio::message::ptr jsonObject = sio::object_message::create();
    jsonObject->get_map()["to"] = sio::string_message::create(target_id);
    jsonObject->get_map()["data"] = sio::string_message::create(message);
    io_->socket()->emit("owt-message", jsonObject, [=](const sio::message::list& msg) {
        if (msg.size() > 0 && msg[0]->get_flag() == sio::message::flag_integer) {
            int64_t error_code = msg[0]->get_int();
            if (on_failure) {
                std::unique_ptr<Exception> exception(
                    new Exception(ExceptionType::kP2PMessageTargetUnreachable,
                        "Remote user cannot be reached."));
                on_failure(std::move(exception));
            }
            return;
        }
        if (on_success) {
            on_success();
        }
        });
}
