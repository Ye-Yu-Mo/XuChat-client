#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
class MainWidget : public QWidget
{
    Q_OBJECT

private:
    static MainWidget* instance;
    MainWidget(QWidget *parent = nullptr);
public:
    static MainWidget* getInstance();
    ~MainWidget();

private:
    QWidget* windowLeft; ///< 窗口左侧
    QWidget* windowMid; ///< 窗口中间
    QWidget* windowRight; ///< 窗口右侧

    // 导航栏按钮
    QPushButton* userAvatar;
    QPushButton* sessionTabBtn;
    QPushButton* friendTabBtn;
    QPushButton* applyTabBtn;

    enum ActiveTab {
        SESSION_LIST,
        FRIEND_LIST,
        APPLY_LIST
    };

    ActiveTab activeTab = SESSION_LIST;

    void initMainWindow();
    void initLeftWindow();
    void initRrightWindow();
    void initMidWindow();

    void initSignalSlot();

    void switchTabToSession();
    void switchTabToFriend();
    void switchTabToApply();

    void loadSessionList();
    void loadFriendList();
    void loadApplyList();
};
#endif // MAINWIDGET_H
