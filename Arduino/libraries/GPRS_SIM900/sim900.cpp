/*
 * sim900.cpp
 * A library for SeeedStudio seeeduino GPRS shield 
 *  
 * Copyright (c) 2015 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : lawliet zou
 * Create Time: April 2015
 * Change Log :
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "sim900.h"

#define DBG_PRINT(s) Serial.print(s)
#define DBG_PRINTLN(s) Serial.println(s)
//#define DBG_PRINT(s)
//#define DBG_PRINTLN(s)

SoftwareSerial *serialSIM900 = NULL;

void  sim900_init(void * uart_device, uint32_t baud)
{
    serialSIM900 = (SoftwareSerial*)uart_device;
	serialSIM900->begin(baud);
}

int sim900_check_readable()
{
    return serialSIM900->available();
}

int sim900_wait_readable (int wait_time)
{
    unsigned long timerStart;
    int dataLen = 0;
    timerStart = millis();
    while((unsigned long) (millis() - timerStart) > wait_time * 1000UL) {
        delay(500);
        dataLen = sim900_check_readable();
        if(dataLen > 0){
            break;
        }
    }
    return dataLen;
}

void sim900_flush_serial()
{
    while(sim900_check_readable()){
        char c = serialSIM900->read();
        delay(1);
    }
}

void sim900_read_buffer(char *buffer, int count, unsigned int timeout, unsigned int chartimeout)
{
  DBG_PRINT("### sim900_read_buffer: ");
    int i = 0;
    unsigned long timerStart, prevChar;
    timerStart = millis();
    prevChar = 0;
    while(1) {
        while (sim900_check_readable()) {
            char c = serialSIM900->read();
            prevChar = millis();
            buffer[i++] = c;
            if(i >= count)break;
            DBG_PRINT(c);
            delay(1);
        }
        if(i >= count)break;
        if ((unsigned long) (millis() - timerStart) > timeout * 1000UL) {
            break;
        }
        //If interchar Timeout => return FALSE. So we can return sooner from this function. Not DO it if we dont recieve at least one char (prevChar <> 0)
        if (((unsigned long) (millis() - prevChar) > chartimeout) && (prevChar != 0)) {
            break;
        }
        delay(1);
    }
  DBG_PRINTLN("#");
}

void sim900_clean_buffer(char *buffer, int count)
{
    for(int i=0; i < count; i++) {
        buffer[i] = '\0';
    }
}

//HACERR quitar esta funcion ?
void sim900_send_byte(uint8_t data)
{
	serialSIM900->write(data);
  DBG_PRINT((char)data);
}

void sim900_send_char(const char c)
{
	serialSIM900->write(c);
  DBG_PRINT(c);
}

void sim900_send_cmd(const char* cmd)
{
  DBG_PRINT("### sim900_send_cmd: ");
  for(int i=0; i<strlen(cmd); i++)
    {
        sim900_send_byte(cmd[i]);
    }
  DBG_PRINTLN("#");
}

void sim900_send_cmd(const __FlashStringHelper* cmd)
{
  DBG_PRINT("### sim900_send_cmd (flash): ");
  int i = 0;
  const char *ptr = (const char *) cmd;
  while (pgm_read_byte(ptr + i) != 0x00) {
    sim900_send_byte(pgm_read_byte(ptr + i++));  
    delay(1);
  }
  DBG_PRINTLN("#");
}

void sim900_send_cmd_P(const char* cmd)
{
  DBG_PRINT("### sim900_send_cmd_P: ");
  while (pgm_read_byte(cmd) != 0x00) {
    sim900_send_byte(pgm_read_byte(cmd++));
    delay(1);
  }
  DBG_PRINTLN("#");
}

void sim900_send_AT(void)
{
    sim900_check_with_cmd(F("AT\r\n"),"OK",CMD);
}

void sim900_send_End_Mark(void)
{
    sim900_send_byte((char)26);
}

boolean sim900_wait_for_resp(const char* resp, DataType type, unsigned int timeout, unsigned int chartimeout)
{
  DBG_PRINT("### sim900_wait_for_resp: ");
    int len = strlen(resp);
    int sum = 0;
    unsigned long timerStart, prevChar;    //prevChar is the time when the previous Char has been read.
    timerStart = millis();
    prevChar = 0;
    while(1) {
        if(sim900_check_readable()) {
            char c = serialSIM900->read();
            prevChar = millis();
            sum = (c==resp[sum]) ? sum+1 : 0;
            if(sum == len)break;
            DBG_PRINT(c);
        }
        if ((unsigned long) (millis() - timerStart) > timeout * 1000UL) {
          DBG_PRINTLN("#timeout#");
            return false;
        }
        //If interchar Timeout => return FALSE. So we can return sooner from this function.
        if (((unsigned long) (millis() - prevChar) > chartimeout) && (prevChar != 0)) {
          DBG_PRINTLN("#interchar timeout#");
            return false;
        }
        delay(1);
    }
    DBG_PRINTLN("#");
    //If is a CMD, we will finish to read buffer.
    if(type == CMD) sim900_flush_serial();
    return true;   
}


boolean sim900_check_with_cmd(const char* cmd, const char *resp, DataType type, unsigned int timeout, unsigned int chartimeout)
{
  DBG_PRINTLN("### sim900_check_with_cmd");
    sim900_send_cmd(cmd);
    return sim900_wait_for_resp(resp,type,timeout,chartimeout);
}

//HACERR que tambien la respuesta pueda ser FLASH STRING
boolean sim900_check_with_cmd(const __FlashStringHelper* cmd, const char *resp, DataType type, unsigned int timeout, unsigned int chartimeout)
{
  DBG_PRINTLN("### sim900_check_with_cmd (flash)");
    sim900_send_cmd(cmd);
    return sim900_wait_for_resp(resp,type,timeout,chartimeout);
}

