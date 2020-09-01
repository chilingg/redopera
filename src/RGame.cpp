#include <RGame.h>
#include <RWindow.h>
#include <RController.h>
#include <REvent.h>
#include <ROpenGL.h>
#include <RInputModule.h>
#include <rsc/RResource.h>
#include <RDebug.h>

#include <sstream>
#include <fstream>
#include <stdexcept>
#include <string>

using namespace Redopera;

bool RGame::once = false;
RWindow *RGame::mainWindow;

std::string RResource::rscPath_;

void glfwErrorCallback(int error, const char* description)
{
    prError("GLFW Error " + std::to_string(error) + ": " + description);
}

RGame::RGame()
{
    if (once)
        throw std::runtime_error("RGame is a singleton!");
    else
        once = true;

    // glfw错误回调
    glfwSetErrorCallback(glfwErrorCallback);

    if (glfwInit() == GLFW_TRUE)
        std::runtime_error("Failed to initialize GLFW");

}

RGame::~RGame()
{
    once = false;
    glfwTerminate();
}

int RGame::exec(RWindow *window)
{
    mainWindow = window;
    window->setAsMainWindow();

    // 需手动检测一次手柄连接，检测之前已连接的手柄
    for(int i = GLFW_JOYSTICK_1; i <= GLFW_JOYSTICK_LAST; ++i)
    {
        if(glfwJoystickIsGamepad(i))
        {
            RInputModule::addGamepad(RInputModule::toJoystickID(i));
            mainWindow->joyPresented.emit(RInputModule::toJoystickID(i), JoystickPresent::CONNECTED);
        }
    }
    // 手柄连接回调
    glfwSetJoystickCallback(joystickPresentCallback);

    return mainWindow->ctrl()->exec();
}

void RGame::joystickPresentCallback(int jid, int event)
{
    if(event == GLFW_CONNECTED && glfwJoystickIsGamepad(jid))
    {
        RInputModule::addGamepad(RInputModule::toJoystickID(jid));
        mainWindow->joyPresented.emit(RInputModule::toJoystickID(jid), JoystickPresent::CONNECTED);
    }
    else if(event == GLFW_DISCONNECTED)
    {
        RInputModule::deleteGamepad(RInputModule::toJoystickID(jid));
        mainWindow->joyPresented.emit(RInputModule::toJoystickID(jid), JoystickPresent::DISCONNECTED);
    }
}

bool RGame::updateGamepadMappings(const char *path)
{
    std::string p = path;
    RResource::rscPath(p);

    std::string code;
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(p);
        //读取文件缓冲到数据流
        std::stringstream sstream;
        sstream << file.rdbuf();

        file.close();
        code = sstream.str();
    }
    catch(...)
    {
        code.clear();
    }

    if(glfwUpdateGamepadMappings(code.c_str()) == GLFW_FALSE)
    {
        prError("Failed to update gamepad mapping! In path: " + p + '\n' +
                   "To https://github.com/gabomdq/SDL_GameControllerDB download gamecontrollerdb.txt file.");
        rDebug << "Updata to default gameoad maooings is " << (updateGamepadMappings() ? "success." : "failed!");
        return false;
    } else
        return true;
}

bool RGame::updateGamepadMappings()
{
    // 加载手柄映射
    std::string mappingCode = std::string() + RInputModule::gamepadMappingCode0
            + RInputModule::gamepadMappingCode1 + RInputModule::gamepadMappingCode2;

    return glfwUpdateGamepadMappings(mappingCode.c_str()) == GLFW_TRUE;
}