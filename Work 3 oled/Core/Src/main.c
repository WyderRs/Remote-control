/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "fonts.h"
#include "ST7735.h"
#include "GFX_FUNCTIONS.h"
//#include "string.h"
#include "sd.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
//--------------------------------------------------
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
 ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi3;

TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim9;
TIM_HandleTypeDef htim10;
TIM_HandleTypeDef htim11;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM9_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI3_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM10_Init(void);
static void MX_TIM11_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
_Bool disk_init = true;

_Bool flag_Menu = true;
_Bool flag_Result = false;
_Bool flag_Grafic = false;
_Bool flag_Status = false;
_Bool flag_Setings = false;

int8_t flag_punkt = 1;

_Bool flag_1 = false;
_Bool flag_2 = false;
_Bool flag_3 = false;
_Bool flag_4 = false;

volatile uint16_t data[3];
float u[3];

uint8_t PWM_4 = 0;

float NUM = 0;
float NUM2 = 0;
float x = 255;

float temp[100];
float press[100];
float alt[100];
float gyro_x[100];
float accX[100];
float accY[100];
float accZ[100];

int num[100];


_Bool flag_ServoOff = false;
_Bool flag_but = false;
_Bool flag_but2 = false;
_Bool SIGNAL = false;

_Bool GraficOne = true;
_Bool ResultOne = true;
_Bool StatusOne = true;
_Bool SetingsOne = true;
_Bool flag_PIN_SET = true;
_Bool flag_PIN_CS = true;
_Bool flag_PWM_BLK = false;

int xt = 0;
int yt = 0;
int xt0 ;
int yt0 ;
int st = 15;
int st_2;
int servoData = 0;
int Batdata = 0;
int dis = 0;
int resive_OK = 1;
volatile uint16_t Timer1 = 0;




typedef struct
{
float temperature;
float pressure;
float altitude;
float gyroX;
float accX;
float accY;
float accZ;
} Str;
static Str transmit;

uint8_t PWM_BLINK = 0;
uint8_t sost;
uint8_t pers;

////////////////////

uint16_t i;
uint8_t sect[512];// Буффер для чтения блока

// Write
FRESULT res; //результат выполнения
uint8_t wtext[]="1111 \nHello";

FILINFO fileInfo;
char *fn;
DIR dir;
DWORD fre_clust, fre_sect, tot_sect;

extern char str1[60];
uint32_t byteswritten, bytesread;
uint8_t result;
extern char USERPath[4]; /* logical drive path */
FATFS SDFatFs;
FATFS *fs;
FIL MyFile; //FIL
////////////////////

uint8_t b;

//void TIM9_UP_IRQHandler(void)
//{
//
//}


uint16_t charger[] =
{

		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xe101, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x6101, 0xe405, 0x8607, 0x8304, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x2101, 0xc405, 0x4507, 0xa506, 0x8506, 0x4607, 0xa101, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0xe303, 0xe607, 0xc506, 0x8506, 0x8506, 0x8506, 0x8506, 0x0507, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0102, 0xe506, 0xe506, 0x8506, 0x8506, 0x8506, 0xc506, 0x8405, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0xe303, 0x4607, 0x8506, 0x8506, 0x0507, 0x6000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x6000, 0xe506, 0x8506, 0xa506, 0x4506, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x6000, 0xa607, 0xc506, 0x8506, 0x8506, 0xc506, 0x6506, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0405, 0x4607, 0xa506, 0x8506, 0xc506, 0xa506, 0x2000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x6101, 0x8506, 0xa506, 0xc506, 0x2304, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2000, 0xc506, 0xa506, 0x2506, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xe303, 0x6607, 0xc506, 0xe506, 0xa304, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x6405, 0x4507, 0x6607, 0x4102, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xc101, 0xe506, 0xc607, 0x4000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0304, 0x4607, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xa000, 0x2203

};



uint16_t Strel[] =		// СТРЕЛКА - УКАЗАТЕЛЬ
{
		  0x0000, 0x0000, 0x0000, 0x1d05, 0x0000, 0x0000, 0x0000,
		  0x0000, 0x0000, 0x0000, 0x1d05, 0x1d05, 0x0000, 0x0000,
		  0x1d05, 0x1d05, 0x1d05, 0x1d05, 0x1d05, 0x0000, 0x0000,
		  0x1d05, 0x0000, 0x0000, 0x0000, 0x0000, 0x1d05, 0x0000,
		  0x1d05, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1d05,
		  0x1d05, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1d05,
		  0x1d05, 0x0000, 0x0000, 0x0000, 0x0000, 0x1d05, 0x0000,
		  0x1d05, 0x1d05, 0x1d05, 0x1d05, 0x1d05, 0x0000, 0x0000,
		  0x0000, 0x0000, 0x0000, 0x1d05, 0x1d05, 0x0000, 0x0000,
		  0x0000, 0x0000, 0x0000, 0x1d05, 0x0000, 0x0000, 0x0000
};


void indicator(_Bool a)
	{
		if(flag_punkt == 1)
		{
			ST7735_DrawImage(3, 16, 7, 10, Strel); // движение указателя
			ST7735_FillRectangle(3, 28, 7, 10, BLACK);
			ST7735_FillRectangle(3, 40, 7, 10, BLACK);
			ST7735_FillRectangle(3, 52, 7, 10, BLACK);
		}
		if(flag_punkt == 2)
		{
			ST7735_FillRectangle(3, 16, 7, 10, BLACK);
			ST7735_DrawImage(3, 28, 7, 10, Strel);
			ST7735_FillRectangle(3, 40, 7, 10, BLACK);
			ST7735_FillRectangle(3, 52, 7, 10, BLACK);
		}
		if(flag_punkt == 3)
		{
			ST7735_FillRectangle(3, 16, 7, 10, BLACK);
			ST7735_FillRectangle(3, 28, 7, 10, BLACK);
			ST7735_DrawImage(3, 40, 7, 10, Strel);
			ST7735_FillRectangle(3, 52, 7, 10, BLACK);
		}
		if(flag_punkt == 4)
		{
			ST7735_FillRectangle(3, 16, 7, 10, BLACK);
			ST7735_FillRectangle(3, 28, 7, 10, BLACK);
			ST7735_FillRectangle(3, 40, 7, 10, BLACK);
			ST7735_DrawImage(3, 52, 7, 10, Strel);
		}
	}



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM9_Init();
  MX_SPI1_Init();
  MX_FATFS_Init();
  MX_SPI3_Init();
  MX_USART1_UART_Init();
  MX_TIM4_Init();
  MX_TIM10_Init();
  MX_TIM11_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim9);
  HAL_TIM_Base_Start_IT(&htim4);
  HAL_TIM_Base_Start_IT(&htim10);

  //////////////////////////////////////////////////////////////////////////////
  /*
  disk_initialize(SDFatFs.drv);
  //write

  if(f_mount(&SDFatFs, (TCHAR const*)USERPath, 0) != FR_OK)
  {
	  //Error_Handler();	// комментируем хендлеры чтобы при включении и одновременном отустствии карты дисплей не зависал
  }
  else
  {
	  if(f_open(&MyFile, "mywrite.txt", FA_OPEN_ALWAYS|FA_WRITE) != FR_OK) // FA_OPEN_ALWAYS|FA_WRITE
	  {
		  //Error_Handler();	// комментируем хендлеры чтобы при включении и одновременном отустствии карты дисплей не зависал
	  }
	  else
	  {
		  // res = f_write(&MyFile, &wtext, sizeof(wtext), (void*)&byteswritten);
		  // wtext[]="1111 \nHello";
		  char buff[] = "123";
		  //for(int i = 0; i <= 4; i ++)
		  //{
		  //res = f_write(&MyFile, buff, sizeof(buff), (void*)&byteswritten);//wtext
		  b = f_size(&MyFile);
		  res = f_lseek(&MyFile, b);
		  //res = f_write(&MyFile, buff, sizeof(buff), (void*)&byteswritten);//wtext
		  res = f_write(&MyFile, "Temperature ", 12, (void*)&byteswritten);//wtext
		  b = f_size(&MyFile);
		  res = f_lseek(&MyFile, b);
		  res = f_write(&MyFile, "Pressure ", 9, (void*)&byteswritten);//wtext
		  b = f_size(&MyFile);
		  res = f_lseek(&MyFile, b);
		  res = f_write(&MyFile, "Altitude ", 9, (void*)&byteswritten);//wtext
		  b = f_size(&MyFile);
		  res = f_lseek(&MyFile, b);
		  res = f_lseek(&MyFile, 1020);
		  res = f_write(&MyFile, "3245 ", 4, (void*)&byteswritten);//wtext
		  if((byteswritten == 0) || (res != FR_OK))
		  {
			  Error_Handler();
		  }
		  f_close(&MyFile);
		  //f_sync(&MyFile);
	  }
  }
  FATFS_UnLinkDriver(USERPath);
  */
  //////////////////////////////////////////////////	////////////////////////////


  ST7735_Init(0);


  HAL_TIM_PWM_Start_IT(&htim9, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start_IT(&htim9, TIM_CHANNEL_2);

  HAL_TIM_PWM_Start_IT(&htim11, TIM_CHANNEL_1);
  TIM11->CCR1 = 65535;
  sost = TIM11->CCR1;
  pers = 100;

  //HAL_ADC_Start_IT(&hadc1); //отключил потому что не нужен так как не используем прерывания
  HAL_ADC_Start_DMA(&hadc1, (uint32_t*) &data, 3);

  HAL_UART_Receive_IT(&huart1, (uint8_t*) &transmit, sizeof(transmit));
  TIM9->CCR1 = 0;
  TIM9->CCR2 = 0;

  ST7735_SetRotation(3);
  fillScreen(BLACK);

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET); // Включаем радиомодуль SV610
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);	// Ставим радиомодуль SV610 сразу в режим работы

  HAL_Delay(500);
  //////////////////////////////////////////////////////////////////////////////
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  char BUF[2];
	  sprintf(BUF, "%d", resive_OK);
	  ST7735_WriteString(140, 90, BUF, Font_7x10, RED, BLACK);
	  if(resive_OK < 10) fillRect(147, 90, 7, 10, BLACK);
	  //////////////////////////////////////////////////////////////////////////////
	  if (resive_OK == 99) resive_OK = 0;
	  temp[resive_OK] = transmit.temperature;
	  press[resive_OK] = ((transmit.pressure / 1000)*100)/100;
	  alt[resive_OK] = transmit.altitude;
	  gyro_x[resive_OK] = transmit.gyroX;//
	  accX[resive_OK] = transmit.accX;
	  accY[resive_OK] = transmit.accY;
	  accZ[resive_OK] = transmit.accZ;
	  num[resive_OK] = resive_OK;
	  //////////////////////////////////////////////////////////////////////////////
	  ////////////////////Функция записи данных на флешку////////////////////////////////
	  if((HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_SET)) flag_but2 = 1;
	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_RESET)
	  {
		  if(disk_init == false) ST7735_WriteString(2, 110, "No SD-Card...        ", Font_7x10, RED, BLACK);
		  else if(disk_init == true)
		  {
			  disk_initialize(SDFatFs.drv);
			  disk_init = false;

			  if(f_mount(&SDFatFs, (TCHAR const*)USERPath, 0) != FR_OK)
			  {
				  //Error_Handler();	// комментируем хендлеры чтобы при включении и одновременном отустствии карты дисплей не зависал
			  }
			  else
			  {
				  if(f_open(&MyFile, "result.txt", FA_CREATE_ALWAYS|FA_WRITE) != FR_OK) // FA_OPEN_ALWAYS|FA_WRITE
				  {
					  //Error_Handler();	// комментируем хендлеры чтобы при включении и одновременном отустствии карты дисплей не зависал
				  }
				  else
				  {
					  res = f_write(&MyFile, " #       Temp            Press           Alt             Gyro          Acc_x           Acc_y           Acc_z\r\n", 112, (void*)&byteswritten);//146
					  b = f_size(&MyFile);
					  ST7735_WriteString(2, 110, "Recording begin...  ", Font_7x10, GREEN, BLACK);
					  for(int i = 0; i < resive_OK; i++)
					  {
						  char DaTa[163];
						  sprintf(DaTa, "№%d\t Temp: %.2f\t Press: %.2f\t Alt: %.2f\t Gyro: %.2f\t Acc_x: %.2f\t Acc_y: %.2f\t Acc_z: %.2f", num[i], temp[i], press[i], alt[i], gyro_x[i], accX[i], accY[i], accZ[i]);
						  res = f_write(&MyFile, DaTa, 98, (void*)&byteswritten);
						  b = f_size(&MyFile);

						  char dat[4] = "\r\n";
						  res = f_write(&MyFile, dat, 4, (void*)&byteswritten);
						  b = f_size(&MyFile);
					  }
					  if((byteswritten == 0) || (res != FR_OK))
					  {
						  Error_Handler();
					  }
					  char Num_Resive[20];
					  sprintf(Num_Resive, " Full data byte:%d",resive_OK);
					  res = f_write(&MyFile, Num_Resive, 18, (void*)&byteswritten);

					  f_close(&MyFile);
					  FATFS_UnLinkDriver(USERPath);
					  ST7735_WriteString(2, 110, "Recording completed.", Font_7x10, RED, BLACK);
					  resive_OK = 0;
				  }
			  }
		  }
			  flag_but = 1;
		  }
	  else flag_but = 0;
	  if(flag_but == 1 && flag_but2 == 1)
	  {
		  flag_but2 = 0;
	  }
	  //////////////////////////////////////////////////////////////////////////////
	  //////////////////////////////////////////////////////////////////////////////
	  HAL_TIM_PWM_Start_IT(&htim9, TIM_CHANNEL_1);
	  HAL_TIM_PWM_Start_IT(&htim9, TIM_CHANNEL_2);

	  HAL_ADC_Start_IT(&hadc1);

	  HAL_UART_Receive_IT(&huart1, (uint8_t*) &transmit, sizeof(transmit));

	  //////////////////////////////////////////////////////////////////////////////
	  if(flag_Menu == true)//---------------------------------------------MENU
	  {
		  drawRect(0, 0, 160, 128, WHITE);	// оконтовка
		  ST7735_WriteString(2, 2, "Menu", Font_7x10, GREEN, BLACK);
		  //////////////////////////////////////////////////////////////////////////////
		  ///////// Вывод заряда аккумулятора
		  drawRect(140, 1, 18, 9, WHITE); // заряд аккумулятора
		  // замеряет заряд на аккумулятора на 4.2 вольта в пределе от 2.5 до 3.3, так как на 2.5 STM ОТРУБАЕТСЯ

		  /////////// Зарядка//////////////
		  if((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15) == GPIO_PIN_SET))
		  {
			  ST7735_DrawImage(141, 11, 15, 16, charger);
		  }
		  else fillRect(141, 11, 15, 16, BLACK);

		  if(Batdata <= 128 && Batdata >= 110)
		  {
			  fillRect(141, 2, 16, 7, GREEN);
		  }
		  else if(Batdata <= 109 && Batdata >= 101)
		  {
			  fillRect(141, 2, 16, 7, YELLOW);
		  }
		  else if(Batdata <= 100 && Batdata >= 90)
		  {
			  fillRect(141, 2, 16, 7, RED);
		  }
		  //////////////////////////////////////////////////////////////////////////////
		  indicator(flag_punkt);
		  //////////////////////////////////////////////////////////////////////////////
		  ST7735_WriteString(10, 16, ":Result", Font_7x10, BLUE, BLACK);
		  if(flag_punkt == 1)//-----------------Result
		  {
			  flag_1 = true;
			  flag_2 = false;
			  flag_3 = false;
			  flag_4 = false;
			 // ResultOne = true;
		  }
		  ST7735_WriteString(10, 28, ":Grafic", Font_7x10, RED, BLACK);
		  if(flag_punkt == 2) //----------------Grafic
		  {
			  flag_1 = false;
			  flag_2 = true;
			  flag_3 = false;
			  flag_4 = false;
			  GraficOne = true;
		  }
		  ST7735_WriteString(10, 40, ":Status", Font_7x10, GREEN, BLACK);
		  if(flag_punkt == 3)//-----------------STATUS
		  {
			  flag_1 = false;
			  flag_2 = false;
			  flag_3 = true;
			  flag_4 = false;
		  }
		  ST7735_WriteString(10, 52, ":Setings", Font_7x10, BLUE, BLACK);
		  if(flag_punkt == 4)//-----------------------SETINGS
		  {
			  flag_1 = false;
			  flag_2 = false;
			  flag_3 = false;
			  flag_4 = true;
		  }
		  //////////////////////////////////////////////////////////////////////////////

		  // вывод значений с АЦП джойстика и заряда аккумулятора
		  char buf20[4];
		  sprintf(buf20, "%.2f", u[0]);
		  //ST7735_WriteString(2, 20, buf20, Font_7x10, GREEN, BLACK);

		  char buf10[4];
		  sprintf(buf10, "%.2f", u[1]);
		  //ST7735_WriteString(2, 40, buf10, Font_7x10, GREEN, BLACK);

		  char buf30[4];
		  u[2] = ((float)data[2])*3.3/256;
		  sprintf(buf30, "%.2f", u[2]);
		  //ST7735_WriteString(80, 40, buf30, Font_7x10, GREEN, BLACK);	//заряд акума

		  char buf31[4];
		  sprintf(buf31, "%.2f", Batdata);
		  //ST7735_WriteString(80, 50, buf31, Font_7x10, GREEN, BLACK);
		  ///////////////////////////////////////////////////////////////////////
		  if((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_SET)) flag_but2 = 1;
		  if((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET))
		  {
			  flag_but = 1;
		  }
		  else flag_but = 0;
		  if(flag_but == 1 && flag_but2 == 1)
		  {
			  flag_but2 = 0;

			  flag_Menu = false;
			  if(flag_1 == true)
			  {
				  flag_Result = true;
			  }
			  if(flag_2 == true)
			  {
				  flag_Grafic = true;
			  }
			  if(flag_3 == true)
			  {
				  flag_Status = true;
			  }
			  if(flag_4 == true)
			  {
				  flag_Setings = true;
			  }
			  fillScreen(BLACK);
		  }


	  }
	  //////////////////////////////////////////////////////////////////////////////
	  if(flag_Result == true && flag_1  == true) //--------------------------------------------RESULT
	  {
		  HAL_UART_Receive_IT(&huart1, (uint8_t*) &transmit, sizeof(transmit));
		  /*
		  if(ResultOne == true)	//функция которая выполняется один раз
		  {
			  ResultOne = false;
			  drawLine(159, 63, 1, 63, YELLOW);
			  xt = 0;
		  }
		  */
		  drawRect(0, 0, 160, 128, WHITE);

		  ST7735_WriteString(2, 2, "Result", Font_7x10, GREEN, BLACK);
		  //////////////////////////////////////////////////////////////////////////////
		  //температура, давление, высота над уровнем моря
		  char buf1[4];
		  sprintf(buf1, "Temperature:%.2fC", transmit.temperature); // игнорировать!
		  ST7735_WriteString(2, 20, buf1, Font_7x10, GREEN, BLACK);

		  char buf2[4];
		  sprintf(buf2, "Pressure:   %.2fkPa", transmit.pressure / 1000); // игнорировать!
		  ST7735_WriteString(2, 30, buf2, Font_7x10, GREEN, BLACK);

		  char buf3[4];
		  sprintf(buf3, "Altitude:   %.2fm", transmit.altitude); // игнорировать!
		  ST7735_WriteString(2, 40, buf3, Font_7x10, GREEN, BLACK);


		  //Г�?РОСКОП X
		  char buf41[4];
		  sprintf(buf41, "Gyro_x: %.2f", transmit.gyroX); // игнорировать!
		  ST7735_WriteString(2, 60, buf41, Font_7x10, BLUE, BLACK);
		  //Г�?РОСКОП Y
		  char buf42[4];
		  //sprintf(buf42, "Gyro_y: %.2f", transmit.gyroY); // игнорировать!
		  //ST7735_WriteString(2, 70, buf42, Font_7x10, BLUE, BLACK);
		  //Г�?РОСКОП Z
		  char buf43[4];
		  //sprintf(buf43, "Gyro_z: %.2f", transmit.gyroZ); // игнорировать!
		  //ST7735_WriteString(2, 80, buf43, Font_7x10, BLUE, BLACK);

		  //УСКОРЕН�?Е X
		  char buf5[4];
		  sprintf(buf5, "Acc_x:%.2f", transmit.accX); // игнорировать!
		  ST7735_WriteString(2, 90, buf5, Font_7x10, MAGENTA, BLACK);
		  //УСКОРЕН�?Е Y
		  char buf6[4];
		  sprintf(buf6, "Acc_y:%.2f", transmit.accY); // игнорировать!
		  ST7735_WriteString(2, 100, buf6, Font_7x10, MAGENTA, BLACK);
		  //УСКОРЕН�?Е Z
		  char buf7[4];
		  sprintf(buf7, "Acc_z:%.2f", transmit.accZ); // игнорировать!
		  ST7735_WriteString(2, 110, buf7, Font_7x10, MAGENTA, BLACK);

		  //////////////////////////////////////////////////////////////////////////////
		  if((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_SET)) flag_but2 = 1;
		  if((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET))
		  {
			  flag_but = 1;
		  }
		  else flag_but = 0;
		  if(flag_but == 1 && flag_but2 == 1)
		  {
			  flag_but2 = 0;

			  flag_Result = false;
			  flag_1  = false;
			  flag_Menu = true;
			  fillScreen(BLACK);
		  }
		  //////////////////////////////////////////////////////////////////////////////
	  }

	  //////////////////////////////////////////////////////////////////////////////
	  if(flag_Grafic == true && flag_2  == true) //--------------------------------------------GRAFIC
	  {
		  if(GraficOne == true)
		  {
			  GraficOne = false;
			  drawLine(159, 63, 1, 63, YELLOW);
			  xt = 0;
		  }
		  drawRect(0, 0, 160, 128, WHITE);
		  ST7735_WriteString(2, 2, "Grafic", Font_7x10, GREEN, BLACK);
		  if(xt == 158)	// Обновление экрана при максимальной длине графика
		  {
			  xt = 0;
			  ST7735_FillRectangle(1, 1, 158, 126, BLACK);
			  drawLine(159, 63, 1, 63, YELLOW);
			  drawRect(0, 0, 160, 128, WHITE);
			  ST7735_WriteString(2, 2, "Grafic", Font_7x10, GREEN, BLACK);
		  }
		  xt++;
		  yt = 63 - (transmit.altitude)/2;
		  drawPixel(xt, yt, WHITE);


		  if((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_SET)) flag_but2 = 1;
		  if((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET))
		  {
			  flag_but = 1;
		  }
		  else flag_but = 0;
		  if(flag_but == 1 && flag_but2 == 1)
		  {
			  flag_but2 = 0;

			  flag_Grafic = false;
			  flag_2  = false;
			  flag_Menu = true;
			  fillScreen(BLACK);
		  }
	  }
	  //////////////////////////////////////////////////////////////////////////////
	  if(flag_Status == true && flag_3  == true) //--------------------------------------------STATUS
	  {
		  if(StatusOne == true)
		  {
			  StatusOne = false;
			  xt = 0;
		  }
		  drawRect(0, 0, 160, 128, WHITE);
		  ST7735_WriteString(2, 2, "Status", Font_7x10, GREEN, BLACK);

		  if(Batdata >= 5) ST7735_WriteString (2, 20, "Power: connected", Font_7x10, GREEN, BLACK);
          else if (Batdata < 5) ST7735_WriteString (2, 20, "Power: disabled ", Font_7x10, RED, BLACK);

		  if(Batdata <= 128 && Batdata >= 110) ST7735_WriteString (2, 30, "Battery: HIGH  ", Font_7x10, GREEN, BLACK);
		  else if(Batdata <= 109 && Batdata >= 101) ST7735_WriteString (2, 30, "Battery: MEDIUM", Font_7x10, YELLOW, BLACK);
		  else if(Batdata <= 100 && Batdata >= 90) ST7735_WriteString (2, 30, "Battery: LOW   ", Font_7x10, RED, BLACK);


		  if(flag_PIN_SET == true) ST7735_WriteString(2, 40, "RF: work", Font_7x10, GREEN, BLACK);
		  else if(flag_PIN_SET == false) ST7735_WriteString(2, 40, "RF: customization", Font_7x10, BLUE, BLACK);

		  if(flag_PIN_CS == true)ST7735_WriteString(2, 50, "RF: ON ", Font_7x10, GREEN, BLACK);
		  else if (flag_PIN_CS == false) ST7735_WriteString(2, 50, "RF: OFF", Font_7x10, RED, BLACK);
		  /*
		   * СЮДА БЫ ЕЩЕ ДОБАВ�?ТЬ ФУНЦ�?Ю ПРОВЕРК�? СОСТОЯН�?Я РАД�?ОМОДУЛЯ, РАБОЧУЮ ЧАСТОТУ, КАЧЕСТВО СВЯЗ�?
		   * ТАКЖЕ ДОБАВ�?ТЬ ФУНКЦ�?Ю ПРОВЕРК�? ПР�?Н�?МАЕМЫХ �? ОТПРАВЛЯЕМЫХ ДАННЫХ
		   * ЕЩЕ ЧТО Н�?БУДЬ МОЖНО ДОБАВ�?ТЬ, ФАНТАЗ�?Я РЕШ�?Т ЧТО ДОБАВ�?ТЬ...
		   */


		  if((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_SET)) flag_but2 = 1;
		  if((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET))
		  {
			  flag_but = 1;
		  }
		  else flag_but = 0;
		  if(flag_but == 1 && flag_but2 == 1)
		  {
			  flag_but2 = 0;

			  flag_Status = false;
			  flag_3  = false;
			  flag_Menu = true;
			  fillScreen(BLACK);
		  }
	  }
	  //////////////////////////////////////////////////////////////////////////////
	  if(flag_Setings == true && flag_4  == true) //--------------------------------------------SETINGS
	  {
		  if(SetingsOne == true)
		  {
			  SetingsOne = false;
			  xt = 0;
		  }

		  drawRect(0, 0, 160, 128, WHITE);
		  ST7735_WriteString(2, 2, "Setings", Font_7x10, GREEN, BLACK);
		  //////////////////////////////////////////////////////////////////////////////
		  if(flag_PWM_BLK == false) indicator(flag_punkt);
		  //////////////////////////////////////////////////////////////////////////////


		  ST7735_WriteString(10, 52, ":Back <-", Font_7x10, GREEN, BLACK);

		  if(flag_PIN_SET == true)ST7735_WriteString(10, 16, ":RF work         ", Font_7x10, GREEN, BLACK);
		  else if (flag_PIN_SET == false) ST7735_WriteString(10, 16, ":RF customization", Font_7x10, BLUE, BLACK);

		  if(flag_PIN_CS == true)ST7735_WriteString(10, 28, ":RF ON ", Font_7x10, GREEN, BLACK);
		  else if (flag_PIN_CS == false) ST7735_WriteString(10, 28, ":RF OFF", Font_7x10, RED, BLACK);

		  char buf15[3];
		  sprintf(buf15, ":LED %d%%", pers); // игнорировать!
		  if(pers != 100) ST7735_FillRectangle(65, 40, 7, 10, BLACK);
		  if(pers == 0) ST7735_FillRectangle(58, 40, 7, 10, BLACK);

		  if(pers == 100) ST7735_WriteString(10, 40, buf15, Font_7x10, GREEN, BLACK);
		  else if(pers == 80) ST7735_WriteString(10, 40, buf15, Font_7x10, ORANGE, BLACK);
		  else if(pers == 60) ST7735_WriteString(10, 40, buf15, Font_7x10, YELLOW, BLACK);
		  else if(pers == 40) ST7735_WriteString(10, 40, buf15, Font_7x10, YELLOW, BLACK);
		  else if(pers == 20) ST7735_WriteString(10, 40, buf15, Font_7x10, RED, BLACK);
		  else if(pers == 0) ST7735_WriteString(10, 40, buf15, Font_7x10, RED, BLACK);

		  char buf25[10];
		  sprintf(buf25, "%d", sost); // игнорировать!
		  //ST7735_WriteString(10, 80, buf25, Font_7x10, MAGENTA, BLACK);	//вывод значение регистра напряжения подсветки
		  if(flag_punkt == 1)
		  {
			  if((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_SET)) flag_but2 = 1;
			  if((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET))
			  {
				  flag_but = 1;
			  }
			  else flag_but = 0;
			  if(flag_but == 1 && flag_but2 == 1)
			  {
				  flag_PIN_SET ^= true;
				  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
				  flag_but2 = 0;
			  }
		  }

		  if(flag_punkt == 2)
		  {
			  if((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_SET)) flag_but2 = 1;
			  if((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET))
			  {
				  flag_but = 1;
			  }
			  else flag_but = 0;
			  if(flag_but == 1 && flag_but2 == 1)
			  {
				  flag_PIN_CS ^= true;
				  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
				  flag_but2 = 0;
			  }
		  }

		  if(flag_punkt == 4)
		  {
			  if((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_SET)) flag_but2 = 1;
			  if((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET))
			  {
				  flag_but = 1;
			  }
			  else flag_but = 0;
			  if(flag_but == 1 && flag_but2 == 1)
			  {
				  flag_but2 = 0;

				  flag_Setings = false;
				  flag_4  = false;
				  flag_Menu = true;
				  fillScreen(BLACK);
			  }
		  }

		  if(flag_punkt == 3)
		  {
			  if((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_SET)) flag_but2 = 1;
			  if((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET))
			  {
				  flag_but = 1;
			  }
			  else flag_but = 0;
			  if(flag_but == 1 && flag_but2 == 1)
			  {
				  flag_PWM_BLK ^= true;

				  flag_but2 = 0;
			  }
		  }
	  }
	  HAL_UART_Receive_IT(&huart1, (uint8_t*) &transmit, sizeof(transmit));
	  //////////////////////////////////////////////////////////////////////////////

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 5;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_8B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 3;
  hadc1.Init.DMAContinuousRequests = ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = 3;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 50000;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 500;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief TIM9 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM9_Init(void)
{

  /* USER CODE BEGIN TIM9_Init 0 */

  /* USER CODE END TIM9_Init 0 */

  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM9_Init 1 */

  /* USER CODE END TIM9_Init 1 */
  htim9.Instance = TIM9;
  htim9.Init.Prescaler = 0;
  htim9.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim9.Init.Period = 60000;
  htim9.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim9.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim9) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 30000;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM9_Init 2 */

  /* USER CODE END TIM9_Init 2 */
  HAL_TIM_MspPostInit(&htim9);

}

/**
  * @brief TIM10 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM10_Init(void)
{

  /* USER CODE BEGIN TIM10_Init 0 */

  /* USER CODE END TIM10_Init 0 */

  /* USER CODE BEGIN TIM10_Init 1 */

  /* USER CODE END TIM10_Init 1 */
  htim10.Instance = TIM10;
  htim10.Init.Prescaler = 50000;
  htim10.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim10.Init.Period = 50;
  htim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim10.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim10) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM10_Init 2 */

  /* USER CODE END TIM10_Init 2 */

}

/**
  * @brief TIM11 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM11_Init(void)
{

  /* USER CODE BEGIN TIM11_Init 0 */

  /* USER CODE END TIM11_Init 0 */

  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM11_Init 1 */

  /* USER CODE END TIM11_Init 1 */
  htim11.Instance = TIM11;
  htim11.Init.Prescaler = 0;
  htim11.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim11.Init.Period = 65535;
  htim11.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim11.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim11) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim11) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim11, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM11_Init 2 */

  /* USER CODE END TIM11_Init 2 */
  HAL_TIM_MspPostInit(&htim11);

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, TFT_CS_Pin|TFT_RST_Pin|TFT_DC_Pin|RF_SET_Pin
                          |SD_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(RF_CS_GPIO_Port, RF_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 BUT_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_0|BUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : TFT_CS_Pin TFT_DC_Pin */
  GPIO_InitStruct.Pin = TFT_CS_Pin|TFT_DC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : TFT_RST_Pin RF_SET_Pin */
  GPIO_InitStruct.Pin = TFT_RST_Pin|RF_SET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PIN_R_Pin */
  GPIO_InitStruct.Pin = PIN_R_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(PIN_R_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : RF_CS_Pin */
  GPIO_InitStruct.Pin = RF_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(RF_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BUT2_Pin */
  GPIO_InitStruct.Pin = BUT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BUT2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SD_CS_Pin */
  GPIO_InitStruct.Pin = SD_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(SD_CS_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
//----------------------------------------------------------
// Прерывания-счетчик полученных данных (срабатывает когда получаем данные)
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart1)
	{
		if(resive_OK == 99) resive_OK = 0;
		resive_OK += 1;
	}
}
//----------------------------------------------------------
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	  if (htim == &htim9)
	  {
		  Timer1++;
	  }
	  if (htim == &htim4)
	  {
		  if(SIGNAL == true) HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		  for(int i = 0; i < 3 ; i++)	// Постоянная проверка положения джойстика
		  {
		    u[i] = (float)(data[i]);
		  }
		  if(flag_PWM_BLK == false)
		  {
			  if(flag_Menu == true || flag_Setings == true)
			  {
				  if(u[0] < 60 && u[1] < 140 && u[1] > 110) // джойстик вниз
				  {
					  if(flag_punkt != 4) flag_punkt++;
					  else flag_punkt = 4;
				  }

				  if(u[0] > 180 && u[1] < 140 && u[1] > 110) // джойстик вверх
				  {
					  if(flag_punkt != 1) flag_punkt--;
					  else flag_punkt = 1;
				  }
			  }
		  }

		  if(flag_PWM_BLK == true) // выбор положения по горизонтали
		  {
			  if((u[1] < 60 && u[0] < 140 && u[0] > 110) && ((pers > 0) && (pers <= 100))) // влево
			  {
				  sost = TIM11->CCR1;
				  TIM11->CCR1 = TIM11->CCR1 - 13017;

				  pers = pers - 20;
			  }
			  if((u[1] > 180 && u[0] < 140 && u[0] > 110) && (pers < 100) && (pers >= 0)) // вправо
			  {
				  sost = TIM11->CCR1;
				  TIM11->CCR1 = TIM11->CCR1 + 13017;

				  pers = pers + 20;
			  }
		  }
	  }
	  if (htim == &htim10)
	  {
		  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == GPIO_PIN_RESET)
		  {
			  servoData = 1;
			  if(flag_Menu == true) fillCircle(148, 35, 5, YELLOW);
			  else fillCircle(148, 35, 5, BLACK);
			  HAL_UART_Transmit(&huart1, (uint8_t*) &servoData, sizeof(1) , 100);
			  /////////////////////////////////
			  SIGNAL = true;
		  }
		  SIGNAL = false;
		  u[2] = ((float)data[2])*3.3/256;
		  Batdata = u[2]* (128 / 3.3); // число от 0 до 128 // значение заряда акума. в диапазоне 0 - 128
	  }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{

}

//----------------------------------------------------------

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
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
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
