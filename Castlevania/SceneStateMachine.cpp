#include "SceneStateMachine.h"

void SceneStateMachine::Update(DWORD deltaTime)
{
    if (curScene)
    {
        curScene->Update(deltaTime);
    }
}

void SceneStateMachine::Render()
{
    if (curScene)
    {
        curScene->Render();
    }
}

unsigned int SceneStateMachine::Add(std::shared_ptr<Scene> scene)
{
    //trả về scene vừa thêm vào map scene
    auto inserted = scenes.insert(std::make_pair(insertedSceneID, scene));

    insertedSceneID++;
    inserted.first->second->OnCreate();

    // trả về id scene vừa thêm vào
    return insertedSceneID - 1;
}

void SceneStateMachine::SwitchTo(unsigned int id)
{

    // trả về scene theo id truyền vào
    auto it = scenes.find(id);
    if (it != scenes.end())
    {
        if (curScene) {};

        curScene = it->second;
    }
}


///loại bỏ scene ra khỏi map scenes
void SceneStateMachine::Remove(unsigned int id)
{
    auto it = scenes.find(id);
    if (it != scenes.end())
    {
        if (curScene == it->second){
            curScene = nullptr;
        }
        it->second->OnDestroy();

        scenes.erase(it);
    }
}

void SceneStateMachine::OnKeyDown(int KeyCode)
{
    if (curScene)
    {
        curScene->OnKeyDown(KeyCode);
    }
}

void SceneStateMachine::OnKeyUp(int KeyCode)
{
    if (curScene)
    {
        curScene->OnKeyUp(KeyCode);
    }
}

void SceneStateMachine::KeyState(BYTE* states)
{
    if (curScene)
    {
        curScene->KeyState(states);
    }
}
