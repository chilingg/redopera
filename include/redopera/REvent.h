#ifndef REVENT_H
#define REVENT_H

#include "RInputModule.h"
#include <assert.h>

namespace Redopera {

class RController;

// 事件通知类集合 ********************

// 循环开始事件
class RStartEvent
{
public:
    explicit RStartEvent(RController *sender):
        sender(sender) {}
    RController *sender;
};

// 循环结束事件
class RFinishEvent
{
public:
    explicit RFinishEvent(RController *sender):
        sender(sender) {}
    RController *sender;
};

// 申请关闭事件
class RCloseEvent
{
public:
    explicit RCloseEvent(RController *sender):
        sender(sender) {}
    RController *sender;
    bool stop = false; // true驳回关闭申请
};

class RInputEvent
{
public:
    RInputEvent(RController *sender):
        sender(sender) {}

    ButtonAction status(Keys key) {
        return RInputModule::instance().keyInputs_[key].action;
    }
    ButtonAction status(MouseButtons btn) {
        return RInputModule::instance().mouseInputs_[btn].action;
    }
    ButtonAction status(GamepadBtn btn, unsigned p = 0) {
        if(RInputModule::instance().gamepadInputs_.empty()) return ButtonAction::RELEASE;

        RInputModule::instance().gamepadInputs_[p].status.buttons[static_cast<unsigned>(btn)] = 2;
        return RInputModule::toButtonAction(1);
    }
    float status(GamepadAxes axis, unsigned p = 0) {
        if(RInputModule::instance().gamepadInputs_.empty())
        {
            if(axis == GamepadAxes::GAMEPAD_AXIS_LEFT_TRIGGER || axis == GamepadAxes::GAMEPAD_AXIS_RIGHT_TRIGGER)
                return -1.f;
            else
                return 0.f;
        }

        return RInputModule::instance().gamepadInputs_[p].status.axes[static_cast<unsigned>(axis)];
    }

    bool press(Keys key) {
        return RInputModule::instance().keyInputs_[key].action == ButtonAction::PRESS
                && RInputModule::instance().keyInputs_[key].action
                != RInputModule::instance().keyInputs_[key].preAction;
    }
    bool press(MouseButtons btn) {
        return RInputModule::instance().mouseInputs_[btn].action == ButtonAction::PRESS
                && RInputModule::instance().mouseInputs_[btn].action
                != RInputModule::instance().mouseInputs_[btn].preAction;
    }
    bool press(GamepadBtn btn, unsigned p = 0) {
        if(RInputModule::instance().gamepadInputs_.empty()) return false;

        unsigned index = static_cast<unsigned>(btn);
        return RInputModule::instance().gamepadInputs_[p].status.buttons[index]
                == static_cast<unsigned char>(ButtonAction::PRESS)
                && RInputModule::instance().gamepadInputs_[p].status.buttons[index]
                != RInputModule::instance().gamepadInputs_[p].preButtons[index];
    }

    bool release(Keys key) {
        return RInputModule::instance().keyInputs_[key].action == ButtonAction::RELEASE
                && RInputModule::instance().keyInputs_[key].action
                != RInputModule::instance().keyInputs_[key].preAction;
    }
    bool release(MouseButtons btn) {
        return RInputModule::instance().mouseInputs_[btn].action == ButtonAction::RELEASE
                && RInputModule::instance().mouseInputs_[btn].action
                != RInputModule::instance().mouseInputs_[btn].preAction;
    }
    bool release(GamepadBtn btn, unsigned p = 0) {
        if(RInputModule::instance().gamepadInputs_.empty()) return false;

        unsigned index = static_cast<unsigned>(btn);
        return RInputModule::instance().gamepadInputs_[p].status.buttons[index]
                == static_cast<unsigned char>(ButtonAction::RELEASE)
                && RInputModule::instance().gamepadInputs_[p].status.buttons[index]
                != RInputModule::instance().gamepadInputs_[p].preButtons[index];
    }

    RPoint2 pos() { return RInputModule::instance().cursorPos_[0]; }
    RPoint2 prePos() { return RInputModule::instance().cursorPos_[1]; }

    RController *sender;
    void *userData;
};

} // Redopera

#endif // REVENT_H
