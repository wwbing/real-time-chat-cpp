#ifndef USERMGR_H
#define USERMGR_H
#include <QObject>
#include <memory>
#include <singleton.h>
#include "userdata.h"
#include <vector>

class UserMgr:public QObject,public Singleton<UserMgr>,public std::enable_shared_from_this<UserMgr>
{
    Q_OBJECT

public:
    friend class Singleton<UserMgr>;
    ~ UserMgr();

    void SetUserInfo(std::shared_ptr<UserInfo> user_info);
    void SetToken(QString token);
    void AppendApplyList(QJsonArray array);
    void AppendFriendList(QJsonArray array);
    void AddApplyList(std::shared_ptr<ApplyInfo> app);
    void AddFriend(std::shared_ptr<AuthRsp> auth_rsp);
    void AddFriend(std::shared_ptr<AuthInfo> auth_info);
    void AppendFriendChatMsg(int friend_id,std::vector<std::shared_ptr<TextChatData>>);

    int                                         GetUid();
    QString                                     GetName();
    QString                                     GetIcon();
    std::shared_ptr<UserInfo>                   GetUserInfo();
    std::vector<std::shared_ptr<ApplyInfo>>     GetApplyList();
    std::vector<std::shared_ptr<FriendInfo>>    GetChatListPerPage();
    std::vector<std::shared_ptr<FriendInfo>>    GetConListPerPage();
    std::shared_ptr<FriendInfo>                 GetFriendById(int uid);

    bool AlreadyApply(int uid);
    bool IsLoadChatFin();
    void UpdateChatLoadedCount();
    void UpdateContactLoadedCount();
    bool IsLoadConFin();
    bool CheckFriendById(int uid);

private:
    UserMgr();

    std::shared_ptr<UserInfo>                   _user_info;
    std::vector<std::shared_ptr<ApplyInfo>>     _apply_list;
    std::vector<std::shared_ptr<FriendInfo>>    _friend_list;
    QMap<int, std::shared_ptr<FriendInfo>>      _friend_map;
    QString                                     _token;
    int                                         _chat_loaded;
    int                                         _contact_loaded;

public slots:
    void SlotAddFriendRsp(std::shared_ptr<AuthRsp> rsp);
    void SlotAddFriendAuth(std::shared_ptr<AuthInfo> auth);
};

#endif // USERMGR_H
