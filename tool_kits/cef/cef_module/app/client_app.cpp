#include "client_app.h" 
#include <string>

#include "include/cef_cookie.h"
#include "include/cef_process_message.h"
#include "include/cef_task.h"
#include "include/cef_v8.h"
#include "manager/cef_manager.h"
#include "util/util.h"

namespace nim_cef
{

ClientApp::ClientApp() 
{
	last_node_is_editable_ = false;
}

//////////////////////////////////////////////////////////////////////////////////////////
// CefApp methods.
void ClientApp::OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line)
{
	// Pass additional command-line flags to the browser process.
	if (process_type.empty()) 
	{
		// �����ӽ���·���ܹؼ�����������ã����ܻᴥ��cef��һ��bug
		// cef��LoadUrl������Ⱦ����ʱ��������ӽ��̵�·�������ܻ�����һ��bug����IDE��debug״̬ʱ����
		// ����ָ�����ӽ���·���Ϳ�����

		// ����ʹ��sandbox�Ļ���������ʹ��������ӽ���;��ʹ��sandbox�Ļ�����һ�μ���flash���ʱ�ᵯ����������ʾ�У�����cef��bug��flash���ӽ��̶��߲��ɼ��
#if !defined(SUPPORT_CEF_FLASH)
#ifdef _DEBUG
 		command_line->AppendSwitchWithValue("browser-subprocess-path", "render_d.exe");
#else
		command_line->AppendSwitchWithValue("browser-subprocess-path", "render.exe");
#endif
#else
		command_line->AppendSwitchWithValue("ppapi-flash-version", "20.0.0.228");
		command_line->AppendSwitchWithValue("ppapi-flash-path", "PepperFlash\\pepflashplayer.dll");
#endif

		//ͬһ�����µ�ʹ��ͬһ����Ⱦ����
		command_line->AppendSwitch("process-per-site");
		command_line->AppendSwitch("disable-gpu");
		command_line->AppendSwitch("disable-gpu-compositing");
		//command_line->AppendSwitchWithValue("proxy-server", "SOCKS5://127.0.0.1:1080");	

		// ����������Ⱦ
		if (CefManager::GetInstance()->IsEnableOffsetRender())
		{
			command_line->AppendSwitch("disable-surfaces");
			command_line->AppendSwitch("enable-begin-frame-scheduling");
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
void ClientApp::OnRegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar)
{
	// Default schemes that support cookies.
	cookieable_schemes_.push_back("http");
	cookieable_schemes_.push_back("https");
}

}