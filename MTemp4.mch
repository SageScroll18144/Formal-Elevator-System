/* MTemp4
 
Author: ghpc
Creation date: 19/06/24
*/
MACHINE
    MTemp4
VARIABLES
    fun
INVARIANT
    fun : INT +-> BOOL
INITIALISATION
    fun := {0|->FALSE, 1|->TRUE, 2|->FALSE}
OPERATIONS
    op1 =
    BEGIN
        fun := { xx,yy | xx : INT & yy : ran(fun) & (xx-1) |-> yy : fun }
    END
END 
