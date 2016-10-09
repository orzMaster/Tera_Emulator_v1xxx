#include "UnionSystem.h"

void UnionSystem::SendElectionState(Client * client)
{
	Stream s = Stream();

	s.WriteInt16(26);
	s.WriteInt16(S_CURRENT_ELECTION_STATE);

	s.WriteInt32(0);
	s.WriteInt32(11);
	s.WriteInt32(0);

	s.WriteInt16(0);
	s.WriteInt64(ServerTimer::GetCurrentUTC() - 3412319); //341231 = 39 days, 11 hours, 51 minutes and 59 seconds.
	s.WritePos(0);
	client->Send(s._raw, s._size);
}
