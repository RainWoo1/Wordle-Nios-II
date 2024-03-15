#include <stdio.h>
#include <stdlib.h>

char *word_list[] = {"aback", "funky", "nerve", "skirt",
                     "scamp", "heart", "giant", "olive"};

char game_board[5][6];

const short int test_screen[];  // full screen
const short int pixelart[];     // a character placeholder
const short int gray_screen[];

char alphabet[26][400];  // 20 X 20

char keyboard[26][274];  // 17 X 22

#define X_SCREEN_SIZE 320
#define Y_SCREEN_SIZE 240
#define num_box 10
#define box_length 5

volatile int pixel_buffer_start;  // global variable
short int Buffer1[240][512];      // 240 rows, 512 (320 + padding) columns
short int Buffer2[240][512];

void plot_pixel(int x, int y, short int line_color);
void clear_screen();
void wait_for_vsync();

int colour[10] = {0xffff, 0xf800, 0x07e0, 0x001f, 0xffff,
                  0xf800, 0x07e0, 0x001f, 0xffff, 0xf800};

void plot_pixel(int x, int y, short int line_color) {
  volatile short int *one_pixel_address;
  // copy back buffer to front buffer
  //   Buffer1[x][y] = Buffer2[x][y];
  // input new color in front buffer
  // Buffer2[x][y] = line_color;
  one_pixel_address = (short int *)(pixel_buffer_start + (y << 10) + (x << 1));
  *one_pixel_address = line_color;
}

void clear_screen() {
  int y, x;

  for (x = 0; x < 320; x++) {
    for (y = 0; y < 240; y++) {
      plot_pixel(x, y, 0x0000);
    }
  }
}

void wait_for_vsync() {
  volatile int *pixel_ctrl_ptr = (int *)0xff203020;  // base address
  int status;

  *pixel_ctrl_ptr = 1;             // start the synchronization process
                                   // write 1 into front buffer address register
  status = *(pixel_ctrl_ptr + 3);  // read the status register

  while ((status & 0x01) != 0)  // polling loop waiting for S bit to go to 0
  {
    status = *(pixel_ctrl_ptr + 3);
  }
}

int main(void) {
  volatile int *pixel_ctrl_ptr = (int *)0xFF203020;
  // declare other variables(not shown)
  // initialize location and direction of rectangles(not shown)

  /* set front pixel buffer to Buffer 1 */
  *(pixel_ctrl_ptr + 1) =
      (int)&Buffer1;  // first store the address in the  back buffer
  /* now, swap the front/back buffers, to set the front buffer location */
  wait_for_vsync();
  /* initialize a pointer to the pixel buffer, used by drawing functions */
  pixel_buffer_start = *pixel_ctrl_ptr;
  clear_screen();  // pixel_buffer_start points to the pixel buffer

  /* set back pixel buffer to Buffer 2 */
  *(pixel_ctrl_ptr + 1) = (int)&Buffer2;
  pixel_buffer_start = *(pixel_ctrl_ptr + 1);  // we draw on the back buffer
  clear_screen();  // pixel_buffer_start points to the pixel buffer

  while (1) {
    // code for drawing the boxes and lines (not shown)
    for (int i = 0; i < X_SCREEN_SIZE; ++i) {
      for (int j = 0; j < Y_SCREEN_SIZE; ++j) {
        // if(test_screen[j * X_SCREEN_SIZE + i] == BLACK) {
        //     if(green) {
        //         plot_pixel(i, j, GREEN);
        //     }
        //     else if(yellow) {
        //         plot_pixel(i, j, YELLOW);

        //     }
        //     else if(gray) {
        //         plot_pixel(i, j, GRAY);
        //     }
        // }
        // else {
        //     plot_pixel(i, j, test_screen[j * X_SCREEN_SIZE + i]);
        // }
        plot_pixel(i, j, test_screen[j * X_SCREEN_SIZE + i]);
        //			  gray_screen
        // plot_pixel(i, j, pixelart[j * 20 + i]);
      }
    }

    wait_for_vsync();  // swap front and back buffers on VGA vertical sync
    pixel_buffer_start = *(pixel_ctrl_ptr + 1);  // new back buffer
  }
}