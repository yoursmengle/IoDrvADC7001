/** 
  ******************************************************************************
  * @�ļ�   main.c
  * @����   �޹�
  * @�汾   V1.0.0
  * @����   2017-05-03 
  * @˵��   
  ********  ������Ƽ����Źɷ����޹�˾  www.lierda.com ***********************         
  *
***/
#include "main.h"

/** @addtogroup STM32L4xx_HAL_Examples
  * @{
  */
 
/** @addtogroup Templates
  * @{
  */
void board_init(void);         // �װ��ʼ��


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);

/* Private functions ---------------------------------------------------------*/
/**
  *����:  void board_init(void)
  *���ܣ��װ��ʼ��
  *
  *
***/
void board_init(void)         
{  
  HAL_Init();                   // HAL���ʼ��
  SystemClock_Config();         //ʱ�ӳ�ʼ��
  led_init();                   //LED��ʼ��
  uart_init();                  //���ڳ�ʼ��
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
  
  board_init();   //�װ��ʼ��
  
  set_FirstPowerOn_flag(); //���ó����ϵ��־λ
  
  initNetWork(); //��ʼ��NBIOT����������

  /* Add your application code here
     */

  /* Infinite loop */
  while (1)
  {
     if(period_sensor_timeout_flag==1)//�������ɼ�����ʱ�䵽
     {
        period_sensor_timeout_flag=0;
        updata_sensor();
     }
     if(period_report_timeout_flag==1)//NBIOT�ϴ���������ʱ�䵽
     {
        period_report_timeout_flag=0;
        if(getConnectState()==Conn_on)//������
          report(); 
     }
     if(get_NB_RF_DATA_NUM())//nb���յ�����������
     {
         set_NB_RF_DATA_NUM_down_1();
         receive_udp_data(ACK_EN);
         printf("have %d frame wait to receive\r\n",get_NB_RF_DATA_NUM());
     }
     if(nbiot_cmd_data[NB_SEND_DATA_ACK].revresult == BACK_TIMEOUT) //���շ�����Ӧ��ʱ
     {
           receive_udp_data(ACK_EN);//��ֹNSONMI����©�����NB��������NSONMI��ʾ
         
     }
  }
}

// ϵͳʱ������
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
