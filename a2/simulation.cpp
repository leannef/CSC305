#include "simulation.h"

#include "scene.h"

#include "imgui.h"

#define FLYTHROUGH_CAMERA_IMPLEMENTATION
#include "flythrough_camera.h"

#include <glm/gtc/type_ptr.hpp>

#include <SDL.h>

std::vector<uint32_t> mSpinningTransformIDs;

void Simulation::Init(Scene* scene)
{
    mScene = scene;

    std::vector<uint32_t> loadedMeshIDs;

    loadedMeshIDs.clear();
    LoadMeshesFromFile(mScene, "assets/cube/cube.obj", &loadedMeshIDs);
    for (uint32_t loadedMeshID : loadedMeshIDs)
    {
        uint32_t newInstanceID;
        AddMeshInstance(mScene, loadedMeshID, &newInstanceID);

        // scale up the cube
        uint32_t newTransformID = scene->Instances[newInstanceID].TransformID;
        scene->Transforms[newTransformID].Scale = glm::vec3(2.0f);
        scene->Transforms[newTransformID].ParentID = -1;
    }

    loadedMeshIDs.clear();
    LoadMeshesFromFile(mScene, "assets/teapot/teapot.obj", &loadedMeshIDs);
    for (uint32_t loadedMeshID : loadedMeshIDs)
    {
        // place a teapot on top of the cube
        {
            uint32_t newInstanceID1;
            AddMeshInstance(scene, loadedMeshID, &newInstanceID1);
            uint32_t newTransformID1 = scene->Instances[newInstanceID1].TransformID;
            scene->Transforms[newTransformID1].Translation += glm::vec3(0.0f, 2.0f, 0.0f);
            scene->Transforms[newTransformID1].ParentID = -1;

            uint32_t newInstanceID2;
            AddMeshInstance(scene, loadedMeshID, &newInstanceID2);
            uint32_t newTransformID2 = scene->Instances[newInstanceID2].TransformID;
            mSpinningTransformIDs.push_back(newTransformID2);
            scene->Transforms[newTransformID2].Translation += glm::vec3(3.0f, -1.0f, 4.0f);
            scene->Transforms[newTransformID2].RotationOrigin =	-scene->Transforms[newTransformID2].Translation;
            scene->Transforms[newTransformID2].ParentID = newTransformID1;

        }

        // place a teapot on the side
        {
            uint32_t newInstanceID;
            AddMeshInstance(mScene, loadedMeshID, &newInstanceID);
            uint32_t newTransformID = scene->Instances[newInstanceID].TransformID;
            scene->Transforms[newTransformID].Translation += glm::vec3(3.0f, 1.0f, -4.0f);

        }
        {
            uint32_t newInstanceID;
            AddMeshInstance(mScene, loadedMeshID, &newInstanceID);
            uint32_t newTransformID = scene->Instances[newInstanceID].TransformID;
            scene->Transforms[newTransformID].Translation += glm::vec3(3.0f, 2.0f, 0.0f);

        }

       }


    loadedMeshIDs.clear();
    LoadMeshesFromFile(mScene, "assets/floor/floor.obj", &loadedMeshIDs);
    for (uint32_t loadedMeshID : loadedMeshIDs)
    {
        uint32_t newInstanceID;
        AddMeshInstance(mScene, loadedMeshID, &newInstanceID);
        scene->Transforms[scene->Instances[newInstanceID].TransformID].ParentID = -1;
    }

    loadedMeshIDs.clear();
    LoadMeshesFromFile(mScene, "assets/sponza/sponza.obj", &loadedMeshIDs);
    for (uint32_t loadedMeshID : loadedMeshIDs)
    {
        if (scene->Meshes[loadedMeshID].Name == "sponza_04")
        {
            continue; }
            uint32_t newInstanceID;
            AddMeshInstance(mScene, loadedMeshID, &newInstanceID);
            uint32_t newTransformID = scene->Instances[newInstanceID].TransformID;
            scene->Transforms[newTransformID].Scale = glm::vec3(1.0f / 50.0f);

    }

    loadedMeshIDs.clear();
    LoadMeshesFromFile(mScene, "assets/skybox/skybox.obj", &loadedMeshIDs);
    for (uint32_t loadedMeshID : loadedMeshIDs)
    {
            uint32_t newInstanceID;
            AddMeshInstance(mScene, loadedMeshID, &newInstanceID);
            uint32_t newTransformID = scene->Instances[newInstanceID].TransformID;
            scene->Transforms[newTransformID].Scale = glm::vec3(1.0f /300.0f );

    }



    Camera mainCamera;
    mainCamera.Eye = glm::vec3(8,4,1);
    glm::vec3 target = glm::vec3(3, 3, 0.0f);
    mainCamera.Look = normalize(target - mainCamera.Eye);
    mainCamera.Up = glm::vec3(0.0f, 1.0f, 0.0f);
    mainCamera.FovY = glm::radians(70.0f);
    mScene->MainCamera = mainCamera;


    Light mainLight;
    mainLight.Position = glm::vec3(5,1,3);
    glm::vec3 target1 = glm::vec3(0.0f);
    mainLight.Direction = normalize(target1 - mainLight.Position);
    mainLight.Up = glm::vec3(0.0f, 1.0f, 0.0f);
    mainLight.FovY = glm::radians(70.0f);
    mScene->MainLight = mainLight;

}

void Simulation::HandleEvent(const SDL_Event& ev)
{
    if (ev.type == SDL_MOUSEMOTION)
    {
        mDeltaMouseX += ev.motion.xrel;
        mDeltaMouseY += ev.motion.yrel;
    }
}

void Simulation::Update(float deltaTime)
{
    const Uint8* keyboard = SDL_GetKeyboardState(NULL);

    int mx, my;
    Uint32 mouse = SDL_GetMouseState(&mx, &my);

    float angularVelocity = 30.0f; // rotating at 30 degrees per second

    for (uint32_t mSpinningTransformID : mSpinningTransformIDs)
        mScene->Transforms[mSpinningTransformID].Rotation *=glm::angleAxis(glm::radians(angularVelocity * deltaTime),glm::vec3(0.0f, 1.0f, 0.0f));

    if ((mouse & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0)
    {
        flythrough_camera_update(
            value_ptr(mScene->MainCamera.Eye),
            value_ptr(mScene->MainCamera.Look),
            value_ptr(mScene->MainCamera.Up),
            NULL,
            deltaTime,
            5.0f, // eye_speed
            0.1f, // degrees_per_cursor_move
            80.0f, // max_pitch_rotation_degrees
            mDeltaMouseX, mDeltaMouseY,
            keyboard[SDL_SCANCODE_W], keyboard[SDL_SCANCODE_A], keyboard[SDL_SCANCODE_S], keyboard[SDL_SCANCODE_D],
            keyboard[SDL_SCANCODE_SPACE], keyboard[SDL_SCANCODE_LCTRL],
            0);
    }

    mDeltaMouseX = 0;
    mDeltaMouseY = 0;

    Light& light = mScene->MainLight;
    if (ImGui::Begin("Example GUI Window"))
    {
        ImGui::Text("Mouse Pos: (%d, %d)", mx, my);
        ImGui::SliderFloat3("Light position", value_ptr(light.Position), -40.0f, 40.0f);
    }
    ImGui::End();


}

void* Simulation::operator new(size_t sz)
{
    // zero out the memory initially, for convenience.
    void* mem = ::operator new(sz);
    memset(mem, 0, sz);
    return mem;
}

