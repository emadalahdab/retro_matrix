// -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: nil; -*-
// Small example how to use the library.
// For more examples, look at demo-main.cc
//
// This code is public domain
// (but note, that the led-matrix library this depends on is GPL v2)


#include "led-matrix.h"
#include "retro_matrix.h"


#include "graphics.h"
#include "mylib.h"

#include <getopt.h>
#include <string>

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h> 
#include <iostream>
#include <vector> 

#include <map>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <linux/input.h>
#include <cstdlib>
#include "libevdev.h"
using rgb_matrix::Font;
using rgb_matrix::Canvas;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Color;

using namespace std;

/*
volatile bool interrupt_received = false;

static void InterruptHandler(int signo) {
  interrupt_received = true;
}
* */


void RetroMatrix::draw_menu(vector<Button> buttons){
	
  int current_selected = 0;
    
  rgb_matrix::Font font;
  if (!font.LoadFont("./rpi-rgb-led-matrix/fonts/4x6.bdf")) {
    fprintf(stderr, "Couldn't load font \n");
  
  }
  
  // make buttons 

  int letter_spacing = 0;

  
  Color bg_color(0, 0, 0);
  Color bright_color(150*brightness, 0, 255*brightness);
  Color dim_color(70*brightness, 0, 150*brightness);
  Color highlight_color(255*brightness,255*brightness,255*brightness);
  
  
  int selected_button = get_selected_button(buttons);
  list <ControllerInput> inputs;
  ResetCanvas(canvas, 64, 64, bg_color);
  draw_buttons(canvas, buttons, font, bright_color, dim_color);
  get_inputs_from_ps4(dev); //clear input buffer
  int fd;
  int rc;
  struct input_event ev;
  string button_target;
  vector<Button> target_buttons;
  cout << "size: "<<buttons.size() << endl;
  while(true){
      inputs = get_inputs_from_ps4(dev);
      for(const auto &input: inputs){
        switch(input.type) {  // go from first input as unlikely to have multiple inputs perframes with no sleep

          case 'y':
            change_selected_button(buttons, input.value, current_selected);
            draw_buttons(canvas, buttons, font, bright_color, dim_color);
            break;
            
          case 'S':
            if(input.value == 1){
              ResetCanvas(canvas, n_rows, n_cols, bg_color);
              return;
            }
            break;
          case 'E':
            
            
            if(input.value == 1){
		      
		selected_button = get_selected_button(buttons);
		button_target = buttons[selected_button].label;
		ResetCanvas(canvas, 64, 64, bg_color);
		// buttons that run programs
		if(button_target.compare("1 PLAYER") ==0){
		  one_p_snake();
		}//else if(button_target.compare("2 PLAYER") ==0){
		  //two_p_snake();
		}else if(button_target.compare("TETRIS") ==0){
		  run_tetris();
		}else if(button_target.compare("GAME OF LIFE") ==0){
		  run_GOL();
		}else if(button_target.compare("RULE 30") ==0){
		  run_R30();
		}else if(button_target.compare("LANGTON'S ANT") ==0){
		  run_ant();
		}else if(button_target.compare("LANGTON'S LOOP") ==0){
		  run_loop();
		  
		}else if(button_target.compare("SHUTDOWN") ==0){
		  system("sudo shutdown now");
		  
		}else if(button_target.compare("SPACE INVADERS") ==0){
		  run_space_invaders();
		
		
		  
		  //menu buttons
		} else {
		  target_buttons = menu_structure[button_target];
		  draw_menu(target_buttons);
		}
		ResetCanvas(canvas, n_rows, n_cols, bg_color);
              }
	      draw_buttons(canvas, buttons, font, bright_color, dim_color);
	      get_inputs_from_ps4(dev); //clear input buffer
              break;
             case 'D': // controller disconnect
              fd = open("/dev/input/event6", O_RDONLY|O_NONBLOCK);
              rc = libevdev_new_from_fd(fd, &dev);
              break;
            default:
              break;
            
        }
      }
  
}
	
}




  
/*

int main(int argc, char *argv[]) {
  RGBMatrix::Options defaults;
  defaults.hardware_mapping = "adafruit-hat";  // or e.g. "adafruit-hat"
  defaults.rows = 32;
  defaults.cols = 64;
  defaults.chain_length = 1;
  defaults.parallel = 1;
  defaults.show_refresh_rate = false;
  
  // use --led-slowdown-gpio=4
  
  Canvas *canvas = rgb_matrix::CreateMatrixFromFlags(&argc, &argv, &defaults);
  if (canvas == NULL)
    return 1;
  

  // It is always good to set up a signal handler to cleanly exit when we
  // receive a CTRL-C for instance. The DrawOnCanvas() routine is looking
  // for that.
  //signal(SIGTERM, InterruptHandler);
  //signal(SIGINT, InterruptHandler);

  DrawOnCanvas(canvas);    // Using the canvas.

  // Animation finished. Shut down the RGB matrix.
  canvas->Clear();
  delete canvas;

  return 0;
}
* */
