//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//
import veins.base.utils.Coord;
import veins.modules.messages.BaseFrame1609_4;
import veins.base.utils.SimpleAddress;

namespace veins;

message A2TMessage11p extends BaseFrame1609_4 {
    LAddress::L2Type senderAddress = -1;
    int serial = 0;
    
    // -------------------------- A2T --------------------------
	bool isFromAmbulance;	// Is the message sent by an ambulance ?
	string amuId;			// ID of the ambulance
	int priority; 			// Priority of the message
	string amuLaneId; 		// Lane ID of the ambulance
	double amuX;			// x position of the ambulance
	double amuY;			// y position of the ambulance
	double senderX;			// x position of the sender
	double senderY;			// y position of the sender
	int maxHop;				// Maximum number of hops of the message (lifespan)
	int hopCount; 			// Number of hops of the message
	// -------------------------- A2T --------------------------
}
