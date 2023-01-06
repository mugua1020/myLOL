#ifndef AICONTROLLER_H
#define AICONTROLLER_H

#include <QObject>
#include "config.h"
#include "character.h"
#include "ai.h"


// 此类控制AI方的所有角色
// 待一个角色通过GameAI类完成行动后，再使下一个角色行动，直至AI回合完成
class AIController : public QTimer
{
    Q_OBJECT
protected:
    Character ** m_character; // 场上的角色的头指针
    int m_characterNum; // 场上角色数
    int m_count; // 遍历0~characterNum-1的循环变量
    int m_aicount, m_usedAI; // AI方有多少角色及已使用角色数
    GameAI *m_gameAI; // GameAI对象
public:
    AIController(Character *t_character[], const int t_characterNum, QWidget* parent = nullptr);
    // 开始AI回合前，需要调用以初始化参数
    void reset(int aicount);
    // 进入AI循环
    void start();
protected:
    // 等待到GameAI操纵角色行动完成后，使下一个角色行动
    void loop();
signals:
    void AIRoundFinished() const ; // AI回合开始信号
    void AIRoundBegin() const ; // AI回合结束信号
};

#endif // AICONTROLLER_H
