
#include "SSEReadOutHit.h"

G4ThreadLocal G4Allocator<SSEReadOutHit>* SSEReadOutHitAllocator=0;

SSEReadOutHit::SSEReadOutHit() 
{ }

SSEReadOutHit::SSEReadOutHit(const SSEReadOutHit &right): G4VHit()
{ }

SSEReadOutHit::~SSEReadOutHit()
{ }


const SSEReadOutHit& SSEReadOutHit::operator=(const SSEReadOutHit & right) 
{
  return *this; 
}

G4bool SSEReadOutHit::operator==(const SSEReadOutHit &right) const 
{ 
  return 1;
}

void SSEReadOutHit::Draw()
{ }


void SSEReadOutHit::Print()
{ }


