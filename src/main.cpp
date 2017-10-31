#include "ElephantLogger.h"

// Just for test
int main(int argc, char** argv) {
    LOG_ERROR("TEST ERROR");
    LOG_WARNING("TEST WARNING");
    LOG_CONFIG("TEST CONFIG");
    LOG_INFO("TEST INFO");
    LOG_TRACE("TEST TRACE");
    LOG_DEBUG("TEST DEBUG");
    return 0;
}
