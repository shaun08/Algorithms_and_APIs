// 2021-02-20: SHAUN08 --> Run length encoding program in C

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define UINT8_OVERFLOW (255)

// This function encodes char buffer and returns the encoded buffer to client
// Client shall take care of verifying length of the encoded buffer and freeing memory
char* run_len_encoding(char *src_buf, size_t buf_size)
{
  int i=0;
  char current_char = '\0';
  char prev_char = current_char;
  uint8_t current_char_count = 0;
  char* ret_buf = NULL;
  char* dest_buf = NULL;

  if(buf_size)
  {
    dest_buf = (char *)malloc(sizeof(char)*buf_size*2);
    ret_buf = dest_buf;
  }

  for(i=0; i<buf_size; i++)
  {
    current_char = src_buf[i];

    // Action for first char in src buffer
    if(i==0)
    {
      prev_char = current_char;
      current_char_count++;
    }
    else // action for the rest of the chars
    {
      if(current_char == prev_char)
      {
        // Overflow check for current char count
        if((current_char_count+1) == UINT8_OVERFLOW)
        {
          *dest_buf = prev_char;
          *dest_buf = ++current_char_count;
          current_char_count = 0;
        }
        else
          current_char_count++;
      }
      else // New character encountered
      {
        *dest_buf++ = prev_char;
        *dest_buf++ = current_char_count;

        prev_char = current_char;
        current_char_count = 1;
      }
    }
  }

  // Fill up last char and its count in the buffer
  if(current_char_count)
  {
    *dest_buf++ = prev_char;
    *dest_buf++ = current_char_count;
    *dest_buf = '\0';
  }

  return ret_buf;
}

int main()
{
    char *src_buffer = "aabbaaccddddddddef";

    printf("Src_buf = %s\n",src_buffer);

    char *dst_buffer = run_len_encoding(src_buffer, 0);//strlen(src_buffer));

    // Dummy client decoder for verification
    if(dst_buffer)
    {
        size_t i=0, len = strlen(dst_buffer);
        printf("Dst_buf = ");
        while(i < len)
        {
            if( (i%2) == 0)
                printf("%c", dst_buffer[i++]);
            else
                printf("%u", (uint8_t)dst_buffer[i++]);
        }
        printf("\n");
        free(dst_buffer);
    }

    return 0;
}
