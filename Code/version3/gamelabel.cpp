#include "gamelabel.h"
#include "config.h"
#include <QFontMetrics>

/*  此文件包含与游戏相关的两个派生自QLabel的类：HintLabel和ClickLabel
 *  HintLabel可以在游戏界面弹出提示框
 *  ClickLabel具有enter时透明、点击发送信号等功能
 */

// 提示框构造函数
HintLabel::HintLabel(QWidget* parent, int x, int y) :
    QLabel(parent)
{
    setPixmap(QPixmap(":/pic/hint.png"));
    setGeometry(x, y, width(), height());
}
HintLabel::HintLabel(QString t_str, QWidget* parent, int x, int y) :
    QLabel(parent), m_str(t_str)
{
    setGeometry(x, y, width(), height());
    setPixmap(QPixmap(":/pic/hint.png"));
    setAttribute(Qt::WA_DeleteOnClose);
    setFixedSize(550, 150);
    update();
    show();
    raise();
}
// 为提示框设置文字
void HintLabel::setText(QString t_str)
{
    m_str = t_str;
    setFixedSize(550, 150);
}
// 打印提示框
void HintLabel::paintEvent(QPaintEvent* ev)
{
    QLabel::paintEvent(ev);
    QPainter painter(this);
    QFont font("华文新魏", 30, 50, false);
    QFontMetrics fontMetrics(font);
    painter.setFont(font);
    painter.setPen(QPen(QColor(120, 120, 120)));
    QString title(m_str);
    int widthOfTitle = fontMetrics.horizontalAdvance(title);//字符串显示的像素大小，居中
    painter.drawText(this->width() / 2 - widthOfTitle / 2, 90, title);
}
// 点击按键，两种模式，一种enter时变透明，一种不变
ClickLabel::ClickLabel(const int w, const int h, const QPixmap map, QWidget* parent, const int t_style) : QLabel(parent)
{
    setFixedSize(w, h);
    m_pic = map;
    m_enterOrNot = false;
    m_style = t_style;
}
// 点击时发送被点击信号
void ClickLabel::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
    QLabel::mousePressEvent(event);
}
// 进入时重绘
void ClickLabel::enterEvent(QEvent*)
{
    m_enterOrNot = true;
    repaint();
}
// 离开时重绘
void ClickLabel::leaveEvent(QEvent*)
{
    m_enterOrNot = false;
    repaint();
}
void ClickLabel::paintEvent(QPaintEvent* eve)
{
    QLabel::paintEvent(eve);
    QPainter painter(this);
    // 如果是透明style，则更新透明度
    if (m_style == TRANSPARENTSTYLE)
    {
        if (m_enterOrNot)
            painter.setOpacity(0.6);
    }
    painter.drawPixmap(0, 0, m_pic);
}
// 重设图片
void ClickLabel::setPixmap(const QPixmap t_pic)
{
    m_pic = t_pic;
}

