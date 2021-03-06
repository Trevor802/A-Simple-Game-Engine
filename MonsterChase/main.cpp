#pragma once
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <ctime>
#include <cstring>
#include <Windows.h>
#include <iostream>
#include <chrono>
#include "SmartPtr.h"
#include "GameObject.hpp"
#include "BaseComponent.h"
#include "RendererComponent.h"
#include "PhysicsComponent.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "PlayerController.hpp"
#include "MonsterController.hpp"
#include "_Sprite/SpriteRender.cpp"
#include <vector>
#include <fstream>
#include "json.hpp"
#include "World.h"
#include <thread>
#include "JobSystem.h"
#include "TimeManager.h"
#include "ScopeLock.h"
#include "Mutex.h"

#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

#include "GLib.h"

using namespace std;
using json = nlohmann::json;
using namespace Engine;

void* LoadFile(const char* i_pFilename, size_t& o_sizeFile);
GLib::Sprites::Sprite* CreateSprite(const char* i_pFilename, float i_Scale);
struct GLib::Sprites::Sprite;

static bool bQuit;
static Vector2 m_input = Vector2();
const float m_speed = 100.0f;

World* pWorld = new World();
CollisionManager* pCollisionManager = new CollisionManager();
vector< GLib::Sprites::Sprite*> Sprites;


class CreateGameObjectsFromFile {
public:
	CreateGameObjectsFromFile(string i_FileName) : m_FileName(i_FileName) { assert(!i_FileName.empty()); };
	void operator() () {
		ifstream jFile(m_FileName);
		json j;
		jFile >> j;
		jFile.close();
		for (auto o : j)
		{
			Vector2 position = Vector2(o["position"][0], o["position"][1]);
			float rot = o["rotation"];
			string name = o["name"];
			string spritePath = o["sprite"];
			float size = o["size"];
			string controllerName = o["controller"];

			StrongPtr<GameObject> gameObject = StrongPtr<GameObject>(new GameObject(position, name));
			gameObject->transform->SetRotation(rot);
			gameObject->transform->gameObject = gameObject;
			gameObject->self = gameObject;
			pWorld->AddNewGameObject(gameObject);
			GLib::Sprites::Sprite* sprite = CreateSprite(spritePath.c_str(), size);

			if (sprite) {
				Sprites.push_back(sprite);
				StrongPtr<RendererComponent> renderer = StrongPtr<RendererComponent>(new RendererComponent());
				renderer->SetSprite(sprite);
				StrongPtr<PhysicsComponent> physics = StrongPtr<PhysicsComponent>(new PhysicsComponent());
				physics->bUseGravity = false;
				StrongPtr<BoxCollider> boxCollider = StrongPtr<BoxCollider>(new BoxCollider());
				unsigned int width, height, depth;
				bool result = GLib::GetDimensions(sprite->m_pTexture, width, height, depth);
				assert(result);
				assert(width > 0 && height > 0);
				boxCollider->Size = Vector2((float)width / 2, (float)height / 2);
				boxCollider->Center = Vector2(0, (float)height / 2);
				StrongPtr<MonsterController> controller = StrongPtr<MonsterController>(new MonsterController(j[0]["controller"].get<MovingStrategy>()));
				gameObject->AddComponent<MonsterController>(controller);
				gameObject->AddComponent<PhysicsComponent>(physics);
				gameObject->AddComponent<RendererComponent>(renderer);
				gameObject->AddComponent<BoxCollider>(boxCollider);
			}
		}
	}

private:
	string m_FileName;
};

void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
{
#ifdef _DEBUG
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];
	if (i_VKeyID == 0x51 && !bWentDown)
		bQuit = true;
	if (i_VKeyID == 0x57 && bWentDown)
		m_input = Vector2(0, 1);
	if (i_VKeyID == 0x53 && bWentDown)
		m_input = Vector2(0, -1);
	if (i_VKeyID == 0x41 && bWentDown)
		m_input = Vector2(-1, 0);
	if (i_VKeyID == 0x44 && bWentDown)
		m_input = Vector2(1, 0);
	if (!bWentDown)
		m_input = Vector2();
	sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	//OutputDebugStringA(Buffer);

#endif // __DEBUG
}

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	// IMPORTANT: first we need to initialize GLib
	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600);
	Time::firstFrameTime = chrono::high_resolution_clock::now();
	Time::lastFrameTime = chrono::high_resolution_clock::now();

	if (bSuccess)
	{
		// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
		GLib::SetKeyStateChangeCallback(TestKeyCallback);
		WeakPtr<GameObject> hero;
		{
			StrongPtr<GameObject> pHero = StrongPtr<GameObject>(new GameObject(Vector2(-300, -200), "trevor"));
			pHero->self = pHero;
			pHero->transform->gameObject = pHero;
			pWorld->AddNewGameObject(pHero);
			pWorld->CheckNewGameObjects();
			hero = pHero;
		}
		
		// Create a couple of sprites using our own helper routine CreateSprite
		GLib::Sprites::Sprite* pGoodGuy = CreateSprite("Sprites\\green.dds", 1.f);
#pragma region Initialize
		if (pGoodGuy) {
			StrongPtr<RendererComponent> renderer = StrongPtr<RendererComponent>(new RendererComponent());
			renderer->SetSprite(pGoodGuy);
			StrongPtr<PhysicsComponent> physics = StrongPtr<PhysicsComponent>(new PhysicsComponent());
			physics->bUseGravity = false;
			StrongPtr<BoxCollider> boxCollider = StrongPtr<BoxCollider>(new BoxCollider());
			unsigned int width, height, depth;
			bool result = GLib::GetDimensions(pGoodGuy->m_pTexture, width, height, depth);
			assert(result);
			assert(width > 0 && height > 0);
			boxCollider->Size = Vector2((float)width / 2, (float)height / 2);
			boxCollider->Center = Vector2(0, (float)height / 2);
			if (hero) {
				hero->AddComponent<PhysicsComponent>(physics);
				StrongPtr<PlayerController> controller = StrongPtr<PlayerController>(new PlayerController());
				hero->AddComponent<PlayerController>(controller);
				hero->AddComponent<RendererComponent>(renderer);
				hero->AddComponent<BoxCollider>(boxCollider);
			}
		}
		Engine::JobSystem::CreateQueue();
		using namespace std::placeholders;
		{
			Engine::JobSystem::RunJob(0, std::bind(CreateGameObjectsFromFile("objects.json")));
			do {
				pWorld->CheckNewGameObjects();
				Sleep(10);
			} while (Engine::JobSystem::HasJob(0));
		}
		pWorld->CheckNewGameObjects();
#pragma endregion

		do
		{
			Time::deltaTime = chrono::duration_cast<chrono::duration<float>>(chrono::high_resolution_clock::now() - Time::lastFrameTime).count();
			Time::lastFrameTime = chrono::high_resolution_clock::now();
			// IMPORTANT: We need to let GLib do it's thing. 
			GLib::Service(bQuit);
		
			if (!bQuit)
			{
				// Fixed update: physics
				if (chrono::duration_cast<chrono::duration<float>>(
					Time::lastFrameTime - Time::lastFixedFrameTime).count() > Time::fixedDeltaTime) {
					pCollisionManager->SetColliders(pWorld);
					pCollisionManager->ProcessCollisions();
					Time::lastFixedFrameTime = chrono::high_resolution_clock::now();
				}

				// IMPORTANT: Tell GLib that we want to start rendering
				GLib::BeginRendering();
				// Tell GLib that we want to render some sprites
				GLib::Sprites::BeginRendering();
				if (pGoodGuy)
				{
					hero->GetComponent<PlayerController>()->SetInput(m_input);
				}
				for (auto o : pWorld->GetGameObjects()) {
					o->Update(Time::deltaTime);
				}

				// Tell GLib we're done rendering sprites
				GLib::Sprites::EndRendering();
				// IMPORTANT: Tell GLib we're done rendering
				GLib::EndRendering();
			}
		} while (bQuit == false);

		if (pGoodGuy)
			GLib::Sprites::Release(pGoodGuy);
		for (auto sprite : Sprites )
		{
			GLib::Sprites::Release(sprite);
		}
		// IMPORTANT:  Tell GLib to shutdown, releasing resources.
		GLib::Shutdown();
	}
	delete pWorld;
	delete pCollisionManager;

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG

}

GLib::Sprites::Sprite* CreateSprite(const char* i_pFilename, float i_Scale = 1.0f)
{
	assert(i_pFilename);

	size_t sizeTextureFile = 0;

	// Load the source file (texture data)
	void* pTextureFile = LoadFile(i_pFilename, sizeTextureFile);

	// Ask GLib to create a texture out of the data (assuming it was loaded successfully)
	GLib::Texture* pTexture = pTextureFile ? GLib::CreateTexture(pTextureFile, sizeTextureFile) : nullptr;

	// exit if something didn't work
	// probably need some debug logging in here!!!!
	if (pTextureFile)
		delete[] pTextureFile;

	if (pTexture == nullptr)
		return NULL;

	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int depth = 0;

	// Get the dimensions of the texture. We'll use this to determine how big it is on screen
	bool result = GLib::GetDimensions(pTexture, width, height, depth);
	assert(result == true);
	assert((width > 0) && (height > 0));

	// Define the sprite edges
	GLib::Sprites::SpriteEdges	Edges = { -float(width / 2.0f * i_Scale), float(height * i_Scale), float(width / 2.0f * i_Scale), 0.0f };
	GLib::Sprites::SpriteUVs	UVs = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f } };
	GLib::RGBA							Color = { 255, 255, 255, 255 };

	// Create the sprite
	GLib::Sprites::Sprite* pSprite = GLib::Sprites::CreateSprite(Edges, 0.1f, Color, UVs);
	if (pSprite == nullptr)
	{
		GLib::Release(pTexture);
		return nullptr;
	}

	// Bind the texture to sprite
	GLib::Sprites::SetTexture(*pSprite, *pTexture);

	return pSprite;
}

void* LoadFile(const char* i_pFilename, size_t& o_sizeFile)
{
	assert(i_pFilename != NULL);

	FILE* pFile = NULL;

	errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
	if (fopenError != 0)
		return NULL;

	assert(pFile != NULL);

	int FileIOError = fseek(pFile, 0, SEEK_END);
	assert(FileIOError == 0);

	long FileSize = ftell(pFile);
	assert(FileSize >= 0);

	FileIOError = fseek(pFile, 0, SEEK_SET);
	assert(FileIOError == 0);

	uint8_t* pBuffer = new uint8_t[FileSize];
	assert(pBuffer);

	size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
	assert(FileRead == FileSize);

	fclose(pFile);

	o_sizeFile = FileSize;

	return pBuffer;
}
/*
struct Counters
{
	long		m_strongCount;
	long		m_weakCount;

	Counters(long i_strongCount = 0, long i_weakCount = 0) :
		m_strongCount(i_strongCount),
		m_weakCount(i_weakCount)
	{

	}
};

template<typename T>
class StrongPointer
{
public:
	StrongPointer(T * i_ptr = NULL);
	~StrongPointer();

	StrongPointer(const StrongPointer & i_other);
	StrongPointer &operator=(const StrongPointer & i_other);

	T * operator->();
	T & operator*();

	operator bool() const;

	bool operator==(const StrongPointer & i_other) const;
};

template<typename T>
class WeakPointer
{
public:
	WeakPointer(T * i_ptr = NULL);

	WeakPointer(const WeakPointer & i_other);
	WeakPointer &operator=(const WeakPointer & i_other);

	StrongPointer<T> Acquire() const;

	bool IsValid() const { return m_pObject != nullptr; }
	operator bool() const { return IsValid();  }

	T * operator->();
	T & operator*();


private:
	T *			m_pObject;
	Counters *	m_pCounters;
};

class UniquePointer
{
public:
	UniquePointer(T * i_ptr = NULL);

	UniquePointer(const UniquePointer & i_other);
	UniquePointer &operator=(const UniquePointer & i_other);

	bool IsValid() const { return m_pObject != nullptr; }
	operator bool() const { return IsValid(); }

	T * operator->();
	T & operator*();

private:
	T *			m_pObject;
};
class Vector3
{
}

class GameObject
{

public:
	Vector3 GetPosition();
};

struct Renderable
{
	WeakPointer<GameObject> m_pObject;
	GLib::Sprite *			m_pSprite;
};

void Draw( Renderable & i_Renderable)
{
	StrongPointer<GameObject> MyObj = i_Renderable.m_pObject.Acquire();

	if (MyObj)
	{
		// if StrongPointer is valid draw it
		GLib::Sprites::RenderSprite(*i_Renderable.m_pSprite, MyObj->GetPosition(), 0.0f);
	}
	else
	{
		// Need to destroy this Renderable since the GameObject has been released
	}
}

void Test()
{
	// Ptr1 is the owner of the new GameObject
	UniquePointer<GameObject> Ptr1(new GameObject("Joe"));

	// Now Ptr2 is the owner and Ptr1 points to NULL
	UniquePointer<GameObject> Ptr2 = Ptr1;

	// Now Ptr1 is the owner and Ptr2 points to NULL
	Ptr1 = Ptr2;
}
*/



//
//  main.cpp
//  GhostChaser
//
//  Created by Trevor Alex on 8/27/19.
//  Copyright © 2019 Trevor Alex. All rights reserved.
//

//#include <iostream>
//#include <ctime>
//#include <string>
//
//#include "MonsterManager.hpp"
//#include "Grid.hpp"
//#include "PlayerController.hpp"
//#include "GLib.h"
//
//#define GRID_WIDTH 5
//#define GRID_HEIGHT 5
//using namespace std;
//
//
//char * getName(){
//    char temp[50];
//    cin >> temp;
//    char *pn = new char[strlen(temp) + 1];
//    strcpy(pn, temp);
//    return pn;
//}
//
//int main(int argc, const char * argv[]) {
//    srand((unsigned int)time(0));
//    Grid grid = Grid(0, 0, GRID_WIDTH, GRID_HEIGHT);
//    MonsterManager* monsterManager = new MonsterManager("Monster", 0, grid);
//    cout << "Input initial monster numbers: ";
//    int initMonster;
//    cin >> initMonster;
//    while (initMonster < 0 || initMonster > MAX_MONSTERS) {
//        cout << "Invalid Number. Input initial monster numbers: ";
//        cin >> initMonster;
//    }
//    for (int i = 0; i < initMonster; i++) {
//        cout << "Input Monster " + to_string(i) + "'s Name: ";
//        monsterManager->spawn(Vector2D::RandInArea(grid.width, grid.height), getName());
//    }
//    cout << "Input Player's Name: ";
//    Actor* hero = new Actor(Vector2D(3, 4), getName());
//    PlayerController* playerController = new PlayerController(grid);
//    playerController->SetActor(hero);
//    monsterManager->SetPlayer(hero);
//    // loop
//    bool update = true;
//    while (update) {
//        cout << "updating" << endl;
//        update = playerController->Update();
//        if (update){
//            monsterManager->update();
//        }
//    };
//    delete hero;
//    delete monsterManager;
//    delete playerController;
//    return 0;
//}
