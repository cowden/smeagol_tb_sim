#ifndef SSESTACKINGACTION_H
#define SSESTACKINGACTION_H

#include "G4UserStackingAction.hh"
#include "G4ClassificationOfNewTrack.hh"

class G4Track;

class SSEStackingAction : public G4UserStackingAction {
public:

  /**
  * Default constructor
  */
  SSEStackingAction();

  /**
  * The Destructor!
  */
  virtual ~SSEStackingAction();

  /**
  * Use the classification of new tracks to 
  * extract some information of each new track.
  */
  virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* );

  /*
  * Virtual method implemented by user, not used by smeagol
  */
  virtual void NewStage();

  /**
  * Virtual method implemented by user, not used by smeagol
  */
  virtual void PrepareNewEvent();

private:

};

#endif
