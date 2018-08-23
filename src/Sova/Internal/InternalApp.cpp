//
// Created by connor on 7/7/18.
//

#include <Modules/Input/Input.h>
#include <Modules/Core/Time/TimePoint.h>
#include <Modules/Core/Time/Clock.h>
#include "InternalApp.h"

InternalApp::InternalApp(Sova::App* sovaApp) {
    sovapp = sovaApp;
}

InternalApp* InternalApp::singleton = nullptr;

void InternalApp::initInternalApp(Sova::App *sovaApp) {
    singleton = new InternalApp(sovaApp);
}

InternalApp* InternalApp::getInternalApp() {
    return singleton;
}

Sova::App* InternalApp::getSovaApp() {
    return singleton->sovapp;
}

void* InternalApp::getGlobal() {
    return singleton->sovapp->getGlobal();
}

AppState::Code InternalApp::OnInit()
{
    dispWidth = sovapp->width;
    dispHeight = sovapp->height;

    //Setup screen
    Gfx::Setup(GfxSetup::Window(dispWidth, dispHeight, sovapp->windowTitle->AsCStr()));
    Input::Setup();

    // setup IO system
    IOSetup ioSetup;
#if ORYOL_EMSCRIPTEN
    ioSetup.FileSystems.Add("http", HTTPFileSystem::Creator());
    ioSetup.Assigns.Add("content:", "http://localhost:8000/content/");
#else
    ioSetup.FileSystems.Add("file", LocalFileSystem::Creator());
    ioSetup.Assigns.Add("content:", "root:content/");
#endif

    IO::Setup(ioSetup);

    resourceManager.setup();

    // setup draw state with dynamic mesh
    this->meshSetup = MeshSetup::Empty(6, Usage::Stream);
    this->meshSetup.Layout
            .Add(VertexAttr::Position, VertexFormat::Float2)
            .Add(VertexAttr::TexCoord0, VertexFormat::Float2)
            .Add(VertexAttr::Color0, VertexFormat::Float3);
    this->meshSetup.AddPrimitiveGroup(PrimitiveGroup(0, 6));
    this->meshSetup.Locator = Locator("2d_sprite_mesh");

    Id canvasShader = sovapp->shaderHandler->getCanvasShader();
    auto pipelineSetup = PipelineSetup::FromLayoutAndShader(this->meshSetup.Layout, canvasShader);
    pipelineSetup.BlendState.BlendEnabled = true;
    pipelineSetup.BlendState.SrcFactorRGB = BlendFactor::SrcAlpha;
    pipelineSetup.BlendState.DstFactorRGB = BlendFactor::OneMinusSrcAlpha;
    pipelineSetup.BlendState.ColorFormat = PixelFormat::RGBA8;
    pipelineSetup.BlendState.DepthFormat = PixelFormat::None;
    pipelineSetup.RasterizerState.CullFaceEnabled = false;

    this->meshResource = Gfx::CreateResource(this->meshSetup);
    this->pipelineResource = Gfx::CreateResource(pipelineSetup);

    // clear the vertex buffer
    Memory::Clear(this->vertexBuffer, sizeof(this->vertexBuffer));

    sovapp->loader->setAppLoaded();

    return App::OnInit();
}

static TimePoint frameTimePoint;

AppState::Code InternalApp::OnRunning()
{
    // update the game in the Sova app
    double frameDelta = Clock::LapTime(frameTimePoint).AsMilliSeconds();

    sovapp->updateTimers(frameDelta);
    sovapp->updateFunction((float) frameDelta);
    destructionManager.FinalizeDestruction();

    //Drawing
    sovapp->drawCameras();
    Oryol::Gfx::BeginPass();
    sovapp->drawViewports();
    Oryol::Gfx::EndPass();
    Gfx::CommitFrame();

    //Network
    sovapp->updateWebsockets();
    sovapp->updateHttpRequests();

    // continue running or quit?
    return Gfx::QuitRequested() ? AppState::Cleanup : AppState::Running;
}

AppState::Code InternalApp::OnCleanup() {

    Gfx::Discard();
    IO::Discard();
    Input::Discard();

    return App::OnCleanup();
}

//--


bool InternalApp::keyPressed(Sova::Key::Code key) {
    Oryol::Key::Code oryolKey = (Oryol::Key::Code) key;
    return Input::KeyPressed(oryolKey);
}

bool InternalApp::mouseButtonPressed(Sova::MouseButton::Code btn) {
    Oryol::MouseButton::Code oryolBtn = (Oryol::MouseButton::Code) btn;
    return Input::MouseButtonPressed(oryolBtn);
}

int InternalApp::getMouseX() {
    return (int) Input::MousePosition().x;
}

int InternalApp::getMouseY() {
    return (int) Input::MousePosition().y;
}
