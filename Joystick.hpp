#ifndef JOYSTICK_HPP
#define JOYSTICK_HPP

#include <string>

namespace controldev
{
    class Joystick {
      public:
      Joystick();
      ~Joystick();

      enum Axis
      {
          AXIS_Sideward = 0,
          AXIS_Forward = 1,
          AXIS_Pan = 4,
          AXIS_Tilt = 5, // What is the Tilt-Axis?
      };

//      static const int FORWARD_AXIS = 1;
//      static const int SIDEWARD_AXIS = 0;
//      static const int PAN_AXIS = 4;
//      static const int TILT_AXIS = 5;

      bool init(std::string const& dev);
      
      void setDeadspot(bool onOff, double size);
      
      bool updateState();
      
      double getAxis(Axis axis_nr) const;

      bool getButtonPressed(int btn_nr) const;

      int getNrAxis() const {
        return nb_axes;
      }
      
      int getNrButtons() const {
        return nb_buttons;
      }

      int getFileDescriptor()
      {
          return fd;
      }

      private:
      int fd;
      bool initialized;
      bool deadspot;
      double deadspot_size;
      
      int *axes;
      int *buttons;
      unsigned char nb_buttons;
      unsigned char nb_axes;
        
    };
}     
#endif
