#include "guidescene.h"
#include "config.h"

/*  GuideScene是关于教程页面 的类*/

GuideScene::GuideScene(QWidget* parent) :
    QDialog(parent)
{
    // 初始化
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    m_page = 0;
    m_pic[0] = QPixmap(GUIDE1_PATH);
    m_pic[1] = QPixmap(GUIDE2_PATH);
    m_pic[2] = QPixmap(GUIDE3_PATH);
    m_pic[3] = QPixmap(GUIDE4_PATH);
    m_pic[4] = QPixmap(GUIDE5_PATH);
    m_pic[5] = QPixmap(GUIDE6_PATH);

}
void GuideScene::mousePressEvent(QMouseEvent*)
{
    // 点击翻页
    m_page++;
    repaint();
}
void GuideScene::paintEvent(QPaintEvent*)
{
    // 如果到达尾页则退回游戏首页，否则显示
    QPainter painter(this);
    if (m_page == 6) {
        m_page = 0;
        parentWidget()->show();
        this->hide();
        return;
    }
    painter.drawPixmap(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, m_pic[m_page]);

}
