/**
  ******************************************************************************
  * @file    USB_Host/MSC_Standalone/Src/menu.c
  * @author  MCD Application Team
  * @brief   This file implements Menu Functions
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------ */
#include "main.h"

/* Private typedef ----------------------------------------------------------- */
/* Private define ------------------------------------------------------------ */
/* Private macro ------------------------------------------------------------- */
/* Private variables --------------------------------------------------------- */
MSC_DEMO_StateMachine msc_demo;
uint32_t JoyState = JOY_NONE;
uint8_t prev_select = 0;
uint8_t joy_select = 0;
uint8_t *MSC_main_menu[] = {
  (uint8_t *)
    "      1 - File Operations                                                   ",
  (uint8_t *)
    "      2 - Explorer Disk                                                     ",
  (uint8_t *)
    "      3 - Re-Enumerate                                                      ",
};

/* Private function prototypes ----------------------------------------------- */
static void MSC_SelectItem(uint8_t ** menu, uint8_t item);
static void MSC_DEMO_ProbeKey(uint32_t state);

/* Private functions --------------------------------------------------------- */

/**
* @brief  Demo state machine.
* @param  None
* @retval None
*/
void Menu_Init(void)
{
  GUI_SetTextColor(GUI_COLOR_GREEN);
  GUI_DisplayStringAtLine(17,
                              (uint8_t *)
                              "Use [Joystick Left/Right] to scroll up/down");
  GUI_DisplayStringAtLine(18,
                              (uint8_t *)
                              "Use [Joystick Up/Down] to scroll MSC menu");
  msc_demo.state = MSC_DEMO_IDLE;
  MSC_SelectItem(MSC_main_menu, 0);
}

/**
* @brief  Manages MSC Menu Process.
* @param  None
* @retval None
*/
void MSC_MenuProcess(void)
{
  switch (msc_demo.state)
  {
  case MSC_DEMO_IDLE:
    MSC_SelectItem(MSC_main_menu, 0);
    msc_demo.state = MSC_DEMO_WAIT;
    msc_demo.select = 0;
    break;

  case MSC_DEMO_WAIT:
    if (msc_demo.select != prev_select)
    {
      prev_select = msc_demo.select;
      MSC_SelectItem(MSC_main_menu, msc_demo.select & 0x7F);

      /* Handle select item */
      if (msc_demo.select & 0x80)
      {
        switch (msc_demo.select & 0x7F)
        {
        case 0:
          msc_demo.state = MSC_DEMO_FILE_OPERATIONS;
          break;

        case 1:
          msc_demo.state = MSC_DEMO_EXPLORER;
          break;

        case 2:
          msc_demo.state = MSC_REENUMERATE;
          break;

        default:
          break;
        }
      }
    }
    break;

  case MSC_DEMO_FILE_OPERATIONS:
    /* Read and Write File Here */
    if (Appli_state == APPLICATION_READY)
    {
      MSC_File_Operations();
    }
    msc_demo.state = MSC_DEMO_WAIT;
    break;

  case MSC_DEMO_EXPLORER:
    /* Display disk content */
    if (Appli_state == APPLICATION_READY)
    {
      Explore_Disk("0:/", 1);
    LCD_UsrTrace("> Select an operation to Continue.\n");
    }
    msc_demo.state = MSC_DEMO_WAIT;
    break;

  case MSC_REENUMERATE:
    /* Force MSC Device to re-enumerate */
    USBH_ReEnumerate(&hUSBHost);
    msc_demo.state = MSC_DEMO_WAIT;
    break;

  default:
    break;
  }
  msc_demo.select &= 0x7F;

  if (joy_select == 1)
  {
    MSC_DEMO_ProbeKey(JoyState);

    switch (JoyState)
    {
    case JOY_LEFT:
      UTIL_LCD_TRACE_ScrollBack();
      break;

    case JOY_RIGHT:
      UTIL_LCD_TRACE_ScrollForward();
      break;

    default:
      break;
    }
    joy_select = 0;
  }
}

/**
* @brief  Manages the menu on the screen.
* @param  menu: Menu table
* @param  item: Selected item to be highlighted
* @retval None
*/
static void MSC_SelectItem(uint8_t ** menu, uint8_t item)
{
  GUI_SetTextColor(GUI_COLOR_WHITE);

  switch (item)
  {
  case 0:
    GUI_SetBackColor(GUI_COLOR_MAGENTA);
    GUI_DisplayStringAtLine(19, menu[0]);
    GUI_SetBackColor(GUI_COLOR_BLUE);
    GUI_DisplayStringAtLine(20, menu[1]);
    GUI_DisplayStringAtLine(21, menu[2]);
    break;

  case 1:
    GUI_SetBackColor(GUI_COLOR_BLUE);
    GUI_DisplayStringAtLine(19, menu[0]);
    GUI_SetBackColor(GUI_COLOR_MAGENTA);
    GUI_DisplayStringAtLine(20, menu[1]);
    GUI_SetBackColor(GUI_COLOR_BLUE);
    GUI_DisplayStringAtLine(21, menu[2]);
    break;

  case 2:
    GUI_SetBackColor(GUI_COLOR_BLUE);
    GUI_DisplayStringAtLine(19, menu[0]);
    GUI_SetBackColor(GUI_COLOR_BLUE);
    GUI_DisplayStringAtLine(20, menu[1]);
    GUI_SetBackColor(GUI_COLOR_MAGENTA);
    GUI_DisplayStringAtLine(21, menu[2]);
    break;
  }
  GUI_SetBackColor(GUI_COLOR_BLACK);
}

/**
* @brief  Probes the MSC joystick state.
* @param  state: Joystick state
* @retval None
*/
static void MSC_DEMO_ProbeKey(uint32_t state)
{
  /* Handle Menu inputs */
  if ((state == JOY_UP) && (msc_demo.select > 0))
  {
    msc_demo.select--;
  }
  else if ((state == JOY_DOWN) && (msc_demo.select < 2))
  {
    msc_demo.select++;
  }
  else if (state == JOY_SEL)
  {
    msc_demo.select |= 0x80;
  }
}

/**
* @brief  EXTI line detection callbacks.
* @param  GPIO_Pin: Specifies the pins connected EXTI line
* @retval None
*/
void BSP_JOY_Callback(JOY_TypeDef JOY, JOYPin_TypeDef JoyPin)
{
    JoyState = BSP_JOY_GetState(JOY1);

    joy_select = 1;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
