#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// https://notisrac.github.io/FileToCArray/

int main() {
  srand(time(NULL));

  char answer[][6] = {"JIMIN", "GEONY", "YEONG"};
  char guess[6];
  int choose = rand() % (sizeof(answer) / sizeof(answer[0]));
  printf("WORD: %s\n", answer[choose]);
  printf("---------------\n");

  int end = 0;

  for (int count = 0; !end && count < 6; count++) {
    printf("GUESS %d: ", count + 1);
    scanf("%s", guess);

    // convert input to upper
    for (int upper = 0; upper < 5; upper++) {
      guess[upper] = toupper(guess[upper]);
    }

    int green_counter = 0;

    for (int i = 0; i < 5; i++) {
      int status = 0;
      for (int j = 0; j < 5; j++) {
        if (answer[choose][j] == guess[i]) {
          if (i == j) {
            status = 2;
            green_counter++;
          } else {
            if (status != 2) {
              status = 1;
            }
          }
        }
      }
      //   index[i] = status;
      if (status == 0) {
        printf("gray ");
      }
      if (status == 1) {
        printf("yellow ");
      }
      if (status == 2) {
        printf("green ");
      }
      if (green_counter == 5) {
        printf("YOU WIN\n");
        end = 1;
      }
    }
    printf("\n");
  }
  if (end == 0) {
    printf("YOU LOSE\n");
  }

  // 0:gray, 1:yellow 2: green

  return 0;
}