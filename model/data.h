#pragma once
#include <Qstring>
#include <QIcon>
#include <QUuid>
#include <QDateTime>
#include <QFile>
#include <QDebug>
namespace Model{

/// @brief 打印日志


/// @brief 获取格式化时间字符串
static inline QString getFormatTime(int64_t timestamp){
    QDateTime datetime = QDateTime::fromMSecsSinceEpoch(timestamp);
    return datetime.toString("MM-DD HH:mm:ss");
}

/// @brief 获取当前时间戳
static inline int64_t getTimestamp(){
    return QDateTime::currentSecsSinceEpoch();
}

/// @brief 从QByteArray转换成QIcon
static inline QIcon getIcon(const QByteArray & byteArray){
    QPixmap pixmap;
    pixmap.loadFromData(byteArray);
    QIcon icon(pixmap);
    return icon;
}

/// @brief 读取二进制文件
static inline QByteArray loadFileToByteArray(const QString& path){
    QFile file(path);
    if (!file.open(QFile::ReadOnly))
    {
        qDebug() << "文件打开失败！";
        return QByteArray();
    }
    return file.readAll();
}

/// @brief 写入二进制文件
static inline void writeByteArrayToFile(const QString& path, const QByteArray& content){
    QFile file(path);
    if (!file.open(QFile::WriteOnly))
    {
        qDebug() << "文件打开失败！";
        return;
    }
    file.write(content);
    file.flush(); // 刷新缓冲区
    file.close();
}
/// @brief 用户信息
class UserInfo{
public:
    QString userID = "";         ///< 用户ID
    QString nickname = "";       ///< 用户昵称
    QString description = "";    ///< 用户签名
    QString phone = "";          ///< 手机号
    QIcon avatar;                ///< 用户头像
};

/// @brief 消息类型
enum MessageType{
    TEXT_TYPE,  ///< 文本类型
    IMAGE_TYPE, ///< 图片类型
    FILE_TYPE,  ///< 文件类型
    SPEECH_TYPE ///< 语音类型
};

/// @brief 消息
class Message{
public:
    QString messageID = "";       ///< 消息ID
    QString chatSessionID = "";   ///< 聊天会话ID
    QString time = "";            ///< 消息的时间 "12-25 21:30"
    MessageType messageType;      ///< 消息类型
    UserInfo sender;              ///< 消息发送者
    QByteArray content;           ///< 消息内容
    QString fileID = "" ;         ///< 文件的身份标识 文件、图片、语音时有效 其余时候为空
    QString fileName = "";        ///< 文件名称 文件、图片、语音时有效 其余时候为空


    /// 工厂方法构建消息对象，extraInfo可以用于初始化fileID
    static Message makeMessage(MessageType type, const QString &chatSessionID, const UserInfo &sender,
                                const QByteArray &content, const QString& extraInfo){
        if(type == MessageType::TEXT_TYPE){
            return makeTextMessage(chatSessionID, sender, content);
        } else if (type == MessageType::IMAGE_TYPE) {
            return makeImageMessage(chatSessionID, sender, content);
        }else if (type == MessageType::FILE_TYPE) {
            return makeFileMessage(chatSessionID, sender, content, extraInfo);
        }else if (type == MessageType::SPEECH_TYPE) {
            return makeSpeechMessage(chatSessionID, sender, content);
        }else {
            // 未知消息类型
            return Message();
        }

    }
private:
    static QString getUUID(){
        return "M" + QUuid::createUuid().toString().sliced(25, 12);
    }



    static Message makeTextMessage(const QString &chatSessionID, const UserInfo &sender, const QByteArray &content){
        Message message;
        message.messageID = getUUID();
        message.chatSessionID = chatSessionID;
        message.sender = sender;
        message.content = content;
        message.messageType = MessageType::TEXT_TYPE;
        message.time = getFormatTime(getTimestamp());
        message.fileID = "";
        message.fileName = "";
        return message;
    }
    static Message makeImageMessage(const QString &chatSessionID, const UserInfo &sender, const QByteArray &content){
        Message message;
        message.messageID = getUUID();
        message.chatSessionID = chatSessionID;
        message.sender = sender;
        message.content = content;
        message.messageType = MessageType::IMAGE_TYPE;
        message.time = getFormatTime(getTimestamp());
        message.fileID = "";
        message.fileName = "";
        return message;
    }
    static Message makeFileMessage(const QString &chatSessionID, const UserInfo &sender,
                                   const QByteArray &content, const QString& filename){
        Message message;
        message.messageID = getUUID();
        message.chatSessionID = chatSessionID;
        message.sender = sender;
        message.content = content;
        message.messageType = MessageType::TEXT_TYPE;
        message.time = getFormatTime(getTimestamp());
        message.fileID = "";
        message.fileName = filename;
        return message;
    }
    static Message makeSpeechMessage(const QString &chatSessionID, const UserInfo &sender, const QByteArray &content){
        Message message;
        message.messageID = getUUID();
        message.chatSessionID = chatSessionID;
        message.sender = sender;
        message.content = content;
        message.messageType = MessageType::SPEECH_TYPE;
        message.time = getFormatTime(getTimestamp());
        message.fileID = "";
        message.fileName = "";
        return message;
    }
};

/// @brief 用户聊天会话
class ChatSessionInfo{
public:
    QString chatSessionID = "";   ///< 会话编号
    QString chatSessionName = ""; ///< 会话名称
    Message lastMessage;          ///< 最近一条消息
    QIcon  avater;                ///< 会话头像
    QString userID = "";          ///< 用于表示聊天对方的ID，私聊是对方ID，群聊为空
};

} // end Model
