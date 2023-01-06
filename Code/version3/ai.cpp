#include "ai.h"

/* GameAI是模拟AI运行的类，通过调用Algorithm寻路，并调用Animation绘制动画 */

GameAI::GameAI()
{
}
// 移动某角色，传入所有角色和行动的角色
void GameAI::moveCharacter(const int id, Character* t_character[], const int characterNum)
{
    // 初始化
    m_character = t_character;
    m_nowCharacter = m_character[id];
    m_Al.init(m_nowCharacter->m_move, m_nowCharacter);

    int tempx = m_nowCharacter->m_cellx;
    int tempy = m_nowCharacter->m_celly;

    // 算法寻找移动可行域
    m_Al.findAvailableCell(tempx, tempy, 0, m_character, characterNum);

    // 寻找距离其他角色的最近距离的初始化
    m_minDist = 0x3f3f3f3f;
    node minNode{ -1,-1 };
    m_attrackid = -1;

    // 寻找距离对手的最近距离
    for (ull i = 0; i < m_Al.m_availableCell.size(); i++)
    {
        for (int j = 0; j < characterNum; j++)
            if (m_character[j]->m_belong == MINE && m_character[j]->m_characterState != Character::DEAD)
            {
                //if(character[1]->characterState==Character::DEAD)qDebug()<<"DEAD";else qDebug()<<"EXISTING";
                int tempDist = ManhattanDist(m_Al.m_availableCell[i], std::make_pair(m_character[j]->m_cellx, m_character[j]->m_celly));
                if (m_minDist > tempDist)
                {
                    minNode = m_Al.m_availableCell[i];
                    m_minDist = tempDist;
                    m_attrackid = j;
                }
            }
    }
    // 寻找如何到达上述最近距离
    m_Al.findPath(m_nowCharacter->m_cellx, m_nowCharacter->m_celly, minNode.first, minNode.second, 0, m_Al.m_resultMap[minNode.first][minNode.second]);

    connect(m_nowCharacter->m_mover, &MoveAnimation::animationFinished, this, &GameAI::attrackCharacter, Qt::UniqueConnection);

    m_nowCharacter->movePos(m_Al.m_resultMap[minNode.first][minNode.second], m_Al.m_path);
}
// 进行攻击操作
void GameAI::attrackCharacter()const
{
    // 如果在最近距离可攻击到敌人，则攻击
    if (m_minDist <= m_nowCharacter->m_attrackable)
    {
        m_nowCharacter->m_attracker->startMove(m_nowCharacter, m_nowCharacter->m_cellx, m_nowCharacter->m_celly,
            m_character[m_attrackid]->m_cellx, m_character[m_attrackid]->m_celly);
        connect(m_nowCharacter->m_attracker, &AttrackAnimation::animationFinished, this, &GameAI::waitFunc, Qt::UniqueConnection);
    }
    // 否则结束
    else
    {
        emit thisCharacterFinished();
    }
}
// 等待攻击结束后发送ai执行完毕指令
void GameAI::waitFunc()const
{
    emit m_character[m_attrackid]->beAttracked(m_nowCharacter->m_attrack);
    QTimer::singleShot(10, [=]() {emit thisCharacterFinished(); });
}
