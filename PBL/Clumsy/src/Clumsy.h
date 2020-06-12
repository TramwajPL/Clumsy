#pragma once

// FOR APPLICATION

#include "Core/Game.h"
#include "Core/Parser.h"
#include "Core/CoreEngine.h"
#include "Core/MousePicker.h"

/////////////////
 
// COMPONENTS
#include "Components/RenderModelComponent.h"

////////////////

#include "Components/MoveComponent.h"
#include "Components/PhysicsObjectComponent.h"
#include "Components/PhysicsEngineComponent.h"

// RENDERING

#include "RenderEngine/Model.h"
#include "RenderEngine/Camera.h"
#include "RenderEngine/Lighting.h"
#include "RenderEngine/RenderEngine.h"
#include "RenderEngine/PostProcessor.h"

/////////////////


// PHYSICS

#include "PhysicsEngine/Aabb.h"
#include "PhysicsEngine/PhysicsEngine.h"
#include "PhysicsEngine/BoundingSphere.h"

/////////////////

// AUDIO

#include "Audio/AudioMaster.h"

//////////////////

// EVENTS

#include "EventSystem/Event.h"
#include "EventSystem/Listener.h"
#include "EventSystem/EventSystem.h"

//////////////////

// CANVAS

#include "GUI/GUI.h"
#include "GUI/Button.h"
#include "GUI/StoreGUI.h"
#include "GUI/WarehouseGUI.h"

//////////////////

// GAME

#include "Game/Player.h"
#include "Game/TurnClass.h"
#include "Game/TurnSystem.h"
#include "Game/Enemy.h"
//////////////////