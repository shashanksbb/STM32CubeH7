/**
  ******************************************************************************
  * @file    JPEG/MJPEG_VideoDecodingFromOSPI/Src/main.c
  * @author  MCD Application Team
  * @brief   This sample code shows how to use the HW JPEG to Decode an MJPEG video file
  *          using the STM32H7xx HAL API.
  ******************************************************************************
    * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
  /* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "decode_dma.h"

/** @addtogroup STM32H7xx_HAL_Examples
  * @{
  */

/** @defroup MJPEG_VideoDecodingFromOSPI
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define AVI_FILE_ADDRESS ((uint32_t)(0x90000000)) /*Address of the MJPEG AVI file located on the OSPI Flash*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
JPEG_HandleTypeDef    JPEG_Handle;
DMA2D_HandleTypeDef    DMA2D_Handle;
static JPEG_ConfTypeDef       JPEG_Info;

uint32_t LCD_X_Size = 0, LCD_Y_Size = 0;
static uint32_t FrameRate;

extern __IO uint32_t Jpeg_HWDecodingEnd;

AVI_CONTEXT AVI_Handel;  /* AVI Parser Handle*/

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void LCD_BriefDisplay(void);
static void LCD_FileErrorDisplay(void);
static void DMA2D_Init(uint16_t xsize, uint16_t ysize, uint32_t ChromaSampling);
static void DMA2D_CopyBuffer(uint32_t *pSrc, uint32_t *pDst, uint16_t ImageWidth, uint16_t ImageHeight);
static void CPU_CACHE_Enable(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  uint32_t isfirstFrame =0 , startTime = 0;
  uint32_t jpegOutDataAdreess = JPEG_OUTPUT_DATA_BUFFER0;
  uint32_t FrameType = 0;
  uint8_t  lcd_status = BSP_ERROR_NONE;
  BSP_OSPI_NOR_Init_t Flash;


  /* Enable the CPU Cache */
  CPU_CACHE_Enable();

   /* STM32H7xx HAL library initialization:
       - Systick timer is configured by default as source of time base, but user
         can eventually implement his proper time base source (a general purpose
         timer for example or other time source), keeping in mind that Time base
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
  HAL_Init();

  /* Configure the system clock to 280 MHz */
  SystemClock_Config();

  /*##-1- Initialize the LEDs , SDRAM and LCD ################################*/
  /*Initialize LED2 and LED3 */
  /* Initialize the LED2 (set to On when Test OK) */
  BSP_LED_Init(LED2);
  /* Initialize the LED3 ( set to On when error) */
  BSP_LED_Init(LED3);


  /*Initialize the OSPI in memory mapped mode*/
  Flash.InterfaceMode = BSP_OSPI_NOR_SPI_MODE;
  Flash.TransferRate  = BSP_OSPI_NOR_STR_TRANSFER;

  BSP_OSPI_NOR_Init(0, &Flash);
  BSP_OSPI_NOR_EnableMemoryMappedMode(0);

  /* Initialize the LCD */
  lcd_status = BSP_LCD_Init(0,LCD_ORIENTATION_LANDSCAPE);
  if(lcd_status != BSP_ERROR_NONE)
  {
    Error_Handler();
  }
  /*link board LCD drivers to BASIC GUI LCD drivers*/
  GUI_SetFuncDriver(&LCD_Driver);

  GUI_Clear(GUI_COLOR_WHITE);
  GUI_SetFont(&Font16);
  /* Get the LCD width and height */
  BSP_LCD_GetXSize(0,&LCD_X_Size);
  BSP_LCD_GetYSize(0,&LCD_Y_Size);

  /*##-2- Initialize the HW JPEG Codec  ######################################*/
  /* Init the HAL JPEG driver */
  JPEG_Handle.Instance = JPEG;
  HAL_JPEG_Init(&JPEG_Handle);

  /*##-3- Initialize the AVI Parser ##########################################*/
  if(AVI_ParserInit(&AVI_Handel, AVI_FILE_ADDRESS) == 0)
  {
    isfirstFrame = 1;
    FrameRate = 0;

    startTime = HAL_GetTick();

    do
    {
      /*##-4- Get a Frame from the AVI file ##################################*/
      FrameType = AVI_GetFrame(&AVI_Handel);

      if(FrameType == AVI_VIDEO_FRAME)
      {
        AVI_Handel.CurrentImage ++;

        /*##-5- Start decoding the current JPEG frame with DMA (Not Blocking ) Method ################*/
        JPEG_Decode_DMA(&JPEG_Handle,(uint32_t) AVI_Handel.pVideoBuffer ,AVI_Handel.FrameSize, jpegOutDataAdreess );


        /*##-6- Wait till end of JPEG decoding ###############################*/
        while(Jpeg_HWDecodingEnd == 0)
        {
        }

        if(isfirstFrame == 1)
        {
          isfirstFrame = 0;
          /*##-7- Get JPEG Info  #############################################*/
          HAL_JPEG_GetInfo(&JPEG_Handle, &JPEG_Info);

          /*##-8- Initialize the DMA2D #######################################*/
          DMA2D_Init(JPEG_Info.ImageWidth, JPEG_Info.ImageHeight, JPEG_Info.ChromaSubsampling);
        }
        /*##-9- Copy the Decoded frame to the display frame buffer using the DMA2D #*/
        DMA2D_CopyBuffer((uint32_t *)jpegOutDataAdreess, (uint32_t *)LCD_FRAME_BUFFER, JPEG_Info.ImageWidth, JPEG_Info.ImageHeight);

        jpegOutDataAdreess = (jpegOutDataAdreess == JPEG_OUTPUT_DATA_BUFFER0) ? JPEG_OUTPUT_DATA_BUFFER1 : JPEG_OUTPUT_DATA_BUFFER0;

#ifdef USE_FRAMERATE_REGULATION
        /* Regulate the frame rate to the video native frame rate by inserting delays */
        FrameRate =  (HAL_GetTick() - startTime) + 1;
        if(FrameRate < ((AVI_Handel.aviInfo.SecPerFrame/1000) * AVI_Handel.CurrentImage))
        {
          HAL_Delay(((AVI_Handel.aviInfo.SecPerFrame /1000) * AVI_Handel.CurrentImage) - FrameRate);
        }
#endif /* USE_FRAMERATE_REGULATION */
      }


    }while(AVI_Handel.CurrentImage  <  AVI_Handel.aviInfo.TotalFrame);

    HAL_DMA2D_PollForTransfer(&DMA2D_Handle, 50);  /* wait for the Last DMA2D transfer to ends */

    if(AVI_Handel.CurrentImage > 0)
    {
      /*##-10- Calc the average decode frame rate #*/
      FrameRate =  (AVI_Handel.CurrentImage * 1000)/(HAL_GetTick() - startTime);
      /* Display decoding info */
      LCD_BriefDisplay();
    }
  }
  else /* Can't Open avi file*/
  {
    LCD_FileErrorDisplay();
  }

  /* Infinite loop */
  while (1)
  {
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  BSP_LED_On(LED3);
  while(1)
  {
  }
}


/**
  * @brief  Init the DMA2D for YCbCr to ARGB8888 Convertion .
  * @param  xsize: Image width
  * @param  ysize: Image Height
  * @param  ChromaSampling: YCbCr CHroma sampling : 4:2:0, 4:2:2 or 4:4:4
  * @retval None
  */
static void DMA2D_Init(uint16_t xsize, uint16_t ysize, uint32_t ChromaSampling)
{
  uint32_t cssMode = JPEG_420_SUBSAMPLING, inputLineOffset = 0;

  if(ChromaSampling == JPEG_420_SUBSAMPLING)
  {
    cssMode = DMA2D_CSS_420;

    inputLineOffset = xsize % 16;
    if(inputLineOffset != 0)
    {
      inputLineOffset = 16 - inputLineOffset;
    }
  }
  else if(ChromaSampling == JPEG_444_SUBSAMPLING)
  {
    cssMode = DMA2D_NO_CSS;

    inputLineOffset = xsize % 8;
    if(inputLineOffset != 0)
    {
      inputLineOffset = 8 - inputLineOffset;
    }
  }
  else if(ChromaSampling == JPEG_422_SUBSAMPLING)
  {
    cssMode = DMA2D_CSS_422;

    inputLineOffset = xsize % 16;
    if(inputLineOffset != 0)
    {
      inputLineOffset = 16 - inputLineOffset;
    }
  }

  /*##-1- Configure the DMA2D Mode, Color Mode and output offset #############*/
  DMA2D_Handle.Init.Mode         = DMA2D_M2M_PFC;
  DMA2D_Handle.Init.ColorMode    = DMA2D_OUTPUT_ARGB8888;
  DMA2D_Handle.Init.OutputOffset = LCD_X_Size - xsize;
  DMA2D_Handle.Init.AlphaInverted = DMA2D_REGULAR_ALPHA;  /* No Output Alpha Inversion*/
  DMA2D_Handle.Init.RedBlueSwap   = DMA2D_RB_REGULAR;     /* No Output Red & Blue swap */

  /*##-2- DMA2D Callbacks Configuration ######################################*/
  DMA2D_Handle.XferCpltCallback  = NULL;

  /*##-3- Foreground Configuration ###########################################*/
  DMA2D_Handle.LayerCfg[1].AlphaMode = DMA2D_REPLACE_ALPHA;
  DMA2D_Handle.LayerCfg[1].InputAlpha = 0xFF;
  DMA2D_Handle.LayerCfg[1].InputColorMode = DMA2D_INPUT_YCBCR;
  DMA2D_Handle.LayerCfg[1].ChromaSubSampling = cssMode;
  DMA2D_Handle.LayerCfg[1].InputOffset = inputLineOffset;
  DMA2D_Handle.LayerCfg[1].RedBlueSwap = DMA2D_RB_REGULAR; /* No ForeGround Red/Blue swap */
  DMA2D_Handle.LayerCfg[1].AlphaInverted = DMA2D_REGULAR_ALPHA; /* No ForeGround Alpha inversion */

  DMA2D_Handle.Instance          = DMA2D;

  /*##-4- DMA2D Initialization     ###########################################*/
  HAL_DMA2D_Init(&DMA2D_Handle);
  HAL_DMA2D_ConfigLayer(&DMA2D_Handle, 1);
}

/**
  * @brief  Copy the Decoded image to the display Frame buffer.
  * @param  pSrc: Pointer to source buffer
  * @param  pDst: Pointer to destination buffer
  * @param  ImageWidth: image width
  * @param  ImageHeight: image Height
  * @retval None
  */
static void DMA2D_CopyBuffer(uint32_t *pSrc, uint32_t *pDst, uint16_t ImageWidth, uint16_t ImageHeight)
{

  uint32_t xPos, yPos, destination,LCD_X_Size,LCD_Y_Size;

  /* Get the LCD width and height */
  BSP_LCD_GetXSize(0,&LCD_X_Size);
  BSP_LCD_GetYSize(0,&LCD_Y_Size);

  /*##-1- calculate the destination transfer address  ############*/
  xPos = (LCD_X_Size - JPEG_Info.ImageWidth)/2;
  yPos = (LCD_Y_Size - JPEG_Info.ImageHeight)/2;

  destination = (uint32_t)pDst + ((yPos * LCD_X_Size) + xPos) * 4;

  HAL_DMA2D_PollForTransfer(&DMA2D_Handle, 25);  /* wait for the previous DMA2D transfer to ends */
  /* copy the new decoded frame to the LCD Frame buffer*/
  HAL_DMA2D_Start(&DMA2D_Handle, (uint32_t)pSrc, destination, ImageWidth, ImageHeight);

}

/**
  * @brief  Display Example description.
  * @param  None
  * @retval None
  */
static void LCD_BriefDisplay(void)
{
  char message[64];

  GUI_SetFont(&Font16);
  GUI_Clear(GUI_COLOR_WHITE);
  GUI_SetBackColor(GUI_COLOR_BLUE);
  GUI_SetTextColor(GUI_COLOR_BLUE);
  GUI_FillRect(0, 0, LCD_X_Size, 112,GUI_COLOR_BLUE);
  GUI_SetTextColor(GUI_COLOR_WHITE);
  GUI_DisplayStringAtLine(1, (uint8_t *)"     MJPEG Video Decoding example");
  GUI_SetFont(&Font12);
  GUI_DisplayStringAtLine(4, (uint8_t *)"       This example shows how to Decode and display");
  GUI_DisplayStringAtLine(5, (uint8_t *)"  an MJPEG video file located on the OSPI external Flash");

  GUI_SetBackColor(GUI_COLOR_WHITE);
  GUI_SetTextColor(GUI_COLOR_BLUE);

  /* JPEG resolution */
  sprintf(message, "Video Resolution            = %lu x %lu", JPEG_Info.ImageWidth, JPEG_Info.ImageHeight);
  GUI_DisplayStringAtLine(10, (uint8_t *)message);

  /* JPEG Quality */
  sprintf(message, "JPEG Quality                =   %lu",JPEG_Info.ImageQuality );
  GUI_DisplayStringAtLine(11, (uint8_t *)message);

  /* JPEG Chroma Sampling */
  if(JPEG_Info.ChromaSubsampling  == JPEG_420_SUBSAMPLING)
  {
    sprintf(message, "ChromaSubsampling           =  4:2:0");
  }
  else if(JPEG_Info.ChromaSubsampling  == JPEG_422_SUBSAMPLING)
  {
    sprintf(message, "ChromaSubsampling           =  4:2:2");
  }
  else if(JPEG_Info.ChromaSubsampling  == JPEG_444_SUBSAMPLING)
  {
    sprintf(message, "ChromaSubsampling           =  4:4:4");
  }

  GUI_DisplayStringAtLine(12, (uint8_t *)message);

  /* Decoding approximative decoding Frame rate */
  sprintf(message, "Average Decoding Frame Rate =   %lu fps", FrameRate);
  GUI_DisplayStringAtLine(13, (uint8_t *)message);

  /* Number of decoded frames */
  sprintf(message, "Number of Frames            =   %lu", AVI_Handel.aviInfo.TotalFrame);
  GUI_DisplayStringAtLine(14, (uint8_t *)message);

}

/**
  * @brief  Display File access error message.
  * @param  None
  * @retval None
  */
static void LCD_FileErrorDisplay(void)
{
  GUI_SetBackColor(GUI_COLOR_WHITE);
  GUI_SetTextColor(GUI_COLOR_WHITE);
  GUI_SetTextColor(GUI_COLOR_RED);
  GUI_SetFont(&Font12);
  GUI_DisplayStringAtLine(26, (uint8_t *)"Unable to open AVI MJPEG video file");
  GUI_DisplayStringAtLine(27, (uint8_t *)"Check that an MJPEG avi is Flashed to the OSPI @0x90000000");

  Error_Handler();
}


/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 280000000 (CPU Clock)
  *            HCLK(Hz)                       = 280000000 (Bus matrix and AHBs Clock)
  *            AHB Prescaler                  = 1
  *            CD APB3 Prescaler              = 2 (APB3 Clock  140MHz)
  *            CD APB1 Prescaler              = 2 (APB1 Clock  140MHz)
  *            CD APB2 Prescaler              = 2 (APB2 Clock  140MHz)
  *            SRD APB4 Prescaler             = 2 (APB4 Clock  140MHz)
  *            HSE Frequency(Hz)              = 24000000
  *            PLL_M                          = 12
  *            PLL_N                          = 280
  *            PLL_P                          = 2
  *            PLL_Q                          = 2
  *            PLL_R                          = 2
  *            VDD(V)                         = 3.3
  *            Flash Latency(WS)              = 6
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;

  /*!< Supply configuration update enable */
  HAL_PWREx_ConfigSupply(PWR_DIRECT_SMPS_SUPPLY);

  /* The voltage scaling allows optimizing the power consumption when the device is
  clocked below the maximum system frequency, to update the voltage scaling value
  regarding system frequency refer to product datasheet.
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
  RCC_OscInitStruct.CSIState = RCC_CSI_OFF;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;

  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 280;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;

  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_1;
  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
  while(1) {};
  }

  /* Select PLL as system clock source and configure  bus clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_D1PCLK1 | RCC_CLOCKTYPE_PCLK1 | \
    RCC_CLOCKTYPE_PCLK2  | RCC_CLOCKTYPE_D3PCLK1);

  RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider  = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider  = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;
  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6);
  if(ret != HAL_OK)
  {
  while(1) {};
  }
}


/**
  * @brief  CPU L1-Cache enable.
  * @param  None
  * @retval None
  */
static void CPU_CACHE_Enable(void)
{
  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}



#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
