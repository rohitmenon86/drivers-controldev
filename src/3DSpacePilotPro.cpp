#include"3DSpacePilotPro.hpp"

#include <linux/input.h>
#include <dirent.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <iostream>

#define PATH_BUFFER_SIZE (1024)

namespace controldev{
  void SpacePilotPro::getValue(ControlButtons& rawControls, AnalogValues& rawValues)
  {

     assert(fd > 0);
     rawValues = oldValues;
     rawControls= oldControls;
    
    /* If input events don't come in fast enough a certain DoF may not be 
     * updated during a frame. This results in choppy and ugly animation.
     * To solve this we record the number of frames a certain DoF was idle
     * and only set the DoF to 0 if we reach a certain idleThreshold.
     * When there is activity on a axis the idleFrameCount is reset to 0.
     */
    int i, eventCnt;
    /* how many bytes were read */
    size_t bytesRead;
    /* the events (up to 64 at once) */
    struct input_event events[64];
    /* keep track of idle frames for each DoF for smoother animation. see above */
    static int idleFrameCount[6] = {0, 0, 0, 0, 0, 0};
    int idleThreshold = 3;
    
    /* read the raw event data from the device */
    bytesRead = read(fd, events, sizeof(struct input_event) * 64);
    eventCnt = (int) ((long)bytesRead / (long)sizeof(struct input_event));
    if (bytesRead < (int) sizeof(struct input_event)) {
      perror("evtest: short read");
      return;
    }
    
    /* Increase all idle counts. They are later reset if there is activity */
    for(i = 0; i < 6; ++i) {
      ++idleFrameCount[i];
    }
    ButtonCode bCode;
    /* handle input events sequentially */
    for(i = 0; i < eventCnt; ++i) {
      if(EV_KEY == events[i].type) {
	std::cout<<"Event code= "<<std::hex<<events[i].code<<std::endl;
	
	switch(events[i].code) {
	  case BTN1:
	    rawControls.button1 = events[i].value;
	    break;
	  case BTN2:
	    rawControls.button2 = events[i].value;
	    break;
	  case BTN3:
	    rawControls.button3 = events[i].value;
	    break;
	  case BTN4:
	    rawControls.button4 = events[i].value; 
	    break;
	  case BTN5:
	    rawControls.button5 = events[i].value;  
	    break;
	  case BTN6:
	    rawControls.button6 = events[i].value;
	    break;
	  case BTN7:
	    rawControls.button7 = events[i].value;
	    break;
	  case BTN8:
	    rawControls.button8 = events[i].value;
	    break;
	  case BTN9:
	    rawControls.button9 = events[i].value;
	    break;
	  case BTN10:
	    rawControls.button10 = events[i].value;  
	    break;
	  case DOMAXIS:
	    rawControls.dominantAxis=events[i].value;
	    break;
	  case TRANS:
	    rawControls.translation=events[i].value;
	    break;
	  case ROT:
	    rawControls.rotation=events[i].value;
	    break;
	  case ESC:
	    rawControls.esc=events[i].value;
	    break;
	  case CTRL:
	    rawControls.ctrl=events[i].value;
	    break;  
	  case ALT:
	    rawControls.alt=events[i].value;
	    break;
	  case SHIFT:
	    rawControls.shift=events[i].value;
	    break;
	  case INC:
	    rawControls.incSensitivity=events[i].value;
	    break;
	  case DEC:
	    rawControls.decSensitivity=events[i].value;
	    break;
	}
      } else if(EV_REL == events[i].type || EV_ABS == events[i].type) {
	switch(events[i].code) {
	  //case ABS_X: //Same value as REL_* so because of the check above, this is not needed
	  case REL_X:
	    rawValues.tx = events[i].value/t_scale;
	    idleFrameCount[0] = 0;
	    break;
	    //case ABS_Y:
	  case REL_Y:
	    rawValues.ty = events[i].value/t_scale;
	    idleFrameCount[1] = 0;
	    break;
	    //case ABS_Z:
	  case REL_Z:
	    rawValues.tz = events[i].value/t_scale;
	    idleFrameCount[2] = 0;
	    break;
	    //case ABS_RX:
	  case REL_RX:
	    rawValues.rx = events[i].value/t_scale;
	    idleFrameCount[3] = 0;
	    break;
	    //case ABS_RY:
	  case REL_RY:
	    rawValues.ry = events[i].value/t_scale;
	    idleFrameCount[4] = 0;
	    break;
	    //case ABS_RZ:
	  case REL_RZ:
	    rawValues.rz = events[i].value/t_scale;
	    idleFrameCount[5] = 0;
	    break;
	}
      }
    }
    
    /* Set rawValue to zero if DoF was idle for more than idleThreshold frames */
    for(i = 0; i < 6; ++i) {
      if(idleFrameCount[i] >= idleThreshold) {
	if(0==i) {
	  rawValues.tx = 0;
	} else if (1==i) {
	  rawValues.ty = 0;
	} else if (2==i) {
	  rawValues.tz = 0;
	} else if (3==i) {
	  rawValues.rx = 0;
	} else if (4==i) {
	  rawValues.ry = 0;
	} else if (5==i) {
	  rawValues.rz = 0;
	}
      }
    }
    
    oldValues= rawValues;
  }
  
}