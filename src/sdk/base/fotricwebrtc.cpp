#include "fotricwebrtc.h"
#include <iostream>
#include "otterobserver.h"
OtterObserver* g_observer;

IR_AONYX_EXPORTS void ir_webrtc_init(ir_webrtcsdk_info* info)
{
	g_observer = OtterObserver::Create((OtterObserver::WebrtcsdkInfo*)info);
	cout << "ir_webrtc_init" << endl;
	return;
}

IR_AONYX_EXPORTS void ir_webrtc_run()
{
	auto success_call = [&](const string uid)
	{
		
	};
	g_observer->Connect(success_call, nullptr);
	g_observer->SetRemoteID();
	cout << "ir_webrtc_connect" << endl;
	return;
}

IR_AONYX_EXPORTS void ir_webrtc_register_message(std::function<void(const string& remote_user_id, const string message)> message_callback)
{
	return g_observer->SetReceiveMessageCallback(message_callback);
}

IR_AONYX_EXPORTS void ir_webrtc_unpublish()
{
	cout << "ir_webrtc_unpublish" << endl;
	return void();
}

IR_AONYX_EXPORTS void ir_webrtc_send_message(std::string msg)
{
	g_observer->SendMesg(msg);
	cout << "ir_webrtc_send_message" << endl;
	return void();
}

IR_AONYX_EXPORTS void ir_webrtc_insert_avpacket(uint8_t* buffer, size_t length, void* reserve)
{
	return g_observer->InsertAVPacket(buffer,length,reserve);
}

IR_AONYX_EXPORTS void ir_webrtc_insert_yuvframe(uint8_t* buffer, size_t length, void* reserve)
{
	return g_observer->InsertYUVFrame(buffer, length, reserve);
}

IR_AONYX_EXPORTS void ir_webrtc_stop()
{
	cout << "ir_webrtc_stop" << endl;
	return void();
}

IR_AONYX_EXPORTS void ir_webrtc_cleanup()
{
	g_observer = nullptr;
	cout << "ir_webrtc_cleanup" << endl;
	return void();
}