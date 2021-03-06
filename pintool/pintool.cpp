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

RTN get_inner_rtn(const RTN& rtn, const std::string& name)
{
    if (!RTN_Valid(rtn)) {
        TRACE("passed rtn is not valid");
        return RTN_Invalid();
    }

    RTN_Open(rtn);
    INS ins = RTN_InsHead(rtn);

    if (INS_Valid(ins)) {
        if (!INS_HasFallThrough(ins)) {
            if (INS_IsDirectBranch(ins)) {
                const ADDRINT rip = INS_NextAddress(ins);

                xed_decoded_inst_t* xedd = INS_XedDec(ins);
                const int jmp_displacement = xed_decoded_inst_get_branch_displacement(xedd);

                RTN_Close(rtn);

                return RTN_CreateAt(rip + jmp_displacement, name);
            } else {
                TRACE("first instruction is not direct jmp");
            }
        } else {
            TRACE("first instruction is not uncoditional jmp or call");
        }
    } else {
        TRACE("cannot get first instruction for rtn");
    }

    RTN_Close(rtn);
    return RTN_Invalid();
}

template<typename FuncType>
FuncType set_probe(const IMG& img, const char* funcname, FuncType probe)
{
    FuncType orig_func = nullptr;
    RTN rtn = RTN_FindByName(img, funcname);

    if (RTN_Valid(rtn)) {
        RTN outter_rtn = RTN_Invalid();
        while (RTN_Valid(rtn) && !RTN_IsSafeForProbedReplacement(rtn) && outter_rtn != rtn) {
            TRACE("given rtn cannot be probed, try to find inner rtn");

            outter_rtn = rtn;
            rtn = get_inner_rtn(outter_rtn, funcname);
        }

        if (RTN_Valid(rtn) && RTN_IsSafeForProbedReplacement(rtn)) {
            orig_func = reinterpret_cast<FuncType>(RTN_ReplaceProbed(rtn, reinterpret_cast<AFUNPTR>(probe)));
        } else {
            TRACE("found rtn cannot be replaced and inner rtn cannot be obtained");
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
