#ifndef GUIDESCENE_H
#define GUIDESCENE_H

#include <QDialog>

class GuideScene : public QDialog
{
    Q_OBJECT
protected:
    int m_page; // 记录页数
    QPixmap m_pic[6]; // 记每页图片
public:
    explicit GuideScene(QWidget * parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent*)override;
    void paintEvent(QPaintEvent*)override;
};

#endif // GUIDESCENE_H
