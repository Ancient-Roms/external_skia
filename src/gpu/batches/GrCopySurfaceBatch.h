/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrCopySurfaceBatch_DEFINED
#define GrCopySurfaceBatch_DEFINED

#include "GrBatch.h"
#include "GrBatchFlushState.h"
#include "GrGpu.h"
#include "GrRenderTarget.h"

class GrCopySurfaceBatch final : public GrBatch {
public:
    static GrBatch* Create(GrSurface* dst, GrSurface* src, const SkIRect& srcRect,
                           const SkIPoint& dstPoint);

    const char* name() const override { return "CopySurface"; }

    uint32_t renderTargetUniqueID() const override {
        GrRenderTarget* rt = fDst.get()->asRenderTarget();
        return rt ? rt->getUniqueID() : 0;
    }

    SkString dumpInfo() const override {
        SkString string;
        string.printf("SRC: 0x%p, DST: 0x%p, SRECT: [L: %d, T: %d, R: %d, B: %d], "
                      "DPT:[X: %d, Y: %d]",
                      fDst.get(), fSrc.get(), fSrcRect.fLeft, fSrcRect.fTop, fSrcRect.fRight,
                      fSrcRect.fBottom, fDstPoint.fX, fDstPoint.fY);
        return string;
    }

private:
    GrCopySurfaceBatch(GrSurface* dst, GrSurface* src, const SkIRect& srcRect,
                       const SkIPoint& dstPoint)
        : fDst(dst)
        , fSrc(src)
        , fSrcRect(srcRect)
        , fDstPoint(dstPoint) {
        this->initClassID<GrCopySurfaceBatch>();        
        fBounds = SkRect::MakeXYWH(SkIntToScalar(dstPoint.fX), SkIntToScalar(dstPoint.fY),
                                   SkIntToScalar(srcRect.width()), SkIntToScalar(srcRect.height()));
    }

    bool onCombineIfPossible(GrBatch* that, const GrCaps& caps) override { return false; }

    void onPrepare(GrBatchFlushState*) override {}

    void onDraw(GrBatchFlushState* state) override {
        state->gpu()->copySurface(fDst.get(), fSrc.get(), fSrcRect, fDstPoint);
    }

    GrPendingIOResource<GrSurface, kWrite_GrIOType> fDst;
    GrPendingIOResource<GrSurface, kRead_GrIOType>  fSrc;
    SkIRect                                         fSrcRect;
    SkIPoint                                        fDstPoint;
};

#endif
