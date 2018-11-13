#include "globals.h"
#include "thrusterSubsystem.h"
#include <assert.h>
void testThrusterSubsystem();
int main(int argc, char** argv) {
    testThrusterSubsystem();
    return 1;
}
void testThrusterSubsystem(){
    initialize();
    *(thrusterData.thrustCommandPtr) = 65535;
    struct localVars test1 = thrusterSubsystemFunction(&thrusterData);
    assert(test1.left == 1);
    assert(test1.right == 1);
    assert(test1.up == 1);
    assert(test1.down == 1);
    assert(test1.magnitude == 15);
    assert(test1.duration == 255);

    *(thrusterData.thrustCommandPtr) = 43717;
    struct localVars test2 = thrusterSubsystemFunction(&thrusterData);
    assert(test2.left == 1);
    assert(test2.right == 0);
    assert(test2.up == 1);
    assert(test2.down == 0);
    assert(test2.magnitude == 12);
    assert(test2.duration == 170);

*(thrusterData.thrustCommandPtr) = 0;
    struct localVars test2 = thrusterSubsystemFunction(&thrusterData);
    assert(test2.left == 0);
    assert(test2.right == 0);
    assert(test2.up == 0);
    assert(test2.down == 0);
    assert(test2.magnitude == 0);
    assert(test2.duration == 0);
}
