/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef FPSMCULOADBASE_HPP
#define FPSMCULOADBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

class FpsMcuLoadBase : public touchgfx::Container
{
public:
    FpsMcuLoadBase();
    virtual ~FpsMcuLoadBase() {}
    virtual void initialize();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::TextArea MCU_FPS_text;
    touchgfx::TextAreaWithOneWildcard fps_mps_wildcard;
    touchgfx::TextArea mcuText;
    touchgfx::TextAreaWithOneWildcard mcuWildcard;

    /*
     * Wildcard Buffers
     */
    static const uint16_t FPS_MPS_WILDCARD_SIZE = 12;
    touchgfx::Unicode::UnicodeChar fps_mps_wildcardBuffer[FPS_MPS_WILDCARD_SIZE];
    static const uint16_t MCUWILDCARD_SIZE = 4;
    touchgfx::Unicode::UnicodeChar mcuWildcardBuffer[MCUWILDCARD_SIZE];

private:

};

#endif // FPSMCULOADBASE_HPP
