#include <iostream>
#include "Game.h"

int main(int, char**) // 注意：这里是SDL2要求的入口函数形式
{
    // 创建Game实例，并运行游戏
    Game game;
    game.Init();
    game.Run();
    
    std::cout << "Hello, SDL2!" << std::endl;

    return 0;
}