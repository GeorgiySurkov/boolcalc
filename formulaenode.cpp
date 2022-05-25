#include "formulaenode.h"

namespace global {
    mstd::map<unsigned int, bool> Workspace;

    void nextArgumentsSet() {
        for (auto it = Workspace.rbegin(); it != Workspace.rend(); ++it) {
            if (!it->second) {
                it->second = true;
                return;
            } else {
                it->second = false;
            }
        }
    }
}