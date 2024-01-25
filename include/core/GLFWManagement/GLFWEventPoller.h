#ifndef GLFW_EVENT_POLLER_H
#define GLFW_EVENT_POLLER_H

// Class: GLFWEventPoller
// Description: Polls for pending events in the GLFW event queue
class GLFWEventPoller {
public:
    // Function: pollEvents
    // Description: Polls for pending events in the GLFW event queue
    static void pollEvents();
};

#endif // GLFW_EVENT_POLLER_H