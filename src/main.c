#include <stdio.h>
#include <string.h>
#include <tcl/tcl.h>

#define MAX_INPUT_LENGTH 1000

int main(int argc, char* argv[]) {
    // Set up Tcl interpreter
    Tcl_Interp *interp;
    interp = Tcl_CreateInterp();
    if (!interp) {
        printf("Failed to create Tcl Interpreter\n");
        return 1;
    }

    // Get script from user
    char scr[MAX_INPUT_LENGTH + 1];
    while (1) {
        printf("Tcl: ");
        fgets(scr, MAX_INPUT_LENGTH, stdin);

        // Get rid of trailing newline; TODO: add trim both ends
        scr[strlen(scr) - 1] = '\0';

        if ((strcmp(scr, "quit") == 0) || (strcmp(scr, "exit") == 0)) {
            break;
        }
        if (TCL_OK != Tcl_Eval(interp, scr)) {
            printf("Error interpreting script\n");
            return 2;
        }
    }


    // After all else, clean up Tcl
    Tcl_DeleteInterp(interp);
    return 0;
}
