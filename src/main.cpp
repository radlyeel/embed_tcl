#include <iostream>
#include <string>
#include <boost/program_options.hpp>
  namespace po = boost::program_options;
#include <tcl/tcl.h>

int main(int argc, char* argv[]) {
    // Set up Tcl interpreter
    Tcl_Interp *interp;
    interp = Tcl_CreateInterp();
    if (!interp) {
        std::cerr << "Failed to create Tcl Interpreter" << std::endl;
        return 1;
    }

    // Hellow, world from Tcl
    if (TCL_OK != Tcl_Eval(interp, "puts \"Hello from Tcl\"")) {
        std::cerr << "Error interpreting script" << std::endl;
        return 2;
    }

    // After all else, clean up Tcl
    Tcl_DeleteInterp(interp);
    return 0;
}
