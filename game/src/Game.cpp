#include "Game.h"
#include "SceneMain.h"

#include <SDL_image.h>

Game::Game()
{
    // 初始化游戏
}

Game::~Game()
{
    // 清理资源
    Clean();
}

Game &Game::GetInstance()
{
    static Game instance;
    return instance;
}

    
void Game::Init()
{
    // SDL初始化
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        // 处理初始化错误
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init Error: %s", SDL_GetError());
        m_IsRunning = false;
    }

    // 创建窗口
    m_Window = SDL_CreateWindow("太空战机", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_WindowWidth, m_WindowHeight, SDL_WINDOW_SHOWN);
    if(m_Window == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindow Error: %s", SDL_GetError());
        m_IsRunning = false;
    }

    // 创建渲染器
    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
    if(m_Renderer == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateRenderer Error: %s", SDL_GetError());
        m_IsRunning = false;
    }
    // SDL_image：图片处理初始化, 让其对PNG和JPG格式的图片进行支持
    if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_Init Error: %s", SDL_GetError());
        m_IsRunning = false;
    }

    // 创建主场景及初始化
    m_CurrentScene = new SceneMain();
    m_CurrentScene->Init();
}

void Game::Run()         // 游戏主循环
{   
    while(m_IsRunning)
    {
        SDL_Event event;
        HandleEvents(&event); // 事件循环
        Update();             // 更新场景
        Render();             // 渲染场景
    }
}

void Game::Clean()
{
    // 清理图片资源
    IMG_Quit();
    
    // 已有当前场景，先清理并删除它
    if(m_CurrentScene != nullptr) 
    {
        m_CurrentScene->Clean();
        delete m_CurrentScene;
    }  
    // 清理SDL资源
    if(m_Renderer != nullptr)
    {
        SDL_DestroyRenderer(m_Renderer);
        m_Renderer = nullptr;
    }
    if(m_Window != nullptr)
    {
        SDL_DestroyWindow(m_Window);
        m_Window = nullptr;
    }
    SDL_Quit();
}

void Game::ChangeScene(Scene* scene)
{   
    if(m_CurrentScene != nullptr) // 已有当前场景，先清理并删除它
    {
        m_CurrentScene->Clean();
        delete m_CurrentScene;
    }    
    m_CurrentScene = scene;       // 更新当前场景并初始化
    m_CurrentScene->Init();
}

SDL_Window* Game::GetWindow()
{
    return m_Window;
}

SDL_Renderer *Game::GetRenderer()
{
    return m_Renderer;
}

void Game::HandleEvents(SDL_Event* event)
{
    while(SDL_PollEvent(event))
    {
        if(event->type == SDL_QUIT) // 处理退出事件
        {
            m_IsRunning = false;
        }
        if(m_CurrentScene != nullptr) // 传递事件给当前场景处理
        {
            m_CurrentScene->HandleEvent(event);
        }
    }
} 

void Game::Update()
{
    // 更新当前场景
    m_CurrentScene->Update();
}

void Game::Render()
{
    // 清空渲染器, 用于清屏
    SDL_RenderClear(m_Renderer);
    // 渲染当前场景
    m_CurrentScene->Render();
    // 更新屏幕，将渲染器的内容显示更新到屏幕上
    SDL_RenderPresent(m_Renderer);
}
