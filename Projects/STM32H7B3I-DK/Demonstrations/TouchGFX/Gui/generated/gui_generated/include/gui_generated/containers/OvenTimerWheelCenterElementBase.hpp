/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef OVENTIMERWHEELCENTERELEMENTBASE_HPP
#define OVENTIMERWHEELCENTERELEMENTBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>

class OvenTimerWheelCenterElementBase : public touchgfx::Container
{
public:
    OvenTimerWheelCenterElementBase();
    virtual ~OvenTimerWheelCenterElementBase() {}
    virtual void initialize();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

private:

};

#endif // OVENTIMERWHEELCENTERELEMENTBASE_HPP
