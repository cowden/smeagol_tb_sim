#ifndef WBACTIONINITIALIZATION_H
#define WBACTIONINITIALIZATION_H

//////////////////
// C S Cowden
////////////

#include "G4VUserActionInitialization.hh"

class WBDetectorConstruction;

class WBActionInitialization : public G4VUserActionInitialization
{
public:
  WBActionInitialization(WBDetectorConstruction*);
  virtual ~WBActionInitialization();

  virtual void BuildForMaster() const;
  virtual void Build() const;

private:
  WBDetectorConstruction * detConstruction_;
};

#endif
