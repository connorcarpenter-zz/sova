#pragma once
//------------------------------------------------------------------------------
/**
    @class Oryol::PNGLoader
    @ingroup Assets
    @brief standard texture loader for most block-compressed texture file formats
*/
#include "Gfx/TextureLoaderBase.h"
#include "IO/private/ioRequests.h"

namespace Oryol {

class PNGLoader : public TextureLoaderBase {
    OryolClassDecl(PNGLoader);
public:
    /// constructor without success-callback
    PNGLoader(const TextureSetup& setup);
    /// constructor with success callback
    PNGLoader(const TextureSetup& setup, LoadedFunc onLoaded);
    /// destructor
    ~PNGLoader();
    /// start loading, return a resource id
    virtual Id Start() override;
    /// continue loading, return resource state (Pending, Valid, Failed)
    virtual ResourceState::Code Continue() override;
    /// cancel the load process
    virtual void Cancel() override;

private:
    Id resId;
    Ptr<IORead> ioRequest;
};

} // namespace Oryol