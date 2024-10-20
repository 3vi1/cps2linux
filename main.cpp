// cps2linux:  Launch linux equivalent executables.

/* Example arguments passed in to this comman from CBM Prg Studio x86:
 *
 * Emulator:
 *   -c2l_x64 "Z:\home\evil\src\NewProject\newproject.prg"
 *
 * Debugger (when using Vice):
 *   -moncommands "Z:\home\evil\src\NewProject\newproject.dup" -c2l_x64 "Z:\home\evil\src\NewProject\test.bas"
 *
 *     NOTE:  The user parameters specified in the emulator config options are not the first ones passed in by CPS.
 *            The -c2l_* parameter comes from the Emulator Control options, but we don't care about the order and
 *            will end up calling the correct executable
 *
 * Debugger (when using C64Debugger):
 *   -c2l_retrodebugger -prg "Z:\home\evil\src\NewProject\test.bas"
 *   -breakpoints "Z:\home\evil\src\NewProject\C64Debuggerbrk.dbg"
 *   -vicesymbols "Z:\home\evil\src\NewProject\C64DebuggerSmbls.dbg" -wait 2500 -autojmp -layout 10
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string rewritePath(const string& path) {
    string rewrittenPath = path.substr(2);
    replace(rewrittenPath.begin(), rewrittenPath.end(), '\\', '/');
    return rewrittenPath;
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <args>" << endl << endl;
        cout << "       -c2l_* in parameters specifies the real app to call." << endl;
        return 1;
    }

    string executable = "";
    std::vector<string> newArgs = {};

    // Read the input arguments.  Deduce the new executable to call, and rewrite the paths such that they drop the drive letter and replace backslashes with forward slashes.
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];

        // If this is a flag that begins with "-c2l_", use the rest of the string as the executable
        if (arg.find("-c2l_") == 0) {
            executable = arg.substr(5);
            continue;
        }

        // If this looks like a path, rewrite it to Linux format and add it to newArgs
        if (arg.find(":\\") != string::npos) {
            newArgs.push_back(rewritePath(arg));
        } else {
            // Otherwise, just copy the argument as is.
            newArgs.push_back(arg);
        }
    }

    // If we didn't find an executable to call, print an error and exit.
    if (executable == "") {
        cout << "No executable specified." << endl;
        return 1;
    }

    // Call the new executable with the rewritten arguments.
    string command = executable;

    // Add the newArgs to the command string
    for (const string& arg : newArgs) {
        command += " " + arg;
    }

    cout << "Calling: " << command << endl;
    return system(command.c_str());
}
