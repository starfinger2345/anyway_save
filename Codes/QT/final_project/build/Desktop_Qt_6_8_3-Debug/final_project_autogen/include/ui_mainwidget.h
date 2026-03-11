/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *L_top_bar;
    QLabel *QL_top_icon;
    QLabel *QL_top_title;
    QDateTimeEdit *QDT;
    QHBoxLayout *L_CAM;
    QVBoxLayout *L_CAM1_background;
    QWidget *W_CAM1_background;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *L_CAM1;
    QLabel *QL_depth_header;
    QLabel *QL_depth_camera;
    QVBoxLayout *L_CAM2_background;
    QWidget *W_CAM2_background;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *L_CAM2;
    QLabel *QL_omx_header;
    QLabel *QL_omx_camera;
    QHBoxLayout *L_map_key;
    QWidget *W_CAM1_background_4;
    QVBoxLayout *verticalLayout_9;
    QVBoxLayout *L_CAM1_4;
    QLabel *QL_depth_header_8;
    QGridLayout *gridLayout_4;
    QPushButton *PB_arrow_up;
    QPushButton *PB_arrow_left;
    QPushButton *PB_arrow_right;
    QPushButton *PB_arrow_stop;
    QPushButton *PB_arrow_down;
    QWidget *W_CAM1_background_2;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *L_CAM2_3;
    QLabel *QL_depth_header_4;
    QLabel *QL_map;
    QWidget *W_CAM2_background_2;
    QVBoxLayout *verticalLayout_8;
    QLabel *QL_lift_header_7;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *L_lift_grid;
    QPushButton *PB_lift_down;
    QPushButton *PB_lift_stop;
    QPushButton *PB_lift_up;
    QVBoxLayout *verticalLayout_2;
    QLabel *L_lift_state_6;
    QLabel *L_lift_state_5;
    QLabel *L_lift_state_4;
    QLabel *L_lift_state_3;
    QLabel *L_lift_state_2;
    QLabel *L_lift_state_1;
    QLabel *L_lift_state_0;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QProgressBar *PBAR_battery;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName("MainWidget");
        MainWidget->resize(900, 825);
        QFont font;
        font.setPointSize(15);
        MainWidget->setFont(font);
        MainWidget->setAcceptDrops(false);
        MainWidget->setAutoFillBackground(false);
        MainWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(33, 33, 33);"));
        verticalLayout_3 = new QVBoxLayout(MainWidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        L_top_bar = new QHBoxLayout();
        L_top_bar->setObjectName("L_top_bar");
        QL_top_icon = new QLabel(MainWidget);
        QL_top_icon->setObjectName("QL_top_icon");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QL_top_icon->sizePolicy().hasHeightForWidth());
        QL_top_icon->setSizePolicy(sizePolicy);
        QL_top_icon->setMinimumSize(QSize(33, 33));
        QL_top_icon->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/top_bar_icon.png")));
        QL_top_icon->setScaledContents(false);
        QL_top_icon->setAlignment(Qt::AlignmentFlag::AlignCenter);
        QL_top_icon->setWordWrap(false);

        L_top_bar->addWidget(QL_top_icon);

        QL_top_title = new QLabel(MainWidget);
        QL_top_title->setObjectName("QL_top_title");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("A2Z")});
        font1.setPointSize(18);
        font1.setBold(true);
        QL_top_title->setFont(font1);
        QL_top_title->setStyleSheet(QString::fromUtf8("color: rgb(255, 106, 0);"));

        L_top_bar->addWidget(QL_top_title);

        QDT = new QDateTimeEdit(MainWidget);
        QDT->setObjectName("QDT");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("A2Z")});
        font2.setPointSize(15);
        font2.setBold(true);
        QDT->setFont(font2);
        QDT->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        QDT->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        QDT->setStyleSheet(QString::fromUtf8("color: rgb(242, 244, 241);\n"
"border: none;"));
        QDT->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        QDT->setReadOnly(true);
        QDT->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        QDT->setCurrentSection(QDateTimeEdit::Section::NoSection);
        QDT->setDisplayFormat(QString::fromUtf8("ss:mm:HH dd-MM-yyyy  "));
        QDT->setCalendarPopup(false);

        L_top_bar->addWidget(QDT);

        L_top_bar->setStretch(1, 1);
        L_top_bar->setStretch(2, 1);

        verticalLayout->addLayout(L_top_bar);

        L_CAM = new QHBoxLayout();
        L_CAM->setObjectName("L_CAM");
        L_CAM1_background = new QVBoxLayout();
        L_CAM1_background->setSpacing(0);
        L_CAM1_background->setObjectName("L_CAM1_background");
        L_CAM1_background->setContentsMargins(0, 0, 0, 0);
        W_CAM1_background = new QWidget(MainWidget);
        W_CAM1_background->setObjectName("W_CAM1_background");
        W_CAM1_background->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        verticalLayout_4 = new QVBoxLayout(W_CAM1_background);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        L_CAM1 = new QVBoxLayout();
        L_CAM1->setSpacing(5);
        L_CAM1->setObjectName("L_CAM1");
        L_CAM1->setContentsMargins(5, 5, 5, 5);
        QL_depth_header = new QLabel(W_CAM1_background);
        QL_depth_header->setObjectName("QL_depth_header");
        QPalette palette;
        QBrush brush(QColor(252, 252, 252, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(255, 106, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        QL_depth_header->setPalette(palette);
        QFont font3;
        font3.setFamilies({QString::fromUtf8("A2Z")});
        font3.setPointSize(13);
        font3.setWeight(QFont::DemiBold);
        font3.setItalic(false);
        QL_depth_header->setFont(font3);
        QL_depth_header->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 106, 0);\n"
"font: 600 13pt \"A2Z\";"));
        QL_depth_header->setAlignment(Qt::AlignmentFlag::AlignCenter);

        L_CAM1->addWidget(QL_depth_header);

        QL_depth_camera = new QLabel(W_CAM1_background);
        QL_depth_camera->setObjectName("QL_depth_camera");
        QL_depth_camera->setStyleSheet(QString::fromUtf8(""));
        QL_depth_camera->setAlignment(Qt::AlignmentFlag::AlignCenter);

        L_CAM1->addWidget(QL_depth_camera);

        L_CAM1->setStretch(0, 2);
        L_CAM1->setStretch(1, 9);

        verticalLayout_4->addLayout(L_CAM1);


        L_CAM1_background->addWidget(W_CAM1_background);


        L_CAM->addLayout(L_CAM1_background);

        L_CAM2_background = new QVBoxLayout();
        L_CAM2_background->setSpacing(0);
        L_CAM2_background->setObjectName("L_CAM2_background");
        L_CAM2_background->setContentsMargins(0, 0, 0, 0);
        W_CAM2_background = new QWidget(MainWidget);
        W_CAM2_background->setObjectName("W_CAM2_background");
        W_CAM2_background->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        verticalLayout_5 = new QVBoxLayout(W_CAM2_background);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        L_CAM2 = new QVBoxLayout();
        L_CAM2->setObjectName("L_CAM2");
        L_CAM2->setContentsMargins(5, 5, 5, 5);
        QL_omx_header = new QLabel(W_CAM2_background);
        QL_omx_header->setObjectName("QL_omx_header");
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        QL_omx_header->setPalette(palette1);
        QL_omx_header->setFont(font3);
        QL_omx_header->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 106, 0);\n"
"font: 600 13pt \"A2Z\";"));
        QL_omx_header->setAlignment(Qt::AlignmentFlag::AlignCenter);

        L_CAM2->addWidget(QL_omx_header);

        QL_omx_camera = new QLabel(W_CAM2_background);
        QL_omx_camera->setObjectName("QL_omx_camera");
        QL_omx_camera->setAlignment(Qt::AlignmentFlag::AlignCenter);

        L_CAM2->addWidget(QL_omx_camera);

        L_CAM2->setStretch(0, 2);
        L_CAM2->setStretch(1, 9);

        verticalLayout_5->addLayout(L_CAM2);


        L_CAM2_background->addWidget(W_CAM2_background);


        L_CAM->addLayout(L_CAM2_background);


        verticalLayout->addLayout(L_CAM);

        L_map_key = new QHBoxLayout();
        L_map_key->setObjectName("L_map_key");
        L_map_key->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        W_CAM1_background_4 = new QWidget(MainWidget);
        W_CAM1_background_4->setObjectName("W_CAM1_background_4");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(W_CAM1_background_4->sizePolicy().hasHeightForWidth());
        W_CAM1_background_4->setSizePolicy(sizePolicy1);
        W_CAM1_background_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        verticalLayout_9 = new QVBoxLayout(W_CAM1_background_4);
        verticalLayout_9->setObjectName("verticalLayout_9");
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        L_CAM1_4 = new QVBoxLayout();
        L_CAM1_4->setObjectName("L_CAM1_4");
        L_CAM1_4->setContentsMargins(5, 5, 5, 5);
        QL_depth_header_8 = new QLabel(W_CAM1_background_4);
        QL_depth_header_8->setObjectName("QL_depth_header_8");
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        QL_depth_header_8->setPalette(palette2);
        QL_depth_header_8->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 106, 0);\n"
"font: 600 13pt \"A2Z\";"));
        QL_depth_header_8->setAlignment(Qt::AlignmentFlag::AlignCenter);

        L_CAM1_4->addWidget(QL_depth_header_8);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName("gridLayout_4");
        PB_arrow_up = new QPushButton(W_CAM1_background_4);
        PB_arrow_up->setObjectName("PB_arrow_up");
        sizePolicy1.setHeightForWidth(PB_arrow_up->sizePolicy().hasHeightForWidth());
        PB_arrow_up->setSizePolicy(sizePolicy1);
        QPalette palette3;
        QBrush brush2(QColor(242, 244, 241, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        QBrush brush3(QColor(59, 56, 56, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush3);
        QBrush brush4(QColor(39, 191, 115, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Highlight, brush4);
        QBrush brush5(QColor(242, 244, 241, 128));
        brush5.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Active, QPalette::PlaceholderText, brush5);
#endif
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::Highlight, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush5);
#endif
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush3);
        palette3.setBrush(QPalette::Disabled, QPalette::Highlight, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush5);
#endif
        PB_arrow_up->setPalette(palette3);
        QFont font4;
        font4.setPointSize(14);
        PB_arrow_up->setFont(font4);
        PB_arrow_up->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        PB_arrow_up->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        PB_arrow_up->setStyleSheet(QString::fromUtf8("background-color: rgb(59, 56, 56);\n"
"color: rgb(242, 244, 241);\n"
"border-color: rgba(191, 64, 64, 0);"));

        gridLayout_4->addWidget(PB_arrow_up, 0, 1, 1, 1);

        PB_arrow_left = new QPushButton(W_CAM1_background_4);
        PB_arrow_left->setObjectName("PB_arrow_left");
        sizePolicy1.setHeightForWidth(PB_arrow_left->sizePolicy().hasHeightForWidth());
        PB_arrow_left->setSizePolicy(sizePolicy1);
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette4.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette4.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette4.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette4.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette4.setBrush(QPalette::Active, QPalette::Window, brush3);
        palette4.setBrush(QPalette::Active, QPalette::Highlight, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette4.setBrush(QPalette::Active, QPalette::PlaceholderText, brush5);
#endif
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette4.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette4.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette4.setBrush(QPalette::Inactive, QPalette::Window, brush3);
        palette4.setBrush(QPalette::Inactive, QPalette::Highlight, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette4.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush5);
#endif
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette4.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette4.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette4.setBrush(QPalette::Disabled, QPalette::Window, brush3);
        palette4.setBrush(QPalette::Disabled, QPalette::Highlight, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette4.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush5);
#endif
        PB_arrow_left->setPalette(palette4);
        PB_arrow_left->setFont(font4);
        PB_arrow_left->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        PB_arrow_left->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        PB_arrow_left->setStyleSheet(QString::fromUtf8("background-color: rgb(59, 56, 56);\n"
"border-color: rgba(191, 64, 64, 0);\n"
"color: rgb(242, 244, 241);"));

        gridLayout_4->addWidget(PB_arrow_left, 1, 0, 1, 1);

        PB_arrow_right = new QPushButton(W_CAM1_background_4);
        PB_arrow_right->setObjectName("PB_arrow_right");
        sizePolicy1.setHeightForWidth(PB_arrow_right->sizePolicy().hasHeightForWidth());
        PB_arrow_right->setSizePolicy(sizePolicy1);
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette5.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette5.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette5.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette5.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette5.setBrush(QPalette::Active, QPalette::Window, brush3);
        palette5.setBrush(QPalette::Active, QPalette::Highlight, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette5.setBrush(QPalette::Active, QPalette::PlaceholderText, brush5);
#endif
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette5.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette5.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette5.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette5.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette5.setBrush(QPalette::Inactive, QPalette::Window, brush3);
        palette5.setBrush(QPalette::Inactive, QPalette::Highlight, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette5.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush5);
#endif
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette5.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        palette5.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette5.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette5.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette5.setBrush(QPalette::Disabled, QPalette::Window, brush3);
        palette5.setBrush(QPalette::Disabled, QPalette::Highlight, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette5.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush5);
#endif
        PB_arrow_right->setPalette(palette5);
        PB_arrow_right->setFont(font4);
        PB_arrow_right->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        PB_arrow_right->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        PB_arrow_right->setStyleSheet(QString::fromUtf8("background-color: rgb(59, 56, 56);\n"
"color: rgb(242, 244, 241);\n"
"border-color: rgba(191, 64, 64, 0);"));

        gridLayout_4->addWidget(PB_arrow_right, 1, 2, 1, 1);

        PB_arrow_stop = new QPushButton(W_CAM1_background_4);
        PB_arrow_stop->setObjectName("PB_arrow_stop");
        sizePolicy1.setHeightForWidth(PB_arrow_stop->sizePolicy().hasHeightForWidth());
        PB_arrow_stop->setSizePolicy(sizePolicy1);
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette6.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette6.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette6.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette6.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette6.setBrush(QPalette::Active, QPalette::Window, brush3);
        palette6.setBrush(QPalette::Active, QPalette::Highlight, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette6.setBrush(QPalette::Active, QPalette::PlaceholderText, brush5);
#endif
        palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette6.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette6.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette6.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette6.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette6.setBrush(QPalette::Inactive, QPalette::Window, brush3);
        palette6.setBrush(QPalette::Inactive, QPalette::Highlight, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette6.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush5);
#endif
        palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette6.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        palette6.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette6.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette6.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette6.setBrush(QPalette::Disabled, QPalette::Window, brush3);
        palette6.setBrush(QPalette::Disabled, QPalette::Highlight, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette6.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush5);
#endif
        PB_arrow_stop->setPalette(palette6);
        PB_arrow_stop->setFont(font4);
        PB_arrow_stop->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        PB_arrow_stop->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        PB_arrow_stop->setStyleSheet(QString::fromUtf8("background-color: rgb(59, 56, 56);\n"
"color: rgb(242, 244, 241);\n"
"border-color: rgba(191, 64, 64, 0);"));

        gridLayout_4->addWidget(PB_arrow_stop, 1, 1, 1, 1);

        PB_arrow_down = new QPushButton(W_CAM1_background_4);
        PB_arrow_down->setObjectName("PB_arrow_down");
        sizePolicy1.setHeightForWidth(PB_arrow_down->sizePolicy().hasHeightForWidth());
        PB_arrow_down->setSizePolicy(sizePolicy1);
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette7.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette7.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette7.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette7.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette7.setBrush(QPalette::Active, QPalette::Window, brush3);
        palette7.setBrush(QPalette::Active, QPalette::Highlight, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette7.setBrush(QPalette::Active, QPalette::PlaceholderText, brush5);
#endif
        palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette7.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette7.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette7.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette7.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette7.setBrush(QPalette::Inactive, QPalette::Window, brush3);
        palette7.setBrush(QPalette::Inactive, QPalette::Highlight, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette7.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush5);
#endif
        palette7.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette7.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        palette7.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette7.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette7.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette7.setBrush(QPalette::Disabled, QPalette::Window, brush3);
        palette7.setBrush(QPalette::Disabled, QPalette::Highlight, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette7.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush5);
#endif
        PB_arrow_down->setPalette(palette7);
        PB_arrow_down->setFont(font4);
        PB_arrow_down->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        PB_arrow_down->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        PB_arrow_down->setStyleSheet(QString::fromUtf8("background-color: rgb(59, 56, 56);\n"
"border-color: rgba(191, 64, 64, 0);\n"
"color: rgb(242, 244, 241);"));

        gridLayout_4->addWidget(PB_arrow_down, 2, 1, 1, 1);

        gridLayout_4->setRowStretch(0, 1);
        gridLayout_4->setRowStretch(1, 1);
        gridLayout_4->setRowStretch(2, 1);
        gridLayout_4->setColumnStretch(0, 1);
        gridLayout_4->setColumnStretch(1, 1);
        gridLayout_4->setColumnStretch(2, 1);

        L_CAM1_4->addLayout(gridLayout_4);

        L_CAM1_4->setStretch(0, 2);
        L_CAM1_4->setStretch(1, 9);

        verticalLayout_9->addLayout(L_CAM1_4);


        L_map_key->addWidget(W_CAM1_background_4);

        W_CAM1_background_2 = new QWidget(MainWidget);
        W_CAM1_background_2->setObjectName("W_CAM1_background_2");
        sizePolicy1.setHeightForWidth(W_CAM1_background_2->sizePolicy().hasHeightForWidth());
        W_CAM1_background_2->setSizePolicy(sizePolicy1);
        W_CAM1_background_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        verticalLayout_6 = new QVBoxLayout(W_CAM1_background_2);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        L_CAM2_3 = new QVBoxLayout();
        L_CAM2_3->setObjectName("L_CAM2_3");
        L_CAM2_3->setContentsMargins(5, 5, 5, 5);
        QL_depth_header_4 = new QLabel(W_CAM1_background_2);
        QL_depth_header_4->setObjectName("QL_depth_header_4");
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette8.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette8.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette8.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette8.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette8.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette8.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette8.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette8.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette8.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        QL_depth_header_4->setPalette(palette8);
        QL_depth_header_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 106, 0);\n"
"font: 600 13pt \"A2Z\";"));
        QL_depth_header_4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        L_CAM2_3->addWidget(QL_depth_header_4);

        QL_map = new QLabel(W_CAM1_background_2);
        QL_map->setObjectName("QL_map");
        QL_map->setAlignment(Qt::AlignmentFlag::AlignCenter);

        L_CAM2_3->addWidget(QL_map);

        L_CAM2_3->setStretch(0, 2);
        L_CAM2_3->setStretch(1, 9);

        verticalLayout_6->addLayout(L_CAM2_3);


        L_map_key->addWidget(W_CAM1_background_2);

        W_CAM2_background_2 = new QWidget(MainWidget);
        W_CAM2_background_2->setObjectName("W_CAM2_background_2");
        sizePolicy1.setHeightForWidth(W_CAM2_background_2->sizePolicy().hasHeightForWidth());
        W_CAM2_background_2->setSizePolicy(sizePolicy1);
        W_CAM2_background_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        verticalLayout_8 = new QVBoxLayout(W_CAM2_background_2);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_8->setContentsMargins(5, 5, 5, 5);
        QL_lift_header_7 = new QLabel(W_CAM2_background_2);
        QL_lift_header_7->setObjectName("QL_lift_header_7");
        QPalette palette9;
        palette9.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette9.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette9.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette9.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette9.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette9.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette9.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette9.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette9.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette9.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        QL_lift_header_7->setPalette(palette9);
        QL_lift_header_7->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 106, 0);\n"
"font: 600 13pt \"A2Z\";"));
        QL_lift_header_7->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_8->addWidget(QL_lift_header_7);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        L_lift_grid = new QGridLayout();
        L_lift_grid->setObjectName("L_lift_grid");
        L_lift_grid->setHorizontalSpacing(8);
        L_lift_grid->setVerticalSpacing(6);
        L_lift_grid->setContentsMargins(0, -1, 0, -1);
        PB_lift_down = new QPushButton(W_CAM2_background_2);
        PB_lift_down->setObjectName("PB_lift_down");
        sizePolicy1.setHeightForWidth(PB_lift_down->sizePolicy().hasHeightForWidth());
        PB_lift_down->setSizePolicy(sizePolicy1);
        QPalette palette10;
        palette10.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette10.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette10.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette10.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette10.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette10.setBrush(QPalette::Active, QPalette::Window, brush3);
        palette10.setBrush(QPalette::Active, QPalette::Highlight, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette10.setBrush(QPalette::Active, QPalette::PlaceholderText, brush5);
#endif
        palette10.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette10.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette10.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette10.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette10.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette10.setBrush(QPalette::Inactive, QPalette::Window, brush3);
        palette10.setBrush(QPalette::Inactive, QPalette::Highlight, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette10.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush5);
#endif
        palette10.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette10.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        palette10.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette10.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette10.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette10.setBrush(QPalette::Disabled, QPalette::Window, brush3);
        palette10.setBrush(QPalette::Disabled, QPalette::Highlight, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette10.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush5);
#endif
        PB_lift_down->setPalette(palette10);
        PB_lift_down->setFont(font4);
        PB_lift_down->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        PB_lift_down->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        PB_lift_down->setStyleSheet(QString::fromUtf8("background-color: rgb(59, 56, 56);\n"
"border-color: rgba(191, 64, 64, 0);\n"
"color: rgb(242, 244, 241);"));

        L_lift_grid->addWidget(PB_lift_down, 3, 0, 1, 1);

        PB_lift_stop = new QPushButton(W_CAM2_background_2);
        PB_lift_stop->setObjectName("PB_lift_stop");
        sizePolicy1.setHeightForWidth(PB_lift_stop->sizePolicy().hasHeightForWidth());
        PB_lift_stop->setSizePolicy(sizePolicy1);
        QPalette palette11;
        palette11.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette11.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette11.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette11.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette11.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette11.setBrush(QPalette::Active, QPalette::Window, brush3);
        palette11.setBrush(QPalette::Active, QPalette::Highlight, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette11.setBrush(QPalette::Active, QPalette::PlaceholderText, brush5);
#endif
        palette11.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette11.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette11.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette11.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette11.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette11.setBrush(QPalette::Inactive, QPalette::Window, brush3);
        palette11.setBrush(QPalette::Inactive, QPalette::Highlight, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette11.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush5);
#endif
        palette11.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette11.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        palette11.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette11.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette11.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette11.setBrush(QPalette::Disabled, QPalette::Window, brush3);
        palette11.setBrush(QPalette::Disabled, QPalette::Highlight, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette11.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush5);
#endif
        PB_lift_stop->setPalette(palette11);
        PB_lift_stop->setFont(font4);
        PB_lift_stop->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        PB_lift_stop->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        PB_lift_stop->setStyleSheet(QString::fromUtf8("background-color: rgb(59, 56, 56);\n"
"color: rgb(242, 244, 241);\n"
"border-color: rgba(191, 64, 64, 0);"));

        L_lift_grid->addWidget(PB_lift_stop, 2, 0, 1, 1);

        PB_lift_up = new QPushButton(W_CAM2_background_2);
        PB_lift_up->setObjectName("PB_lift_up");
        sizePolicy1.setHeightForWidth(PB_lift_up->sizePolicy().hasHeightForWidth());
        PB_lift_up->setSizePolicy(sizePolicy1);
        QPalette palette12;
        palette12.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette12.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette12.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette12.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette12.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette12.setBrush(QPalette::Active, QPalette::Window, brush3);
        palette12.setBrush(QPalette::Active, QPalette::Highlight, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette12.setBrush(QPalette::Active, QPalette::PlaceholderText, brush5);
#endif
        palette12.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette12.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette12.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette12.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette12.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette12.setBrush(QPalette::Inactive, QPalette::Window, brush3);
        palette12.setBrush(QPalette::Inactive, QPalette::Highlight, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette12.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush5);
#endif
        palette12.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette12.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        palette12.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette12.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette12.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette12.setBrush(QPalette::Disabled, QPalette::Window, brush3);
        palette12.setBrush(QPalette::Disabled, QPalette::Highlight, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette12.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush5);
#endif
        PB_lift_up->setPalette(palette12);
        PB_lift_up->setFont(font4);
        PB_lift_up->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        PB_lift_up->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        PB_lift_up->setStyleSheet(QString::fromUtf8("background-color: rgb(59, 56, 56);\n"
"color: rgb(242, 244, 241);\n"
"border-color: rgba(191, 64, 64, 0);"));

        L_lift_grid->addWidget(PB_lift_up, 1, 0, 1, 1);

        L_lift_grid->setColumnStretch(0, 1);
        L_lift_grid->setRowMinimumHeight(0, 1);

        horizontalLayout_2->addLayout(L_lift_grid);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName("verticalLayout_2");
        L_lift_state_6 = new QLabel(W_CAM2_background_2);
        L_lift_state_6->setObjectName("L_lift_state_6");
        sizePolicy1.setHeightForWidth(L_lift_state_6->sizePolicy().hasHeightForWidth());
        L_lift_state_6->setSizePolicy(sizePolicy1);
        L_lift_state_6->setStyleSheet(QString::fromUtf8("border: 1px solid grey;\n"
"border-radius: 5px;\n"
"text-align: center;\n"
"background-color: rgb(242, 244, 241);"));
        L_lift_state_6->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(L_lift_state_6);

        L_lift_state_5 = new QLabel(W_CAM2_background_2);
        L_lift_state_5->setObjectName("L_lift_state_5");
        sizePolicy1.setHeightForWidth(L_lift_state_5->sizePolicy().hasHeightForWidth());
        L_lift_state_5->setSizePolicy(sizePolicy1);
        L_lift_state_5->setStyleSheet(QString::fromUtf8("border: 1px solid grey;\n"
"border-radius: 5px;\n"
"text-align: center;\n"
"background-color: rgb(242, 244, 241);"));
        L_lift_state_5->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(L_lift_state_5);

        L_lift_state_4 = new QLabel(W_CAM2_background_2);
        L_lift_state_4->setObjectName("L_lift_state_4");
        sizePolicy1.setHeightForWidth(L_lift_state_4->sizePolicy().hasHeightForWidth());
        L_lift_state_4->setSizePolicy(sizePolicy1);
        L_lift_state_4->setStyleSheet(QString::fromUtf8("border: 1px solid grey;\n"
"border-radius: 5px;\n"
"text-align: center;\n"
"background-color: rgb(242, 244, 241);"));
        L_lift_state_4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(L_lift_state_4);

        L_lift_state_3 = new QLabel(W_CAM2_background_2);
        L_lift_state_3->setObjectName("L_lift_state_3");
        sizePolicy1.setHeightForWidth(L_lift_state_3->sizePolicy().hasHeightForWidth());
        L_lift_state_3->setSizePolicy(sizePolicy1);
        L_lift_state_3->setStyleSheet(QString::fromUtf8("border: 1px solid grey;\n"
"border-radius: 5px;\n"
"text-align: center;\n"
"background-color: rgb(242, 244, 241);"));
        L_lift_state_3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(L_lift_state_3);

        L_lift_state_2 = new QLabel(W_CAM2_background_2);
        L_lift_state_2->setObjectName("L_lift_state_2");
        sizePolicy1.setHeightForWidth(L_lift_state_2->sizePolicy().hasHeightForWidth());
        L_lift_state_2->setSizePolicy(sizePolicy1);
        L_lift_state_2->setStyleSheet(QString::fromUtf8("border: 1px solid grey;\n"
"border-radius: 5px;\n"
"text-align: center;\n"
"background-color: rgb(242, 244, 241);"));
        L_lift_state_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(L_lift_state_2);

        L_lift_state_1 = new QLabel(W_CAM2_background_2);
        L_lift_state_1->setObjectName("L_lift_state_1");
        sizePolicy1.setHeightForWidth(L_lift_state_1->sizePolicy().hasHeightForWidth());
        L_lift_state_1->setSizePolicy(sizePolicy1);
        L_lift_state_1->setStyleSheet(QString::fromUtf8("border: 1px solid grey;\n"
"border-radius: 5px;\n"
"text-align: center;\n"
"background-color: rgb(242, 244, 241);"));
        L_lift_state_1->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(L_lift_state_1);

        L_lift_state_0 = new QLabel(W_CAM2_background_2);
        L_lift_state_0->setObjectName("L_lift_state_0");
        sizePolicy1.setHeightForWidth(L_lift_state_0->sizePolicy().hasHeightForWidth());
        L_lift_state_0->setSizePolicy(sizePolicy1);
        L_lift_state_0->setStyleSheet(QString::fromUtf8("border: 1px solid grey;\n"
"border-radius: 5px;\n"
"text-align: center;\n"
"background-color: rgb(242, 244, 241);"));
        L_lift_state_0->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(L_lift_state_0);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout_8->addLayout(horizontalLayout_2);

        verticalLayout_8->setStretch(0, 2);
        verticalLayout_8->setStretch(1, 9);

        L_map_key->addWidget(W_CAM2_background_2);

        L_map_key->setStretch(0, 2);
        L_map_key->setStretch(1, 7);
        L_map_key->setStretch(2, 2);

        verticalLayout->addLayout(L_map_key);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(MainWidget);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("border: 1px solid grey;\n"
"border-radius: 5px;\n"
"text-align: center;\n"
"background-color: rgb(242, 244, 241);\n"
"font: 500 9pt \"A2Z\";"));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(label);

        PBAR_battery = new QProgressBar(MainWidget);
        PBAR_battery->setObjectName("PBAR_battery");
        sizePolicy1.setHeightForWidth(PBAR_battery->sizePolicy().hasHeightForWidth());
        PBAR_battery->setSizePolicy(sizePolicy1);
        PBAR_battery->setStyleSheet(QString::fromUtf8("QProgressBar {\n"
"    border: 1px solid grey;\n"
"    border-radius: 5px;\n"
"    text-align: center;\n"
"    background-color: #FFFFFF;\n"
"	font: 500 9pt \"A2Z\";\n"
"}\n"
"\n"
"QProgressBar::chunk {\n"
"    border-radius: 5px;\n"
"    background-color: #04ED85\n"
"	font: 500 9pt \"A2Z\";\n"
"}"));
        PBAR_battery->setValue(24);
        PBAR_battery->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(PBAR_battery);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label_2 = new QLabel(MainWidget);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("font: 500 11pt \"A2Z\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(label_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        label_3 = new QLabel(MainWidget);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("font: 500 11pt \"A2Z\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(label_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 4);
        horizontalLayout->setStretch(2, 1);
        horizontalLayout->setStretch(3, 4);
        horizontalLayout->setStretch(5, 4);
        horizontalLayout->setStretch(6, 12);

        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 11);
        verticalLayout->setStretch(2, 11);
        verticalLayout->setStretch(3, 1);

        verticalLayout_3->addLayout(verticalLayout);


        retranslateUi(MainWidget);

        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QCoreApplication::translate("MainWidget", "MainWidget", nullptr));
        QL_top_icon->setText(QString());
        QL_top_title->setText(QCoreApplication::translate("MainWidget", "\352\265\254\354\241\260 \355\203\220\354\202\254 \353\241\234\353\264\207", nullptr));
        QL_depth_header->setText(QCoreApplication::translate("MainWidget", "CAM 1", nullptr));
        QL_depth_camera->setText(QCoreApplication::translate("MainWidget", "depth", nullptr));
        QL_omx_header->setText(QCoreApplication::translate("MainWidget", "CAM 2", nullptr));
        QL_omx_camera->setText(QCoreApplication::translate("MainWidget", "omx", nullptr));
        QL_depth_header_8->setText(QCoreApplication::translate("MainWidget", "ARROW KEY", nullptr));
        PB_arrow_up->setText(QCoreApplication::translate("MainWidget", "\342\226\262", nullptr));
        PB_arrow_left->setText(QCoreApplication::translate("MainWidget", "\342\227\200", nullptr));
        PB_arrow_right->setText(QCoreApplication::translate("MainWidget", "\342\226\266", nullptr));
        PB_arrow_stop->setText(QCoreApplication::translate("MainWidget", "\342\226\240", nullptr));
        PB_arrow_down->setText(QCoreApplication::translate("MainWidget", "\342\226\274", nullptr));
        QL_depth_header_4->setText(QCoreApplication::translate("MainWidget", "MAP", nullptr));
        QL_map->setText(QCoreApplication::translate("MainWidget", "map", nullptr));
        QL_lift_header_7->setText(QCoreApplication::translate("MainWidget", "LIFT KEY", nullptr));
        PB_lift_down->setText(QCoreApplication::translate("MainWidget", "\342\226\274", nullptr));
        PB_lift_stop->setText(QCoreApplication::translate("MainWidget", "\342\226\240", nullptr));
        PB_lift_up->setText(QCoreApplication::translate("MainWidget", "\342\226\262", nullptr));
        L_lift_state_6->setText(QCoreApplication::translate("MainWidget", "5", nullptr));
        L_lift_state_5->setText(QCoreApplication::translate("MainWidget", "4", nullptr));
        L_lift_state_4->setText(QCoreApplication::translate("MainWidget", "3", nullptr));
        L_lift_state_3->setText(QCoreApplication::translate("MainWidget", "2", nullptr));
        L_lift_state_2->setText(QCoreApplication::translate("MainWidget", "1", nullptr));
        L_lift_state_1->setText(QCoreApplication::translate("MainWidget", "0", nullptr));
        L_lift_state_0->setText(QCoreApplication::translate("MainWidget", "-1", nullptr));
        label->setText(QCoreApplication::translate("MainWidget", "OFF", nullptr));
        label_2->setText(QCoreApplication::translate("MainWidget", "speed", nullptr));
        label_3->setText(QCoreApplication::translate("MainWidget", "speed", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
