#pragma once 

#include "Scene.h"
#include "Object.h"

#include <SDL.h>

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

public:
    void KeyboardControlPlayer();                   // 让玩家通过键盘来控制飞机

private:
    Player m_player; // 玩家飞机对象

};
