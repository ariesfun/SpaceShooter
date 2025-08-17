#pragma once

#include "Scene.h"

// 游戏主类，负责管理游戏循环和场景
class Game {
public:
   Game();
   ~Game();

public:
   void Init();                              // 游戏类初始化
   void Run();                               // 游戏运行：包括事件处理、更新和渲染三个步骤
   void Clean();                             // 清理资源
   void ChangeScene(Scene* scene);           // 切换场景

private:
   void HandleEvents(SDL_Event* event);      // 游戏主循环的三个阶段：事件处理、更新、渲染场景
   void Update();
   void Render();

private:
   bool           m_IsRunning = true;        // 当前游戏运行状态
   Scene*         m_CurrentScene = nullptr;  // 当前场景
   SDL_Window*    m_Window = nullptr;        // SDL窗口
   SDL_Renderer*  m_Renderer = nullptr;      // SDL渲染器
   int            m_WindowWidth = 600;       // 窗口宽度, 像素值
   int            m_WindowHeight = 800;      // 窗口高度

};