#ifndef SRC_INCLUDES_CLIENTS_CLIENTDATA_HPP
#define SRC_INCLUDES_CLIENTS_CLIENTDATA_HPP

#define BYTE unsigned char
#define DWORD unsigned int

namespace clients {
  typedef struct tagTDATA {
    BYTE cPriority; //request priority 0 – 255 (0 – the highest priority)
    DWORD dwTicks; //time when request forming in system ticks
    DWORD dwClientId; //unique client identifier
    char Data[255]; //abstract data
  } TDATA, *PTDATA;

  struct TDATA_Compare {
    bool operator() (const TDATA& l, const TDATA& r) const {
      return l.cPriority < r.cPriority;
    }
  };
}

#endif /* SRC_INCLUDES_CLIENTS_CLIENTDATA_HPP */
