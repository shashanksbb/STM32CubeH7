/**
  ******************************************************************************
  * @file    rocket_game_win.c
  * @author  MCD Application Team
  * @brief   game functions
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stddef.h>
#include <string.h>
#include "WM.h"
#include "k_modules_res.h"

/* Genereted bitmaps used for the Game */
extern GUI_CONST_STORAGE GUI_BITMAP bmBackground;
extern GUI_CONST_STORAGE GUI_BITMAP bmCoin1;
extern GUI_CONST_STORAGE GUI_BITMAP bmCoin10;
extern GUI_CONST_STORAGE GUI_BITMAP bmCoin11;
extern GUI_CONST_STORAGE GUI_BITMAP bmCoin12;
extern GUI_CONST_STORAGE GUI_BITMAP bmCoin13;
extern GUI_CONST_STORAGE GUI_BITMAP bmCoin2;
extern GUI_CONST_STORAGE GUI_BITMAP bmCoin3;
extern GUI_CONST_STORAGE GUI_BITMAP bmCoin4;
extern GUI_CONST_STORAGE GUI_BITMAP bmCoin5;
extern GUI_CONST_STORAGE GUI_BITMAP bmCoin6;
extern GUI_CONST_STORAGE GUI_BITMAP bmCoin7;
extern GUI_CONST_STORAGE GUI_BITMAP bmCoin8;
extern GUI_CONST_STORAGE GUI_BITMAP bmCoin9;
extern GUI_CONST_STORAGE GUI_BITMAP bmgame_over;
extern GUI_CONST_STORAGE GUI_BITMAP bmreplay_button;
extern GUI_CONST_STORAGE GUI_BITMAP bmrocket_down1_game_over;
extern GUI_CONST_STORAGE GUI_BITMAP bmrocket_down2_game_over;
extern GUI_CONST_STORAGE GUI_BITMAP bmrocket_down_game_over;
extern GUI_CONST_STORAGE GUI_BITMAP bmscore;
extern GUI_CONST_STORAGE GUI_BITMAP bmscore_shape_game_over;
extern GUI_CONST_STORAGE GUI_BITMAP bmmoon;
extern GUI_CONST_STORAGE GUI_BITMAP bmplanet1;
extern GUI_CONST_STORAGE GUI_BITMAP bmplanet2;
extern GUI_CONST_STORAGE GUI_BITMAP bmplanet3;
extern GUI_CONST_STORAGE GUI_BITMAP bmmountains1;
extern GUI_CONST_STORAGE GUI_BITMAP bmmountains2;
extern GUI_CONST_STORAGE GUI_BITMAP bmsky2;
extern GUI_CONST_STORAGE GUI_BITMAP bmgame_title;
extern GUI_CONST_STORAGE GUI_BITMAP bmplay_button;
extern GUI_CONST_STORAGE GUI_BITMAP bmgoldCoin;
extern GUI_CONST_STORAGE GUI_BITMAP bmscoreShape;

extern const GUI_BITMAP * rocket_game[];

/** @addtogroup GAME_MODULE
  * @{
  */

/** @defgroup GAME
  * @brief game routines
  * @{
  */
    
static WM_HWIN hWinGame;
static void Startup(WM_HWIN hWin, uint16_t xpos, uint16_t ypos);

/* Defines -------------------------------------------------------------------*/
#define COLOR_SKY  0x3B151B

#define ID_ROCKET_GAME_CPU_TIMER  0

#define ID_CPU_TEXT               1

#define ID_BUTTON_MENU            (GUI_ID_USER + 0x1)
#define ID_BUTTON_PLAY            (GUI_ID_USER + 0x2)
#define ID_BUTTON_REPLAY          (GUI_ID_USER + 0x3)
  
/* Private typedef -----------------------------------------------------------*/
K_ModuleItem_Typedef  rocket_game_board =
{
  MODULE_GAME,
  "Rocket Game",
  &hWinGame,
  0,
  0,
  Startup,
  NULL,
};

typedef struct {
  int xPos;                                 /* xSize                        */
  int yPos;                                 /* ySize                        */
  int dx;                                   /* BytesPerLine                 */
  int dy;                                   /* BitsPerPixel                 */
  int NumImages;                            /* Pointer to picture data      */
  GUI_CONST_STORAGE GUI_BITMAP ** apImages; /* Pointer to palette           */
  int Index;                                
} SPRITE;

/* External variables --------------------------------------------------------*/
extern osSemaphoreId osDma2dSemph;
extern int GameIsInuse;

/* Static variables  ---------------------------------------------------------*/
static WM_HWIN  hWinPlayScreen;
static WM_HWIN  hWinGameoverScreen;
static WM_HWIN  hWinRocket;

static int CoinsPickedUp   = 0;
static int AnimateParallax = 1;
static uint32_t ObstacleId = 0;

static GUI_RECT RocketRect = { 0, 0, 0, 0 };
static GUI_TIMER_HANDLE GameTimer      = 0;

static char Scoretmp[100] = "";

/* Private variables ---------------------------------------------------------*/
char tmp[64];

int UpdateOrNot = 0;
int touched = 0;
int Oldtouched = 0;

__IO uint32_t i = 0;

/* Coins bitmap arrays */
GUI_CONST_STORAGE GUI_BITMAP *CoinAnimationImages[] = 
{
  &bmCoin1,
  &bmCoin2,
  &bmCoin3,
  &bmCoin4,
  &bmCoin5,
  &bmCoin6,
  &bmCoin7,
  &bmCoin8,
  &bmCoin9,
  &bmCoin10,
  &bmCoin11,
  &bmCoin12,
  &bmCoin13,
};

GUI_CONST_STORAGE GUI_BITMAP *MoonImages[] = 
{
  &bmmoon,
};

GUI_CONST_STORAGE GUI_BITMAP *Planet1Images[] = 
{
  &bmplanet1,
};

GUI_CONST_STORAGE GUI_BITMAP *Planet2Images[] = 
{
  &bmplanet2,
};

GUI_CONST_STORAGE GUI_BITMAP *Planet3Images[] = 
{
  &bmplanet3,
};

static SPRITE CoinSprite = { 484, 150, -8, -6, GUI_COUNTOF(CoinAnimationImages), CoinAnimationImages, 0 };

/* Moving objects array */
SPRITE ObstaclesArray[] =
{
  { 484, 200, -6, -6, GUI_COUNTOF(MoonImages), MoonImages, 0 },
  { 484, 250, -8, -8, GUI_COUNTOF(Planet1Images), Planet1Images, 0 },
  { 484, 300, -10, -10, GUI_COUNTOF(Planet2Images), Planet2Images, 0 },
  { 484, 350, -12, -12, GUI_COUNTOF(Planet3Images), Planet3Images, 0 },
};

/* Private function prototypes -----------------------------------------------*/
static void ChangeObstacleId(void);
static void OnGameTimer(GUI_TIMER_MESSAGE * pTM);
static void UpdateScore(int score);
static void MoveSpriteDiagonal(SPRITE * pSprite);
       void _DrawPrallax(void);

/**
  * @brief  Paints menu button
  * @param  hObj: button handle
  * @retval None
  */
static void _OnPaint_MenuButton(BUTTON_Handle hObj)
{
  GUI_DrawBitmap(&bmmenu, 10, 10);
}

/**
  * @brief  Paints play button
  * @param  hObj: button handle
  * @retval None
  */
static void _OnPaint_PlayButton(BUTTON_Handle hObj)
{
  if ((WIDGET_GetState(hObj) & BUTTON_STATE_PRESSED))
  {
    GUI_DrawBitmap(&bmplay_button, 0, 0);   

    /* Create the main game timer */
    GameTimer = GUI_TIMER_Create(OnGameTimer, 70, 0, 0);
    GUI_TIMER_SetPeriod(GameTimer, 70);

    /* Start the parallax animation */
    AnimateParallax = 1;
    WM_HideWindow(hWinPlayScreen);
  }
  else
  {
    GUI_DrawBitmap(&bmplay_button, 0, 0);
  }
}

/**
  * @brief  Paints replay button
  * @param  hObj: button handle
  * @retval None
  */
static void _OnPaint_ReplayButton(BUTTON_Handle hObj)
{
  if ((WIDGET_GetState(hObj) & BUTTON_STATE_PRESSED))
  {
    GUI_DrawBitmap(&bmreplay_button, 0, 0);

    /* Create the main game timer */
    GameTimer = GUI_TIMER_Create(OnGameTimer, 70, 0, 0);
    GUI_TIMER_SetPeriod(GameTimer, 70);

    /* Reset the collected coins counter */
    CoinsPickedUp = 0;

    /* Start the parallax animation */
    AnimateParallax = 1;

    /* Hide the gameover window */
    WM_HideWindow(hWinGameoverScreen);

    /* Show the rocket window */
    WM_SetWindowPos(hWinRocket, 264, 192, 100, 63);
    WM_ShowWindow(hWinRocket);
  }
  else
  {
    GUI_DrawBitmap(&bmreplay_button, 0, 0);
  }
}

/**
  * @brief  callback for menu button
  * @param  pMsg: pointer to data structure of type WM_MESSAGE
  * @retval None
  */
static void _cbButton_Menu(WM_MESSAGE * pMsg) 
{
  switch (pMsg->MsgId) 
  {
    case WM_PAINT:
      _OnPaint_MenuButton(pMsg->hWin);
      break;
    default:
      /* The original callback */
      BUTTON_Callback(pMsg);
      break;
  }
}

/**
  * @brief  callback for play button
  * @param  pMsg: pointer to data structure of type WM_MESSAGE
  * @retval None
  */
static void _cbButton_Play(WM_MESSAGE * pMsg) 
{
  switch (pMsg->MsgId) 
  {
    case WM_PAINT:
      _OnPaint_PlayButton(pMsg->hWin);
      break;
    default:
      /* The original callback */
      BUTTON_Callback(pMsg);
      break;
  }
}

/**
  * @brief  callback for replay button
  * @param  pMsg: pointer to data structure of type WM_MESSAGE
  * @retval None
  */
static void _cbButton_Replay(WM_MESSAGE * pMsg) 
{
  switch (pMsg->MsgId) 
  {
    case WM_PAINT:
      _OnPaint_ReplayButton(pMsg->hWin);
      break;
    default:
      /* The original callback */
      BUTTON_Callback(pMsg);
      break;
  }
}

/**
  * @brief  Timer callback used to check collision between the rocket and moving objects
  * @param  pTM: pointer to data structure of type GUI_TIMER_MESSAGE
  * @retval None
  */
static void OnGameTimer(GUI_TIMER_MESSAGE * pTM)
{
  GUI_TIMER_Restart(pTM->hTimer);
  /* Keep timer running */
  WM_InvalidateWindow(hWinGame);
   
  UpdateOrNot = 0;   
  
  /* Compute the rocket collision area */
  GUI_RECT rocketCollisionArea; 
  
  rocketCollisionArea.x0 = RocketRect.x0;
  rocketCollisionArea.y0 = RocketRect.y0 + 0;
  rocketCollisionArea.x1 = RocketRect.x0 + 100 - 5;
  rocketCollisionArea.y1 = RocketRect.y0 + 63 - 5;

  /* Detect collision between the rocket and the coin */
  if (!(CoinSprite.xPos      >= rocketCollisionArea.x1 ||
        CoinSprite.xPos + 28 <= rocketCollisionArea.x0 ||
        CoinSprite.yPos      >= rocketCollisionArea.y1 ||
        CoinSprite.yPos + 26 <= rocketCollisionArea.y0))
  {
    /* Reset the coin position to the right of the screen */
    CoinSprite.xPos = 484;

    /* Increase the player score */
    CoinsPickedUp++;
  } 
  

  /* Detect collision between the rocket and the obstacles */
  if (!(ObstaclesArray[ObstacleId].xPos                                                 >= rocketCollisionArea.x1 ||
        ObstaclesArray[ObstacleId].xPos + ObstaclesArray[ObstacleId].apImages[0]->XSize <= rocketCollisionArea.x0 ||
        ObstaclesArray[ObstacleId].yPos                                                 >= rocketCollisionArea.y1 ||
        ObstaclesArray[ObstacleId].yPos + ObstaclesArray[ObstacleId].apImages[0]->YSize <= rocketCollisionArea.y0))
  {
    if(touched != Oldtouched)
    {
    /* Reset the coin position to the right of the screen */
    CoinSprite.xPos = 484;

    /* Reset the obstacle position to the right of the screen */
    ObstaclesArray[ObstacleId].xPos = 484;

    /* Stop the parallax animation */
    AnimateParallax = 0;

    /* Change the obstacle ID */
    ChangeObstacleId();

    /* Delete the timers */
    if (GameTimer != 0)
    {
      GUI_TIMER_Delete(GameTimer);
      GameTimer = 0;
    }    

    /* Show the gameover window */
    WM_ShowWindow(hWinGameoverScreen);

    /* Hide the rocket window */
    WM_HideWindow(hWinRocket);
    touched     = 0;
    Oldtouched  = 0;
    }
  } 
  else
  {
    /* Update the displayed score */
    UpdateScore(CoinsPickedUp);

    if (ObstaclesArray[ObstacleId].xPos >= 484)
    {
      ChangeObstacleId();
    }
    WM_GetWindowRectEx(hWinRocket, &RocketRect);
    Oldtouched = touched;
  }
}

/**
  * @brief  This function is used to update the displayed score
  * @param  score: The score to display
  * @retval None
  */
static void UpdateScore(int score)
{
  static int currentScore = -1;  
  
  if (currentScore != score)
  {
    sprintf((char *)Scoretmp , "%d", score);

    currentScore = score;
  }
}

/**
  * @brief  This funciton is used to move a sprite on the X and Y axis
  * @param  pSprite: pointer to data structure of type SPRITE
  * @retval None
  */
void MoveSpriteDiagonal(SPRITE * pSprite)
{
  /* Set new index */
  pSprite->Index += 1;
  if (pSprite->Index >= pSprite->NumImages)
  {
    pSprite->Index = 0;
  }

  /* Adjust X-position */
  pSprite->xPos += pSprite->dx;
  if (pSprite->xPos > 484)
  {
    pSprite->xPos = -1L * pSprite->apImages[pSprite->Index]->XSize;
  }
  if (pSprite->xPos < -1L * pSprite->apImages[pSprite->Index]->XSize)
  {
    pSprite->xPos = 484;
  }

  /* Adjust Y-position */
  pSprite->yPos += pSprite->dy;
  if (pSprite->yPos < 0)
  {
    pSprite->dy = -pSprite->dy;
  }
  if (pSprite->yPos > (272 - pSprite->apImages[pSprite->Index]->YSize))
  {
    pSprite->dy = -1 * pSprite->dy;
  }
  GUI_DrawBitmap(pSprite->apImages[pSprite->Index], pSprite->xPos, pSprite->yPos);
}

/**
  * @brief  This function is used to change the moving obstacle
  * @retval None
  */
static void ChangeObstacleId()
{
  ObstacleId++;
  
  if (ObstacleId >= GUI_COUNTOF(ObstaclesArray))
  {
    ObstacleId = 0;
  }  
}

/**
  * @brief  callback for play window
  * @param  pMsg: pointer to data structure of type WM_MESSAGE
  * @retval None
  */
static void _cbWinPlayScreen(WM_MESSAGE * pMsg)
{
  WM_HWIN hItem;

  switch (pMsg->MsgId)
  {
    case WM_CREATE:
      hItem = BUTTON_CreateEx(200, 150, bmplay_button.XSize, bmplay_button.YSize, pMsg->hWin, WM_CF_SHOW, 0, ID_BUTTON_PLAY);
      WM_SetCallback(hItem, _cbButton_Play); 

      break;

    case WM_PAINT:
      GUI_DrawBitmap(&bmgame_title, 180, 0);
      break;

    default:
      WM_DefaultProc(pMsg);
      break;
  }
}

/**
  * @brief  callback for gameover window
  * @param  pMsg: pointer to data structure of type WM_MESSAGE
  * @retval None
  */
static void _cbWinGameoverScreen(WM_MESSAGE * pMsg)
{
  WM_HWIN hItem;
  char tmp[100] = "0\0";

  switch (pMsg->MsgId)
  {
    case WM_CREATE:
      hItem = BUTTON_CreateEx(200, 150, bmreplay_button.XSize, bmreplay_button.YSize, pMsg->hWin, WM_CF_SHOW, 0, ID_BUTTON_REPLAY);
      WM_SetCallback(hItem, _cbButton_Replay); 
      break;

    case WM_PAINT:
      GUI_DrawBitmap(&bmgame_over,              160,          120 - 80);
      GUI_DrawBitmap(&bmrocket_down_game_over,  215,          100 - 80);
      GUI_DrawBitmap(&bmrocket_down1_game_over, 380,          240 - 80);
      GUI_DrawBitmap(&bmrocket_down2_game_over, 70,           190 - 80);
      GUI_DrawBitmap(&bmscore_shape_game_over,  195,          195 - 80);
      GUI_DrawBitmap(&bmscore,                  195 + 8,      200 + 0 - 80);
      GUI_DrawBitmap(&bmgoldCoin,               180 + 8 + 75, 195 + 1 - 80);

      GUI_SetFont(GUI_FONT_13B_1);

      GUI_SetTextMode(GUI_TM_TRANS);

      sprintf((char *)tmp , "%d", CoinsPickedUp);

      GUI_DispStringAt(tmp, 133 + 3 + 80 + 30 , 190 + 8 - 80);

      break;

    default:
      WM_DefaultProc(pMsg);
      break;
  }
}


void _DrawPrallax(void)
{
  static int mountain2_xPos = 0;
  static int mountain1_xPos = 0;
  static int sky1_xPos      = 0;

  if (AnimateParallax == 1)
  {
    /* Moontains 2 */
    mountain1_xPos -= 8;
    if (mountain1_xPos < 0)
    {
      mountain1_xPos += bmmountains2.XSize;
    }
    /* Moontains 1 */
    mountain2_xPos -= 16;
    if (mountain2_xPos < 0)
    {
      mountain2_xPos += bmmountains1.XSize;
    }
    /*  Sky 2 */
    sky1_xPos -= 8;
    if (sky1_xPos < 0)
    {
      sky1_xPos += bmsky2.XSize;
    }
  }
  /* Moontains 2 */
  GUI_DrawBitmap(&bmmountains2, mountain1_xPos                     , 271 - bmmountains2.YSize);
  GUI_DrawBitmap(&bmmountains2, mountain1_xPos - bmmountains2.XSize, 271 - bmmountains2.YSize);
      
  /* Moontains 1 */
  GUI_DrawBitmap(&bmmountains1, mountain2_xPos                     , 271 - bmmountains1.YSize);
  GUI_DrawBitmap(&bmmountains1, mountain2_xPos - bmmountains1.XSize, 271 - bmmountains1.YSize);  
  /* Sky 2 */
  GUI_DrawBitmap(&bmsky2, sky1_xPos               , 0);      
  GUI_DrawBitmap(&bmsky2, sky1_xPos - bmsky2.XSize, 0);
  /* The score is only displayed when the game is running */
  if (AnimateParallax == 1)
  {
    GUI_DrawBitmap(&bmgoldCoin, 5 , 5);
  }
}

/**
  * @brief  callback for parallax window
  * @param  pMsg: pointer to data structure of type WM_MESSAGE
  * @retval None
  */
static void _cbWinParallax(WM_MESSAGE * pMsg)
{
  static WM_HWIN HwinMainMenuButton = 0;

  
  WM_HWIN hItem;

  switch (pMsg->MsgId)
  {
    case WM_CREATE:

      HwinMainMenuButton = BUTTON_CreateEx(440, 5, 35, 30, pMsg->hWin, WM_CF_SHOW | WM_CF_STAYONTOP, 0, ID_BUTTON_MENU);
      WM_SetCallback(HwinMainMenuButton, _cbButton_Menu);

      hItem = TEXT_CreateEx(50, 8, 150, 15, pMsg->hWin, WM_CF_SHOW, TEXT_CF_LEFT, ID_CPU_TEXT, "CPU load: 0%");
      TEXT_SetFont(hItem, GUI_FONT_13B_1);
      TEXT_SetTextColor(hItem, GUI_WHITE);    
      break;

    case WM_PAINT:
      if(UpdateOrNot == 0)
      {
        GUI_DrawBitmap(&bmBackground, 0, 0);
        _DrawPrallax();
        MoveSpriteDiagonal(&CoinSprite);
        MoveSpriteDiagonal(&ObstaclesArray[ObstacleId]);
        UpdateOrNot = 1;
      }
        /* Get CPU usage */
      sprintf((char *)tmp , "CPU load : %d%%", osGetCPUUsage());

      hItem = WM_GetDialogItem(pMsg->hWin, ID_CPU_TEXT);
      TEXT_SetText(hItem, tmp);
      
      GUI_SetFont(GUI_FONT_13B_1);
      GUI_SetTextMode(GUI_TM_TRANS);
      GUI_DispStringAt(Scoretmp, 25, 7);

      break;   

    case WM_NOTIFY_PARENT:
      switch (pMsg->Data.v) 
      {
        case WM_NOTIFICATION_CLICKED:
          if (pMsg->hWinSrc == HwinMainMenuButton)
          {
            /* Reset the coin position to the right of the screen */
            CoinSprite.xPos = 484;

            /* Reset the obstacle position to the right of the screen */
            ObstaclesArray[ObstacleId].xPos = 484;

            /* Stop the parallax animation */
            AnimateParallax = 0;

            /* Reset the collected coins counter */
            CoinsPickedUp = 0;

            /* Delete the timers */
            if (GameTimer != 0)
            {
              GUI_TIMER_Delete(GameTimer);
              GameTimer = 0;
            }

            /* Delete the background window */
            WM_DeleteWindow(hWinGame);
            sprintf((char *)Scoretmp , "%s", "");
          }

          break; 
      }
      
      break;

    case WM_DELETE:

      break;

    default:
      WM_DefaultProc(pMsg);
      break;
  }
}

/**
  * @brief  callback for rocket window
  * @param  pMsg: pointer to data structure of type WM_MESSAGE
  * @retval None
  */
static void _cbWinRocket(WM_MESSAGE * pMsg)
{
  switch (pMsg->MsgId)
  {
    case WM_PAINT:
      GUI_DrawBitmap(rocket_game[i++], 0, 0);
      if (i > 1)
      {
        i = 0;
      }
      break;
    case WM_TOUCH:
      touched++;
      break;
    default:
      WM_DefaultProc(pMsg);
      break;
  }
}

static void Startup(WM_HWIN hWin, uint16_t xpos, uint16_t ypos)
{
  WM_MOTION_Enable(1);
  UpdateOrNot = 0;
  touched     = 0;
  Oldtouched  = 0;

  /* Create the parallax background window */
  hWinGame = WM_CreateWindowAsChild(xpos, ypos, 480, 272, hWin, WM_CF_SHOW, _cbWinParallax, 0);

  /* Create the rocket window */
  hWinRocket = WM_CreateWindowAsChild(200, 120, 100, 61, hWinGame, WM_CF_HASTRANS | WM_CF_SHOW | WM_CF_MOTION_Y | WM_CF_MOTION_X, _cbWinRocket, 0);

  /* Create the play window */
  hWinPlayScreen = WM_CreateWindowAsChild(0, 40, 480, 240, hWinGame, WM_CF_HASTRANS | WM_CF_SHOW, _cbWinPlayScreen, 0);

  /* Create the replay window */
  hWinGameoverScreen = WM_CreateWindowAsChild(0, 30, 480, 240, hWinGame, WM_CF_HASTRANS, _cbWinGameoverScreen, 0);
  
}

/**
  * @}
  */

/**
  * @}
  */
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

