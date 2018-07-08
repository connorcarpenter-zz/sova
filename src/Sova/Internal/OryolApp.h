#pragma once

//
// Created by connor on 7/7/18.
//


#include "Pre.h"
#include "Core/Main.h"
#include "Core/Containers/StaticArray.h"
#include "IO/IO.h"
#include "HttpFS/HTTPFileSystem.h"
#include "LocalFS/LocalFileSystem.h"
#include "Gfx/Gfx.h"
#include "Assets/Gfx/ShapeBuilder.h"
#include "PNGLoader.h"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "shaders.h"

#include <Sova/App.h>

using namespace Oryol;
using namespace Sova;

class OryolApp : public Oryol::App {

public:
    OryolApp(Sova::App* sovaApp);
    AppState::Code OnRunning();
    AppState::Code OnInit();
    AppState::Code OnCleanup();
private:
    Sova::App* sovapp = nullptr;
    Id texture;
    Id canvasPass;
    DrawState canvasDrawState;

    int viewPortX = 0;
    int viewPortY = 0;
    int viewPortW = 0;
    int viewPortH = 0;

    int Width = 0;
    int Height = 0;
    int canvasWidth = 0;
    int canvasHeight = 0;
    int dispWidth = 0;
    int dispHeight = 0;

    void applyViewPort();

    void renderCanvas();
    void setupCanvas(const TextureSetup& rtSetup);
    Oryol::DrawState drawState;
    int numVertices;
    struct vertex {
        float x, y, u, v;
    };
    static const int MaxNumVertices = 6;
    vertex vertexBuffer[MaxNumVertices];

    const void* updateVertices(int& outNumBytes);

    int writeVertex(int index, float x, float y, float u, float v);
};

OryolApp::OryolApp(Sova::App* sovaApp){
    sovapp = sovaApp;
}

AppState::Code OryolApp::OnInit()
{
    Width = sovapp->width;
    Height = sovapp->height;
    canvasWidth = Width;
    canvasHeight = Height;
    dispWidth = canvasWidth * 2;
    dispHeight = canvasHeight * 2;

    //Setup screen
    Gfx::Setup(GfxSetup::Window(dispWidth, dispHeight, "Oryol 2d example"));

    // setup IO system
    IOSetup ioSetup;
#if ORYOL_EMSCRIPTEN
    ioSetup.FileSystems.Add("http", HTTPFileSystem::Creator());
    ioSetup.Assigns.Add("tex:", "http://localhost:8000/data/");
#else
    ioSetup.FileSystems.Add("file", LocalFileSystem::Creator());
    ioSetup.Assigns.Add("tex:", "root:data/");
#endif

    IO::Setup(ioSetup);

    // setup resource
    TextureSetup texBluePrint;
    texBluePrint.Sampler.MinFilter = TextureFilterMode::Nearest;
    texBluePrint.Sampler.MagFilter = TextureFilterMode::Nearest;
    texBluePrint.Sampler.WrapU = TextureWrapMode::ClampToEdge;
    texBluePrint.Sampler.WrapV = TextureWrapMode::ClampToEdge;
    static const char* texturePath = "tex:myNinaSmall.png";
    this->texture = Gfx::LoadResource(PNGLoader::Create(TextureSetup::FromFile(texturePath, texBluePrint)));

    //Setup offscreen render target
    auto rtSetup = TextureSetup::RenderTarget2D(canvasWidth, canvasHeight);
    rtSetup.Sampler.MinFilter = TextureFilterMode::Nearest;
    rtSetup.Sampler.MagFilter = TextureFilterMode::Nearest;
    Id canvasTexture = Gfx::CreateResource(rtSetup);
    this->canvasPass = Gfx::CreateResource(PassSetup::From(canvasTexture));

    auto quadSetup = MeshSetup::FullScreenQuad(Gfx::QueryFeature(GfxFeature::OriginTopLeft));
    this->canvasDrawState.Mesh[0] = Gfx::CreateResource(quadSetup);
    Id shd = Gfx::CreateResource(Shader::Setup());

    auto ps = PipelineSetup::FromLayoutAndShader(quadSetup.Layout, shd);
    this->canvasDrawState.Pipeline = Gfx::CreateResource(ps);
    this->canvasDrawState.FSTexture[0] = canvasTexture;

    setupCanvas(rtSetup);

    return App::OnInit();
}

AppState::Code OryolApp::OnRunning() {

    // render into offscreen render target
    Gfx::BeginPass(this->canvasPass);
    renderCanvas();
    Gfx::EndPass();

    // copy offscreen render target into backbuffer
    Gfx::BeginPass();
    this->applyViewPort();
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

//------------------------------------------------------------------------------
void
OryolApp::applyViewPort() {
    float aspect = float(Width) / float(Height);
    const int fbWidth = Gfx::DisplayAttrs().FramebufferWidth;
    const int fbHeight = Gfx::DisplayAttrs().FramebufferHeight;
    this->viewPortY = 0;
    this->viewPortH = fbHeight;
    this->viewPortW = (const int) (fbHeight * aspect);
    this->viewPortX = (fbWidth - viewPortW) / 2;
    Gfx::ApplyViewPort(this->viewPortX, this->viewPortY, this->viewPortW, this->viewPortH);
}

//--
void
OryolApp::setupCanvas(const TextureSetup& rtSetup) {
    this->numVertices = 6;//(this->numTilesX * this->numTilesY + this->numSprites) * 6;

    // setup draw state with dynamic mesh
    auto meshSetup = MeshSetup::Empty(this->numVertices, Usage::Stream);
    meshSetup.Layout
            .Add(VertexAttr::Position, VertexFormat::Float2)
            .Add(VertexAttr::TexCoord0, VertexFormat::Float2);
    meshSetup.AddPrimitiveGroup(PrimitiveGroup(0, this->numVertices));
    this->drawState.Mesh[0] = Gfx::CreateResource(meshSetup);
    Id shd = Gfx::CreateResource(CanvasShader::Setup());
    auto ps = PipelineSetup::FromLayoutAndShader(meshSetup.Layout, shd);
    ps.BlendState.BlendEnabled = true;
    ps.BlendState.SrcFactorRGB = BlendFactor::SrcAlpha;
    ps.BlendState.DstFactorRGB = BlendFactor::OneMinusSrcAlpha;
    ps.BlendState.ColorFormat = rtSetup.ColorFormat;
    ps.BlendState.DepthFormat = rtSetup.DepthFormat;
    ps.RasterizerState.CullFaceEnabled = false;
    this->drawState.Pipeline = Gfx::CreateResource(ps);

    // setup sprite texture

    this->drawState.FSTexture[0] = this->texture;

    // clear the vertex buffer
    Memory::Clear(this->vertexBuffer, sizeof(this->vertexBuffer));
}

void OryolApp::renderCanvas() {
    const auto resState = Gfx::QueryResourceInfo(this->texture).State;
    if (resState == ResourceState::Valid) {
        int numBytes = 0;
        const void* data = this->updateVertices(numBytes);
        Gfx::UpdateVertices(this->drawState.Mesh[0], data, numBytes);
        Gfx::ApplyDrawState(this->drawState);
        Gfx::Draw();
    }
}

const void*
OryolApp::updateVertices(int& outNumBytes) {
    int vIndex = 0;

    //0 is 0, 1 is canvasWidth, canvasHeight
    float x0 = 0.0f;
    float y0 = 0.0f;
    float x1 = 128.0f / canvasWidth;
    float y1 = 96.0f / canvasHeight;

    //0 is 0, 1 is texWidth/texHeight
    //This is the texture
    float u0 = 0.0f;
    float v0 = 0.0f;
    float u1 = 1.0f;
    float v1 = 1.0f;

    vIndex = this->writeVertex(vIndex, x0, y0, u0, v0);
    vIndex = this->writeVertex(vIndex, x1, y0, u1, v0);
    vIndex = this->writeVertex(vIndex, x1, y1, u1, v1);
    vIndex = this->writeVertex(vIndex, x0, y0, u0, v0);
    vIndex = this->writeVertex(vIndex, x1, y1, u1, v1);
    vIndex = this->writeVertex(vIndex, x0, y1, u0, v1);

    outNumBytes = this->numVertices * sizeof(vertex);
    return this->vertexBuffer;
}

//------------------------------------------------------------------------------
int
OryolApp::writeVertex(int index, float x, float y, float u, float v) {
    this->vertexBuffer[index].x = x;
    this->vertexBuffer[index].y = y;
    this->vertexBuffer[index].u = u;
    this->vertexBuffer[index].v = v;
    return index + 1;
}