/** 
  ******************************************************************************
  * @文件   main.c
  * @作者   罗桂发
  * @版本   V1.0.0
  * @日期   2017-05-03 
  * @说明   
  ********  利尔达科技集团股份有限公司  www.lierda.com ***********************         
  *
***/
#include "main.h"

/** @addtogroup STM32L4xx_HAL_Examples
  * @{
  */
 
/** @addtogroup Templates
  * @{
  */
void board_init(void);         // 底板初始化


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);

/* Private functions ---------------------------------------------------------*/
/**
  *函数:  void board_init(void)
  *功能：底板初始化
  *
  *
***/
void board_init(void)         
{  
  HAL_Init();                   // HAL库初始化
  SystemClock_Config();         //时钟初始化
  led_init();                   //LED初始化
  uart_init();                  //串口初始化
  printf(" LIERDA NBxx_01 Sample Code\r\n");
  printf("LIERDA SCIENCE & TECHNOLOGY GROUP CO.,LTD\r\n");
  GPS_init();
  uart_timer_init();
  sensor_init();  
  battery_init();
}
/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{ 
  
  board_init();   //底板初始化
  
  set_FirstPowerOn_flag(); //设置初次上电标志位
  
  initNetWork(); //初始化NBIOT，连接网络

  /* Add your application code here
     */

  /* Infinite loop */
  while (1)
  {
     if(period_sensor_timeout_flag==1)//传感器采集周期时间到
     {
        period_sensor_timeout_flag=0;
        updata_sensor();
     }
     if(period_report_timeout_flag==1)//NBIOT上传数据周期时间到
     {
        period_report_timeout_flag=0;
        if(getConnectState()==Conn_on)//已连接
          report(); 
     }
     if(get_NB_RF_DATA_NUM())//nb接收到服务器数据
     {
         set_NB_RF_DATA_NUM_down_1();
         receive_udp_data(ACK_EN);
         printf("have %d frame wait to receive\r\n",get_NB_RF_DATA_NUM());
     }
     if(nbiot_cmd_data[NB_SEND_DATA_ACK].revresult == BACK_TIMEOUT) //接收服务器应答超时
     {
           receive_udp_data(ACK_EN);//防止NSONMI命令漏掉造成NB后续不发NSONMI提示
         
     }
  }
}

// 系统时钟配置
// System Clock source            = PLL (MSI)
// SYSCLK(Hz)                     = 80000000
// HCLK(Hz)                       = 80000000
// AHB Prescaler                  = 1
// APB1 Prescaler                 = 1
// APB2 Prescaler                 = 1
// MSI Frequency(Hz)              = 4000000
// PLL_M                          = 1
// PLL_N                          = 40
// PLL_R                          = 2
// PLL_P                          = 7
// PLL_Q                          = 4
// Flash Latency(WS)              = 4
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLP = 7;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    
    while(1);
  }
  
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    while(1);
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
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
