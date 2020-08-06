#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "xmem.h"
#include "xis.h"
#include "xcpu.h"

extern int xcpu_execute( xcpu *c ) {

  //Read instruction from memory
  unsigned char instruction[2];
  xmem_load(c->pc,instruction);

  //Increment the program counter by 2 bytes as each instruction is 16 bits
  (c->pc) += 2;
  
  //Variables to hold the registers
  unsigned short reg2 = XIS_REG2(instruction[1]);
  unsigned short reg1 = XIS_REG1(instruction[1]);

  //Values to use with the data transfer/conversion functions
  unsigned short* ptr;
  unsigned char data[2];
  unsigned char hold;

  //Decode the instruction, only need the first byte which is the op code
  //the second byte is the actual values needed to perform the stuff 
  switch(instruction[0]){

  case I_ADD:
    c->regs[reg2] = (c->regs[reg2])+(c->regs[reg1]);
    break;

  case I_SUB:
    c->regs[reg2] = (c->regs[reg2])-(c->regs[reg1]);
    break;
  
 case I_MUL:
    c->regs[reg2] = (c->regs[reg2])*(c->regs[reg1]);
    break;

  case I_DIV:
    c->regs[reg2] = (c->regs[reg2])/(c->regs[reg1]);
    break;

  case I_AND:
    c->regs[reg2] = (c->regs[reg2])&(c->regs[reg1]);
    break;
  
  case I_OR:
    c->regs[reg2] = (c->regs[reg2])|(c->regs[reg1]);
    break;

  case I_XOR:
    c->regs[reg2] = (c->regs[reg2])^(c->regs[reg1]);
    break;

  case I_SHR:
    c->regs[reg2] = (c->regs[reg2])>>(c->regs[reg1]);
    break;

  case I_SHL:
    c->regs[reg2] = (c->regs[reg2])<<(c->regs[reg1]);
    break;

  case I_TEST:
    if ((c->regs[reg1] & c->regs[reg2]) != 0){
      c->state = c->state | 0x0001;
    }
    else{
      c->state = c->state & 0xFFFE;
    }
    break;

  case I_CMP:
    if (c->regs[reg1] <  c->regs[reg2]){
      c->state = c->state | 0x0001;
    }
    else{
      c->state = c->state & 0xFFFE;
    }
    break;

  case I_EQU:
    if (c->regs[reg1] ==  c->regs[reg2]){
      c->state = c->state | 0X0001;
    }
    else{
      c->state = c->state & 0xFFFE; 
    }
    break;

  case I_MOV:
    c->regs[reg2] = c->regs[reg1];
    break;

  case I_LOAD:
    //Convert data stored in the register to a char array so it can be used with xmem_load
    ShortToChar(c->regs[reg2], data);
    xmem_load(c->regs[reg1], data);
    //Set our pointer to data stored in the second register
    *ptr = c->regs[reg2];
    //Convert to a short
    CharToShort(data, ptr);
    //Set the register to the first byte of ptr
    c->regs[reg2] = ptr[0];
    break;

  case I_STOR:
    ShortToChar(c->regs[reg1], data);
    xmem_store(data, c->regs[reg2]);
    break;

  case I_LOADB:
    //Same as above load but only for 1 byte
    //Hold used to account for endian differences between xsim and unix
    ShortToChar(c->regs[reg2], data);
    hold = data[0];
    xmem_load(c->regs[reg1], data);
    *ptr = c->regs[reg2];
    data[0] = hold;
    CharToShort(data, ptr);
    c->regs[reg2] = ptr[0];
    break;

  case I_STORB:
    //Hold use to account for endian differences between xsim and unix
    xmem_load(c->regs[reg2], data);
    hold = data[1];
    ShortToChar(c->regs[reg1], data);
    data[0] = hold;
    xmem_store(data, c->regs[reg2]);
    break;

  case I_NEG:
    c->regs[reg2] = -(c->regs[reg2]);
    break;

  case I_NOT:
    c->regs[reg1] = !(c->regs[reg1]);
    break;

  case I_INC:
    c->regs[reg1] = c->regs[reg1] + 1;
    break;

  case I_DEC:
    c->regs[reg1] = c->regs[reg1] - 1;
    break;

  case I_PUSH:
    c->regs[15] = c->regs[15] - 2;
    ShortToChar(c->regs[reg1], data);
    xmem_store(data, c->regs[15]);
    break;

  case I_POP:
    ShortToChar(c->regs[reg1], data);
    xmem_load(c->regs[15], data);
    *ptr = c->regs[reg1];
    CharToShort(data, ptr);
    c->regs[15] = c->regs[15] + 2;
    break;

  case I_JMPR:
    c->pc = c->regs[reg1];
    break;

  case I_CALLR:
    c->regs[15] = c->regs[15] - 2;
    ShortToChar(c->pc, data);
    xmem_store(data, c->regs[15]);
    c->pc = c->regs[reg1];
    break;

  case I_OUT:
    putchar(c->regs[reg1]);
    break;

  case I_BR:
    if ((c->state & 0x0001) == 0x001){
      c->pc = c->pc - 2;
      c->pc = c->pc + instruction[1];
    }
    break;

  case I_JR:
    c->pc = c->pc + instruction[1];
    break;

  case I_RET:
    ShortToChar(c->pc, data);
    xmem_load(c->regs[15], data);
    ptr[0] = 0;
    CharToShort(data, ptr);
    c->pc = ptr[0];
    c->regs[15] = c->regs[15] + 2;
    break;

  case I_CLD:
    c->state = c->state & 0xFFFD;
    break;

  case I_STD:
    c->state = c->state | 0x0002;
    break;

  case I_JMP:
    xmem_load(c->pc, data);
    CharToShort(data, ptr);
    c->pc = ptr[0];
    break;

  case I_CALL:
    c->regs[15] = c->regs[15] - 2;
    ShortToChar(c->pc + 2, data);
    xmem_store(data, c->regs[15]);
    xmem_load(c->pc, data);
    CharToShort(data, ptr);
    c->pc = ptr[0];
    break;

  case I_LOADI:
    ShortToChar(c->regs[reg1], data);
    xmem_load(c->pc, data);
    *ptr = c->regs[reg1];
    CharToShort(data, ptr);
    c->regs[reg1] = ptr[0];
    c->pc = c->pc + 2;
    break;

  case I_BAD:
    return 0;
    break;

  default:
    return 1;
    break;
  }
  //Check for debug flag, if on call xcpu_print()
  int debugFlag = CHECK_BIT(c->state);
  if(debugFlag == 1){
    xcpu_print(c);
  }

  return 1;
}

/* Not needed for assignment 1 */
int xcpu_exception( xcpu *c, unsigned int  ex ) {
  return 0;
}

//Converts from a Short to a Char so it can be used with the xmem functions
void ShortToChar(unsigned short dataShort, unsigned char data[2]){
  //Extracts the first byte of the short and stores it in the end of the data array
  //This accounts for the Endian discrepency between the xsim and the unix OS
  data[1] = dataShort & 0xff;
  data[0] = (dataShort >> 8) & 0xff;
}

//Same as above but reverse
void CharToShort(unsigned char data[2], unsigned short *dataShort){
  //We just need to load the array into the short pointer
 *dataShort = data[0] << 8 | data[1];
}

