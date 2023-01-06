#ifndef ALGORITHM_H
#define ALGORITHM_H
#include "character.h"
#include "gamemap.h"

class FindPathAlgorithm
{
public:
    int m_resultMap[MAP_COL+1][MAP_ROW+1]; // dfs后移动/攻击的可行域，其中-1代表不可行，
                            //正数代表可行域距离当前位置的曼哈顿距离，此距离为所有路径的最小值
    FindPathAlgorithm(); // 0为不可行，1为可行
    int m_totalMove; // 可行域圈定的最大距离
    bool m_foundPathOrNot; // 是否找到可行的路
    Character * m_nowCharacter; // 场上角色数
    std::vector<node> m_availableCell; // 储存所有可行格子，以(x,y)形式存储
    std::vector<int> m_path;// 走到 某一可行格子的路径，由"config.h"中枚举变量"DIRACTION"规定
public:
    // dfs寻找可行域
    void findAvailableCell(int x,int y,int depth, Character*[], int characterNum);
    // 找当前点到达可行域点的路径，以DIRECTION的enum值存入vector
    void findPath(const int x, const int y, const int endx, const int endy, const int tempsteps, const int totalsteps);
    // 数据初始化
    void init();
    void init(const int, Character *t_nowCharacter);
};

#endif // ALGORITHM_H
