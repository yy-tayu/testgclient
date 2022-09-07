#include "otterobserver.h"
#include <iostream>

bool Check(OtterObserver::WebrtcsdkInfo* info)
{
	return true;
}

OtterObserver::OtterObserver(WebrtcsdkInfo*server_info)
	: local_id_{ server_info->local_id_ }, remote_id_{ server_info->remote_id_ }, signaling_address_{ server_info->signaling_address_}
	, resolution_{ server_info->video_width_, server_info->video_height_ }, stream_type_{ server_info->stream_type_ }, fps_{25}
	, stun_address_{ server_info->stun_address_}, trun_address_{ server_info->trun_address_}
	, pc_{ nullptr }, signaling_channel_{ nullptr }, encoder_{ nullptr }, frame_generator_{nullptr}
{
	switch (server_info->stream_type_)
	{
	case StreamType::kSendH264:
		encoder_.reset(new VideoEncode());
		break;
	case StreamType::kSendYUV:
		frame_generator_.reset(new FrameGenerator());
		break;
	default:
		break;
	}
	signaling_channel_.reset(new P2PSocketSignalingChannel());
	GlobalConfiguration::SetEncodedVideoFrameEnabled(true);
	GlobalConfiguration::SetAEC3Enabled(false);
	GlobalConfiguration::SetAECEnabled(false);
	GlobalConfiguration::SetAGCEnabled(false);
	GlobalConfiguration::SetVideoHardwareAccelerationEnabled(false);
	VideoEncodingParameters video_params;
	VideoCodecParameters video_codec_params;
	video_codec_params.name = VideoCodec::kH264;
	video_params.codec = video_codec_params;
	configuration_.video_encodings = { video_params };
	pc_.reset(new P2PClient(configuration_, signaling_channel_));
	pc_->AddObserver(*this);
}

OtterObserver* OtterObserver::Create(WebrtcsdkInfo* server_info)
{
	if (!Check(server_info))
	{
		return nullptr;
	}
	static OtterObserver instance(server_info);
	return  &instance;
}

void OtterObserver::OnMessageReceived(const std::string& remote_user_id, const std::string message)
{
	if (message == "start-publish") {
		PublishStream();
	}
	else if(message == "control"){
		
	}
	else
	{
		if (mssage_callback_ != nullptr)
			mssage_callback_(remote_user_id, message);
	}
}

void OtterObserver::Connect(function<void(const string&)>on_success, function<void(unique_ptr<Exception>)> on_failed)
{
	pc_->Connect(signaling_address_, local_id_, on_success, on_failed);
}

void OtterObserver::SetReceiveMessageCallback(function<void(const string& remote_user_id, const string message)> callback)
{
	mssage_callback_ = callback;
}

void OtterObserver::SetRemoteID()
{
	pc_->AddAllowedRemoteId(remote_id_);
}

void OtterObserver::SendMesg(std::string message)
{
	pc_->Send(remote_id_, message,
		[=]() {
			cout << "Text messaging successfully!" << endl;
		},
		[=](unique_ptr<Exception> exception) {
			cout << "Messaging failed!" << endl;
		});
}

void OtterObserver::PublishStream()
{
	switch (stream_type_)
	{
	case StreamType::kSendScreenCast:
	{
		desktop_sp_.reset(new LocalDesktopStreamParameters(false, true));
		desktop_sp_->CapturePolicy(LocalDesktopStreamParameters::DesktopCapturePolicy::kEnableDirectX);
		desktop_sp_->SourceType(LocalDesktopStreamParameters::DesktopSourceType::kFullScreen);
		local_stream_ = LocalStream::Create(desktop_sp_, nullptr);
		break;
	}
	case StreamType::kSendYUV:
	{
		if (frame_generator_ != nullptr) {
			break;
		}
		customized_sp_.reset(new LocalCustomizedStreamParameters(false, true));
		customized_sp_->Fps(fps_);
		customized_sp_->Resolution(resolution_.width, resolution_.height);
		local_stream_ = LocalStream::Create(customized_sp_, std::move(frame_generator_));
		break;
	}
	case StreamType::kSendH264:
	{
		if (encoder_ == nullptr) {
			break;
		}
		customized_sp_.reset(new LocalCustomizedStreamParameters(false, true));
		customized_sp_->Fps(fps_);
		customized_sp_->Resolution(resolution_.width, resolution_.height);
		local_stream_ = LocalStream::Create(customized_sp_, encoder_.get());
		break;
	}
	default:
		break;
	}
	pc_->Publish(remote_id_,
		local_stream_,
		[=](std::shared_ptr<P2PPublication> publication) {
			publication_ = publication;
		},
		[=](std::unique_ptr<Exception> exception) {
		});
}

void OtterObserver::InsertAVPacket(uint8_t* buffer, size_t length, void* reserve)
{
	encoder_->InsertAVPacket(buffer, length, reserve);
}

void OtterObserver::InsertYUVFrame(uint8_t* buffer, size_t length, void* reserve)
{
	frame_generator_->InsertYUVFrame(buffer, length);
}
