//------------------------------------------------------------------------------
//  PNGLoader.cc
//------------------------------------------------------------------------------
#include "lodepng/lodepng.h"
#include "Pre.h"
#include "PNGLoader.h"
#include "IO/IO.h"
#include "Gfx/Gfx.h"
#include "Gfx/private/gfxResourceContainer.h"

namespace Oryol {

//------------------------------------------------------------------------------
PNGLoader::PNGLoader(const TextureSetup& setup_) :
TextureLoaderBase(setup_) {
    // empty
}

//------------------------------------------------------------------------------
PNGLoader::PNGLoader(const TextureSetup& setup_, LoadedFunc loadedFunc_) :
TextureLoaderBase(setup_, loadedFunc_) {
  // empty
}

//------------------------------------------------------------------------------
PNGLoader::~PNGLoader() {
    o_assert_dbg(!this->ioRequest);
}

//------------------------------------------------------------------------------
void
PNGLoader::Cancel() {
    if (this->ioRequest) {
        this->ioRequest->Cancelled = true;
        this->ioRequest = nullptr;
    }
}

//------------------------------------------------------------------------------
Id
PNGLoader::Start() {
    this->resId = Gfx::resource()->prepareAsync(this->setup);
    this->ioRequest = IO::LoadFile(setup.Locator.Location());
    return this->resId;
}

//------------------------------------------------------------------------------
ResourceState::Code
PNGLoader::Continue() {
    o_assert_dbg(this->resId.IsValid());
    o_assert_dbg(this->ioRequest.isValid());
    
    ResourceState::Code result = ResourceState::Pending;
    
    if (this->ioRequest->Handled) {
        if (IOStatus::OK == this->ioRequest->Status) {
            // yeah, IO is done, let lodepng parse the texture data
            // and create the texture resource
            const uint8_t* data = this->ioRequest->Data.Data();
            const int numBytes = this->ioRequest->Data.Size();

            //

            unsigned char* image;
            unsigned width, height;
            unsigned char* png = (unsigned char*) data;
            size_t pngsize = (size_t) numBytes;

            lodepng_decode32(&image, &width, &height, png, pngsize); //this returns error... should handle that

            const int imageNumBytes = width * height * 4;
            //

            TextureSetup texSetup = TextureSetup::FromPixelData2D(width, height, 1, PixelFormat::RGBA8);
            texSetup.Sampler.MinFilter = TextureFilterMode::Nearest;
            texSetup.Sampler.MagFilter = TextureFilterMode::Nearest;
            texSetup.Sampler.WrapU = TextureWrapMode::ClampToEdge;
            texSetup.Sampler.WrapV = TextureWrapMode::ClampToEdge;
            texSetup.ImageData.Sizes[0][0] = imageNumBytes;

            // call the Loaded callback if defined, this
            // gives the app a chance to look at the
            // setup object, and possibly modify it
            if (this->onLoaded) {
                this->onLoaded(texSetup);
            }

            // NOTE: the prepared texture resource might have already been
            // destroyed at this point, if this happens, initAsync will
            // silently fail and return ResourceState::InvalidState
            // (the same for failedAsync)
            result = Gfx::resource()->initAsync(this->resId, texSetup, image, imageNumBytes);
        }
        else {
            // IO had failed
            result = Gfx::resource()->failedAsync(this->resId);
        }
        this->ioRequest = nullptr;
    }
    return result;
}

} // namespace Oryol
