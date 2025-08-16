#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

int main(int, char**) // 注意：这里是SDL2要求的入口函数形式
{
    std::cout << "Hello, SDL2!" << std::endl;

    // 测试验证SDL各个子模块库的功能
    // SDL2初始化:初始化所有SDL子系统
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // 创建窗口
    SDL_Window* window = SDL_CreateWindow(u8"测试窗口", 
                                          100, 
                                          100, 
                                          800, 600, 
                                          SDL_WINDOW_SHOWN); // SDL_WINDOW_SHOWN表示窗口创建后立即显示
    if (!window)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    // 创建渲染器
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // 默认使用硬件去渲染
    if (!renderer)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // SDL_image：图片处理
    // SDL_image初始化, 让其对PNG和JPG格式的图片进行支持
    if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG))
    {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        return 1;
    }
    // 从本地资源中加载一张图片
    SDL_Texture* texture = IMG_LoadTexture(renderer, "assets/image/other/yuan_shen.png");


    // SDL_mixer: 音乐处理
    // SDL_mixer初始化
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) // 从左到右参数：采样率、音频格式、声道数(2表示立体声)、缓冲区大小
    {
        std::cerr << "Mix_OpenAudio Error: " << Mix_GetError() << std::endl;
        return 1;
    }
    // 加载并播放音乐文件
    Mix_Music* music = Mix_LoadMUS("assets/music/03_Racing_Through_Asteroids_Loop.ogg");
    if (!music)
    {
        std::cerr << "Mix_LoadMUS Error: " << Mix_GetError() << std::endl;
        return 1;
    }
    Mix_PlayMusic(music, -1); // -1表示循环播放


    // SDL_ttf: 处理文本
    // SDL_TTF初始化
    if(TTF_Init() != 0)
    {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        return 1;
    }
    // 加载字体和渲染文本
    TTF_Font* font = TTF_OpenFont("assets/font/VonwaonBitmap-16px.ttf", 24);
    // 创建文本纹理
    SDL_Color color = {0, 0, 0, 255}; // 白色
    SDL_Surface* surface = TTF_RenderUTF8_Solid(font, "Hello, SDL! 中文我也可以！！！", color);
    if(!surface)
    {
        std::cerr << "TTF_RenderUTF8_Solid Error: " << TTF_GetError() << std::endl;
        return 1;
    }
    SDL_Texture* aTextTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if(!aTextTexture)
    {
        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // 定义图片初始位置和速度
    int imgX = 400;
    int imgY = 550;
    int imgW = 50;
    int imgH = 50;
    int imgSpeed = 3;
    int direction = 1; // 1: 右移, -1: 左移

    // 渲染循环
    while(true)
    {
        SDL_Event event;
        if(SDL_PollEvent(&event)) // 使用SDL_PollEvent检查是否有新的事件
        {
            if (event.type == SDL_QUIT) // 处理退出事件
            {
                break; 
            }
        }

        // 更新图片位置
        imgX += imgSpeed * direction;
        if (imgX <= 0 || imgX + imgW >= 800) // 碰到窗口(横向窗口X轴)边缘就反向
        {
            direction *= -1;
        }

        // 清屏
        SDL_RenderClear(renderer);  // 清除渲染器的内容，准备绘制新的帧
        // 画一个长方形
        SDL_Rect rect = {150, 100, 200, 200}; // 长方形的 中心位置x,y 矩形的宽高w,h
        SDL_SetRenderDrawColor(renderer, 0, 200, 222, 255); // 画笔设置蓝色
        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   // 恢复窗口的底色

        // 画图片
        SDL_Rect aImgRect = {400, 100, 300, 300};
        SDL_RenderCopy(renderer, texture, nullptr, &aImgRect);

         // 画图片（动画）
        SDL_Rect aImgRect1 = {imgX, imgY, imgW, imgH};
        SDL_RenderCopy(renderer, texture, nullptr, &aImgRect1);

        // 显示文本
        SDL_Rect textRect = {380, 100, surface->w, surface->h}; // 文本位置
        SDL_RenderCopy(renderer, aTextTexture, nullptr, &textRect);

        // 更新屏幕，将渲染器的内容更新到屏幕上
        SDL_RenderPresent(renderer);

        SDL_Delay(20); // 控制帧率，大约60FPS
    }


    // 清理和退出，程序结束时需要释放所有SDL资源
    // SDL图片资源清理
    SDL_DestroyTexture(texture);
    IMG_Quit();

    // SDL音频资源清理
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    Mix_Quit();
    
    // SDL字体资源清理
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(aTextTexture);
    TTF_CloseFont(font);
    TTF_Quit();

    // SDL清理
    SDL_DestroyRenderer(renderer); // 销毁渲染器
    SDL_DestroyWindow(window);     // 销毁窗口
    SDL_Quit();                    // 退出SDL库

    return 0;
}