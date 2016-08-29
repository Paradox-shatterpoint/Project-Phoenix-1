/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETCURRENTSKILLTITLECOMMAND_H_
#define SETCURRENTSKILLTITLECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetCurrentSkillTitleCommand : public QueueCommand {
public:

	SetCurrentSkillTitleCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == NULL)
			return GENERALERROR;

		String titleSkill = arguments.toString().toLowerCase();

		if (ghost->getAdminLevel() >= 15) {
			if (!titleSkill.isEmpty() && !creature->hasSkill(titleSkill))
			creature->sendSystemMessage("Overriding Skill Title - God Only");
		} else {
			if (!titleSkill.isEmpty() && !creature->hasSkill(titleSkill))
			return GENERALERROR;
		}

		ghost->setTitle(titleSkill, true);
		creature->sendSystemMessage("Your Title was set to: " + titleSkill);
		//creature->playEffect("clienteffect/int_camshake_heavy.cef", "head"); no more of this nonsense plz. i will die

		return SUCCESS;
	}

};

#endif //SETCURRENTSKILLTITLECOMMAND_H_