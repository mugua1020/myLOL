#include "aicontroller.h"

/*  AIController是AI的控制类，有一个GameAI成员变量
 *  主要控制方法为通过循环，使得AI运行是依次而非同时的
 */

AIController::AIController(Character* t_character[], const  int t_characterNum, QWidget* parent) :
    QTimer(parent), m_characterNum(t_characterNum), m_count(-1)
{
    m_character = t_character;
    m_gameAI = new GameAI;
}
// 开始AI回合前，需要调用以初始化参数
void AIController::reset(int t_aicount)
{
    m_count = -1;
    m_aicount = t_aicount;
    m_usedAI = 0;
}
// 进入AI循环
void AIController::start()
{
    emit AIRoundBegin();
    connect(m_gameAI, &GameAI::thisCharacterFinished, this, &AIController::loop, Qt::UniqueConnection);
    loop();
}
// 等待到GameAI操纵角色行动完成后，使下一个角色行动
void AIController::loop()
{
    m_count++;
    if (m_aicount == m_usedAI)
    {
        // 如果所有AI都用完，则发射AI回合结束信号
        emit AIRoundFinished();
        return;
    }
    for (; m_count < m_characterNum; m_count++)// 遍历所有角色
    {
        // 如果此角色属于AI方且没死，则用GameAI移动
        if (m_character[m_count]->m_belong == YOURS && m_character[m_count]->m_characterState != Character::DEAD)
        {
            m_usedAI++;
            m_gameAI->moveCharacter(m_count, m_character, m_characterNum);
            return;
        }
    }
}
