#pragma once
#include "iteam_info_ui.h"
#include "module/service/user_service.h"
#include "module/service/team_service.h"
#include "shared/ui/msgbox.h"
#include "module/service/photo_service.h"
namespace nim_comp
{
	class TeamInfoBox : public ui::VBox,public ITeamInfoUI
	{
	public:
		TeamInfoBox() = default;
		TeamInfoBox(bool create_or_display, nim::NIMTeamType type, const std::string& team_id, const nim::TeamInfo& team_info, bool value= false);
		virtual ~TeamInfoBox();
	public:
		virtual void DoInit() override;
		bool IsCreateOrDisplay() const;
		std::wstring GetTeamID() const;
		nim::NIMTeamType GetTeamType() const;
		/**
		* 设置标题栏标题
		* @param[in] title 标题栏标题
		* @return void	无返回值
		*/
		virtual void SetTaskbarTitle(const std::wstring &title) override;
		virtual void Close(UINT nRet = 0) override;
		virtual void ActiveWindow() override;
		void AttachSetTaskbarTitle(const std::function<void(const std::wstring&)>& cb);
		void AttachClose(const std::function<void(UINT)>& cb);
		void AttachActive(const std::function<void()>& cb);
		/**
		* 更新群成员信息
		* @return void	无返回值
		*/
		virtual void UpdateTeamMember() override;
	private:
		/**
		* 响应获取到群成员信息的回调含塑化
		* @param[in] team_id 群组id
		* @param[in] count 群成员数量
		* @param[in] team_member_list 群成员信息
		* @return void	无返回值
		*/
		void OnGetTeamMembers(const std::string& team_id, int count, const std::list<nim::TeamMemberProperty>& team_member_list);

	

		/**
		* 处理群头像点击的消息
		* @param[in] args 消息的相关信息
		* @return bool true 继续传递控件消息，false 停止传递控件消息
		*/
		bool OnHeadImageClicked(ui::EventArgs* args);
	private:
		/**
		* 处理头像修改完毕后的回调函数
		* @param[in] id 用户id
		* @param[in] url 头像的下载地址
		* @return void	无返回值
		*/
		void OnModifyHeaderComplete(const std::string& id, const std::string &url);

		/**
		* 添加一个邀请成员的按钮到界面上
		* @return void	无返回值
		*/
		void AddInviteButton();

		/**
		* 处理邀请成员的按钮被点击的消息
		* @param[in] param 消息的相关信息
		* @return bool true 继续传递控件消息，false 停止传递控件消息
		*/
		bool OnInviteUesrBtnClick(ui::EventArgs *param);

		/**
		* 响应成员邀请完毕的回调函数
		* @param[in] friend_list 邀请的好友列表
		* @param[in] team_list 无需关心的参数
		* @return void	无返回值
		*/
		void SelectedCompleted(const std::list<UTF8String>& friend_list, const std::list<UTF8String>& team_list, bool delete_enable);

		/**
		* 创建一个群成员项控件
		* @param[in] member_info 群成员信息
		* @return void	无返回值
		*/
		ui::HBox* CreateTeamMemberListItem(const nim::TeamMemberProperty& member_info, bool delelte_enable = false);

		/**
		* 根据自己的身份更新界面显示的效果
		* @return void	无返回值
		*/
		void UpdateUIByIdentity();

		/**
		* 处理群成员删除按钮的单击消息
		* @param[in] container_element 群成员控件
		* @param[in] user_id 群成员用户id
		* @param[in] args 消息的相关信息
		* @return bool true 继续传递控件消息，false 停止传递控件消息
		*/
		bool OnBtnDeleteClick(ui::Box* container_element, const UTF8String& user_id, ui::EventArgs* args);

		/**
		* 响应确认是否删除的提示框的回调函数
		* @param[in] user_id 用户id
		* @param[in] ret 提示框返回值
		* @return void	无返回值
		*/
		void OnMsgbox(const UTF8String& user_id, MsgBoxRet ret);

		/**
		* 处理群成员项鼠标移入的消息
		* @param[in] team_member_item 群成员控件
		* @param[in] args 消息的相关信息
		* @return bool true 继续传递控件消息，false 停止传递控件消息
		*/
		bool OnTeamMemberItemMouseEnter(ui::Box* team_member_item, ui::EventArgs* args);

		/**
		* 处理群成员项鼠标移出的消息
		* @param[in] team_member_item 群成员控件
		* @param[in] args 消息的相关信息
		* @return bool true 继续传递控件消息，false 停止传递控件消息
		*/
		bool OnTeamMemberItemMouseLeave(ui::Box* team_member_item, ui::EventArgs* args);

		/**
		* 处理群成员项单击消息
		* @param[in] user_id 群成员id
		* @param[in] args 消息的相关信息
		* @return bool true 继续传递控件消息，false 停止传递控件消息
		*/
		bool OnBtnHeadImageClick(const UTF8String& user_id, ui::EventArgs* args);

		/**
		* 处理确认按钮单击消息
		* @param[in] param 消息的相关信息
		* @return bool true 继续传递控件消息，false 停止传递控件消息
		*/
		bool OnBtnConfirmClick(ui::EventArgs* param);

		/**
		* 处理取消按钮单击消息
		* @param[in] param 消息的相关信息
		* @return bool true 继续传递控件消息，false 停止传递控件消息
		*/
		bool OnBtnCancelClick(ui::EventArgs* param);

		/**
		* 处理解散群按钮单击消息
		* @param[in] param 消息的相关信息
		* @return bool true 继续传递控件消息，false 停止传递控件消息
		*/
		bool OnBtnDissmissClick(ui::EventArgs* param);

		/**
		* 处理退出群按钮单击消息
		* @param[in] param 消息的相关信息
		* @return bool true 继续传递控件消息，false 停止传递控件消息
		*/
		bool OnBtnQuitClick(ui::EventArgs* param);

		/**
		* 响应群成员增加的回调函数
		* @param[in] tid 群组id
		* @param[in] team_member_info 群成员信息
		* @return void	无返回值
		*/
		void OnTeamMemberAdd(const std::string& tid, const nim::TeamMemberProperty& team_member_info);

		/**
		* 响应群成员移除的回调函数
		* @param[in] tid 群组id
		* @param[in] uid 用户id
		* @return void	无返回值
		*/
		void OnTeamMemberRemove(const std::string& tid, const std::string& uid);

		/**
		* 响应群成员昵称改变的回调函数
		* @param[in] tid_uid 包含群组id和用户id的字符串
		* @param[in] team_card 群昵称
		* @return void	无返回值
		*/
		void OnTeamMemberChange(const std::string& tid_uid, const std::string& team_card);

		/**
		* 响应群管理员改变的回调函数
		* @param[in] tid 群组id
		* @param[in] uid 用户id
		* @param[in] admin 是否为管理员
		* @return void	无返回值
		*/
		void OnTeamAdminSet(const std::string& tid, const std::string& uid, bool admin);

		/**
		* 响应群主改变的回调函数
		* @param[in] tid 群组id
		* @param[in] uid 新群主id
		* @return void	无返回值
		*/
		void OnTeamOwnerChange(const std::string& tid, const std::string& uid);

		/**
		* 响应用户信息改变的回调函数
		* @param[in] uinfos 用户信息列表
		* @return void	无返回值
		*/
		void OnUserInfoChange(const std::list<nim::UserNameCard>& uinfos);

		/**
		* 响应用户头像改变的回调函数
		* @param[in] type 头像类型
		* @param[in] accid 用户id
		* @param[in] photo_path 头像路径
		* @return void	无返回值
		*/
		void OnUserPhotoReady(PhotoType type, const std::string& accid, const std::wstring &photo_path);

		/**
		* 响应群移除的回调函数
		* @param[in] tid 群组id
		* @return void	无返回值
		*/
		void OnTeamRemove(const std::string& tid);
		/**
		* 响应群名称改变事件
		* @param[in] team_info 群信息
		* @return void	无返回值
		*/
		void OnTeamNameChange(const nim::TeamInfo& team_info);
		/**
		* 判断是否为可以显示到群列表的群成员类型
		* @param[in] user_type 群成员类型
		* @return bool true 是，false 否
		*/
		bool IsTeamMemberType(const nim::NIMTeamUserType user_type);
	
		void RefreshInfo(nim::TeamInfo* team_info);
	private:
		ui::ListBox* tile_box_;
		ui::RichEdit* re_team_name_;
		ui::RichEdit* re_team_intro_;
		ui::Button* invitebtn_;
		ui::Button* btn_dismiss_;
		ui::Button* btn_quit_;
		ui::Button* btn_header_ = nullptr;

	private:
		bool create_or_display_;
		std::string tid_;
		nim::NIMTeamType type_;
		nim::TeamInfo team_info_;
		std::map<std::string, nim::TeamMemberProperty> team_member_list_;
		nim::TeamMemberProperty my_property_;
		AutoUnregister unregister_cb;
		std::function<void(const std::wstring& title)> taskbar_title_function_;
		std::function<void(UINT nRet)> close_function_;
		std::function<void()> active_function_;
	private:
		std::wstring temp_file_path_;
		std::string new_header_url_;
		bool view_mode_;
	};
}