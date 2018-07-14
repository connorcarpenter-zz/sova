//
// Created by connor on 7/7/18.
//

#include <Modules/Input/Input.h>
#include "OryolApp.h"

OryolApp::OryolApp(Sova::App* sovaApp) {
    sovapp = sovaApp;
}

OryolApp* OryolApp::singleton = nullptr;

void OryolApp::initOryolApp(Sova::App* sovaApp) {
    singleton = new OryolApp(sovaApp);
}

OryolApp* OryolApp::getOryolApp() {
    return singleton;
}

AppState::Code OryolApp::OnInit()
{
    canvasWidth = sovapp->width / 2;
    canvasHeight = sovapp->height / 2;
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

    //Setup offscreen render target
    auto renderTargetSetup = TextureSetup::RenderTarget2D(canvasWidth, canvasHeight);
    renderTargetSetup.Sampler.MinFilter = TextureFilterMode::Nearest;
    renderTargetSetup.Sampler.MagFilter = TextureFilterMode::Nearest;
    Id canvasTexture = Gfx::CreateResource(renderTargetSetup);
    this->canvasPass = Gfx::CreateResource(PassSetup::From(canvasTexture));

    //Setup onscreen render
    auto fullscreenQuadSetup = MeshSetup::FullScreenQuad(Gfx::QueryFeature(GfxFeature::OriginTopLeft));
    this->windowDrawState.Mesh[0] = Gfx::CreateResource(fullscreenQuadSetup);

    Id normalShader = sovapp->shaderHandler->getNormalShader();
    auto ps = PipelineSetup::FromLayoutAndShader(fullscreenQuadSetup.Layout, normalShader);
    this->windowDrawState.Pipeline = Gfx::CreateResource(ps);
    this->windowDrawState.FSTexture[0] = canvasTexture;

    setupCanvas(renderTargetSetup);

    sovapp->loader->setAppLoaded();

    return App::OnInit();
}

AppState::Code OryolApp::OnRunning() {

    // update the game in the Sova app

    sovapp->updateFunction();

    Gfx::BeginPass(this->canvasPass);
    sovapp->draw();
    Gfx::EndPass();

    // copy offscreen render target into backbuffer
    Gfx::BeginPass();
    Gfx::ApplyDrawState(this->windowDrawState);
    Gfx::Draw();
    Gfx::EndPass();

    Gfx::CommitFrame();

    // continue running or quit?
    return Gfx::QuitRequested() ? AppState::Cleanup : AppState::Running;
}

AppState::Code OryolApp::OnCleanup() {

    Gfx::Discard();
    IO::Discard();
    Input::Discard();

    return App::OnCleanup();
}

//--
void
OryolApp::setupCanvas(const TextureSetup& rtSetup)
{
    // setup draw state with dynamic mesh
    this->meshSetup = MeshSetup::Empty(6, Usage::Stream);
    this->meshSetup.Layout
            .Add(VertexAttr::Position, VertexFormat::Float2)
            .Add(VertexAttr::TexCoord0, VertexFormat::Float2);
    this->meshSetup.AddPrimitiveGroup(PrimitiveGroup(0, 6));
    this->meshSetup.Locator = Locator("2d_sprite_mesh");

    Id canvasShader = sovapp->shaderHandler->getCanvasShader();
    this->pipelineSetup = PipelineSetup::FromLayoutAndShader(this->meshSetup.Layout, canvasShader);
    this->pipelineSetup.BlendState.BlendEnabled = true;
    this->pipelineSetup.BlendState.SrcFactorRGB = BlendFactor::SrcAlpha;
    this->pipelineSetup.BlendState.DstFactorRGB = BlendFactor::OneMinusSrcAlpha;
    this->pipelineSetup.BlendState.ColorFormat = rtSetup.ColorFormat;
    this->pipelineSetup.BlendState.DepthFormat = rtSetup.DepthFormat;
    this->pipelineSetup.RasterizerState.CullFaceEnabled = false;

    this->meshResource = Gfx::CreateResource(this->meshSetup);
    this->pipelineResource = Gfx::CreateResource(this->pipelineSetup);

    // clear the vertex buffer
    Memory::Clear(this->vertexBuffer, sizeof(this->vertexBuffer));
}

bool OryolApp::keyPressed(Sova::Key::Code key) {
    Oryol::Key::Code oryolKey = (Oryol::Key::Code) key;
    return Input::KeyPressed(oryolKey);
}

bool OryolApp::mouseButtonPressed(Sova::MouseButton::Code btn) {
    Oryol::MouseButton::Code oryolBtn = (Oryol::MouseButton::Code) btn;
    return Input::MouseButtonPressed(oryolBtn);
}

int OryolApp::getMouseX() {
    return (int) Input::MousePosition().x;
}

int OryolApp::getMouseY() {
    return (int) Input::MousePosition().y;
}
