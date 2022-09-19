import veins.base.utils.Coord;
import veins.modules.messages.BaseFrame1609_4;
import veins.base.utils.SimpleAddress;

namespace veins;

packet AccidentMessage extends BaseFrame1609_4     
{
	string a_description;	
	Coord a_location;
	double a_speed;
}