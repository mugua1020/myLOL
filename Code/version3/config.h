#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>
#include <QMouseEvent>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QTimer>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QTextCodec>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRgb>
#include <QThread>
#include <QSound>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QMovie>

// 主窗口参数
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 960
#define WINDOW_BOUNDARY 64
#define CELL_SIZE 64
#define MAP_HEIGHT m_map.m_height
#define MAP_WIDTH m_map.m_width

// QTimer参数
#define MOUSE_MOVE_TIMER_INTERVAL 150
#define ANIMATION_DURATION 200
#define ZOOM_DURATION 300
#define CAPTURE_SCREEN_INTERVAL 3000

// 游戏参数
#define HP_HEIGHT 6
#define HP_DISTANCE 10
#define RELIVE 16



// 图片路径
#define MAP_PATH  "://pic/map.png"
#define EGG_PATH "://pic/egg.png"
#define WARRIOR_PATH ":/pic/warrior.jpg"
#define ASSASSIN_PATH ":/pic/assassin.jpg"
#define SHOOTER_PATH ":/pic/shooter.jpg"
#define MASTER_PATH ":/pic/master.jpg"
#define TANK_PATH ":/pic/tank.jpg"
#define GUIDE1_PATH ":/pic/guide1.png"
#define GUIDE2_PATH ":/pic/guide2.png"
#define GUIDE3_PATH ":/pic/guide3.png"
#define GUIDE4_PATH ":/pic/guide4.png"
#define GUIDE5_PATH ":/pic/guide5.png"
#define GUIDE6_PATH ":/pic/guide6.png"

#define MAIN_SCENE_BACKGROUND_PATH ":/pic/background.png"
#define MAIN_SCENE_GUIDE_BUTTON_PATH ":/pic/guide_button.png"
#define MAIN_SCENE_ONE_PLAYER_BUTTON_PATH ":/pic/one_player_button.png"
#define MAIN_SCENE_TWO_PLAYERS_BUTTON_PATH ":/pic/two_players_button.png"

// 音乐路径
#define BGM_PATH ":/music/bgm.wav"
#define ATTRACK_MUSIC_PATH ":/music/attrack.wav"
#define CLICK_MUSIC_PATH ":/music/click.wav"


//设置地图参数
#define MAP_ROW 15
#define MAP_COL 25
const int MAP[MAP_ROW+1][MAP_COL+1] = {
    {0, 0, 0, 0, 0, 0,     0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0,     0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1,     1, 1, 2, 1, 1,  1, 2, 2, 2, 1,  1, 1, 1, 1, 1,  1, 1, 1, 1, 0},
    {0, 0, 1, 2, 1, 1,     1, 1, 2, 1, 1,  1, 2, 0, 2, 1,  1, 1, 1, 1, 1,  0, 0, 2, 0, 0},
    {0, 0, 1, 1, 1, 1,     1, 2, 2, 2, 1,  1, 2, 2, 2, 1,  1, 0, 1, 1, 1,  1, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 1,     1, 1, 2, 1, 1,  1, 1, 1, 1, 1,  0, 1, 1, 1, 1,  1, 1, 1, 1, 0},
    
    {0, 0, 1, 1, 1, 1,     1, 1, 1, 1, 1,  1, 1, 1, 1, 1,  1, 1, 1, 1, 1,  1, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 1,     1, 2, 2, 2, 1,  1, 3, 1, 0, 1,  1, 3, 3, 3, 1,  1, 1, 1, 1, 0},
    {0, 0, 2, 2, 2, 2,     1, 2, 3, 2, 1,  1, 1, 0, 1, 1,  1, 3, 2, 3, 1,  3, 3, 3, 3, 0},
    {0, 0, 1, 1, 1, 1,     1, 2, 2, 2, 1,  1, 0, 1, 2, 1,  1, 3, 3, 3, 1,  1, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 1,     1, 1, 1, 1, 1,  1, 1, 1, 1, 1,  1, 1, 1, 1, 1,  1, 1, 1, 1, 0},
    
    {0, 0, 1, 1, 1, 1,     1, 1, 1, 1, 0,  1, 1, 1, 1, 1,  1, 1, 3, 1, 1,  1, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 1,     1, 1, 1, 0, 1,  1, 3, 3, 3, 1,  1, 3, 3, 3, 1,  1, 1, 1, 1, 0},
    {0, 0, 0, 3, 0, 0,     1, 1, 1, 1, 1,  1, 3, 0, 3, 1,  1, 1, 3, 1, 1,  1, 1, 3, 1, 0},
    {0, 0, 1, 1, 1, 1,     1, 1, 1, 1, 1,  1, 3, 3, 3, 1,  1, 1, 3, 1, 1,  1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0,     0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0}
};




// 最大最小值函数
inline int min(int x,int y){return x < y ? x : y;}
inline int max(int x,int y){return x > y ? x : y;}

// 常见变量名的别名
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef std::pair<int,int> node;

// 定义曼哈顿距离
inline int ManhattanDist(node x, node y)
{
    return abs(x.first - y.first) + abs(x.second - y.second);
}
inline int ManhattanDist(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

// 一些枚举变量
enum BELONGING{MINE, YOURS};
enum DERECTION{UP, DOWN, LEFT, RIGHT};
enum GAMEMODE{ONEPLAYER = 1, TWOPLAYERS = 0};


#endif // CONFIG_H
