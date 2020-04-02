#include "SceneStateMachine.h"

void SceneStateMachine::Update(DWORD deltaTime)
{
    // nếu scene hiện tại khác null
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

    //gọi hàm thay thế contructor của các scene
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
        if (curScene)
        {
            // If we have a current scene, we call its OnDeactivate method.
            // phần disactivate và OnActivate dùng để vô hiệu hóa trạng
            // thái các đối tượng trong scene cũ, ta chưa cần dùng đến
       //     curScene->OnDeactivate();
        }

        // Setting the current scene ensures that it is updated and drawn.
        // set current scene là scene vừa chuyển sang
        curScene = it->second;

     //   curScene->OnActivate();
    }
}


///loại bỏ scene ra khỏi map scenes
void SceneStateMachine::Remove(unsigned int id)
{
    auto it = scenes.find(id);
    if (it != scenes.end())
    {
        if (curScene == it->second)
        {
            // If the scene we are removing is the current scene, 
            // we also want to set that to a null pointer so the scene 
            // is no longer updated.
            curScene = nullptr;
        }

        // We make sure to call the OnDestroy method 
        // of the scene we are removing.
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
