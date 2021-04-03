// Step One: just copy what's in the book
#include <stdlib.h>   // For random()
#include <tcl/tcl.h>
/*
 * Declarations for application-specific command procedures
 */

int RandomCmd(ClientData clientData,
             Tcl_Interp *interp,
             int argc, CONST char *argv[]);
int RandomObjCmd(ClientData clientData,
             Tcl_Interp *interp,
             int objc, Tcl_Obj *CONST objv[]);

/*
 * Random_Init is called when the package is loaded.
 */

int Random_Init(Tcl_Interp *interp) {
   /*
    * Initialize the stub table interface, which is
    * described in Chapter 48.
    */

   if (Tcl_InitStubs(interp, "8.1", 0) == NULL) {
      return TCL_ERROR;
   }
   /*
    * Register two variations of random.
    * The orandom command uses the object interface.
    */

   Tcl_CreateCommand(interp, "random", RandomCmd,
         (ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);
   Tcl_CreateObjCommand(interp, "orandom", RandomObjCmd,
         (ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);

   /*
    * Declare that we implement the random package
    * so scripts that do "package require random"
    * can load the library automatically.
    */
   Tcl_PkgProvide(interp, "random", "1.1");
   return TCL_OK;
}

/*
 * RandomCmd --
 * This implements the random Tcl command. With no arguments
 * the command returns a random integer.
 * With an integer valued argument "range",
 * it returns a random integer between 0 and range.
 */
int
RandomCmd(ClientData clientData, Tcl_Interp *interp,
      int argc, CONST char *argv[])
{
   int rand, error;
   int range = 0;
   char buf[20];
   if (argc > 2) {
      interp->result = "Usage: random ?range?";
      return TCL_ERROR;
   }
   if (argc == 2) {
      if (Tcl_GetInt(interp, argv[1], &range) != TCL_OK) {
         return TCL_ERROR;
      }
   }
   rand = random();
   if (range != 0) {
      rand = rand % range;
   }
   sprintf(buf, "%d", rand);
   Tcl_SetResult(interp, buf, TCL_VOLATILE);
   return TCL_OK;
}

/*
 * RandomObjCmd --
 * This implements the random Tcl command from
 * Example 47–2 using the object interface.
 */
int
RandomObjCmd(ClientData clientData, Tcl_Interp *interp,
      int objc, Tcl_Obj *CONST objv[])
{
   Tcl_Obj *resultPtr;
   int rand, error;
   int range = 0;
   if (objc > 2) {
      Tcl_WrongNumArgs(interp, 1, objv, "?range?");
      return TCL_ERROR;
   }
   if (objc == 2) {
      if (Tcl_GetIntFromObj(interp, objv[1], &range) !=
            TCL_OK) {
         return TCL_ERROR;
      }
   }
   rand = random();
   if (range != 0) {
      rand = rand % range;
   }
   resultPtr = Tcl_GetObjResult(interp);
   Tcl_SetIntObj(resultPtr, rand);
   return TCL_OK;
}

