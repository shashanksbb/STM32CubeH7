/**
  ******************************************************************************
  * This file is part of the TouchGFX 4.12.0 distribution.
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

#ifndef UIEVENTLISTENER_HPP
#define UIEVENTLISTENER_HPP

#include <touchgfx/hal/Types.hpp>

namespace touchgfx
{
class ClickEvent;
class DragEvent;
class GestureEvent;

/**
 * @class UIEventListener UIEventListener.hpp touchgfx/UIEventListener.hpp
 *
 * @brief This class declares a handler interface for user interface events.
 *
 *        This class declares a handler interface for user interface events, i.e. events
 *        generated by the users interaction with the device. With the exception of the system
 *        timer tick, all other system events, which are not related to the user interface
 *        device peripherals (display, keys etc.) are not part of this interface.
 */
class UIEventListener
{
public:

    /**
     * @fn virtual void UIEventListener::handleClickEvent(const ClickEvent& event)
     *
     * @brief This handler is invoked when a mouse click or display touch event has been detected
     *        by the system.
     *
     *        This handler is invoked when a mouse click or display touch event has been
     *        detected by the system.
     *
     * @param event The event data.
     */
    virtual void handleClickEvent(const ClickEvent& event)
    {
    }

    /**
     * @fn virtual void UIEventListener::handleDragEvent(const DragEvent& event)
     *
     * @brief This handler is invoked when a drag event has been detected by the system.
     *
     *        This handler is invoked when a drag event has been detected by the system.
     *
     * @param event The event data.
     */
    virtual void handleDragEvent(const DragEvent& event)
    {
    }

    /**
     * @fn virtual void UIEventListener::handleGestureEvent(const GestureEvent& event)
     *
     * @brief This handler is invoked when a gesture event has been detected by the system.
     *
     *        This handler is invoked when a gesture event has been detected by the system.
     *
     * @param event The event data.
     */
    virtual void handleGestureEvent(const GestureEvent& event)
    {
    }

    /**
     * @fn virtual void UIEventListener::handleKeyEvent(uint8_t c)
     *
     * @brief This handler is invoked when a key (or button) event has been detected by the system.
     *
     *        This handler is invoked when a key (or button) event has been detected by the
     *        system.
     *
     * @param c The key or button pressed.
     */
    virtual void handleKeyEvent(uint8_t c)
    {
    }

    /**
     * @fn virtual void UIEventListener::handleTickEvent()
     *
     * @brief This handler is invoked when a system tick event has been generated.
     *
     *        This handler is invoked when a system tick event has been generated. The system
     *        tick period is configured in the HAL.
     */
    virtual void handleTickEvent()
    {
    }

    /**
     * @fn virtual void UIEventListener::handlePendingScreenTransition()
     *
     * @brief This handler is invoked when a change screen event is pending.
     *
     *        This handler is invoked when a change screen event is pending.
     */
    virtual void handlePendingScreenTransition()
    {
    }

    /**
     * @fn virtual UIEventListener::~UIEventListener()
     *
     * @brief Destructor.
     *
     *        Destructor.
     */
    virtual ~UIEventListener()
    {
    }
};
} // namespace touchgfx

#endif // UIEVENTLISTENER_HPP
