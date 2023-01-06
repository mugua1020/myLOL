#include "gamemap.h"

/*  GameMap储存游戏地图每个格点、长宽等数据，在确定关卡id后进行导入方可使用 */

int GameMap::binMap[MAP_COL+1][MAP_ROW+1] = {};

GameMap::GameMap()
{
    m_pic.load(MAP_PATH);
    m_height = CELL_SIZE*MAP_ROW;
    m_width = CELL_SIZE*MAP_COL;
    m_maxCellx = MAP_COL;
    m_maxCelly = MAP_ROW;
    for(int i=0; i<MAP_ROW; i++){
        for(int j=0; j<MAP_COL; j++){
            binMap[j][i] = MAP[i][j];
        }
    }

}



// GameMap::GameMap(int id)
// {
//     // 载入图片
//     if (id == 1)
//         m_pic.load(MAP1_PATH); //
//     else
//         m_pic.load(MAP2_PATH);

//     // 设置数据
//     m_height = CELL_SIZE * originx[id - 1];
//     m_width = CELL_SIZE * originy[id - 1];
//     m_maxCellx = originy[id - 1];
//     m_maxCelly = originx[id - 1];

//     // 向binMap导入地图
//     for (int i = 0; i <= originx[id - 1]; i++)
//     {
//         for (int j = 0; j <= originy[id - 1]; j++)
//         {
//             binMap[j][i] = originMap[id - 1][i][j];
//         }
//     }
// }
