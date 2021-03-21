#include <iostream>
#include <string>
#include <boost/program_options.hpp>
  namespace po = boost::program_options;
#include <tcl/tcl.h>

/* This version supports this level of dialog.  Not that x is
 * remembered

[daryl@mac-dol-2 build_mb]$./embedtcl
Tcl: puts "Hello from Tcl"
Hello from Tcl
Tcl: puts "again"
again
Tcl: set x "Hello X"
Tcl: puts $x
Hello X
Tcl: quit
[daryl@mac-dol-2 build_mb]$

*/
int main(int argc, char* argv[]) {
    // Set up Tcl interpreter
    Tcl_Interp *interp;
    interp = Tcl_CreateInterp();
    if (!interp) {
        std::cerr << "Failed to create Tcl Interpreter" << std::endl;
        return 1;
    }

    // Get script from user
    std::string scr;
    while (true) {
        std::cout << "Tcl: ";
        std::getline(std::cin, scr);
        if (scr == "quit") {
            break;
        }
        if (TCL_OK != Tcl_Eval(interp, scr.c_str())) {
            std::cerr << "Error interpreting script" << std::endl;
            return 2;
        }
    }


    // After all else, clean up Tcl
    Tcl_DeleteInterp(interp);
    return 0;
}
