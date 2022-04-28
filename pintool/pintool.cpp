#include <cstdlib>

#include "pin.H"

#include "log.h"
#include "path.h"
#include "time.h"


namespace pintool
{
using viete_formula_probe_fn = double (*)(unsigned);
viete_formula_probe_fn viete_formula_orig;

const char* viete_formula_func_name = "viete_formula";

double viete_formula_probe(unsigned iter_num)
{
    time::timer t;
    const double ret = viete_formula_orig(iter_num);
    const time::timer::ticks_type elapsed_time = t.elapsed();

    TRACE("wall time of " << viete_formula_func_name << " is " << elapsed_time << " us,"
          << " number of iterations is " << iter_num);

    return ret;
}

template<typename FuncType>
FuncType set_probe(const IMG& img, const char* funcname, FuncType probe)
{
    FuncType orig_func = nullptr;
    RTN rtn = RTN_FindByName(img, funcname);

    if (RTN_Valid(rtn)) {
        if (RTN_IsSafeForProbedReplacement(rtn)) {
            orig_func = reinterpret_cast<FuncType>(RTN_ReplaceProbed(rtn, reinterpret_cast<AFUNPTR>(probe)));
        } else {
            TRACE("found rtn cannot be replaced");
        }
    } else {
        TRACE("function " << funcname << " is not found");
    }

    return orig_func;
}

VOID image_load(IMG img, VOID* v)
{
    const std::string& filename = path::filename(img);

    if (filename == "pi.dll") {
        viete_formula_orig = set_probe(img, viete_formula_func_name, viete_formula_probe);
    }
}

} // namespace pintool

int main(int argc, char* argv[])
{
    if (PIN_Init(argc, argv)) {
        ERROR("cannot initialize Pin");
        return EXIT_FAILURE;
    }

    PIN_InitSymbols();
    IMG_AddInstrumentFunction(pintool::image_load, 0);

    PIN_StartProgramProbed();
    return EXIT_SUCCESS;
}
