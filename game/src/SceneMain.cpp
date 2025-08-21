#include "SceneMain.h"
#include "Game.h"
#include <SDL_keyboard.h>
#include <iostream>

SceneMain::SceneMain()
{

}

SceneMain::~SceneMain()
{

}

void SceneMain::Init()
{
    // 从本地文件加载图片
    m_player.texture = IMG_LoadTexture(TheGame.GetRenderer(), "assets/image/SpaceShip.png");
    // 将纹理染为自定义色（红色分量最大，绿/蓝为0）
    SDL_SetTextureColorMod(m_player.texture, 0, 230, 158);
    if (!m_player.texture) // 检查纹理加载是否成功
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_LoadTexture Error: %s", SDL_GetError());
        return;
    }

    // 获取纹理的宽高
    SDL_QueryTexture(m_player.texture, nullptr, nullptr, &m_player.width, &m_player.height);
    int scale = 4; // 缩放因子，玩家飞机缩小倍数
    m_player.width /= scale;
    m_player.height /= scale;

    // 初始化玩家飞机位置
    int windowWidth, windowHeight;
    SDL_GetWindowSize(TheGame.GetWindow(), &windowWidth, &windowHeight);
    m_player.position.x = windowWidth / 2.0f - m_player.width / 2.0f; // 居中位置
    m_player.position.y = windowHeight * 1.0f - m_player.height;
}

void SceneMain::Update()
{
    KeyboardControlPlayer();
}

void SceneMain::Render()
{
    // 绘制玩家飞机图片
    SDL_Rect aPlayerImgRect = {static_cast<int>(m_player.position.x), static_cast<int>(m_player.position.y), m_player.width, m_player.height};
    SDL_RenderCopy(TheGame.GetRenderer(), m_player.texture, nullptr, &aPlayerImgRect);
}

void SceneMain::Clean()
{
    // SDL图片资源清理
    if(m_player.texture)
    {
        SDL_DestroyTexture(m_player.texture);
        m_player.texture = nullptr;
    }
}

void SceneMain::HandleEvent(SDL_Event *event)
{
    // 处理主场景中的输入事件
    if (event->type == SDL_KEYDOWN)
    {
    }
}

void SceneMain::KeyboardControlPlayer()
{
    // 玩家通过键盘来控制飞机的上下左右移动
    const Uint8* keystate = SDL_GetKeyboardState(nullptr);
    if (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_W])
    {
        m_player.position.y -= 1.0f;
    }
    if (keystate[SDL_SCANCODE_DOWN] || keystate[SDL_SCANCODE_S])
    {
        m_player.position.y += 1.0f;
    }
    if (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_A])
    {
        m_player.position.x -= 1.0f;
    }
    if (keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D])
    {
        m_player.position.x += 1.0f;
    }


    // 飞机碰撞检测：限制飞机的移动范围
    int windowWidth, windowHeight;
    SDL_GetWindowSize(TheGame.GetWindow(), &windowWidth, &windowHeight);
    if (m_player.position.x < 0) // 左边界
    {
        m_player.position.x = 0;
    }
    if (m_player.position.x > windowWidth*1.0f - m_player.width) // 右边界
    {
        m_player.position.x = windowWidth*1.0f - m_player.width;
    }
    if (m_player.position.y < 0) // 上边界
    {
        m_player.position.y = 0;
    }
    if (m_player.position.y > windowHeight*1.0f - m_player.height) // 下边界
    {
        m_player.position.y = windowHeight*1.0f - m_player.height;
    }

}
