#ifndef SSEPrimaryGeneratorAction_h
#define SSEPrimaryGeneratorAction_h

////////////////////////////////////
// C S Cowden
////////////////////////////////////

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;

class SSEPrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction
{
public:
  SSEPrimaryGeneratorAction();
  virtual ~SSEPrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event* event);

  void SetRandomFlag(G4bool value);

private:

  G4ParticleGun* particleGun_;

};


#endif
