//
// Created by connor on 7/7/18.
//

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
    canvasWidth = sovapp->width;
    canvasHeight = sovapp->height;
    dispWidth = canvasWidth * 2;
    dispHeight = canvasHeight * 2;

    //Setup screen
    Gfx::Setup(GfxSetup::Window(dispWidth, dispHeight, "Oryol 2d example"));

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

    // setup resource
    TextureSetup texBluePrint;
    texBluePrint.Sampler.MinFilter = TextureFilterMode::Nearest;
    texBluePrint.Sampler.MagFilter = TextureFilterMode::Nearest;
    texBluePrint.Sampler.WrapU = TextureWrapMode::ClampToEdge;
    texBluePrint.Sampler.WrapV = TextureWrapMode::ClampToEdge;
    static const char* texturePath = "content:images/myNinaSmall.png";
    this->texture = Gfx::LoadResource(PNGLoader::Create(TextureSetup::FromFile(texturePath, texBluePrint)));

    //Setup offscreen render target
    auto rtSetup = TextureSetup::RenderTarget2D(canvasWidth, canvasHeight);
    rtSetup.Sampler.MinFilter = TextureFilterMode::Nearest;
    rtSetup.Sampler.MagFilter = TextureFilterMode::Nearest;
    Id canvasTexture = Gfx::CreateResource(rtSetup);
    this->canvasPass = Gfx::CreateResource(PassSetup::From(canvasTexture));

    auto quadSetup = MeshSetup::FullScreenQuad(Gfx::QueryFeature(GfxFeature::OriginTopLeft));
    this->canvasDrawState.Mesh[0] = Gfx::CreateResource(quadSetup);
    Id shd = sovapp->shaderHandler->getNormalShader();

    auto ps = PipelineSetup::FromLayoutAndShader(quadSetup.Layout, shd);
    this->canvasDrawState.Pipeline = Gfx::CreateResource(ps);
    this->canvasDrawState.FSTexture[0] = canvasTexture;

    setupCanvas(rtSetup);

    sovapp->loader->setAppLoaded();

    return App::OnInit();
}

AppState::Code OryolApp::OnRunning() {

    // update the game in the Sova app

    sovapp->updateFunction();

    Gfx::BeginPass(this->canvasPass);

    sovapp->draw();

    // render into offscreen render target

    Gfx::EndPass();

    // copy offscreen render target into backbuffer
    Gfx::BeginPass();
    Gfx::ApplyDrawState(this->canvasDrawState);
    Gfx::Draw();
    Gfx::EndPass();

    Gfx::CommitFrame();

    // continue running or quit?
    return Gfx::QuitRequested() ? AppState::Cleanup : AppState::Running;
}

AppState::Code OryolApp::OnCleanup() {

    Gfx::Discard();
    IO::Discard();

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

    Id shd = sovapp->shaderHandler->getCanvasShader();
    this->pipelineSetup = PipelineSetup::FromLayoutAndShader(this->meshSetup.Layout, shd);
    this->pipelineSetup.BlendState.BlendEnabled = true;
    this->pipelineSetup.BlendState.SrcFactorRGB = BlendFactor::SrcAlpha;
    this->pipelineSetup.BlendState.DstFactorRGB = BlendFactor::OneMinusSrcAlpha;
    this->pipelineSetup.BlendState.ColorFormat = rtSetup.ColorFormat;
    this->pipelineSetup.BlendState.DepthFormat = rtSetup.DepthFormat;
    this->pipelineSetup.RasterizerState.CullFaceEnabled = false;

    // clear the vertex buffer
    Memory::Clear(this->vertexBuffer, sizeof(this->vertexBuffer));
}