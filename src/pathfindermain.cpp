#include "gevents.h"
#include "gwindow.h"
#include "PathfinderGUI.h"
#include "WorldGrid.h"
#include "console.h"

static const std::string WINDOW_TITLE = "Project Pathfinder";
static const bool RANDOM_USE_SEED = false;   // true to get predictable random mazes

/*
 * Prints an introductory text message on the screen.
 */
static void intro();

/*
 * Main program.
 */
int main() {
    if (RANDOM_USE_SEED) {
        setRandomSeed(106);
    }
    
    intro();

    // create GUI window and position the console to its right
    setConsoleLocation(WorldGrid::WINDOW_WIDTH + 6 * WorldAbstract::WINDOW_MARGIN,
                       WorldAbstract::WINDOW_MARGIN);   // temporary
    // setConsoleSize(CONSOLE_WIDTH, CONSOLE_HEIGHT);
    setConsoleEventOnClose(true);
    
    PathfinderGUI gui(WINDOW_TITLE);
    pause(100);
    gui.snapConsoleLocation();

    // main event loop to process events as they happen
    while (true) {
        GEvent e = waitForEvent(ACTION_EVENT | MOUSE_EVENT | WINDOW_EVENT);
        if (e.getEventType() == MOUSE_CLICKED || e.getEventType() == MOUSE_MOVED) {
            gui.processMouseEvent(GMouseEvent(e));
        } else if (e.getEventClass() == ACTION_EVENT) {
            gui.processActionEvent(GActionEvent(e));
        } else if (e.getEventClass() == WINDOW_EVENT) {
            gui.processWindowEvent(GWindowEvent(e));
        }
    }
    return 0;
}

static void intro() {
    std::cout << "Welcome to Project Pathfinder!" << std::endl;
    std::cout << "This program searches for paths through graphs" << std::endl;
    std::cout << "representing mazes using A* search algorithm." << std::endl;
    std::cout << "The mazes can also be generated randomly using" << std::endl;
    std::cout << "Kruskal's algorithm for minimum spanning trees." << std::endl;
}
