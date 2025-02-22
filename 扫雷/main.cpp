// main.cpp
#include "FloatEngine.h"
#include "MineSweeper.h"
class Room_GamePlay :public Room{
public:
    Room_GamePlay() {
        CreateFromTemplate<MineSweeper>();
    }
};
int main() {
    Game game;
    game.CreateWindow(640, 480, "MineSweeper");
    WinFuns::ShowWindow(GetWindowHandle(), 1);
    if (game.CanStart()) {
        // 创建房间并进入游戏循环
        auto room = new Room_GamePlay;
        Room_Goto(room);
        // 设置游戏帧率并开始游戏循环
        game.Play(60);

        // 游戏结束后销毁房间
        delete room;
    }

    // 销毁游戏窗口
    game.Destroy();
    return 0;
}