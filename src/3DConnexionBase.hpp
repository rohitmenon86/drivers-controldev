#ifndef _3DCONNEXION_BASE_HPP_
#define _3DCONNEXION_BASE_HPP_

#define CONNEXION_VENDOR_ID    0x046d

namespace controldev{
  
  struct AnalogValues {
    double tx;
    double ty;
    double tz;
    double rx;
    double ry;
    double rz;
    
    
    void setZero(){
      tx=0;
      ty=0;
      tz=0;
      rx=0;
      rz=0;
    };
  };


  class ConnexionBase{
    
  public:
    enum Mapping{
      TX = 0,
      TY,
      TZ,
      RX,
      RY,
      RZ
    };
    
    enum ProductID{
      
      CONNEXION_SPACE_TRAVELLER_DEVICE_ID= 0xc623,
      CONNEXION_SPACE_PILOT_DEVICE_ID=     0xc625,
      CONNEXION_SPACE_NAVIGATOR_DEVICE_ID= 0xc626,
      CONNEXION_SPACE_EXPLORER_DEVICE_ID=  0xc627,
      CONNEXION_SPACE_PILOT_PRO_DEVICE_ID= 0xc629
    };
      
    
    ConnexionBase();
     ~ConnexionBase();
    
    /* Scan all devices in /dev/input/ to find the SpaceMouse.
    * Returns the true if an SpaceMouse could be found.
    */
    bool init();
    
    void close();
    
    /**
    * Returns the file Decriptor, -1 if no valid FD is there
    */
    int getFileDescriptor();
    
    /** 
    * Refrence getter for axis scalinig, modifications are allowed via this reference member
    */
    double& axisScaling(Mapping id);
    
    
    void getValue(controldev::AnalogValues&, controldev::AnalogValues&);
    
  protected:
    int fd;
    double scale[6];
    AnalogValues oldValues;
    double r_scale;
    double t_scale;
    ProductID deviceID;
  };
}

#endif