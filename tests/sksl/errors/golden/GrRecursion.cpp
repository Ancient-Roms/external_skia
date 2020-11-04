

/**************************************************************************************************
 *** This file was autogenerated from GrRecursion.fp; do not modify.
 **************************************************************************************************/
#include "GrRecursion.h"

#include "src/core/SkUtils.h"
#include "src/gpu/GrTexture.h"
#include "src/gpu/glsl/GrGLSLFragmentProcessor.h"
#include "src/gpu/glsl/GrGLSLFragmentShaderBuilder.h"
#include "src/gpu/glsl/GrGLSLProgramBuilder.h"
#include "src/sksl/SkSLCPP.h"
#include "src/sksl/SkSLUtil.h"
class GrGLSLRecursion : public GrGLSLFragmentProcessor {
public:
    GrGLSLRecursion() {}
    void emitCode(EmitArgs& args) override {
        GrGLSLFPFragmentBuilder* fragBuilder = args.fFragBuilder;
        const GrRecursion& _outer = args.fFp.cast<GrRecursion>();
        (void) _outer;
        SkString factorial_name = fragBuilder->getMangledFunctionName("factorial");
        const GrShaderVar factorial_args[] = { GrShaderVar("x", kInt_GrSLType) };
        const String factorial_impl = String::printf(R"SkSL(return x <= 1 ? 1 : x * %s(x - 1);
)SkSL"
, factorial_name.c_str());
        fragBuilder->emitFunction(kInt_GrSLType, factorial_name.c_str(), {factorial_args, 1}, factorial_impl.c_str());
        fragBuilder->codeAppendf(
R"SkSL(int _0_factorial;
{
    _0_factorial = 7 * %s(6);
}

%s = half4(half(_0_factorial));

)SkSL"
, factorial_name.c_str(), args.fOutputColor);
    }
private:
    void onSetData(const GrGLSLProgramDataManager& pdman, const GrFragmentProcessor& _proc) override {
    }
};
GrGLSLFragmentProcessor* GrRecursion::onCreateGLSLInstance() const {
    return new GrGLSLRecursion();
}
void GrRecursion::onGetGLSLProcessorKey(const GrShaderCaps& caps, GrProcessorKeyBuilder* b) const {
}
bool GrRecursion::onIsEqual(const GrFragmentProcessor& other) const {
    const GrRecursion& that = other.cast<GrRecursion>();
    (void) that;
    return true;
}
bool GrRecursion::usesExplicitReturn() const {
    return false;
}
GrRecursion::GrRecursion(const GrRecursion& src)
: INHERITED(kGrRecursion_ClassID, src.optimizationFlags()) {
        this->cloneAndRegisterAllChildProcessors(src);
}
std::unique_ptr<GrFragmentProcessor> GrRecursion::clone() const {
    return std::make_unique<GrRecursion>(*this);
}
#if GR_TEST_UTILS
SkString GrRecursion::onDumpInfo() const {
    return SkString();
}
#endif
