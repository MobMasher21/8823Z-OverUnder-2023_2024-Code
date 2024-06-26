using namespace vex;

extern brain Brain;

// VEXcode devices
extern distance triballSensor;
extern digital_out ArmDown;
extern digital_out ArmUp;
extern inertial Inertial;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );