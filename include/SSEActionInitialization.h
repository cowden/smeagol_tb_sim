#ifndef SSEActionInitialization_h
#define SSEActionInitialization_h

///////////////////////////////////////////
// C S Cowden
///////////////////////////////////////////

#include "G4VUserActionInitialization.hh"

class SSEDetectorConstruction;

class SSEActionInitialization: public G4VUserActionInitialization
{
public:
  SSEActionInitialization(SSEDetectorConstruction*);
  virtual ~SSEActionInitialization();

  virtual void BuildForMaster() const;
  virtual void Build() const;

private:
  SSEDetectorConstruction * detConstruction_;

};

#endif
