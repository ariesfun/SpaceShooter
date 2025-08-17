#pragma once
#include <SDL.h>

// 场景抽象基类，其子类负责特定场景的逻辑
class Scene {
public:
    Scene() = default;
    virtual ~Scene() = default;

public:
    virtual void Init() = 0;                             // 初始化场景
    virtual void Update() = 0;                           // 更新场景
    virtual void Render() = 0;                           // 渲染场景
    virtual void Clean() = 0;                            // 清理场景
    virtual void HandleEvent(SDL_Event* event) = 0;      // 处理事件

};