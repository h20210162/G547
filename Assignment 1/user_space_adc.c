#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>              /* open */
#include <unistd.h>             /* exit */
#include <stdint.h>
#include <sys/ioctl.h>          /* ioctl */
#include "chardev_adc.h"


uint16_t data;


int ioctl_channel_select(int file_desc, int *channel)
{
    int ret_val;
    ret_val = ioctl(file_desc, Channel_select, channel);
    if (ret_val < 0) 
    {
        printf("ioctl_channel_select failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}

int ioctl_alignment_select(int file_desc, int *align)
{
    int ret_val;
    ret_val = ioctl(file_desc, alignment_select, align);
    if (ret_val < 0) 
    {
        printf("ioctl_alignment_select failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}
                                                                             // conversion of data into binary representation
void binary(uint16_t n)
{
  int b[16];
  int i = 0;
  while (n > 0) 
  {
      b[i] = n % 2;
      n = n / 2;
      i++;
  }
  printf("number in binary is:");
  
  for (int j = i - 1; j >= 0; j--)
     {
      printf("%d", b[j]);
     }
      printf("\n");
if (n < 0)
{
  printf("enter a real number..");
  printf("data in binary form is : ");
}
} 

                                                                            // Calling the ioctl functions for data flow to user space

int main()
{
    int file_desc, ret_val;
    int channel;
    int align;
    int mode;
    file_desc = open(DEVICE_FILE_NAME, 0);
    if (file_desc < 0) 
    {
        printf("Can't open device file: %s\n", DEVICE_FILE_NAME);
        exit(-1);
    }
    
                                                                               // selection of adc channels and alignment of data
    printf("select a Channel between 0 to 7: ");
    scanf("%d", &channel);
    printf("select left or right Alignment ( '0' for left alignment, '1' for right alignment): ");
    scanf("%d", &align);
    printf("select the conversin mode i.e single shot or continous ( '0' for singleshot '1' for continous): ");
    scanf(" %d", &mode);
       
    ioctl_channel_select(file_desc, &channel);
    ioctl_alignment_select(file_desc, &align);
    read(file_desc,&data,sizeof(data));
    {
      if(align == 0)
      {
          printf("left alignment number is :- %u\n", data);
          binary(data); 
          printf("data read from ADC is : %u\n ", data);
          data = data*16;
          binary(data);
      }
      else if(align == 1)
      {
          printf("left alignment number is :- %u\n", data);
          binary(data); 
          printf("data read from ADC is : %u\n ", data);
          data = data*16;
          binary(data);
      }
    }
    
    close(file_desc);
    return 0;
}
