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
        // �������䲢������Ϸѭ��
        auto room = new Room_GamePlay;
        Room_Goto(room);
        // ������Ϸ֡�ʲ���ʼ��Ϸѭ��
        game.Play(60);

        // ��Ϸ���������ٷ���
        delete room;
    }

    // ������Ϸ����
    game.Destroy();
    return 0;
}