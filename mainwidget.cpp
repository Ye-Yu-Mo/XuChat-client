#include "mainwidget.h"
#include "sessionfriendarea.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QPainterPath>

MainWidget* MainWidget::instance = nullptr;

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("XuChat");
    this->setWindowIcon(QIcon(":/resource/image/logo_w.png"));

    // 初始化窗口的样式布局
    initMainWindow();
    initLeftWindow();
    initRrightWindow();
    initMidWindow();
    initSignalSlot();
}

MainWidget::~MainWidget() {}

MainWidget* MainWidget::getInstance(){
    if(instance == nullptr)
    {
        // 以桌面为父窗口
        instance = new MainWidget;
    }
    return instance;
}
void MainWidget::initMainWindow(){
    QHBoxLayout* layout = new QHBoxLayout(); // 控件管理器
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);
    this->setMinimumHeight(655);

    windowLeft = new QWidget();
    windowRight = new QWidget();
    windowMid = new QWidget();

    windowLeft->setFixedWidth(88);
    windowMid->setFixedWidth(316);
    windowRight->setMinimumWidth(628);

    windowLeft->setStyleSheet("QWidget { background-color: rgb(18, 18, 18) }");
    windowMid->setStyleSheet("QWidget { background-color: rgb(25, 25, 25) }");
    windowRight->setStyleSheet("QWidget { background-color: rgb(17, 17, 17) }");

    layout->addWidget(windowLeft);
    layout->addWidget(windowMid);
    layout->addWidget(windowRight);
}

QPixmap createRoundedPixmap(const QPixmap& srcPixmap, int radius) {
    if (srcPixmap.isNull())
        return QPixmap();

    QPixmap roundedPixmap(srcPixmap.size());
    roundedPixmap.fill(Qt::transparent); // 填充透明背景

    QPainter painter(&roundedPixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QBrush brush(srcPixmap);
    QRect rect(0, 0, srcPixmap.width(), srcPixmap.height());

    QPainterPath path;
    path.addRoundedRect(rect, radius, radius);

    painter.setClipPath(path);
    painter.drawPixmap(rect, srcPixmap);

    return roundedPixmap;
}


void MainWidget::initLeftWindow(){
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSpacing(20);
    layout->setContentsMargins(0,50,0,0);
    windowLeft->setLayout(layout);

    // 用户头像
    userAvatar = new QPushButton();
    userAvatar->setFixedSize(45, 45);
    userAvatar->setIconSize(QSize(45, 45));
    QPixmap pixmap(":/resource/image/defaultAvatar.jpg");
    QPixmap roundedPixmap = createRoundedPixmap(pixmap, 100);
    userAvatar->setIcon(QIcon(roundedPixmap));
    userAvatar->setStyleSheet(
        "QPushButton {"
        "background-color: transparent;"
        "border-radius: 22px;"
        "border: 1px solid #ccc;"
        "}"
        );
    layout->addWidget(userAvatar, 1, Qt::AlignTop | Qt::AlignHCenter);


    // 会话按钮
    sessionTabBtn = new QPushButton();
    sessionTabBtn->setFixedSize(45,45);
    sessionTabBtn->setIconSize(QSize(30,30));
    sessionTabBtn->setIcon(QIcon(":/resource/image/session_active.png"));
    sessionTabBtn->setStyleSheet("QPushButton { background-color: transparent }");
    layout->addWidget(sessionTabBtn, 1, Qt::AlignTop | Qt::AlignHCenter);

    // 好友按钮
    friendTabBtn = new QPushButton();
    friendTabBtn->setFixedSize(45,45);
    friendTabBtn->setIconSize(QSize(30,30));
    friendTabBtn->setIcon(QIcon(":/resource/image/friend_inactive_w.png"));
    friendTabBtn->setStyleSheet("QPushButton { background-color: transparent }");
    layout->addWidget(friendTabBtn, 1, Qt::AlignTop | Qt::AlignHCenter);

    // 好友申请
    applyTabBtn = new QPushButton();
    applyTabBtn->setFixedSize(45,45);
    applyTabBtn->setIconSize(QSize(30,30));
    applyTabBtn->setIcon(QIcon(":/resource/image/apply_inactive_w.png"));
    applyTabBtn->setStyleSheet("QPushButton { background-color: transparent }");
    layout->addWidget(applyTabBtn, 1, Qt::AlignTop | Qt::AlignHCenter);

    layout->addStretch(20);
}
void MainWidget::initRrightWindow(){
}
void MainWidget::initMidWindow(){
    QGridLayout* layout = new QGridLayout();
    layout->setContentsMargins(0,20,0,0);
    layout->setSpacing(0);
    windowMid->setLayout(layout);

    searchEdit = new QLineEdit();
    searchEdit->setFixedHeight(30);
    searchEdit->setPlaceholderText("搜索");
    searchEdit->setStyleSheet("QLineEdit { border-radius: 5px;"
                            "background-color: rgb(37, 37, 37);"
                            "padding-left: 5px;"
                            "}");

    addFriendBtn = new QPushButton();
    addFriendBtn->setFixedSize(30, 30);
    addFriendBtn->setIcon(QIcon("://resource/image/cross.png"));
    QString style = "QPushButton {"
                    "border-radius: 5px;"
                    "background-color: rgb(37, 37, 37);"
                    "}";
    style += "QPushButton::pressed {background-color: rgb(64, 66, 68);}";
    addFriendBtn->setStyleSheet(style);

    SessionFriendArea* sessionFriednArea = new SessionFriendArea();
    QWidget* space1 = new QWidget();
    space1->setFixedWidth(10);
    QWidget* space2 = new QWidget();
    space2->setFixedWidth(10);
    QWidget* space3 = new QWidget();
    space3->setFixedWidth(10);

    layout->addWidget(space1, 0, 0);
    layout->addWidget(searchEdit,0, 1);
    layout->addWidget(space2, 0, 2);
    layout->addWidget(addFriendBtn, 0, 3);
    layout->addWidget(space3, 0, 4);
    layout->addWidget(sessionFriednArea, 1, 0, 1, 5);
}

void MainWidget::switchTabToSession(){
    activeTab = SESSION_LIST;
    sessionTabBtn->setIcon(QIcon(":/resource/image/session_active"));
    friendTabBtn->setIcon(QIcon(":/resource/image/friend_inactive_w"));
    applyTabBtn->setIcon(QIcon(":/resource/image/apply_inactive_w"));
    this->loadSessionList();
}
void MainWidget::switchTabToFriend(){
    activeTab = FRIEND_LIST;
    sessionTabBtn->setIcon(QIcon(":/resource/image/session_inactive_w"));
    friendTabBtn->setIcon(QIcon(":/resource/image/friend_active"));
    applyTabBtn->setIcon(QIcon(":/resource/image/apply_inactive_w"));
    this->loadFriendList();
}
void MainWidget::switchTabToApply(){
    activeTab = APPLY_LIST;
    sessionTabBtn->setIcon(QIcon(":/resource/image/session_inactive_w"));
    friendTabBtn->setIcon(QIcon(":/resource/image/friend_inactive_w"));
    applyTabBtn->setIcon(QIcon(":/resource/image/apply_active"));
    this->loadApplyList();
}

void MainWidget::loadSessionList(){

}
void MainWidget::loadFriendList(){

}
void MainWidget::loadApplyList(){

}

/// @brief 连接信号槽 处理标签页切换
void MainWidget::initSignalSlot(){
    connect(sessionTabBtn, &QPushButton::clicked, this, &MainWidget::switchTabToSession);
    connect(friendTabBtn, &QPushButton::clicked, this, &MainWidget::switchTabToFriend);
    connect(applyTabBtn, &QPushButton::clicked, this, &MainWidget::switchTabToApply);
}
