#ifndef __BARCODEEXCEPTION_H__
#define __BARCODEEXCEPTION_H__

#include <exception>
#include <iostream>
#include <string>
namespace sojet {
namespace barcode {

 /**
  * Checked exception thrown when a barcode is constructed with invalid
  * data or options.
  */
class BarcodeException : public std::exception {
public:
    BarcodeException(const std::string& errmsg):m_Msg(errmsg){

    }

    const char * what () const throw () {
        return m_Msg.c_str();
    }
private:
    std::string m_Msg;
};

}
}

#endif //__BARCODEEXCEPTION_H__
