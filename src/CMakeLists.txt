rock_library(controldev
    SOURCES JoyPad.cpp  
            Joystick.cpp
	    LogitechG27.cpp  
	    SliderBox.cpp 
            ConnexionHID.cpp
            3DConnexionBase.cpp
            3DSpacePilotPro.cpp
    HEADERS JoyPad.hpp  
            Joystick.hpp  
	    LogitechG27.hpp  
	    SliderBox.hpp
            ConnexionHID.hpp
            3DConnexionBase.hpp
            3DSpacePilotPro.hpp
    DEPS_PKGCONFIG libsysfs libusb)



rock_executable(JoystickTest JoystickTest.cpp
    DEPS controldev)

rock_executable(ConnexionTest connexion_test.cpp
    DEPS controldev)

rock_executable(Test_3DMouse test_spacepilot.cpp
    DEPS controldev)

rock_executable(LogitechG27Init LogitechG27Init.cpp
    DEPS controldev)

ADD_EXECUTABLE(LogitechG27Test LogitechG27Test.cpp)
TARGET_LINK_LIBRARIES(LogitechG27Test controldev pthread)

rock_executable(SliderboxTest testSB.cpp
    DEPS controldev)

