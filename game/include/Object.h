#pragma once
#include <SDL.h>
#include <SDL_image.h>

// 游戏中所有实体对象

// 游戏玩家（战机）
struct Player
{
    SDL_Texture* texture = nullptr;     // 玩家纹理
    SDL_FPoint position = {0.0f, 0.0f}; // 玩家位置
    int width = 0;                      // 玩家飞机图片宽度
    int height = 0;                     // 玩家飞机图片高度
};


