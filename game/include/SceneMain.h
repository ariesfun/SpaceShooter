#pragma once 

#include "Scene.h"

// 场景的主类，负责管理主场景的逻辑
class SceneMain :public Scene {
public:
    SceneMain();
    ~SceneMain();

public:
    void Init() override;                           // 初始化场景
    void Update() override;                         // 更新场景
    void Render() override;                         // 渲染场景
    void Clean() override;                          // 清理场景 
    void HandleEvent(SDL_Event* event) override;    // 处理事件


};